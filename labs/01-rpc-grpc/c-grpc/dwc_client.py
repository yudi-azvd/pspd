#!/usr/bin/python

from __future__ import print_function
import sys
from functools import reduce
from concurrent import futures
import logging

import grpc

from dwc_pb2 import DwcRequest, DwcResponse
from dwc_pb2_grpc import DistributedWordCounterStub


def read_content_from_file(file_path: str):
    with open(file_path, 'r') as f:
        content = f.read()
    return content.split()


def merge_dwc_responses(response: DwcResponse, accumulator: DwcResponse):
    for word in accumulator.word_frequency:
        if word in response.word_frequency:
            response.word_frequency[word] += accumulator.word_frequency[word]
        else:
            response.word_frequency[word] = accumulator.word_frequency[word]
    return response


def run(args: 'tuple[list[str], str]'):
    words, host = args
    with grpc.insecure_channel(host, options=(('grpc.enable_http_proxy', 0),)) as channel:
        stub1 = DistributedWordCounterStub(channel)
        response: DwcResponse = stub1.count(DwcRequest(words=words))
        return response


def main(file_path: str, hosts: 'list[str]'):
    words = read_content_from_file(file_path)

    with futures.ProcessPoolExecutor(max_workers=2) as executor:
        half = len(words)//2
        workers_args = zip([words[:half], words[half:]], hosts)
        responses = executor.map(run, workers_args)
        final_response = reduce(merge_dwc_responses, responses, DwcResponse())

        print('Words:')
        print(final_response.word_frequency)
        print('Total words:')
        print(len(final_response.word_frequency))


if __name__ == '__main__':
    if len(sys.argv) != 4:
        print(f'Usage: {sys.argv[0]} <file-path> <IP1:PORT1> <IP2:PORT2>')
        exit(1)

    argv = sys.argv
    logging.basicConfig()
    main(argv[1], [argv[2], argv[3]])

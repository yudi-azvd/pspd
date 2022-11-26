#!/usr/bin/python

from concurrent import futures
import logging

import grpc
from dwc_pb2 import DwcRequest, DwcResponse
import dwc_pb2_grpc


class Dwc(dwc_pb2_grpc.DistributedWordCounterServicer):
    def count(self, request: DwcRequest, context):
        words = request.words
        word_frequency = {}
        for w in words:
            if w not in word_frequency:
                word_frequency[w] = 1
            else:
                word_frequency[w] += 1

        print(word_frequency)
        return DwcResponse(word_frequency=word_frequency)


def serve():
    PORT = '50051'
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=5))
    dwc_pb2_grpc.add_DistributedWordCounterServicer_to_server(Dwc(), server)
    server.add_insecure_port('[::]:' + PORT)
    server.start()
    print('Server started, listening on ' + PORT)

    server.wait_for_termination()


if __name__ == '__main__':
    logging.basicConfig()
    serve()

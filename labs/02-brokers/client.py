#!/usr/bin/python

from pika.channel import Channel
from pika.frame import Method
from pika.spec import BasicProperties, Basic
from common import ROUTING_KEY
import pika
import sys
import json
import uuid


def divide_work(total_words: int, workers=1):
    '''Maneira muito ingênua de dividir o trabalho entre a quantidade
    de workers quase igualmente. A maior diferença é 1.'''
    words_for_worker = [0 for _ in range(workers)]
    i = 0
    total_words_original = total_words
    while total_words > 0:
        words_for_worker[i % workers] += 1
        total_words -= 1
        i += 1
    assert sum(words_for_worker) == total_words_original
    return words_for_worker


class WordCountMerger:
    word_count = {
        'word_len_6' : 0,
        'word_len_6_10' : 0,
        'words' : {},
    }

    @classmethod
    def merge(cls, word_count: dict):
        print(word_count.keys())
        cls.word_count['word_len_6'] += word_count['word_len_6']
        cls.word_count['word_len_6_10'] += word_count['word_len_6_10']

        for word in word_count['words']:
            if word not in cls.word_count['words']:
                cls.word_count['words'][word] = 1
            else:
                cls.word_count['words'][word] += 1

class WordCounterRpcClient:
    MAX_WORKERS = 6

    def __init__(self) -> None:
        self.connection = pika.BlockingConnection(
            pika.ConnectionParameters('localhost'))
        self.channel = self.connection.channel()
        result: Method = self.channel.queue_declare(queue='', exclusive=True)
        self.callback_queue = result.method.queue

        self.channel.basic_consume(
            queue=self.callback_queue,
            on_message_callback=self._on_response,
            auto_ack=True
        )
        self.response: dict = None
        self.corr_id = None

    def _on_response(self, channel, method, props, body: bytes):
        if self.corr_id == props.correlation_id:
            self.response = json.loads(body.decode())

    def call(self, words: 'list[str]'):
        self.response = dict()
        self.corr_id = str(uuid.uuid4())
        self._publish(words)
        self.connection.process_data_events(time_limit=None)

        return self.response

    def _publish(self, words: 'list[str]'):
        self.channel.basic_publish(
            exchange='',
            routing_key=ROUTING_KEY,
            properties=pika.BasicProperties(
                reply_to=self.callback_queue,
                correlation_id=self.corr_id,
            ),
            body=json.dumps(words)
        )


def read_content_from_file(file_path: str):
    with open(file_path, 'r') as f:
        content = f.read()
    return content.split()


def main():
    argv = sys.argv
    if len(argv) <= 2:
        print(f'Usage: python {argv[0]} <file-path:str> <workers:int>')
        exit(1)

    workers = int(argv[2])
    if workers not in range(0, 7):
        print('Number of worker should int the range [0, 6]')
        exit(1)

    file_path = argv[1]
    words = read_content_from_file(file_path)
    words_for_workers = divide_work(len(words), workers)
    print('>> words_for_worker', words_for_workers)
    client = WordCounterRpcClient()
    offset = 0
    for words_job in words_for_workers:
        words_slice = words[offset:offset+words_job]
        word_count = client.call(words_slice)
        offset += words_job
        WordCountMerger.merge(word_count)
        # print(word_count)
    print('After merge:')
    print('#len(word) in [6, 10]', WordCountMerger.word_count['word_len_6_10'])
    print('#len(word) < 6       ', WordCountMerger.word_count['word_len_6'])
    print('Total words          ', len(WordCountMerger.word_count['words']))


if __name__ == '__main__':
    main()

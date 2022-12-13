#!/usr/bin/python

import json
import sys
import pika
from pika.channel import Channel
from pika import BlockingConnection, ConnectionParameters
from pika.spec import BasicProperties, Basic
from common import ROUTING_KEY

def count_words(words: 'list[str]'):
    word_count = {}
    word_count['word_len_6'] = 0
    word_count['word_len_6_10'] = 0
    word_count['words'] = {}
    # print(type(words))
    # print(words)
    for word in words:
        word_len = len(word)
        if word_len < 6:
            word_count['word_len_6'] += 1
        elif 6 < word_len and word_len < 10:
            word_count['word_len_6_10'] += 1

        if word not in word_count['words']:
            word_count['words'][word] = 1
        else:
            word_count['words'][word] += 1
    return word_count


def on_request(channel: Channel, method: Basic.Deliver, props: BasicProperties, body: bytes):
    words = json.loads(body.decode())
    word_count = count_words(words)
    print(f'Received {len(words)} words')
    channel.basic_publish(
        exchange='', 
        routing_key=props.reply_to, 
        properties=pika.BasicProperties(correlation_id=props.correlation_id),
        body=json.dumps(word_count))
    channel.basic_ack(delivery_tag=method.delivery_tag)
    print('Waiting for messages...')

def main():
    connection = BlockingConnection(ConnectionParameters('localhost'))
    channel = connection.channel()
    channel.queue_declare(queue=ROUTING_KEY)
    channel.basic_qos(prefetch_count=1)
    channel.basic_consume(
        queue=ROUTING_KEY,
        on_message_callback=on_request
    )

    print('Waiting for messages...')
    channel.start_consuming()


if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print('Interrupted')
    try:
        sys.exit(0)
    except SystemExit:
        sys.exit(0)

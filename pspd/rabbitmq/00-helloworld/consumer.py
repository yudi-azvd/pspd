#!/usr/bin/python

import pika
from pika.channel import Channel
import sys

counter = 0

def main():
    connection = pika.BlockingConnection(pika.ConnectionParameters('localhost'))
    channel = connection.channel()

    channel.queue_declare('hello')

    def callback(channel: Channel, method, properties, body):
        print('[x] Received %r' % body)
        counter += 1

    channel.basic_consume(
        queue='hello',
        auto_ack=True,
        on_message_callback=callback
    )


    print('Waiting for messages')
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

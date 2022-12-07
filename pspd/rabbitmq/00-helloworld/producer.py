#!/usr/bin/python

import pika
import sys

message = 'Hwllo world'
if len(sys.argv) > 1:
    message = sys.argv[1]

connection = pika.BlockingConnection(pika.ConnectionParameters('localhost'))
channel = connection.channel()

channel.queue_declare(queue='hello')

channel.basic_publish(
    exchange='',
    routing_key='hello',
    body=message,
)

print(f'[x] Sent {message}')

connection.close()

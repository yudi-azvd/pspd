#!/usr/bin/python

import pika
import sys
import json

message = 'Hello world'
if len(sys.argv) > 1:
    message = ' '.join(sys.argv[1:])

connection = pika.BlockingConnection(pika.ConnectionParameters('localhost'))
channel = connection.channel()

channel.queue_declare(queue='hello')

channel.basic_publish(
    exchange='',
    routing_key='hello',
    body=json.dumps(message),
)

print(f'[x] Sent {message}')

connection.close()
'''

( 
python producer.py First message.
python producer.py Second message..
python producer.py Third message...
python producer.py Fourth message....
python producer.py Fifth message.....
)
'''

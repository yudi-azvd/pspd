#!/usr/bin/python

import pprint
import sys

if __name__ == '__main__':
  argv = sys.argv

  if len(argv) != 2:
    print('Usage: ./wc.py <file path>')
    exit(1)

  file_path = argv[1]
  with open(file_path, 'r') as f:
    content = f.read()
  
  words = content.split()
  word_frequency = {}

  for w in words:
    if w not in word_frequency:
      word_frequency[w] = 1
    else:
      word_frequency[w] += 1
  
  pp = pprint.PrettyPrinter(indent=2)
  pp.pprint(word_frequency)
  print(len(word_frequency))




  
  


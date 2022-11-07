#!/bin/bash
find . -iname "*.c" -o -iname "*.h" | xargs clang-format -i
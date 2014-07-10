#!/bin/sh

find ./ -name "*.d" -exec rm -v {} \;
find ./ -name "*.o" -exec rm -v {} \;
rm main.*

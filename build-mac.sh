#!/bin/bash
mkdir -p bin/mac
cp -r out/. bin/linux/
gcc src/main.c -g -ggdb -w -lraylib -lm -o bin/mac/main -std=c99 -pedantic
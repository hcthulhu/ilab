#!/bin/bash

gcc -c list1.c -o list1.o
gcc -c list2.c -o list2.o
gcc -Wall -g list1.o list2.o -o list12.exe
rm list1.o
rm list2.o
echo "Compilation succeful"

#!/bin/bash
echo g++ enemysharelib.cpp -c
rm -f enemysharelib.o
g++ enemysharelib.cpp -c

echo g++ microprocess.cpp -o enemymicroprocess
rm -f enemymicroprocess
g++ microprocess.cpp -o enemymicroprocess

echo g++ example.cpp enemysharelib.o -o runexample
rm -f runexample
g++ example.cpp enemysharelib.o -o runexample
#!/bin/bash
# Compile the .o file
echo g++ enemysharelib.cpp -c
rm -f enemysharelib.o
g++ enemysharelib.cpp -c

# Compile the microservice
echo g++ microprocess.cpp -o enemymicroprocess
rm -f enemymicroprocess
g++ microprocess.cpp -o enemymicroprocess

# Example program compilation
echo g++ example.cpp enemysharelib.o -o runexample
rm -f runexample
g++ example.cpp enemysharelib.o -o runexample
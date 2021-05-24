#!/bin/bash

g++ -std=c++14 -o3 $1.cpp -o $1
echo "$1"
./$1


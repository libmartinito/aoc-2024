#!/bin/bash

if [ "$#" -ne 1 ]; then
  echo "Usage: $0 <day>"
  exit 1
fi

DAY="$1"

g++ -std=c++11 -O2 -Wall day-"$DAY".cpp -o day-"$DAY"

if [ $? -eq 0 ]; then
  ./day-"$DAY"
else
  echo "Compilation failed"
  exit 1
fi

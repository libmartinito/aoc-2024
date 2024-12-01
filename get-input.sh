#!/bin/bash

if [ "$#" -ne 2 ]; then
  echo "Usage: $0 <year> <day>"
  exit 1
fi

YEAR="$1"
DAY="$2"

URL="https://adventofcode.com/$YEAR/day/$DAY/input"
HEADER="Cookie: session=$AOC_TOKEN"
OUTPUT_FILE="input/day-$DAY.txt"

curl -s -L -H "$HEADER" "$URL" -o "$OUTPUT_FILE"

echo "Raw body written to $OUTPUT_FILE"

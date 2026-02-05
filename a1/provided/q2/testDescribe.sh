#!/usr/bin/env bash

if [ $# -lt 1 ]; then
  echo "Usage: $0 <test-set-file>" >&2
  exit 1
fi

testset="$1"

if [ ! -r "$testset" ]; then
  echo "Error: cannot read test set file '$testset'" >&2
  exit 1
fi

while IFS= read -r line; do
  for stem in $line; do
    echo "Description for test case $stem:"
    desc="${stem}.desc"
    if [ -f "$desc" ]; then
      cat "$desc"
    else
      echo "$stem No test description"
    fi
  done
done < "$testset"
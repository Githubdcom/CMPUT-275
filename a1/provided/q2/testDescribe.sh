#!/bin/bash

# (a) No argument → usage message to stderr
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <test set file>" >&2
    exit 1
fi

testset="$1"

# Read each stem (whitespace-separated)
for stem in $(cat "$testset"); do
    echo "Description for test case $stem:"

    descfile="$stem.desc"

    if [ -f "$descfile" ]; then
        cat "$descfile"
    else
        echo "$stem No test description"
    fi
done

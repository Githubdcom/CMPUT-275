#!/usr/bin/env bash

# Usage error to stderr if no argument provided
if [ $# -lt 1 ]; then
    echo "Usage: $0 <test-set-file>" >&2
    exit 1
fi

testset="$1"

# Optional: verify the test set file is readable
if [ ! -r "$testset" ]; then
    echo "Error: cannot read test set file '$testset'" >&2
    exit 1
fi

# Iterate over all stems (strings separated by whitespace) in the test set file
# Handles absolute and relative paths; just appends ".desc" to check for description files.
while IFS= read -r line; do
    # Split the line by any whitespace into stems
    for stem in $line; do
    echo "Description for test case $stem:"
    desc="${stem}.desc"
    if [ -f "$desc" ]; then
        cat "$desc"
    else
        echo "$stem: No test description"
    fi
    done
done < "$testset"
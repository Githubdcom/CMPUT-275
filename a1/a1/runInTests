#!/usr/bin/env bash

# Check we got exactly 2 arguments
if [ $# -ne 2 ]; then
    echo "Usage: $0 <command> <test-set-file>" >&2
    exit 1
fi

cmd="$1"
testset="$2"

# Check test set file is readable
if [ ! -r "$testset" ]; then
    echo "Error: cannot read test set file '$testset'" >&2
    exit 1
fi

# Iterate over each stem in the test set file
while IFS= read -r line; do
    for stem in $line; do
        in_file="${stem}.in"
        out_file="${stem}.out"

    # Temporary file to hold actual output
    tmp_actual="$(mktemp)"

    # Run the command, redirecting input from stem.in and capturing output
    # We do: $cmd < "$in_file"
    if [ ! -r "$in_file" ]; then
        echo "Warning: input file '$in_file' not found or not readable" >&2
        rm -f "$tmp_actual"
        continue
    fi
    if [ ! -r "$out_file" ]; then
        echo "Warning: expected output file '$out_file' not found or not readable" >&2
        rm -f "$tmp_actual"
        continue
    fi

    # Run the command with input redirected, save stdout to tmp_actual
    $cmd < "$in_file" > "$tmp_actual"

    # Compare tmp_actual with stem.out using diff
    if diff -q "$tmp_actual" "$out_file" > /dev/null; then
        echo "Test $stem passed"
    else
        echo "Test $stem failed"
        echo "Expected output:"
        cat "$out_file"
        echo "Actual output:"
        cat "$tmp_actual"
    fi

    # Clean up temporary file
    rm -f "$tmp_actual"
    done
done < "$testset"
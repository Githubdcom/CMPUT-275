#!/usr/bin/env bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 <command> <test-set-file>" >&2
    exit 1
fi

cmd="$1"
testset="$2"

if [ ! -r "$testset" ]; then
    echo "Error: cannot read test set file '$testset'" >&2
    exit 1
fi

while IFS= read -r line; do
    for stem in $line; do
        in_file="${stem}.in"
        out_file="${stem}.out"
        args_file="${stem}.args"

    # Read args (empty if file missing)
    args=""
    if [ -f "$args_file" ]; then
        args="$(cat "$args_file")"
    fi

    # Capture actual output (stdout) of running: cmd < stem.in with args from stem.args
    actual="$($cmd $args < "$in_file")"

    # Compare with expected output
    if diff -q <(printf '%s\n' "$actual") "$out_file" >/dev/null; then
        echo "Test $stem passed"
    else
        echo "Test $stem failed"
        echo "Expected output:"
        cat "$out_file"
        echo "Actual output:"
        printf '%s\n' "$actual"
    fi
    done
done < "$testset"
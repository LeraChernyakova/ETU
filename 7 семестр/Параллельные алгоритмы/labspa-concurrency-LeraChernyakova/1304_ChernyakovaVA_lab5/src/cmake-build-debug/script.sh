#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <file1> <file2>"
    exit 1
fi

hash1=$(sha256sum "$1" | awk '{ print $1 }')

hash2=$(sha256sum "$2" | awk '{ print $1 }')

if [ "$hash1" == "$hash2" ]; then
    echo "The files have the same hash."
else
    echo "The files have different hashes."
fi

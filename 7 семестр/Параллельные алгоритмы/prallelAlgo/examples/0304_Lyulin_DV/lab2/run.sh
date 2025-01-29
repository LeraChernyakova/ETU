#! /bin/bash

. ../benchmark_lib.sh

# main

producers="${1:-1}"
consumers="${2:-2}"
tasks="${3:-5}"
size="${4:-3}"

benchmark "./lab2 ${producers} ${consumers} ${tasks} ${size}"

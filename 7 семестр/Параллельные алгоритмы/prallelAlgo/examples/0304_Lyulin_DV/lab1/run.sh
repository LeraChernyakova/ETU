#! /bin/bash

. ../benchmark_lib.sh

function run_proc()
{
  ./in_proc ${rows1} ${cols1rows2} ${cols1rows2} ${cols2} &
  ./calc_proc &
  ./out_proc
}

# main

rows1="${2:-3}"
cols1rows2="${3:-3}"
cols2="${4:-3}"

if [ "${1}" = 'proc' ]; then
  benchmark 'run_proc' 1000
elif [ "${1}" = 'thread' ]; then
  benchmark "./thread_proc ${rows1} ${cols1rows2} ${cols1rows2} ${cols2}" 1000
elif [ "${1}" = 'thread_par' ]; then
  benchmark "./thread_proc_par ${rows1} ${cols1rows2} ${cols1rows2} ${cols2}" 1000
else
  echo "Usage: ${0} {proc|thread|thread_par} [rows1] [rows2/cols1] [cols2]"
fi
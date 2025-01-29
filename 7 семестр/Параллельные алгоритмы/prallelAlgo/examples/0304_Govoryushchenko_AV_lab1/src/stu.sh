#! /bin/bash
./reader 150 150 150 150 &
# sleep 0.1
./executor &
# sleep 0.1
./writer

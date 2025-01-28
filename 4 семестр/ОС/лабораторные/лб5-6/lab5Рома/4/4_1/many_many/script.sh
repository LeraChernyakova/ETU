#!/bin/bash

for i in {1..5}
	do
	    ./p23 "from${i}.txt" "to${i}.txt" &
    done
    wait

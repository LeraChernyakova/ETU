#!/bin/bash

signal_val=34
pid=$1
val_counter=0

echo `sudo kill -10 $pid -q 1`
echo `sudo kill -10 $pid -q 2`

for (( counter=0; counter<10; counter++ ))
do
	echo `sudo kill -34 $pid -q $val_counter`
	((val_counter=val_counter+1))
done

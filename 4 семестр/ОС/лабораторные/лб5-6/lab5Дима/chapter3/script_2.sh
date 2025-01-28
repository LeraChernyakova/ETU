#!/bin/bash

signal_val=34
pid=$1
value=0

for (( counter=0; counter<10; counter++ ))
do
	echo `sudo kill -34 $pid -q $value`
	(( value=value+1 ))
done

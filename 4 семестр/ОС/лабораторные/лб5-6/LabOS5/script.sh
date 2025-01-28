#!/bin/bash

pid=$1
val_counter=0

for (( counter = 0; counter < 5; counter++ ))
do 
	echo `sudo kill -64 $pid -q $val_counter`
	(( val_counter=val_counter+1 )) 
done

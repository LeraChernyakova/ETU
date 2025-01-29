#!/bin/bash

for i in {1..3}
do
	./task_1 "from${i}.txt" "to${i}.txt" &
done
wait

#!/bin/bash

for i in {1..3}
do
    gnome-terminal -- bash -c "./server testFile$i.txt channel${i}1 channel${i}2; exec bash" &
    sleep 2
    gnome-terminal -- bash -c "./client channel${i}1 channel${i}2; exec bash" &
    sleep 1
done


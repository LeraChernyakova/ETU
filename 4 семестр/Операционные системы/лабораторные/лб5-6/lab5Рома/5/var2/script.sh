#!/bin/bash

# Количество читателей и писателей
num_readers=2
num_writers=2

# Запуск читателей
for ((i=0; i<$num_readers; i++)); do
    gnome-terminal -- ./server
done

# Запуск писателей
for ((i=0; i<$num_writers; i++)); do
    gnome-terminal -- ./client
done


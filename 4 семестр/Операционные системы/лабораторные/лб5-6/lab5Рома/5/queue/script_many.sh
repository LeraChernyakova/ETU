#!/bin/bash

gcc -o server server.c
gcc -o client client.c

# Создание 3 пар сервер-клиент
for i in {1..3}
do
    key=$i

    # Запуск сервера
    gnome-terminal -- bash -c "./server $key; exec bash"

    sleep 1

    # Запуск клиента
    gnome-terminal -- bash -c "./client $key $i; exec bash"

    sleep 1
done


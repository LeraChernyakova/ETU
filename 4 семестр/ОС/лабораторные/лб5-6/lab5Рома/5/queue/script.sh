#!/bin/bash

# Запускаем сервер с очередью 9000
gnome-terminal -- ./server 9000 &
echo "Started server on queue"

# Даем серверу время на запуск
sleep 2

# Запускаем 5 клиентов, каждый подключается к серверу
for i in {0..4}; do
    gnome-terminal -- ./client 9000 $i &
    echo "Started client $i connecting to queue"
done


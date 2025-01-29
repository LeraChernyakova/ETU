#!/bin/bash

# Запускаем сервер с очередью 8000
gnome-terminal -- ./server 8000 &
echo "Started server on queue"

# Даем серверу время на запуск
sleep 2

# Запускаем 3 клиентов, каждый подключается к серверу
for i in {0..2}; do
    gnome-terminal -- ./client 8000 $i &
    echo "Started client $i connecting to queue"
done


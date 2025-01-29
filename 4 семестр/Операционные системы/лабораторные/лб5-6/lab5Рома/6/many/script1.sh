#!/bin/bash

# Запускаем серверы на портах 9000-9004
for i in {0..4}; do
    port=$((9000 + i))
    gnome-terminal -- ./server $port &
    echo "Started server $i on port $port"
done

# Даем серверам время на запуск
sleep 2

# Запускаем клиентов, каждый подключается к своему серверу
for i in {0..4}; do
    port=$((9000 + i))
    gnome-terminal -- ./client 127.0.0.1 $port "Hello, Server $i!" &
    echo "Started client $i connecting to port $port"
done


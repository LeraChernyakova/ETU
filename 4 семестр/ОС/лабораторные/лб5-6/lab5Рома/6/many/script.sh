#!/bin/bash

# Запускаем серверы на портах 9000-9004
for i in {0..4}; do
    port=$((9000 + i))
    ./server $port &
    server_pids[$i]=$!
    echo "Started server $i on port $port"
done

# Даем серверам время на запуск
sleep 2

# Запускаем клиентов, каждый подключается к своему серверу
for i in {0..4}; do
    port=$((9000 + i))
    ./client 127.0.0.1 $port "Hello, Server $i!" &
    client_pids[$i]=$!
    echo "Started client $i connecting to port $port"
done

# Ждем завершения работы клиентов
for pid in ${client_pids[*]}; do
    wait $pid
done

# Останавливаем серверы
for pid in ${server_pids[*]}; do
    kill $pid
done


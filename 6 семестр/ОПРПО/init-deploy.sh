#!/bin/bash

if [ -z "$1" ]; then
  FILE=./docker-compose.prod.yaml
else
  FILE=$1
fi

docker compose -f "$FILE" down -v
docker compose -f "$FILE" up -d --build
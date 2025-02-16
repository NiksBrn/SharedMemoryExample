#!/bin/bash

set -e

echo "Сборка Docker-образа..."
sudo docker build -t shared-memory-example .
echo "Сборка завершена. Образ shared-memory-example готов."
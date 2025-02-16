#!/bin/bash

set -e

echo "Запуск Docker-контейнера..."
sudo docker run --rm shared-memory-example
echo "Контейнер завершил работу."
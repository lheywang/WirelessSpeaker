#!/usr/bin/env bash
set -e # Exit immediately if a command exits with a non-zero status

# THIS FILE IS FOR DOCKER USAGE. DO NOT RUN ON YOUR LOCAL MACHINE

cd /app
exec make -j$(nproc) "$@"

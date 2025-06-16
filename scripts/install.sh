#!/usr/bin/env bash

# ===========================================================================================================
# scripts/install.sh
# 
# Handle the docker image build and configuration for the whole compilation step.
#
# ===========================================================================================================

# First, load config
set -a ; . ./.config ; set +a

cd docker/
docker build -t ${DOCKER_NAME} -f dockerfile .

echo "--------------------------------------------------------------------"
echo "Installed everything on your computer !"
echo "You can now compile the project"
echo "--------------------------------------------------------------------"

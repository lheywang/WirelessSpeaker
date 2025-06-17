#!/usr/bin/env bash

# ===========================================================================================================
# scripts/install.sh
# 
# Handle the docker image build and configuration for the whole compilation step.
#
# ===========================================================================================================

# First, load config
set -a ; . ./.config ; set +a

# Then, build the docker image
cd docker/
docker build -t ${DOCKER_NAME} -f dockerfile .
cd ..

# Finally, build the tools for the developper
cd tools/utils && cmake . && sudo make install



echo "--------------------------------------------------------------------"
echo "Installed everything on your computer !"
echo "You can now compile the project"
echo "--------------------------------------------------------------------"

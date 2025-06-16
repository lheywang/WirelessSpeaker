#!/usr/bin/env bash
<<<<<<< HEAD

# ===========================================================================================================
# scripts/install.sh
# 
# Handle the docker image build and configuration for the whole compilation step.
#
# ===========================================================================================================

# First, load config
set -a ; . ./.config ; set +a

# Then, build the docker image
docker build -t ${DOCKER_NAME} -f docker/dockerfile .

# Finally, build the tools for the developper
cd tools/utils && cmake . && sudo make install


=======

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
>>>>>>> 61da582 (Changed the build fronted to be into a docker container, to isolate the crosscompiling from the host os. Enable building and debugging in my os, Fedora)

echo "--------------------------------------------------------------------"
echo "Installed everything on your computer !"
echo "You can now compile the project"
echo "--------------------------------------------------------------------"

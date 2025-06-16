# ===========================================================================================================
# MAKEFILE
#
# Handle all of the build process for the whole project.
# May be runned on bare OS, but is generally called inside a docker
# 
# l.heywang <leonard.heywang@proton.me>
# v1 on Nov 2024
# v2 on Jun 2025
# ===========================================================================================================

# Load the number of system cores to fasten the build process
MAX_CORES := $(shell nproc)

# Load shared variables among different build steps
-include .config

# Configuring PHONY
.PHONY: clean deep_clean all format doc __clean __deep_clean __all __format __doc 

# Configure some variables
DOCKER_ARGS := --rm -v "$(shell pwd):/app"

# ===========================================================================================================
# USER ACCESSIBLE COMMANDS (invoke behind the scene docker)
# ===========================================================================================================
clean:
	@docker run ${DOCKER_ARGS} \
		${DOCKER_NAME} \
		__clean

deep_clean:
	@docker run ${DOCKER_ARGS} \
		${DOCKER_NAME} \
		__deep_clean

all:
	@docker run ${DOCKER_ARGS} \
		${DOCKER_NAME} \
		-e NAME="${NAME}" \
		-e APPNAME="${NAME}" \
		__all

format:
	@docker run ${DOCKER_ARGS} \
		${DOCKER_NAME} \
		__format

doc:
	@docker run ${DOCKER_ARGS}\
		${DOCKER_NAME} \
		__doc


# ===========================================================================================================
# GLOBAL RECIPES (TO BE RUNNED UNDER DOCKER)
# Theses shall not be runned under plain OS. 
# ===========================================================================================================
__clean:
	@-cd build/ && make clean
	@rm -f build/bin/*.bin build/bin/*.o

	@-cd doc/latex && make clean
	@-cd tools/device-tree && make dtc_clean
	
	@echo "------------------------------------------------------------------------------------------------------------"
	@echo "Cleaned build/ doc/ and tools/ and default/ binaries !"
	@echo "------------------------------------------------------------------------------------------------------------"

__deep_clean:
	@echo "Removing caches..."

	@-rm -r -f build/
	@-rm -r -f doc/
	@-cd tools/device-tree && make dtc_clean

	@echo "------------------------------------------------------------------------------------------------------------"
	@echo "Deleted build/ doc/ default/ !"
	@echo "------------------------------------------------------------------------------------------------------------"

__all: build/bin/config.o build/bin/header.o
	@mkdir -p build/
	@echo "------------------------------------------------------------------------------------------------------------"
	@echo "Compiling C/C++ sources files..."
	@echo "------------------------------------------------------------------------------------------------------------"
	@cmake -S src/ -DCMAKE_TOOLCHAIN_FILE=/usr/local/share/cmake/toolchain.cmake -B build/
	@cd build/ && make all -j$(MAX_CORES)

	@echo "------------------------------------------------------------------------------------------------------------"
	@echo "Compiled source on $(shell pwd)/build/${APPNAME}"
	@echo "You can now execute it on the target !"
	@echo "------------------------------------------------------------------------------------------------------------"

__format:
	@find src/ -iname '*.h' -o -iname '*.cpp' -o -iname '*.c' -o -iname '*hpp' | xargs clang-format -i -style=file
		
	@echo "------------------------------------------------------------------------------------------------------------"
	@echo "Formatted all of the source files ! (.c / .h / .hpp / .cpp)"
	@echo "------------------------------------------------------------------------------------------------------------"

# ===========================================================================================================
# RECIPES FOR DOCUMENTATION
# ===========================================================================================================

# If Doxygen is installed, it will generate the doc and build the HTML doc for the whole project
__doc:
	@echo "------------------------------------------------------------------------------------------------------------"
	@echo "Creating documentation... "
	@echo "------------------------------------------------------------------------------------------------------------"

	@doxygen Doxyfile

	@echo "------------------------------------------------------------------------------------------------------------"
	@echo "Generated HTML doc on $(shell pwd)/doc/html/index.html"
	@echo "Generated HTML doc on file://///wsl.localhost/Debian$(shell pwd)/doc/html/index.html"
	@echo "------------------------------------------------------------------------------------------------------------"

# ===========================================================================================================
# RECIPES FOR EMBEDDED DATA
# ===========================================================================================================
build/bin/config.o: default/config/config.toml
	@mkdir -p build/bin/	
	@echo "------------------------------------------------------------------------------------------------------------"
	@echo "Preparing config default binary data..."
	@echo "------------------------------------------------------------------------------------------------------------"

	@python3 tools/default-generator/config/config-generator.py $< build/bin/config.bin
	@aarch64-linux-gnu-ld -r -b binary -o  $@ build/bin/config.bin

	@echo "Generated $@"

build/bin/header.o: default/header/header.toml
	@mkdir -p build/bin/
	@echo "------------------------------------------------------------------------------------------------------------"
	@echo "Preparing header default binary data..."
	@echo "------------------------------------------------------------------------------------------------------------"
	
	@python3 tools/default-generator/header/header-generator.py $< build/bin/header.bin 
	@aarch64-linux-gnu-ld -r -b binary -o  $@ build/bin/header.bin

	@echo "Generated $@"

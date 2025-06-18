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
.PHONY: clean deep_clean all format doc tests __clean __deep_clean __all __format __doc __tests

# Configure some variables
DOCKER_ARGS := --rm -it -v "$(shell pwd):/app"

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

infos:
	@docker run ${DOCKER_ARGS}\
		${DOCKER_NAME} \
		__infos

tests:
	@docker run ${DOCKER_ARGS}\
		${DOCKER_NAME} \
		-e NAME="${NAME}" \
		-e APPNAME="${NAME}" \
		__tests

doc:
	@docker run ${DOCKER_ARGS}\
		${DOCKER_NAME} \
		__doc

pdf:  doc
	@docker run ${DOCKER_ARGS}\
		${DOCKER_NAME} \
		__pdf



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
	@-rm -r -f build_tests
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
	@cmake -DCMAKE_TOOLCHAIN_FILE=/usr/local/share/cmake/toolchain.cmake -B build/
	@cd build/ && make all -s -j$(MAX_CORES)

	@echo "------------------------------------------------------------------------------------------------------------"
	@echo "Compiled source on ./build/${APPNAME}"
	@echo "You can now execute it on the target !"
	@echo "------------------------------------------------------------------------------------------------------------"

__format:
	@find src/ -iname '*.h' -o -iname '*.cpp' -o -iname '*.c' -o -iname '*hpp' | xargs clang-format -i -style=file
		
	@echo "------------------------------------------------------------------------------------------------------------"
	@echo "Formatted all of the source files ! (.c / .h / .hpp / .cpp)"
	@echo "------------------------------------------------------------------------------------------------------------"

__infos:
	@echo "------------------------------------------------------------------------------------------------------------"
	@echo "toolchain informations :"
	@echo "------------------------------------------------------------------------------------------------------------"
	@echo ""

	cat /usr/local/share/cmake/toolchain.cmake

	@echo "------------------------------------------------------------------------------------------------------------"
	@echo "tools versions"
	@echo "------------------------------------------------------------------------------------------------------------"
	@echo ""

	cat /usr/local/share/infos/versions.txt

__tester:
	@mkdir -p build_tests/
	@echo "------------------------------------------------------------------------------------------------------------"
	@echo "Compiling C/C++ sources files for UnitTests ..."
	@echo "------------------------------------------------------------------------------------------------------------"
	@cmake -DBUILD_TESTS=ON -B build_tests/
	@cd build_tests/ && make all -s -j$(MAX_CORES)

	@echo "------------------------------------------------------------------------------------------------------------"
	@echo "Compiled tests on ./build_tests/UnitsTests"
	@echo "You can now execute it to ensure the code quality!"
	@echo "------------------------------------------------------------------------------------------------------------"

__tests: __tester
	@echo "------------------------------------------------------------------------------------------------------------"
	@echo "Running UnitTests..."
	@echo "------------------------------------------------------------------------------------------------------------"

	@cd build_tests/ && ./UnitsTests -c -v

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
	@echo "Generated HTML doc on ./doc/html/index.html"
	@echo "------------------------------------------------------------------------------------------------------------"

__pdf:
	@echo "------------------------------------------------------------------------------------------------------------"
	@echo "Building PDF documentation... "
	@echo "------------------------------------------------------------------------------------------------------------"

	@cd doc/latex/ && make pdf
	@cp doc/latex/refman.pdf doc/${NAME}.pdf

	@echo "------------------------------------------------------------------------------------------------------------"
	@echo "Generated PDF doc on ./doc/${NAME}.pdf"
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

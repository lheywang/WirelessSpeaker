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

# Configuring PHONY
.PHONY: clean deep_clean all format doc tests coverage __clean __deep_clean __all __format __doc __tests __coverage


# Load shared variables among different build steps
-include .config

# ===========================================================================================================
# VARIABLES
# ===========================================================================================================

# Load the number of system cores to fasten the build process
MAX_CORES := $(shell nproc)

# Configure some variables (remove -it flag for runners)
ifeq ($(CI),true)
DOCKER_ARGS := --rm -v "$(shell pwd):/app"
else
DOCKER_ARGS := --rm -it -v "$(shell pwd):/app"
endif

DOCKER_VARS := -e NAME="${NAME}" -e APPNAME="${NAME}"

# Reset
Color_Off=\033[0m

# Regular Colors
Black=\033[0;30m
Red=\033[0;31m
Green=\033[0;32m
Yellow=\033[0;33m
Blue=\033[0;34m
Purple=\033[0;35m
Cyan=\033[0;36m
White=\033[0;37m

# Bold
BBlack=\033[1;30m
BRed=\033[1;31m
BGreen=\033[1;32m
BYellow=\033[1;33m
BBlue=\033[1;34m
BPurple=\033[1;35m
BCyan=\033[1;36m
BWhite=\033[1;37m

# Configuring build paths
debug=build/debug
release=build/release
documentation=build/doc/

# ===========================================================================================================
# USER ACCESSIBLE COMMANDS (invoke behind the scene docker)
# ===========================================================================================================
clean:
	@docker run ${DOCKER_ARGS} \
		${DOCKER_NAME} \
		${DOCKER_VARS} \
		__clean

deep_clean:
	@docker run ${DOCKER_ARGS} \
		${DOCKER_NAME} \
		${DOCKER_VARS} \
		__deep_clean

all:
	@docker run ${DOCKER_ARGS} \
		${DOCKER_NAME} \
		${DOCKER_VARS} \
		__all

format:
	@docker run ${DOCKER_ARGS} \
		${DOCKER_NAME} \
		${DOCKER_VARS} \
		__format

infos:
	@docker run ${DOCKER_ARGS}\
		${DOCKER_NAME} \
		${DOCKER_VARS} \
		__infos

tests:
	@docker run ${DOCKER_ARGS}\
		${DOCKER_NAME} \
		${DOCKER_VARS} \
		__tests

tester:
	@docker run ${DOCKER_ARGS}\
		${DOCKER_NAME} \
		${DOCKER_VARS} \
		__tester

doc:
	@docker run ${DOCKER_ARGS}\
		${DOCKER_NAME} \*
		${DOCKER_VARS} \
		__doc

pdf:  doc
	@docker run ${DOCKER_ARGS}\
		${DOCKER_NAME} \
		${DOCKER_VARS} \
		__pdf


# ===========================================================================================================
# GLOBAL RECIPES (TO BE RUNNED UNDER DOCKER)
# Theses shall not be runned under plain OS. 
# ===========================================================================================================
__clean:
	@-+cd /app/doc/latex && $(MAKE) clean
	@-+cd /app/tools/device-tree && $(MAKE) dtc_clean

	@-+cd ${release} && $(MAKE) clean
	@-+cd ${debug} && $(MAKE) clean
	@-rm -f ${release}/bin/*.bin ${release}/bin/*.o 
	@-rm -f ${debug}/bin/*.bin ${debug}/bin/*.o 
	
	@echo "${BGreen}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo "${BGreen}Cleaned build/ doc/ and tools/ and default/ binaries !${Color_Off}"
	@echo "${BGreen}------------------------------------------------------------------------------------------------------------${Color_Off}"

__deep_clean:
	@-rm -rf ${release} ${debug}
	@-rm -r -f ${documentation}
	@+cd tools/device-tree && $(MAKE) dtc_clean

	@echo "${BGreen}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo "${BGreen}Deleted ${release} ${debug} ${documentation} !${Color_Off}"
	@echo "${BGreen}------------------------------------------------------------------------------------------------------------${Color_Off}"

__all: build/prod/bin/config.o build/prod/bin/header.o
	@mkdir -p build/prod/

	@echo "${BYellow}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo "${BYellow}Compiling C/C++ sources files...${Color_Off}"
	@echo "${BYellow}------------------------------------------------------------------------------------------------------------${Color_Off}"

	@cmake -DCMAKE_TOOLCHAIN_FILE=/usr/local/share/cmake/toolchain.cmake -B build/prod/
	@cd build/prod/ && $(MAKE) all -s -j$(MAX_CORES)

	@echo "${BGreen}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo "${BGreen}Compiled source on ./build/${APPNAME}${Color_Off}"
	@echo "${BGreen}You can now execute it on the target !${Color_Off}"
	@echo "${BGreen}------------------------------------------------------------------------------------------------------------${Color_Off}"

__format:
	@find src/ -iname '*.h' -o -iname '*.cpp' -o -iname '*.c' -o -iname '*hpp' | xargs clang-format -i -style=file
	@find inc/ -iname '*.h' -o -iname '*.cpp' -o -iname '*.c' -o -iname '*hpp' | xargs clang-format -i -style=file
		
	@echo "${BCyan}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo "${BCyan}Formatted all of the source files ! (.c / .h / .hpp / .cpp)${Color_Off}"
	@echo "${BCyan}------------------------------------------------------------------------------------------------------------${Color_Off}"

__infos:
	@echo "${BCyan}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo "${BCyan}toolchain informations :${Color_Off}"
	@echo "${BCyan}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo ""

	@cat /usr/local/share/cmake/toolchain.cmake

	@echo "${BCyan}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo "${BCyan}tools versions${Color_Off}"
	@echo "${BCyan}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo ""

	@cat /usr/local/share/infos/versions.txt

__tester: build/debug/bin/config.o build/debug/bin/header.o
	@echo "${BYellow}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo "${BYellow}Compiling C/C++ sources files for UnitTests ...${Color_Off}"
	@echo "${BYellow}------------------------------------------------------------------------------------------------------------${Color_Off}"

	@mkdir -p build/debug/

	@cmake -DBUILD_TESTS=ON -B build/debug/
	@cd build/debug/ && $(MAKE) all -s -j$(MAX_CORES)

	@echo "${BGreen}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo "${BGreen}Compiled tests on ./build_tests/UnitsTests${Color_Off}"
	@echo "${BGreen}You can now execute it to ensure the code quality!${Color_Off}"
	@echo "${BGreen}------------------------------------------------------------------------------------------------------------${Color_Off}"

__tests: __tester
	@echo "${BYellow}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo "${BYellow}Running UnitTests...${Color_Off}"
	@echo "${BYellow}------------------------------------------------------------------------------------------------------------${Color_Off}"

	@cd build/debug/ && ./UnitsTests -c

# ===========================================================================================================
# RECIPES FOR DOCUMENTATION
# ===========================================================================================================

# If Doxygen is installed, it will generate the doc and build the HTML doc for the whole project
__doc:
	@echo "${BYellow}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo "${BYellow}Creating documentation... ${Color_Off}"
	@echo "${BYellow}------------------------------------------------------------------------------------------------------------${Color_Off}"

	@doxygen Doxyfile

	@echo "${BGreen}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo "${BGreen}Generated HTML doc on ./doc/html/index.html${Color_Off}"
	@echo "${BGreen}Generated LaTeX doc on ./doc/latex/reflan.tex${Color_Off}"
	@echo "${BGreen}------------------------------------------------------------------------------------------------------------${Color_Off}"

__pdf:
	@echo "${BYellow}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo "${BYellow}Building PDF documentation... ${Color_Off}"
	@echo "${BYellow}------------------------------------------------------------------------------------------------------------${Color_Off}"

	@cd doc/latex/ && make pdf
	@cp doc/latex/refman.pdf doc/${NAME}.pdf

	@echo "${BGreen}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo "${BGreen}Generated PDF doc on ./doc/${NAME}.pdf${Color_Off}"
	@echo "${BGreen}------------------------------------------------------------------------------------------------------------${Color_Off}"


# ===========================================================================================================
# RECIPES FOR EMBEDDED DATA
# ===========================================================================================================
build/prod/bin/config.o: default/config/config.toml
	@mkdir -p build/prod/bin/
	@echo "${BYellow}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo "${BYellow}Preparing config default binary data...${Color_Off}"
	@echo "${BYellow}------------------------------------------------------------------------------------------------------------${Color_Off}"

	@python3 tools/default-generator/config/config-generator.py $< build/prod/bin/config.bin
	@aarch64-linux-gnu-ld -r -b binary -o  $@ build/prod/bin/config.bin

	@echo "Generated $@"

build/prod/bin/header.o: default/header/header.toml
	@mkdir -p build/prod/bin/
	@echo "${BYellow}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo "${BYellow}Preparing header default binary data...${Color_Off}"
	@echo "${BYellow}------------------------------------------------------------------------------------------------------------${Color_Off}"
	
	@python3 tools/default-generator/header/header-generator.py $< build/prod/bin/header.bin 
	@aarch64-linux-gnu-ld -r -b binary -o  $@ build/prod/bin/header.bin

	@echo "Generated $@"

build/debug/bin/config.o: default/config/config.toml
	@mkdir -p build/prod/bin/
	@echo "${BYellow}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo "${BYellow}Preparing config default binary data...${Color_Off}"
	@echo "${BYellow}------------------------------------------------------------------------------------------------------------${Color_Off}"

	@python3 tools/default-generator/config/config-generator.py $< build/debug/bin/config.bin
	@aarch64-linux-gnu-ld -r -b binary -o  $@ build/prod/bin/config.bin

	@echo "Generated $@"

build/debug/bin/header.o: default/header/header.toml
	@mkdir -p build/prod/bin/
	@echo "${BYellow}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo "${BYellow}Preparing header default binary data...${Color_Off}"
	@echo "${BYellow}------------------------------------------------------------------------------------------------------------${Color_Off}"
	
	@python3 tools/default-generator/header/header-generator.py $< build/debug/bin/header.bin 
	@aarch64-linux-gnu-ld -r -b binary -o  $@ build/prod/bin/header.bin

	@echo "Generated $@"

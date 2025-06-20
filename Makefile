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
.SILENT: clean deep_clean all format doc tests coverage __clean __deep_clean __all __format __doc __tests __coverage

# Remove useless logs
export MAKEFLAGS += --no-print-directory

# Load shared variables among different build steps
-include .config

# ===========================================================================================================
# VARIABLES
# ===========================================================================================================

# Load the number of system cores to fasten the build process
MAX_CORES := $(shell nproc)

# Configure some variables (remove -it flag for runners)
ifeq ($(CI),true)
DOCKER_ARGS := --rm -v "$(shell pwd):${DOCKER_BASE}"
else
DOCKER_ARGS := --rm -it -v "$(shell pwd):${DOCKER_BASE}"
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

# ===========================================================================================================
# USER ACCESSIBLE COMMANDS (invoke behind the scene docker)
# ===========================================================================================================
clean:
	@docker run ${DOCKER_ARGS} \
		${DOCKER_NAME} \
		${DOCKER_VARS} \
		-e MAKEFLAGS="${MAKEFLAGS}"\
		__clean

deep_clean:
	@docker run ${DOCKER_ARGS} \
		${DOCKER_NAME} \
		${DOCKER_VARS} \
		-e MAKEFLAGS="${MAKEFLAGS}"\
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
		-e MAKEFLAGS="${MAKEFLAGS}"\
		__format

infos:
	@docker run ${DOCKER_ARGS}\
		${DOCKER_NAME} \
		${DOCKER_VARS} \
		-e MAKEFLAGS="${MAKEFLAGS}"\
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
		${DOCKER_NAME} \
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
	@-+cd ${DOCKER_BASE}/${BUILD_DOC}/latex && $(MAKE) clean
	@-+cd ${DOCKER_BASE}/tools/device-tree && $(MAKE) dtc_clean

	@+cd ${DOCKER_BASE}/${BUILD_RELEASE} && $(MAKE) clean
	@+cd ${DOCKER_BASE}/${BUILD_DEBUG} && $(MAKE) clean
	@-rm -f ${DOCKER_BASE}/${BUILD_RELEASE}/bin/*.bin ${DOCKER_BASE}/${BUILD_RELEASE}/bin/*.o 
	@-rm -f ${DOCKER_BASE}/${BUILD_DEBUG}/bin/*.bin ${DOCKER_BASE}/${BUILD_DEBUG}/bin/*.o 
	
	@echo "${BGreen}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo "${BGreen} Cleaned build/ doc/ and tools/ and default/ binaries !${Color_Off}"
	@echo "${BGreen}------------------------------------------------------------------------------------------------------------${Color_Off}"

__deep_clean:
	@-rm -rf ${DOCKER_BASE}/${BUILD_RELEASE} ${DOCKER_BASE}/${BUILD_DEBUG}
	@-rm -r -f ${DOCKER_BASE}/${BUILD_DOC}
	@+cd tools/device-tree && $(MAKE) dtc_clean

	@echo "${BGreen}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo "${BGreen} Deleted ${BUILD_RELEASE} ${BUILD_DEBUG} ${BUILD_DOC} !${Color_Off}"
	@echo "${BGreen}------------------------------------------------------------------------------------------------------------${Color_Off}"

__all: ${DOCKER_BASE}/${BUILD_RELEASE}/bin/config.o ${DOCKER_BASE}/${BUILD_RELEASE}/bin/header.o
	@mkdir -p ${DOCKER_BASE}/${BUILD_RELEASE}

	@echo "${BYellow}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo "${BYellow} Compiling C/C++ sources files...${Color_Off}"
	@echo "${BYellow}------------------------------------------------------------------------------------------------------------${Color_Off}"

	@cmake -DCMAKE_TOOLCHAIN_FILE=/usr/local/share/cmake/toolchain.cmake -B ${DOCKER_BASE}/${BUILD_RELEASE}
	@cd ${DOCKER_BASE}/${BUILD_RELEASE} && $(MAKE) all -s -j$(MAX_CORES)

	@echo "${BGreen}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo "${BGreen} Compiled source on ./build/${APPNAME}${Color_Off}"
	@echo "${BGreen} You can now execute it on the target !${Color_Off}"
	@echo "${BGreen}------------------------------------------------------------------------------------------------------------${Color_Off}"

__format:
	@find ${DOCKER_BASE}/src/ -iname '*.h' -o -iname '*.cpp' -o -iname '*.c' -o -iname '*hpp' | xargs clang-format -i -style=file
	@find ${DOCKER_BASE}/inc/ -iname '*.h' -o -iname '*.cpp' -o -iname '*.c' -o -iname '*hpp' | xargs clang-format -i -style=file
		
	@echo "${BCyan}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo "${BCyan} Formatted all of the source files ! (.c / .h / .hpp / .cpp)${Color_Off}"
	@echo "${BCyan}------------------------------------------------------------------------------------------------------------${Color_Off}"

__infos:
	@echo "${BCyan}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo "${BCyan} Toolchain informations :${Color_Off}"
	@echo "${BCyan}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo ""

	@cat /usr/local/share/cmake/toolchain.cmake

	@echo "${BCyan}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo "${BCyan} Tools versions${Color_Off}"
	@echo "${BCyan}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo ""

	@cat /usr/local/share/infos/versions.txt

__tester: ${DOCKER_BASE}/${BUILD_DEBUG}/bin/config.o ${DOCKER_BASE}/${BUILD_DEBUG}/bin/header.o
	@echo "${BYellow}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo "${BYellow} Compiling C/C++ sources files for UnitTests ...${Color_Off}"
	@echo "${BYellow}------------------------------------------------------------------------------------------------------------${Color_Off}"

	@mkdir -p ${DOCKER_BASE}/${BUILD_DEBUG}

	@cmake -DBUILD_TESTS=ON -B ${DOCKER_BASE}/${BUILD_DEBUG}
	@cd ${DOCKER_BASE}/${BUILD_DEBUG} && $(MAKE) all -s -j$(MAX_CORES)

	@echo "${BGreen}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo "${BGreen} Compiled tests on ./build_tests/UnitsTests${Color_Off}"
	@echo "${BGreen} You can now execute it to ensure the code quality!${Color_Off}"
	@echo "${BGreen}------------------------------------------------------------------------------------------------------------${Color_Off}"

__tests: __tester
	@echo "${BYellow}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo "${BYellow} Running UnitTests...${Color_Off}"
	@echo "${BYellow}------------------------------------------------------------------------------------------------------------${Color_Off}"

	@cd ${DOCKER_BASE}/${BUILD_DEBUG} && ./UnitsTests -c

# ===========================================================================================================
# RECIPES FOR BUILD_DOC
# ===========================================================================================================

# If Doxygen is installed, it will generate the doc and build the HTML doc for the whole project
__doc:
	@echo "${BYellow}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo "${BYellow} Creating documentation ... ${Color_Off}"
	@echo "${BYellow}------------------------------------------------------------------------------------------------------------${Color_Off}"

	@mkdir -p ${DOCKER_BASE}/${BUILD_DOC}
	@DOCKER_BASE=${DOCKER_BASE} BUILD_DOC=${BUILD_DOC} doxygen ${DOCKER_BASE}/Doxyfile >> ${DOCKER_BASE}/${BUILD_DOC}/logs.txt

	@echo "${BGreen}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo "${BGreen} Generated HTML doc on ./doc/html/index.html${Color_Off}"
	@echo "${BGreen} Generated LaTeX doc on ./doc/latex/reflan.tex${Color_Off}"
	@echo "${BGreen}------------------------------------------------------------------------------------------------------------${Color_Off}"

__pdf:
	@echo "${BYellow}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo "${BYellow} Building PDF BUILD_DOC... ${Color_Off}"
	@echo "${BYellow}------------------------------------------------------------------------------------------------------------${Color_Off}"

	@+cd ${DOCKER_BASE}/${BUILD_DOC}/latex && make pdf
	@cp ${DOCKER_BASE}/${BUILD_DOC}/latex/refman.pdf ${DOCKER_BASE}/${BUILD_DOC}/${NAME}.pdf

	@echo "${BGreen}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo "${BGreen} Generated PDF doc on ./doc/${NAME}.pdf${Color_Off}"
	@echo "${BGreen}------------------------------------------------------------------------------------------------------------${Color_Off}"


# ===========================================================================================================
# RECIPES FOR EMBEDDED DATA
# ===========================================================================================================
$(DOCKER_BASE)/$(BUILD_RELEASE)/bin/config.o: default/config/config.toml
	@mkdir -p ${DOCKER_BASE}/${BUILD_RELEASE}/bin/
	@mkdir -p /tmp/WirelessSpeaker/
	@echo "${BYellow}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo "${BYellow} Preparing config default binary data...${Color_Off}"
	@echo "${BYellow}------------------------------------------------------------------------------------------------------------${Color_Off}"

	@python3 ${DOCKER_BASE}/tools/default-generator/config/config-generator.py $< /tmp/WirelessSpeaker/r_config.bin
	@aarch64-linux-gnu-ld -r -b binary -o  $@ /tmp/WirelessSpeaker/r_config.bin

	@echo "Generated $@"

$(DOCKER_BASE)/$(BUILD_RELEASE)/bin/header.o: ${DOCKER_BASE}/${DEFAULT_LOC}/header/header.toml
	@mkdir -p ${DOCKER_BASE}/${BUILD_RELEASE}/bin/
	@mkdir -p /tmp/WirelessSpeaker/
	@echo "${BYellow}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo "${BYellow}Preparing header default binary data...${Color_Off}"
	@echo "${BYellow}------------------------------------------------------------------------------------------------------------${Color_Off}"
	
	@python3 ${DOCKER_BASE}/tools/default-generator/header/header-generator.py $< /tmp/WirelessSpeaker/r_header.bin
	@aarch64-linux-gnu-ld -r -b binary -o  $@ /tmp/WirelessSpeaker/r_header.bin

	@echo "Generated $@"

$(DOCKER_BASE)/$(BUILD_DEBUG)/bin/config.o: default/config/config.toml
	@mkdir -p ${DOCKER_BASE}/${BUILD_DEBUG}/bin/
	@mkdir -p /tmp/WirelessSpeaker/
	@echo "${BYellow}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo "${BYellow} Preparing config default binary data...${Color_Off}"
	@echo "${BYellow}------------------------------------------------------------------------------------------------------------${Color_Off}"

	@python3 ${DOCKER_BASE}/tools/default-generator/config/config-generator.py $< /tmp/WirelessSpeaker/d_header.bin
	@aarch64-linux-gnu-ld -r -b binary -o  $@ /tmp/WirelessSpeaker/d_header.bin

$(DOCKER_BASE)/$(BUILD_DEBUG)/bin/header.o: default/header/header.toml
	@mkdir -p ${DOCKER_BASE}/${BUILD_DEBUG}/bin/
	@mkdir -p /tmp/WirelessSpeaker/
	@echo "${BYellow}------------------------------------------------------------------------------------------------------------${Color_Off}"
	@echo "${BYellow} Preparing header default binary data...${Color_Off}"
	@echo "${BYellow}------------------------------------------------------------------------------------------------------------${Color_Off}"
	
	@python3 ${DOCKER_BASE}/tools/default-generator/header/header-generator.py $< /tmp/WirelessSpeaker/d_config.bin 
	@aarch64-linux-gnu-ld -r -b binary -o  $@ /tmp/WirelessSpeaker/d_config.bin 

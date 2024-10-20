
MAX_CORES := $(shell nproc)
EXECNAME := build/WirelessSpeaker.arm

# ===========================================================================================================
# GLOBAL RECIPES
# ===========================================================================================================
clean:
	@-cd build/ && make clean
	@-cd doc/latex && make clean
	@-cd tools/device-tree && make dtc_clean
	@rm -f default/config/*.bin default/config/*.o
	@rm -f default/header/*.bin default/header/*.o

	@echo "--------------------------------------------------------------------"
	@echo "Cleaned build/ doc/ and tools/ and default/ binaries !"
	@echo "--------------------------------------------------------------------"

clean_all: clean
	@echo "Removing caches..."

	@-rm -r -f build/
	@-rm -r -f doc/

	@echo "--------------------------------------------------------------------"
	@echo "Deleted build/ doc/ default/ !"
	@echo "--------------------------------------------------------------------"

all: default/config/config.o default/header/header.o
	@mkdir -p build/
	@cd build/ && cmake ../src/CMakeLists.txt
	@cd build/ && make all -j$(MAX_CORES)

	@echo "--------------------------------------------------------------------"
	@echo "Compiled source on $(shell pwd)/build/WirelessSpeaker.arm"
	@echo "You can now execute it on the target !"
	@echo "--------------------------------------------------------------------"

# ===========================================================================================================
# RECIPES FOR DOCUMENTATION
# ===========================================================================================================

# If Doxygen is installed, it will generate the doc and build the PDF from the TeX source for the whole project.
doc:
	@echo "--------------------------------------------------------------------"
	@echo "Creating documentation... "
	@echo "It may take a while !"

	@doxygen Doxyfile
	@cd ./doc/latex && make pdf > log-file 2>&1

	@echo "--------------------------------------------------------------------"
	@echo "Generated PDF doc on $(shell pwd)/doc/latex/refman.pdf"
	@echo "Generated PDF doc on file://///wsl.localhost/Debian$(shell pwd)/doc/latex/refman.pdf"
	@echo "Generated HTML doc on $(shell pwd)/doc/html/index.html"
	@echo "Generated HTML doc on file://///wsl.localhost/Debian$(shell pwd)/doc/html/index.html"
	@echo "--------------------------------------------------------------------"

# ===========================================================================================================
# RECIPES FOR EMBEDDED DATA
# ===========================================================================================================
default/config/config.o: default/config/config.toml
	@echo "--------------------------------------------------------------------"
	@echo "Preparing config default binary data..."
	@echo "--------------------------------------------------------------------"

	python3 tools/default-generator/config/config-generator.py default/config/config.toml default/config/config.bin
	aarch64-linux-gnu-ld -r -b binary -o  default/config/config.o default/config/config.bin

	@echo "Generated default/config/config.o"

default/header/header.o: default/header/header.toml
	@echo "--------------------------------------------------------------------"
	@echo "Preparing header default binary data..."
	@echo "--------------------------------------------------------------------"
	
	python3 tools/default-generator/header/header-generator.py default/header/header.toml default/header/header.bin 
	aarch64-linux-gnu-ld -r -b binary -o  default/header/header.o default/header/header.bin

	@echo "Generated default/header/header.o"

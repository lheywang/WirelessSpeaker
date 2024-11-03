
MAX_CORES := $(shell nproc)
EXECNAME := build/WirelessSpeaker.arm

# ===========================================================================================================
# GLOBAL RECIPES
# ===========================================================================================================
clean:
	@-cd build/ && make clean
	@rm -f build/bin/*.bin build/bin/*.o

	@-cd doc/latex && make clean
	@-cd tools/device-tree && make dtc_clean
	
	@echo "------------------------------------------------------------------------------------------------------------"
	@echo "Cleaned build/ doc/ and tools/ and default/ binaries !"
	@echo "------------------------------------------------------------------------------------------------------------"

deep_clean:
	@echo "Removing caches..."

	@-rm -r -f build/
	@-rm -r -f doc/
	@-cd tools/device-tree && make dtc_clean

	@echo "------------------------------------------------------------------------------------------------------------"
	@echo "Deleted build/ doc/ default/ !"
	@echo "------------------------------------------------------------------------------------------------------------"

all: build/bin/config.o build/bin/header.o
	@mkdir -p build/
	@echo "------------------------------------------------------------------------------------------------------------"
	@echo "Compiling C/C++ sources files..."
	@echo "------------------------------------------------------------------------------------------------------------"
	@cmake -S src/ -B build/
	@cd build/ && make all -j$(MAX_CORES)

	@echo "------------------------------------------------------------------------------------------------------------"
	@echo "Compiled source on $(shell pwd)/build/WirelessSpeaker.arm"
	@echo "You can now execute it on the target !"
	@echo "------------------------------------------------------------------------------------------------------------"

format:
	find src/ -iname '*.h' -o -iname '*.cpp' -o -iname '*.c' -o -iname '*hpp' | xargs clang-format -i -style=file

# ===========================================================================================================
# RECIPES FOR DOCUMENTATION
# ===========================================================================================================

# If Doxygen is installed, it will generate the doc and build the PDF from the TeX source for the whole project.
doc:
	@echo "------------------------------------------------------------------------------------------------------------"
	@echo "Creating documentation... "
	@echo "It may take a while !"

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

	python tools/default-generator/config/config-generator.py $< build/bin/config.bin
	aarch64-linux-gnu-ld -r -b binary -o  $@ build/bin/config.bin

	@echo "Generated $@"

build/bin/header.o: default/header/header.toml
	@mkdir -p build/bin/
	@echo "------------------------------------------------------------------------------------------------------------"
	@echo "Preparing header default binary data..."
	@echo "------------------------------------------------------------------------------------------------------------"
	
	python tools/default-generator/header/header-generator.py $< build/bin/header.bin 
	aarch64-linux-gnu-ld -r -b binary -o  $@ build/bin/header.bin

	@echo "Generated $@"

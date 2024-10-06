
MAX_CORES := $(shell nproc)
EXECNAME := build/WirelessSpeaker.arm

# ===========================================================================================================
# GLOBAL RECIPES
# ===========================================================================================================
clean:
	-cd build/ && make clean
	-cd doc/ && make clean
	-cd tools/device-tree && make dtc_clean
	@echo "Removed build artifacts ! Cmake cache remains. Use clean_all to remove everything"

clean_all: clean
	@echo "Removing caches..."
	-rm -r -f build/
	-rm -r -f doc/

all:
	@mkdir -p build/
	@cd build/ && cmake ../src/CMakeLists.txt
	@cd build/ && make all -j$(MAX_CORES)

# ===========================================================================================================
# RECIPES FOR DOCUMENTATION
# ===========================================================================================================

# If Doxygen is installed, it will generate the doc and build the PDF from the TeX source for the whole project.
doc:
	@doxygen Doxyfile
	@cd ./doc/latex && make pdf

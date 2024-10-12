
MAX_CORES := $(shell nproc)
EXECNAME := build/WirelessSpeaker.arm

# ===========================================================================================================
# GLOBAL RECIPES
# ===========================================================================================================
clean:
	@-cd build/ && make clean
	@-cd doc/latex && make clean
	@-cd tools/device-tree && make dtc_clean
	@echo "--------------------------------------------------------------------"
	@echo "Cleaned build/ doc/ and tools/ !"
	@echo "--------------------------------------------------------------------"

clean_all: clean
	@echo "Removing caches..."
	@-rm -r -f build/
	@-rm -r -f doc/
	@echo "--------------------------------------------------------------------"
	@echo "Deleted build/ doc/ !"
	@echo "--------------------------------------------------------------------"

all:
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

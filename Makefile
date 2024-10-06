
MAX_CORES := $(shell nproc)
EXECNAME := build/WirelessSpeaker.arm

# ===========================================================================================================
# GLOBAL RECIPES
# ===========================================================================================================
clean:
	-cd build/ && make clean
	-cd tools/utils && make clean
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

# ===========================================================================================================
# RECIPES FOR AUTOMATED DEPLOYEMENT
# ===========================================================================================================



## Define the software as autostart
src_autostart: install

# This recipe compile the eeprom generator, execute it, before copying the file to the RPi and deploying it.
# Warning : This may take some time due to the large files sizes.
# This recipe is independant since only needed once ! We don't want to flash our eeprom every time.
src_eeprom: 
	cd tools/eeprom && ./eepmake ../$(EEPROM).txt $(EEPROM).eep

src_weeprom: src_eeprom
	cd tools/eeprom && sudo ./eepflash.sh -w -t=24c32 -a=0x50 -f=$(EEPROM).eep
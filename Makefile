# Define basic ouput name.
SRC_EXECNAME = application

# Define EEPROM Source
EEPROM := Keywang-WirelessSpeakerV1

# Output folder name
OUTPUTDIR = build

# Define RPi IP or Domain name and location of the RSA key for automated deployment.
# Customize this field depending on your installation !
RPI = 192.168.1.7
# Customize this one with your filepath !
KEY = ~/.ssh/id_rsa

# Reminder : 
# You can generate a SSH using ssh-keygen, then follow the steps
# Then, add it to the RPi using ssh-copy-id -i [YOUR kEY].pub USER@DESTINATION
# Thus, any followwing steps will be authenticated.


# This horror list all dir and subdir up to the 5th order qnd append /src. Used for autocompile.
VPATH = $(sort $(dir $(wildcard src/*/) $(wildcard src/*/*/) $(wildcard src/*/*/*/) $(wildcard src/*/*/*/*/) $(wildcard src/*/*/*/*/*/) $(wildcard src/*/*/*/*/*/*/) $(wildcard src/*/*/*/*/*/*/))) src/


# define cross compiler parameters and flags
arm_CC = aarch64-linux-gnu-g++
arm_compiler_CFLAGS = -mcpu=cortex-a53 -O3 -MMD -std=c++20 -Wall -Wextra
arm_linker_CFLAGS = -mcpu=cortex-a53 -static -O3 -Wall -Wextra

# ===========================================================================================================
# AUTO GENERATED VARIABLES. DO NOT TOUCH.
# ===========================================================================================================

# Include every cpp file on the folder.
files = $(shell find -name "*.cpp")
files += $(shell find -name "*.c")

# Define object files, and it's equivalent with the build folder.
objects = $(foreach file,$(files), $(notdir $(file)))
tobjects = $(objects:.cpp=.o)
fobjects = $(addprefix $(OUTPUTDIR)/, $(tobjects))


# ===========================================================================================================
# RECIPES FOR COMPILATION.
# ===========================================================================================================

# All only build the executable.
all: $(SRC_EXECNAME).arm

# Clean the build artifacts + the previous doxygen build docs
clean:
	@rm -f *.arm $(SRC_EXECNAME)
	@rm -f -r $(OUTPUTDIR)
	@rm -f -r doc/ 
	@echo "Deleted doc/ build/ and executable (.arm)"
	@cd tools/eeprom/ && make clean

# Generic .o compiler. Used to compile all files.
$(OUTPUTDIR)/%.o: %.cpp
	@mkdir -p $(OUTPUTDIR)
	$(arm_CC) $(arm_compiler_CFLAGS) -o build/$(@F) -c $<

# Standard output file. Names as .arm to prevent any confusion with .elf files.
$(SRC_EXECNAME).arm: $(fobjects)
	@echo "$(fobjects)"
	@touch $(SRC_EXECNAME).arm
	$(arm_CC) $(arm_linker_CFLAGS) -o $(SRC_EXECNAME).arm $(fobjects)
	@chmod +x $(SRC_EXECNAME).arm

# ===========================================================================================================
# RECIPES FOR DEPLOYEMENT.
# ===========================================================================================================

# Theses two rules assume a raspbeerypi is available on your network, and correctly configured.
# They enable the ability to deploy and run the code to test it remotely, from your computer.

src_install: $(SRC_EXECNAME).arm
	ssh -i $(KEY) pi@$(RPI) -f "touch /home/pi/$(SRC_EXECNAME).elf"
	scp -i $(KEY) $(SRC_EXECNAME).arm pi@$(RPI):/home/pi/$(SRC_EXECNAME).elf 
	ssh -i $(KEY) pi@$(RPI) -f "chmod +x /home/pi/$(SRC_EXECNAME).elf"

## SSH link to run the file from the host system.
src_run: $(SRC_EXECNAME).arm install
	ssh -i $(KEY) pi@$(RPI) -f "cd /home/pi/ && ./$(SRC_EXECNAME).elf"

## Define the software as autostart
src_autostart: install

# This recipe compile the eeprom generator, execute it, before copying the file to the RPi and deploying it.
# Warning : This may take some time due to the large files sizes.
# This recipe is independant since only needed once ! We don't want to flash our eeprom every time.
src_eeprom: 
	cd tools/eeprom && ./eepmake ../$(EEPROM).txt $(EEPROM).eep

src_weeprom: src_eeprom
	cd tools/eeprom && sudo ./eepflash.sh -w -t=24c32 -a=0x50 -f=$(EEPROM).eep

# ===========================================================================================================
# RECIPES FOR DOCUMENTATION
# ===========================================================================================================

# If Doxygen is installed, it will generate the doc and build the PDF from the TeX source for the whole project.
src_doc:
	@doxygen Doxyfile
	@cd ./doc/latex && make pdf

# ===========================================================================================================
# RECIPES FOR EVERYONE !
# ===========================================================================================================
install_dependencies:
	sudo apt-get install build-essential libc6-dev make doxygen ssh libi2c-dev device-tree-compiler g++-aarch64-linux-gnu

install_dev-dependencies: install_dependencies
	sudo apt-get install texlive-full libfdt-dev gcc 
	cd tools/ && git clone https://github.com/raspberrypi/utils.git
	cd tools/utils && cmake . && sudo make install
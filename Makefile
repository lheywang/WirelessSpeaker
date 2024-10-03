# Define basic ouput name.
EXECNAME = application

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
all: $(EXECNAME).arm

# Clean the build artifacts + the previous doxygen build docs
clean:
	@rm -f *.arm $(EXECNAME)
	@rm -f -r $(OUTPUTDIR)
	@rm -f -r doc/ 
	@echo "Deleted doc/ build/ and executable (.arm)"
	@cd tools/eeprom/ && make clean

# Generic .o compiler. Used to compile all files.
$(OUTPUTDIR)/%.o: %.cpp
	@mkdir -p $(OUTPUTDIR)
	$(arm_CC) $(arm_compiler_CFLAGS) -o build/$(@F) -c $<

# Standard output file. Names as .arm to prevent any confusion with .elf files.
$(EXECNAME).arm: $(fobjects)
	@echo "$(fobjects)"
	@touch $(EXECNAME).arm
	$(arm_CC) $(arm_linker_CFLAGS) -o $(EXECNAME).arm $(fobjects)
	@chmod +x $(EXECNAME).arm

# ===========================================================================================================
# RECIPES FOR DEPLOYEMENT.
# ===========================================================================================================

# Theses two rules assume a raspbeerypi is available on your network, and correctly configured.
# They enable the ability to deploy and run the code to test it remotely, from your computer.

install: $(EXECNAME).arm
	ssh -i $(KEY) pi@$(RPI) -f "touch /home/pi/$(EXECNAME).elf"
	scp -i $(KEY) $(EXECNAME).arm pi@$(RPI):/home/pi/$(EXECNAME).elf 
	ssh -i $(KEY) pi@$(RPI) -f "chmod +x /home/pi/$(EXECNAME).elf"

## SSH link to run the file from the host system.
run: $(EXECNAME).arm install
	ssh -i $(KEY) pi@$(RPI) -f "cd /home/pi/ && ./$(EXECNAME).elf"

## Define the software as autostart
autostart: install

# This recipe compile the eeprom generator, execute it, before copying the file to the RPi and deploying it.
# Warning : This may take some time due to the large files sizes.
# This recipe is independant since only needed once ! We don't want to flash our eeprom every time.
eeprom: 
	@cd tools/eeprom && make all
	@cd tools/eeprom ./eepmake eeprom_settings.txt myhat.eep


weeprom:

# ===========================================================================================================
# RECIPES FOR DOCUMENTATION
# ===========================================================================================================

# If Doxygen is installed, it will generate the doc and build the PDF from the TeX source for the whole project.
doc:
	@doxygen Doxyfile
	@cd ./doc/latex && make pdf



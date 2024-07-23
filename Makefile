# Define basic ouput name.
EXECNAME = application

# Output folder name
OUTPUTDIR = build

# This horror list all dir and subdir up to the 5th order qnd append /src. Used for autocompile.
VPATH = $(sort $(dir $(wildcard src/*/) $(wildcard src/*/*/) $(wildcard src/*/*/*/) $(wildcard src/*/*/*/*/) $(wildcard src/*/*/*/*/*/))) src/


# define cross compiler parameters and flags
arm_CC = aarch64-linux-gnu-g++
arm_compiler_CFLAGS = -mcpu=cortex-a53 -O3 -MMD -std=c++11 -Wall -Wextra
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

test:
	@echo "$(VPATH)"
	@echo "$(files)"
	@echo "$(fobjects)"

# All only build the executable.
all: $(EXECNAME).arm

# Clean the build artifacts.
clean:
	@rm -f *.o $(EXECNAME)
	@rm -f *.arm $(EXECNAME)
	@rm -f *.x86 $(EXECNAME)
	@rm -f -r $(OUTPUTDIR)

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
# This may need a password.
	scp $(EXECNAME).arm pi@raspberrypi.home:/home/$(EXECNAME).elf 
	ssh pi@raspberrypi.home -f "chmod +x /home/$(EXECNAME).elf"

## SSH link to run the file from the host system.
run: $(EXECNAME).arm install
# This may need a password.
	ssh pi@raspberrypi.home -f "cd /home/ && ./$(EXECNAME).elf && exit"



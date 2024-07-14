# Include every cpp file on the folder.
# Header files are automatically included when needed.
files = $(wildcard *.cpp)

# define cross compiler parameters and flags
arm_CC = aarch64-linux-gnu-g++
arm_CFLAGS = -mcpu=cortex-a53 -static -O3 -Wall
armaux_CFLAGS = -mcpu=cortex-a53 -static -O0 -Wall -g -W # Debugger flags added and Warning/

# Define basic ouput name.
EXECNAME = output

# ## Define build processes : 
# all correspond to target build
all: clean $(EXECNAME).arm

# Clean remove .o files or execnames.
clean:
	@rm -f *.o $(EXECNAME)
	@rm -f *.arm $(EXECNAME)
	@rm -f *.x86 $(EXECNAME)

# ## Architecture specific builds
# ARM V6 build optimized. Ready for production.
$(EXECNAME).arm: clean
	@touch $(EXECNAME).arm
	$(arm_CC) $(arm_CFLAGS) -o $(EXECNAME).arm -c $(files)
	@chmod +x $(EXECNAME).arm

# ARM V6 build, less optimized with every warnings.
arm_debug: clean
	@touch $(EXECNAME).arm
	$(arm_CC) $(armaux_CFLAGS) -o $(EXECNAME).arm -c $(files)
	@chmod +x $(EXECNAME).arm

## SCP links to place the file on the RPi
install: $(EXECNAME).arm
# This may need a password.
	scp $(EXECNAME).arm pi@raspberrypi.home:/home/$(EXECNAME).elf 

## SSH link to run the file from the host system.
run: $(EXECNAME).arm install
# This may need a password.
	ssh pi@raspberrypi.home -f "cd /home/ && ./$(EXECNAME).elf && exit"



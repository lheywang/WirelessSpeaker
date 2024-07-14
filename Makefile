# define some files
# In the future, add every file that shall be compiled here, separated by spaces.
files = main.cpp

# define some variables
arm_CC = arm-linux-gnueabihf-g++
arm_CFLAGS = -O3 -g3 -Wall
armaux_CFLAGS = -O0 -g3 -Wall -g -W # This one add Clang / LLVM debugger outputs and lower optimisation.
x86_CC = g++
x86_CFLAGS = -O0 -Wall

EXECNAME = output.elf

# ## Define build processes : 
# all correspond to target build
all: clean arm

# Clean remove .o files or execnames.
clean:
	@rm -f *.o $(EXECNAME)

# ## Architecture specific builds
# ARM V6 build optimized. Ready for production.
arm: clean
	$(arm_CC) $(arm_CFLAGS) -o $(EXECNAME) -c $(files)
	@chmod +x $(EXECNAME)

# ARM V6 build, less optimized with every warnings.
arm_debug: clean
	$(arm_CC) $(armaux_CFLAGS) -o $(EXECNAME) -c $(files)
	@chmod +x $(EXECNAME)
	
# X86 build, only for compiling purposes tests. Will be removed.
x86: clean
	@echo "Running in x86 mode. Output cannot be executed or launched after."
	$(x86_CC) $(x86_CFLAGS) -o $(EXECNAME) -c $(files)
	@chmod +x $(EXECNAME)

## SSH links
#install: arm
#	scp ... To be tested.



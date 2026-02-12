# Global Makefile to build EVERYTHING needed.

all: rw612 stm32_if niosV

rw612: common

stm32_if: common

niosV: common

common:
	mkdir -p build/
	cmake -S src/ -B build/
	cmake --build build/

common_test:
	mkdir -p build/
	cmake -S src/ -B build/ -DTESTS_BUILDS_LCXP=ON
	cmake --build build/ 


clean:
	cmake --build build/ --target clean

# Global Makefile to build EVERYTHING needed.

all: rw612 stm32_if niosV

rw612: common

stm32_if: common

niosV: common

common:
	mkdir -p build/
	cmake -S src/ -B build/
	cmake --build build/

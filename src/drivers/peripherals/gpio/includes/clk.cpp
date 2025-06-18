/**
 * @file clk.cpp
 * @author ddouglass
 * @brief This file contain source code for GPCLK0 module on RPi Zero 2W. Original made by ddouglass (https://github.com/LCOGT/minimal_clk/tree/main)
 * @version 1.0
 * @date 2022-07-05
 *
 * @copyright Copyright (c) 2022
 *
 * @warning I've (lheywang) removed some useless functions for MY needs.
 *
 */

// Header
#include "drivers/peripherals/core/clk.hpp"

// STD
#include <cstdint>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

// ==============================================================================
// PRIVATE DEFINES
// ==============================================================================
// Valids for RP3A0 die (BCM2836 and BCM2837 chips only !)
#define piPeriphBase 0x3F000000
#define piBusAddr 0xC0000000

#define SYST_BASE (piPeriphBase + 0x003000)
#define CLK_BASE (piPeriphBase + 0x101000)
#define GPIO_BASE (piPeriphBase + 0x200000)

#define CLK_LEN 0xA8
#define GPIO_LEN 0xB4
#define SYST_LEN 0x1C

#define GPPUD 37

#define CLK_PASSWD (0x5A << 24)

#define CLK_CTL_MASH(x) ((x) << 9)
#define CLK_CTL_BUSY (1 << 7)
#define CLK_CTL_KILL (1 << 5)
#define CLK_CTL_ENAB (1 << 4)
#define CLK_CTL_SRC(x) ((x) << 0)

#define CLK_SRCS 4

#define CLK_CTL_SRC_OSC 1 /* 19.2 MHz or 54 MHz (Pi4)*/
#define CLK_CTL_SRC_PLLC 5 /* 1000 MHz */
#define CLK_CTL_SRC_PLLD 6 /*  500 MHz  or 750 MHz (Pi4)*/
#define CLK_CTL_SRC_HDMI 7 /*  216 MHz */

#define CLK_DIV_DIVI(x) ((x) << 12)
#define CLK_DIV_DIVF(x) ((x) << 0)

#define CLK_GP0_CTL 28
#define CLK_GP0_DIV 29
#define CLK_GP1_CTL 30
#define CLK_GP1_DIV 31
#define CLK_GP2_CTL 32
#define CLK_GP2_DIV 33

/* gpio modes. */

#define PI_INPUT 0
#define PI_ALT0 4

static uint32_t* gpioReg = (uint32_t*)MAP_FAILED;
static uint32_t* systReg = (uint32_t*)MAP_FAILED;
static uint32_t* clkReg = (uint32_t*)MAP_FAILED;

// ==============================================================================
// PRIVATE FUNCTIONS
// ==============================================================================

static uint32_t* initMapMem(int fd, uint32_t addr, uint32_t len)
{
    return (uint32_t*)mmap(
        0, len, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_SHARED | MAP_LOCKED, fd, addr);
}

void gpioSetMode(unsigned gpio, unsigned mode)
{
    int reg, shift;

    reg = gpio / 10;
    shift = (gpio % 10) * 3;

    gpioReg[reg] = (gpioReg[reg] & ~(7 << shift)) | (mode << shift);
}

int gpioInitialise()
{
    int fd;

    fd = open("/dev/mem", O_RDWR | O_SYNC);

    if(fd < 0)
    {
        fprintf(
            stderr,
            "[ GPCLK0 ][ gpioInitialise ] : This program needs root privileges. Try using sudo\n");
        return -1;
    }

    gpioReg = initMapMem(fd, GPIO_BASE, GPIO_LEN);
    systReg = initMapMem(fd, SYST_BASE, SYST_LEN);
    clkReg = initMapMem(fd, CLK_BASE, CLK_LEN);

    close(fd);

    if((gpioReg == MAP_FAILED) || (systReg == MAP_FAILED) || (clkReg == MAP_FAILED))
    {
        fprintf(stderr, "[ GPCLK0 ][ gpioInitialise ] : Bad, mmap failed\n");
        return -1;
    }
    return 0;
}

// ==============================================================================
// FUNCTIONS
// ==============================================================================

int initClock(int source, int divI, int divF, int MASH)
{
    if(gpioInitialise() < 0)
        return -1;
    gpioSetMode(4, PI_ALT0);

    int src[CLK_SRCS] = {CLK_CTL_SRC_PLLD, CLK_CTL_SRC_OSC, CLK_CTL_SRC_HDMI, CLK_CTL_SRC_PLLC};

    int clkSrc;

    if((source < 0) || (source > 3))
        return -3;
    if((divI < 2) || (divI > 4095))
        return -4;
    if((divF < 0) || (divF > 4095))
        return -5;
    if((MASH < 0) || (MASH > 3))
        return -6;

    clkSrc = src[source];

    /* wait for clock to stop */
    while(*clkReg & CLK_CTL_BUSY)
    {
        usleep(10);
    }

    *clkReg = (CLK_PASSWD | CLK_DIV_DIVI(divI) | CLK_DIV_DIVF(divF));
    usleep(10);
    *clkReg = (CLK_PASSWD | CLK_CTL_MASH(MASH) | CLK_CTL_SRC(clkSrc));
    usleep(10);
    *clkReg |= (CLK_PASSWD | CLK_CTL_ENAB);

    return 0;
}

int termClock()
{
    gpioSetMode(4, PI_INPUT);
    *clkReg = CLK_PASSWD | CLK_CTL_KILL; // Segfault if original syntax.

    /* wait for clock to stop */
    while(*clkReg & CLK_CTL_BUSY)
    {
        usleep(10);
    }

    return 0;
}
/**
 * @file GPIO.cpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Source for the GPIO base functions
 * @version 0.1
 * @date 2024-10-03
 *
 * @copyright Copyright (c) 2024
 *
 */

// ==============================================================================
// INCLUDES
// ==============================================================================
#include "GPIO.hpp"
#include "GPIO_Engine.hpp"

#include <linux/gpio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <cstdint>

// ==============================================================================
// FUNCTIONS
// ==============================================================================
int GetGPIOChipInfos(gpiochip_info *info)
{
    // device file management
    int fd = open(DEV_NAME, O_RDONLY);
    if (fd < 0)
    {
        fprintf(stderr, "[ GPIO ][ GetGPIOChipInfos ] : Failed to open the device file for %s", DEV_NAME);
        return -1;
    }

    // request data
    int ret = ioctl(fd, GPIO_GET_CHIPINFO_IOCTL, info);
    close(fd);
    if (ret < 0)
    {
        fprintf(stderr, "[ GPIO ][ GetGPIOChipsInfos ] : Failed to fetch the infos about the gpiochip.");
        return -2;
    }

    // Close and exit
    return 0;
}

int GetGPIOInfo(GPIO *info)
{
    struct gpioline_info line;
    line.line_offset = (__u32)info->PinNumber;

    int fd = open(DEV_NAME, O_RDONLY);
    if (fd < 0)
    {
        fprintf(stderr, "[ GPIO ][ GetGPIOInfo ] : Failed to open the device file for %s :  %s", DEV_NAME, strerror(errno));
        return -1;
    }
    int ret = ioctl(fd, GPIO_GET_LINEINFO_IOCTL, &line);
    if (ret < 0)
    {
        fprintf(stderr, "[ GPIO ][ GetGPIOInfo ] : Failed to read infos for GPIO at offset %d : %s", info->PinNumber, strerror(errno));
        close(fd);
        return -2;
    }

    // Copying the data
    memcpy(info->Name, line.name, GPIO_MAX_NAME_SIZE);

    info->InOut = (line.flags & GPIOLINE_FLAG_IS_OUT) ? true : false;
    info->Polarity = (line.flags & GPIOLINE_FLAG_ACTIVE_LOW) ? true : false;

    info->Type = 0;
    info->Type = (line.flags & GPIOLINE_FLAG_OPEN_DRAIN) ? 1 : ((line.flags & GPIOLINE_FLAG_OPEN_SOURCE) ? 2 : 0);

    info->Kernel = (line.flags & GPIOLINE_FLAG_KERNEL) ? 1 : 0;

    // Close and exit
    close(fd);
    return 0;
}

int ReadGPIO(GPIO *info, int *const status)
{
    struct gpiohandle_request rq;
    struct gpiohandle_data data;

    int fd = open(DEV_NAME, O_RDONLY);
    if (fd < 0)
    {
        fprintf(stderr, "[ GPIO ][ ReadGPIO ] : Failed to open the device file for %s :  %s", DEV_NAME, strerror(errno));
        return -1;
    }

    rq.lineoffsets[0] = info->PinNumber;
    rq.flags = GPIOHANDLE_REQUEST_INPUT;
    rq.lines = 1;
    int ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &rq);
    close(fd);
    if (ret < 0)
    {
        fprintf(stderr, "[ GPIO ][ ReadGPIO ] : Failed to get the line handle for GPIO at offset %d : %s", info->PinNumber, strerror(errno));
        return -2;
    }

    ret = ioctl(rq.fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data);
    close(rq.fd);
    if (ret < 0)
    {
        fprintf(stderr, "[ GPIO ][ ReadGPIO ] : Unable to get line value using ioctl at offset %d : %s", info->PinNumber, strerror(errno));
        return -3;
    }
    *status = data.values[0];
    info->InOut = false;
    return 0;
}

int WriteGPIO(GPIO *info, const int Status)
{
    struct gpiohandle_request rq;
    struct gpiohandle_data data;

    int fd = open(DEV_NAME, O_RDONLY);
    if (fd < 0)
    {
        fprintf(stderr, "[ GPIO ][ WriteGPIO ] : Failed to open the device file for %s :  %s", DEV_NAME, strerror(errno));
        return -1;
    }

    rq.lineoffsets[0] = info->PinNumber;
    rq.flags = GPIOHANDLE_REQUEST_OUTPUT;
    rq.lines = 1;
    int ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &rq);
    close(fd);
    if (ret < 0)
    {
        fprintf(stderr, "[ GPIO ][ WriteGPIO ] : Failed to get the line handle for GPIO at offset %d : %s", info->PinNumber, strerror(errno));
        return -2;
    }

    data.values[0] = (uint8_t)Status;
    ret = ioctl(rq.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
    close(rq.fd);
    if (ret == -1)

    {
        fprintf(stderr, "[ GPIO ][ WriteGPIO ] : Unable to set line value using ioctl at offset %d : %s", info->PinNumber, strerror(errno));
        return -3;
    }
    info->InOut = true;
    return 0;
}

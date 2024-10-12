/**
 * @file GPIO.cpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Source for the GPIO base functions
 * @version 1.0
 * @date 2024-10-03
 *
 * @copyright Copyright (c) 2024
 *
 */

// ==============================================================================
// INCLUDES
// ==============================================================================
#include "GPIO.hpp"

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
GPIO GPIO_GetInfos(const PINS Pin, const GPMODES Mode)
{
    struct GPIO info;
    struct gpioline_info line;

    line.line_offset = (__u32)Pin;
    info.Mode = (__u8)Mode;

    int fd = open(DEV_NAME, O_RDONLY);
    if (fd < 0)
    {
        std::cerr << "[ GPIO ][ GetGPIOInfo ] : Failed to open the device file for "
                  << DEV_NAME
                  << " : "
                  << strerror(errno)
                  << std::endl;
        return info;
    }
    int ret = ioctl(fd, GPIO_GET_LINEINFO_IOCTL, &line);
    if (ret < 0)
    {
        std::cerr << "[ GPIO ][ GetGPIOInfo ] : Failed to read infos for GPIO at offset "
                  << info.PinNumber
                  << " : "
                  << strerror(errno)
                  << std::endl;
        close(fd);
        return info;
    }

    // Copying the data
    memcpy(info.Name, line.name, GPIO_MAX_NAME_SIZE);

    info.InOut = (line.flags & GPIOLINE_FLAG_IS_OUT) ? true : false;
    info.Polarity = (line.flags & GPIOLINE_FLAG_ACTIVE_LOW) ? true : false;

    info.Type = 0;
    info.Type = (line.flags & GPIOLINE_FLAG_OPEN_DRAIN) ? 1 : ((line.flags & GPIOLINE_FLAG_OPEN_SOURCE) ? 2 : 0);

    info.Kernel = (line.flags & GPIOLINE_FLAG_KERNEL) ? 1 : 0;

    // Close and exit
    close(fd);
    return info;
}

int ReadGPIO(GPIO *info, int *const status)
{
    struct gpiohandle_request rq;
    struct gpiohandle_data data;

    int fd = open(DEV_NAME, O_RDONLY);
    if (fd < 0)
    {
        std::cerr << "[ GPIO ][ ReadGPIO ] : Failed to open the device file for "
                  << DEV_NAME
                  << " : "
                  << strerror(errno)
                  << std::endl;
        return -1;
    }

    rq.lineoffsets[0] = info->PinNumber;
    rq.flags = GPIOHANDLE_REQUEST_INPUT;
    rq.lines = 1;
    int ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &rq);
    close(fd);
    if (ret < 0)
    {
        std::cerr << "[ GPIO ][ ReadGPIO ] : Failed to get the line handle for GPIO at offset "
                  << info->PinNumber
                  << " : "
                  << strerror(errno)
                  << std::endl;
        return -2;
    }

    ret = ioctl(rq.fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data);
    close(rq.fd);
    if (ret < 0)
    {
        std::cerr << "[ GPIO ][ ReadGPIO ] : Unable to get line value using ioctl at offset "
                  << info->PinNumber
                  << " : "
                  << strerror(errno)
                  << std::endl;
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
        std::cerr << "[ GPIO ][ WriteGPIO ] : Failed to open the device file for "
                  << DEV_NAME
                  << " : "
                  << strerror(errno)
                  << std::endl;
        return -1;
    }

    rq.lineoffsets[0] = info->PinNumber;
    rq.flags = GPIOHANDLE_REQUEST_OUTPUT;
    rq.lines = 1;
    int ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &rq);
    close(fd);
    if (ret < 0)
    {
        std::cerr << "[ GPIO ][ WriteGPIO ] : Failed to get the line handle for GPIO at offset"
                  << info->PinNumber
                  << " : "
                  << strerror(errno)
                  << std::endl;
        return -2;
    }

    data.values[0] = (uint8_t)Status;
    ret = ioctl(rq.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
    close(rq.fd);
    if (ret == -1)

    {
        std::cerr << "[ GPIO ][ WriteGPIO ] : Unable to set line value using ioctl at offset "
                  << info->PinNumber
                  << " : "
                  << strerror(errno)
                  << std::endl;
        return -3;
    }
    info->InOut = true;
    return 0;
}
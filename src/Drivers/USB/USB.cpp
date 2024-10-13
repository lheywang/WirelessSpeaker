/**
 * @file USB_Engine.cpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Implement USB functions in C++
 * @version 0.1
 * @date 2024-10-09
 *
 * @copyright Copyright (c) 2024
 *
 */

/*
#include "USB.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <errno.h>
#include <linux/usb.h>
#include "iostream"

USB_Bus *USB_GetInfos(const USB_Devices Bus)
{
    USB_Bus *USB = new USB_Bus;

    int DeviceID = 0;
    switch (Bus)
    {
    case USB_Devices::AUDIO:
        DeviceID = 0x99; // TO BE CHANGED!!!!!
        break;
    }
    snprintf(USB->USB_Filename, sizeof(USB->USB_Filename), "/dev/bus/usb/%d", DeviceID);

    USB->USB_File = open(USB->USB_Filename, O_RDWR);
    if (USB->USB_File < 0)
    {
        std::cerr << "[ USB ][ GetInfos ] : Unable to open device file : "
                  << USB->USB_Filename
                  << " : "
                  << strerror(errno)
                  << std::endl;
        return USB;
    }

    int res = 0;
    res = ioctl(USB->USB_File, 0x06, &USB->desc); // HARD CODED VALUE FOR USB_DEVICE_GET_DESCRIPTOR. To be checked !
    if (res < 0)
    {
        std::cerr << "[ USB ][ GetInfos ] : Unable to fetch device descriptor : "
                  << USB->USB_Filename
                  << " : "
                  << strerror(errno)
                  << std::endl;
        return USB;
    }
}

int USB_Close(USB_Bus *USB)
{
    close(USB->USB_File);
    delete USB;
    return 0;
}

int USB_Write(USB_Bus *USB, int *const Data, const int Len)
{
    int count = 0;
    count = write(USB->USB_File, Data, Len);
    if (count != Len)
    {
        std::cerr << "[ USB ][ Write ] : Could not write the requested data lengh : "
                  << strerror(errno)
                  << std::endl;
        return -1;
    }
    return 0;
}

int USB_Read(USB_Bus *USB, int *const Data, const int Len)
{
    int count = 0;
    count = read(USB->USB_File, Data, Len);
    if (count < Len)
    {
        std::cerr << "[ USB ][ Read ] : Could not read the specified data lengh : "
                  << strerror(errno)
                  << std::endl;
        return -1;
    }
    return 0;
}
*/
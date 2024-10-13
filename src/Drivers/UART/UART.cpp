/**
 * @file UART.cpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Implement UART functions in C++
 * @version 1.0
 * @date 2024-10-09
 *
 * @copyright Copyright (c) 2024
 *
 * @remark Class was tested successfully on 13/10/2024.
 *
 */

#include <stdio.h>
#include <string.h>

#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>

#include <termios.h>

#include "UART.hpp"

UART_Bus *UART_GetInfos(const int Bus)
{
    UART_Bus *UART = new UART_Bus;

    snprintf(UART->UART_Filename, sizeof(UART->UART_Filename), "/dev/serial%d", Bus);
    UART->UART_File = open(UART->UART_Filename, O_RDWR);
    if (UART->UART_File < 0)
    {
        std::cerr << "[ UART ][ GetInfos ] : Cannot open requested device file : "
                  << UART->UART_Filename
                  << " - "
                  << strerror(errno)
                  << std::endl;
        return UART;
    }

    int res = 0;
    res = tcgetattr(UART->UART_File, &UART->TTY);

    if (res < 0)
    {
        std::cerr << "[ UART ][ GetInfos ] : Failed to get the COM port settings : "
                  << strerror(errno)
                  << std::endl;
        return UART;
    }

    return UART;
}

int UART_Close(UART_Bus *UART)
{
    close(UART->UART_File);
    delete UART;
    return 0;
}

int UART_Configure(UART_Bus *UART,
                   const UART_PARITY ParityBit,
                   const UART_STOP StopBit,
                   const UART_DATA_WIDTH BitNumber,
                   const UART_CTRL FLowControl,
                   const UART_BAUD BaudRate)
{
    // =======================
    // C FLAG
    // =======================
    // Parity bit
    if ((bool)ParityBit == true)
        UART->TTY.c_cflag |= PARENB; // Enable parity
    else
        UART->TTY.c_cflag &= ~PARENB; // Disable parity

    // Stop bit
    if ((int)StopBit > 1)
        UART->TTY.c_cflag |= CSTOPB; // 2 stop bit
    else
        UART->TTY.c_cflag &= ~CSTOPB; // 1 stop bit

    int CSFlag = 0;
    switch ((int)BitNumber)
    {
    case 5:
        CSFlag = CS5;
        break;
    case 6:
        CSFlag = CS6;
        break;
    case 7:
        CSFlag = CS7;
        break;
    case 8:
        CSFlag = CS8;
        break;
    }

    UART->TTY.c_cflag &= ~CSIZE; // Clear old value
    UART->TTY.c_cflag |= CSFlag;

    if (((int)FLowControl & (int)UART_CTRL::HW_FLOW) > 0)
        UART->TTY.c_cflag |= CRTSCTS; // Enable hardware flow control
    else
        UART->TTY.c_cflag &= ~CRTSCTS; // Disable hardware flow control

    UART->TTY.c_cflag |= (CREAD | CLOCAL); // Turn on READ & ignore ctrl lines (CLOCAL = 1)

    // =======================
    // L FLAG
    // =======================
    UART->TTY.c_lflag &= ~ICANON;
    UART->TTY.c_lflag &= ~ECHO;   // Disable echo
    UART->TTY.c_lflag &= ~ECHOE;  // Disable erasure
    UART->TTY.c_lflag &= ~ECHONL; // Disable new-line echo
    UART->TTY.c_lflag &= ~ISIG;   // Disable interpretation of INTR, QUIT and SUSP

    // =======================
    // I FLAG
    // =======================
    if (((int)FLowControl & (int)UART_CTRL::SW_FLOW) > 0)
        UART->TTY.c_iflag |= (IXON | IXOFF | IXANY); // Enable software flow control
    else
        UART->TTY.c_iflag &= ~(IXON | IXOFF | IXANY); // Disable software flow control
    UART->TTY.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL);

    // =======================
    // O FLAG
    // =======================
    UART->TTY.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    UART->TTY.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed

    // =======================
    // DELAYS
    // =======================
    UART->TTY.c_cc[VTIME] = MAX_WAIT_DELAY_DS;
    UART->TTY.c_cc[VMIN] = MIN_RECV_BYTES;

    // =======================
    // IOCTL
    // =======================
    cfsetispeed(&UART->TTY, (int)BaudRate);
    cfsetospeed(&UART->TTY, (int)BaudRate);

    int res = tcsetattr(UART->UART_File, TCSANOW, &UART->TTY);

    if (res < 0)
    {
        std::cerr << "[ UART ][ Configure ] : Failed to save settings for the COM port : "
                  << strerror(errno)
                  << std::endl;
        return -3;
    }
    return 0;
}
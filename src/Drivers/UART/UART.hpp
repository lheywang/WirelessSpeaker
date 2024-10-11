/**
 * @file UART.hpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Define UART Constants
 * @version 0.1
 * @date 2024-10-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "UART_Engine.hpp"
#include <termios.h>

#define HW_FLOW 0x01
#define SW_FLOW 0x02

#define MAX_WAIT_DELAY_DS 5 // 500 ms
#define MIN_RECV_BYTES 0

#define INTERFACE "CY7C65213"
#define MAX_BAUD 3'000'000
#define MAX_FIFO 256
#define HW_CONTROL true
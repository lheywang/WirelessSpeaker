/**
 * @file    lcap.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief
 * @version 0.1
 * @date    2026-02-10
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

/* *******************************************************************
 * INCLUDE
 * *******************************************************************/
// STD
#include <cstdint>

// Standard library
#include "lcxp.h"

namespace lcip
{

    /* *******************************************************************
     * ENUMS
     * *******************************************************************/
    typedef enum opcodes
    {
        // SYS
        SYS_PING = 0x00,
        SYS_ACK = 0x01,
        SYS_NACK = 0x02,
        SYS_RESET = 0x03,
        SYS_READY = 0x04,
        SYS_INFO_GET = 0x05,
        SYS_INFO_RET = 0x06,
        SYS_UUID_GET = 0x07,
        SYS_UUID_GET = 0x08,

        // USER OUTPUTS
        LEDS_SET = 0x10,

        // USER INPUTS
        BP_GET = 0x20,
        BP_VALUES = 0x21,

        // SCREEN CONFIG
        SCREEN_INIT = 0x30,
        SCREEN_SHOW = 0x31,
        SCREEN_VOL = 0x32,
        SCREEN_PWR = 0x33,
        SCREEN_OFF = 0x34,

        // INTERRUPTS
        BP_TOUCHED = 0xF0
    };

    /* *******************************************************************
     * STRUCTS
     * *******************************************************************/

    /* *******************************************************************
     * CLASS
     * *******************************************************************/

    class LCIP : public lcxp::LCxP
    {
    public:
        // CONSTRUCTORS AND DESTRUCTORS

    private:
    };

}
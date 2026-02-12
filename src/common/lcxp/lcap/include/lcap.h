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

namespace lcap {

    /* *******************************************************************
    * ENUMS
    * *******************************************************************/
    typedef enum opcodes {
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

        // AUDIO CONFIG
        AUD_FMT = 0x10,
        AUD_MUTE = 0x11,
        AUD_SRC_TYPE = 0x12,

        // TRANSPORT CONTROLS
        TR_STOP = 0x20,
        TR_PLAY = 0x21,
        TR_PAUSE = 0x22,
        TR_NEXT = 0x23,
        TR_PREV = 0x24,

        // SCREEN CONFIG
        META_STATE = 0x30,
        META_TITLE = 0x31,
        META_ARTIST = 0x32,
        META_ALBUM = 0x33,
        META_TIME = 0x34,

        // INTERRUPTS
        BP_TOUCHED = 0xF0
    };

    /* *******************************************************************
    * STRUCTS
    * *******************************************************************/

    /* *******************************************************************
    * CLASS
    * *******************************************************************/

    class LCAP {
        
    };

}
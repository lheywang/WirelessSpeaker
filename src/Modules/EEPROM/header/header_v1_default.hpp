/**
 * @file header_default.hpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Define header default values.
 * @version 0.1
 * @date 2024-10-17
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "header.hpp"

constexpr struct EEPROM_HEADER_V1 DEFAULT_HEADER_V1
{
    .DATA_VERSION{
        .Major = 1,
        .Median = 0,
        .Minor = 0,
    },
        .LAST_WRITE{
            .Year = {19, 70},
            .Month = 01,
            .Day = 01,
            .Hour = 00,
            .Minutes = 00,
            .Seconds = 01,
        },
        .HARDWARE_VERSION{
            .Major = 1,
            .Minor = 0,
        },
        .BOM_VERSION{
            .Major = 1,
            .Minor = 0,
        },
        .SERIAL_NB{
            .Letters = {'S', 'P'},
            .Decimals = {'0', '0', '0', '0', '0', '0'},
        },
        .DESIGN_DATE{
            .Year = {19, 70},
            .Month = 01,
            .Day = 01,
            .Hour = 00,
            .Minutes = 00,
            .Seconds = 01,
        },
        .DATA_ADD = 0x80,
        .DATA_LEN = 256,
};
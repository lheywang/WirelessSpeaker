/**
 * @file config_v1_default.hpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Define default settings for the Config V1 struct
 * @version 0.1
 * @date 2024-10-17
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "StructV1.hpp"

constexpr struct CONFIG_V1 CONFIG_DEFAULT
{
    .Audio{
        .EQ{
            .BassGain = 0x80,
            .MediumGainRight = 0x80,
            .MediumGainLeft = 0x80,
            .HighGainRight = 0x80,
            .HighGainLeft = 0x80,
            .LowPassValueLeft = 0x20,
            .LowPassValueRight = 0x20,
            .HighPassValueLeft = 0x20,
            .HighPassValueRight = 0x20,
        },
        .DAC{
            .Automute_delay = 0x04,
            .Global_Volume = 0x30,
            .Left_Volume = 0x30,
            .Right_Volume = 0x30,
            .LeftDataPath = 0x01,
            .RightDataPath = 0x01,
            .LeftAnalogAtten = 0x00,
            .RightAnalogAtten = 0x00,
            .NumberOfDSPProfiles = 0x00,
        },
        .BassAmp{
            .PowerLimit = 0xFF,
        },
        .LeftAmp{
            .PowerLimit = 0xFF,
        },
        .RightAmp{
            .PowerLimit = 0xFF,
        },
    },
        .LedsBack{
            .Brightness = 0xC0,
            .MaximalBrightness = 0xFF,
        },
        .LedsTop1{
            .Brightness = 0xC0,
            .MaximalBrightness = 0xFF,
        },
        .LedsTop2{
            .Brightness = 0xC0,
            .MaximalBrightness = 0xFF,
        },
        .LedsTop3{
            .Brightness = 0xC0,
            .MaximalBrightness = 0xFF,
        },
        .Capacitive{
            .Threshold = 0x04,
            .Sensivity = 0x03,
        },
        .PDProfile1{
            .Voltage = {20, 00},
            .Current = {5, 00},
            .EnablePPS = 0x00,
        },
        .PDProfile2{
            .Voltage = {20, 00},
            .Current{3, 6},
            .EnablePPS = 0x00,
        },
        .SpeakerName = "WIRELESS SPEAKER !",
};

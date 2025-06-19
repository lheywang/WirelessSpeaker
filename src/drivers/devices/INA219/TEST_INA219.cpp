/**
 * @file TEST_INA219.cpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Source for unittesting the different conversion functions
 * @version 1.0
 * @date 2025-06-19
 *
 * @copyright Copyright (c) 2025
 *
 */

// ==============================================================================
// INCLUDES
// ==============================================================================

// Including the unit test framework
#include "CppUTest/TestHarness.h"

// Include the tested header
#include "drivers/devices/INA219.hpp"

// Utils
#include <utils/term_color.hpp>

// STD
#include <cstdint>

// ==============================================================================
// DEFINES
// ==============================================================================
#define FLOAT_TOLERANCE                                                                            \
    (1 / 32) // Sensor is given for 0.0625° of precision. This value correspond to half of it.

// ==============================================================================
// TEST GROUPS
// ==============================================================================

// Define a test group. All tests within this group will share setup/teardown if defined.
TEST_GROUP(INA219_FloatToIntsConversion)
{
    INA219* sensor;
    I2C_Bus bus = I2C_Bus{
        .I2C_file = 0x0000000,
        .I2C_filename = "/dev/i2c.0",
        .I2C_bus = 0,
    };

    void setup()
    {
        sensor = new INA219(&bus, CURRENT_MONITOR::SHUNT_0);
        return;
    };
    void teardown()
    {
        delete sensor;
        sensor = nullptr;
        return;
    };
};
TEST_GROUP(INA219_IntsToFloatConversion)
{
    INA219* sensor;
    I2C_Bus bus = I2C_Bus{
        .I2C_file = 0x0000000,
        .I2C_filename = "/dev/i2c.0",
        .I2C_bus = 0,
    };

    void setup()
    {
        sensor = new INA219(&bus, CURRENT_MONITOR::SHUNT_0);
    };
    void teardown()
    {
        delete sensor;
        sensor = nullptr;
    };
};

// ==============================================================================
// TESTS (FloatToInts)
// ==============================================================================

// Now, define your individual test cases
TEST(INA219_FloatToIntsConversion, HandlesPositiveFloat)
{
    std::cout << CYAN << "[ INA219  ]: Testing positives floats..." << RESET;
    float inputs[] = {0.01f, 0.02f, 39.98f, 40.0f};
    int16_t outputs[] = {1, 2, 3998, 4000};

    for(int k = 0; k < 4; k++) // Loop for different values
    {
        for(int g = 1; g < 5; g++) // Loop for different gains
        {

            sensor->__SetPGASetting(g);
            int16_t out = sensor->ConvertFloatToInt(inputs[k]);
            CHECK_EQUAL(outputs[k], out);
        }
    }
    std::cout << GREEN << " OK !" << RESET << std::endl;
}

TEST(INA219_FloatToIntsConversion, HandlesNegativeFloat)
{
    std::cout << CYAN << "[ INA219  ]: Testing negatives floats..." << RESET;
    float inputs[] = {-0.01f, -0.02f, -39.98f, -40.0f};
    int16_t outputs[] = {-1, -2, -3998, -4000};

    for(int k = 0; k < 4; k++) // Loop for different values
    {
        for(int g = 1; g < 5; g++) // Loop for different gains
        {

            sensor->__SetPGASetting(g);
            int16_t out =
                sensor->ConvertFloatToInt(inputs[k]) &
                0xFFFF; // A Cast is required for the test to pass, otherwise the sign won't extend !
            CHECK_EQUAL(outputs[k], out);
        }
    }
    std::cout << GREEN << " OK !" << RESET << std::endl;
}

TEST(INA219_FloatToIntsConversion, HandlesNullFloat)
{
    std::cout << CYAN << "[ INA219  ]: Testing zero floats..." << RESET;
    float inputs = 0.0f;
    int16_t outputs = 0;

    for(uint8_t g = 1; g < 5; g++)
    {
        sensor->__SetPGASetting(g);
        int16_t out =
            sensor->ConvertFloatToInt(inputs) &
            0xFFFF; // A Cast is required for the test to pass, otherwise the sign won't extend !
        CHECK_EQUAL(outputs, out);
    }

    std::cout << GREEN << " OK !" << RESET << std::endl;
}

TEST(INA219_FloatToIntsConversion, HandlesLargePositiveFloat)
{
    std::cout << CYAN << "[ INA219  ]: Testing large positives floats..." << RESET;
    float inputs[] = {159.99f, 160.02f, 319.98f, 320.00f};
    int16_t outputs[] = {15999, 16002, 31998, 32000};

    for(int k = 0; k < 4; k++) // Loop for different values
    {
        int16_t out = sensor->ConvertFloatToInt(inputs[k]);
        CHECK_EQUAL(outputs[k], out);
    }
    std::cout << GREEN << " OK !" << RESET << std::endl;
}

TEST(INA219_FloatToIntsConversion, HandlesLargeNegativeFloat)
{
    std::cout << CYAN << "[ INA219  ]: Testing large negatives floats..." << RESET;
    float inputs[] = {-159.99f, -160.02f, -319.98f, -320.00f};
    int16_t outputs[] = {-15999, -16002, -31998, -32000};

    for(int k = 0; k < 4; k++) // Loop for different values
    {
        int16_t out =
            sensor->ConvertFloatToInt(inputs[k]) &
            0xFFFF; // A Cast is required for the test to pass, otherwise the sign won't extend !
        CHECK_EQUAL(outputs[k], out);
    }
    std::cout << GREEN << " OK !" << RESET << std::endl;
}

TEST(INA219_FloatToIntsConversion, HandlesBoundariesFloat)
{
    std::cout << CYAN << "[ INA219  ]: Testing boundaries floats..." << RESET;
    float inputs[] = {40.00f, 80.00f, 160.00f, 320.00f, -40.00f, -80.00f, -160.00f, -320.00f};
    int16_t outputs[] = {4000, 8000, 16000, 32000, -4000, -8000, -16000, -32000};
    int gains[] = {4, 3, 2, 1, 4, 3, 2, 1};

    for(int k = 0; k < 8; k++) // Loop for different values
    {
        sensor->__SetPGASetting(gains[k]);
        int16_t out =
            sensor->ConvertFloatToInt(inputs[k]) &
            0xFFFF; // A Cast is required for the test to pass, otherwise the sign won't extend !
        CHECK_EQUAL(outputs[k], out);
    }
    std::cout << GREEN << " OK !" << RESET << std::endl;
}

// ==============================================================================
// TESTS (Ints2Float)
// ==============================================================================*

// Now, define your individual test cases
// TEST(INA219_IntsToFloatConversion, HandlesPositiveFloat)
// {
//     int inputs[] = {1, 2, 3, 4};
//     float outputs[] = {0, 0, 0, 0};

//     for(int k = 1; k < 4; k++)
//     {
//         sensor->__SetPGASetting(k);
//         int out = sensor->ConvertIntToFloat(inputs[k - 1]);
//         DOUBLES_EQUAL(out, outputs[k - 1], FLOAT_TOLERANCE);
//     }
// }
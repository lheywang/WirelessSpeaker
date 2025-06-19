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

// STD
#include <utils/term_color.hpp>

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
    int outputs[] = {1, 2, 3998, 4000};

    for(int k = 0; k < 4; k++) // Loop for different values
    {
        for(int g = 1; g < 5; g++) // Loop for different gains
        {

            sensor->__SetPGASetting(g);
            int out = sensor->ConvertFloatToInt(inputs[k]);
            CHECK_EQUAL(outputs[k], out);
        }
    }
    std::cout << GREEN << " OK !" << RESET << std::endl;
}

// Now, define your individual test cases
TEST(INA219_FloatToIntsConversion, HandlesNegativeFloat)
{
    std::cout << CYAN << "[ INA219  ]: Testing negatives floats..." << RESET;
    float inputs[] = {-0.01f, -0.02f, -39.98f, -40.0f};
    int outputs[] = {-1, -2, -3998, -4000};

    for(int k = 0; k < 4; k++) // Loop for different values
    {
        for(int g = 1; g < 5; g++) // Loop for different gains
        {

            sensor->__SetPGASetting(g);
            int out = sensor->ConvertFloatToInt(inputs[k]);
            CHECK_EQUAL(outputs[k], out);
        }
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
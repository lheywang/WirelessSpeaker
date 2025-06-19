/**
 * @file TEST_MCP9808.cpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Source for unittesting the different conversion functions
 * @version 1.0
 * @date 2025-06-17
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
#include "drivers/devices/MCP9808.hpp"

// Including terminals outputs
#include "utils/term_color.hpp"

// ==============================================================================
// DEFINES
// ==============================================================================
#define FLOAT_TOLERANCE                                                                            \
    (1 / 32) // Sensor is given for 0.0625° of precision. This value correspond to half of it.

// ==============================================================================
// TEST GROUPS
// ==============================================================================

// Define a test group. All tests within this group will share setup/teardown if defined.
TEST_GROUP(MCP9808_FloatToIntsConversion){void setup(){} void teardown(){}};
TEST_GROUP(MCP9808_IntsToFloatConversion){void setup(){} void teardown(){}};

// ==============================================================================
// TESTS (FloatToInts)
// ==============================================================================

// Now, define your individual test cases
TEST(MCP9808_FloatToIntsConversion, HandlesPositiveFloat)
{
    std::cout << CYAN << "[ MCP9808 ]: Testing Positive floats..." << RESET;
    float input = 10.0f;
    int output = 0;
    FloatToInts(input, &output);
    CHECK_EQUAL(0x00A0, output);

    input = 2.25f;
    output = 0;
    FloatToInts(input, &output);
    CHECK_EQUAL(0x024, output);
    std::cout << GREEN << " OK !" << RESET << std::endl;
}

TEST(MCP9808_FloatToIntsConversion, HandlesNegativeFloat)
{
    std::cout << CYAN << "[ MCP9808 ]: Testing Negative floats..." << RESET;
    float input = -5.0f;
    int output = 0;
    FloatToInts(input, &output);
    CHECK_EQUAL(0x1050, output);

    input = -1.5f;
    output = 0;
    FloatToInts(input, &output);
    CHECK_EQUAL(0x1018, output);
    std::cout << GREEN << " OK !" << RESET << std::endl;
}

TEST(MCP9808_FloatToIntsConversion, HandlesZero)
{
    std::cout << CYAN << "[ MCP9808 ]: Testing Zeroes..." << RESET;
    float input = 0.0f;
    int output = 0;
    FloatToInts(input, &output);
    CHECK_EQUAL(0x0000, output);
    std::cout << GREEN << " OK !" << RESET << std::endl;
}

TEST(MCP9808_FloatToIntsConversion, HandlesLargePositiveFloat)
{
    std::cout << CYAN << "[ MCP9808 ]: Testing Large positive floats..." << RESET;
    float input = 100.9f;
    int output = 0;
    FloatToInts(input, &output);
    CHECK_EQUAL(0x064E, output);
    std::cout << GREEN << " OK !" << RESET << std::endl;
}

TEST(MCP9808_FloatToIntsConversion, HandlesLargeNegativeFloat)
{
    std::cout << CYAN << "[ MCP9808 ]: Testing Large negative floats..." << RESET;
    float input = -100.9f;
    int output = 0;
    FloatToInts(input, &output);
    CHECK_EQUAL(0x164E, output);
    std::cout << GREEN << " OK !" << RESET << std::endl;
}

TEST(MCP9808_FloatToIntsConversion, BoundaryValueFloatPart)
{
    std::cout << CYAN << "[ MCP9808 ]: Testing boundaries floats..." << RESET;
    float input = 0.0625f;
    int output = 0;
    FloatToInts(input, &output);
    CHECK_EQUAL(0x0001, output);

    input = 0.9375f;
    output = 0;
    FloatToInts(input, &output);
    CHECK_EQUAL(0x000F, output);

    input = 255.9375f;
    output = 0;
    FloatToInts(input, &output);
    CHECK_EQUAL(0x0FFF, output);

    input = -255.9375f;
    output = 0;
    FloatToInts(input, &output);
    CHECK_EQUAL(0x1FFF, output);
    std::cout << GREEN << " OK !" << RESET << std::endl;
}

// ==============================================================================
// TESTS (IntsToFloat)
// ==============================================================================

// Now, define your individual test cases
TEST(MCP9808_IntsToFloatConversion, HandlesPositiveInteger)
{
    std::cout << CYAN << "[ MCP9808 ]: Testing Positive integers..." << RESET;
    int input = 0x01A5;
    float output = 0.0f;
    IntsToFloat(input, &output);
    DOUBLES_EQUAL(26.3125f, output, FLOAT_TOLERANCE);
    std::cout << GREEN << " OK !" << RESET << std::endl;
}

TEST(MCP9808_IntsToFloatConversion, HandlesNegativeInteger)
{
    std::cout << CYAN << "[ MCP9808 ]: Testing Negative integers..." << RESET;
    int input = 0xF1A5;
    float output = 0.0f;
    IntsToFloat(input, &output);
    DOUBLES_EQUAL(-26.3125f, output, FLOAT_TOLERANCE);
    std::cout << GREEN << " OK !" << RESET << std::endl;
}

TEST(MCP9808_IntsToFloatConversion, HandlesZero)
{
    std::cout << CYAN << "[ MCP9808 ]: Testing zero integers..." << RESET;
    int input = 0x0000;
    float output = 0.0f;
    IntsToFloat(input, &output);
    DOUBLES_EQUAL(0.0f, output, FLOAT_TOLERANCE);
    std::cout << GREEN << " OK !" << RESET << std::endl;
}

TEST(MCP9808_IntsToFloatConversion, HandlesLargePositiveFloat)
{
    std::cout << CYAN << "[ MCP9808 ]: Testing Large positive integers..." << RESET;
    int input = 0x03FF;
    float output = 0.0f;
    IntsToFloat(input, &output);
    DOUBLES_EQUAL(63.9375f, output, FLOAT_TOLERANCE);
    std::cout << GREEN << " OK !" << RESET << std::endl;
}

TEST(MCP9808_IntsToFloatConversion, HandlesLargeNegativeFloat)
{
    std::cout << CYAN << "[ MCP9808 ]: Testing Large negative integers..." << RESET;
    int input = 0x13FF;
    float output = 0.0f;
    IntsToFloat(input, &output);
    DOUBLES_EQUAL(-63.9375f, output, FLOAT_TOLERANCE);
    std::cout << GREEN << " OK !" << RESET << std::endl;
}

TEST(MCP9808_IntsToFloatConversion, BoundaryValueFloatPart)
{
    std::cout << CYAN << "[ MCP9808 ]: Testing boundaries integers..." << RESET;
    int input = 0xE000; // 3 unused bits
    float output = 0.0f;
    IntsToFloat(input, &output);
    DOUBLES_EQUAL(0.0f, output, FLOAT_TOLERANCE);

    input = 0xF010;
    output = 0.0f;
    IntsToFloat(input, &output);
    DOUBLES_EQUAL(-1.0f, output, FLOAT_TOLERANCE);
    std::cout << GREEN << " OK !" << RESET << std::endl;
}
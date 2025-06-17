#include "CppUTest/CommandLineTestRunner.h"

// This is the main function that runs all tests.
// You can pass command-line arguments to the test runner.
int main(int ac, char** av)
{
    return CommandLineTestRunner::RunAllTests(ac, av);
}
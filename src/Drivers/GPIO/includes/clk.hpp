/**
 * @file clk.hpp
 * @author ddouglass
 * @brief This file contain header code for GPCLK0 module on RPi Zero 2W. Original made by ddouglass (https://github.com/LCOGT/minimal_clk/tree/main)
 * @version 0.1
 * @date 2022-07-05
 *
 * @copyright Copyright (c) 2022
 *
 * @warning I've (lheywang) removed some useless functions for MY needs.
 *
 */

/**
 * @brief Initialize the clock the RPi Zero 2W and variants only !
 *
 *  Value  | Source
 *  ------ | ------
 *    0    | PLLD (500 MHz)
 *    1    | OSC (19.2 MHz)
 *    2    | HDMI (216 MHz)
 *    3    | PLLC (1 GHz)
 *
 *  Value  | Mash
 *  ------ | ------
 *    0    | OFF
 *    1    | Level 1
 *    2    | Level 2
 *    3    | Level 3
 *
 * @param[in] source Clock Source.
 * @param[in] divI Integer part of the divider (> 2 and < 4096)
 * @param[in] divF Real part of the divider (> -1 and < 4096)
 * @param[in] MASH Noise shapping filter mode
 *
 * @return  0 : OK
 * @return -1 : Cannot open GPIO
 * @return -2 : Invalid source
 * @return -3 : Invalid Integer divider
 * @return -4 : Invalid Real divider
 * @return -5 : Invalid noise shapping filter
 */
int initClock(int source, int divI, int divF, int MASH);

/**
 * @brief Close the clock
 *
 * @return 0
 */
int termClock();
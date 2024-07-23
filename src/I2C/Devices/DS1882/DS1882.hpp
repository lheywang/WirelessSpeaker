// ==============================================================================
//                              I2C/Devices/DS1882/DS1882.hpp
//                              Wrote by lheywang
//
// Define our basic I2C settings on the boards, such as : 
// - Register Addresses
// ==============================================================================

// Only included one time
#pragma once

// ==============================================================================
// IC REGISTER ADDRESSES
// ==============================================================================

#define     DS1882_DATA_SIZE    8 // 8b register here

// wipers value (bits 6 and 7)
#define     WIPER_0         0x00
#define     WIPER_1         0x40
#define     CONFIG          0x80

// define attenuation values
#define     ATTEN_EXTENDED  [[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63], [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 90]]
#define     ATTEN_DEFAULT   [[0, 1, 2? 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33], [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 39, 42, 45, 48, 51, 54, 57, 60, 90]]    

// config register defined values
#define     ZERO_CROSSING   0x01
#define     WIPER_RES       0x00
#define     WIPER_VOLATILE  0x02
#define     EEPROM_STORE    0x80

// ==============================================================================
// IC CLASS FUNCTIONS
// ==============================================================================

class DS1882 {
    private:

    public:
    // Constructors
        DS1882(); // Default to POTI0
        DS1882(int address);

    // Destructors
        ~DS1882();

    // Methods
        /**
         * @brief : Change the value of a potentiometer.
         * 
         * @param wiper int : Wiper selection. Use value defined in the header
         * @param value int : Wiper value.
         * 
         * @return int : 0 if correct, -1 if incorrect wiper has been choosed.
         */
        int WriteWiper(int wiper, int value);

        /**
         * @brief : read the value of a potentiometer
         * 
         * @param wiper int : Wiper selection. Use value defined in the header
         * 
         * @return int : value. -1 if incorrect wiper has been choosen.
         */
        int ReadWiper(int wiper);


};
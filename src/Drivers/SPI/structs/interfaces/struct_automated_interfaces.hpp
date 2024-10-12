/**
 * @file struct_automated_interfaces.hpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Define the user accessible interfaces that are managed automatically behaviors.
 * @version 0.1
 * @date 2024-10-08
 *
 * @copyright Copyright (c) 2024
 *
 */

/*! Define values that are stored on the EEPROM for the USB-C PD3 Interface*/
struct BasicPDO
{
    bool EnablePPS; /*!< Enable PPS (Programmable Power Supply)*/
    float Voltage;  /*!< Voltage requested for this PDO*/
    float Current;  /*!< Current requested for this PDO*/
};
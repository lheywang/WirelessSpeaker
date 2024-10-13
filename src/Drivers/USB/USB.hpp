/**
 * @file USB.hpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Define USB Constants
 * @version 0.1
 * @date 2024-10-09
 *
 * @copyright Copyright (c) 2024
 *
 */

// ==============================================================================
// DATA STRUCTURES
// ==============================================================================

/*! Define possible USB device to be openned */

// enum class USB_Devices
// {
//     AUDIO = 0x00, /*!< USB Audio Input*/
// };

/*! Define our custom USB struct that is used to define parameters. */
// struct USB_Bus
// {
//     int USB_File;                      /*!< USB file descriptor*/
//     char USB_Filename[30];             /*!< USB file name*/
//     int USB_Bus;                       /*!< USB Bus number*/
//     struct usb_device_descriptor desc; /*!< Linux USB Bus object*/
// };

// ==============================================================================
// FUNCTIONS
// ==============================================================================

// /**
//  * @brief Open the USB Device.
//  *
//  * @param[in] Bus The device to open
//  *
//  * @return  0 : OK
//  * @return -1 : Unable to open device file.
//  * @return -2 : Unable to fetch the device descriptor.
//  */
// USB_Bus *USB_GetInfos(const USB_Devices Bus);

// /**
//  * @brief Close an USB connection.
//  *
//  * @param[in] USB The connection to close
//  *
//  * @return  0 : OK
//  */
// int USB_Close(USB_Bus *USB);

// /**
//  * @brief Send data to this USB Device
//  *
//  * @param[in] USB An USB Struct to which the define the target of the data
//  * @param[in] Data A list of values to be sent
//  * @param[in] Len The lengh of the list
//  *
//  * @return  0 : OK
//  * @return -1 : IOCTL error.
//  */
// int USB_Write(USB_Bus *USB, int *const Data, const int Len);

// /**
//  * @brief
//  *
//  * @param[in] USB An USB Struct to which the define the target of the data
//  * @param[in] Data A list of values to be recevied
//  * @param[in] Len The lengh of the list
//  *
//  * @return  0 : OK
//  * @return -1 : IOCTL error.
//  */
// int USB_Read(USB_Bus *USB, int *const Data, const int Len);
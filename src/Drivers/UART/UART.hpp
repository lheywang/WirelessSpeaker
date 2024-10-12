/**
 * @file UART.hpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Define UART functions
 * @version 0.1
 * @date 2024-10-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <termios.h>

// ==============================================================================
// DATA STRUCTURES
// ==============================================================================

/*! Define values that are used to define the way to control the UART comm */
enum class UART_CTRL
{
    HW_FLOW = 0x01, /*!< Hardware control (require RTS / CTS)*/
    SW_FLOW = 0x02, /*!< Software control*/
};

constexpr int MAX_WAIT_DELAY_DS = 5; /*!< Up to 500ms without receiving any bytes trigger an exception*/
constexpr int MIN_RECV_BYTES = 0;    /*!< Each read call shall return at least 0 bytes*/

/*! Define USB to uart interface settings */
enum class CY7C65213
{
    MAX_BAUD = 3'000'000, /*!< Maximal baud rate for this chip*/
    MAX_FIFO = 256,       /*!< Max number of bytes sent before overflow*/
    HW_CONTROL = 1,       /*!< Does this chip is capable of hardware control*/
};

/*! Define a custom struct to be used within the UART driver*/
struct UART_Bus
{
    int UART_File;          /*!< UART file descriptor*/
    char UART_Filename[30]; /*!< UART file name*/
    int UART_Bus;           /*!< UART Bus number*/
    struct termios TTY;     /*!< Linux driver struct that store settings for this bus.*/
};

// ==============================================================================
// FUNCTIONS
// ==============================================================================

/**
 * @brief Open a new UART device
 *
 * @warning In case of failure, the file descriptor will remain negative ! And thus, unusable.
 *
 * @param Bus The number of the bus to be used.
 *
 * @return UART_bus
 */
UART_Bus *UART_GetInfos(const int Bus);

/**
 * @brief Close an existing UART device
 *
 * @param UART An UART object to be deleted.
 *
 * @return  0 : OK
 */
int UART_Close(UART_Bus *UART);

/**
 * @brief Configure the settings of the UART port to be used. Shall be called before any IO Operation.
 *
 * @param UART A pointer to an UART object
 * @param ParityBit Set to !0 to enable the parity bit
 * @param StopBit set the number of stop bits
 * @param BitNumber Set the number of bits to be sent for each transmit
 * @param FLowControl Enable any form of flow control. Send 0, HW_FLOW or SW_FLOW
 * @param BaudRate Set the baud rate used for the transfer.
 *
 * @return  0 : OK
 * @return -1 : Invalid bit number to be send
 * @return -2 : Invalid baud rate
 * @return -3 : IOCTL error.
 */
int UART_Configure(UART_Bus *UART,
                   const int ParityBit,
                   const int StopBit,
                   const int BitNumber,
                   const UART_CTRL FLowControl,
                   const int BaudRate);

/**
 * @brief Write a buffer to the UART port
 *
 * @param UART A pointer to an UART object
 * @param TX The buffer to be wrote on the TX line
 * @param Len The number of bytes to transmit
 *
 * @return  0 : OK
 * @return -1 : Failed to allocate buffer
 */
int UART_Write(UART_Bus *UART, int *const TX, const int Len);

/**
 * @brief Read a buffer from the UART port
 * @warning This function may block the process for 500 ms if not data has been received !
 *
 * @param UART A pointer to an UART object
 * @param RX The buffer to be rode
 * @param Len The number of bytes to receives
 *
 * @return  0 : OK
 * @return -1 : Failed to allocate buffer
 * @return -2 : IOCTL error.
 */
int UART_Read(UART_Bus *UART, int *const RX, const int Len);
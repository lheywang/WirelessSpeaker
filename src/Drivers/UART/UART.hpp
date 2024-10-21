/**
 * @file UART.hpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Define UART functions
 * @version 0.1
 * @date 2024-10-09
 *
 * @copyright Copyright (c)
 *
 * @remark Class was tested successfully on 13/10/2024.
 *
 */

#include <cstdlib>
#include <errno.h>
#include <string.h>
#include <termios.h>

// ==============================================================================
// DATA STRUCTURES
// ==============================================================================

/*! Define values that are used to define the way to control the UART comm */
enum class UART_CTRL
{
    HW_FLOW = 0x01, /*!< Hardware control (require RTS / CTS)*/
    SW_FLOW = 0x02, /*!< Software control*/
    NONE = 0x00, /*!< No control*/
};

/*! Define values that are used to define the way to control the UART parity comm */
enum class UART_PARITY
{
    OFF = 0x00, /*!< Enable parity bit*/
    ON = 0x021, /*!< Disable parity bit*/
};

/*! Define values that are used to define the way to control the UART stop bit comm */
enum class UART_STOP
{
    ONE = 0x01, /*!< One stop bit*/
    TWO = 0x02, /*!< Two stop bit*/
};

/*! Define values that are used to define the way to control the UART bit number comm */
enum class UART_DATA_WIDTH
{
    FIVE = 0x05, /*!< 5 data bit*/
    SIX = 0x06, /*!< 6 data bit*/
    SEVEN = 0x07, /*!< 7 data bit*/
    EIGHT = 0x08, /*!< 8 data bit*/
};

/*! Define values that are used to define the way to control the UART baud rate comm */
enum class UART_BAUD
{
    BD_0 = 0000000, /*!< PAUSE */
    BD_50 = 0000001, /*!< 50 bauds*/
    BD_75 = 0000002, /*!< 75 bauds*/
    BD_110 = 0000003, /*!< 110 bauds*/
    BD_134 = 0000004, /*!< 134 bauds*/
    BD_150 = 0000005, /*!< 150 bauds*/
    BD_200 = 0000006, /*!< 200 bauds*/
    BD_300 = 0000007, /*!< 300 bauds*/
    BD_600 = 0000010, /*!< 600 bauds*/
    BD_1K2 = 0000011, /*!< 1200 bauds STANDARD VALUE !*/
    BD_1K8 = 0000012, /*!< 1800 bauds*/
    BD_2K4 = 0000013, /*!< 2400 bauds*/
    BD_4K8 = 0000014, /*!< 4800 bauds*/
    BD_9K6 = 0000015, /*!< 9600 bauds STANDARD VALUE !*/
    BD_19K2 = 0000016, /*!< 19200 bauds STANDARD VALUE !*/
    BD_38K4 = 0000017, /*!< 38400 bauds STANDARD VALUE !*/
    BD_57K6 = 0010001, /*!< 57600 bauds STANDARD VALUE !*/
    BD_115K2 = 0010002, /*!< 115200 bauds STANDARD VALUE !*/
    BD_230K4 = 0010003, /*!< 230400 bauds*/
    BD_460K8 = 0010004, /*!< 460800 bauds*/
    BD_500K0 = 0010005, /*!< 500000 bauds*/
    BD_576K = 0010006, /*!< 576000 bauds*/
    BD_921K6 = 0010007, /*!< 921600 bauds STANDARD VALUE !*/
    BD_1M = 0010010, /*!< 1000000 bauds*/
    BD_1M152 = 0010011, /*!< 1152000 bauds*/
    BD_1M5 = 0010012, /*!< 1500000 bauds*/
    BD_2M = 0010013, /*!< 2000000 bauds*/
    BD_2M5 = 0010014, /*!< 2500000 bauds*/
    BD_3M = 0010015, /*!< 3000000 bauds*/
    BD_3M5 = 0010016, /*!< 3500000 bauds*/
    BD_4M = 0010017, /*!< 4000000 bauds*/
};

constexpr int MAX_WAIT_DELAY_DS =
    5; /*!< Up to 500ms without receiving any bytes trigger an exception*/
constexpr int MIN_RECV_BYTES = 0; /*!< Each read call shall return at least 0 bytes*/

/*! Define USB to uart interface settings */
enum class CY7C65213
{
    MAX_BAUD = 3'000'000, /*!< Maximal baud rate for this chip*/
    MAX_FIFO = 256, /*!< Max number of bytes sent before overflow*/
    HW_CONTROL = 1, /*!< Does this chip is capable of hardware control*/
};

/*! Define a custom struct to be used within the UART driver*/
struct UART_Bus
{
    int UART_File; /*!< UART file descriptor*/
    char UART_Filename[30]; /*!< UART file name*/
    int UART_Bus; /*!< UART Bus number*/
    struct termios TTY; /*!< Linux driver struct that store settings for this bus.*/
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
UART_Bus* UART_GetInfos(const int Bus);

/**
 * @brief Close an existing UART device
 *
 * @param UART An UART object to be deleted.
 *
 * @return  0 : OK
 */
int UART_Close(UART_Bus* UART);

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
 * @return -1 : IOCTL error.
 */
int UART_Configure(UART_Bus* UART,
                   const UART_PARITY ParityBit,
                   const UART_STOP StopBit,
                   const UART_DATA_WIDTH BitNumber,
                   const UART_CTRL FLowControl,
                   const UART_BAUD BaudRate);

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
template <typename T>
int UART_Write(UART_Bus* UART, T* const TX, const int Len)
{
    // Allocate a unsigned long long buffer to store the data to be written.
    char* TX_buf = (char*)malloc(sizeof(char) * Len);
    if(TX_buf == 0)
    {
        std::cerr << "[ UART ][ Write ] : Could not allocate the input buffer : " << strerror(errno)
                  << std::endl;
        return -1;
    }

    // Let's copy all of the input data to the new one !
    for(int i = 0; i < Len; i++)
        TX_buf[i] = (char)TX[i];

    // Write to file !
    write(UART->UART_File, TX_buf, Len);

    free(TX_buf);
    return 0;
}

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
template <typename T>
int UART_Read(UART_Bus* UART, T* const RX, const int Len)
{
    // Allocate a unsigned long long buffer to the data to be rode.
    char* RX_buf = (char*)malloc(sizeof(char) * Len);
    if(RX == 0)
    {
        std::cerr << "[ UART ][ Read ] : Could not allocate the output buffer : " << strerror(errno)
                  << std::endl;
        return -1;
    }
    memset(RX_buf, 0x00, Len * sizeof(char));

    int num_bytes = read(UART->UART_File, RX_buf, Len);

    if(num_bytes < 0)
    {
        std::cerr << "[ UART ][ Read ] : Failed to read the RX line : " << strerror(errno)
                  << std::endl;
        return -2;
    }

    // Copy the output data
    for(int i = 0; i < Len; i++)
        RX[i] = (T)RX_buf[i];

    free(RX_buf);
    return 0;
}

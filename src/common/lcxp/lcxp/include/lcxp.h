/**
 * @file    lcxp.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Base file for the LCxP parser. Useless by default.
 * @version 0.1
 * @date    2026-02-10
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

/* *******************************************************************
 * INCLUDE
 * *******************************************************************/
// STD
#include <cstdint>

namespace lcxp
{

    /* *******************************************************************
     * CONSTANTS
     * *******************************************************************/
    // PARSER OPTIONS
    constexpr int MAX_PARSER_CALLBACKS = 24;

    // Buffer sizes
    constexpr int MAX_BUFFER_SIZE = 256;  // Max buffer size to be parsed.
    constexpr int MAX_PAYLOAD_SIZE = 250; // Max payload size to be parsed by the dedicated commands.

    /* *******************************************************************
     * STRUCTS
     * *******************************************************************/
    /**
     *  Define the struct passed to the custom parser.
     *  This struct contain two elements :
     *      - the buffer of the payload.
     *      - a void pointer to the output struct of the parser, since it's type and memory layout is unknown.
     */
    struct LCxP_parser_struct
    {
        uint8_t buffer[MAX_PAYLOAD_SIZE];
        uint8_t sender_id;
        void *output_struct;
    };

    /**
     *  Define the struct used to store callback data.
     *  Contain two elements :
     *      - the opcode to which this callback is tied.
     *      - a function pointer, to call when needed.
     */
    struct parser_callback
    {
        uint8_t opcode;
        uint32_t (*parser)(struct LCxP_parser_struct *arg);
    };

    /* *******************************************************************
     * CLASS
     * *******************************************************************/

    class LCxP
    {

    public:
        // CONSTRUCTORS AND DESTRUCTORS
        /**
         * @brief   Construct a new LCxP object.
         *          Accept two types of input data : Nothing (bytes will be added after), or a full received buffer ()
         *
         */
        LCxP();
        LCxP(uint8_t buffer[MAX_BUFFER_SIZE], uint32_t size);

        /**
         * @brief Destroy the LCxp object
         *
         */
        ~LCxP();

        // COMMAND REGISTERING :
        /**
         * @brief                   Register a new parser on the class (There must be less than MAX_PARSER_CALLBACKS registered callbacks).
         *                          This function will be called when the matching opcode will be found.
         *
         * @param[in] opcode        The opcode that shall trigger the callback.
         * @param[in] parser        A function pointer to a uint32_t func(struct *LCxP_parser_struct) to be able to parse the payload.
         *
         * @return uint32_t
         * @retval 0    The parser successfully added the callback to it's internal table.
         * @retval 1    There was already too much callbacks known.
         * @retval 2    There was already a callback registered for this opcode.
         */
        uint32_t register_command(uint8_t opcode, uint32_t (*parser)(struct LCxP_parser_struct *arg));

        /**
         * @brief                   Remove a previously used callback from the internal list.
         *
         * @param[in] opcode        The target opcode.
         *
         * @return uint32_t
         * @retval 0    The command was removed from the internal database.
         * @retval 1    The command was unknown from the internal database. Could not remove it.
         */
        uint32_t remove_command(uint8_t opcode);

        // BUFFER
        /**
         * @brief                   Clear all of the buffer used internally. Can be called after a transmission error where bytes may be invalid.
         *                          Automatically called after the end of the parsing of a command.
         *
         * @return uint32_t
         * @retval 0    Always zero.
         */
        uint32_t clear_buffers();

        /**
         * @brief                   Append a byte to the internal buffer for parsing.
         *
         * @param[in] byte          The byte to the added to the buffer.
         *
         * @return uint32_t
         * @retval 0                The byte was added to the buffer.
         * @retval 1                The buffer was full. Could not add the byte.
         */
        uint32_t add_byte(uint8_t byte);

        /**
         * @brief                   Append more than one byte to the internal buffer for parsing.
         *
         * @param[in] byte          A pointer to a uint8_t array of bytes to be added.
         * @param[in] number        The number of bytes to be copied.
         *
         * @return uint32_t
         * @retval 0                The byte was added to the buffer.
         * @retval 1                The buffer was full. Could not add the byte.
         * @retval 2                At least one byte could not be added. The first one where added.
         */
        uint32_t add_Nbyte(uint8_t *byte, uint8_t number);

        // PARSER
        /**
         * @brief                   Start the parsing of the buffer.
         *                          Since the callbacks are called, we can easily imagine acting, directly within the parser context,
         *                          saving some code complexity and memory.
         *
         *                          Automatically clear itself in case of successfull parsing.
         *                          Make sure to save the important data before leaving your function !
         *
         * @return uint32_t
         * @retval 0                The parsing was correctly done.
         * @retval 1                Invalid frame alignement structure.
         * @retval 2                Invalid checksum of the package.
         */
        uint32_t parse_buffer();

    private:
        /*
         * VARIABLES
         */
        // BUFFER
        uint8_t buffer_size;             // The actual buffer size. Used essentially for the byte by byte creation.
        uint8_t buffer[MAX_BUFFER_SIZE]; // The full buffer of data.

        // VARIABLES
        uint8_t registeredCallbacks; // Store the number of registered callbacks.

        // CALLBACKS
        parser_callback callbacks_structs[MAX_PARSER_CALLBACKS]; // Store the callbacks.
        /*
         * FUNCTIONS
         */

        /**
         * @brief                   Get the checksum object, as the following form :
         *                          CHECKSUM = DEV_ID ^ SEQ_ID ^ CMD ^ LEN ^ (SUM(PAYLOAD) & 0xFF)
         *
         * @param[in] dev_id        The sender id in the command.
         * @param[in] seq_id        The sequence id in the command.
         * @param[in] cmd           The opcode in the command.
         * @param[in] len           The total len in the command. Used for both len, and iterative sum of the payload.
         * @param[in] payload       Pointer to the base of the payload.
         *
         * @return uint8_t  The value of the computed checksum.
         */
        uint8_t get_checksum(uint8_t dev_id, uint8_t seq_id, uint8_t cmd, uint8_t len, uint8_t *payload);
    };
}
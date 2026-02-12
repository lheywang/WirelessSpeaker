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
     * ENUMS
     * *******************************************************************/
    enum opcodes
    {
        SYS_PING = 0x00,
        SYS_ACK = 0x01,
        SYS_NACK = 0x02,
        SYS_RESET = 0x03,
        SYS_READY = 0x04,
        SYS_INFO_GET = 0x05,
        SYS_INFO_RET = 0x06,
        SYS_UUID_GET = 0x07,
        SYS_UUID_RET = 0x08
    };

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
     * ********************************************************************/
    /*
     *  Define the struct used to store the results of the parsing, in a 
     *  more convenient way.
     *  Contain all the elements defined in the standard : 
     */
    struct parser_result
    {
        uint8_t dev_id;
        uint8_t seq_id;
        uint8_t cmd;
        uint8_t len;
        uint8_t * payload;
        uint8_t checksum;
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
        virtual ~LCxP();

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
        template <typename T>
        uint32_t register_command(uint8_t opcode, uint32_t (T::*parser)(struct parser_result *arg))
        {
            // Exit rapidly if none are available.
            if (this->registeredCallbacks >= MAX_PARSER_CALLBACKS)
                return 1;

            /*
            * First, seek for the first available structure. There's one since there's at least one slot available.
            */
            uint8_t pos = 0;
            for (int i = 0; i < MAX_PARSER_CALLBACKS; i++)
            {
                if (this->callbacks_structs[i].parser == nullptr)
                {
                    pos = i;
                    break;
                }
            }

            /*
             * Check if the opcode isn't already registered
             */
            for (int i = 0; i < MAX_PARSER_CALLBACKS; i++)
            {
                if (this->callbacks_structs[i].opcode == opcode)
                    return 2;
            }

            /*
            * Fill the structure and return
            */
            this->callbacks_structs[pos].opcode = opcode;
            this->callbacks_structs[pos].parser = reinterpret_cast<MemberHandler>(parser);

            // Increment the registered counter by one.
            this->registeredCallbacks += 1;
            return 0;
        }

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
         * @retval N                N bytes couldn't be added (the last ones ...)
         */
        uint32_t add_Nbyte(uint8_t *byte, uint8_t number);

        // PARSER & BUILDER
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
        uint32_t parse();

        /**
         * @brief                   Build the response buffer, from the filled opcode, and the potentially
         *                          modified result struct.
         * 
         * @return &uint8_t         An handle to the built buffer, ready to be sent over the
         *                          communication medium (UART...). 
         */
        uint8_t * build();

        // DEFAULT HANDLER, COMMON COMMANDS
        /** @defgroup defaults The defaults functions, available for all childs.
         *  @{
         */
        virtual uint32_t sys_ping(struct parser_result *arg);
        virtual uint32_t sys_ack(struct parser_result *arg);
        virtual uint32_t sys_nack(struct parser_result *arg);
        virtual uint32_t sys_reset(struct parser_result *arg);
        virtual uint32_t sys_ready(struct parser_result *arg);
        virtual uint32_t sys_info_get(struct parser_result *arg);
        virtual uint32_t sys_info_ret(struct parser_result *arg);
        virtual uint32_t sys_uuid_get(struct parser_result *arg);
        virtual uint32_t sys_uuid_ret(struct parser_result *arg);
        /** @} */ // end of group1

        /**
         * @brief                   Get the checksum object, as the following form :
         *                          CHECKSUM = DEV_ID ^ SEQ_ID ^ CMD ^ LEN ^ (SUM(PAYLOAD) & 0xFF)
         *
         *
         * @return uint8_t  The value of the computed checksum.
         */
        uint8_t get_checksum();

        // IO Commands
        /**
         * @brief                   Send the internal buffer over the designated bus.
         * 
         * @note                    This function MUST be overidded on the target. Otherwise, the usage 
         *                          of std::cout will *probably* cause issues.
         * 
         * @return                  uint32_t 
         */
        virtual uint32_t send();

        // SETTER AND GETTERS
        uint64_t get_uuid();
        uint64_t get_hwid();
        uint32_t set_uuid(uint64_t uuid);
        uint32_t set_hwid(uint64_t hwid);

    private:
        // TYPEDEFS
        typedef uint32_t (LCxP::*MemberHandler)(parser_result *arg);

        // STRUCTS
        /**
         *  Define the struct used to store callback data.
         *  Contain two elements :
         *      - the opcode to which this callback is tied.
         *      - a function pointer, to call when needed.
         */
        struct parser_callback
        {
            uint8_t opcode;
            MemberHandler parser;
        };

        /*
         * VARIABLES
         */
        // RESULTS
        struct parser_result result;

        // BUFFER
        uint8_t buffer_size;             // The actual buffer size. Used essentially for the byte by byte creation.
        uint8_t buffer[MAX_BUFFER_SIZE]; // The full buffer of data.

        // VARIABLES
        uint8_t registeredCallbacks; // Store the number of registered callbacks.

        // CALLBACKS
        parser_callback callbacks_structs[MAX_PARSER_CALLBACKS]; // Store the callbacks.

        // GLOBAL VARIABLES
        uint64_t uuid;
        uint32_t hwid;

        /*
         * FUNCTIONS
         */
    };
}
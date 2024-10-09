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

/**
 * @struct BasicPDO
 * @brief Define the basic elements of a PDO
 *
 * @param BasicPDO::EnablePPS Do we need to support PPS ?
 * @param BasicPDO::Voltage Defined output voltage. Must be correct for all of the subcircuits.
 * @param BasicPDO::Current Defined current output. Less current means less power.
 */
struct BasicPDO
{
    bool EnablePPS;

    float Voltage;
    float Current;
};
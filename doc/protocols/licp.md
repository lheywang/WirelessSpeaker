# LACP - Lightweight Audio Control Protocol (v1.1)

**Version:** 1.1  
**Date:** Feburary 1, 2026  
**Status:** Draft / Specification  
**Architecture:** Host (FPGA/NIOS V) <-> Interface controllers (STM32)

---

## 1. Overview
LICP is a deterministic, packet-based serial protocol designed for communication between a central Audio Host (FPGA) and various "Satellite" Input Modules (Wi-Fi, BLE, USB). It prioritizes zero-allocation parsing and fixed structures for easy DMA implementation.

This one is based on the more general lxcp base, which define the common functions.

### 1.1 Physical Layer
* **Transport:** UART (8N1).
* **Baud Rate:** 115200 (Default), 921600 (Recommended for high-traffic metadata).
* **Endianness:** **Little Endian** (LSB first) for all multi-byte values.

---

## 2. Packet Structure
Every packet follows a fixed 5-byte header format followed by variable payload and a checksum.

| Offset   | Field       | Type   | Description                                                      |
| :------- | :---------- | :----- | :--------------------------------------------------------------- |
| **0**    | **SYNC**    | `u8`   | Constant **`0xAA`**. Frame alignment.                            |
| **1**    | **DEV_ID**  | `u8`   | Logical ID of the sender (See Section 2.1).                      |
| **2**    | **SEQ_ID**  | `u8`   | Rolling counter (0-255). Used to match Requests/Responses.       |
| **3**    | **CMD**     | `u8`   | Operation Code (OpCode).                                         |
| **4**    | **LEN**     | `u8`   | Length of the **PAYLOAD** (0 to 255).                            |
| **5...** | **PAYLOAD** | `u8[]` | Data bytes.                                                      |
| **End**  | **CSUM**    | `u8`   | Checksum: `(DEV_ID + SEQ_ID + CMD + LEN + SUM(PAYLOAD)) & 0xFF`. |

### 2.1 Device Identifiers (`DEV_ID`)
Allows the Host to run a generic parser while knowing the context of the data.
* `0xAA`: **HOST** (The FPGA/NIOS V)
* `0xAB`: **SAT_TOP** (Main interface)

---

## 3. Command Set

### 3.1 System Management (0x00 - 0x0F)
*Hardware identification and life-signs.*

| CMD      | Mnemonic       | Payload        | Dir  | Description                                        |
| :------- | :------------- | :------------- | :--- | :------------------------------------------------- |
| **0x00** | `SYS_PING`     | None           | H⇄S  | Alive check. Response required.                    |
| **0x01** | `SYS_ACK`      | None           | H⇄S  | Success. `SEQ_ID` must match the original request. |
| **0x02** | `SYS_NACK`     | `[ERR_CODE]`   | H⇄S  | Failure. Payload indicates error type.             |
| **0x03** | `SYS_RESET`    | None           | H→S  | Force software reset of the Satellite.             |
| **0x04** | `SYS_READY`    | `[FW_VER]`     | S→H  | Sent on boot. Payload: Firmware version (u8).      |
| **0x05** | `SYS_INFO_GET` | None           | H→S  | Request Hardware details.                          |
| **0x06** | `SYS_INFO_RET` | `[TYPE_STR]`   | S→H  | Response. ASCII String (e.g., "Top:Rev3").         |
| **0x07** | `SYS_UUID_RET` | `[UUID_BYTES]` | S→H  | Response. Unique Hardware Serial/MAC.              |

### 3.2 User outputs Configuration (0x10 - 0x1F)
*Leds controls*

| CMD      | Mnemonic   | Payload Spec                                                                     | Dir  | Description                       |
| :------- | :--------- | :------------------------------------------------------------------------------- | :--- | :-------------------------------- |
| **0x10** | `LEDS_SET` | `[PWM_VALUE_6][PWM_VALUE_5][PWM_VALUE_4][PWM_VALUE_3][PWM_VALUE_2][PWM_VALUE_1]` | H→S  | Set pwm duty cycles for each leds |

### 3.3 User inputs Configuration (0x20 - 0x2F)
*Touch sensing buttons values*

| CMD      | Mnemonic    | Payload     | Dir  | Description                                                        |
| :------- | :---------- | :---------- | :--- | :----------------------------------------------------------------- |
| **0x20** | `BP_GET`    | None        | H→S  | Request the buttons status. Respond with ACK, and then the values. |
| **0x21** | `BP_VALUES` | [MASK]  S→H |      | The buttons pressed mask.                                          |

### 3.4 User screen Configuration (0x30 - 0x4F)
*Screen update*

| CMD      | Mnemonic      | Payload                         | Dir  | Description                                                             |
| :------- | :------------ | :------------------------------ | :--- | :---------------------------------------------------------------------- |
| **0x30** | `SCREEN_INIT` | None                            | H→S  | Initialize the screen, and blank it.                                    |
| **0x31** | `SCREEN_SHOW` | `[ELEM_ID]`                     | H→S  | The name of the icon to be shown. See 4.1 for more details              |
| **0x32** | `SCREEN_VOL`  | `[VOLUME]`                      | H→S  | Show the actual speaker volume                                          |
| **0x33** | `SCREEN_PWR`  | `[ELEM_ID][MAX_WATT][ACT_WATT]` | H→S  | Show the actual speaker power source, and the actual and maximal power. |

### 3.5 Requests (0xF0 - 0xFF)

| CMD      | Mnemonic     | Payload | Dir  | Description                                                              |
| :------- | :----------- | :------ | :--- | :----------------------------------------------------------------------- |
| **0xF0** | `BP_TOUCHED` | None    | S→H  | Inform the master that a button has been touched. ACK is optionnal here. |
---

## 4. Payload Definitions

### 4.1 Screen show (`SCREEN_SHOW` - 0x31)
Fixed one byte payload, to show some elements

| Value    | Mnemonic  | Notes                                 |
| :------- | :-------- | :------------------------------------ |
| **0x01** | `BT`      | Bluetooth audio source is choosen.    |
| **0x02** | `USB`     | USB audio source is choosen.          |
| **0x03** | `NETWORK` | WiFi or RJ45 audio source is choosen. |
| **0x04** | `SPDIF`   | SPDIF audio source is choosen.        |
| **0x05** | `HDMI`    | HDMI audio source is choosen.         |

### 4.2 Screen power (`SCREEN_PWR` - 0x33)
Fixed one byte payload, to show some elements

| Value    | Mnemonic | Notes                          |
| :------- | :------- | :----------------------------- |
| **0x01** | `DC`     | Speaker is using the DC power. |
| **0x02** | `USB`    | Speaker is using USB-PD power. |
| **0x03** | `PoE`    | Speaker is using PoE power.    |

### 4.2 Error Codes (for `SYS_NACK`)
* `0x01`: Invalid Checksum.
* `0x02`: Unknown Command.
* `0x03`: Invalid Payload Length.
* `0x04`: Busy / Not Ready.


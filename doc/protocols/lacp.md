# LACP - Lightweight Audio Control Protocol (v1.1)

**Version:** 1.1  
**Date:** January 30, 2026  
**Status:** Draft / Specification  
**Architecture:** Host (FPGA/NIOS V) <-> Satellites (ESP32/STM32)

---

## 1. Overview
LACP is a deterministic, packet-based serial protocol designed for communication between a central Audio Host (FPGA) and various "Satellite" Input Modules (Wi-Fi, BLE, USB). It prioritizes zero-allocation parsing and fixed structures for easy DMA implementation.

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
| **0**    | **SYNC**    | `u8`   | Constant **`0x55`**. Frame alignment.                            |
| **1**    | **DEV_ID**  | `u8`   | Logical ID of the sender (See Section 2.1).                      |
| **2**    | **SEQ_ID**  | `u8`   | Rolling counter (0-255). Used to match Requests/Responses.       |
| **3**    | **CMD**     | `u8`   | Operation Code (OpCode).                                         |
| **4**    | **LEN**     | `u8`   | Length of the **PAYLOAD** (0 to 250).                            |
| **5...** | **PAYLOAD** | `u8[]` | Data bytes.                                                      |
| **End**  | **CSUM**    | `u8`   | Checksum: `(DEV_ID + SEQ_ID + CMD + LEN + SUM(PAYLOAD)) & 0xFF`. |

### 2.1 Device Identifiers (`DEV_ID`)
Allows the Host to run a generic parser while knowing the context of the data.
* `0x1A`: **HOST** (The FPGA/NIOS V)
* `0x2A`: **SAT_WIFI** (Wi-Fi 5/6 Module)
* `0x3A`: **SAT_BLE** (Bluetooth LE Module)
* `0x4A`: **SAT_USB** (USB/SPDIF Module)
* `0x5A`: **SAT_HDMI** (HDMI Bridge)

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
| **0x06** | `SYS_INFO_RET` | `[TYPE_STR]`   | S→H  | Response. ASCII String (e.g., "ESP32-C5:Rev3").    |
| **0x07** | `SYS_UUID_GET` | None           | H→S  | Request unique Hardware Serial/MAC.                |
| **0x08** | `SYS_UUID_RET` | `[UUID_BYTES]` | S→H  | Response. Unique Hardware Serial/MAC.              |

### 3.2 Audio Configuration (0x10 - 0x1F)
*Clocking and stream flow control.*

| CMD      | Mnemonic       | Payload Spec            | Dir  | Description                                              |
| :------- | :------------- | :---------------------- | :--- | :------------------------------------------------------- |
| **0x10** | `AUD_FMT`      | `[RATE:4][BIT:1][CH:1]` | S→H  | Notify format change. Host MUST Ack before audio starts. |
| **0x11** | `AUD_MUTE`     | `[STATE]`               | H→S  | `0x01`=Mute (Send 0s or Stop I2S), `0x00`=Unmute.        |
| **0x12** | `AUD_SRC_TYPE` | `[SRC_ID]`              | S→H  | Report active internal source (e.g., DLNA vs AirPlay).   |

### 3.3 Transport Control (0x20 - 0x2F)
*Playback manipulation.*

| CMD      | Mnemonic   | Payload | Dir  | Description                                      |
| :------- | :--------- | :------ | :--- | :----------------------------------------------- |
| **0x20** | `TR_STOP`  | None    | H→S  | Stop stream, clear buffers, release audio locks. |
| **0x21** | `TR_PLAY`  | None    | H→S  | Start or Resume stream.                          |
| **0x22** | `TR_PAUSE` | None    | H→S  | Pause stream (maintain buffer).                  |
| **0x23** | `TR_NEXT`  | None    | H→S  | Skip to next track.                              |
| **0x24** | `TR_PREV`  | None    | H→S  | Skip to previous track.                          |

### 3.4 Metadata (0x30 - 0x4F)
*UI updates.*

| CMD      | Mnemonic      | Payload          | Dir  | Description                                           |
| :------- | :------------ | :--------------- | :--- | :---------------------------------------------------- |
| **0x30** | `META_STATE`  | `[STATE_ID]`     | S→H  | `00`=Idle, `01`=Buffering, `02`=Playing, `03`=Paused. |
| **0x31** | `META_TITLE`  | `[String...]`    | S→H  | UTF-8 String (Track Name).                            |
| **0x32** | `META_ARTIST` | `[String...]`    | S→H  | UTF-8 String (Artist).                                |
| **0x33** | `META_ALBUM`  | `[String...]`    | S→H  | UTF-8 String (Album).                                 |
| **0x34** | `META_TIME`   | `[CUR:2][TOT:2]` | S→H  | Current/Total time in seconds (u16).                  |

---

## 4. Payload Definitions

### 4.1 Audio Format (`AUD_FMT` - 0x10)
Fixed 6-byte payload.

| Offset | Field           | Type  | Notes                                                   |
| :----- | :-------------- | :---- | :------------------------------------------------------ |
| 0-3    | **Sample Rate** | `u32` | Little Endian (e.g., `44100` -> `0x44 0xAC 0x00 0x00`). |
| 4      | **Bit Depth**   | `u8`  | `16`, `24`, or `32`.                                    |
| 5      | **Channels**    | `u8`  | `1` (Mono), `2` (Stereo), `6` (5.1).                    |

### 4.2 Error Codes (for `SYS_NACK`)
* `0x01`: Invalid Checksum.
* `0x02`: Unknown Command.
* `0x03`: Invalid Payload Length.
* `0x04`: Busy / Not Ready.
* `0x05`: Hardware Fault (I2S Init Failed).

---

## 5. Workflows

### 5.1 Host Requests Hardware Info
Identifying who is connected to the bus.

1.  **HOST** sends: `[SYNC][HOST][SEQ=10][SYS_INFO_GET][LEN=0][CSUM]`
2.  **SAT** receives. Checks CSUM. Matches `SEQ=10`.
3.  **SAT** sends: `[SYNC][SAT_WIFI][SEQ=10][SYS_INFO_RET][LEN=13]["ESP32-C6:Rev1"][CSUM]`

### 5.2 Muting the Audio Source
The user presses mute on the FPGA; the Satellite must stop sending I2S data to save power/bandwidth.

1.  **HOST** sends: `[SYNC][HOST][SEQ=55][AUD_MUTE][LEN=1][0x01][CSUM]`
2.  **SAT** receives. Immediately disables I2S DMA or outputs zero-samples.
3.  **SAT** sends: `[SYNC][SAT_USB][SEQ=55][SYS_ACK][LEN=0][CSUM]`

### 5.3 Handling Mis-responses (Sequence ID Check)
Ensuring the Host doesn't process an old ACK for a new command.

1.  **HOST** sends `TR_NEXT` with `SEQ=20`.
2.  ... timeout ... (Satellite took too long).
3.  **HOST** sends `TR_PLAY` with `SEQ=21`.
4.  **SAT** finally replies to the first command (`SEQ=20`).
5.  **HOST** reads header `SEQ=20`.
6.  **HOST** logic: "I am expecting Ack for 21. Received 20. Drop packet."
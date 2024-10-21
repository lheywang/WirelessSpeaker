# Generator config default files !
import tomllib
import argparse
import datetime

if __name__ == "__main__":
    # Create the buffer
    buf = bytearray(128)

    default_val = 0xFF

    # Parse arguments !
    parser = argparse.ArgumentParser(
        prog="Header-Generator",
        description="Dump a toml file into a binary header file ready to be compiled into the executable",
    )
    parser.add_argument("filename")
    parser.add_argument("output")
    args = parser.parse_args()

    data = None
    with open(args.filename, "rb") as f:
        data = tomllib.load(f)

    # Here, I copy manually the data to ensure a consistence between the spec and the outputed file.

    # 1 Byte of padding
    buf[0x00] = default_val

    # Header Versions
    buf[0x01] = data["Versions"]["HeaderVersion"][0]
    buf[0x02] = data["Versions"]["HeaderVersion"][1]
    buf[0x03] = data["Versions"]["HeaderVersion"][2]

    # Timestamp of write, to 01/01/1970
    buf[0x04] = 19
    buf[0x05] = 70
    buf[0x06] = 1
    buf[0x07] = 1
    buf[0x08] = 00
    buf[0x09] = 00
    buf[0x0A] = 1

    # Hardware Versions
    buf[0x0B] = data["Versions"]["HardwareVersion"][0]
    buf[0x0C] = data["Versions"]["HardwareVersion"][1]

    # BOM Versions
    buf[0x0D] = data["Versions"]["BOMVersion"][0]
    buf[0x0E] = data["Versions"]["BOMVersion"][1]

    # Serial Number
    base = int(0x0F)
    for index, char in enumerate(data["SN"]["Serial"]):
        buf[base + index] = ord(char)

    # Padding
    base = 0x17
    for index in range(base, base + 0x08, 1):
        buf[index] = default_val

    # Production date, to 01/01/2025
    buf[0x1F] = 20
    buf[0x20] = 25
    buf[0x21] = 1
    buf[0x22] = 1
    buf[0x23] = 00
    buf[0x24] = 00
    buf[0x25] = 1

    # CRC values. Are set to default val since calculated before any writes.
    buf[0x26] = 0x00
    buf[0x27] = 0x00
    buf[0x28] = 0x00
    buf[0x29] = 0x00

    # Padding
    base = 0x2A
    for index in range(base, base + 0x08, 1):
        buf[index] = default_val

    # Number of DSP Profiles
    buf[0x32] = 0x00

    # Padding
    base = 0x33
    for index in range(base, base + 0x0D, 1):
        buf[index] = default_val

    buf[0x40] = 0x01
    buf[0x41] = 0xC0

    base = 0x42
    for index in range(base, len(buf), 1):
        buf[index] = 0x00

    with open(args.output, "wb") as f:
        f.write(buf)

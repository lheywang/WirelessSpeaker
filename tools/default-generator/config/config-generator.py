# Generator config default files !
import tomllib
import argparse

if __name__ == "__main__":
    buf = bytearray(256)

    default_val = 0xFF

    # Parse arguments !
    parser = argparse.ArgumentParser(
        prog="Config-Generator",
        description="Dump a toml file into a binary eeprom (config default) file ready to be compiled into the executable",
    )
    parser.add_argument("filename")
    parser.add_argument("output")
    args = parser.parse_args()

    data = None
    with open(args.filename, "rb") as f:
        data = tomllib.load(f)

    # Here, I copy manually the data to ensure a consistence between the spec and the outputed file.

    # EQ Config
    buf[0x00] = data["EQ"]["Bass"]
    buf[0x01] = data["EQ"]["MediumR"]
    buf[0x02] = data["EQ"]["MediumL"]
    buf[0x03] = data["EQ"]["HighR"]
    buf[0x04] = data["EQ"]["HighL"]
    buf[0x05] = data["EQ"]["LPValL"]
    buf[0x06] = data["EQ"]["LPValR"]
    buf[0x07] = data["EQ"]["HPValL"]
    buf[0x08] = data["EQ"]["HPValR"]
    buf[0x09] = data["EQ"]["RL"]

    # DAC
    buf[0x0A] = data["DAC"]["MuteDelay"]
    buf[0x0B] = data["DAC"]["Volume"]
    buf[0x0C] = data["DAC"]["VolumeL"]
    buf[0x0D] = data["DAC"]["VolumeR"]
    buf[0x0E] = data["DAC"]["DataL"]
    buf[0x0F] = data["DAC"]["DataR"]
    buf[0x10] = data["DAC"]["AnalogAttenL"]
    buf[0x11] = data["DAC"]["AnalogAttenR"]

    # 1 byte padding here !
    buf[0x12] = default_val

    # AMP
    buf[0x13] = data["AMP"]["PLBas"]
    buf[0x14] = data["AMP"]["PLLeft"]
    buf[0x15] = data["AMP"]["PLLRight"]

    # LEDS
    buf[0x16] = data["LEDS"]["BrightnessTOP"]
    buf[0x17] = data["LEDS"]["BrightnessMAXTOP"]
    buf[0x18] = data["LEDS"]["BrightnessBACK1"]
    buf[0x19] = data["LEDS"]["BrightnessMAXBACK1"]
    buf[0x2A] = data["LEDS"]["BrightnessBACK2"]
    buf[0x1B] = data["LEDS"]["BrightnessMAXBACK2"]
    buf[0x1C] = data["LEDS"]["BrightnessBACK3"]
    buf[0x1D] = data["LEDS"]["BrightnessMAXBACK3"]

    # TOUCH
    buf[0x1E] = data["TOUCH_SENSOR"]["Threshold"]
    buf[0x1F] = data["TOUCH_SENSOR"]["Sensivity"]

    # PDO
    buf[0x20] = data["PDO"]["Profile1Volt"][0]
    buf[0x21] = data["PDO"]["Profile1Volt"][1]
    buf[0x22] = data["PDO"]["Profile1Curr"][0]
    buf[0x23] = data["PDO"]["Profile1Curr"][1]
    buf[0x24] = data["PDO"]["Profile1PPS"]
    buf[0x25] = data["PDO"]["Profile2Volt"][0]
    buf[0x26] = data["PDO"]["Profile2Volt"][1]
    buf[0x27] = data["PDO"]["Profile2Curr"][0]
    buf[0x28] = data["PDO"]["Profile2Curr"][1]
    buf[0x29] = data["PDO"]["Profile2PPS"]

    # 22 bytes of padding
    base = 0x2A
    for index in range(base, base + 0x16, 1):
        buf[index] = default_val

    base = 0x40
    for index, Char in enumerate(data["NAME"]["Name"]):
        addr = base + (index * 2)
        char = Char.encode("utf-16")
        buf[addr] = char[3]
        buf[addr + 1] = char[2]

    buf[0x80] = 0x00  # Ensure end of string detection !
    for index in range(0x81, len(buf), 1):
        buf[index] = default_val

    with open(args.output, "wb") as f:
        f.write(buf)

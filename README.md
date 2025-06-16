# WirelessSpeaker
This project is intended to build a Wireless speaker based on a RaspberryPi Zero 2W board, with a custom PCB behind it. The goal is to produce a complete software stackup, capable 
of streaming audio over : - Bluetooth - WiFi (UPNP) - USB (only work for slave enabled board as the RPI Zero. Does not work on the RPi classic boards)

## Disclaimer
In this repo, I used some lib's developped by others. They're under */includes/ folder. You may find a Link to their source repo as well as their License. All of the edit are 
specified on a EDIT file near the library. This is done for you to be able to precisely determine which where the point that was modified on the original source code.

## PCB :
The PCB is responsible for all of the electricals interractions, such as : - RPi to the DAC (PCM5252) - DAC to filters (split every channels and provide simple equalizer) - filters 
to amplifiers (TPA3128D2) - Overall management of temperature, and defaults - Power supplies (based on USB-C PD3 protocol)

## Serial protocols
The project is based on a lot of serial buses to manage everything ! This include : - I2S for the audio - I2C for all management IC - SPI for EEPROM (not the HAT one !) - UART for 
USB communication over with the battery

**Notes** PCB is provided in a separated folder as it is, and isn't garanteed to be fully verified.

## Licenses
This project is subject to two licenses : - GPL v3.0 for ALL of the software (source, binaries...) - CERN OHL for ALL of the hardware (schematic, layout, gerber...)

## Supporting me ?
If you found the project interessting / usefull, please consider supporting me ! This can be done in multiple ways :

- Star the project on github, to make it visible - Share to your friends / communities, to make this project a bit more known - Supporing the developpement team by donating money on 
the following link : [Paypal](https://paypal.me/heywangleonard?country.x=FR&locale.x=fr_FR).

Any of theses actions is purely based on voluntarism, and will be warmly thank !

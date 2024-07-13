# WirelessSpeaker
This project is intended to build a Wireless speaker based on a RaspberryPi Zero 2W board, with a custom PCB behind it.
The goal is to produce a complete software stackup, capable of streaming audio over : 
- Bluetooth
- WiFi (UPNP)
- USB (only work for slave enabled board as the RPI Zero. Does not work on the RPi classic boards)

## PCB : 
The PCB is responsible for all of the electricals interractions, such as : 
- RPi to the DAC (PCM5252)
- DAC to filters (split every channels)
- filters to amplifiers (TPA3128D2)
- Overall management of temperature, and defaults
- Power supplies (based on USB-C PD3 protocol)

## Software architecture

## How to install ?
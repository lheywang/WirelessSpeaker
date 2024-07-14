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
## Tools
If you want only to build to system, run this command : 
> sudo apt(-get) install g++-aarch64-linux-gnu

***WARNING** Sometimes, install may be broken. Be sure that everything as suceeded to be zorking as intended.*

**Notes** : 
*If somes want's to add support to another Pi, you're welcome !*

## How to build and / or deploy : 
The makefile define differents steps where you can interract : 
- clean : Clean all files
- all : Compile only the files.
- arm_debug : Compile an image with lower level of optimization and debug codes. Warning are used to inform the developper of all points.
- install : Compile if not already done and try to copy the output on the root of the raspberrypi.home home folder (pi user)
- run : Install and then attempt an ssh log to launch the code.

**Notes**
- The last two steps may need login or configuration of the RPi on SSH.
- You can run any of the commands, if the prerequites aren't met they will be generated.


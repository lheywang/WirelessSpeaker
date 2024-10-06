# WirelessSpeaker
This project is intended to build a Wireless speaker based on a RaspberryPi Zero 2W board, with a custom PCB behind it.
The goal is to produce a complete software stackup, capable of streaming audio over : 
- Bluetooth
- WiFi (UPNP)
- USB (only work for slave enabled board as the RPI Zero. Does not work on the RPi classic boards)

## PCB : 
The PCB is responsible for all of the electricals interractions, such as : 
- RPi to the DAC (PCM5252)
- DAC to filters (split every channels and provide simple equalizer)
- filters to amplifiers (TPA3128D2)
- Overall management of temperature, and defaults
- Power supplies (based on USB-C PD3 protocol)

## Serial protocols
The project is based on a lot of serial buses to manage everything !
This include : 
- I2S for the audio
- I2C for all management IC
- SPI for EEPROM (not the HAT one !)
- UART for USB communication over with the battery

**Notes**
PCB is provided in a separated folder as it is, and isn't garanteed to be fully verified.

## How to ?
### How to install ?
#### Configuration of the Pi
You will need a Rpi, and, naturally the whole PCB for the project.

#### SSH Config
Since all compilation and generation steps are done on a computer, to save you some time, we extensively use SSH / SCP to copy files and commands.
Every access will require you the password, and that's boring.
Against that, we recommend using a public / private key pair !

To generate it, use : 
> ssh-keygen (on your root folder)
> ssh-copy-id -i [YOUR KEY].pub USER@DESTINATION
And that's done !

#### Deploying the software
To deploy the software, two steps are needed ! We've developped sh scripts files that does everything for you !
First, install all of the tools :
> cd scripts 
> open and edit the RPi IP and key in top of all of the scripts.
> sh install.sh
>**NOTES** : There is an install-dev.sh, which is intended for developpers. Contains several GB of tools that aren't required to build the software.
> sh deploy.sh

AND... That's all ! The script as managed everything for you !

### For more advanced users !
### Makefiles recipes, for more advanced users : 
The project is based on a mix of makefiles, CmakeLists.txt and other builds tools.
A main Makefile is available for you, and exports : 
- clean : Remove artifacts of build
- clean_all : Remove all files related to builds (incl. Cmakes caches)
- all : Build the executable 
- doc : Build the pdf + html documentation.

**Notes** : 
*If somes want's to add support to another Pi, you're welcome !*

## Global architecture
On the project, the software is designed in the following way : 

📦data : Store all of the data used by some tools (doxygen !)
📦scripts : Installation scripts !
 ┣ 📜deploy.sh
 ┣ 📜install-dev.sh
 ┣ 📜install.sh
 ┗ 📜update.sh
 📦src
 ┣ 📂Drivers All of the drivers (incl. Devices and buses)
 ┃ ┣ 📂Devices : All of the devices drivers.
 ┃ ┣ 📂GPIO : GPIO Driver
 ┃ ┃ ┣ 📜GPIO.hpp
 ┃ ┃ ┣ 📜GPIO_Engine.cpp
 ┃ ┃ ┗ 📜GPIO_Engine.hpp
 ┃ ┣ 📂I2C : I2C Driver
 ┃ ┃ ┣ 📂includes
 ┃ ┃ ┃ ┣ 📜smbus.cpp
 ┃ ┃ ┃ ┗ 📜smbus.h
 ┃ ┃ ┣ 📜I2C.hpp
 ┃ ┃ ┣ 📜I2C_Engine.cpp
 ┃ ┃ ┗ 📜I2C_Engine.hpp
 ┃ ┣ 📂SPI : SPI Driver
 ┃ ┃ ┗ 📜SPI.hpp
 ┃ ┗ 📂USB : USB Driver
 ┣ 📂Modules : We define here some higher level interractions with the differents devices. We call from here the drivers. 
 ┃ ┣ 📂UPNP
 ┃ ┣ 📂LEDS
 ┃ ┣ 📂Temperature
 ┃ ┗ 📂UpSampler
 ┣ 📜CMakeLists.txt
 ┗ 📜main.cpp
📦tools
 ┣ 📂device-tree : Device tree compiler and source file 
 ┃ ┣ 📜Makefile
 ┃ ┗ 📜WirelessSpeakerV1.dts
 ┣ 📂utils : Some utils, used to flash the eeprom or apply the dtoverlay !
 ┃ ┣ 📂dtmerge
 ┃ ┣ 📂eeptools
 ┃ ┣ 📂kdtc
 ┃ ┣ 📂otpset
 ┃ ┣ 📂ovmerge
 ┃ ┣ 📂pinctrl
 ┃ ┣ 📂raspinfo
 ┃ ┣ 📂vcgencmd
 ┃ ┣ 📂vclog
 ┃ ┣ 📂vcmailbox
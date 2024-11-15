# WirelessSpeaker
This project is intended to build a Wireless speaker based on a RaspberryPi Zero 2W board, with a custom PCB behind it.
The goal is to produce a complete software stackup, capable of streaming audio over : 
- Bluetooth
- WiFi (UPNP)
- USB (only work for slave enabled board as the RPI Zero. Does not work on the RPi classic boards)

## Disclaimer 
In this repo, I used some lib's developped by others. They're under */includes/ folder. You may find a Link to their source repo as well as their License.
All of the edit are specified on a EDIT file near the library.

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
> ssh-copy-id -i [YOUR KEY].pub USER @ DESTINATION
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

## Supporting me ?
If you found the project interessting / usefull, please consider supporting me !
This can be done in multiple ways :

- Star the project on github, to make it visible
- Share to your friends / communities, to make this project a bit more known
- Supporing the developpement team by donating money on the following link : [Paypal](https://paypal.me/heywangleonard?country.x=FR&locale.x=fr_FR).

Any of theses actions is purely based on voluntarism, and will be warmly thank !

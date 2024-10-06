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

**Notes**
PCB is provided in a separated folder as it is, and isn't garanteed to be fully verified.

## Software architecture

## How to install ?
### Tools
If you want only to build to system, run this command :
> sudo apt(-get) update && upgrade -y 
> sudo apt(-get) install build-essentials libc6-dev make doxygen ssh libi2c-dev device-tree-compiler g++-aarch64-linux-gnu 

And if you're developper, you're going to need theses :
> sudo apt(-get) install texlive-full graphwiz libfdt-dev device-tree gcc 

> **WARNING Sometimes, install may be broken. Be sure that everything as suceeded to be working as intended.**

**Notes** : 
*If somes want's to add support to another Pi, you're welcome !*

### First, configure the Pi
You're going to need a Pi, with an OS installed on it. We recommend RPi OS lite, since graphicals features that wont be used remain out, thus more performance ! 
A basic setup shall be done, this include a Wi-fi connection. The remaining will be done automatically.
-> If you don't have a screen nor keyboard, don't panic ! You can always pre-configure Wi-Fi things by customizing the image using RPi-Imager tool. And for SSH, just add a file named ssh without extension at the root of the SD (on Windows).

**Note** The user shall be configured as Pi, or you will need to edit it on the Makefile.

### SSH Config
Since all compilation and generation steps are done on a computer, to save you some time, we extensively use SSH / SCP to copy files and commands.
Every access will require you the password, and that's boring.
Against that, we recommend using a public / private key pair !

To generate it, use : 
> ssh-keygen (on your root folder)
> ssh-copy-id -i [YOUR KEY].pub USER@DESTINATION
And that's done !

### Deploying the software
Now, it's the big moment to compile all of the code and the EEPROM files, and deploy on the RPi.
First, run 
> make weeprom (to generate the hat.eep file and deploy it on the hat.)
> make autostart (to compile the whole software (may take some time) and deploy it. Now, after each boot the software will be started)

And that's done for you !

## For more advanced users !
### Makefiles recipes, for more advanced users : 
The makefile define differents steps where you can interract : 
- **clean** : Clean all files
- **all** : Compile only the files.
- **install** : Compile if not already done and try to copy the output on the root of the raspberrypi.home home folder (pi user)
- **run** : Install and then attempt an ssh log to launch the code.
- **doc** : Create the HTML and PDF documentations for the project using Doxygen
- **autostart** : Add an crontab request at boot to start the software.
- **eeprom** : Generate the eeprom file.
- **weeprom** : Genererate the eeprom file and write it on the hardware.

> **NOTES**
> You can speed up the build process by using make [recipe] -j [core number]
> You will then compile each file on a core, thus way faster.
> The last step, the linking will be done on a single core.

> **NOTES**
> - The last two steps may need login or configuration of the RPi on SSH.
> - You can run any of the commands, if the prerequites aren't met they will be generated.

> **NOTES**
> For using the ssh / scp functions, a properly configured RasbperryPi need to be present.
> Please refer to their own documentation for theses functionnalities.

> **NOTES**
> For using Doxygen, a proper LaTeX suite shall be installed and configured.
> Required modules : TexLive Full + graphwiz.


**WARNING : This command make the assumption of the presence of a RPi on your network**

Then, if you want you need to create the .sh script that start the software automatically.

If you're developper, to compile the whole documentation run :
> make doc

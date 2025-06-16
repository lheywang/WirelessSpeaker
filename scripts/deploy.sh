#!/usr/bin/env bash

# ===========================================================================================================
# scripts/deploy.sh
# 
# Handle the deployement of the tool to the target device trough SSH.
#
# ===========================================================================================================

# First, load config
set -a ; . ./.config ; set +a

# Running commands...
echo "--------------------------------------------------------------------"
echo "
This tool will :
- Compile the software, and copy it to the home/[user] of the pi
- Create the autostart file
- Add the device tree file to the boot/overlays
- Flash the onboard EEPROM to make the kernal boot
- Enable the I2C0 on your pi"
echo "--------------------------------------------------------------------"

# =============================================================================
# COMPILATION
# =============================================================================

echo "Compiling everything..."
echo "--------------------------------------------------------------------"
cd .. && make all
cd ../tools/device-tree && make dtc_compile
cd ../tools/utils/eeptools && ./eepmake ../../HL-WirelessSpeakerV1.txt ../../WirelessSpeajerV1.eep
echo "--------------------------------------------------------------------"
echo "Compiling done !".
echo "--------------------------------------------------------------------"

# =============================================================================
# MOVING FILES
# =============================================================================

echo "Copying files to the IP..."
echo "--------------------------------------------------------------------"

# Executable
ssh -i ${KEY} pi@${IP} -f "touch /home/pi/${APPNAME}.elf"
scp -i ${KEY} build/${APPNAME} pi@${IP}:/home/pi/${APPNAME}.elf 

# EEPROM hat
ssh -i ${KEY} pi@${IP} -f "touch /home/pi/eeprom.eep"
scp -i ${KEY} ../tools/WirelessSpeaker.eep pi@${IP}:/home/pi/eeprom.eep 

# Device tree
ssh -i ${KEY} pi@${IP} -f "touch /boot/overlays/WirelessSpeaker.dtb"
scp -i ${KEY} ../tools/device-tree/WirelessSpeakerV1.dtbo pi@${IP}:/boot/firmware/overlays/WirelessSpeaker.dtbo

# I2C Flash tool
ssh -i ${KEY} pi@${IP} -f "touch /home/pi/eepflash.sh"
scp -i ${KEY} ../tools/utils/eeptools/eepflash.sh pi@${IP}:/home/pi/eepflash.sh

echo "--------------------------------------------------------------------"
echo "Copying files done !"
echo "--------------------------------------------------------------------"

# =============================================================================
# CONFIGURATION
# =============================================================================

echo "Applying files modifications..."
echo "--------------------------------------------------------------------"
ssh -i ${KEY} pi@${IP} -f "chmod +x /home/pi/${APPNAME}.elf"
ssh -i ${KEY} pi@${IP} -f "dtoverlay /boot/overlays/WirelessSpeaker.dtb"
ssh -i ${KEY} pi@${IP} -f "sudo bash -c 'echo -e '# Enabling I2C0 bus\n$(cat /boot/firmware/config.txt)' > /boot/firmware/config.txt" # Write in the top of the file. Not that great but OK.
ssh -i ${KEY} pi@${IP} -f "sudo bash -c 'echo -e 'dtparam=i2c_vc=on\n$(cat /boot/firmware/config.txt)' > /boot/firmware/config.txt"
ssh -i ${KEY} pi@${IP} -f "sudo bash -c 'echo -e '\n /home/pi/${APPNAME}.elf$(cat /home/pi/.bashrc)' > /home/pi/.bashrc"
echo "--------------------------------------------------------------------"
echo "Finished applying modifications !"
echo "--------------------------------------------------------------------"

# =============================================================================
# FLASHING EEPROM
# =============================================================================

echo "Flashing I2C0 HAT EEPROM..."
echo "--------------------------------------------------------------------"
ssh -i ${KEY} pi@${IP} -f "sudo ./eepflash.sh -w -t=24c32 -a=0x50 -f=eeprom.eep"
echo "--------------------------------------------------------------------"
echo "Finished flashing EEPROM !"
echo "--------------------------------------------------------------------"

# =============================================================================
# REMOVING USELESS FILES !
# =============================================================================

echo "Removng temporary files..."
echo "--------------------------------------------------------------------"
ssh -i ${KEY} pi@${IP} -f "rm -f eepflash.sh eeprom.eep"
rm ../tools/WirelessSpeaker.eep
cd .. && make clean
echo "--------------------------------------------------------------------"
echo "Removed useless files"
echo "--------------------------------------------------------------------"

# =============================================================================
# REBOOTING
# =============================================================================

echo "
Installation done !
The RaspberryPi will now reboot."
echo "--------------------------------------------------------------------"
ssh -i ${KEY} pi@${IP} -f "sudo reboot"
exit
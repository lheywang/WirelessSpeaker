# Define RPi IP or Domain name and location of the RSA key for automated deployment.
# Customize this field depending on your installation !
RPI="192.168.1.7"
# Customize this one with your filepath !
KEY="~/.ssh/id_rsa"

# Reminder : 
# You can generate a SSH using ssh-keygen, then follow the steps
# Then, add it to the RPi using ssh-copy-id -i [YOUR kEY].pub USER@DESTINATION
# Thus, any followwing steps will be authenticated.

EXECNAME="build/WirelessSpeaker.arm"

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

echo "Copying files to the RPi..."
echo "--------------------------------------------------------------------"

# Executable
ssh -i ${KEY} pi@${RPI} -f "touch /home/pi/${EXECNAME}.elf"
scp -i ${KEY} ${EXECNAME} pi@${RPI}:/home/pi/${EXECNAME}.elf 

# EEPROM hat
ssh -i ${KEY} pi@${RPI} -f "touch /home/pi/eeprom.eep"
scp -i ${KEY} ../tools/WirelessSpeaker.eep pi@${RPI}:/home/pi/eeprom.eep 

# Device tree
ssh -i ${KEY} pi@${RPI} -f "touch /boot/overlays/WirelessSpeaker.dtb"
scp -i ${KEY} ../tools/device-tree/WirelessSpeakerV1.dtbo pi@${RPI}:/boot/firmware/overlays/WirelessSpeaker.dtbo

# I2C Flash tool
ssh -i ${KEY} pi@${RPI} -f "touch /home/pi/eepflash.sh"
scp -i ${KEY} ../tools/utils/eeptools/eepflash.sh pi@${RPI}:/home/pi/eepflash.sh

echo "--------------------------------------------------------------------"
echo "Copying files done !"
echo "--------------------------------------------------------------------"

# =============================================================================
# CONFIGURATION
# =============================================================================

echo "Applying files modifications..."
echo "--------------------------------------------------------------------"
ssh -i ${KEY} pi@${RPI} -f "chmod +x /home/pi/${EXECNAME}.elf"
ssh -i ${KEY} pi@${RPI} -f "dtoverlay /boot/overlays/WirelessSpeaker.dtb"
ssh -i ${KEY} pi@${RPI} -f "sudo bash -c 'echo -e '# Enabling I2C0 bus\n$(cat /boot/firmware/config.txt)' > /boot/firmware/config.txt" # Write in the top of the file. Not that great but OK.
ssh -i ${KEY} pi@${RPI} -f "sudo bash -c 'echo -e 'dtparam=i2c_vc=on\n$(cat /boot/firmware/config.txt)' > /boot/firmware/config.txt"
ssh -i ${KEY} pi@${RPI} -f "sudo bash -c 'echo -e '\n /home/pi/${EXECNAME}.elf$(cat /home/pi/.bashrc)' > /home/pi/.bashrc"
echo "--------------------------------------------------------------------"
echo "Finished applying modifications !"
echo "--------------------------------------------------------------------"

# =============================================================================
# FLASHING EEPROM
# =============================================================================

echo "Flashing I2C0 HAT EEPROM..."
echo "--------------------------------------------------------------------"
ssh -i ${KEY} pi@${RPI} -f "sudo ./eepflash.sh -w -t=24c32 -a=0x50 -f=eeprom.eep"
echo "--------------------------------------------------------------------"
echo "Finished flashing EEPROM !"
echo "--------------------------------------------------------------------"

# =============================================================================
# REMOVING USELESS FILES !
# =============================================================================

echo "Removng temporary files..."
echo "--------------------------------------------------------------------"
ssh -i ${KEY} pi@${RPI} -f "rm -f eepflash.sh eeprom.eep"
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
ssh -i ${KEY} pi@${RPI} -f "sudo reboot"
exit
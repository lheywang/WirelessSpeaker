# Define RPi IP or Domain name and location of the RSA key for automated deployment.
# Customize this field depending on your installation !
RPI = 192.168.1.7
# Customize this one with your filepath !
KEY = ~/.ssh/id_rsa

# Reminder : 
# You can generate a SSH using ssh-keygen, then follow the steps
# Then, add it to the RPi using ssh-copy-id -i [YOUR kEY].pub USER@DESTINATION
# Thus, any followwing steps will be authenticated.

EXECNAME := build/WirelessSpeaker.arm

echo "
This tool will :
- Compile the software, and copy it to the home/[user] of the pi
- Create the autostart file
- Add the device tree file to the boot/overlays
- Flash the onboard EEPROM to make the kernal boot
- Enable the I2C0 on your pi"

echo "Compiling everything..."
cd .. && make all
cd ../tools/device-tree && make dtc_compile

echo "Compiling done !"
echo "Copying files to the RPi..."

ssh -i $(KEY) pi@$(RPI) -f "touch /home/pi/$(EXECNAME).elf"
scp -i $(KEY) $(EXECNAME).arm pi@$(RPI):/home/pi/$(EXECNAME).elf 

ssh -i $(KEY) pi@$(RPI) -f "touch /boot/overlays/WirelessSpeaker.dtb"
scp -i $(KEY) ../tools/device-tree/WirelessSpeakerV1.dtb pi@$(RPI):/boot/overlays/WirelessSpeaker.dtb 

echo "Copying files done !"
echo "Applying files modificatios..."

ssh -i $(KEY) pi@$(RPI) -f "chmod +x /home/pi/$(EXECNAME).elf"

# Flash EEPROM
# I2C0
# dtoverlay (to be installed !)
# autostart
# Add check for eepflash !
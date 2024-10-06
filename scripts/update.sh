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

echo "
This tool will :
- Compile the software, and copy it to the home/[user] of the pi"
echo "WARNING : THIS TOOL DOES NOT UPDATE THE DEVICE TREE !"

# =============================================================================
# COMPILATION
# =============================================================================

echo "Compiling everything..."
cd .. && make all
echo "Compiling done !"

# =============================================================================
# MOVING FILES
# =============================================================================

echo "Copying files to the RPi..."

# Executable
ssh -i ${KEY} pi@${RPI} -f "touch /home/pi/${EXECNAME}.elf"
scp -i ${KEY} ${EXECNAME} pi@${RPI}:/home/pi/${EXECNAME}.elf 

echo "Copying files done !"

# =============================================================================
# CONFIGURATION
# =============================================================================

echo "Applying files modifications..."
ssh -i ${KEY} pi@${RPI} -f "chmod +x /home/pi/${EXECNAME}.elf"
echo "Finished applying modifications !"

# =============================================================================
# REBOOTING
# =============================================================================

echo "
Update done !
The RaspberryPi will now reboot."
ssh -i ${KEY} pi@${RPI} -f "sudo reboot"
exit
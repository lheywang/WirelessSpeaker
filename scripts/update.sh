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
echo "--------------------------------------------------------------------"
echo "WARNING : THIS TOOL DOES NOT UPDATE THE DEVICE TREE !"
echo "--------------------------------------------------------------------"

# =============================================================================
# COMPILATION
# =============================================================================

echo "Compiling everything..."
echo "--------------------------------------------------------------------"
cd .. && make all
echo "--------------------------------------------------------------------"
echo "Compiling done !"
echo "--------------------------------------------------------------------"

# =============================================================================
# MOVING FILES
# =============================================================================

echo "Copying files to the RPi..."
echo "--------------------------------------------------------------------"

# Executable
ssh -i ${KEY} pi@${RPI} -f "touch /home/pi/${EXECNAME}.elf"
scp -i ${KEY} ${EXECNAME} pi@${RPI}:/home/pi/${EXECNAME}.elf 

echo "--------------------------------------------------------------------"
echo "Copying files done !"
echo "--------------------------------------------------------------------"

# =============================================================================
# CONFIGURATION
# =============================================================================

echo "Applying files modifications..."
echo "--------------------------------------------------------------------"
ssh -i ${KEY} pi@${RPI} -f "chmod +x /home/pi/${EXECNAME}.elf"
echo "--------------------------------------------------------------------"
echo "Finished applying modifications !"
echo "--------------------------------------------------------------------"

# =============================================================================
# REBOOTING
# =============================================================================

echo "
Update done !
The RaspberryPi will now reboot."
echo "--------------------------------------------------------------------"
ssh -i ${KEY} pi@${RPI} -f "sudo reboot"
exit
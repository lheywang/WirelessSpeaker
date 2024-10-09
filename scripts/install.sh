#bin/
echo "I will now install and set up everything to make the compilation possible..."

apt-get install -y build-essential libc6-dev make doxygen ssh libi2c-dev device-tree-compiler g++-aarch64-linux-gnu cmake
cd ../tools/ && git clone https://github.com/raspberrypi/utils.git
cd ../tools/utils && cmake . && sudo make install
echo "If no errors occureds, all tools are installed sucessfully"
exit

echo "--------------------------------------------------------------------"
echo "Installed everything on your computer !"
echo "You can now compile the project"
echo "--------------------------------------------------------------------"

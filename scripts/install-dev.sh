#bin/
echo "I will now install and set up everything to make the compilation possible..."

apt-get install -y build-essential libc6-dev make doxygen ssh libi2c-dev device-tree-compiler g++-aarch64-linux- cmake texlive-full libfdt-dev gcc graphviz
cd ../tools/ && git clone https://github.com/raspberrypi/utils.git
cd ../tools/utils && cmake . && sudo make install

echo "--------------------------------------------------------------------"
echo "Installed everything on your computer !"
echo "You can now compile and update the project on github !"
echo "--------------------------------------------------------------------"

exit
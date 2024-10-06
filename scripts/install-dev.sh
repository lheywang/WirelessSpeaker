#bin/
echo "I will now install and set up everything to make the compilation possible..."

apt-get install -y build-essential libc6-dev make doxygen ssh libi2c-dev device-tree-compiler g++-aarch64-linux- cmake
apt-get install texlive-full libfdt-dev gcc graphviz
cd ../tools/ && git clone https://github.com/raspberrypi/utils.git
cd ../tools/utils && cmake . && sudo make install

exit
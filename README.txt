You need esp-idf-5.4.3 and python 3.10, you will find both in the extra_packages folder

To install idf:
cd into idf folder
./install.sh

cd into qutee project folder
. ~/pathtothefolder/esp-idf-5.4.3/export.sh

To install python:
cd into python folder
./configure --enable-optimizations
make -j$(nproc)
sudo make altinstall

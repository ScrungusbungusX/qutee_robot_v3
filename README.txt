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

Adding dependencies:
idf.py add-dependency espressif/esp_diagnostics
idf.py add-dependency espressif/esp_schedule
idf.py add-dependency espressif/esp-zigbee-lib
idf.py add-dependency espressif/mdns
idf.py add-dependency espressif/cbor
idf.py add-dependency espressif/esp-dsp
idf.py add-dependency espressif/esp_secure_cert_mgr
idf.py add-dependency espressif/jsmn
idf.py add-dependency espressif/qrcode
idf.py add-dependency espressif/eigen
idf.py add-dependency espressif/esp_insights
idf.py add-dependency espressif/esp-sr
idf.py add-dependency espressif/json_generator
idf.py add-dependency espressif/rmaker_common
idf.py add-dependency espressif/esp_diag_data_store
idf.py add-dependency espressif/esp_rainmaker
idf.py add-dependency espressif/esp-zboss-lib
idf.py add-dependency espressif/json_parser
idf.py add-dependency joltwallet/littlefs
idf.py add-dependency espressif/arduino-esp32

idf.py update-dependencies

This is extremely important - otherwise the target for the chip name is wrong:
idf.py set-target 'esp32-s3'

If you need to change some config settings, located in sdkconfig:
idf.py menuconfig

idf.py fullclean
idf.py reconfigure
idf.py build

For flashing you may need to chmod (change permission) for the usb slot its connected to:
sudo chmod 777 /dev/ttyACM0

Note: its not always ACM0, the name could be different - to check use 'ls /dev/tty*'
You can unplug the robot, rerun the command and see which one is missing

idf.py -p /dev/ttyACM0 flash

idf.py -p /dev/ttyACM0 monitor

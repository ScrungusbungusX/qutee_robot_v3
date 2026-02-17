 
// port_handler_esp32.h
#pragma once
#include <stdint.h>

namespace dynamixel {

class PortHandler {
public:
    PortHandler(int uart_num);  // ESP32 UART number
    bool openPort();
    void closePort();
    int writePort(const uint8_t *data, int length);
    int readPort(uint8_t *data, int length);
    void setBaudRate(int baudrate);
    bool isOpen();
};

} // namespace dynamixel

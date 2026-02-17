 
// port_handler_esp32.cpp
#include "dynamixel_sdk/group_sync_read.h"
#include "dynamixel_sdk/port_handler_esp32.h"
#include "driver/uart.h"

namespace dynamixel {

PortHandler::PortHandler(int uart_num) { /* init uart */ }
bool PortHandler::openPort() { return true; }
void PortHandler::closePort() { }
int PortHandler::writePort(const uint8_t *data, int length) { return length; }
int PortHandler::readPort(uint8_t *data, int length) { return 0; }
void PortHandler::setBaudRate(int baudrate) { }
bool PortHandler::isOpen() { return true; }

} // namespace dynamixel

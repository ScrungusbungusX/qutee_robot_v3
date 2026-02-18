#include "dynamixel_sdk/port_handler.h"

#if defined(ESP_PLATFORM)
#include "dynamixel_sdk/port_handler_esp32.h"
#elif defined(__linux__)
#include "dynamixel_sdk/port_handler_linux.h"
#elif defined(__APPLE__)
#include "dynamixel_sdk/port_handler_mac.h"
#elif defined(_WIN32) || defined(_WIN64)
#include "dynamixel_sdk/port_handler_windows.h"
#elif defined(ARDUINO) || defined(__OPENCR__) || defined(__OPENCM904__) || defined(ARDUINO_OpenRB)
#include "dynamixel_sdk/port_handler_arduino.h"
#endif

using namespace dynamixel;

PortHandler *PortHandler::getPortHandler(const char *port_name)
{
#if defined(ESP_PLATFORM)
    return new PortHandlerESP32(port_name);

#elif defined(__linux__)
    return new PortHandlerLinux(port_name);

#elif defined(__APPLE__)
    return new PortHandlerMac(port_name);

#elif defined(_WIN32) || defined(_WIN64)
    return new PortHandlerWindows(port_name);

#elif defined(ARDUINO) || defined(__OPENCR__) || defined(__OPENCM904__) || defined(ARDUINO_OpenRB)
    return new PortHandlerArduino(port_name);

#else
    return nullptr;
#endif
}

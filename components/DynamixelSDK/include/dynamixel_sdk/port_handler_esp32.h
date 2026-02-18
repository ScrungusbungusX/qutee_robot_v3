#pragma once

#include "dynamixel_sdk/port_handler.h"
#include "driver/uart.h"
#include "esp_timer.h"

namespace dynamixel {

class PortHandlerESP32 : public PortHandler {
public:
    explicit PortHandlerESP32(const char* port_name);
    virtual ~PortHandlerESP32();

    bool    openPort() override;
    void    closePort() override;
    void    clearPort() override;

    void    setPortName(const char* port_name) override;
    char*   getPortName() override;

    bool    setBaudRate(const int baudrate) override;
    int     getBaudRate() override;

    int     getBytesAvailable() override;

    int     readPort(uint8_t *packet, int length) override;
    int     writePort(uint8_t *packet, int length) override;

    void    setPacketTimeout(uint16_t packet_length) override;
    void    setPacketTimeout(double msec) override;

    bool    isPacketTimeout() override;

private:
    uart_port_t uart_num_;
    int baudrate_;
    char port_name_[32];

    int64_t packet_start_time_;
    int64_t packet_timeout_;
};

} // namespace dynamixel

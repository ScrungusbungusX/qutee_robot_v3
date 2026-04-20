#pragma once
#ifndef QUTEE_DYNAMIXEL_PORT_HANDLER_HPP_
#define QUTEE_DYNAMIXEL_PORT_HANDLER_HPP_

#include <driver/uart.h>
#include <driver/gpio.h>
#include "utility/port_handler.h"

class QuteeDxlPortHandler : public DXLPortHandler
{
public:
    explicit QuteeDxlPortHandler(uart_port_t uart_num, gpio_num_t dir_pin);

    virtual void begin();
    virtual void begin(int baud);
    virtual void end();
    virtual int available();
    virtual int read();
    virtual size_t write(uint8_t);
    virtual size_t write(uint8_t*, size_t);

private:
    uart_port_t uart_num_;
    gpio_num_t dir_pin_;
    unsigned long baud_;

    inline void setTX();
    inline void setRX();
};

#endif

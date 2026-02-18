#include "dynamixel_sdk/port_handler_esp32.h"
#include "string.h"

namespace dynamixel {

PortHandlerESP32::PortHandlerESP32(const char* port_name)
{
    is_using_ = false;
    baudrate_ = DEFAULT_BAUDRATE_;

    strncpy(port_name_, port_name, sizeof(port_name_) - 1);
    port_name_[sizeof(port_name_) - 1] = '\0';

    // Example: "UART_NUM_1" → select UART1
    if (strcmp(port_name, "UART1") == 0)
        uart_num_ = UART_NUM_1;
    else if (strcmp(port_name, "UART2") == 0)
        uart_num_ = UART_NUM_2;
    else
        uart_num_ = UART_NUM_0;

    packet_start_time_ = 0;
    packet_timeout_ = 0;
}

PortHandlerESP32::~PortHandlerESP32()
{
    closePort();
}

bool PortHandlerESP32::openPort()
{
    uart_config_t uart_config = {
        .baud_rate = baudrate_,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };

    if (uart_param_config(uart_num_, &uart_config) != ESP_OK)
        return false;

    if (uart_driver_install(uart_num_, 2048, 0, 0, NULL, 0) != ESP_OK)
        return false;

    is_using_ = true;
    return true;
}

void PortHandlerESP32::closePort()
{
    uart_driver_delete(uart_num_);
    is_using_ = false;
}

void PortHandlerESP32::clearPort()
{
    uart_flush(uart_num_);
}

void PortHandlerESP32::setPortName(const char* port_name)
{
    strncpy(port_name_, port_name, sizeof(port_name_) - 1);
}

char* PortHandlerESP32::getPortName()
{
    return port_name_;
}

bool PortHandlerESP32::setBaudRate(const int baudrate)
{
    baudrate_ = baudrate;
    return (uart_set_baudrate(uart_num_, baudrate_) == ESP_OK);
}

int PortHandlerESP32::getBaudRate()
{
    return baudrate_;
}

int PortHandlerESP32::getBytesAvailable()
{
    size_t length;
    uart_get_buffered_data_len(uart_num_, &length);
    return (int)length;
}

int PortHandlerESP32::readPort(uint8_t *packet, int length)
{
    return uart_read_bytes(uart_num_, packet, length, 0);
}

int PortHandlerESP32::writePort(uint8_t *packet, int length)
{
    return uart_write_bytes(uart_num_, (const char*)packet, length);
}

void PortHandlerESP32::setPacketTimeout(uint16_t packet_length)
{
    packet_start_time_ = esp_timer_get_time();
    packet_timeout_ = packet_length * 1000;  // microseconds estimate
}

void PortHandlerESP32::setPacketTimeout(double msec)
{
    packet_start_time_ = esp_timer_get_time();
    packet_timeout_ = (int64_t)(msec * 1000.0);
}

bool PortHandlerESP32::isPacketTimeout()
{
    int64_t now = esp_timer_get_time();
    return (now - packet_start_time_) > packet_timeout_;
}

} // namespace dynamixel

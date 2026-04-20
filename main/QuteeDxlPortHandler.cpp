#include "QuteeDxlPortHandler.hpp"

static const char* TAG = "ESP2Dynamixel";

QuteeDxlPortHandler::QuteeDxlPortHandler(uart_port_t uart_num, gpio_num_t dir_pin)
: DXLPortHandler(),
  uart_num_(uart_num),
  dir_pin_(dir_pin)
{}

inline void QuteeDxlPortHandler::setTX() {
    gpio_set_level(dir_pin_, 1);
}

inline void QuteeDxlPortHandler::setRX() {
    gpio_set_level(dir_pin_, 0);
}

void QuteeDxlPortHandler::begin()
{
    begin(57600);
}

void QuteeDxlPortHandler::begin(int baud)
{
    baud_ = baud;

    ESP_LOGI(TAG, "PORT INIT (HALF DUPLEX)");

    uart_config_t uart_config = {
        .baud_rate = baud,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };

    // Configure DIR pin
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << dir_pin_),
        .mode = GPIO_MODE_OUTPUT,
    };
    gpio_config(&io_conf);

    setRX();  // default to receive

    if (uart_is_driver_installed(uart_num_)) {
        uart_driver_delete(uart_num_);
    }

    ESP_ERROR_CHECK(uart_param_config(uart_num_, &uart_config));

    ESP_ERROR_CHECK(uart_set_pin(
        uart_num_,
        GPIO_NUM_17,  // TX
        GPIO_NUM_18,  // RX (can still be defined, but bus is shared externally)
        UART_PIN_NO_CHANGE,
        UART_PIN_NO_CHANGE
    ));

    ESP_ERROR_CHECK(uart_driver_install(
        uart_num_,
        4096,
        4096,
        0,
        NULL,
        0
    ));

    setOpenState(true);

    ESP_LOGI(TAG, "PORT READY");
}

size_t QuteeDxlPortHandler::write(uint8_t *buf, size_t len)
{
    setTX();

    int written = uart_write_bytes(uart_num_, buf, len);
    uart_wait_tx_done(uart_num_, pdMS_TO_TICKS(20));

    ets_delay_us(50);

    setRX();

    return (written > 0) ? (size_t)written : 0;
}

void QuteeDxlPortHandler::end()
{
    uart_driver_delete(uart_num_);
    setOpenState(false);
}

int QuteeDxlPortHandler::available()
{
    size_t len = 0;
    uart_get_buffered_data_len(uart_num_, &len);
    return (int)len;
}

int QuteeDxlPortHandler::read()
{
    uint8_t byte;
    int len = uart_read_bytes(uart_num_, &byte, 1, pdMS_TO_TICKS(10));
    return (len == 1) ? byte : -1;
}

size_t QuteeDxlPortHandler::write(uint8_t c)
{
    return write(&c, 1);
}


idf_component_register(
    SRCS "src/Dynamixel2Arduino.cpp"
         "src/utility/port_handler.cpp"
    INCLUDE_DIRS
         "src"
    REQUIRES
          driver
          espressif__arduino-esp32
          arduino
)  # driver is needed for UART, GPIO, etc.


idf_component_register(
    SRCS "src/Dynamixel2Arduino.cpp"
         "src/utility/port_handler.cpp"
         "src/utility/master.cpp"
         "src/utility/slave.cpp"
         "src/dxl_c/protocol.cpp"
         "src/actuator.cpp"
    INCLUDE_DIRS
         "src"
    REQUIRES
          driver
          espressif__arduino-esp32
          arduino
          DynamixelSDK
)  # driver is needed for UART, GPIO, etc.

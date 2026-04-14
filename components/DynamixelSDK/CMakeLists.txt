idf_component_register(
    SRCS
        "src/dynamixel_sdk/port_handler_esp32.cpp"
        "src/dynamixel_sdk/packet_handler.cpp"
        "src/dynamixel_sdk/protocol1_packet_handler.cpp"
        "src/dynamixel_sdk/protocol2_packet_handler.cpp"
        "src/dynamixel_sdk/group_sync_read.cpp"
        "src/dynamixel_sdk/group_sync_write.cpp"
        "src/dynamixel_sdk/group_bulk_read.cpp"
        "src/dynamixel_sdk/group_bulk_write.cpp"

        #"src/dynamixel_sdk/group_fast_bulk_read.cpp"
        #"src/dynamixel_sdk/group_fast_sync_read.cpp"
        #"src/dynamixel_sdk/group_handler.cpp"
        "src/dynamixel_sdk/port_handler_arduino.cpp"
        "src/dynamixel_sdk/port_handler_linux.cpp"
        "src/dynamixel_sdk/port_handler_mac.cpp"
        "src/dynamixel_sdk/port_handler_windows.cpp"
        "src/dynamixel_sdk/port_handler.cpp"

        #"src/dynamixel_easy_sdk/connector.cpp"
        #"src/dynamixel_easy_sdk/control_table.cpp"
        #"src/dynamixel_easy_sdk/dynamixel_error.cpp"
        #"src/dynamixel_easy_sdk/group_executor.cpp"
        #"src/dynamixel_easy_sdk/motor.cpp"

    INCLUDE_DIRS
        "include"
        "include/dynamixel_sdk"

    REQUIRES
        driver
        esp_timer
)

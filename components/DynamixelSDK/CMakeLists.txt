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

    INCLUDE_DIRS
        "include"
        "include/dynamixel_sdk"

    REQUIRES
        driver
)

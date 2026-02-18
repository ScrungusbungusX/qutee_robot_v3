
if(CMAKE_GENERATOR STREQUAL "Unix Makefiles")
set(submake "$(MAKE)")
else()
set(submake "make")
endif()

if (${IDF_VERSION_MAJOR} EQUAL 5)
    set(CMAKE_C_STANDARD 17)
else()
    set(CMAKE_C_STANDARD 11)
endif()

set(EXTRA_COMPONENT_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/../managed_components
    ${CMAKE_CURRENT_SOURCE_DIR}/../components/arduino
    ${CMAKE_CURRENT_SOURCE_DIR}/../components/Adafruit_BNO055
    ${CMAKE_CURRENT_SOURCE_DIR}/../components/Adafruit_ST7789
    ${CMAKE_CURRENT_SOURCE_DIR}/../components/Adafruit-GFX-Library
    ${CMAKE_CURRENT_SOURCE_DIR}/../components/Adafruit_BusIO
    ${CMAKE_CURRENT_SOURCE_DIR}/../components/Dynamixel2Arduino
    ${CMAKE_CURRENT_SOURCE_DIR}/../components/DynamixelSDK
    ${CMAKE_CURRENT_SOURCE_DIR}/../components/Adafruit_Sensor
    ${CMAKE_CURRENT_SOURCE_DIR}/../components/Adafruit_MAX1704X
)

idf_component_register(
    SRCS
        "main.cpp"
        "Qutee.cpp"
        "QuteeDxlPortHandler.cpp"

    INCLUDE_DIRS

    REQUIRES
        eigen
        Dynamixel2Arduino
        DynamixelSDK
        arduino
        Adafruit_Sensor
        Adafruit_BNO055
        Adafruit_ST7789
        Adafruit_MAX1704X
)

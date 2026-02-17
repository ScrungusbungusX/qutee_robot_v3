 
idf_component_register(
    SRCS "Adafruit_BNO055.cpp"
    INCLUDE_DIRS "."       # Look for headers in the root of this component
    REQUIRES
        espressif__arduino-esp32
        Adafruit_BusIO
        Adafruit_Sensor # List dependencies here if needed (e.g., arduino)
)

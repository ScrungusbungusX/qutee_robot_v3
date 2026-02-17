 
idf_component_register(
    SRCS "Adafruit_MAX1704X.cpp"
    INCLUDE_DIRS "."       # Look for headers in the root of this component
    REQUIRES
        espressif__arduino-esp32
        Adafruit_BusIO # List dependencies here if needed (e.g., arduino)
)

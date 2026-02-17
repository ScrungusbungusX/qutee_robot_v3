 
idf_component_register(
    SRCS "Adafruit_Sensor.cpp"
    INCLUDE_DIRS "."       # Look for headers in the root of this component
    REQUIRES
        espressif__arduino-esp32 # List dependencies here if needed (e.g., arduino)
)

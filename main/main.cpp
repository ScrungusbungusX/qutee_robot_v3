#include "Qutee.hpp"
#include "esp_log.h"

static const char* TAG = "QUTEE_MAIN";

extern "C" void app_main() {
    ESP_LOGI(TAG, "Initializing Qutee...");

    Qutee robot;

    robot.init();          // initialize motors, TFT, IMU, NVS
    robot.select_name();   // choose or load robot name
    robot.calibration();   // IMU calibration if required
    robot.go_to_neutral_pose(); // reset motors

    ESP_LOGI(TAG, "Starting main control loop...");

    while (true) {
        robot.run_episode();
    }
}


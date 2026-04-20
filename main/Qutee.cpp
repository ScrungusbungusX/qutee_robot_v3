#include "Qutee.hpp"
#include "QuteeDxlPortHandler.hpp"

#include "esp_task_wdt.h"
#include <inttypes.h>
#include "driver/ledc.h"

// Init

#include "Qutee.hpp"
#include "QuteeDxlPortHandler.hpp"

#include "esp_task_wdt.h"
#include <inttypes.h>
#include "driver/ledc.h"

const char* Qutee::TAG = "QUTEE";

Qutee::Qutee()
    : _dxl_port(UART_NUM_1, GPIO_NUM_18)
{
    memset(&_sr_infos, 0, sizeof(_sr_infos));
    memset(&_sw_infos, 0, sizeof(_sw_infos));
}

const int Qutee::DXL_IDs[] = {11, 12, 13, 21, 22, 23, 31, 32, 33, 41, 42, 43};
const uint8_t Qutee::DXL_ID_CNT = 12;

// INIT
void Qutee::init()
{
    ESP_LOGI(TAG, "Initialising Qutee (STABLE MODE)");

    init_dynamixel_stack();

    init_motors();
    scan();

    for (int i = 0; i < DXL_ID_CNT; i++) {
        _info_xels_sr[i].id = DXL_IDs[i];
        _info_xels_sr[i].p_recv_buf = (uint8_t*)&_sr_data[i];
    }

    _sr_infos.packet.p_buf = _user_pkt_buf;
    _sr_infos.packet.buf_capacity = sizeof(_user_pkt_buf);
    _sr_infos.packet.is_completed = false;
    _sr_infos.addr = SR_START_ADDR;
    _sr_infos.addr_length = SR_ADDR_LEN;
    _sr_infos.p_xels = _info_xels_sr;
    _sr_infos.xel_count = DXL_ID_CNT;

    test_move();

    ESP_LOGI(TAG, "INIT COMPLETE");
}

void Qutee::init_dynamixel_stack()
{
    ESP_LOGI(TAG, "Setting up DXL stack");

    _dxl_port.begin(57600);   // MUST come first

    ESP_LOGI(TAG, "before setPort");
    _dxl.setPort(&_dxl_port);
    ESP_LOGI(TAG, "after setPort");

    _dxl.setPortProtocolVersion(2.0);

    vTaskDelay(pdMS_TO_TICKS(50));  // IMPORTANT stabilisation delay

    _dxl.begin(57600);
}

// Scan motors

void Qutee::scan()
{
  // put your setup code here, to run once:
  int8_t found_dynamixel = 0;
  for (int id = 1; id <= 252; id++) {
    vTaskDelay(pdMS_TO_TICKS(2));  // IMPORTANT for half duplex stability

    ESP_LOGI("DXL", "Testing ID: %d", id);

    if (_dxl.ping(id))
    {
        ESP_LOGI("DXL", "ID %d Model: %d", id, _dxl.getModelNumber(id));
        found_dynamixel++;
    }
  }
  ESP_LOGI("DXL: ","Total %i DYNAMIXEL(s) found!\n",found_dynamixel );
}

// PID setup

void Qutee::set_PID_gains() {
    // adjust these values depending on how your robot behaves. 0.05 looks like a good target to have on all motors during checkup.
    uint16_t position_p_gain = 1600;
    uint16_t position_i_gain = 0;
    uint16_t position_d_gain = 40;
    // Set Position PID Gains
    for (int i = 0; i < DXL_ID_CNT; i++) {
        int id = DXL_IDs[i];

        _dxl.writeControlTableItem(ControlTableItem::POSITION_P_GAIN, id, 1600);
        _dxl.writeControlTableItem(ControlTableItem::POSITION_I_GAIN, id, 0);
        _dxl.writeControlTableItem(ControlTableItem::POSITION_D_GAIN, id, 40);
    }
}

// Motor init

void Qutee::init_motors() {
    for (int i = 0; i < DXL_ID_CNT; i++) {
        int id = DXL_IDs[i];

        _dxl.torqueOff(id);
        _dxl.setOperatingMode(id, OP_POSITION);
        _dxl.torqueOn(id);

        ESP_LOGI(TAG, "Torque ON ID=%d", id);

        _dxl.writeControlTableItem(ControlTableItem::PROFILE_VELOCITY, id, 0);
    }

    set_PID_gains();
}

// Read positions

void Qutee::get_motor_positions() {
    uint8_t recv = _dxl.syncRead(&_sr_infos);

    if (recv > 0) {
        for (int i = 0; i < recv; i++) {
            ESP_LOGI(TAG, "ID %d Pos %" PRId32,
                     _info_xels_sr[i].id,
                     _sr_data[i].present_position);
        }
    } else {
        ESP_LOGE(TAG, "SyncRead failed: %ld", (long)_dxl.getLastLibErrCode());
    }
}

// Test movement

void Qutee::test_move() {

    //get_motor_positions();

    ESP_LOGI(TAG, "TEST MOVE");

    for (int i = 0; i < DXL_ID_CNT; i++) {
        _sw_data[i].goal_position = 2048 + 300;
    }

    _dxl.syncWrite(&_sw_infos);
    vTaskDelay(pdMS_TO_TICKS(1000));

    for (int i = 0; i < DXL_ID_CNT; i++) {
        _sw_data[i].goal_position = 2048 - 300;
    }

    _dxl.syncWrite(&_sw_infos);
}

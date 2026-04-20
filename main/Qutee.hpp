#pragma once

#include <cstdint>
#include <cstring>
#include <esp_log.h>

#include "Dynamixel2Arduino.h"
#include "QuteeDxlPortHandler.hpp"

class Qutee {
public:
    Qutee();

    void init();
    void scan();
    void init_motors();
    void test_move();
    void get_motor_positions();
    void set_PID_gains();

    static const int DXL_IDs[12];
    static const uint8_t DXL_ID_CNT;

private:
    static const char* TAG;

    QuteeDxlPortHandler _dxl_port;
    DYNAMIXEL::Dynamixel2Arduino _dxl;

    // =========================
    // Sync READ structures
    // =========================
    typedef struct {
        int32_t present_position;
    } __attribute__((packed)) sr_data_t;

    sr_data_t _sr_data[12];

    DYNAMIXEL::InfoSyncReadInst_t _sr_infos;
    DYNAMIXEL::XELInfoSyncRead_t _info_xels_sr[12];

    static constexpr uint16_t SR_START_ADDR = 132;
    static constexpr uint16_t SR_ADDR_LEN   = 4;

    uint8_t _user_pkt_buf[128];

    // =========================
    // Sync WRITE structures
    // =========================
    typedef struct {
        int32_t goal_position;
    } __attribute__((packed)) sw_data_t;

    sw_data_t _sw_data[12];

    DYNAMIXEL::InfoSyncWriteInst_t _sw_infos;
    DYNAMIXEL::XELInfoSyncWrite_t _info_xels_sw[12];

    static constexpr uint16_t SW_START_ADDR = 116;
    static constexpr uint16_t SW_ADDR_LEN   = 4;

    void init_dynamixel_stack();
};

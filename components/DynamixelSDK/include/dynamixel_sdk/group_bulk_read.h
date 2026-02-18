/*******************************************************************************
* Copyright 2017 ROBOTIS CO., LTD.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#ifndef DYNAMIXEL_SDK_INCLUDE_DYNAMIXEL_SDK_GROUPBULKREAD_H_
#define DYNAMIXEL_SDK_INCLUDE_DYNAMIXEL_SDK_GROUPBULKREAD_H_

#pragma once
#include <map>
#include <vector>
#include <algorithm>
#include "dynamixel_sdk/packet_handler.h"
#include "dynamixel_sdk/port_handler.h"

namespace dynamixel
{

////////////////////////////////////////////////////////////////////////////////
/// @brief The class for reading multiple Dynamixel data from different addresses with different lengths at once
////////////////////////////////////////////////////////////////////////////////
class WINDECLSPEC GroupBulkRead
{
private:
    PortHandler* port_;
    PacketHandler* ph_;

    std::vector<uint8_t> id_list_;
    std::map<uint8_t, uint16_t> address_list_;
    std::map<uint8_t, uint16_t> length_list_;
    std::map<uint8_t, uint8_t*> data_list_;
    std::map<uint8_t, uint8_t*> error_list_;

    uint8_t* param_;
    bool is_param_changed_;
    bool last_result_;

protected:
    void makeParam();

public:
    GroupBulkRead(PortHandler* port, PacketHandler* ph);
    ~GroupBulkRead() { clearParam(); }

    bool addParam(uint8_t id, uint16_t start_address, uint16_t data_length);
    void removeParam(uint8_t id);
    void clearParam();

    int txPacket();
    int rxPacket();
    int txRxPacket();

    bool isAvailable(uint8_t id, uint16_t address, uint16_t data_length);
    uint32_t getData(uint8_t id, uint16_t address, uint16_t data_length);
    bool getError(uint8_t id, uint8_t* error);
};

} // namespace dynamixel

#endif /* DYNAMIXEL_SDK_INCLUDE_DYNAMIXEL_SDK_GROUPBULKREAD_H_ */

#include "dynamixel_sdk/group_bulk_read.h"
#include <cstring>

namespace dynamixel
{

GroupBulkRead::GroupBulkRead(PortHandler* port, PacketHandler* ph)
    : port_(port), ph_(ph), param_(nullptr), is_param_changed_(false), last_result_(false)
{
}

void GroupBulkRead::makeParam()
{
    if (id_list_.empty())
        return;

    if (param_ != nullptr)
        delete[] param_;

    if (ph_->getProtocolVersion() == 1.0)
        param_ = new uint8_t[id_list_.size() * 3]; // ID + ADDR + LENGTH
    else
        param_ = new uint8_t[id_list_.size() * 5]; // ID + ADDR(2) + LENGTH(2)

    for (size_t i = 0; i < id_list_.size(); ++i)
    {
        uint8_t id = id_list_[i];
        if (ph_->getProtocolVersion() == 1.0)
        {
            param_[i * 3 + 0] = id;
            param_[i * 3 + 1] = address_list_[id];
            param_[i * 3 + 2] = length_list_[id];
        }
        else
        {
            param_[i * 5 + 0] = id;
            param_[i * 5 + 1] = address_list_[id] & 0xFF;
            param_[i * 5 + 2] = (address_list_[id] >> 8) & 0xFF;
            param_[i * 5 + 3] = length_list_[id] & 0xFF;
            param_[i * 5 + 4] = (length_list_[id] >> 8) & 0xFF;
        }
    }

    is_param_changed_ = false;
}

bool GroupBulkRead::addParam(uint8_t id, uint16_t start_address, uint16_t data_length)
{
    if (std::find(id_list_.begin(), id_list_.end(), id) != id_list_.end())
        return false;

    id_list_.push_back(id);
    address_list_[id] = start_address;
    length_list_[id] = data_length;
    data_list_[id] = new uint8_t[data_length];
    error_list_[id] = new uint8_t(0);

    is_param_changed_ = true;
    return true;
}

void GroupBulkRead::removeParam(uint8_t id)
{
    auto it = std::find(id_list_.begin(), id_list_.end(), id);
    if (it != id_list_.end())
    {
        delete[] data_list_[id];
        delete error_list_[id];
        id_list_.erase(it);
        data_list_.erase(id);
        error_list_.erase(id);
        address_list_.erase(id);
        length_list_.erase(id);
        is_param_changed_ = true;
    }
}

void GroupBulkRead::clearParam()
{
    for (auto id : id_list_)
    {
        delete[] data_list_[id];
        delete error_list_[id];
    }
    id_list_.clear();
    data_list_.clear();
    error_list_.clear();
    address_list_.clear();
    length_list_.clear();

    if (param_ != nullptr)
    {
        delete[] param_;
        param_ = nullptr;
    }

    is_param_changed_ = true;
}

int GroupBulkRead::txPacket()
{
    if (id_list_.empty())
        return COMM_NOT_AVAILABLE;

    if (is_param_changed_ || param_ == nullptr)
        makeParam();

    if (ph_->getProtocolVersion() == 1.0)
        return ph_->bulkReadTx(port_, param_, id_list_.size() * 3);
    else
        return ph_->bulkReadTx(port_, param_, id_list_.size() * 5);
}

int GroupBulkRead::rxPacket()
{
    if (id_list_.empty())
        return COMM_NOT_AVAILABLE;

    last_result_ = true;
    int result = COMM_SUCCESS;

    for (auto id : id_list_)
    {
        int comm = ph_->readRx(port_, id, length_list_[id], data_list_[id], error_list_[id]);
        if (comm != COMM_SUCCESS)
        {
            last_result_ = false;
            result = comm;
        }
    }

    return result;
}

int GroupBulkRead::txRxPacket()
{
    int tx_result = txPacket();
    if (tx_result != COMM_SUCCESS)
        return tx_result;

    return rxPacket();
}

bool GroupBulkRead::isAvailable(uint8_t id, uint16_t address, uint16_t data_length)
{
    if (!last_result_ || data_list_.find(id) == data_list_.end())
        return false;
    if (address < address_list_[id] || address + data_length > address_list_[id] + length_list_[id])
        return false;
    return true;
}

uint32_t GroupBulkRead::getData(uint8_t id, uint16_t address, uint16_t data_length)
{
    if (!isAvailable(id, address, data_length))
        return 0;

    uint32_t value = 0;
    for (uint16_t i = 0; i < data_length; ++i)
    {
        value |= (uint32_t)data_list_[id][address - address_list_[id] + i] << (8 * i);
    }
    return value;
}

bool GroupBulkRead::getError(uint8_t id, uint8_t* error)
{
    if (ph_->getProtocolVersion() == 1.0 || !last_result_ || error_list_.find(id) == error_list_.end())
        return false;

    *error = *error_list_[id];
    return true;
}

} // namespace dynamixel

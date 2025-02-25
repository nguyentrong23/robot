#include "dh_lce.h"

namespace dhr {
DH_LCE::DH_LCE() {
  is_first_update_data_ = true;
  InitDataMap();
}

DH_LCE::DH_LCE(int slave_address) {
  slave_address_ = slave_address;
  is_first_update_data_ = true;
  InitDataMap();
}

void DH_LCE::SetSlaveAddress(int address) {
  if(IsValueInRange(SLAVE_ADDRESS_MAX, SLAVE_ADDRESS_MIN, address)) {
    slave_address_ = address;
  }
}

void DH_LCE::UpdateData(const QModbusDataUnit unit) {
  for (qsizetype index=0;index<unit.valueCount();++index) {
    quint16 address = static_cast<quint16>(unit.startAddress()) +
                      static_cast<quint16>(index);
    if (data_map_.contains(address)) {
      data_map_[address] = unit.value(index);
    }
  }

  if (is_first_update_data_) {
    last_linear_state_ = data_map_[feedback_linear_status];
    is_first_update_data_ = false;
    return;
  }

  if (last_linear_state_ != data_map_[feedback_linear_status]) {
    is_linear_state_change_ = true;
    last_linear_state_ = data_map_[feedback_linear_status];
    return;
  }
}

LCEData DH_LCE::DeviceInfo() {
  LCEData rgi_info;
  ConvertFeedbackData(rgi_info);
  return rgi_info;
}

bool DH_LCE::IsLinearStateChange(DhLinearStatus &state) {
  bool result = is_linear_state_change_;
  if (result) { is_linear_state_change_ = false; }
  state = static_cast<DhLinearStatus>(data_map_[feedback_linear_status]);
  return result;
}

ModbusFunc DH_LCE::GetDeviceFeedbackInfo() {
  return GetDeviceFeedbackInfo(slave_address_);
}

ModbusFunc DH_LCE::SetInitDevice() {
  return SetInitDevice(slave_address_);
}

ModbusFunc DH_LCE::SetLinearPosition(int position) {
  return SetLinearPosition(slave_address_, position);
}

ModbusFunc DH_LCE::SetLinearForce(int force) {
  return SetLinearForce(slave_address_, force);
}

ModbusFunc DH_LCE::SetLinearSpeed(int speed) {
  return SetLinearSpeed(slave_address_, speed);
}

ModbusFunc DH_LCE::GetDeviceFeedbackInfo(int slave_address) {
  ModbusFunc func(slave_address, FuncCode::kFuncReadHoldingRegs,
                  feedback_linear_init_state, static_cast<quint16>(0x18));
  return func;
}

ModbusFunc DH_LCE::SetInitDevice(int slave_address) {
  ModbusFunc func(slave_address, FuncCode::kFuncWriteHoldingRegs,
                  control_init, 1);
  func.value.push_back(165);
  return func;
}

ModbusFunc DH_LCE::SetLinearPosition(int slave_address, int position) {
  ModbusFunc func(slave_address, FuncCode::kFuncWriteHoldingRegs,
                  control_linear_position, 1);
  func.value.push_back(position);
  if(!IsValueInRange(LINEAR_POSITION_MAX, LINEAR_POSITION_MIN, position)) {
    func.slave_address = 255;
  }
  return func;
}

ModbusFunc DH_LCE::SetLinearForce(int slave_address, int force) {
  ModbusFunc func(slave_address, FuncCode::kFuncWriteHoldingRegs,
                  control_linear_force, 1);
  func.value.push_back(force);
  if(!IsValueInRange(LINEAR_FORCE_MAX, LINEAR_FORCE_MIN, force)) {
    func.slave_address = 255;
  }
  return func;
}

ModbusFunc DH_LCE::SetLinearSpeed(int slave_address, int speed) {
  ModbusFunc func(slave_address, FuncCode::kFuncWriteHoldingRegs,
                  control_linear_speed, 1);
  func.value.push_back(speed);
  if(!IsValueInRange(LINEAR_SPEED_MAX, LINEAR_SPEED_MIN, speed)) {
    func.slave_address = 255;
  }
  return func;
}

void DH_LCE::InitDataMap() {
  ///// MAPPING FEEDBACK DATA
  // control map
  data_map_[control_init] = 0x00;
  data_map_[control_linear_force] = 0x00;
  data_map_[control_linear_position] = 0x00;
  data_map_[control_linear_speed] = 0x00;
  // feedback map
  data_map_[feedback_linear_init_state] = 0x00;
  data_map_[feedback_linear_status] = 0x00;
  data_map_[feedback_linear_position] = 0x00;
  data_map_[feedback_linear_speed] = 0x00;
  data_map_[feedback_linear_current] = 0x00;
  data_map_[feedback_error_code] = 0x00;
}

void DH_LCE::ConvertFeedbackData(LCEData &lce_info) {
  lce_info.feedback.linear_init_state =
      static_cast<DhInitState>(data_map_[feedback_linear_init_state]);
  lce_info.feedback.linear_status =
      static_cast<DhLinearStatus>(data_map_[feedback_linear_status]);
  lce_info.feedback.linear_position = data_map_[feedback_linear_position];
  lce_info.feedback.linear_speed = data_map_[feedback_linear_speed];
  lce_info.feedback.linear_current = data_map_[feedback_linear_current];
  lce_info.feedback.error_code =
      static_cast<DhError>(data_map_[feedback_error_code]);
}
}

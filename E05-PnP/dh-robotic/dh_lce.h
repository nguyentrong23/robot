#ifndef DH_LCE_H
#define DH_LCE_H

#include "dhr_define.h"

namespace dhr {
class LCEData
{
public:
  struct LCEFeedback
  {
    DhInitState linear_init_state = DhInitState::kInitNone;
    DhLinearStatus linear_status = DhLinearStatus::kLinearAtPosition;
    int linear_position = 0x00;
    int linear_speed = 0x00;
    int linear_current = 0x00;
    DhError error_code = DhError::kErrorNone;
  };

  DhModelInfo model_info;
  LCEFeedback feedback;
};

class DH_LCE
{
public:
  DH_LCE();
  DH_LCE(int slave_address = 1);

  void SetSlaveAddress(int address);
  void UpdateData(const QModbusDataUnit unit);
  LCEData DeviceInfo();
  bool IsLinearStateChange(DhLinearStatus &state);

  ModbusFunc GetDeviceFeedbackInfo();
  ModbusFunc SetInitDevice();
  ModbusFunc SetLinearPosition(int position);
  ModbusFunc SetLinearForce(int force);
  ModbusFunc SetLinearSpeed(int speed);

  static ModbusFunc GetDeviceFeedbackInfo(int slave_address);
  static ModbusFunc SetInitDevice(int slave_address);
  static ModbusFunc SetLinearPosition(int slave_address, int position);
  static ModbusFunc SetLinearForce(int slave_address, int force);
  static ModbusFunc SetLinearSpeed(int slave_address, int speed);

private:
  void InitDataMap();
  void ConvertFeedbackData(LCEData &lce_info);

public:
  int slave_address_;

  static const quint16 control_init = 0x0100;
  static const quint16 control_linear_force = 0x0101;
  static const quint16 control_linear_position = 0x0103;
  static const quint16 control_linear_speed = 0x0104;

  static const quint16 feedback_linear_init_state = 0x0200;
  static const quint16 feedback_linear_status = 0x0201;
  static const quint16 feedback_linear_position = 0x0202;
  static const quint16 feedback_linear_speed = 0x0203;
  static const quint16 feedback_linear_current = 0x0204;
  static const quint16 feedback_error_code = 0x0205;

private:
  QMap<quint16, quint16> data_map_;
  bool is_first_update_data_ = true;
  quint16 last_linear_state_;
  bool is_linear_state_change_;
};
}

#endif // DH_LCE_H

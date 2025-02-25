#ifndef DH_RGI_H
#define DH_RGI_H

#include "dhr_define.h"

namespace dhr {
class RGIData
{
public:
  struct RGIFeedback
  {
    DhInitState gripper_init_state = DhInitState::kInitNone;
    DhGripperStatus gripper_status = DhGripperStatus::kGriperAtPosition;
    int gripper_position = 0x00;
    int gripper_speed = 0x00;
    int gripper_current = 0x00;
    DhInitState rotation_init_state = DhInitState::kInitNone;
    DhRotationStatus rotation_status = DhRotationStatus::kRotationAtPosition;
    int rotation_speed = 0x00;
    int rotation_current = 0x00;
    int rotation_angle = 0x00;
    DhError error_code = DhError::kErrorNone;
  };

  DhModelInfo model_info;
  RGIFeedback feedback;
};

class DH_RGI
{
public:
  DH_RGI();
  DH_RGI(int slave_address = 1);

  void SetSlaveAddress(int address);
  void UpdateData(const QModbusDataUnit unit);
  RGIData DeviceInfo();
  bool IsGripperStateChange(DhGripperStatus &state);
  bool IsRotateStateChange(DhRotationStatus &state);

  ModbusFunc GetDeviceFeedbackInfo();
  ModbusFunc SetInitDevice();
  ModbusFunc SetGripperPosition(int position);
  ModbusFunc SetGripperForce(int force);
  ModbusFunc SetGripperSpeed(int speed);
  ModbusFunc SetRotationAngle(int angle);
  ModbusFunc SetRotationTorque(int torque);
  ModbusFunc SetRotationSpeed(int speed);

  static ModbusFunc GetDeviceFeedbackInfo(int slave_address);
  static ModbusFunc SetInitDevice(int slave_address);
  static ModbusFunc SetGripperPosition(int slave_address, int position);
  static ModbusFunc SetGripperForce(int slave_address, int force);
  static ModbusFunc SetGripperSpeed(int slave_address, int speed);
  static ModbusFunc SetRotationAngle(int slave_address, int angle);
  static ModbusFunc SetRotationTorque(int slave_address, int torque);
  static ModbusFunc SetRotationSpeed(int slave_address, int speed);

private:
  void InitDataMap();
  void ConvertFeedbackData(RGIData &rgi_info);

public:
  int slave_address_;

  static const quint16 control_init = 0x0100;
  static const quint16 control_grip_force = 0x0101;
  static const quint16 control_grip_position = 0x0103;
  static const quint16 control_grip_speed = 0x0104;
  static const quint16 control_rotation_angle = 0x0105;
  static const quint16 control_rotation_speed = 0x0107;
  static const quint16 control_rotation_torque = 0x0108;

  static const quint16 feedback_grip_init_state = 0x0200;
  static const quint16 feedback_grip_status = 0x0201;
  static const quint16 feedback_grip_position = 0x0202;
  static const quint16 feedback_grip_speed = 0x0203;
  static const quint16 feedback_grip_current = 0x0204;
  static const quint16 feedback_error_code = 0x0205;
  static const quint16 feedback_rotation_angle = 0x0208;
  static const quint16 feedback_rotation_init_state = 0x020A;
  static const quint16 feedback_rotation_status = 0x020B;
  static const quint16 feedback_rotation_speed = 0x020C;
  static const quint16 feedback_rotation_current = 0x020D;

private:
  QMap<quint16, quint16> data_map_;
  bool is_first_update_data_ = true;
  quint16 last_grip_state_;
  quint16 last_rotate_state_;
  bool is_gripper_state_change_;
  bool is_rotate_state_change_;
};
}


#endif // DH_RGI_H

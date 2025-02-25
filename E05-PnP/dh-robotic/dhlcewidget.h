#ifndef DHLCEWIDGET_H
#define DHLCEWIDGET_H

#include <QWidget>
#include "dhr_define.h"
#include "dh_lce.h"

namespace Ui {
class DhLceWidget;
}

using namespace dhr;

class DhLceWidget : public QWidget
{
  Q_OBJECT

public:
  explicit DhLceWidget(QWidget *parent = nullptr);
  ~DhLceWidget();

  void ShowLceDeviceSetParameters(LCEData::LCEFeedback feedback_data);
  void ShowLceDeviceInfo(LCEData::LCEFeedback feedback_data);
  bool IsAutoInit();
  int GetSlaveAddress();
  void SetSlaveEditBoxEnable(bool is_enable);

private:
  void InitActions();

signals:
  void SignalsLceInitialize();
  void SignalsLinear_PositionEdited(int position);
  void SignalsLinear_ForceEdited(int force);
  void SignalsLinear_SpeedEdited(int speed);

private:
  Ui::DhLceWidget *ui;
};

#endif // DHLCEWIDGET_H

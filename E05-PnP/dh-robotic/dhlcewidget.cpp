#include "dhlcewidget.h"
#include "ui_dhlcewidget.h"

DhLceWidget::DhLceWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DhLceWidget)
{
  ui->setupUi(this);
  InitActions();
}

DhLceWidget::~DhLceWidget()
{
  delete ui;
}

void DhLceWidget::ShowLceDeviceSetParameters(LCEData::LCEFeedback feedback_data) {
  ui->doubleSpinBox_linear_position->setValue(feedback_data.linear_position / 100);
  ui->spinBox_linear_force->setValue(100);
  ui->spinBox_linear_speed->setValue(100);
}

void DhLceWidget::ShowLceDeviceInfo(LCEData::LCEFeedback feedback_data) {
  // linear info
  ui->label_linear_init_state->setText(
      "Initialize state: " + dhr::EnumConvert(feedback_data.linear_init_state));
  ui->label_linear_status->setText(
      "Status: " + dhr::EnumConvert(feedback_data.linear_status));
  ui->label_linear_position->setText(
      "Current position: " + QString::number(feedback_data.linear_position / 100));
}

bool DhLceWidget::IsAutoInit() {
  return ui->checkBox_auto_initialize->isChecked();
}

int DhLceWidget::GetSlaveAddress() {
  return ui->spinBox_lce_address->value();
}

void DhLceWidget::SetSlaveEditBoxEnable(bool is_enable) {
  ui->spinBox_lce_address->setEnabled(is_enable);
}

void DhLceWidget::InitActions() {
  connect(ui->btn_initialize, &QPushButton::clicked, this, [this] () {
    emit SignalsLceInitialize();
  });

  connect(ui->doubleSpinBox_linear_position, &QDoubleSpinBox::editingFinished,
          this, [this] () {
    int value = ui->doubleSpinBox_linear_position->value() * 100;
    emit SignalsLinear_PositionEdited(value);
  });

  connect(ui->btn_linear_test_1, &QPushButton::clicked, this, [this] () {
    int value = ui->doubleSpinBox_linear_test_1->value() * 100;
    emit SignalsLinear_PositionEdited(value);
  });

  connect(ui->btn_linear_test_2, &QPushButton::clicked, this, [this] () {
    int value = ui->doubleSpinBox_linear_test_2->value() * 100;
    emit SignalsLinear_PositionEdited(value);
  });

  connect(ui->btn_linear_test_3, &QPushButton::clicked, this, [this] () {
    int value = ui->doubleSpinBox_linear_test_3->value() * 100;
    emit SignalsLinear_PositionEdited(value);
  });

  connect(ui->spinBox_linear_force, &QSpinBox::editingFinished,
          this, [this] () {
    emit SignalsLinear_ForceEdited(ui->spinBox_linear_force->value());
  });

  connect(ui->spinBox_linear_speed, &QSpinBox::editingFinished,
          this, [this] () {
    emit SignalsLinear_SpeedEdited(ui->spinBox_linear_speed->value());
  });


}

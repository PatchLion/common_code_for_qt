#include "SliderForm.h"
#include "ui_SliderForm.h"
#include "MonitorManager.h"
#include "Defines.h"
SliderForm::SliderForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SliderForm)
{
    ui->setupUi(this);
}

SliderForm::~SliderForm()
{
    delete ui;
}

void SliderForm::on_horizontalSliderValue1_valueChanged(int value)
{
	KVMonitorManager().setMonitoringValue(Value1, value);
}

void SliderForm::on_horizontalSliderValue2_valueChanged(int value)
{
	KVMonitorManager().setMonitoringValue(Value2, value);
}

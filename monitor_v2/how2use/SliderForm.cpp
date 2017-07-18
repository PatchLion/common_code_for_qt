#include "SliderForm.h"
#include "ui_SliderForm.h"
#include "Defines.h"

SliderForm::SliderForm(const QString& groupID, QWidget *parent) :
    QWidget(parent)
	, ui(new Ui::SliderForm)
	, m_groupID(groupID)
{
    ui->setupUi(this);

	for (int i = 0; i < kWeeklyName.size(); i++)
	{
		ui->comboBoxWeekly->addItem(kWeeklyName[i]);
	}
	ui->comboBoxWeekly->setCurrentIndex(TestParams::defaultValue<EWeekly>(m_groupID, Param_Weekly));

	for (int i = 0; i < kCountries.size(); i++)
	{
		ui->comboBoxCountries->addItem(kCountries[i]);
	}
	ui->comboBoxCountries->setCurrentText(TestParams::defaultValue<QString>(m_groupID, Param_Counties));

	const int min = TestParams::minimum<int>(m_groupID, Param_DegreeRange);
	const int max = TestParams::maximum<int>(m_groupID, Param_DegreeRange);
	const int defaultV = TestParams::defaultValue<int>(m_groupID, Param_DegreeRange);

	ui->horizontalSliderIntRange->setRange(min, max);
	ui->horizontalSliderIntRange->setValue(defaultV);

	ui->spinBoxInt->setRange(-10000, 10000);
	ui->spinBoxInt->setValue(TestParams::defaultValue<int>(m_groupID, Param_Int));

	ui->spinBoxStruct->setRange(-10000, 10000);
	ui->spinBoxStruct->setValue(TestParams::defaultValue<stTest>(m_groupID, Param_Other).value);
}

SliderForm::~SliderForm()
{
    delete ui;
}

void SliderForm::on_comboBoxWeekly_currentIndexChanged(int index)
{
	TestParams::setValue<EWeekly>(m_groupID, Param_Weekly, static_cast<EWeekly>(index));
}

void SliderForm::on_horizontalSliderIntRange_valueChanged(int value)
{
	TestParams::setValue<int>(m_groupID, Param_DegreeRange, value);
}

void SliderForm::on_spinBoxInt_valueChanged(int value)
{
	TestParams::setValue<int>(m_groupID, Param_Int, value);
}

void SliderForm::on_comboBoxCountries_currentIndexChanged(int index)
{
	TestParams::setValue<QString>(m_groupID, Param_Counties, kCountries[index]);
}

void SliderForm::on_spinBoxStruct_valueChanged(int value)
{
	TestParams::setValue<stTest>(m_groupID, Param_Other, stTest(value));
}

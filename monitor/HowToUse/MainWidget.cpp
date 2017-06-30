#include "MainWidget.h"
#include <QtGui>

#include "Defines.h"
CMainWidget::CMainWidget(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);

	//setFixedSize(800, 600);

	Monitor::Keys keys;
	keys << Value1;
	keys << Value2;

	setMonitoringKeys(keys);

	lineEditValue1->setReadOnly(true);
	lineEditValue2->setReadOnly(true);
	m_sliderForm.show();
}

CMainWidget::~CMainWidget()
{
	
}

void CMainWidget::onMonitoringValueChanged(const Monitor::KeyValuePairs& kvs)
{
	if (kvs.contains(Value1))
	{
		lineEditValue1->setText(QString::number(kvs[Value1].toInt()));
	}
	if (kvs.contains(Value2))
	{
		lineEditValue2->setText(QString::number(kvs[Value2].toInt()));
	}
}

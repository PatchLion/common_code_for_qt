#include "MainWidget.h"
#include <QtGui>
#include <QtWidgets>
#include "Defines.h"

CMainWidget::CMainWidget(const QString& groupID, QWidget *parent)
	: QWidget(parent)
	, m_groupID(groupID)
{

	setupUi(this);

	TestParams::addMonitor(m_groupID, this);

	QList<ParamTypes> listTypes;
	listTypes << Param_Counties;
	listTypes << Param_Weekly;
	listTypes << Param_Other;
	listTypes << Param_DegreeRange;
	listTypes << Param_Int;
	setMonitParamTypes(listTypes);
}

CMainWidget::~CMainWidget()
{
	
}

void CMainWidget::log(const QString& msg)
{
	if (!msg.isEmpty())
	{
		QListWidgetItem* item = new QListWidgetItem(msg);
		listWidgetLog->addItem(item);
		listWidgetLog->scrollToItem(item);
	}
	
}

void CMainWidget::onParamsChanged(const QVariant& key, const QVariant& value)
{
	switch (key.toInt())
	{
	case Param_Counties:
	{
		log(QString::fromLocal8Bit("��ѡ�Ĺ�����: %1 [Ĭ��: %2]").arg(value.toString()).arg(TestParams::defaultValue<QString>(m_groupID, Param_Counties)));
	}
	break;
	case Param_Weekly:
	{
		const int index = TestParams::defaultValue<EWeekly>(m_groupID, Param_Weekly);

		log(QString::fromLocal8Bit("������%1 [Ĭ��: %2]").arg(kWeeklyName[value.toInt()]).arg(kWeeklyName[index]));
	}
		break;
	case Param_Int:
	{
		log(QString::fromLocal8Bit("Intֵ�仯: %1 [Ĭ��: %2]").arg(value.toInt()).arg(TestParams::defaultValue<int>(m_groupID, Param_Int)));
	}
		break;
	case Param_Other:
	{
		log(QString::fromLocal8Bit("Structֵ�仯: %1 [Ĭ��: %2]").arg(value.value<stTest>().value).arg(TestParams::defaultValue<stTest>(m_groupID, Param_Other).value));
	}
	break;
	case Param_DegreeRange:
	{
		const int min = TestParams::minimum<int>(m_groupID, Param_DegreeRange);
		const int max = TestParams::maximum<int>(m_groupID, Param_DegreeRange);
		const int v = TestParams::value<int>(m_groupID, Param_DegreeRange);
		Q_ASSERT(v == value.toInt());
		const double percent = TestParams::percent<int>(m_groupID, Param_DegreeRange);
		log(QString::fromLocal8Bit("����(��Χ)ֵ�仯: %1 (ȡֵ��Χ: %2 - %3) (�ٷֱ�: %4%)  [Ĭ��: %5]").arg(v).arg(min).arg(max).arg(percent * 100, 0, 'f', 0).arg(TestParams::defaultValue<int>(m_groupID, Param_DegreeRange)));
	}
		break;
	}
}

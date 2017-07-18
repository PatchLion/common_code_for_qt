#ifndef MainWidget_H
#define MainWidget_H
#include <QtWidgets/QWidget>
#include "ui_MainWidget.h"
#include "SliderForm.h"
#include "Defines.h"
#include "ParamsMonitorIncludes.h"

class CMainWidget : public QWidget, public Ui::MainWidget, public CParamWithValuesMonitor<ParamTypes>
{
    Q_OBJECT
public:
	CMainWidget(const QString& groupID, QWidget *parent = 0);
    ~CMainWidget();

protected:
	//参数改变
	virtual void onParamsChanged(const QVariant& key, const QVariant& value);

private:
	void log(const QString& msg);

private:
	QString m_groupID;
};

#endif // MainWidget_H

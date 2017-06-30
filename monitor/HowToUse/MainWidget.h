#ifndef MainWidget_H
#define MainWidget_H
#include <QtWidgets/QWidget>
#include "ui_MainWidget.h"
#include "Monitor.h"
#include "SliderForm.h"
class CMainWidget : public QWidget, public Ui::MainWidget, public Monitor::CMonitor
{
    Q_OBJECT
public:
    CMainWidget(QWidget *parent = 0);
    ~CMainWidget();

protected:
	//监控的值改变
	virtual void onMonitoringValueChanged(const Monitor::KeyValuePairs& kvs);

private:
	SliderForm m_sliderForm;
};

#endif // MainWidget_H

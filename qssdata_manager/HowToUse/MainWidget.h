#ifndef MainWidget_H
#define MainWidget_H
#include <QtWidgets/QWidget>
#include "ui_MainWidget.h"
#include "QSSDataUser.h"

class CMainWidget : public QWidget, public Ui::MainWidget, public QSSData::QSSDataUser
{
    Q_OBJECT
public:
    CMainWidget(QWidget *parent = 0);
    ~CMainWidget();

protected Q_SLOTS:
	void on_pushButtonRefreshQSS_clicked(bool checked);
	void on_pushButtonClear_clicked(bool checked);

protected:
	void refreshStyleSheet();
};

#endif // MainWidget_H

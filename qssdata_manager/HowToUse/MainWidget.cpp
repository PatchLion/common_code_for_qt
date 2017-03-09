#include "MainWidget.h"
#include <QtGui>
#include "QSSDataRefresher.h"
#include "QSSDataManager.h"

CMainWidget::CMainWidget(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);

	setFixedSize(800, 600);

	refreshStyleSheet();
}

CMainWidget::~CMainWidget()
{
	
}

void CMainWidget::refreshStyleSheet()
{
	pushButtonOK->setStyleSheet(LoadQSSData("pushbutton_main_okbutton"));
	pushButtonClose->setStyleSheet(LoadQSSData("pushbutton_main_closebutton"));
	radioButtonOptionA->setStyleSheet(LoadQSSData("radiobutton_main_style1"));
	radioButtonOptionB->setStyleSheet(LoadQSSData("radiobutton_main_style1"));
	comboBoxStyle1->setStyleSheet(LoadQSSData("combobox_mian_style1"));
}

void CMainWidget::on_pushButtonRefreshQSS_clicked(bool checked)
{
	QSSDataManager().reloadQSS("./resources/styles");
	QSSRefresher().refresh();
}

void CMainWidget::on_pushButtonClear_clicked(bool checked)
{
	QSSDataManager().clear();
	QSSRefresher().refresh();
}
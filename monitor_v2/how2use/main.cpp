#include <QApplication>
#include "MainWidget.h"
#include "SliderForm.h"



int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	const QString groupID = TestParams::createMonitGroup();

	CMainWidget mainWidget(groupID);
	mainWidget.show();

	CMainWidget mainWidget2(groupID);
	mainWidget2.show();

	CMainWidget mainWidget3(groupID);
	mainWidget3.show();

	SliderForm form(groupID);
	form.show();

	return app.exec();
}
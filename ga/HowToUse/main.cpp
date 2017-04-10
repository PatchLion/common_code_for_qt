#include <QCoreApplication>
#include "GAStatistics.h"

int main(int argc, char** argv)
{
	QCoreApplication app(argc, argv);

	GAStatistics::setClientID("uuid");
	GAStatistics::setTrackingID("tracking-id");

	GAStatisticsInstance().sendEvent("category", "action", "label", 1);
	GAStatisticsInstance().sendPageView("page", "title");

	return app.exec();
}
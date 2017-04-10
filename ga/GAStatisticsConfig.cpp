#include "GAStatisticsConfig.h"

namespace GAStatistics
{
	QString g_trackingID;
	QString g_clientID;
}

void GAStatistics::setTrackingID(const QString& id)
{
	g_trackingID = id;
}

QString GAStatistics::trackingID()
{
	return g_trackingID;
}

void GAStatistics::setClientID(const QString& id)
{
	g_clientID = id;
}

QString GAStatistics::clientID()
{
	return g_clientID;
}

#ifndef GAStatisticsConfig_h__
#define GAStatisticsConfig_h__

#include <QtCore>

//ͳ������
namespace GAStatistics
{
	//tracking id
	void setTrackingID(const QString& id);
	QString trackingID();

	//client id
	void setClientID(const QString& id);
	QString clientID();
}
#endif // GAStatisticsConfig_h__

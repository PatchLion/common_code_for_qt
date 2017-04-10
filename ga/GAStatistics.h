#ifndef GAStatistics_h__
#define GAStatistics_h__

#include <QtCore>
#include "Singleton.h"
#include "GAStatisticsConfig.h"

class QNetworkAccessManager;
class CGAStatistics : public QObject
{
	Q_OBJECT

public:
	CGAStatistics(QObject *parent = 0);
	~CGAStatistics();

public:
	//pageview
	void sendPageView(const QString& page, const QString& title);

	//event
	void sendEvent(const QString& category, const QString& action, const QString& label, int value);

Q_SIGNALS:
	void sigStatisticsPage(const QString& page, const QString& title);
	void sigStatisticsEvent(const QString& category, const QString& action, const QString& label, int value);

private Q_SLOTS:
	void onStatisticsPage(const QString& page, const QString& title);
	void onStatisticsEvent(const QString& category, const QString& action, const QString& label, int value);

protected:
	//
	QNetworkAccessManager *networkManager();

private:
	QString hostName() const;

private:
	QNetworkAccessManager *m_networkManager;
};

#define GAStatisticsInstance() Singleton<CGAStatistics>::instance()
#endif // GAStatistics_h__

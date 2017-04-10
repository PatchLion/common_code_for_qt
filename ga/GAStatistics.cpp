#include "GAStatistics.h"
#include <QtNetwork>

const char*  kGoogleAnalyticsServerUrl = "http://www.google-analytics.com/collect";

CGAStatistics::CGAStatistics(QObject *parent /*= 0*/)
	:QObject(parent)
	, m_networkManager(0)
{
	connect(this, &CGAStatistics::sigStatisticsEvent, this, &CGAStatistics::onStatisticsEvent, Qt::QueuedConnection);
	connect(this, &CGAStatistics::sigStatisticsPage, this, &CGAStatistics::onStatisticsPage, Qt::QueuedConnection);
}

CGAStatistics::~CGAStatistics()
{

}

void CGAStatistics::sendPageView(const QString& page, const QString& title)
{
	emit sigStatisticsPage(page, title);
}

void CGAStatistics::sendEvent(const QString& category, const QString& action, const QString& label, int value)
{
	emit sigStatisticsEvent(category, action, label, value);
  
}

QString CGAStatistics::hostName() const
{
	QString hostName = QHostInfo::localHostName() + "." + QHostInfo::localDomainName();

	return hostName;
}

void CGAStatistics::onStatisticsPage(const QString& page, const QString& title)
{
	QUrl url(kGoogleAnalyticsServerUrl);
	QNetworkRequest req(url);
	req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

	// Build up the query parameters.
	QUrlQuery query;
	query.addQueryItem("v", "1"); // Version
	query.addQueryItem("tid", GAStatistics::trackingID()); // Tracking ID - use value assigned to you by Google Analytics
	query.addQueryItem("cid", GAStatistics::clientID()); // Client ID
	query.addQueryItem("t", "pageview"); // Pageview hit type
	query.addQueryItem("dh", hostName()); // Document hostname
	query.addQueryItem("dp", page); // Page
	query.addQueryItem("dt", title); // Title

	QByteArray data;
	data.append(query.query());

	qDebug() << "GA pageview: " << data; // Output for debug purposes.

	QNetworkReply* reply = networkManager()->post(req, data);

	if (reply)
	{
		connect(reply, &QNetworkReply::finished, reply, &QNetworkReply::deleteLater);
	}
}

void CGAStatistics::onStatisticsEvent(const QString& category, const QString& action, const QString& label, int value)
{
	QUrl url(kGoogleAnalyticsServerUrl);
	QNetworkRequest req(url);
	req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

	// Build up the query parameters.
	QUrlQuery query;
	query.addQueryItem("v", "1"); // Version
	query.addQueryItem("tid", GAStatistics::trackingID()); // Tracking ID - use value assigned to you by Google Analytics
	query.addQueryItem("cid", GAStatistics::clientID()); // Client ID
	query.addQueryItem("t", "event"); // Event hit type
	query.addQueryItem("ec", category); // Event category
	query.addQueryItem("ea", action); // Event action
	query.addQueryItem("el", label); // Event label
	query.addQueryItem("ev", QString::number(value)); // Event value

	QByteArray data;
	data.append(query.query());
	qDebug() << "send GA event: " << data; // Output for debug purposes.
	QNetworkReply* reply = networkManager()->post(req, data);

	if (reply)
	{
		connect(reply, &QNetworkReply::finished, reply, &QNetworkReply::deleteLater);
	}
}

QNetworkAccessManager * CGAStatistics::networkManager()
{
	if (!m_networkManager)
	{
		m_networkManager = new QNetworkAccessManager(this);
	}

	return m_networkManager;
}
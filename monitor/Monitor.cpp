#include "Monitor.h"
#include <QtCore>
#include "MonitorManager.h"

Monitor::CMonitor::CMonitor()
{
	KVMonitorManager().addMonitor(this);
}

Monitor::CMonitor::~CMonitor()
{
	KVMonitorManager().removeMonitor(this);
}

void Monitor::CMonitor::setMonitoringValue(const Monitor::KeyValuePairs& kvs)
{
	KVMonitorManager().setMonitoringValueByMonitor(kvs, this);
}

void Monitor::CMonitor::setMonitoringValue(const Monitor::Key& key, const Monitor::Value& value)
{
	KVMonitorManager().setMonitoringValueByMonitor(key, value, this);
}


#include "MonitorManager.h"
#include <QtCore>
#include "Monitor.h"


Monitor::CMonitorManager::CMonitorManager(const Monitor::KeyValuePairs& init /*= Monitor::KeyValuePairs()*/)
	: c_initKVs(init)
	, m_kvs(init)
{

}

Monitor::CMonitorManager::~CMonitorManager()
{

}

void Monitor::CMonitorManager::setMonitoringValueByMonitor(const Monitor::KeyValuePairs& kvs, Monitor::CMonitor* monitor)
{
	Monitor::KeyValuePairs changedKVs;
	Monitor::KeyValuePairs::const_iterator kvItor = kvs.begin();

	for (kvItor; kvs.end() != kvItor; kvItor++)
	{
		const Monitor::Key k = kvItor.key();
		Monitor::KeyValuePairs::iterator itor = m_kvs.find(k);
		if ((m_kvs.end() != itor && (itor.value() != kvItor.value())) //key-value 存在 但是发送改变
			|| m_kvs.end() == itor) //key-value 不存在
		{
				m_kvs[k] = kvItor.value();
				changedKVs[k] = kvItor.value();
		}
	}

	if (!changedKVs.isEmpty())
	{
		Q_FOREACH(Monitor::CMonitor* m, m_monitors)
		{
			if (m && (!monitor || (monitor && m != monitor)))
			{
				notifyMonitor(changedKVs, m);
			}
		}
	}

}

void Monitor::CMonitorManager::setMonitoringValueByMonitor(const Monitor::Key& key, const Monitor::Value& value, Monitor::CMonitor* monitor)
{
	Monitor::KeyValuePairs kvs;
	kvs[key] = value;
	setMonitoringValueByMonitor(kvs, monitor);
}

void Monitor::CMonitorManager::setMonitoringValue(const Monitor::KeyValuePairs& kvs)
{
	setMonitoringValueByMonitor(kvs, 0);
}

void Monitor::CMonitorManager::setMonitoringValue(const Monitor::Key& key, const Monitor::Value& value)
{
	setMonitoringValueByMonitor(key, value, 0);
}

Monitor::Value Monitor::CMonitorManager::value(const Monitor::Key& key)
{
	if (m_kvs.contains(key))
	{
		return m_kvs[key];
	}

	return Monitor::Value();
}


bool Monitor::CMonitorManager::isKeyExist(const Monitor::Key& key) const
{
	return m_kvs.contains(key);
}


void Monitor::CMonitorManager::addMonitor(Monitor::CMonitor* monitor)
{
	if (monitor)
	{
		Monitor::Monitors::iterator itor = qFind(m_monitors.begin(), m_monitors.end(), monitor);

		if (m_monitors.end() == itor)
		{
			m_monitors.append(monitor);
		}
	}
}

void Monitor::CMonitorManager::removeMonitor(Monitor::CMonitor* monitor)
{
	if (monitor)
	{
		Monitor::Monitors::iterator itor = qFind(m_monitors.begin(), m_monitors.end(), monitor);

		if (m_monitors.end() != itor)
		{
			m_monitors.erase(itor);
		}
	}
}

void Monitor::CMonitorManager::notifyMonitor(const Monitor::KeyValuePairs& kvs, Monitor::CMonitor* monitor)
{
	if (!monitor)
	{
		return;
	}

	Monitor::KeyValuePairs changedKVs;
	Monitor::KeyValuePairs::const_iterator kvItor = kvs.begin();

	for (kvItor; kvs.end() != kvItor; kvItor++)
	{
		const int k = kvItor.key();

		//判断是否监控该参数
		if (monitor->monitoringKeys().contains(k))
		{
			changedKVs.insert(k, kvItor.value());
		}
	}

	if (!changedKVs.isEmpty())
	{
		monitor->onMonitoringValueChanged(changedKVs);
	}
}

void Monitor::CMonitorManager::reset()
{
	setMonitoringValue(c_initKVs); //用于触发参数改变通知(如果有)
	m_kvs = c_initKVs;
}

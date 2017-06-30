//参数监控者
#ifndef Monitor_h__
#define Monitor_h__

#include "MonitorDefines.h"

namespace Monitor
{
	class CMonitorManager;
	class CMonitor
	{
		friend class CMonitorManager;

	public:
		CMonitor();
		virtual ~CMonitor();

	public:
		//设置监控的Key类型
		void setMonitoringKeys(const Monitor::Keys& keys) { m_monitoringKeys = keys; }
		void setMonitoringKey(const Monitor::Key& key) { m_monitoringKeys.clear(); m_monitoringKeys << key; }

		//监控的key类型
		Monitor::Keys monitoringKeys() const { return m_monitoringKeys; }

	protected:
		//监控的值改变
		virtual void onMonitoringValueChanged(const Monitor::KeyValuePairs& kvs) { Q_UNUSED(kvs); }

		//设置参数
		void setMonitoringValue(const Monitor::KeyValuePairs& kvs);
		void setMonitoringValue(const Monitor::Key& key, const Monitor::Value& value);

	private:
		Keys m_monitoringKeys;
	};
}

#endif // Monitor_h__

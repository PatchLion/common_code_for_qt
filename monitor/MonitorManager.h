//参数监控者管理
#ifndef MonitorManager_h__
#define MonitorManager_h__

#include "MonitorDefines.h"
#include "Singleton.h"


namespace Monitor
{
	class CMonitor;
	class CMonitorManager
	{
		friend class CMonitor;
	public:
		CMonitorManager(const Monitor::KeyValuePairs& init = Monitor::KeyValuePairs());
		~CMonitorManager();

	public:
		//设置参数
		void setMonitoringValue(const Monitor::KeyValuePairs& kvs);
		void setMonitoringValue(const Monitor::Key& key, const Monitor::Value& value);

		//参数值
		Monitor::Value value(const Monitor::Key& key);

		//key是否存在
		bool isKeyExist(const Monitor::Key& key) const;

		//重置
		void reset();

	private:
		//监控者
		void addMonitor(Monitor::CMonitor* monitor);
		void removeMonitor(Monitor::CMonitor* monitor);

		//设置参数（带监控者自己的指针）
		void setMonitoringValueByMonitor(const Monitor::KeyValuePairs& kvs, Monitor::CMonitor* monitor);
		void setMonitoringValueByMonitor(const Monitor::Key& key, const Monitor::Value& value, Monitor::CMonitor* monitor);

		//通知监控者
		void notifyMonitor(const Monitor::KeyValuePairs& kvs, Monitor::CMonitor* monitor);

	private:
		const Monitor::KeyValuePairs c_initKVs;
		Monitor::KeyValuePairs m_kvs;
		Monitor::Monitors m_monitors;
	};
}
#define KVMonitorManager() Singleton<Monitor::CMonitorManager>::instance()
#endif // MonitorManager_h__

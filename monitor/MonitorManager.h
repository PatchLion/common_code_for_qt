//��������߹���
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
		//���ò���
		void setMonitoringValue(const Monitor::KeyValuePairs& kvs);
		void setMonitoringValue(const Monitor::Key& key, const Monitor::Value& value);

		//����ֵ
		Monitor::Value value(const Monitor::Key& key);

		//key�Ƿ����
		bool isKeyExist(const Monitor::Key& key) const;

		//����
		void reset();

	private:
		//�����
		void addMonitor(Monitor::CMonitor* monitor);
		void removeMonitor(Monitor::CMonitor* monitor);

		//���ò�������������Լ���ָ�룩
		void setMonitoringValueByMonitor(const Monitor::KeyValuePairs& kvs, Monitor::CMonitor* monitor);
		void setMonitoringValueByMonitor(const Monitor::Key& key, const Monitor::Value& value, Monitor::CMonitor* monitor);

		//֪ͨ�����
		void notifyMonitor(const Monitor::KeyValuePairs& kvs, Monitor::CMonitor* monitor);

	private:
		const Monitor::KeyValuePairs c_initKVs;
		Monitor::KeyValuePairs m_kvs;
		Monitor::Monitors m_monitors;
	};
}
#define KVMonitorManager() Singleton<Monitor::CMonitorManager>::instance()
#endif // MonitorManager_h__

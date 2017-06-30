//���������
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
		//���ü�ص�Key����
		void setMonitoringKeys(const Monitor::Keys& keys) { m_monitoringKeys = keys; }
		void setMonitoringKey(const Monitor::Key& key) { m_monitoringKeys.clear(); m_monitoringKeys << key; }

		//��ص�key����
		Monitor::Keys monitoringKeys() const { return m_monitoringKeys; }

	protected:
		//��ص�ֵ�ı�
		virtual void onMonitoringValueChanged(const Monitor::KeyValuePairs& kvs) { Q_UNUSED(kvs); }

		//���ò���
		void setMonitoringValue(const Monitor::KeyValuePairs& kvs);
		void setMonitoringValue(const Monitor::Key& key, const Monitor::Value& value);

	private:
		Keys m_monitoringKeys;
	};
}

#endif // Monitor_h__

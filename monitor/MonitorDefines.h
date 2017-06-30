#ifndef MonitorDefines_h__
#define MonitorDefines_h__

#include <QtCore>

namespace Monitor
{
	class CMonitor;
	typedef int Key;
	typedef QVariant Value;
	typedef QList<Key> Keys;
	typedef QMap<Key, Value> KeyValuePairs;
	typedef QList<Monitor::CMonitor*> Monitors;
}

#endif // MonitorDefines_h__

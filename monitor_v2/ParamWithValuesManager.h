#ifndef ParamWithValuesManager_h__
#define ParamWithValuesManager_h__


#include "ParamWithValues.h"
#include "Singleton.h"

class CParamWithValuesManager
{
public:
	CParamWithValuesManager(){}
	virtual ~CParamWithValuesManager(){}

	//参数监控组
	template <class K>
	QString createMonitGroup()
	{
		Params::CParamWithValues<K>* g = new Params::CParamWithValues<K>;
		groups<K>()[g->groupID()] = g;
		return g->groupID();
	}

	//
	template <class K>
	void releaseMonitGroup(const QString& id)
	{
		Params::CParamWithValues<K>* p = groups<K>()[id];
		SAFE_DELETE(p);
		groups<K>().remove(id);
	}

	template<class K, class V>
	V defaultValue(const QString& groupID, K key)
	{
		Params::CParamWithValues<K>* p = groups<K>()[groupID];

		Q_ASSERT_X(p, "object is null!", "p == null!");

		return p->defaultValue<V>(key);
	}

	//监控者
	template<class K>
	void addMonitor(const QString& groupID, CParamWithValuesMonitor<K>* monitor)
	{
		Params::CParamWithValues<K>* p = groups<K>()[groupID];

		Q_ASSERT_X(p, "object is null!", "p == null!");

		p->addMonitor(monitor);
	}
	template<class K>
	void removeMonitor(const QString& groupID, CParamWithValuesMonitor<K>* monitor)
	{
		Params::CParamWithValues<K>* p = groups<K>()[groupID];

		Q_ASSERT_X(p, "object is null!", "p == null!");

		p->removeMonitor(monitor);
	}

	template < class K, class VT>
	double defaultPercent(const QString& groupID, K key)
	{
		Params::CParamWithValues<K>* p = groups<K>()[groupID];

		Q_ASSERT_X(p, "object is null!", "p == null!");

		return p->defaultPercent<VT>(key);
	}

	template<class K, class V>
	V value(const QString& groupID, K key)
	{
		Params::CParamWithValues<K>* p = groups<K>()[groupID];

		Q_ASSERT_X(p, "object is null!", "p == null!");

		return p->value<V>(key);
	}
	//设置参数
	template <class K, class V>
	bool setValue(const QString& groupID, const K& key, const V& value, CParamWithValuesMonitor<K>* monitor = 0)
	{
		Params::CParamWithValues<K>* p = groups<K>()[groupID];

		Q_ASSERT_X(p, "object is null!", "p == null!");

		return p->setValue(key, value, monitor);
	}

	//
	template <class K, class V>
	void reset(const QString& groupID, const K& key)
	{
		Params::CParamWithValues<K>* p = groups<K>()[groupID];

		Q_ASSERT_X(p, "object is null!", "p == null!");

		if (p)
		{
			p->reset<V>();
		}
	}
	//最小值，只有有取值范围的值有效
	template<class K, class VT>
	double minimum(const QString& groupID, K key)
	{
		Params::CParamWithValues<K>* p = groups<K>()[groupID];

		Q_ASSERT_X(p, "object is null!", "p == null!");

		return	p->minimum<VT>(key);
	}
	//最大值，只有有取值范围的值有效
	template<class K, class VT>
	double maximum(const QString& groupID, K key)
	{
		Params::CParamWithValues<K>* p = groups<K>()[groupID];

		Q_ASSERT_X(p, "object is null!", "p == null!");

		return	p->maximum<VT>(key);
	}
	//百分比，只有有取值范围的值有效
	template<class K, class VT>
	double percent(const QString& groupID, K key) 
	{
		Params::CParamWithValues<K>* p = groups<K>()[groupID];

		Q_ASSERT_X(p, "object is null!", "p == null!");

		return	p->percent<VT>(key);
	}

	//设置参数（带监控者自己的指针）
	template <class K, class V>
	bool setParamWithMonitor(const QString& groupID, const K& key, const V& value, CParamWithValuesMonitor<K>* monitor)
	{
		return setValue<K, V>(groupID, key, value, monitor);
	}

	//重置
	template <class K>
	void reset(const QString& groupID)
	{
		Params::CParamWithValues<K>* p = groups<K>()[groupID];

		Q_ASSERT_X(p, "object is null!", "p == null!");

		p->resetAllParams();
	}

	template<class K>
	QMap<QString, Params::CParamWithValues<K>*>& groups() const
	{
		static QMap<QString, Params::CParamWithValues<K>* > g_groups;
		return g_groups;
	}
	
};

#define PVMInstance() Singleton<CParamWithValuesManager>::instance()
#endif // ParamWithValuesManager_h__

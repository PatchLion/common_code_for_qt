#ifndef ParamWithValues_h__
#define ParamWithValues_h__

#include <QtCore>
#include "ParamsMacroDefine.h"
#include "ParamsStructDefine.h"
#include "ParamWithValuesMonitor.h"

namespace Params
{
	template<class K>
	class CParamWithValues
	{
	public:
		CParamWithValues()
			: m_groupID(QUuid::createUuid().toString())
		{
			initParams();
		}


	public:
		//��ʼ����������ƫ�ػ�
		void initParams() {}

		//���ò�������ƫ�ػ�
		void resetAllParams() {}

		//
		QString groupID() const { return m_groupID; }

		//Ĭ��ֵ
		template<class VT>
		VT defaultValue(K key)
		{
			Params::CParamValue<VT>* p = param<VT>(key);

			Q_ASSERT(p);

			return p->defaultValue();
		}

		//����ֵ
		template<class VT>
		bool setValue(K key, const VT& t, CParamWithValuesMonitor<K>* monitor)
		{
			Params::CParamValue<VT>* p = param<VT>(key);

			Q_ASSERT(p);

			if (p->setValue(t))
			{
				notifyMonitor(key, t, monitor);
				return true;
			}
			return false;
		}

		//ֵ
		template<class VT>
		VT value(K key)
		{
			Params::CParamValue<VT>* p = param<VT>(key);

			Q_ASSERT(p);

			return p->value();
		}

		//�ٷֱȣ�ֻ����ȡֵ��Χ��ֵ��Ч
		template<class VT>
		double percent(K key) 
		{
			Params::CParamValue<VT>* p = param<VT>(key);

			Q_ASSERT(p);
			Q_ASSERT(p->type() == ParamType_Range);

			return ((Params::CRangeParamValue<VT>*)p)->percent();
		}



		//Ĭ��ֵ�İٷֱȣ�ֻ����ȡֵ��Χ��ֵ��Ч
		template<class VT>
		double defaultPercent(K key)
		{
			Params::CParamValue<VT>* p = param<VT>(key);

			Q_ASSERT(p);
			Q_ASSERT(p->type() == ParamType_Range);

			return ((Params::CRangeParamValue<VT>*)p)->defaultPercent();
		}


		//���ݰٷֱ�ȡֵ��ֻ����ȡֵ��Χ��ֵ��Ч
		template<class VT>
		VT valueByPercent(K key, double percent)
		{
			Params::CParamValue<VT>* p = param<VT>(key);

			Q_ASSERT(p);
			Q_ASSERT(p->type() == ParamType_Range);

			return ((Params::CRangeParamValue<VT>*)p)->valueByPercent(percent);
		}

		//��Сֵ��ֻ����ȡֵ��Χ��ֵ��Ч
		template<class VT>
		double minimum(K key)
		{
			Params::CParamValue<VT>* p = param<VT>(key);

			Q_ASSERT(p);
			Q_ASSERT(p->type() == ParamType_Range);

			return ((Params::CRangeParamValue<VT>*)p)->minimum();
		}
		//���ֵ��ֻ����ȡֵ��Χ��ֵ��Ч
		template<class VT>
		double maximum(K key)
		{
			Params::CParamValue<VT>* p = param<VT>(key);

			Q_ASSERT(p);
			Q_ASSERT(p->type() == ParamType_Range);

			return ((Params::CRangeParamValue<VT>*)p)->maximum();
		}

		//
		virtual EParamType type() const { return ParamType_Normal; }

		//
		static bool isValueEqual(const K& src, const K&dest) { return src == dest; }

		//�����
		void addMonitor(CParamWithValuesMonitor<K>* monitor)
		{
			Q_ASSERT(monitor);

			QList<CParamWithValuesMonitor<K>*>& listMonitor = Params::CParamWithValues<K>::monitors(this);

			if (!listMonitor.contains(monitor))
			{
				listMonitor << monitor;
			}
		}

		void removeMonitor(CParamWithValuesMonitor<K>* monitor)
		{
			if (monitor)
			{
				QList<CParamWithValuesMonitor<K>*>& listMonitor = Params::CParamWithValues<K>::monitors(this);

				if (listMonitor.contains(monitor))
				{
					listMonitor.removeOne(monitor);
				}
			}
		}

		//�������в���
		template<class VT>
		void reset()
		{
			Q_FOREACH(Params::CParamValue<VT>* param, paramMap<VT>(this).values())
			{
				if (param)
				{
					param->reset();
				}
			}
		}
	protected:
		//��Ӳ���
		template <class VT>
		bool addParam(K key, Params::CParamValue<VT>* param)
		{
			Q_ASSERT(param);

			if (isKeyExist<VT>(key))
			{
				qWarning() << QString("Key: %1 exist!").arg(key);
				return false;
			}

			QMap<K, Params::CParamValue<VT>*>& mapValues = paramMap<VT>(this);

			mapValues[key] = param;

			return true;
		}

		static QList<CParamWithValuesMonitor<K>*>& monitors(CParamWithValues<K>* obj)
		{
			Q_ASSERT(obj);

			static QMap<CParamWithValues<K>*, QList<CParamWithValuesMonitor<K>*>> maps;

			if (!maps.contains(obj))
			{
				maps[obj] = QList<CParamWithValuesMonitor<K>*>();
			}

			return maps[obj];
		}

		template<class V>
		void notifyMonitor(const K& key, const V& value, CParamWithValuesMonitor<K>* sender)
		{
			QList<CParamWithValuesMonitor<K>*>& listMonitor = Params::CParamWithValues<K>::monitors(this);

			Q_FOREACH (CParamWithValuesMonitor<K>* monitor, listMonitor)
			{
				if (monitor && monitor->monitParamTypes().contains(key)
					&& (!sender || (sender && monitor != sender)))
				{
					monitor->onParamsChanged(QVariant::fromValue(key), QVariant::fromValue(value));
				}
			}
		}

	private:
		//����ӳ���
		template<class VT> 
		static QMap<K, Params::CParamValue<VT>*>& paramMap(CParamWithValues<K>* obj)
		{
			Q_ASSERT(obj);

			static QMap<CParamWithValues<K>*, QMap<K, Params::CParamValue<VT>*>> totalmaps;
			if (!totalmaps.contains(obj))
			{
				totalmaps[obj] = QMap<K, Params::CParamValue<VT>*>();
			}

			return totalmaps[obj];
		}

		//��ȡ����
		template<class VT> 
		Params::CParamValue<VT>* param(K key)
		{
			QMap<K, Params::CParamValue<VT>*>& mapValues = paramMap<VT>(this);

			QMap<K, Params::CParamValue<VT>*>::iterator paramItor = mapValues.begin();
			for (paramItor; mapValues.end() != paramItor; paramItor++)
			{
				if (paramItor.key() == key)
				{
					return paramItor.value();
				}
			}

			return 0;
		}

		//Key�Ƿ����
		template<class VT> 
		bool isKeyExist(K key)
		{
			QMap<K, Params::CParamValue<VT>*>& mapValues = paramMap<VT>(this);

			return mapValues.contains(key);
		}

	private:
		const QString m_groupID;
	};

	bool CParamWithValues<double>::isValueEqual(const double& src, const double&dest){ return FLOAT_VALUE_EQUAL(src, dest); }
	bool CParamWithValues<float>::isValueEqual(const float& src, const float&dest){ return FLOAT_VALUE_EQUAL(src, dest); }

}
#endif // ParamWithValues_h__

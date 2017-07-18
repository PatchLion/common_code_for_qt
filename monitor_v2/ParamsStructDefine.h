#ifndef ParamsStructDefine_h__
#define ParamsStructDefine_h__

#include "QtCommonMacros.h"

namespace Params
{

	enum EParamType
	{
		ParamType_Normal,
		ParamType_Range,
		ParamType_List,
	};

	//��ͨ����
	template <class V>
	class CParamValue
	{
	public:
		CParamValue<V>(const V& def)
			: m_defaultValue(def)
			, m_value(def){}

	public:
		//Ĭ��ֵ
		V defaultValue() const{ return m_defaultValue; }

		//����ֵ�����óɹ�����true������ʧ�ܣ�ֵδ�����ı䣩����false
		bool setValue(const V& t);
		V value() const { return m_value; }

		//����
		void reset() { m_value = m_defaultValue; }

		//
		virtual EParamType type() const { return ParamType_Normal; }

	protected:
		//ֵ�Ƿ���ֵ��Χ��
		virtual bool isValueInRange(const V& value) const { return true; }

	private:
		const V m_defaultValue;
		V m_value;
	};

	//ȡ��Χ���磨0~255��
	template <class V>
	class CRangeParamValue : public CParamValue<V>
	{
	public:
		CRangeParamValue<V>(const V&min, const V&def, const V& max)
			: CParamValue<V>(def)
		{ setRange(min, max);	}

	public:
		//��Χ
		void setRange(const V& min, const V& max);
	
		//��Сֵ
		V minimum() const { return m_minimum; }
		
		//���ֵ
		V maximum() const { return m_maximum; }

		//��ǰֵ���ڰٷֱ�
		double percent() const;
		double defaultPercent()  const { return percentByValue(defaultValue()); }

		//
		V valueByPercent(double percent) const;

		//Percent
		double percentByValue(const V& value) const;

		//ֵ�Ƿ���ֵ��Χ��
		virtual bool isValueInRange(const V& value) const;

		//
		virtual EParamType type() const { return ParamType_Range; }

	private:
		V m_minimum;  //��Сֵ
		V m_maximum;	//���ֵ
	};


	//��Χ�б����� ["��һ", "�ܶ�", "����", "����", "����", "����", "����"]
	template <class V>
	class CListParamValue : public CParamValue<V>
	{
	public:
		CListParamValue<V>(const QList<V>&listvalue, const V& def)
			: CParamValue<V>(def)
			, m_listRange(listvalue){}

		//
		virtual EParamType type() const { return ParamType_List; }

		QList<V> listRange() const { return m_listRange; }

	protected:
		//ֵ�Ƿ���ֵ��Χ��
		virtual bool isValueInRange(const V& value) const;


	private:
		QList<V> m_listRange; //ȡֵ��Χ
	};
}

#include "ParamsStructDefine.inl"
#endif // ParamsStructDefine_h__

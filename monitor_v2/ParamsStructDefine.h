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

	//普通参数
	template <class V>
	class CParamValue
	{
	public:
		CParamValue<V>(const V& def)
			: m_defaultValue(def)
			, m_value(def){}

	public:
		//默认值
		V defaultValue() const{ return m_defaultValue; }

		//设置值，设置成功返回true，设置失败（值未发生改变）返回false
		bool setValue(const V& t);
		V value() const { return m_value; }

		//重置
		void reset() { m_value = m_defaultValue; }

		//
		virtual EParamType type() const { return ParamType_Normal; }

	protected:
		//值是否在值范围中
		virtual bool isValueInRange(const V& value) const { return true; }

	private:
		const V m_defaultValue;
		V m_value;
	};

	//取范围，如（0~255）
	template <class V>
	class CRangeParamValue : public CParamValue<V>
	{
	public:
		CRangeParamValue<V>(const V&min, const V&def, const V& max)
			: CParamValue<V>(def)
		{ setRange(min, max);	}

	public:
		//范围
		void setRange(const V& min, const V& max);
	
		//最小值
		V minimum() const { return m_minimum; }
		
		//最大值
		V maximum() const { return m_maximum; }

		//当前值所在百分比
		double percent() const;
		double defaultPercent()  const { return percentByValue(defaultValue()); }

		//
		V valueByPercent(double percent) const;

		//Percent
		double percentByValue(const V& value) const;

		//值是否在值范围中
		virtual bool isValueInRange(const V& value) const;

		//
		virtual EParamType type() const { return ParamType_Range; }

	private:
		V m_minimum;  //最小值
		V m_maximum;	//最大值
	};


	//范围列表，例如 ["周一", "周二", "周三", "周四", "周五", "周六", "周日"]
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
		//值是否在值范围中
		virtual bool isValueInRange(const V& value) const;


	private:
		QList<V> m_listRange; //取值范围
	};
}

#include "ParamsStructDefine.inl"
#endif // ParamsStructDefine_h__

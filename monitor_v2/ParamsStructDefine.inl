#include "ParamsStructDefine.h"

#define VALUE_TO_PERCENT(min, value, max) ((double)(value - min) / (double)(max - min))
#define PERCENT_TO_VALUE(min, percent, max) (min + (double)(max - min) * percent)

template <class V>
bool Params::CParamValue<V>::setValue(const V& t)
{
	if (isValueInRange(t))
	{
		m_value = t;
		return true;
	}
	else
	{
		return false;
	}
}

template <class V>
void Params::CRangeParamValue<V>::setRange(const V& min, const V& max)
{
	if (min < max)
	{
		m_minimum = min;
		m_maximum = max;
	}
	else
	{
		m_minimum = max;
		m_maximum = min;
	}
}


template <class V>
bool Params::CRangeParamValue<V>::isValueInRange(const V& value) const
{
	return (value >= minimum() && value <= maximum());
}

template <class V>
bool Params::CListParamValue<V>::isValueInRange(const V& value) const
{
	return m_listRange.contains(value);
}


template <class V>
double Params::CRangeParamValue<V>::percent() const
{
	return percentByValue(value());
}

template <class V>
double Params::CRangeParamValue<V>::percentByValue(const V& value) const
{
	return VALUE_TO_PERCENT(minimum(), value, maximum());
}

template <class V>
V Params::CRangeParamValue<V>::valueByPercent(double percent) const
{
	return PERCENT_TO_VALUE(minimum(), percent, maximum());
}

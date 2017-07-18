#ifndef Defines_h__
#define Defines_h__

#include "ParamsMonitorIncludes.h"

static const QStringList kWeeklyName = { QString::fromLocal8Bit("����һ")
, QString::fromLocal8Bit("���ڶ�")
, QString::fromLocal8Bit("������")
, QString::fromLocal8Bit("������")
, QString::fromLocal8Bit("������")
, QString::fromLocal8Bit("������")
, QString::fromLocal8Bit("������") };
static const QStringList kCountries = { QString::fromLocal8Bit("�й�")
, QString::fromLocal8Bit("������˹̹")
, QString::fromLocal8Bit("����")
, QString::fromLocal8Bit("�¹�")
, QString::fromLocal8Bit("����")
, QString::fromLocal8Bit("�ձ�")
, QString::fromLocal8Bit("ӡ��") };
enum ParamTypes
{
	Param_Counties,
	Param_Weekly, //List
	Param_Int,  //value
	Param_DegreeRange, //range
	Param_Other,
};
struct stTest
{
	stTest()
	{
		value = 0;
	}
	stTest(int value)
	{
		this->value = value;
	}
	stTest& operator=(int value)
	{
		this->value = value;
		return *this;
	}

	bool operator==(const stTest& other) const
	{
		if (this != &other)
		{
			return value == other.value;
		}
		
		return true;
	}

	int value;
};

Q_DECLARE_METATYPE(stTest);
enum EWeekly
{
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday ,
	Saturday ,
	Sunday,

	DefaultWeekly = Sunday,
};


Q_DECLARE_METATYPE(ParamTypes);
Q_DECLARE_METATYPE(EWeekly);
DECLARE_PVM_FUNCTIONS(ParamTypes, TestParams);

void Params::CParamWithValues<ParamTypes>::initParams()
{
	QList<EWeekly> weekly;
	weekly << Monday << Tuesday << Wednesday << Thursday << Friday << Saturday << Sunday;

	addParam(Param_Counties, new CListParamValue<QString>(kCountries, kCountries[3]));
	addParam(Param_Weekly, new CListParamValue<EWeekly>(weekly, DefaultWeekly));
	addParam(Param_Int, new CParamValue<int>(35));
	addParam(Param_DegreeRange, new CRangeParamValue<int>(0, 60, 360));
	addParam(Param_Other, new CParamValue<stTest>(stTest(9999)));
}
void Params::CParamWithValues<ParamTypes>::resetAllParams()
{
	reset<QString>();
	reset<EWeekly>();
	reset<int>();
	reset<stTest>();
}

#endif // Defines_h__

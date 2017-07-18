#ifndef ParamsMacroDefine_h__
#define ParamsMacroDefine_h__

#include "ParamWithValuesManager.h"

/*
���������ص������ռ估����
name: �����ռ�
����
name::createMonitGroup: ��������飬 ���ؼ����ID
name::releaseMonitGroup(�����ID): �ͷż�������
name::setValue(�����ID, �������ͣ�����ֵ): Ϊ��������ֵ
name::value(�����ID, ��������): ��ȡ����ֵ
name::defaultValue(�����ID, ��������): ��ȡ����Ĭ��ֵ
name::percent(�����ID, ��������, ����ֵ): ��ȡ����ֵ�����ٷֱ�(ֻ�з�Χȡֵ������Ч)
name::setPercent(�����ID, ��������): ��ȡ����Ĭ��ֵ�����ٷֱ�(ֻ�з�Χȡֵ������Ч)
name::minimum(�����ID, ��������): ��ȡ����ֵ��Сֵ(ֻ�з�Χȡֵ������Ч)
name::maximum(�����ID, ��������): ��ȡ����ֵ���ֵ(ֻ�з�Χȡֵ������Ч)
name::reset(�����ID, ��������): ���ò���ΪĬ��ֵ
name::addMonitor(�����ID, �����): Ϊ�������Ӽ����
name::removeMonitor(�����ID, �����): Ϊ������Ƴ������
name::setParamWithMonitor(�����ID, ��������, ����ֵ, �����): ���ò���ֵ(Я�����ò����ļ���ߣ���ü���߲����յ������仯֪ͨ)

������������:
enum EEngineParams
{
ParamType_Week,
ParamType_Angle,
ParamType_EffectID,
ParamType_Intensity,
ParamType_WB,
};

Q_DECLARE_METATYPE(EEngineParams);

DECLARE_PVM_FUNCTIONS(EEngineParams, EnginePVM)

void Params::CParamWithValues<EEngineParams>::initParams()
{
	QList<QString> weeks;
	weeks << "1" << "2" << "3" << "4" << "5" << "6" << "7";
	addParam(ParamType_Week, new Params::CListParamValue<QString>(weeks, weeks[weeks.size() - 1]));
	addParam(ParamType_Angle, new Params::CRangeParamValue<int>(0, 0, 360, true));
	addParam(ParamType_EffectID, new Params::CParamValue<int>(-1));
	addParam(ParamType_Intensity, new Params::CRangeParamValue<double>(0, 30.0, 100.0, false));
	addParam(ParamType_WB, new Params::CRangeParamValue<double>(0, 30.0, 100, true));
}
void Params::CParamWithValues<EEngineParams>::resetAllParams()
{
	//��ͬ�Ĳ�������ҪҪ�ֱ�����
	reset<QString>();
	reset<int>();
	reset<double>();
}
*/
#define DECLARE_PVM_FUNCTIONS(type, name) \
namespace name\
{\
	static QString createMonitGroup() { return PVMInstance().createMonitGroup<type>(); }\
	static void releaseMonitGroup(const QString& gid) { PVMInstance().releaseMonitGroup<type>(gid); }\
	template<class V>\
	static bool setValue(const QString& gid, const type& key, const V& value) { return PVMInstance().setValue<type, V>(gid, key, value); }\
	template<class V>\
	static V value(const QString& gid, const type& key) { return PVMInstance().value<type, V>(gid, key); }\
	template<class V>\
	static V defaultValue(const QString& gid, const type& key) { return PVMInstance().defaultValue<type, V>(gid, key); }\
	template<class V>\
	static double percent(const QString& gid, const type& key) { return PVMInstance().percent<type, V>(gid, key); }\
	template<class V> \
	double minimum(const QString& gid, const type& key) { return PVMInstance().minimum<type, V>(gid, key); }\
	template<class V> \
	double maximum(const QString& gid, const type& key){ return PVMInstance().maximum<type, V>(gid, key); }\
	template<class V>\
	static double defaultPercent(const QString& gid, const type& key){ return PVMInstance().defaultPercent<type, V>(gid, key); } \
	template <class V>\
	static void reset(const QString& gid, const type& key){ PVMInstance().reset<type, V>(gid, key); } \
	static void addMonitor(const QString& gid, CParamWithValuesMonitor<type>* monitor){ PVMInstance().addMonitor<type>(gid, monitor); } \
	static void removeMonitor(const QString& gid, CParamWithValuesMonitor<type>* monitor){ PVMInstance().removeMonitor<type>(gid, monitor); } \
	template<class V>\
	static bool setParamWithMonitor(const QString& gid, const type& key, const V& value, CParamWithValuesMonitor<type>* monitor){ return PVMInstance().setParamWithMonitor<type, V>(gid, key, value, monitor); } \
}

#endif // ParamsMacroDefine_h__

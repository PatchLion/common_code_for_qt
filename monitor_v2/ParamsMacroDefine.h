#ifndef ParamsMacroDefine_h__
#define ParamsMacroDefine_h__

#include "ParamWithValuesManager.h"

/*
定义参数监控的命名空间及函数
name: 命名空间
函数
name::createMonitGroup: 创建监控组， 返回监控组ID
name::releaseMonitGroup(监控组ID): 释放监控组对象
name::setValue(监控组ID, 参数类型，参数值): 为参数设置值
name::value(监控组ID, 参数类型): 获取参数值
name::defaultValue(监控组ID, 参数类型): 获取参数默认值
name::percent(监控组ID, 参数类型, 参数值): 获取参数值所处百分比(只有范围取值参数有效)
name::setPercent(监控组ID, 参数类型): 获取参数默认值所处百分比(只有范围取值参数有效)
name::minimum(监控组ID, 参数类型): 获取参数值最小值(只有范围取值参数有效)
name::maximum(监控组ID, 参数类型): 获取参数值最大值(只有范围取值参数有效)
name::reset(监控组ID, 参数类型): 重置参数为默认值
name::addMonitor(监控组ID, 监控者): 为监控组添加监控者
name::removeMonitor(监控组ID, 监控者): 为监控组移除监控者
name::setParamWithMonitor(监控组ID, 参数类型, 参数值, 监控者): 设置参数值(携带设置参数的监控者，则该监控者不会收到参数变化通知)

参数定义例子:
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
	//不同的参数类型要要分别重置
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

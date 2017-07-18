#ifndef ParamWithValuesMonitor_h__
#define ParamWithValuesMonitor_h__

template<class K>
class CParamWithValuesMonitor
{
public:
	//��صĲ�������
	QList<K> monitParamTypes() const { return m_monitTypes; }
	void setMonitParamType(const K& type) { m_monitTypes.clear(); m_monitTypes << type; }
	void setMonitParamTypes(const QList<K>& listTypes) { m_monitTypes = listTypes; }

	//�����ı�
	virtual void onParamsChanged(const QVariant& key, const QVariant& value){}


private:
	QList<K> m_monitTypes;
};
#endif // ParamWithValuesMonitor_h__

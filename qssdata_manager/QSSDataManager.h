/*********************************************************************************
  *
  *
  *FileName:          QSSDataManager.h
  *
  *Author:         	   dai xiaobing
  *
  *Date:         	       2017-3-9
  *
  *Description:    qss样式数据管理类
  **********************************************************************************/
#ifndef QSSDataManager_h__
#define QSSDataManager_h__

#include <QtCore/QString>
#include <QtCore/QMap>
#include "Singleton.h"

namespace QSSData
{
	class CQSSDataManager
	{
	private:
		typedef QMap<QString, QString> MapKeyToStyleData;

	public:
		CQSSDataManager();

	public:
		//样式数据
		QString data(const QString& name) const;

		//刷新样式数据
		void reloadQSS(const QString& styleDir);

		void clear() { m_mapKeyToData.clear(); }

	private:
		void load(const QString& styleDir);

	private:
		MapKeyToStyleData				m_mapKeyToData;
	};
}
#define QSSDataManager()		(Singleton<QSSData::CQSSDataManager>::instance())
#define LoadQSSData(name)   (Singleton<QSSData::CQSSDataManager>::instance().data(name))
#endif // QSSDataManager_h__

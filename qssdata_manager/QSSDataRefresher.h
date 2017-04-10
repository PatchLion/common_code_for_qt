/*********************************************************************************
  *
  *
  *FileName:          QSSDataRefresher.h
  *
  *Author:         	   dai xiaobing
  *
  *Date:         	       2017-3-9
  *
  *Description:			QSSË¢ÐÂÆ÷
**********************************************************************************/
#ifndef QSSDataRefresher_h__
#define QSSDataRefresher_h__

#include <QtCore>
#include "Singleton.h"

namespace QSSData
{
	class QSSDataUser;
	class QSSDataRefresher
	{
		friend class QSSDataUser;
	public:
		QSSDataRefresher(){}
		~QSSDataRefresher(){}

	public:
		void refresh();

	private:
		void addUser(QSSDataUser* user);
		void removeUser(QSSDataUser*user);

	private:
		QList<QSSDataUser*> m_listQSSDataUser;
	};
}

#define  QSSRefresher() Singleton<QSSData::QSSDataRefresher>::instance()

#endif // QSSDataRefresher_h__

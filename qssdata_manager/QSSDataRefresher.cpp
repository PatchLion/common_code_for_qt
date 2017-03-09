#include "QSSDataRefresher.h"
#include "QSSDataUser.h"

void QSSData::QSSDataRefresher::addUser(QSSDataUser* user)
{
	if (!user)
	{
		return;
	}
	QList<QSSDataUser*>::iterator userItor = qFind(m_listQSSDataUser.begin(), m_listQSSDataUser.end(), user);
	if (m_listQSSDataUser.end() == userItor)
	{
		m_listQSSDataUser.append(user);
	}
}

void QSSData::QSSDataRefresher::removeUser(QSSDataUser*user)
{
	if (!user)
	{
		return;
	}
	QList<QSSDataUser*>::iterator userItor = qFind(m_listQSSDataUser.begin(), m_listQSSDataUser.end(), user);
	if (m_listQSSDataUser.end() != userItor)
	{
		m_listQSSDataUser.erase(userItor);
	}
}

void QSSData::QSSDataRefresher::refresh()
{
	Q_FOREACH(QSSDataUser* user, m_listQSSDataUser)
	{
		if (user)
		{
			user->refreshStyleSheet();
		}
	}
}
#include "QSSDataUser.h"
#include "QSSDataRefresher.h"

QSSData::QSSDataUser::QSSDataUser()
{
	QSSRefresher().addUser(this);
}

QSSData::QSSDataUser::~QSSDataUser()
{
	QSSRefresher().removeUser(this);
}


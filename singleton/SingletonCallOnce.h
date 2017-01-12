#ifndef SingletonCallOnce_h__
#define SingletonCallOnce_h__

#include <QtCore/QtGlobal>
#include <QtCore/QAtomicInt>
#include <QtCore/QMutex>
#include <QtCore/QWaitCondition>
#include <QtCore/QThreadStorage>
#include <QtCore/QThread>

namespace CallOnce {
	enum ECallOnce {
		CO_Request,
		CO_InProgress,
		CO_Finished
	};

	Q_GLOBAL_STATIC(QThreadStorage<QAtomicInt*>, once_flag_o)
}

template<class Function>
inline static void qCallOnce(Function func, QBasicAtomicInt& flag)
{
	using namespace CallOnce;
#if QT_VERSION < 0x050000
	int protectFlag = flag.fetchAndStoreAcquire(flag);
#endif
#if QT_VERSION >= 0x050000
	int protectFlag = flag.fetchAndStoreAcquire(flag.load());
#endif

	if (CO_Finished == protectFlag) return; 
	if (CO_Request == protectFlag && flag.testAndSetRelaxed(protectFlag,CO_InProgress))
	{
		func();
		flag.fetchAndStoreRelease(CO_Finished);
	}
	else
	{
		do
		{
			QThread::yieldCurrentThread();
		} 
		while (!flag.testAndSetAcquire(CO_Finished, CO_Finished));
	}
}

template<class Function>
inline static void qCallOncePerThread(Function func)
{
	using namespace CallOnce; 
	if (!once_flag_o()->hasLocalData())
	{
		once_flag_o()->setLocalData(new QAtomicInt(CO_Request));
		qCallOnce(func, *once_flag_o()->localData());
	}
}
#endif // SingletonCallOnce_h__
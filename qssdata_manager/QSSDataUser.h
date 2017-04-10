#ifndef QSSDataUser_h__
#define QSSDataUser_h__

namespace QSSData
{
	class QSSDataRefresher;
	class QSSDataUser
	{
		friend class QSSDataRefresher;
	public:
		QSSDataUser();
		virtual ~QSSDataUser();

	protected:
		virtual void refreshStyleSheet() {}
	};
}
#endif // QSSDataUser_h__

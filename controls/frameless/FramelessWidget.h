#ifndef FramelessWidget_h__
#define FramelessWidget_h__

#include <QtWidgets>

#define Use_Qt_Widget_MinMax

class CFramelessWidget :public QDialog
{
	Q_OBJECT

private:
	enum EMouseInArea
	{
		AreaOther = 0,
		AreaTitle,
		AreaLeft,
		AreaTop,
		AreaRight,
		AreaBottom,
		AreaTopLeft,
		AreaTopRight,
		AreaBottomLeft,
		AreaBottomRight,
	};

public:
	CFramelessWidget(QWidget *parent = 0);
	~CFramelessWidget();
	

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
	void showEvent(QShowEvent *event);
	void paintEvent(QPaintEvent *event);

protected:
	void moveWindow(QPoint);
	void checkNewPoint(QPoint &point);
	void showMaximizedSize();

protected:
	virtual QRect topLeftRect() const;
	virtual QRect topRightRect() const;
	virtual QRect bottomLeftRect() const;
	virtual QRect bottomRightRect() const;
	virtual QRect topRect() const;
	virtual QRect leftRect() const;
	virtual QRect rightRect() const;
	virtual QRect bottomRect() const;
	virtual QRect tittleRect() const;

	virtual bool isWidgetTypeNeedSetMouseTracking(QWidget* widget);
private:
	static QList<QWidget*> childWidgets(QWidget*widget);
	void changeChildControlsMouseTrackingState(QWidget* widget);
	bool isControlInArea(const QRect& rect) const;
	EMouseInArea checkMouseInAreaType(const QPoint& pos);
	void changeMouseCursorByAreaType(EMouseInArea areaType, Qt::MouseButton button);

private:
	bool					m_isMousePressing;
#ifdef Q_OS_WIN
#ifndef Use_Qt_Widget_MinMax 
	bool					m_isWindowMaxSize;					//是否最大窗口;
	QRect                 m_geometryBeforeDbClk;		//双击放大前的窗口尺寸
#endif
#endif
	QPoint				m_lastPoint;									//保存鼠标按下的位置;
	QRect					m_lastRect;									//保存鼠标按下窗口区域;
	QRectF				m_deskRect;
	QByteArray		m_position;									//定义一个窗口位置的信息;
	EMouseInArea  m_mouseInAreaType;					//拖动边框位置;

};
#endif // FramelessWidget_h__

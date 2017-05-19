#include "FramelessWidget.h"

//拖动区域长度
const int kTopDrag = 5;
const int kRightDrag = 5;
const int kBottomDrag = 5;
const int kLeftDrag = 5;

CFramelessWidget::CFramelessWidget(QWidget *parent)
	: QDialog(parent)
	, m_mouseInAreaType(AreaOther)
	, m_isMousePressing(false)
{
	QDesktopWidget* desktopWidget = QApplication::desktop();
	m_deskRect = desktopWidget->availableGeometry();
#ifdef Q_OS_WIN
	setWindowFlags(windowFlags() | Qt::Window | Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);
	setAttribute(Qt::WA_TranslucentBackground);
#ifndef Use_Qt_Widget_MinMax 
	m_isWindowMaxSize = false;
#endif
#else
    setWindowFlags(Qt::WindowMinimizeButtonHint);
    setMinimumSize(1024, 700);
	setMaximumSize(m_deskRect.width(), m_deskRect.height());
#endif	

    setMouseTracking(true);
}
void CFramelessWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
#ifdef Q_OS_WIN
	m_mouseInAreaType = checkMouseInAreaType(event->pos());
	changeMouseCursorByAreaType(m_mouseInAreaType, event->button());
    if (m_mouseInAreaType == AreaTitle)
    {
#ifdef Q_OS_WIN
#ifndef Use_Qt_Widget_MinMax 
		if (m_isWindowMaxSize)
		{
			setGeometry(m_geometryBeforeDbClk);
			m_isWindowMaxSize = false;
		}
		else
		{
			m_geometryBeforeDbClk = geometry();
			showMaximizedSize();
			m_isWindowMaxSize = true;
		}
#else
		if (!isMaximized())
		{
			showMaximized();
		}
		else
		{
			showNormal();
		}
#endif
#endif
	}
#endif
	QDialog::mouseDoubleClickEvent(event);
}

void CFramelessWidget::mousePressEvent(QMouseEvent *event)
{
#ifdef Q_OS_WIN
	if (event->buttons() == Qt::LeftButton)
	{
		m_isMousePressing = true;
		m_lastPoint = event->globalPos();
		m_lastRect = geometry();
		m_mouseInAreaType = checkMouseInAreaType(event->pos());
		changeMouseCursorByAreaType(m_mouseInAreaType, event->button());
	}
#endif
	QDialog::mousePressEvent(event);
}

void CFramelessWidget::mouseMoveEvent(QMouseEvent *event)
{
#ifdef Q_OS_WIN
	//改变鼠标状态
	if (!m_isMousePressing)
	{
		//非按下状态才改变鼠标样式
		m_mouseInAreaType = checkMouseInAreaType(event->pos());
		changeMouseCursorByAreaType(m_mouseInAreaType, event->button());
	}
	else
	{
#ifdef Q_OS_WIN
#ifndef Use_Qt_Widget_MinMax 
		if (m_isWindowMaxSize)
#else
		if (isMaximized())
#endif
#endif
		{
			const QPoint offset = event->globalPos() - m_lastPoint;
			if (m_mouseInAreaType == AreaTitle)
			{
#ifdef Q_OS_WIN
#ifndef Use_Qt_Widget_MinMax 
				showNormal();
				m_isWindowMaxSize = false;
				double dPercent = (double)event->globalPos().x() / (double)width();
				showNormal();
				setGeometry(event->globalPos().x() - minimumSize().width() * dPercent, pos().y(), minimumSize().width(), minimumSize().height());
				m_lastRect = geometry();
#else
				showNormal();
#endif
#endif
			}
		}
		else
		{
			QPoint newPoint = event->globalPos();

			if (m_mouseInAreaType != AreaOther)
			{
				moveWindow(newPoint);
			}
		}
		
	}
#endif
	QDialog::mouseMoveEvent(event);
}

void CFramelessWidget::mouseReleaseEvent(QMouseEvent *event)
{
	setCursor(Qt::ArrowCursor);
	m_isMousePressing = false;
	QDialog::mouseReleaseEvent(event);
}

void CFramelessWidget::changeMouseCursorByAreaType(EMouseInArea areaType, Qt::MouseButton button)
{
	switch (areaType)
	{
	case CFramelessWidget::AreaOther: setCursor(Qt::ArrowCursor); break;
	case CFramelessWidget::AreaTitle: {(Qt::LeftButton == button) ?  setCursor(Qt::ClosedHandCursor) : setCursor(Qt::OpenHandCursor); }break;
	case CFramelessWidget::AreaLeft: setCursor(Qt::SizeHorCursor); break;
	case CFramelessWidget::AreaTop: setCursor(Qt::SizeVerCursor); break;
	case CFramelessWidget::AreaRight: setCursor(Qt::SizeHorCursor); break;
	case CFramelessWidget::AreaBottom: setCursor(Qt::SizeVerCursor); break;
	case CFramelessWidget::AreaTopLeft: setCursor(Qt::SizeFDiagCursor); break;
	case CFramelessWidget::AreaTopRight: setCursor(Qt::SizeBDiagCursor); break;
	case CFramelessWidget::AreaBottomLeft: setCursor(Qt::SizeBDiagCursor); break;
	case CFramelessWidget::AreaBottomRight: setCursor(Qt::SizeFDiagCursor); break;
	default: setCursor(Qt::ArrowCursor); break;
	}
}

CFramelessWidget::EMouseInArea CFramelessWidget::checkMouseInAreaType(const QPoint& pos)
{
	if (topLeftRect().contains(pos))					return AreaTopLeft;
	else if (topRightRect().contains(pos))			return AreaTopRight;
	else if (bottomLeftRect().contains(pos))		return AreaBottomLeft;
	else if (bottomRightRect().contains(pos))	return AreaBottomRight;
	else if (topRect().contains(pos))					return AreaTop;
	else if (bottomRect().contains(pos))			return AreaBottom;
	else if (leftRect().contains(pos))					return AreaLeft;
	else if (rightRect().contains(pos))					return AreaRight;
	else if (tittleRect().contains(pos))					return AreaTitle;
	else return AreaOther;
}

void CFramelessWidget::moveWindow(QPoint newPoint)
{
	int maxWidth = maximumWidth();
	int maxHeight = maximumHeight();
	int minWidht = minimumWidth();
	int minHeight = minimumHeight();
	QRect newRect = m_lastRect;
	QPoint topLeftPoint = m_lastRect.topLeft();
	QPoint bottomRightPoint = m_lastRect.bottomRight();
	QPoint offsetPoint = newPoint - m_lastPoint;
	if (m_mouseInAreaType == AreaTitle)//¬±√ç√É‚Äö¬ø‚àè¬´¬Ø‚Äù√ö¬µ∆í√ï≈ì‚àÇ√ò
	{
		QPoint point = topLeftPoint + offsetPoint;
		checkNewPoint(point);
		newRect = QRect(point, bottomRightPoint + offsetPoint);
	}
	else if (m_mouseInAreaType == AreaTopLeft)//√ï≈ì‚àÇ√ò¬´¬Ø‚Äù√ö≈í‚Ñ¢‚óä√õ‚Ä¶≈ìŒ©¬?
	{
		newRect = QRect(topLeftPoint + offsetPoint, bottomRightPoint);
		//√∑√ø‚Äì¬¨‚àÇ¬Æ‚Äú√Ç¬•‚àû√∏‚ÅÑ¬´¬Ø‚Äù√ö¬µ∆í‚óä√õ‚Ä¶≈ìŒ©¬´x¬£¬®y
		if (newRect.width() < minWidht)
		{
			newRect.setX(bottomRightPoint.x() - minWidht);
		}
		if (newRect.height() < minHeight)
		{
			newRect.setY(bottomRightPoint.y() - minHeight);
		}
		if (newRect.width() > maxWidth)
		{
			newRect.setX(bottomRightPoint.x() - maxWidth);
		}
		if (newRect.height() > maxHeight)
		{
			newRect.setY(bottomRightPoint.y() - maxHeight);
		}
	}
	else if (m_mouseInAreaType == AreaTop)//¬±Ô¨Ç√∏√ö‚Ä¶≈?
	{
		newRect = QRect(QPoint(topLeftPoint.x(), topLeftPoint.y() + offsetPoint.y()), bottomRightPoint);
		//√∑√ø‚Äì¬¨‚àÇ¬Æ‚Äú√Ç¬•‚àû√∏‚ÅÑ¬´¬Ø‚Äù√ö¬µ∆í‚óä√õ‚Ä¶≈ìŒ©¬´y
		if (newRect.height() < minHeight)
		{
			newRect.setY(bottomRightPoint.y() - minHeight);
		}
		if (newRect.height() > maxHeight)
		{
			newRect.setY(bottomRightPoint.y() - maxHeight);
		}
	}
	else if (m_mouseInAreaType == AreaTopRight)//‚Äù‚Äú‚Ä¶≈ìŒ©¬?
	{

		newRect = QRect(QPoint(topLeftPoint.x(), topLeftPoint.y() + offsetPoint.y()), QPoint(bottomRightPoint.x() + offsetPoint.x(), bottomRightPoint.y()));
		//√∑√ø‚Äì¬¨‚àÇ¬Æ‚Äú√Ç¬•‚àû√∏‚ÅÑ¬´¬Ø‚Äù√ö¬µ∆í‚óä√õ‚Ä¶≈ìŒ©¬´y
		if (newRect.height() < minHeight)
		{
			newRect.setY(bottomRightPoint.y() - minHeight);
		}
		if (newRect.height() > maxHeight)
		{
			newRect.setY(bottomRightPoint.y() - maxHeight);
		}
	}
	else if (m_mouseInAreaType == AreaRight)//¬±Ô¨Ç√∏√ö‚Äù‚Ä?
	{

		newRect = QRect(topLeftPoint, QPoint(bottomRightPoint.x() + offsetPoint.x(), bottomRightPoint.y()));
	}
	else if (m_mouseInAreaType == AreaBottomRight)//‚Äù‚Äú≈ì¬¨Œ©¬?
	{

		newRect = QRect(topLeftPoint, bottomRightPoint + offsetPoint);

	}
	else if (m_mouseInAreaType == AreaBottom)//¬±Ô¨Ç√∏√ö≈ì¬?
	{
		newRect = QRect(topLeftPoint, QPoint(bottomRightPoint.x(), bottomRightPoint.y() + offsetPoint.y()));
	}
	else if (m_mouseInAreaType == AreaBottomLeft)//‚óä√õ≈ì¬¨Œ©¬?
	{

		newRect = QRect(QPoint(topLeftPoint.x() + offsetPoint.x(), topLeftPoint.y()), QPoint(bottomRightPoint.x(), bottomRightPoint.y() + offsetPoint.y()));
		//√∑√ø‚Äì¬¨‚àÇ¬Æ‚Äú√Ç¬•‚àû√∏‚ÅÑ¬´¬Ø‚Äù√ö¬µ∆í‚óä√õ‚Ä¶≈ìŒ©¬´x
		if (newRect.width() < minWidht)
		{
			newRect.setX(bottomRightPoint.x() - minWidht);
		}
		if (newRect.width() > maxWidth)
		{
			newRect.setX(bottomRightPoint.x() - maxWidth);
		}
	}
	else if (m_mouseInAreaType == AreaLeft)//¬±Ô¨Ç√∏√ö‚óä√õ
	{
		newRect = QRect(QPoint(topLeftPoint.x() + offsetPoint.x(), topLeftPoint.y()), bottomRightPoint);
		//√∑√ø‚Äì¬¨‚àÇ¬Æ‚Äú√Ç¬•‚àû√∏‚ÅÑ¬´¬Ø‚Äù√ö¬µ∆í‚óä√õ‚Ä¶≈ìŒ©¬´x
		if (newRect.width() < minWidht)
		{
			newRect.setX(bottomRightPoint.x() - minWidht);
		}
		if (newRect.width() > maxWidth)
		{
			newRect.setX(bottomRightPoint.x() - maxWidth);
		}
	}
	setGeometry(newRect);
	update();
}

CFramelessWidget::~CFramelessWidget()
{

}

void CFramelessWidget::showEvent(QShowEvent *event)
{
#ifdef Q_OS_WIN
#ifndef Use_Qt_Widget_MinMax 
	m_geometryBeforeDbClk = geometry();
#endif
#endif
	changeChildControlsMouseTrackingState(this);
}

void CFramelessWidget::paintEvent(QPaintEvent *event)
{

}

void CFramelessWidget::showMaximizedSize()
{
#ifdef Q_OS_WIN
#ifndef Use_Qt_Widget_MinMax 
	QRect m_deskRect;
	QDesktopWidget* desktopWidget = QApplication::desktop();//¬™√í¬ª¬∞√∏‚Ä¶‚Äù‚àö‚óä¬ø‚àö√ä¬•√õ‚Äì¬?
	m_deskRect = desktopWidget->availableGeometry();
	if (m_isWindowMaxSize)//¬™√∑‚àè¬?
	{
		setWindowState(Qt::WindowNoState);
		restoreGeometry(m_position);
		m_isWindowMaxSize = false;
	}
	else
	{
		m_isWindowMaxSize = true;
		m_position = this->saveGeometry();
		setGeometry(QRect(m_deskRect.x(), m_deskRect.y(), m_deskRect.width(), m_deskRect.height()));
		setWindowState(Qt::WindowMaximized);
		//showMaximized();
	}
#else
	showMaximized();
#endif
#endif
}

void CFramelessWidget::checkNewPoint(QPoint &point)
{
	const int WOFFSET = 20;
	const int HOFFSET = 20;
	if (point.x() < m_deskRect.x() - this->width() + WOFFSET)
	{
		point.setX(m_deskRect.x() - this->width() + WOFFSET);
	}
	if (point.y() < m_deskRect.y() - this->height() + HOFFSET)
	{
		point.setY(m_deskRect.y() - this->height() + HOFFSET);
	}
	if (point.x() > (m_deskRect.x() + m_deskRect.width() - WOFFSET))
	{
		point.setX(m_deskRect.x() + m_deskRect.width() - WOFFSET);
	}
	if (point.y() > (m_deskRect.y() + m_deskRect.height() - HOFFSET))
	{
		point.setY(m_deskRect.y() + m_deskRect.height() - HOFFSET);
	}
}

QRect CFramelessWidget::topLeftRect() const
{
	return QRect(QPoint(0, 0), QPoint(kLeftDrag, kTopDrag));
}
QRect CFramelessWidget::topRightRect() const
{
	return QRect(QPoint(width() - kRightDrag, 0), 
		QPoint(width(), kTopDrag));
}
QRect CFramelessWidget::bottomLeftRect() const
{
	return QRect(QPoint(0, height() - kBottomDrag), 
		QPoint(kLeftDrag, height() - kLeftDrag));
}
QRect CFramelessWidget::bottomRightRect() const
{
	return QRect(QPoint(width() - kRightDrag, height() - kBottomDrag), 
		QPoint(width(), height()));
}
QRect CFramelessWidget::topRect() const
{
	return QRect(QPoint(0, 0), 
		QPoint(width(), kTopDrag));
}
QRect CFramelessWidget::leftRect() const
{
	return QRect(QPoint(0, kTopDrag), 
		QPoint(kLeftDrag, height() - kBottomDrag));
}
QRect CFramelessWidget::rightRect() const
{
	return QRect(QPoint(width() - kRightDrag, kTopDrag),
		QPoint(width(), height()- kBottomDrag));
}
QRect CFramelessWidget::bottomRect() const
{
	return QRect(QPoint(kLeftDrag, height() - kBottomDrag),
		QPoint(width() - kRightDrag, height()));

}
QRect CFramelessWidget::tittleRect() const
{
	return QRect(QPoint(kLeftDrag, kTopDrag), 
		QPoint(width() - kRightDrag, kTopDrag+100));
}
/*

bool CFramelessWidget::eventFilter(QObject *object, QEvent *event)
{
	if (object != this)
	{
		QWidget* widget = dynamic_cast<QWidget*>(object);

		if (widget && widget->parentWidget() == this && isControlInArea(widget->geometry()))
		{
			
			QMouseEvent* mouseEvent = dynamic_cast<QMouseEvent*>(event);
			switch (event->type())
			{
			case QEvent::MouseButtonPress:
			{
				//mousePressEvent(mouseEvent);
			}
			break;
			case QEvent::MouseButtonRelease:
			{
				//mouseReleaseEvent(mouseEvent);
			}
			break;
			case QEvent::MouseButtonDblClick:
			{
				//mouseDoubleClickEvent(mouseEvent);
			}
			break;
			case QEvent::MouseMove:
			{
				mouseMoveEvent(mouseEvent);
			}
			break;
			}
		}
	}
	return QDialog::eventFilter(object, event);
}
*/

QList<QWidget*> CFramelessWidget::childWidgets(QWidget*parentWidget)
{
	QList<QWidget*> listWidget;
	if (parentWidget)
	{
		QObjectList listObject = parentWidget->children();
		Q_FOREACH(QObject* object, listObject)
		{
			QWidget* widget = dynamic_cast<QWidget*>(object);
			if (widget)
			{
				listWidget << widget;
			}
		}
	}
	
	return listWidget;
}
bool CFramelessWidget::isWidgetTypeNeedSetMouseTracking(QWidget* widget)
{
	if (dynamic_cast<QAbstractButton*>(widget)
		|| dynamic_cast<QComboBox*>(widget)
		|| dynamic_cast<QTextBrowser*>(widget)
		|| dynamic_cast<QPlainTextEdit*>(widget)
		|| dynamic_cast<QSpinBox*>(widget)
		|| dynamic_cast<QDoubleSpinBox*>(widget)
		|| dynamic_cast<QLineEdit*>(widget))
	{
		return false;
	}

	return true;
}


void CFramelessWidget::changeChildControlsMouseTrackingState(QWidget* parentwidget)
{
	QList<QWidget*> listWidget = childWidgets(parentwidget);
	Q_FOREACH (QWidget* widget , listWidget)
	{
		if (isControlInArea(widget->geometry()) 
			&& isWidgetTypeNeedSetMouseTracking(widget))
		{
			widget->setMouseTracking(true);
			//widget->installEventFilter(this);
			changeChildControlsMouseTrackingState(widget);
		}
		/*else
		{
			widget->removeEventFilter(this);
		}*/
		
	}
}

bool CFramelessWidget::isControlInArea(const QRect& rect) const
{
	return (topLeftRect().intersects(rect)
		|| topRightRect().intersects(rect)
		|| bottomLeftRect().intersects(rect)
		|| bottomRightRect().intersects(rect)
		|| topRect().intersects(rect)
		|| leftRect().intersects(rect)
		|| rightRect().intersects(rect)
		|| bottomRect().intersects(rect)
		|| tittleRect().intersects(rect));
}

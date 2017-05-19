#include "demo.h"
#include <QtWidgets>
#include <QtCore>

CTestMainWidget::CTestMainWidget(QWidget* parent /*= 0*/)
	: CFramelessWidget(parent)
{	
	setupUi(this);

	setStyleSheet("background-color: lightgray");
}

CTestMainWidget::~CTestMainWidget()
{

}
qint64 g_index = 0;
void CTestMainWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
	qDebug() << "Mouse Double Click! " << g_index++;
	CFramelessWidget::mouseDoubleClickEvent(event);
}

void CTestMainWidget::mousePressEvent(QMouseEvent *event)
{
	qDebug() << "Mouse Pressed! " << g_index++;
	CFramelessWidget::mousePressEvent(event);
}

void CTestMainWidget::mouseReleaseEvent(QMouseEvent *event)
{
	qDebug() << "Mouse Release! " << g_index++;
	CFramelessWidget::mouseReleaseEvent(event);
}

void CTestMainWidget::mouseMoveEvent(QMouseEvent *event)
{
	qDebug() << "Mouse Move! " << g_index++;
	CFramelessWidget::mouseMoveEvent(event);
}

void CTestMainWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setBrush(Qt::blue);
	painter.setPen(Qt::blue);

	painter.drawRoundedRect(rect(), 10, 10);
}

QRect CTestMainWidget::tittleRect() const
{
	return widgetHead->geometry();
}

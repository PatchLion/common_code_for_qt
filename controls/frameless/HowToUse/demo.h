#ifndef demo_h__
#define demo_h__

#include "FramelessWidget.h"
#include "ui_demo.h"

class CTestMainWidget : public CFramelessWidget, public Ui_TestMainWidget
{
	Q_OBJECT
public:
	CTestMainWidget(QWidget* parent = 0);
	~CTestMainWidget();

protected:
	void mouseDoubleClickEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

	void paintEvent(QPaintEvent *event);

protected:
	QRect tittleRect() const;
};
#endif // demo_h__

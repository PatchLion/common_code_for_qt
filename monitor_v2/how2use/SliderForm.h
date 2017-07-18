#ifndef SLIDERFORM_H
#define SLIDERFORM_H

#include <QWidget>
#include "Defines.h"

namespace Ui {
class SliderForm;
}

class SliderForm : public QWidget
{
    Q_OBJECT

public:
	explicit SliderForm(const QString& groupID, QWidget *parent = 0);
    ~SliderForm();

protected Q_SLOTS :
void on_comboBoxCountries_currentIndexChanged(int index);
	void on_comboBoxWeekly_currentIndexChanged(int index);
	void on_horizontalSliderIntRange_valueChanged(int value);
	void on_spinBoxInt_valueChanged(int value);
	void on_spinBoxStruct_valueChanged(int value);
private:
    Ui::SliderForm *ui;
	QString m_groupID;

};

#endif // SLIDERFORM_H

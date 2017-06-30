#ifndef SLIDERFORM_H
#define SLIDERFORM_H

#include <QWidget>

namespace Ui {
class SliderForm;
}

class SliderForm : public QWidget
{
    Q_OBJECT

public:
    explicit SliderForm(QWidget *parent = 0);
    ~SliderForm();
protected Q_SLOTS:
void on_horizontalSliderValue1_valueChanged(int value);
void on_horizontalSliderValue2_valueChanged(int value);
private:
    Ui::SliderForm *ui;
};

#endif // SLIDERFORM_H

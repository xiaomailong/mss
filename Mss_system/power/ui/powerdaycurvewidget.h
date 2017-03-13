#ifndef POWERDAYCURVEWIDGET_H
#define POWERDAYCURVEWIDGET_H

#include <QWidget>

namespace Ui {
class PowerDayCurveWidget;
}

class PowerDayCurveWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PowerDayCurveWidget(QWidget *parent = 0);
    ~PowerDayCurveWidget();

private:
    Ui::PowerDayCurveWidget *ui;
};

#endif // POWERDAYCURVEWIDGET_H

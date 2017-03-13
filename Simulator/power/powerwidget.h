#ifndef POWERWIDGET_H
#define POWERWIDGET_H

#include <QWidget>

namespace Ui {
class PowerWidget;
}

class PowerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PowerWidget(QWidget *parent = 0);
    ~PowerWidget();

private:
    Ui::PowerWidget *ui;
};

#endif // POWERWIDGET_H

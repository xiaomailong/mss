#ifndef CIWIDGET_H
#define CIWIDGET_H

#include <QWidget>

namespace Ui {
class CiWidget;
}

class CiWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CiWidget(QWidget *parent = 0);
    ~CiWidget();

private:
    Ui::CiWidget *ui;
};

#endif // CIWIDGET_H

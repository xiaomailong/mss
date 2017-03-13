#ifndef VOBCWIDGET_H
#define VOBCWIDGET_H

#include <QWidget>

namespace Ui {
class VobcWidget;
}

class VobcWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VobcWidget(QWidget *parent = 0);
    ~VobcWidget();

private:
    Ui::VobcWidget *ui;
};

#endif // VOBCWIDGET_H

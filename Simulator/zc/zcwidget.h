#ifndef ZCWIDGET_H
#define ZCWIDGET_H

#include <QWidget>

namespace Ui {
class ZcWidget;
}

class ZcWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ZcWidget(QWidget *parent = 0);
    ~ZcWidget();

private:
    Ui::ZcWidget *ui;
};

#endif // ZCWIDGET_H

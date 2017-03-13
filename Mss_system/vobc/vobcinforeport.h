#ifndef VOBCINFOREPORT_H
#define VOBCINFOREPORT_H

#include <QWidget>

namespace Ui {
class VobcInfoReport;
}

class VobcInfoReport : public QWidget
{
    Q_OBJECT

public:
    explicit VobcInfoReport(QWidget *parent = 0,int type =0,QString deviceName =NULL);
    ~VobcInfoReport();

private:
    Ui::VobcInfoReport *ui;
};

#endif // VOBCINFOREPORT_H

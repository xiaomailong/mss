#ifndef ATSINFOREPORT_H
#define ATSINFOREPORT_H

#include <QWidget>

namespace Ui {
class AtsInfoReport;
}

class AtsInfoReport : public QWidget
{
    Q_OBJECT

public:
    explicit AtsInfoReport(QWidget *parent = 0);
    ~AtsInfoReport();

private:
    Ui::AtsInfoReport *ui;
};

#endif // ATSINFOREPORT_H

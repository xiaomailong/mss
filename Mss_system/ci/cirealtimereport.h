#ifndef CIREALTIMEREPORT_H
#define CIREALTIMEREPORT_H

#include <QWidget>

namespace Ui {
class CiRealTimeReport;
}

class CiRealTimeReport : public QWidget
{
    Q_OBJECT

public:
    explicit CiRealTimeReport(QWidget *parent = 0);
    ~CiRealTimeReport();

private:
    Ui::CiRealTimeReport *ui;
};

#endif // CIREALTIMEREPORT_H

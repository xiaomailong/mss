#ifndef SHOWDETAILALARM_H
#define SHOWDETAILALARM_H

#include <QMainWindow>

namespace Ui {
class ShowDetailAlarm;
}

class ShowDetailAlarm : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShowDetailAlarm(QWidget *parent = 0);
    ~ShowDetailAlarm();
    void fillData(QStringList strList);

private slots:
    void on_closeBtn_clicked();

private:
    Ui::ShowDetailAlarm *ui;
};

#endif // SHOWDETAILALARM_H

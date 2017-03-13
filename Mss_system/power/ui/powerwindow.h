#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

//add by yhj 20170211 for power monitor system
#include "powerprocess.h"
#include "powersimulatedataservice.h"
//add end
#include"power/ui/powerreaddata.h"
class PowerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PowerWindow(QWidget *parent = 0);
    ~PowerWindow();
    void closeEvent(QCloseEvent *event);
public slots:
    void onEventForPower(int type,QString actionName);
    void onWindowDestroy();
    void onTabClose(int index);
private:
    QTabWidget *tabWidget;
    QHash<QString, QWidget *> hashTabWidget;
    enum ActionType{day_report =1,day_curve=2,month_curve=3,year_curve=4,realtime_curve =5,power_alarm};
    QThread *thread;
    PowerReadData *readData;
    enum CurveType{ dayType,monthType,yearType};
signals:
    void sendEventToMss(const QString msg);

};

#endif // MAINWINDOW_H

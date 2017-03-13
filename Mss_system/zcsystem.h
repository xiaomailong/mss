#ifndef ZCSYSTEM_H
#define ZCSYSTEM_H
#include "zc/zcdatathread.h"
#include "zc/zcgplot.h"
#include "zc/zcreaddata.h"
#include <QMainWindow>
#include <QTabWidget>
#include <QString>
#include <QWidget>

class ZcSystem : public QMainWindow
{
    Q_OBJECT
public:
    explicit ZcSystem(QWidget *parent = 0);
    void closeEvent(QCloseEvent *event);
signals:
    void sendEventToMss(const QString msg); //zc system send message to Mss
public slots:
    void onTabClose(int);
    void receive_ui_zc_ci_ls(); //zc system receive alarm message from data processing layer 
    void onEventFromMss(const QString msg);  //zc system receive message from Mss
    void onEventFromMap(int type,QString deviceName); //zc system receive message from Map
    void onReceiveZcGplot(const QString msg); //zc system receive message from ZcGplot
    void onWindowDestroy(); //zc system window destory
private:
    QTabWidget *zcTabWidget;  //zc tabwidget to contain ats vobc ci
    QHash<QString, QWidget *> zcHashTabWidget; //zc hash Tabwidget
    QThread *zcSystemThread; //the thread of zc system
    ZCReadData * zcReadData; //zc read data from databases
};

#endif // ZCSYSTEM_H

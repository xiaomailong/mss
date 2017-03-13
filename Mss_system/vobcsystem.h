#ifndef VOBCSYSTEM_H
#define VOBCSYSTEM_H

#include <QMainWindow>
#include <QWidget>
#include "vobcdevice.h"
#include "vobccabinet.h"
#include "vobcalarmreport.h"
#include "vobc/vobcreaddatathread.h"
#include "vobc_data.h"

class VobcSystem : public QMainWindow
{
    Q_OBJECT
public:
    explicit VobcSystem(QWidget *parent = 0);
    ~VobcSystem();
    void closeEvent(QCloseEvent *event);


signals:
    void sendEventToMss(const QString msg);
    void sendAlarmToDevice(vobc_subsys_msg_t AtsMsg);

public slots:
    void onEventFromMss(const QString msg);
    void onEventFromMap(int type,QString deviceName);
    void onAlarmFromMss(vobc_subsys_msg_t AtsMsg);
    void onTabClose(int index);
    void onWindowDestroy();

private:
    QTabWidget *tabWidget;
    QHash<QString, QWidget *> hashTabWidget;
    QThread *thread;
    VobcReadDataThread *readData;
};

#endif // VOBCSYSTEM_H

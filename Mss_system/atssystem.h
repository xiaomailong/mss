#ifndef ATSSYSTEM_H
#define ATSSYSTEM_H

#include <QMainWindow>
#include <QTabWidget>
#include "ats/atsdevice.h"
#include "ats/atsalarmreport.h"
#include "ats/atsmonitorvobc.h"
#include "ats/atsmonitorci.h"
#include "ats/atsmonitorzc.h"
#include "ats/atsreaddata.h"
#include "ats_data.h"

#include <QThread>

class AtsSystem : public QMainWindow
{
    Q_OBJECT
public:
    explicit AtsSystem(QWidget *parent = 0);
    void closeEvent(QCloseEvent *event);

signals:
    void sendEventToMss(const QString msg);
    void sendAlarmToDevice(ats_mss_alarm_t* alarm_info);

public slots:

    void onTabClose(int index);

    void onEventFormMss(const QString msg);

    void onEventFromMap(int type,QString deviceName);

    void onAlarmFromMss(ats_mss_alarm_t* alarm_info);

    void onWindowDestroy();

private:

    QTabWidget *atsTabWidget;
    AtsDevice *atsDevice ;
    QHash<QString, QWidget *> hashTabWidget;

    QThread *thread;
    AtsReadData *readData;

};

#endif // ATSSYSTEM_H
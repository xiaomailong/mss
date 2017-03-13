#ifndef CISYSTEM_H
#define CISYSTEM_H
#include "ci_data.h"
#include <QMainWindow>
#include "ci/cireaddatathread.h"

class CiSystem : public QMainWindow
{
    Q_OBJECT
public:
    explicit CiSystem(QWidget *parent = 0);
    void closeEvent(QCloseEvent *event);

signals:
    void sendEventToMss(const QString msg);
    void sendEventToDevice(int state);
    void sendLevelOneAlarm();

    void sendEventToDevices(ci_ci_t* data);

public slots:
    void onEventFromMss(const QString msg);
    void onEventFromMap(int type,QString deviceName);
    void onTabClose(int index);
    void receiveCiAlarm(ci_ci_t* data);
    void onWindowDestroy();

private:
    QTabWidget *tabWidget;
    QHash<QString, QWidget *> hashTabWidget;
    QThread *thread;
    CiReadDataThread *readData;
};

#endif // CISYSTEM_H

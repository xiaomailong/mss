#ifndef VOBCSIMULATE_H
#define VOBCSIMULATE_H

#include <QObject>
#include <QThread>
#include "vobc_data.h"
class VobcSimulate : public QThread
{
    Q_OBJECT
public:
    explicit VobcSimulate(QObject *parent = 0);
    void setStopFlag(bool flag);

signals:
    void randomDcsData(quint8 *, quint16);
    void randomMsgAlarm(vobc_subsys_msg_t);
public slots:
protected:
    void run();
private:
    bool isStop = false;
};

#endif // VOBCSIMULATE_H

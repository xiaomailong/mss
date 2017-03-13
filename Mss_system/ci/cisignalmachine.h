#ifndef CISIGNALMACHINE_H
#define CISIGNALMACHINE_H

#include <QWidget>
#include <QPushButton>
#include <QPainter>

class CiSignalMachine : public QPushButton
{
    Q_OBJECT
public:
    explicit CiSignalMachine(QWidget *parent = 0);

    void paintEvent(QPaintEvent *);
signals:

public slots:
    void onEventFromDevice(int state);
    void onAlarmFromDevice(int alarmLevel);

private:
    bool isRed;
    bool hasAlarm;
    int alarmLevel;
};

#endif // CISIGNALMACHINE_H

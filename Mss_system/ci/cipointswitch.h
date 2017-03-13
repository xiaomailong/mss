#ifndef CIPOINTSWITCH_H
#define CIPOINTSWITCH_H

#include <QWidget>
#include <QPushButton>

class CiPointSwitch : public QPushButton
{
    Q_OBJECT
public:
    explicit CiPointSwitch(QWidget *parent = 0);

    void paintEvent(QPaintEvent *);
signals:

public slots:
    void onEventFromDevice(int state);
    void onAlarmFromDevice(int alarmLevel);
private:
    bool isRotate;
    bool hasAlarm;
    int alarmLevel;
};

#endif // CIPOINTSWITCH_H

#ifndef CITRANSPONDERS_H
#define CITRANSPONDERS_H

#include <QWidget>
#include <QPushButton>

class CiTransponders : public QPushButton
{
    Q_OBJECT
public:
    explicit CiTransponders(QWidget *parent = 0);

    void paintEvent(QPaintEvent *);

signals:

public slots:
    void onEventFromDevice(int state);
    void onAlarmFromDevice(int alarmLevel);
private:
    bool isWorking;
    bool hasAlarm;
    int alarmLevel;
};

#endif // CITRANSPONDERS_H

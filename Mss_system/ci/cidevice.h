#ifndef CIDEVICE_H
#define CIDEVICE_H

#include <QWidget>
#include <QPushButton>
#include <QPaintEvent>
#include <QLabel>
#include <QFont>
#include <QMenu>
#include "citransponders.h"
#include "ciaxlecounter.h"
#include "cipointswitch.h"
#include "cisignalmachine.h"
#include "ci_data.h"
#include "cixmlutil.h"

class CiDevice : public QWidget
{
    Q_OBJECT
public:
    explicit CiDevice(QWidget *parent = 0);

    ~CiDevice();

    void paintEvent(QPaintEvent *event);

    void resizeEvent(QResizeEvent *event);

    void wheelEvent(QWheelEvent *event);

    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

    void drawButtons(QPushButton *button,int width,int height,int x, int y);

    void drawArrows(QPainter &painter,qreal x,qreal y,int direction);

    void drawLabel(QLabel *label,QFont font,int size,int x, int y, int width, int height);

    void setDeviceToolTip(QObject *obj);

protected:
    bool eventFilter(QObject *watched, QEvent *event);

signals:
    void showReport(int type,QString deviceName);
    void sendStateToSignal(int state);
    void sendStateToTransponders(int state);
    void sendStateToZhuanzhe(int state);
    void sendStateToJizhou(int state);

    void sendAlarmToSignal(int alarmLevel);
    void sendAlarmToTransponders(int alarmLevel);
    void sendAlarmToZhuanzhe(int alarmLevel);
    void sendAlarmToJizhou(int alarmLevel);

public slots:
    void queryDeviceStatesReport();
    void queryAlarmReport();

    void onEventFromCis(ci_ci_t* data);

private:
    QPushButton *buttonCI;
    QPushButton *buttonRelay;
    QPushButton *buttonAxle;
    QPushButton *buttonLEU;
    QPushButton *buttonPSD;
    QPushButton *buttonESP;
    QPushButton *buttonIBP;
    QPushButton *buttonSPKS;

    QPushButton *buttonIO;
    QPushButton *buttonRelayOut;
    QPushButton *buttonPSDOut;
    QPushButton *buttonESPOut;
    QPushButton *buttonIBPOut;

    CiAxleCounter *buttonAxle1;
    CiAxleCounter *buttonAxle2;
    CiPointSwitch *buttonPointSwitch;
    CiSignalMachine *buttonSignalMachine;
    CiTransponders *buttonTransponders1;
    CiTransponders *buttonTransponders2;

    enum directions{up = 0,down = 1,left = 2,right = 3};

    QLabel *equipmentStationText;
    QLabel *equipmentNonCentralizedStationText;
    QLabel *ethernetText1;
    QLabel *ethernetText2;
    QLabel *ethernetText3;
    QLabel *relayText1;
    QLabel *relayText2;
    QLabel *sourceText;
    QLabel *noSourceText;
    QLabel *pointSwitchText;
    QLabel *axleCounterText;
    QLabel *signalMachineText;


private:
    float scale;
    int transX;
    int transY;
    QPoint startPoint;
    QPoint endPoint;
    QMenu *menu;
    QObject *rightPressButton;

    QHash<qint32,QString> hashDeviceMap;
    QList<QString> list;

};

#endif // CIDEVICE_H

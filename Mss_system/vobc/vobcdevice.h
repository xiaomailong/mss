#ifndef VOBCDEVICE_H
#define VOBCDEVICE_H

#include <QWidget>
#include <QPushButton>
#include <QDockWidget>
#include "vobc_data.h"

class VobcDevice : public QWidget
{
    Q_OBJECT
public:
    explicit VobcDevice(QWidget *parent = 0);

    ~VobcDevice();

    void paintEvent(QPaintEvent *event);

    void resizeEvent(QResizeEvent * event);

    void drawButton(QPushButton *button,int startX,int startY,int w,int h,QString name);

    void drawCustomLine(QPainter& p,QPoint point,QPoint point2,int direction, bool both,const QString& name);

    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

    void wheelEvent(QWheelEvent *event);

    void initDeviceXmlInfo();

    void setDeviceTip(QObject *object);

protected:
    bool eventFilter(QObject *obj, QEvent *event);

signals:
    void showReport(int type,QString deviceName);

public slots:
    void queryDayReport();
    void queryMonReport();
    void queryDayInformation();
    void queryMonInformation();
    void onAlarm(vobc_subsys_msg_t AtsMsg);

private:
    QPushButton *buttonHead;
    QPushButton *buttonTail;
    QPushButton *buttonSw1;
    QPushButton *buttonSw2;
    QPushButton *buttonNet;
    QPushButton *buttonIO;
    QPushButton *buttonPower;
    QPushButton *buttonAp1;
    QPushButton *buttonAp2;
    QPushButton *buttonDmi1;
    QPushButton *buttonDmi2;
    QPushButton *buttonBtm1;
    QPushButton *buttonBtm2;
    QPushButton *buttonBtm11;
    QPushButton *buttonBtm22;
    QPushButton *buttonRadar1;
    QPushButton *buttonRadar2;
    QPushButton *buttonPulse1;
    QPushButton *buttonPulse2;
    QPushButton *buttonPulse3;
    QPushButton *buttonPulse4;

    QMenu *menu;
    QObject *rightPressButton;

    float b;
    int transX;
    int transY;
    enum directions{Up = -1,Down = 1,Left = -2,Right = 2};
    QPoint lastPoint;
    QPoint endPoint;

    QHash<int,QPushButton *> hashDeviceMap;
    QList<int> breakDownList;
    QHash<int,QStringList> hashInfoMap;
    enum device{
        head,
        tail,
        btm1,
        btm2,
        ap1,
        ap2,
        dmi1,
        dmi2,
        io,
        net,
        power,
        sw1,
        sw2,
        radar1,
        radar2,
        pulse1,
        pulse3
    };

};

#endif // VOBCDEVICE_H

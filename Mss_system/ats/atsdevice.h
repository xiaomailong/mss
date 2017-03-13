#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMenu>
#include <ats_data.h>

namespace Ui {
class AtsDevice;
}

class AtsDevice : public QWidget
{
    Q_OBJECT

public:
    explicit AtsDevice(QWidget *parent = 0);
    ~AtsDevice();

signals:
    void showReport(int type,QString deviceName);

public slots:
    void queryDayReport();
    void queryMonthReport();
    void queryDeviceState();
    void onShowAlarm(ats_mss_alarm_t* alarm_info);

protected:

    void paintEvent(QPaintEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void initViews();
    void initDeviceXmlInfo();
    void setDeviceTip(QObject *object);
    bool eventFilter(QObject *object, QEvent *event);
    void drawLabel(QLabel *label,int startX,int startY,int w,int h,QString name);
    void drawLine(QPainter& p, int startX, int startY, int stopX,int stopY);
    void drawButton(QPushButton *button,int startX,int startY,int w,int h,QString name);

private:

    QMenu *menu;
    QObject *pressButton;
    QLabel *controlCenter;
    QLabel *leftCenter;
    QLabel *rightCenter;
    QLabel *aNetwork;
    QLabel *bNetwork;

    QPushButton *interChanger1;
    QPushButton *interChanger2;

    QLabel *displayEditLable;
    QPushButton *displayEdit;

    QLabel *dispatcherLable;
    QPushButton *dispatcher;

    QLabel *printerLable ;
    QPushButton *printer;

    QLabel *displayLable;
    QPushButton *display;

    QPushButton *applyServer1;
    QLabel *applyServer1Lable;

    QLabel *applyServer2Lable;
    QPushButton *applyServer2;

    QLabel *dbServer1Lable;
    QPushButton *dbServer1;

    QLabel *diskArrayLabel;
    QPushButton *diskArray;

    QLabel *dbServer2Lable;
    QPushButton *dbServer2;

    QPushButton *clockSystem;

    QLabel *descibeLable;

    QLabel *largeScreenLable;
    QPushButton *largeScreen;

    QLabel *interfaceServer1Lable;
    QPushButton *interfaceServer1;

    QLabel *interfaceServer2Lable;
    QPushButton *interfaceServer2;

    QLabel *atsMaintenanceLable;
    QPushButton *atsMaintenance;

    QLabel *commServer1Lable;
    QPushButton *commServer1;

    QLabel *commServer2Lable;
    QPushButton *commServer2;

    float b;
    int transX;
    int transY;
    QPoint lastPoint;
    QPoint endPoint;

    QHash<int,QPushButton *> hashDeviceMap;
    QList<int> breakDownList;
    QHash<int,QStringList> hashInfoMap;
    enum device{
        interchanger1,
        interchanger2,
        displayws,
        dispatherws,
        rundisplayws,
        largescreenws,
        atsmaintenancews,
        colorprinter,
        apply1,
        apply2,
        db1,
        db2,
        interface1,
        interface2,
        comm1,
        comm2
    };

};

#endif // WIDGET_H

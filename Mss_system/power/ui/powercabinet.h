#ifndef POWERCABINET_H
#define POWERCABINET_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
class Powercabinet: public QWidget
{

public:
    explicit Powercabinet(QWidget *parent = 0);

    ~Powercabinet();

    void paintEvent(QPaintEvent *event);

    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void wheelEvent(QWheelEvent *event);

    void resizeEvent(QResizeEvent * event);

    void drawFrame(QPainter& p,QPoint point,bool isHigh);

    void drawButton(QPushButton *button,int startX,int startY,int w,int h,QString name);

signals:

public slots:

private:
    QPushButton *button_fan;
    QPushButton *button_rtm;
    QPushButton *button_unknown1;
    QWidget *widgetA;
    QPushButton *button_1;
    QPushButton *button_2;
    QPushButton *button_3;
    QPushButton *button_4;
    QPushButton *button_5;
    QPushButton *button_6;
    QPushButton *button_7;
    QPushButton *button_8;
    QPushButton *button_9;
    QPushButton *button_10;
    QHBoxLayout *hLayout1;
    QPushButton *button_unknown2;
    QWidget *widgetAB;
    QWidget *widgetB;
    QPushButton *button2_1;
    QPushButton *button2_2;
    QPushButton *button2_3;
    QPushButton *button2_4;
    QPushButton *button2_5;
    QPushButton *button2_6;
    QPushButton *button2_7;
    QPushButton *button2_8;
    QPushButton *button2_9;
    QPushButton *button2_10;

    QPushButton *button3_1;
    QPushButton *button3_2;
    QPushButton *button3_3;
    QPushButton *button3_4;
    QPushButton *button3_5;
    QPushButton *button3_6;
    QPushButton *button3_7;
    QPushButton *button3_8;
    QPushButton *button3_9;
    QPushButton *button3_10;
    QHBoxLayout *hLayout3;
    QWidget *widgetC;

    QHBoxLayout *hLayout2;
    QPushButton *button_unknown3;
    QPushButton *button_relays;
    QPushButton *button_btm;
    QPushButton *button_conn;

    float scale;
    int transX;
    int transY;
    QPoint lastPoint;
    QPoint endPoint;
};

#endif // POWERCABINET_H

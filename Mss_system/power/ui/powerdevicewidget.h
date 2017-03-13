#ifndef POWERDEVICEWIDGET_H
#define POWERDEVICEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QMenu>
#include <QLabel>
#include <QMainWindow>

class PowerDeviceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PowerDeviceWidget(QWidget *parent = 0);
    bool event(QEvent *event);
    void initUi();
    void paintEvent(QPaintEvent *event);
    void drawRect(QPainter *painter,QPen *pen,QBrush *brush,const QColor &color,int penwidth,Qt::PenStyle style,int x,int y,int w,int h);
    void drawHorizionLine(QPainter *painter,QPen *pen,const QColor &color,int penwidth,int x1,int y1,int x2,int y2  );
    void drawButton(QPushButton *button,QPainter *painter,QString style,int x,int y,int w,int h);
    void drawVerticalLine(QPainter *painter,QPen *pen,const QColor &color,int penwidth,int x1,int y1,int x2,int y2 );
    void drawLabel(QLabel *label,QString str,int x1,int y1,int x2,int y2);
    void wheelEvent(QWheelEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);
public slots:
    void show_contextmenu(const QPoint& pos);
    void QueryDayReport();
    void QueryDayCurve();
    void QueryMonthCurve();
    void QueryYearCurve();
    void QueryRealTimeCurve();
    void QueryPowerAlarm();

signals:
     void showDayReport(int type,QString actionName);
     void showDayCurve(int type,QString actionName);
     void showMonthCurve(int type,QString actionName);
     void showYearCurve(int type,QString actionName);
     void showRealTimeCurve(int type,QString actionName);
     void showPowerAlarm(int type,QString actionName);
private:

    QMenu *m_pmenu;
    QMenu *menu1;
    QMenu *popMenu;
    QPushButton *buttonPower;
    QPushButton *buttonLock;
    QPushButton *buttonZC;
    QPushButton *buttonATS;
    QPushButton *buttonCI;
    QLabel *USPLabel ;
    QLabel *PowerLabel ;
    float scale;
    int transX;
    int transY;
    QPoint lastPoint;
    QPoint endPoint;
    QMainWindow *dayreportwindow;
    enum ActionType{day_report =1,day_curve=2,month_curve=3,year_curve=4,realtime_curve=5,power_alarm};
};

#endif // POWERDEVICEWIDGET_H

#ifndef POWERWIDGET_H
#define POWERWIDGET_H
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include<QMainWindow>
class Powerwidget: public QWidget
{
    Q_OBJECT

public:
    explicit Powerwidget(QWidget *parent = 0);
    ~Powerwidget();
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

signals:
     void showDayReport(int type,QString actionName);
private:

    QMenu *m_pmenu;
    QMenu *menu1;
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
    enum ActionType{day_report =1,day_curve=2,month_curve=3,year_curve=4};
};

#endif // POWERWIDGET_H

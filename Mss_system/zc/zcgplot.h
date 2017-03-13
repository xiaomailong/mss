#ifndef ZCGPLOT_H
#define ZCGPLOT_H

#include <QWidget>
#include <QPaintEvent>
#include <QPushButton>
#include <QObject>


class ZCGplot : public QWidget
{
    Q_OBJECT
public:
    explicit ZCGplot(QWidget *parent = 0);

private:
    void paintEvent(QPaintEvent *); //the paint event to draw gplot
    void resizeEvent(QResizeEvent *);
    void drawButton(QPushButton *,int ,int ,int ,int ,QString); //draw butoon
    void drawCustomLine(QPainter& ,QPoint, double, double); //draw line
    void mousePressEvent(QMouseEvent *); //mouse press event
    void mouseMoveEvent(QMouseEvent *); //mouse move event
    void mouseReleaseEvent(QMouseEvent *); //mource release event
    void wheelEvent(QWheelEvent *); //the wheel event of mouse

signals:
    void showReport(int ,QString); 
    void zcSendEventToMss(const QString);
public slots:
    void queryDayAlarmReport();
    void queryMonthAlarmReport();
    void queryDutInformation();
    void zcClickshowAts();
    void zcClickshowCi();
    void zcClickshowVobc();
protected:
    bool eventFilter(QObject *, QEvent *);

private:
    QPushButton *buttonOfZc;
    QPushButton *buttonOfAts;
    QPushButton *buttonOfCi;
    QPushButton *buttonOfvobc;
    QMenu *zcClickRightMenu;
    QObject *rightbutton;
    float zcGplotMagnification;
    int transX;
    int transY;
    QPoint lastPoint;
    QPoint endPoint;
};

#endif // ZCGPLOT_H

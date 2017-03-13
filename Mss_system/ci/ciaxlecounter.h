#ifndef CIAXLECOUNTER_H
#define CIAXLECOUNTER_H

#include <QWidget>
#include <QPushButton>

class CiAxleCounter : public QPushButton
{
    Q_OBJECT
public:
    explicit CiAxleCounter(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);

signals:

};

#endif // CIAXLECOUNTER_H

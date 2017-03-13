#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QWidget>
#include <QChart>
#include <QChartView>

QT_CHARTS_USE_NAMESPACE

class PowerChartWidget : public QWidget
{
    Q_OBJECT
public:
    PowerChartWidget(QWidget *parent = 0);

    void updateUI(QMap<QString,qint16> map,int curveType);

signals:

public slots:

private:
    QChartView *chartView;
    enum CurveType{ dayType,monthType,yearType};
};

#endif // CHARTWIDGET_H

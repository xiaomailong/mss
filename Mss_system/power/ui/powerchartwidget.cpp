
#include "powerchartwidget.h"
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QCategoryAxis>
#include <QDebug>

QT_CHARTS_USE_NAMESPACE

PowerChartWidget::PowerChartWidget(QWidget *parent) : QWidget(parent)
{
    chartView = new QChartView(parent);
    chartView->setMinimumSize(900,700);
    chartView->move(50,50);
    chartView->show();
    chartView->setRenderHint(QPainter::Antialiasing);
}


void PowerChartWidget::updateUI(QMap<QString,qint16> m_map,int curveType)
{
    //![1]
        QLineSeries *series = new QLineSeries();

        qDebug() <<"updateUI map size= "<<m_map.size();
        QMap<QString,qint16>::iterator it; //遍历map
        int i =0 ;
        for ( it = m_map.begin(); it != m_map.end(); it++ )
        {

            qDebug() <<it.key()<<"updateUI :"<<it.value();
            series->append( QPointF(i,it.value()));
            i++;
        }

        QChart *chart = new QChart();
        chart->legend()->hide();
        chart->addSeries(series);

        // Customize series
        QPen pen(QRgb(0xfdb157));
        pen.setWidth(3);
        series->setPen(pen);

        // Customize chart title
        QFont font;
        font.setPixelSize(16);
        chart->setTitleFont(font);
        chart->setTitleBrush(QBrush(Qt::black));
        chart->setTitle("");

        QCategoryAxis *axisX = new QCategoryAxis();
        QCategoryAxis *axisY = new QCategoryAxis();

        // Customize axis label font
        QFont labelsFont;
        labelsFont.setPixelSize(12);
        axisX->setLabelsFont(labelsFont);
        axisY->setLabelsFont(labelsFont);

        // Customize axis colors
        QPen axisPen(QRgb(0xd18952));
        axisPen.setWidth(2);
        axisX->setLinePen(axisPen);
        axisY->setLinePen(axisPen);
        axisX->setTitleText("时间");
        axisY->setTitleText("电压");
        axisX->setTitleVisible(true);
        axisY->setTitleVisible(true);
        axisX->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
        axisY->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);

        // Customize axis label colors
        QBrush axisBrush(Qt::black);
        axisX->setLabelsBrush(axisBrush);
        axisY->setLabelsBrush(axisBrush);

        //// Customize grid lines and shades
        axisX->setGridLineVisible(true);
        axisY->setGridLineVisible(true);

        int lastKey;
        i =0 ;
        for ( it = m_map.begin(); it != m_map.end(); it++ )
        {
            qDebug() <<"ChartWidget it.key()"  <<it.key()<<"it.value()"<<it.value();
            axisX->append(it.key(),i);
            lastKey=i;

            i++;

            axisY->append(QString("'%1'").arg(it.value()),it.value());
            if(curveType == yearType)
            {
                it = it++;

            }

        }
        qDebug() <<"ChartWidget zwz count ="<<i;
        qDebug() <<m_map.begin().key()<<": :"<<lastKey;
        axisX->setStartValue(0);
        axisX->setRange(0,110);
        axisY->setRange(0,240);
        chart->addSeries(series);
        chart->setAxisX(axisX, series);
        chart->setAxisY(axisY, series);

        chartView->setChart(chart);
}

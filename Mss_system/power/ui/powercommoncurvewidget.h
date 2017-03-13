#ifndef POWERCOMMONCURVEWIDGET_H
#define POWERCOMMONCURVEWIDGET_H

#include <QWidget>
#include <QDate>
#include"power/ui/powerreaddata.h"
#include "power/ui/powerchartwidget.h"
namespace Ui {
class PowerCommonCurveWidget;
}

class PowerCommonCurveWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PowerCommonCurveWidget(QWidget *parent = 0,PowerReadData *readData =NULL,int curveType =0);
    ~PowerCommonCurveWidget();
    QDate date;

    QDateTime dateTime2;
private:
    Ui::PowerCommonCurveWidget *ui;
    PowerChartWidget *chw;
    int CurveType =0;
    QString devicename ="";
    int deviceType = 0 ;
public slots:
    void OnGetData(QSqlQueryModel *model);
private slots:
    void on_dateEdit_userDateChanged(const QDate &date1);

    void on_comboBox_2_currentIndexChanged(const QString &arg1);

    void on_comboBox_currentIndexChanged(int index);

    void on_queryButton_clicked();

signals:
    void sendEventToRead(const QString &query);
};

#endif // POWERCOMMONCURVEWIDGET_H

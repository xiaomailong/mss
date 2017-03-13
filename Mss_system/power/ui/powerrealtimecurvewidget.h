#ifndef POWERREALTIMECURVEWIDGET_H
#define POWERREALTIMECURVEWIDGET_H

#include <QWidget>
#include <QSqlTableModel>
#include "power/ui/powerdisplaychoicemodel.h"
#include "power/ui/powerreaddata.h"

namespace Ui {
class PowerRealTimeCurveWidget;
}

class PowerRealTimeCurveWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PowerRealTimeCurveWidget(QWidget *parent = 0,PowerReadData *readData=NULL);
    ~PowerRealTimeCurveWidget();

private:
    Ui::PowerRealTimeCurveWidget *ui;
    PowerDisplayChoiceModel *model;
    QSqlQueryModel *sqlTablemodel;
    QStringList realtimeTableList;
    int sqlQueryCount =0 ;
    enum displayqueue{device_name =0,display_voltage=1,electric_current=2,display_frequency=3,phase=4,display_time=5};
    void getRealTimeData( const QString &query);
public slots:
    void displaySqlTableColumn(const QModelIndex &index,bool checked);
    void allChecked();
    void allClean();
    void cleanAllCheckBox();
    void cleanAllCleanBox();
    void displayTime();
    void OnGetData(QSqlQueryModel *model);
signals:
    void sendEventToRead(const QString &query);
private slots:
    void on_queryButton_clicked();
};

#endif // POWERREALTIMECURVEWIDGET_H

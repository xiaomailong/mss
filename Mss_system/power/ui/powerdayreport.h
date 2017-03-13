#ifndef DAYREPORT_H
#define DAYREPORT_H
#include "powerdisplaychoicemodel.h"
#include <QWidget>
#include <QSqlTableModel>
#include"power/ui/powerreaddata.h"

namespace Ui {
class PowerDayReport;
}
class PowerDayReport : public QWidget
{
    Q_OBJECT

public:
    explicit PowerDayReport(QWidget *parent = 0,PowerReadData *readData=NULL);
    ~PowerDayReport();

private:
    Ui::PowerDayReport *ui;
    PowerDisplayChoiceModel *model;
    QSqlQueryModel *sqlTablemodel;
    QStringList realtimeTableList;
    int sqlQueryCount =0 ;
public slots:
    void displaySqlTableColumn(const QModelIndex &index,bool checked);
    void allChecked();
    void allClean();
    void cleanAllCheckBox();
    void cleanAllCleanBox();
    void getDayReportData( );
    void OnGetData(QSqlQueryModel *model);
signals:
    void sendEventToRead(const QString &query);
};

#endif // DAYREPORT_H

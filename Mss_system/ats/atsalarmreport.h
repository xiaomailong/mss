#ifndef ATSALARMREPORT_H
#define ATSALARMREPORT_H

#include <QWidget>
#include <QSqlTableModel>
#include <QDateTime>
#include <ats/atsreaddata.h>

namespace Ui {
class AtsAlarmReport;
}

class AtsAlarmReport : public QWidget
{
    Q_OBJECT

public:
    explicit AtsAlarmReport(QWidget *parent = 0,AtsReadData *readData=NULL,int type =0,QString deviceName =NULL);
    ~AtsAlarmReport();
    void findData();
    void updateStatus();

signals:
    void sendEventToRead(const QString id,const QString tableName,QString filter);

public slots:
    void onDataFromRead(const QString id,QSqlTableModel *tableModel);

private slots:
    void on_findbutton_clicked();
    void on_firstbutton_clicked();
    void on_prebutton_clicked();
    void on_nextbutton_clicked();
    void on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime);
    void on_dateTimeEdit_2_dateTimeChanged(const QDateTime &dateTime);
    void on_devicecomboBox_currentIndexChanged(int index);
    void on_typecomboBox_currentIndexChanged(int index);
    void on_faultcomboBox_currentIndexChanged(int index);
    void on_faulttypecomboBox_currentIndexChanged(int index);
    void on_lastbutton_clicked();

private:
    Ui::AtsAlarmReport *ui;

    int type;
    QString deviceName;

    QDateTime dateTime1;
    QDateTime dateTime2;
    int totalPage;
    int currentPage;
    int totalCount;
    enum {pageRecordCount=100};
    bool isGetCount=true;
    QSqlTableModel *model;

    int deviceIndex;
    int deviceTypeIndex;
    int faultTypeIndex;
    int faultLevelIndex;
};

#endif // ATSALARMREPORT_H

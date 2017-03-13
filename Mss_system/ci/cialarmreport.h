#ifndef CIALARMREPORT_H
#define CIALARMREPORT_H

#include <QWidget>
#include <cireaddatathread.h>
#include <QDateTime>

namespace Ui {
class CiAlarmReport;
}

class CiAlarmReport : public QWidget
{
    Q_OBJECT

public:
    explicit CiAlarmReport(QWidget *parent = 0,CiReadDataThread *readData=NULL,int type =0,QString deviceName =NULL);
    ~CiAlarmReport();
    void findData();
    void updateStatus();

signals:
    void sendEventToRead(const QString id,const QString tableName,QString filter);

public slots:
    void onDataFromRead(const QString id,QSqlTableModel *tableModel);

private slots:
    void on_deviceComboBox_currentIndexChanged(int index);

    void on_typeComboBox_currentIndexChanged(int index);

    void on_faultTypeComboBox_currentIndexChanged(int index);

    void on_faultLevelComboBox_currentIndexChanged(int index);

    void on_beginDateTimeEdit_dateTimeChanged(const QDateTime &dateTime);

    void on_endDateTimeEdit_dateTimeChanged(const QDateTime &dateTime);

    void on_firstPage_clicked();

    void on_prevPage_clicked();

    void on_nextPage_clicked();

    void on_lastPage_clicked();

    void on_monitorButton_clicked();


private:
    Ui::CiAlarmReport *ui;
    int type;
    QString deviceName;

    QDateTime beginDateTime;
    QDateTime endDateTime;
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

#endif // CIALARMREPORT_H

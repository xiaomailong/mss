#ifndef VOBCALARMREPORT_H
#define VOBCALARMREPORT_H

#include <QWidget>
#include <QSqlTableModel>
#include <QDateTime>
#include "vobcreaddatathread.h"

namespace Ui {
class VobcAlarmReport;
}

class VobcAlarmReport : public QWidget
{
    Q_OBJECT

public:
    explicit VobcAlarmReport(QWidget *parent = 0,VobcReadDataThread *readData=NULL,int type =0,QString deviceName =NULL);
    ~VobcAlarmReport();
    void findData();
    void updateStatus();

signals:
    void sendEventToRead(const QString id,const QString tableName,QString filter);

public slots:
    void onDataFromRead(const QString id,QSqlTableModel *tableModel);

private slots:

    void on_findButton_clicked();

    void on_firstButton_clicked();

    void on_perviousButton_clicked();

    void on_nextButton_clicked();

    void on_lastButton_clicked();

    void on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime);

    void on_dateTimeEdit_2_dateTimeChanged(const QDateTime &dateTime);

    void on_deviceComboBox_currentIndexChanged(int index);

    void on_typeComboBox_currentIndexChanged(int index);

    void on_faultTypeComboBox_currentIndexChanged(int index);

    void on_faultLevelComboBox_currentIndexChanged(int index);

private:
    Ui::VobcAlarmReport *ui;
    int type;
    QString deviceName;

    QDateTime dateTime1;
    QDateTime dateTime2;
    int totalPage;
    int currentPage;
    int totalCount;
    enum
    {
        PageRecordCount=100
    };
    bool isGetCount=true;
    QSqlTableModel *model;
    bool isFinding=false;

    int deviceIndex;
    int deviceTypeIndex;
    int faultTypeIndex;
    int faultLevelIndex;
};

#endif // VOBCALARMREPORT_H

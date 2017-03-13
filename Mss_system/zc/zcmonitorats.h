#ifndef ZCMONITORATS_H
#define ZCMONITORATS_H

#include <QWidget>
#include <QSqlQueryModel>
#include "zcreaddata.h"
#include <QDateTime>
namespace Ui {
class ZCMonitorATS;
}

class ZCMonitorATS : public QWidget
{
    Q_OBJECT

public:
    explicit ZCMonitorATS(QWidget *parent = 0,ZCReadData *readData = NULL);
    ~ZCMonitorATS();
signals:
    void sendEventToRead(const QString,const QString);
public slots:
    void onEventFromRead(QSqlTableModel *);
private slots:
    void on_queryButton_clicked();
    void on_prevButton_clicked();
    void on_nextButton_clicked();
    void on_switchPageButton_clicked();
    void on_filter_cbo_currentIndexChanged(int);
    void on_comboBox_currentIndexChanged(int);
    void on_pushButton_clicked();
    void on_startDateEdit_dateTimeChanged(const QDateTime &dateTime);
    void on_endDateEdit_dateTimeChanged(const QDateTime &dateTime);

private:
    void findData(); //query data from database
    void updateStatus(); //refresh the button status and label message
    void getTotalPage();  //to get total page
private:
    Ui::ZCMonitorATS *ui;
    int packageIndex;
    int currentPage;  //current page
    int totalPage; //total page of the revord
    int totalRecrodCount; //total Recrod Count
    int PageRecordCount;  //Page Record Count
    bool isGetCount=true;
    bool isFinding=false;
    QSqlTableModel *model;
    QDateTime startDateTime;  //start time
    QDateTime endDateTime; //endtime
};

#endif // ZCMONITORATS_H

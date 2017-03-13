#ifndef POWERALARMSYSTEM_H
#define POWERALARMSYSTEM_H


#include <QWidget>
#include <QSqlTableModel>
#include <QDateTime>
#include "powerreaddata.h"

namespace Ui {
class PowerAlarmSystem;
}

class PowerAlarmSystem : public QWidget
{
    Q_OBJECT

public:
    explicit PowerAlarmSystem(QWidget *parent = 0,PowerReadData *readData=NULL,int type =0,QString deviceName =NULL);
    ~PowerAlarmSystem();
    void findData();
    void updateStatus();

signals:
    void sendEventToRead(const QString id,/*const QString tableName,*/QString filter);

public slots:
    void onDataFromRead(const QString id,QSqlQueryModel *tableModel);

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
    Ui::PowerAlarmSystem *ui;
    int type;
    QString deviceName;

    QDateTime dateTime1;
    QDateTime dateTime2;
    int totalPage;
    int currentPage;
    int totalCount;
    enum {pageRecordCount=100};
    bool isGetCount=true;
    QSqlQueryModel *model;

    int deviceIndex;
    int deviceTypeIndex;
    int faultTypeIndex;
    int faultLevelIndex;
};
#endif // POWERALARMSYSTEM_H

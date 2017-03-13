#ifndef VOBCMONITORATS_H
#define VOBCMONITORATS_H

#include <QWidget>
#include "vobcreaddatathread.h"
#include <QSqlTableModel>
#include <QDateTime>

namespace Ui {
class VobcMonitorATS;
}

class VobcMonitorATS : public QWidget
{
    Q_OBJECT

public:
    explicit VobcMonitorATS(QWidget *parent = 0,VobcReadDataThread *readData=NULL);
    ~VobcMonitorATS();
    void findData();
    void updateStatus();

signals:
    void sendEventToRead(const QString tableName,const QString filter);

public slots:
    void onDataFromRead(QSqlTableModel *model);


private slots:
    void on_findButton_clicked();

    void on_firstButton_clicked();

    void on_perviousButton_clicked();

    void on_nextButton_clicked();

    void on_lastButton_clicked();

    void on_packageComboBox_currentIndexChanged(int index);

    void on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime);

    void on_dateTimeEdit_2_dateTimeChanged(const QDateTime &dateTime);

private:
    Ui::VobcMonitorATS *ui;

    int packageIndex;
    QDateTime dateTime1;
    QDateTime dateTime2;
    int totalPage;
    int currentPage;
    int totalCount;
    enum {PageRecordCount=100};

    bool isGetCount=true;
    bool isFinding=false;

    QSqlTableModel *model;
};

#endif // VOBCMONITORATS_H

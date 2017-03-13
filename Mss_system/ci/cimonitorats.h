#ifndef CIMONITORATS_H
#define CIMONITORATS_H

#include <QWidget>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlError>
#include "cireaddatathread.h"
#include <QDateTime>

namespace Ui {
class CiMonitorAts;
}

class CiMonitorAts : public QWidget
{
    Q_OBJECT

public:
    explicit CiMonitorAts(QWidget *parent = 0,CiReadDataThread *readData = NULL);
    ~CiMonitorAts();

    void findData();

    void updateStatus();

signals:
    void sendEventToRead(const QString tableName,const QString filter);

public slots:
    void onEventFromRead(QSqlTableModel *model);

private slots:

    void on_monitorButton_clicked();

    void on_prevButton_clicked();

    void on_nextButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_startDateTime_dateTimeChanged(const QDateTime &dateTime);

    void on_endDateTime_dateTimeChanged(const QDateTime &dateTime);

    void on_firstPageButton_clicked();

    void on_lastPageButton_clicked();

private:
    Ui::CiMonitorAts *ui;

    int packageIndex;
    QDateTime beginDateTime;
    QDateTime endDateTime;
    int totalPage;
    int currentPage;
    int totalCount;
    enum {PageRecordCount=100};

    bool isGetCount=true;

    QSqlTableModel *model;

};

#endif // CIMONITORATS_H

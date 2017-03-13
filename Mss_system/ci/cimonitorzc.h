#ifndef CIMONITORZC_H
#define CIMONITORZC_H

#include <QWidget>
#include <QSqlTableModel>
#include "cireaddatathread.h"
#include <QDateTime>

namespace Ui {
class CiMonitorZc;
}

class CiMonitorZc : public QWidget
{
    Q_OBJECT

public:
    explicit CiMonitorZc(QWidget *parent = 0,CiReadDataThread *readData = NULL);
    ~CiMonitorZc();

    void findData();

    void updateStatus();

signals:
    void sendEventToRead(const QString tableName,const QString filter);

public slots:
    void onEventFromRead(QSqlTableModel *model);

private slots:
    void on_monitorButton_clicked();

    void on_prevPage_clicked();

    void on_nextPage_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_startDateTime_dateTimeChanged(const QDateTime &dateTime);

    void on_endDateTime_dateTimeChanged(const QDateTime &dateTime);

    void on_firstPageButton_clicked();

    void on_lastPageButton_clicked();

private:
    Ui::CiMonitorZc *ui;
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

#endif // CIMONITORZC_H

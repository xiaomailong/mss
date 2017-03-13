#ifndef ATSMONITORCI_H
#define ATSMONITORCI_H

#include <QWidget>
#include <QSqlTableModel>
#include <ats/atsreaddata.h>
#include <QDateTime>

#include <QThread>


namespace Ui {
class AtsMonitorCi;
}

class AtsMonitorCi : public QWidget
{
    Q_OBJECT

public:
    explicit AtsMonitorCi(QWidget *parent = 0,AtsReadData *readData=NULL);
    ~AtsMonitorCi();
    void findData();
    void updateStatus();
signals:
    void sendEventToRead(const QString tableName,const QString filter);

private slots:

    void onDataFromRead(QSqlTableModel *model);
    void on_pushButton_clicked();
    void on_firstbutton_clicked();
    void on_prebutton_clicked();
    void on_nextbutton_clicked();
    void on_comboBox_currentIndexChanged(int index);
    void on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime);
    void on_dateTimeEdit_2_dateTimeChanged(const QDateTime &dateTime);

    void on_lastbutton_clicked();

private:
    Ui::AtsMonitorCi *ui;

    QSqlTableModel *model;
    int packageIndex;
    QDateTime dateTime1;
    QDateTime dateTime2;
    int totalPage;
    int currentPage;
    int totalCount;
    enum {pageRecordCount=100};
    bool isGetCount=true;
};

#endif // ATSMONITORCI_H

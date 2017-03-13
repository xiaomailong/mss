#ifndef CI_ROUTE_THREAD_H
#define CI_ROUTE_THREAD_H

#include <QObject>
#include <QtSql>
#include "ci_data.h"
#include <QUdpSocket>
#include "vobc_data.h"
Q_DECLARE_METATYPE(vobc_subsys_msg_t)
class CiService : public QObject
{
    Q_OBJECT
public:
    explicit CiService(QObject *parent = 0);
    void initCiData();
    ~CiService();
    void dealCiUdpData(quint8* buf, quint16 len);
    enum CiProcessError
    {
        DbOpenError = 1,
        TbCreateError,
        EntryInsertError,
        DataInvalid
    };
public slots:
    void receiveUdpData();
    void receiveRouteData(quint8* buf,quint16 len);
    void start();
signals:
    void error(int type);
    void started();
    void sendToCiUi(ci_ci_t* data);
    void ciAlarm(vobc_subsys_msg_t alarm);
private:
     QSqlDatabase dbConn;
     QSqlQuery dbQuery;
     bool createTable(const QString& queryStr);
     bool openDB();
     void qDebugErrorValid(QString header);
     void qDebugErrorInsert(QString header);
     QUdpSocket* ciUdpClient;
};

#endif // CI_ROUTE_THREAD_H

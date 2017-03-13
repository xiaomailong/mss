#ifndef SIMULATE_DATA_THREAD_H
#define SIMULATE_DATA_THREAD_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QUdpSocket>

class CiSimulate : public QObject
{
    Q_OBJECT
public:
    explicit CiSimulate(QObject *parent = 0);
    ~CiSimulate();
signals:
    void sendCiRoute(quint8* buf,quint16 len);
private:
    QUdpSocket* ciUdpService;
    QTimer* ciUdpTimer;
    QTimer* ciRouteTimer;
public slots:
    void start();
private slots:
     void sendCiUdpData();
     void sendCiRouteData();
};

#endif // SIMULATE_DATA_THREAD_H

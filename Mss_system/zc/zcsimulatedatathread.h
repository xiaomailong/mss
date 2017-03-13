#ifndef ZcSimulateDataThread_H
#define ZcSimulateDataThread_H

#include <QObject>
#include <QUdpSocket>
#include <QThread>

class ZcSimulateDataThread : public QObject
{
    Q_OBJECT
public:
    explicit ZcSimulateDataThread(QObject *parent = 0);
    bool isStop = false;

signals:
    void send_zc(quint8* buf, quint16 len);
    void send_zc2(quint8* buf, quint16 len);

public slots:
    void start();
private:
    QUdpSocket *sendZcUdpSocket;
};

#endif // ZcSimulateDataThread_H

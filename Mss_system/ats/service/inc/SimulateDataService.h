#ifndef SIMULATEDATASERVICE_H
#define SIMULATEDATASERVICE_H

#include <QObject>
#include <QTimer>
#include <QUdpSocket>

class SimulateDataService : public QObject
{
    Q_OBJECT
public:
    explicit SimulateDataService(QObject *parent = 0);
    ~SimulateDataService();
private:
    QTimer *m_timer_ats_vobc;
    QTimer *m_timer_ats_ci;
    QTimer *m_timer_ats_zc;
    QUdpSocket *m_receiver;
    quint32 m_ats_vobc_msg_list;
    quint32 m_ats_ci_msg_list;
    quint32 m_ats_zc_msg_list;
    quint32 m_ats_mss_msg_list;

signals:
    void dataReceived(quint8* buf, quint16 len);
    void deviceDataReceived(quint8* buf, quint16 len);
    void msgPacked(quint8* buf, quint16 len);
public slots:
    void start();
    void stop();
private slots:
    void onTimeout();
    void onReadyRead();
};

#endif // SIMULATEDATASERVICE_H

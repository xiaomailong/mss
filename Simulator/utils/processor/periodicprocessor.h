#ifndef PERIODICPROCESSOR_H
#define PERIODICPROCESSOR_H

#include <QObject>
#include <QTimer>
#include "abstractprocessor.h"
class PeriodicProcessor: public QObject
{
    Q_OBJECT
public:
    explicit PeriodicProcessor(NetworkProcessor::NetworkType networkType = NetworkProcessor::BasicUdpType);
    virtual ~PeriodicProcessor();
    void setNetworktype(NetworkProcessor::NetworkType networkType);
    void start(int msec = 250);
    void stop();
    void setHost(const QHostAddress &host);
    void setPort(quint16 port);
protected:
    void setData(const QByteArray &dataGram);
private slots:
    void onTimeOut();
    void onFinished();
private:
    Q_DISABLE_COPY(PeriodicProcessor)
    virtual AbstractProcessor* constructProcessor() = 0;
private:
    QByteArray dataGram;
    QHostAddress host;
    quint16 port;
    QTimer timer;
    NetworkProcessor::NetworkType networkType;
};

#endif // PERIODICPROCESSOR_H

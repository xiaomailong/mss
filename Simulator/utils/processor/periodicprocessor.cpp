#include "periodicprocessor.h"
#include <QThread>
#include "simulatorconfig.h"
#include "simulatorlogconfig.h"

PeriodicProcessor::PeriodicProcessor(NetworkProcessor::NetworkType networkType)
{
    SIMULATOR_LOG_ENTRY();
    this->networkType = networkType;
    timer.setSingleShot(false);
}
PeriodicProcessor::~PeriodicProcessor()
{
    SIMULATOR_LOG_ENTRY();
    timer.stop();
}

void PeriodicProcessor::setNetworktype(NetworkProcessor::NetworkType networkType)
{
    SIMULATOR_LOG_ENTRY();
    this->networkType = networkType;
}

void PeriodicProcessor::setData(const QByteArray &dataGram)
{
    SIMULATOR_LOG_ENTRY();
    this->dataGram = dataGram;
}

void PeriodicProcessor::setHost(const QHostAddress &host)
{
    SIMULATOR_LOG_ENTRY();
    this->host = host;
}
void PeriodicProcessor::setPort(quint16 port)
{
    SIMULATOR_LOG_ENTRY();
    this->port = port;
}
void PeriodicProcessor::start(int msec)
{
    SIMULATOR_LOG_ENTRY();
    timer.start(msec);
    connect(&timer, &QTimer::timeout, this, &PeriodicProcessor::onTimeOut);
}

void PeriodicProcessor::onTimeOut()
{
    SIMULATOR_LOG_ENTRY();
    AbstractProcessor* processor = constructProcessor();
    processor->setPort(port);
    processor->setHost(host);
    connect(processor, &AbstractProcessor::finished, this, &PeriodicProcessor::onFinished);
    processor->start();

}

void PeriodicProcessor::onFinished()
{
    SIMULATOR_LOG_ENTRY();
    delete sender();
}
void PeriodicProcessor::stop()
{
    SIMULATOR_LOG_ENTRY();
    timer.stop();
}


#include "abstractprocessor.h"
#include "simulatorconfig.h"
#include "simulatorlogconfig.h"

AbstractProcessor::AbstractProcessor()
{
    SIMULATOR_LOG_ENTRY();
    processor = new NetworkProcessor();
}

AbstractProcessor::AbstractProcessor(NetworkProcessor::NetworkType networkType) : QObject()
{
    SIMULATOR_LOG_ENTRY();
    switch(networkType)
    {
    case NetworkProcessor::BasicUdpType:
    {
        processor = new NetworkProcessor();
    }
        break;
    case NetworkProcessor::RsspIType:
    {
        SIMULATOR_WARN()<< networkType << " Unsupport yet!!!! Use default instead";
        processor = new NetworkProcessor();
    }
        break;
    default:
    {
        processor = NULL;
    }
        break;
    }
}

AbstractProcessor::~AbstractProcessor()
{
    SIMULATOR_LOG_ENTRY();
    thread.quit();
    thread.wait();
    if(processor != NULL)
    {
        delete processor;
    }
}

void AbstractProcessor::setHost(const QHostAddress &host)
{
    SIMULATOR_LOG_ENTRY();
    if(processor != NULL)
    {
        processor->setHost(host);
    }

}
void AbstractProcessor::setPort(quint16 port)
{
    SIMULATOR_LOG_ENTRY();
    if(processor != NULL)
    {
        processor->setPort(port);
    }

}
void AbstractProcessor::setData(const QByteArray &dataGram)
{
    SIMULATOR_LOG_ENTRY();
    if(processor != NULL)
    {
        processor->setData(dataGram);
    }
}

void AbstractProcessor::start()
{
    SIMULATOR_LOG_ENTRY();
    if(processor != NULL)
    {
        processor->moveToThread(&thread);
        constructData();
        connect(&thread, &QThread::started, processor, &NetworkProcessor::start, Qt::AutoConnection);
        connect(&thread, &QThread::finished, processor, &NetworkProcessor::stop, Qt::AutoConnection);
        connect(processor, &NetworkProcessor::finished, this, &AbstractProcessor::onFinished, Qt::AutoConnection);
        connect(processor, &NetworkProcessor::error, this, &AbstractProcessor::onError, Qt::AutoConnection);
        thread.start();
    }
    else
    {
        emit finished(static_cast<int>(NetwrokProcessorNotFound));
    }
}


void AbstractProcessor::onFinished()
{
    SIMULATOR_LOG_ENTRY();
    thread.quit();
    thread.wait();
    emit finished(0);
}
void AbstractProcessor::onError(int code)
{
    SIMULATOR_LOG_ENTRY();
    SIMULATOR_WARN()<<code;
    thread.quit();
    thread.wait();
    emit finished(NetworkError);
}

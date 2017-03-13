#include "networkprocessor.h"
#include "simulatorlogconfig.h"
#include "simulatorconfig.h"
NetworkProcessor::NetworkProcessor()
{
    SIMULATOR_LOG_ENTRY();
    sender = NULL;
}

NetworkProcessor::~NetworkProcessor()
{
    SIMULATOR_LOG_ENTRY();
}

void NetworkProcessor::setData(const QByteArray &dataGram)
{
    SIMULATOR_LOG_ENTRY();
    this->dataGram = dataGram;
}

void NetworkProcessor::setHost(const QHostAddress &host)
{
    SIMULATOR_LOG_ENTRY();
    this->host = host;
}

void NetworkProcessor::setPort(quint16 port)
{
    SIMULATOR_LOG_ENTRY();
    this->port = port;
}

void NetworkProcessor::rePackData()
{
    SIMULATOR_LOG_ENTRY();
    //Do nothing
    //Child can use this function to repack data in dataGram
}

void NetworkProcessor::start()
{
    SIMULATOR_LOG_ENTRY();
    SIMULATOR_INFO()<<dataGram;
    sender = new QUdpSocket();
    connect(sender, QUdpSocket::bytesWritten, this, NetworkProcessor::bytesWritten);
    //Repack data in dataGram
    rePackData();
    if(sender->writeDatagram(dataGram.constData(),dataGram.size(), host, port) <= 0){
        SIMULATOR_WARN()<<"Error detected!!!";
        emit error(static_cast<int>(DataInvalidError));
    }
}
void NetworkProcessor::stop()
{
    SIMULATOR_LOG_ENTRY();
    if(sender != NULL){
        delete sender;
        sender = NULL;
    }
}

void NetworkProcessor::bytesWritten(qint64 bytes)
{
    SIMULATOR_LOG_ENTRY();
    SIMULATOR_DEBUG()<<bytes;
    emit finished();
}

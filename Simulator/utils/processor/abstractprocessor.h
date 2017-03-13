#ifndef ABSTRACTPROCESSOR_H
#define ABSTRACTPROCESSOR_H
#include <QObject>
#include <QThread>
#include "networkprocessor.h"
class AbstractProcessor : public QObject
{
    Q_OBJECT
public:
    enum ProcessorErrorCode
    {
        NetwrokProcessorNotFound = 1,
        NetworkError
    };
    explicit AbstractProcessor(NetworkProcessor::NetworkType networkType);
    AbstractProcessor();
    virtual ~AbstractProcessor();
    void start();
    void setHost(const QHostAddress &host);
    void setPort(quint16 port);
protected:
    void setData(const QByteArray &dataGram);
private:
    virtual void constructData() = 0;
signals:
    void finished(int result);
private slots:
    void onFinished();
    void onError(int code);
private:
    Q_DISABLE_COPY(AbstractProcessor)
private:
    QThread thread;
    NetworkProcessor *processor;
};

#endif // ABSTRACTPROCESSOR_H

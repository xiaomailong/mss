#ifndef NETWORKPROCESSOR_H
#define NETWORKPROCESSOR_H

#include <QObject>
#include <QUdpSocket>
class NetworkProcessor : public QObject
{
    Q_OBJECT
public:
    enum NetworkType {
        BasicUdpType,
        RsspIType
    };
    enum NetworkProcessorError{
      DataInvalidError = 1,
    };
    NetworkProcessor();
    virtual ~NetworkProcessor();
    void setData(const QByteArray &dataGram);
    void setHost(const QHostAddress &host);
    void setPort(quint16 port);
signals:
    void finished();
    void error(int code);
public slots:
    void start();
    void stop();
    virtual void rePackData();
protected:
    QByteArray dataGram;
private:
    Q_DISABLE_COPY(NetworkProcessor)
private slots:
    void bytesWritten(qint64 bytes);
private:
    QUdpSocket *sender;
    QHostAddress host;
    quint16 port;
};

#endif // NETWORKPROCESSOR_H

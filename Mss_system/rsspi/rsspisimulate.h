#ifndef RSSPISIMULATE_H
#define RSSPISIMULATE_H

#include <QObject>
#include <QDebug>
#include <QUdpSocket>
#include "rsspi.h"

class RsspiSimulate : public QObject
{
    Q_OBJECT
public:
    explicit RsspiSimulate(QObject *parent = 0);
    void BindSend();

signals:

public slots:
    void SimulateMssRsspiData(quint8 *userData, quint16 len);

private:
    QUdpSocket *pRsspiSend;
    RsspI *pRsspi;
    QByteArray sendBuf;
    QByteArray SimulateData;
};

#endif // RSSPISIMULATE_H

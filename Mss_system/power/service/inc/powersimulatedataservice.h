#ifndef POWERSIMULATEDATASERVICE_H
#define POWERSIMULATEDATASERVICE_H

#include "power_data.h"
#include "mssdbconfig.h"

#include <QObject>
#include <QThread>
#ifdef USE_UDP
#include <QUdpSocket>
#endif


class PowerSimulateDataService : public QThread
{
    Q_OBJECT
public:
    PowerSimulateDataService();

signals:
    void sendPowerSimulateData(quint8* buf);
    /**
     * @brief sendPowerSimulateData :a signal used to tell the powerprocess here send a record of data,
     *                               please receive it
     *
     * @param buf :the raw data
     * @return
      */

protected:
    void run();
    /**
     * @brief run :send the simulated data ,the real data will applied by suppliers ,here we apply a way to send data
     *
      */

#ifdef USE_UDP
    QUdpSocket *udpSocketOfPowersend; //UDPÌ×½Ó×Ö
#endif
};

#endif // POWERSIMULATEDATASERVICE_H

#ifndef ATSPERIODICPROCESSOR_H
#define ATSPERIODICPROCESSOR_H

#include <QObject>
#include "periodicprocessor.h"
#include "atsdatafactory.h"
#include "atsburstprocessor.h"
class AtsPeriodicProcessor: public PeriodicProcessor
{
    Q_OBJECT
public:
    AtsPeriodicProcessor(AtsDataFactory::AtsDataType dataType,
                                  const void* extraInfo = NULL,
                                  NetworkProcessor::NetworkType networkType = NetworkProcessor::BasicUdpType);
    ~AtsPeriodicProcessor();
private:
    AbstractProcessor* constructProcessor();
    AtsPeriodicProcessor() =delete;
    Q_DISABLE_COPY(AtsPeriodicProcessor)
private:
    AtsDataFactory::AtsDataType dataType;
    const void *extraInfo;
    NetworkProcessor::NetworkType networkType;
};

#endif // ATSPERIODICPROCESSOR_H

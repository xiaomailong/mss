#ifndef ATSBURSTPROCESSOR_H
#define ATSBURSTPROCESSOR_H
#include "atsdatafactory.h"
#include "burstprocessor.h"
class AtsBurstProcessor : public BurstProcessor
{
    Q_OBJECT
public:
    AtsBurstProcessor(AtsDataFactory::AtsDataType dataType,
                    const void* extraInfo = NULL,
                    NetworkProcessor::NetworkType networkType = NetworkProcessor::BasicUdpType);
    ~AtsBurstProcessor();
private:
    void constructData();
private:
    AtsBurstProcessor() =delete;
    Q_DISABLE_COPY(AtsBurstProcessor)
private:
    AtsDataFactory::AtsDataType dataType;
    const void *extraInfo;
    NetworkProcessor::NetworkType networkType;
};

#endif // ATSBURSTPROCESSOR_H

#ifndef BURSTPROCESSOR_H
#define BURSTPROCESSOR_H

#include "abstractprocessor.h"
class BurstProcessor: public AbstractProcessor
{
    Q_OBJECT
public:
    explicit BurstProcessor(NetworkProcessor::NetworkType networkType = NetworkProcessor::BasicUdpType);
    virtual ~BurstProcessor();
private:
    virtual void constructData();
private:
    Q_DISABLE_COPY(BurstProcessor)
};

#endif // BURSTPROCESSOR_H

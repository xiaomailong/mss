#include "burstprocessor.h"
#include "simulatorconfig.h"
#include "simulatorlogconfig.h"
BurstProcessor::BurstProcessor(NetworkProcessor::NetworkType networkType)
    :AbstractProcessor(networkType)
{
    SIMULATOR_LOG_ENTRY();
}

BurstProcessor::~BurstProcessor()
{
    SIMULATOR_LOG_ENTRY();
}
void BurstProcessor::constructData()
{
    SIMULATOR_LOG_ENTRY();
}

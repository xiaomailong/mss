#include "atsperiodicprocessor.h"
#include "atsburstprocessor.h"
#include "simulatorconfig.h"
#include "simulatorlogconfig.h"
AtsPeriodicProcessor::AtsPeriodicProcessor(AtsDataFactory::AtsDataType dataType,
                                           const void* extraInfo,
                                           NetworkProcessor::NetworkType networkType)
    :PeriodicProcessor(networkType)
{
    ATS_SIMULATOR_LOG_ENTRY();
    this->dataType = dataType;
    this->extraInfo = extraInfo;
    this->networkType = networkType;
}

AtsPeriodicProcessor::~AtsPeriodicProcessor()
{
    ATS_SIMULATOR_LOG_ENTRY();
    if(this->extraInfo != NULL)
    {
        //should do free!!
    }
}

AbstractProcessor* AtsPeriodicProcessor::constructProcessor()
{
    ATS_SIMULATOR_LOG_ENTRY();
    AbstractProcessor* processor = new AtsBurstProcessor(dataType, extraInfo, networkType);
    return processor;
}

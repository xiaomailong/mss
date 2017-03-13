#include "atsburstprocessor.h"
#include "atsdatafactory.h"
#include "simulatorconfig.h"
#include "simulatorlogconfig.h"

AtsBurstProcessor::AtsBurstProcessor(AtsDataFactory::AtsDataType dataType,
                                 const void* extraInfo,
                                 NetworkProcessor::NetworkType networkType)
    :BurstProcessor(networkType)
{
    ATS_SIMULATOR_LOG_ENTRY();
    this->dataType = dataType;
    this->extraInfo = extraInfo;
    this->networkType = networkType;
}
AtsBurstProcessor::~AtsBurstProcessor()
{
    ATS_SIMULATOR_LOG_ENTRY();
}

void AtsBurstProcessor::constructData()
{
    quint8* buf = NULL;
    quint16 len = 0;
    ATS_SIMULATOR_LOG_ENTRY();
    AtsDataFactory& factory = AtsDataFactory::getInstance();
    if(extraInfo != NULL)
    {
        factory.getData(dataType, extraInfo, &buf, &len);
    }
    else
    {
        factory.getData(dataType, &buf, &len);
    }
    setData(QByteArray((const char*)buf, len));
    delete[] buf;
}



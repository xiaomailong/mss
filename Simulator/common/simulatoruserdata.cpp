#include "simulatoruserdata.h"
#include "atsperiodicprocessor.h"
#include "simulatorconfig.h"
#include "simulatorlogconfig.h"
SimulatorUserData:: ~SimulatorUserData()
{
    SIMULATOR_LOG_ENTRY();
    if(data != NULL)
    {
        delete data;
        data = NULL;
    }
}
SimulatorUserData:: SimulatorUserData(QObject* data) : data(data)
{
    SIMULATOR_LOG_ENTRY();
}

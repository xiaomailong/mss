#ifndef SIMULATORUSERDATA_H
#define SIMULATORUSERDATA_H

#include <QObject>
#define SIMULATOR_USER_DATA_ID 0x0200
class SimulatorUserData : public QObjectUserData
{
public:
    SimulatorUserData(QObject* data);
    ~SimulatorUserData();
public:
    QObject* data;
};

#endif // SIMULATORUSERDATA_H

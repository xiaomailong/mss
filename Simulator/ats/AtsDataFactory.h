#ifndef ATSDATAFACTORY_H
#define ATSDATAFACTORY_H
#include <qglobal.h>
#include <QAtomicInteger>
class AtsDataFactory
{
private:
    AtsDataFactory();
    Q_DISABLE_COPY(AtsDataFactory)
    ~AtsDataFactory();
public:
    enum AtsDataType
    {
        AtsVobcHeartBeatDataType,
        AtsVobcAtoCmdDataType,
        AtsCiHeartBeatDataType,
        AtsCiCmdDataType,
        AtsCiStatusDataType,
        AtsZcHeartBeatDataType,
        AtsZcTsrValidateDataType,
        AtsZcTsrExecCmdDataType,
        AtsZcTsrOnConfirmDataType,
        AtsMssAlarmDataType,
        VobcMssAlarmDataType
    };
public:
    static AtsDataFactory& getInstance();
    void getData(AtsDataType type, quint8**bufPtr, quint16* lenPtr);
    void getData(AtsDataType type, const void* extraInfo, quint8**bufPtr, quint16* lenPtr);
private:
    QAtomicInteger<quint32> atsVobcMsgList;
    QAtomicInteger<quint32> atsCiMsgList;
    QAtomicInteger<quint32> atsZcMsgList;
    QAtomicInteger<quint32> atsMssMsgList;
};
#endif // ATSDATAFACTORY_H

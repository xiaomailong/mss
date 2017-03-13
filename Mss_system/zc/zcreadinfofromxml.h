#ifndef ZCREADINFOFROMXML_H
#define ZCREADINFOFROMXML_H
#include <QString>
#include <QStringList>

class ZCReadInfofromXml
{
public:
    ZCReadInfofromXml();
    static QString readInfoFromXML(QString filePath, QString deviceName, QString deviceNo);
};

#endif // ZCREADINFOFROMXML_H

#ifndef POWERDOMXML_H
#define POWERDOMXML_H
#include <QString>

#include <QDomDocument>
#include <QDomElement>

class PowerdomXml
{
public:
    PowerdomXml();
    static QString readInfoFromXML(QString filePath, QString deviceName, QString deviceNo);
};

#endif // POWERDOMXML_H

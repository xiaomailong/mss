#ifndef VOBCDOMXML_H
#define VOBCDOMXML_H
#include <QString>
#include <QStringList>
#include <QDomDocument>
#include <QDomElement>


class VobcDomXML
{
public:
    VobcDomXML();

    static QStringList readXML(QString filePath, QString deviceName);

    static QStringList readXML(QString filePath, QString deviceName,bool isHead);

    static QString readInfoFromXML(QString filePath, QString deviceName, QString deviceNo);

};

#endif // VOBCDOMXML_H

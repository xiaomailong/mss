#ifndef ATSDOMXML_H
#define ATSDOMXML_H

#include <QString>
#include <QStringList>


class AtsDomXml
{
public:
    AtsDomXml();
    static QStringList readXML(QString filePath, QString deviceName);

    static QString readInfoFromXML(QString filePath, QString deviceName, QString deviceNo);

};

#endif // ATSDOMXML_H

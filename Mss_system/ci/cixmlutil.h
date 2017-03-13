#ifndef CIXMLUTIL_H
#define CIXMLUTIL_H
#include <QString>


class CiXMLUtil
{
public:
    CiXMLUtil();

    static QString readXML(QString filePath ,QString deviceName,QString deviceCode);

};

#endif // XMLUTIL_H

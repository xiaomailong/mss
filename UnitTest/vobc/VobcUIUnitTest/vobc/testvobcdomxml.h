#ifndef TESTVOBCDOMXML_H
#define TESTVOBCDOMXML_H

#include <QObject>
#include <QtTest>
#include "vobcdomxml.h"

class TestVobcDomXml : public QObject
{
    Q_OBJECT
public:
    TestVobcDomXml();


private Q_SLOTS:
    void testReadXML();
    void testReadXMLLoc();
    void testReadInfoFromXML();

};

#endif // TESTVOBCDOMXML_H

#ifndef TESTATSDOMXML_H
#define TESTATSDOMXML_H

#include <QObject>
#include <QtTest>

#include <atsdomxml.h>

class TestAtsDomXml : public QObject
{
    Q_OBJECT
public:
    explicit TestAtsDomXml(QObject *parent = 0);

private Q_SLOTS:
    void testReadXML();
    void testReadInfoFromXML();
};

#endif // TESTATSDOMXML_H

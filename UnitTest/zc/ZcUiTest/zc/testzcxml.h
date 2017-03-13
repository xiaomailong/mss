#ifndef TESTZCXML_H
#define TESTZCXML_H
#include <QObject>
#include <QtTest>

class TestZcXml: public QObject
{
    Q_OBJECT
public:
    TestZcXml();

private Q_SLOTS:
    void testReadInfoFromXML();
};

#endif // TESTZCXML_H

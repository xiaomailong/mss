#ifndef TESTCIXML_H
#define TESTCIXML_H

#include <QObject>

class TestCiXml : public QObject
{
    Q_OBJECT
public:
    TestCiXml();

signals:

private Q_SLOTS:
    void testReadXML();
};

#endif // TESTCIXML_H

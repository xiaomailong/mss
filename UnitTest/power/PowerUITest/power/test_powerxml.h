#ifndef TEST_POWERXML_H
#define TEST_POWERXML_H

#include <QObject>

class Test_PowerXml : public QObject
{
    Q_OBJECT
public:
    explicit Test_PowerXml(QObject *parent = 0);

signals:

public slots:
private Q_SLOTS:
    void testReadXML();
};

#endif // TEST_POWERXML_H

#include "testatsdomxml.h"
#include <QtTest>

#include <atsdomxml.h>

TestAtsDomXml::TestAtsDomXml(QObject *parent) : QObject(parent)
{

}

void TestAtsDomXml::testReadXML()
{
    QStringList atpList=AtsDomXml::readXML("://xml/ats/ats_workstation.xml","workstation");
    QVERIFY(atpList.length()==5);
    QVERIFY(atpList.contains("displayws"));
    QVERIFY(atpList.contains("dispatherws"));
    QVERIFY(atpList.contains("rundisplayws"));
    QVERIFY(atpList.contains("largescreenws"));
    QVERIFY(atpList.contains("atsmaintenancews"));
}

void TestAtsDomXml::testReadInfoFromXML()
{
    QString tip=AtsDomXml::readInfoFromXML("://xml/ats/ats_workstation.xml","workstation","displayws");
    QVERIFY(tip.length()>0);
    QVERIFY(tip.contains("设备类型"));
    QVERIFY(tip.contains("安装位置"));
    QVERIFY(tip.contains("制造厂商"));
    QVERIFY(tip.contains("服役起始时间"));
    QVERIFY(tip.contains("基本配置"));
    QVERIFY(tip.contains("系统配置"));
    QVERIFY(tip.contains("软件版本"));
    QVERIFY(tip.contains("维修记录"));
}

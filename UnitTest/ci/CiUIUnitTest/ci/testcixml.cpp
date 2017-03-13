#include "testcixml.h"
#include "cixmlutil.h"
#include <QTest>

TestCiXml::TestCiXml()
{

}

void TestCiXml::testReadXML()
{
    QString tip = CiXMLUtil::readXML("://xml/ci/ciaxlecounter.xml","COUNTER","1");
    QVERIFY(tip.length()>0);
    QVERIFY(tip.contains("设备名称"));
    QVERIFY(tip.contains("安装位置"));
    QVERIFY(tip.contains("供电"));
    QVERIFY(tip.contains("输出"));
    QVERIFY(tip.contains("车速范围"));
    QVERIFY(tip.contains("环境温度"));
    QVERIFY(tip.contains("维修记录"));
    QVERIFY(tip.contains("使用年限"));
    QVERIFY(tip.contains("制造厂商"));
    QVERIFY(tip.contains("出厂日期"));
    QVERIFY(tip.contains("服役起始时间"));

}

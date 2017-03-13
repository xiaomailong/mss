#include "test_powerxml.h"
#include "powerdomxml.h"
#include <QtTest>
Test_PowerXml::Test_PowerXml(QObject *parent) : QObject(parent)
{

}


void Test_PowerXml::testReadXML()
{
    QString tip=PowerdomXml::readInfoFromXML("://xml/power/power_deviceinfo.xml","atp","DEVICE1");
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

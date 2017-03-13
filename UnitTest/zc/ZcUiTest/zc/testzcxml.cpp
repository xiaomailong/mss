#include "testzcxml.h"
#include "zc/zcreadinfofromxml.h"
TestZcXml::TestZcXml()
{

}
void TestZcXml::testReadInfoFromXML()
{
    QString tip=ZCReadInfofromXml::readInfoFromXML("://xml/zc/zcInformation.xml","ZCI","1");
    QVERIFY(tip.length()>0);
    QVERIFY(tip.contains("厂商信息"));
    QVERIFY(tip.contains("服役起始时间"));
    QVERIFY(tip.contains("cpu信息"));
    QVERIFY(tip.contains("memory info"));
    QVERIFY(tip.contains("安装的操作系统"));
    QVERIFY(tip.contains("安装软件版本"));
    QVERIFY(tip.contains("维修记录"));
    QVERIFY(tip.contains("授权登录人员信息"));

}

#include "testvobcdomxml.h"
#include <QtTest>
#include "vobcdomxml.h"

TestVobcDomXml::TestVobcDomXml()
{

}

void TestVobcDomXml::testReadXML()
{
    QStringList atpList=VobcDomXML::readXML("://xml/vobc/vobc_atp.xml","atp");
    QVERIFY(atpList.length()==2);
    QVERIFY(atpList.contains("Dx-1654"));
    QVERIFY(atpList.contains("atp_2"));

    QStringList btmList=VobcDomXML::readXML("://xml/vobc/vobc_btm.xml","btm");
    QVERIFY(btmList.length()==2);
    QVERIFY(btmList.contains("btm_1"));
    QVERIFY(btmList.contains("Dx-1654"));

}

void TestVobcDomXml::testReadXMLLoc()
{
    QStringList atpListHead=VobcDomXML::readXML("://xml/vobc/vobc_atp.xml","atp",true);
    QVERIFY(atpListHead.length()==1);
    QVERIFY(atpListHead.contains("Dx-1654"));

    QStringList atpListTail=VobcDomXML::readXML("://xml/vobc/vobc_atp.xml","atp",false);
    QVERIFY(atpListTail.length()==1);
    QVERIFY(atpListTail.contains("atp_2"));
}

void TestVobcDomXml::testReadInfoFromXML()
{
    QString tip=VobcDomXML::readInfoFromXML("://xml/vobc/vobc_atp.xml","atp","Dx-1654");
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

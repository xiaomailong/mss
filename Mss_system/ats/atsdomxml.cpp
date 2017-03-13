#include "atsdomxml.h"

#include <QFile>
#include <QDomDocument>
#include <QDomProcessingInstruction>
#include <QDomElement>
#include <QTextStream>
#include <QDebug>
#include <QDateTime>

#define ATS_DEBUG_ENABLED 0

#if ATS_DEBUG_ENABLED
#define ATS_DEBUG       qDebug
#define ATS_INFO        qInfo
#define ATS_WARN        qWarning
#define ATS_FATAL       qFatal
#define ATS_CRITICAL       qCritical
#else
#define ATS_DEBUG       QT_NO_QDEBUG_MACRO
#define ATS_INFO        QT_NO_QDEBUG_MACRO
#define ATS_WARN        QT_NO_QDEBUG_MACRO
#define ATS_FATAL       QT_NO_QDEBUG_MACRO
#define ATS_CRITICAL    QT_NO_QDEBUG_MACRO
#endif

AtsDomXml::AtsDomXml()
{

}

QStringList AtsDomXml::readXML(QString filePath, QString deviceName)
{
    QStringList deviceNoList;

    QFile file(filePath);
    if(!file.exists())
    {
        ATS_DEBUG() << "ats xml file not exist";
        return deviceNoList;
    }
    bool isOk = file.open(QIODevice::ReadOnly);
    if(isOk==false)
    {
        ATS_DEBUG() << "readXML ReadOnly error";
        return deviceNoList;
    }
    QDomDocument doc;
    isOk = doc.setContent(&file);
    if(isOk==false)
    {
        ATS_DEBUG() << "readXML setContent error";
        return deviceNoList;
    }
    file.close();

    QDomNodeList nodeList = doc.elementsByTagName(deviceName);
    for( int i = 0; i < nodeList.count(); i++ )
    {
        QDomElement e = nodeList.at(i).toElement();
        QString number=e.attribute("deviceNo");
        //ATS_DEBUG()<<"deviceNo:"<<number;
        deviceNoList.append(number);
    }
    return deviceNoList;
}


QString AtsDomXml::readInfoFromXML(QString filePath, QString deviceName, QString deviceNo)
{
    QString info;
    QFile file(filePath);
    if(!file.exists())
    {
        ATS_DEBUG() << "ats xml file not exist";
        return info;
    }
    bool isOk = file.open(QIODevice::ReadOnly);
    if(isOk==false)
    {
        ATS_DEBUG() << "readXML ReadOnly error";
        return info;
    }
    QDomDocument doc;
    isOk = doc.setContent(&file);
    if(isOk==false)
    {
        ATS_DEBUG() << "readXML setContent error";
        return info;
    }
    file.close();

    QDomNodeList nodeList = doc.elementsByTagName(deviceName);
    for( int i = 0; i < nodeList.count(); i++ )
    {
        QDomElement e = nodeList.at(i).toElement();
        QString number=e.attribute("deviceNo");
        if(number.compare(deviceNo))
        {
            continue;
        }
        info.append("设备编号:"+number+"\n");
        QDomNodeList childlist = e.childNodes();
        for( int i = 0; i < childlist.count(); i++ )
        {
            QDomNode node = childlist.at( i );
            if(!node.isElement())
            {
                ATS_DEBUG()<<"node not element";
            }
            if(node.toElement().tagName()=="type")
            {
                info.append("设备类型:"+node.toElement().text()+"\n");
            }
            else if(node.toElement().tagName()=="position")
            {
                info.append("安装位置:"+node.toElement().text()+"\n");
            }
            else if(node.toElement().tagName()=="manufacture")
            {
                info.append("制造厂商:"+node.toElement().text()+"\n");
            }
            else if(node.toElement().tagName()=="purchasedate")
            {
                info.append("服役起始时间:"+node.toElement().text()+"\n");
            }
            else if(node.toElement().tagName()=="baseconfig")
            {
                info.append("基本配置:"+node.toElement().text()+"\n");
            }
            else if(node.toElement().tagName()=="systemconfig")
            {
                info.append("系统配置:"+node.toElement().text()+"\n");
            }
            else if(node.toElement().tagName()=="swversion")
            {
                info.append("软件版本:"+node.toElement().text()+"\n");
            }
            else if(node.toElement().tagName()=="maintenanceinfo")
            {
                info.append("维修记录:"+node.toElement().text()+"\n");
            }
        }
        break;
    }
    return info;
}



#include "powerdomxml.h"
#include <QFile>
#include <QDomDocument>
#include <QDomProcessingInstruction>
#include <QDomElement>
#include <QTextStream>
#include <QDebug>
#include <QDateTime>

PowerdomXml::PowerdomXml()
{

}
QString PowerdomXml::readInfoFromXML(QString filePath, QString deviceName, QString deviceNo)
{
    QString info;
    QFile file(filePath);
    if(!file.exists())
    {
        qDebug() << "power xml file not exist";
        return info;
    }
    bool isOk = file.open(QIODevice::ReadOnly);
    if(isOk==false){
        qDebug() << "readXML ReadOnly error";
        return info;
    }
    QDomDocument doc;
    isOk = doc.setContent(&file);
    if(isOk==false){
        qDebug() << "readXML setContent error";
        return info;
    }
    file.close();

    QDomNodeList nodeList = doc.elementsByTagName(deviceName);
    for( int i = 0; i < nodeList.count(); i++ )
    {
        QDomElement e = nodeList.at(i).toElement();
        QString number=e.attribute("deviceNo");
        qDebug()<<"zwz number ="<<number;
        if(number.compare(deviceNo)){
            continue;
        }
        info.append("设备编号:"+number+"\n");
        QDomNodeList childlist = e.childNodes();
        for( int i = 0; i < childlist.count(); i++ )
        {
            QDomNode node = childlist.at( i );
            if(!node.isElement()){
                qDebug()<<"node not element";
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

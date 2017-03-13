#include "zcreadinfofromxml.h"
#include <QFile>
#include <QDebug>
#include <QDomDocument>
#include <QDomProcessingInstruction>
#include <QDomElement>
#include <QTextStream>
#include <QDateTime>

ZCReadInfofromXml::ZCReadInfofromXml()
{

}
QString ZCReadInfofromXml::readInfoFromXML(QString filePath, QString deviceName, QString deviceNo)
{
    QString info=NULL;
    QFile file(filePath);
    if(!file.exists())
    {
        qDebug() << "zc readXML file not exist";
        return info;
    }
    bool isOk = file.open(QIODevice::ReadOnly);
    if(isOk==false)
    {
        qDebug() << "zc readXML ReadOnly error";
        return info;
    }
    QDomDocument doc;
    isOk = doc.setContent(&file);
    if(isOk==false)
    {
        qDebug() << "zc readXML setContent error";
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
                qDebug()<<"node not element";
            }
            if(node.toElement().tagName()=="vendor")
            {
                info.append(node.toElement().text()+"\n");
            }
            else if(node.toElement().tagName()=="starttime")
            {
                info.append(node.toElement().text()+"\n");
            }
            else if(node.toElement().tagName()=="cpu")
            {
                info.append(node.toElement().text()+"\n");
            }
            else if(node.toElement().tagName()=="memory")
            {
                info.append(node.toElement().text()+"\n");
            }
            else if(node.toElement().tagName()=="operating_system")
            {
                info.append(node.toElement().text()+"\n");
            }
            else if(node.toElement().tagName()=="software_version")
            {
                info.append(node.toElement().text()+"\n");
            }
            else if(node.toElement().tagName()=="maintenance_record")
            {
                info.append(node.toElement().text()+"\n");
            }
            else if(node.toElement().tagName()=="person_id")
            {
                info.append(node.toElement().text());
            }
        }
        break;
    }
    return info;
}

#include "cixmlutil.h"
#include <QFile>
#include <QDomComment>
#include <QDomProcessingInstruction>
#include <QDomElement>
#include <QDebug>

CiXMLUtil::CiXMLUtil()
{

}

QString CiXMLUtil::readXML(QString filePath, QString deviceName, QString deviceCode)
{
    QString info;
    QFile file(filePath);
    if(!file.exists())
    {
        return info;
    }

    bool isOK = file.open(QIODevice::ReadOnly);
    if(isOK == false)
    {
        return info;
    }

     QDomDocument doc;
     isOK = doc.setContent(&file);
     if(isOK == false)
     {
         return info;
     }
     file.close();

     QDomNodeList nodeList = doc.elementsByTagName(deviceName);
     for(int i=0;i<nodeList.count();i++)
     {
         QDomElement element = nodeList.at(i).toElement();
         QString number = element.attribute("code");
         if(number.compare(deviceCode))
         {
             continue;
         }
         info.append("设备编号:"+number+"\n");
          QDomNodeList childlist = element.childNodes();
         for( int i = 0; i < childlist.count(); i++ )
         {
             QDomNode node = childlist.at( i );
             if(node.isElement())
             {
                 qDebug()<<"node not element ="<<node.toElement().text();
             }
             if(node.toElement().tagName()=="temp")
             {
                 info.append("环境温度:"+node.toElement().text()+"\n");
             }else if(node.toElement().tagName()=="speed")
             {
                 info.append("车速范围:"+node.toElement().text()+"\n");
             }else if(node.toElement().tagName()=="input")
             {
                 info.append("输出:"+node.toElement().text()+"\n");
             }else if(node.toElement().tagName()=="power")
             {
                 info.append("供电:"+node.toElement().text()+"\n");
             }else if(node.toElement().tagName()=="name")
             {
                 info.append("设备名称:"+node.toElement().text()+"\n");
             }else if(node.toElement().tagName()=="type")
             {
                 info.append("设备类型:"+node.toElement().text()+"\n");
             }else if(node.toElement().tagName()=="position")
             {
                 info.append("安装位置:"+node.toElement().text()+"\n");
             }else if(node.toElement().tagName()=="manufacture")
             {
                 info.append("制造厂商:"+node.toElement().text()+"\n");
             }else if(node.toElement().tagName()=="purchasedate")
             {
                 info.append("服役起始时间:"+node.toElement().text()+"\n");
             }else if(node.toElement().tagName()=="baseconfig")
             {
                 info.append("基本配置:"+node.toElement().text()+"\n");
             }else if(node.toElement().tagName()=="systemconfig")
             {
                 info.append("系统配置:"+node.toElement().text()+"\n");
             }else if(node.toElement().tagName()=="swversion")
             {
                 info.append("软件版本:"+node.toElement().text()+"\n");
             }else if(node.toElement().tagName()=="maintenanceinfo")
             {
                 info.append("维修记录:"+node.toElement().text()+"\n");
             }else if(node.toElement().tagName()=="date")
             {
                 info.append("出厂日期:"+node.toElement().text()+"\n");
             }else if(node.toElement().tagName()=="year")
             {
                 info.append("使用年限:"+node.toElement().text()+"\n");
             }else if(node.toElement().tagName()=="width")
             {
                 info.append("宽:"+node.toElement().text()+"\n");
             }else if(node.toElement().tagName()=="height")
             {
                 info.append("高:"+node.toElement().text()+"\n");
             }else if(node.toElement().tagName()=="opentime")
             {
                 info.append("滑动门开门行程时间:"+node.toElement().text()+"\n");
             }else if(node.toElement().tagName()=="closetime")
             {
                 info.append("滑动门关门行程时间:"+node.toElement().text()+"\n");
             }else if(node.toElement().tagName()=="noise")
             {
                 info.append("噪音:"+node.toElement().text()+"\n");
             }else if(node.toElement().tagName()=="press")
             {
                 info.append("开关门力:"+node.toElement().text()+"\n");
             }else if(node.toElement().tagName()=="color")
             {
                 info.append("信号灯颜色:"+node.toElement().text()+"\n");
             }else if(node.toElement().tagName()=="distance")
             {
                 info.append("距离:"+node.toElement().text()+"\n");
             }else if(node.toElement().tagName()=="jianguilen")
             {
                 info.append("尖轨长度:"+node.toElement().text()+"\n");
             }else if(node.toElement().tagName()=="huguilen")
             {
                 info.append("护轨长度:"+node.toElement().text()+"\n");
             }else if(node.toElement().tagName()=="crossangel")
             {
                 info.append("辙叉角度:"+node.toElement().text()+"\n");
             }
         }
         break;

     }
    return info;
}

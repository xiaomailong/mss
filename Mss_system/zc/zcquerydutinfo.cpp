#include "zcquerydutinfo.h"
#include "ui_zcquerydutinfo.h"
#include "zcreadinfofromxml.h"
ZcQueryDutinfo::ZcQueryDutinfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZcQueryDutinfo)
{
    ui->setupUi(this);
    ui->label->setText(ZCReadInfofromXml::readInfoFromXML("://xml/zc/zcInformation.xml","ZCI","1"));
}

ZcQueryDutinfo::~ZcQueryDutinfo()
{
    delete ui;
}

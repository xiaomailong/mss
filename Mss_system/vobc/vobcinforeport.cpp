#include "vobcinforeport.h"
#include "ui_vobcinforeport.h"

VobcInfoReport::VobcInfoReport(QWidget *parent,int type,QString deviceName) :
    QWidget(parent),
    ui(new Ui::VobcInfoReport)
{
    ui->setupUi(this);
    type=type;
    deviceName=deviceName;
}

VobcInfoReport::~VobcInfoReport()
{
    delete ui;
}

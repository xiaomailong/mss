#include "atsinforeport.h"
#include "ui_atsinforeport.h"

AtsInfoReport::AtsInfoReport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AtsInfoReport)
{
    ui->setupUi(this);
}

AtsInfoReport::~AtsInfoReport()
{
    delete ui;
}

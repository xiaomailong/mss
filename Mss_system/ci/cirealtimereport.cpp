#include "cirealtimereport.h"
#include "ui_cirealtimereport.h"

CiRealTimeReport::CiRealTimeReport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CiRealTimeReport)
{
    ui->setupUi(this);
}

CiRealTimeReport::~CiRealTimeReport()
{
    delete ui;
}

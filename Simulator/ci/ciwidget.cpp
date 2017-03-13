#include "ciwidget.h"
#include "ui_ciwidget.h"

CiWidget::CiWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CiWidget)
{
    ui->setupUi(this);
}

CiWidget::~CiWidget()
{
    delete ui;
}

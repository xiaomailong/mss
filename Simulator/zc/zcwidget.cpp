#include "zcwidget.h"
#include "ui_zcwidget.h"

ZcWidget::ZcWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZcWidget)
{
    ui->setupUi(this);
}

ZcWidget::~ZcWidget()
{
    delete ui;
}

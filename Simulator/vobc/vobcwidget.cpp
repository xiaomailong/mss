#include "vobcwidget.h"
#include "ui_vobcwidget.h"

VobcWidget::VobcWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VobcWidget)
{
    ui->setupUi(this);
}

VobcWidget::~VobcWidget()
{
    delete ui;
}

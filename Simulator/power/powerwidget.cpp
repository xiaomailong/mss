#include "powerwidget.h"
#include "ui_powerwidget.h"

PowerWidget::PowerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PowerWidget)
{
    ui->setupUi(this);
}

PowerWidget::~PowerWidget()
{
    delete ui;
}

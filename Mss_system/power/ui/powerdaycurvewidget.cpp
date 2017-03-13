#include "powerdaycurvewidget.h"
#include "ui_powerdaycurvewidget.h"

PowerDayCurveWidget::PowerDayCurveWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PowerDayCurveWidget)
{
    ui->setupUi(this);
}

PowerDayCurveWidget::~PowerDayCurveWidget()
{
    delete ui;
}

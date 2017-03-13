#include "showdetailalarm.h"
#include "ui_showdetailalarm.h"
#include <QDebug>

ShowDetailAlarm::ShowDetailAlarm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShowDetailAlarm)
{
    ui->setupUi(this);

    setWindowTitle(tr("报警处理信息"));
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint& ~Qt::WindowMinimizeButtonHint);
    resize(640,480);

    ui->alarmType->setText("");
    ui->alarmDevice->setText("");
    ui->alarmDetail->setText("");
    ui->alarmSubSys->setText("");
    ui->alarmTime->setText("");
    ui->deviceLocal->setText("");
}

ShowDetailAlarm::~ShowDetailAlarm()
{
    delete ui;
}

void ShowDetailAlarm::on_closeBtn_clicked()
{
    this->close();
}

void ShowDetailAlarm::fillData(QStringList strList)
{
    QString str = strList.join(",");
    //qDebug()<<"str="<<str;
    int count = strList.count();
    if(count == 0) return;

    if (strList.size() < 6) {
        return;
    }

    ui->alarmType->setText(strList.at(0));
    ui->alarmSubSys->setText(strList.at(1));
    ui->alarmDevice->setText(strList.at(2));
    ui->deviceLocal->setText(strList.at(3));
    ui->alarmTime->setText(strList.at(4));
    ui->alarmDetail->setText(strList.at(5));

    return;
}

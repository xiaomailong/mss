#include "atswidget.h"
#include "ui_atswidget.h"
#include "atsperiodicprocessor.h"
#include "atsburstprocessor.h"
#include "simulatorconfig.h"
#include "simulatorlogconfig.h"
#include "ats_data.h"
#include "mssdatadefine.h"
#include "simulatoruserdata.h"

AtsWidget::AtsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AtsWidget)
{
    ui->setupUi(this);
}

AtsWidget::~AtsWidget()
{
    delete ui;
}

void AtsWidget::onFinished()
{
    qDebug("Entry");
    delete sender();
}

void AtsWidget::on_tsr_sure_clicked()
{
    qDebug("Entry");
    AtsBurstProcessor* cur_proc = new AtsBurstProcessor(AtsDataFactory::AtsZcTsrValidateDataType);
    connect(cur_proc, &AtsBurstProcessor::finished, this, &AtsWidget::onFinished);
    if(!ui->port->text().isEmpty())
    {
        cur_proc->setPort((quint16)(ui->port->text().toUInt()));
    }
    if(!ui->ip->text().isEmpty())
    {
        cur_proc->setHost(QHostAddress(ui->ip->text()));
    }
    cur_proc->start();
}

void AtsWidget::on_tsr_opcmd_clicked()
{
    qDebug("Entry");
    AtsBurstProcessor* cur_proc = new AtsBurstProcessor(AtsDataFactory::AtsZcTsrExecCmdDataType);
    connect(cur_proc, &AtsBurstProcessor::finished, this, &AtsWidget::onFinished);
    if(!ui->port->text().isEmpty())
    {
        cur_proc->setPort((quint16)(ui->port->text().toUInt()));
    }
    if(!ui->ip->text().isEmpty())
    {
        cur_proc->setHost(QHostAddress(ui->ip->text()));
    }
    cur_proc->start();
}

void AtsWidget::on_tsr_power_clicked()
{
    qDebug("Entry");
    AtsBurstProcessor* cur_proc = new AtsBurstProcessor(AtsDataFactory::AtsZcTsrOnConfirmDataType);
    connect(cur_proc, &AtsBurstProcessor::finished, this, &AtsWidget::onFinished);
    if(!ui->port->text().isEmpty())
    {
        cur_proc->setPort((quint16)(ui->port->text().toUInt()));
    }
    if(!ui->ip->text().isEmpty())
    {
        cur_proc->setHost(QHostAddress(ui->ip->text()));
    }
    cur_proc->start();
}

void AtsWidget::on_ats_ci_opcmd_clicked()
{
    qDebug("Entry");
    AtsBurstProcessor* cur_proc = new AtsBurstProcessor(AtsDataFactory::AtsCiCmdDataType);
    connect(cur_proc, &AtsBurstProcessor::finished, this, &AtsWidget::onFinished);
    if(!ui->port->text().isEmpty())
    {
        cur_proc->setPort((quint16)(ui->port->text().toUInt()));
    }
    if(!ui->ip->text().isEmpty())
    {
        cur_proc->setHost(QHostAddress(ui->ip->text()));
    }
    cur_proc->start();
}

void AtsWidget::on_ats_vobc_cmd_clicked()
{
    qDebug("Entry");
    AtsBurstProcessor* cur_proc = new AtsBurstProcessor(AtsDataFactory::AtsVobcAtoCmdDataType);
    connect(cur_proc, &AtsBurstProcessor::finished, this, &AtsWidget::onFinished);
    if(!ui->port->text().isEmpty())
    {
        cur_proc->setPort((quint16)(ui->port->text().toUInt()));
    }
    if(!ui->ip->text().isEmpty())
    {
        cur_proc->setHost(QHostAddress(ui->ip->text()));
    }
    cur_proc->start();
}

void AtsWidget::on_ats_vobc_heart_clicked()
{
    qDebug("Entry");
    SimulatorUserData* userData = reinterpret_cast<SimulatorUserData*>(ui->ats_vobc_heart->userData(SIMULATOR_USER_DATA_ID));
    if(userData == NULL)
    {
        AtsPeriodicProcessor* cur_proc = new AtsPeriodicProcessor(AtsDataFactory::AtsVobcHeartBeatDataType);
        if(!ui->port->text().isEmpty())
        {
            cur_proc->setPort((quint16)(ui->port->text().toUInt()));
        }
        if(!ui->ip->text().isEmpty())
        {
            cur_proc->setHost(QHostAddress(ui->ip->text()));
        }
        if(!ui->ats_vobc_heart_time->text().isEmpty())
        {
            cur_proc->start(ui->ats_vobc_heart_time->text().toInt());
        } else
        {
            cur_proc->start();
        }
        userData = new SimulatorUserData(cur_proc);
        ui->ats_vobc_heart->setUserData(SIMULATOR_USER_DATA_ID, userData);
        ui->ats_vobc_heart->setText(QString("停止"));
    }
    else
    {
        AtsPeriodicProcessor* cur_proc = reinterpret_cast<AtsPeriodicProcessor*>(userData->data);
        cur_proc->stop();
        delete userData;
        ui->ats_vobc_heart->setUserData(SIMULATOR_USER_DATA_ID, NULL);
        ui->ats_vobc_heart->setText(QString("开始"));
    }
}

void AtsWidget::on_ats_zc_time_clicked()
{
    qDebug("Entry");
    SimulatorUserData* userData = reinterpret_cast<SimulatorUserData*>(ui->ats_zc_time->userData(SIMULATOR_USER_DATA_ID));
    if(userData == NULL)
    {
        AtsPeriodicProcessor* cur_proc = new AtsPeriodicProcessor(AtsDataFactory::AtsZcHeartBeatDataType);
        if(!ui->port->text().isEmpty())
        {
            cur_proc->setPort((quint16)(ui->port->text().toUInt()));
        }
        if(!ui->ip->text().isEmpty())
        {
            cur_proc->setHost(QHostAddress(ui->ip->text()));
        }
        if(!ui->ats_zc_time_time->text().isEmpty())
        {
            cur_proc->start(ui->ats_zc_time_time->text().toInt());
        }
        else
        {
            cur_proc->start();
        }
        userData = new SimulatorUserData(cur_proc);
        ui->ats_zc_time->setUserData(SIMULATOR_USER_DATA_ID, userData);
        ui->ats_zc_time->setText(QString("停止"));
    }
    else
    {
        AtsPeriodicProcessor* cur_proc = reinterpret_cast<AtsPeriodicProcessor*>(userData->data);
        cur_proc->stop();
        delete userData;
        ui->ats_zc_time->setUserData(SIMULATOR_USER_DATA_ID, NULL);
        ui->ats_zc_time->setText(QString("开始"));
    }

}

void AtsWidget::on_ats_ci_run_clicked()
{
    qDebug("Entry");
    SimulatorUserData* userData = reinterpret_cast<SimulatorUserData*>(ui->ats_ci_run->userData(SIMULATOR_USER_DATA_ID));
    if(userData == NULL)
    {
        AtsPeriodicProcessor* cur_proc = new AtsPeriodicProcessor(AtsDataFactory::AtsCiStatusDataType);
        if(!ui->port->text().isEmpty())
        {
            cur_proc->setPort((quint16)(ui->port->text().toUInt()));
        }
        if(!ui->ip->text().isEmpty())
        {
            cur_proc->setHost(QHostAddress(ui->ip->text()));
        }
        if(!ui->ats_ci_run_time->text().isEmpty())
        {
            cur_proc->start(ui->ats_ci_run_time->text().toInt());
        }
        else
        {
            cur_proc->start();
        }
        userData = new SimulatorUserData(cur_proc);
        ui->ats_ci_run->setUserData(SIMULATOR_USER_DATA_ID, userData);
        ui->ats_ci_run->setText(QString("停止"));
    }
    else
    {
        AtsPeriodicProcessor* cur_proc = reinterpret_cast<AtsPeriodicProcessor*>(userData->data);
        cur_proc->stop();
        delete userData;
        ui->ats_ci_run->setUserData(SIMULATOR_USER_DATA_ID, NULL);
        ui->ats_ci_run->setText(QString("开始"));
    }
}


void AtsWidget::on_ats_mss_button_clicked()
{
    qDebug("Entry");
    ats_mss_alarm_t extraInfo;
    AtsBurstProcessor* cur_proc = NULL;
    memset(&extraInfo, 0, sizeof(extraInfo));
    if(ui->checkBoxVobc->isChecked())
    {
        cur_proc = new AtsBurstProcessor(AtsDataFactory::VobcMssAlarmDataType, reinterpret_cast<void*>(&extraInfo));
    }
    else
    {
        cur_proc = new AtsBurstProcessor(AtsDataFactory::AtsMssAlarmDataType, reinterpret_cast<void*>(&extraInfo));
    }
    if(!ui->port->text().isEmpty())
    {
        cur_proc->setPort((quint16)(ui->port->text().toUInt()));
    }
    if(!ui->ip->text().isEmpty())
    {
        cur_proc->setHost(QHostAddress(ui->ip->text()));
    }
    if(!ui->sys_id->text().isEmpty())
    {
        extraInfo.sys_id = (quint16)(ui->sys_id->text().toUInt());
    }
    if(!ui->dev_type->text().isEmpty())
    {
        extraInfo.dev_type = (quint8)(ui->dev_type->text().toUInt());
    }
    if(!ui->dev_id->text().isEmpty())
    {
        extraInfo.dev_id = (quint16)(ui->dev_id->text().toUInt());
    }
    if(!ui->dev_local->text().isEmpty())
    {
        extraInfo.dev_local = (quint8)(ui->dev_local->text().toUInt());
    }
    if(!ui->alarm_type->text().isEmpty())
    {
        extraInfo.alarm_type = (quint8)(ui->alarm_type->text().toUInt());
    }
    if(!ui->alarm_subtype->text().isEmpty())
    {
        extraInfo.alarm_subtype = (quint8)(ui->alarm_subtype->text().toUInt());
    }
    if(!ui->alarm_level->text().isEmpty())
    {
        extraInfo.alarm_level = (quint8)(ui->alarm_level->text().toUInt());
    }
    if(!ui->alarm_code->text().isEmpty())
    {
        extraInfo.alarm_code = (quint16)(ui->alarm_code->text().toUInt());
    }
    connect(cur_proc, &AtsBurstProcessor::finished, this, &AtsWidget::onFinished);
    cur_proc->start();
}

void AtsWidget::on_ats_ci_time_clicked()
{
    qDebug("Entry");
    SimulatorUserData* userData = reinterpret_cast<SimulatorUserData*>(ui->ats_ci_time->userData(SIMULATOR_USER_DATA_ID));
    if(userData == NULL)
    {
        AtsPeriodicProcessor* cur_proc = new AtsPeriodicProcessor(AtsDataFactory::AtsCiHeartBeatDataType);
        if(!ui->port->text().isEmpty())
        {
            cur_proc->setPort((quint16)(ui->port->text().toUInt()));
        }
        if(!ui->ip->text().isEmpty())
        {
            cur_proc->setHost(QHostAddress(ui->ip->text()));
        }
        if(!ui->ats_ci_time_time->text().isEmpty())
        {
            cur_proc->start(ui->ats_ci_time_time->text().toInt());
        }
        else
        {
            cur_proc->start();
        }
        userData = new SimulatorUserData(cur_proc);
        ui->ats_ci_time->setUserData(SIMULATOR_USER_DATA_ID, userData);
        ui->ats_ci_time->setText(QString("停止"));
    }
    else
    {
        AtsPeriodicProcessor* cur_proc = reinterpret_cast<AtsPeriodicProcessor*>(userData->data);
        cur_proc->stop();
        delete userData;
        ui->ats_ci_time->setUserData(SIMULATOR_USER_DATA_ID, NULL);
        ui->ats_ci_time->setText(QString("开始"));
    }
}

#include <QSplashScreen>
#include <QCommandLinkButton>
#include "splash.h"
#include <QDebug>

Splash::Splash(QSplashScreen *parent) : QSplashScreen(parent)
{
    enterBtn = new QCommandLinkButton(this);
    enterBtn->setText(tr("点击进入"));
    enterBtn->move(600,600);
    connect(enterBtn,&QCommandLinkButton::clicked,this,&Splash::enterMssSystem);
}

void Splash::enterMssSystem()
{
    m_pSysWidget->setHidden(false);
    m_pSysWidget->setVisible(true);
    m_pSysWidget->show();
    finish(m_pSysWidget);
    delete this;
}

void Splash::setBtnEnabled(bool enabled)
{
    enterBtn->setEnabled(enabled);
    return;
}

void Splash::SetSystemWidget(MssSystem* pWdgt)
{
    m_pSysWidget = pWdgt;
}

Splash::~Splash()
{
    qDebug()<<"delete splash";
}

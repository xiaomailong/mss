#include "msssystem.h"
#include "ui_msssystem.h"
#include <QMessageBox>
#include <QDebug>
#include <QMetaType>
#include "mssdbconfig.h"
#include "showdetailalarm.h"
bool POWER_USE_UDP_SIMULATE = true;
bool POWER_USE_UDP_RECEIVE = true;

MssSystem::MssSystem(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MssSystem)
{
    setHidden(true);
    setVisible(false);
    ui->setupUi(this);

    setWindowTitle(tr("MSS 系统"));
    widget = new QWidget;
    subsysWidget = new QWidget;
    alarmWidget = new QWidget;
    alarmDetailWidget = new QWidget;
    setCentralWidget(widget);
    createAction();
    createMenus();
    //showFullScreen();

    //子系统主界面
    QGroupBox *subsys = createSubSys();
    QVBoxLayout *subsysLayout = new QVBoxLayout;
    subsysLayout->addWidget(subsys);

    //警报系统
    QGroupBox *alarm = createAlarm();
    QVBoxLayout *alarmLayout = new QVBoxLayout;
    alarmLayout->addWidget(alarm);

    //警报系统详细信息界面
    QGroupBox *alarmDetail = showAlarmDetail();
    QVBoxLayout *alarmDetailLayout = new QVBoxLayout;
    alarmDetailLayout->addWidget(alarmDetail);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    subsysWidget->setLayout(subsysLayout);
    alarmWidget->setLayout(alarmLayout);
    alarmDetailWidget->setLayout(alarmDetailLayout);


    mainLayout->addWidget(subsysWidget);
    mainLayout->addWidget(alarmWidget);
    mainLayout->addWidget(alarmDetailWidget);

    alarmDetailWidget->setVisible(false);

    mainLayout->setStretchFactor(subsysWidget,15);
    mainLayout->setStretchFactor(alarmWidget,2);
    mainLayout->setStretchFactor(alarmDetailWidget,10);

    widget->setLayout(mainLayout);
    this->setStyleSheet("QCheckBox:hover{color:red}QCheckBox:checked{color:red}");

    setMinimumSize(800,450);
    //setMaximumSize(200,120);
    //qDebug("MainWindow: thread id: %d", (int)QThread::currentThreadId());
    //showwidget = new showWidget(this);
   // setCentralWidget(showwidget);
    showMaximized();

    mLabel = new QLabel(); //add by phy
    MySqlDBInit();
    //**jc** vobc code begin
    MssVobcInit();
    //do connect here
    qRegisterMetaType<vobc_subsys_msg_t>("vobc_subsys_msg_t");
    simulateService = new VobcSimulate(this);
    connect(simulateService, &VobcSimulate::finished, simulateService, &QObject::deleteLater);
#ifdef RECEIVER_DIRECT
    connect(simulateService, &VobcSimulate::randomDcsData, vobcDcsService, &VobcDcsService::handleDcsData);
#endif

    //display vobc alarm msg
    vobcAtsService->setInstFlag(true);
    connect(vobcAtsService, &VobcAtsService::reportAlarmMsg, this, &MssSystem::onReceiveVobcAlarm);
#ifdef SIMULATE
    simulateService->start();
    connect(this, &MssSystem::destroyed, this, &MssSystem::SimulateDestroy);
#endif
    //**jc** vobc code end
    //ci system data background thread
    mssCiInit();
    MssZcInit();
    MssAtsInit();
    connect(m_atsprocess, &AtsProcess::vobcDeviceDataReceived,vobcAtsService, &VobcAtsService::handleAtsData);
#ifdef RSSPISIMULATETEST
    RsspiSimulateInit();
#else
    MssRsspiInit();//BYD flying.zhao 2017-2-20 Fix Rssp
#endif

    //add by yhj 20170211 for power monitor system
    mssPowerInit();
    //add end
    //connect alarm signals
    connect(vobcAtsService, &VobcAtsService::reportAlarmMsg, this, &MssSystem::receive_alarm_data);
    connect(ciThread, &CiService::ciAlarm, this, &MssSystem::receive_alarm_data);
    connect(m_atsprocess, &AtsProcess::deviceDataReceived1,this, &MssSystem::receive_alarm_data);
    connect(zcDataThread, &ZcDataThread::sendUiZcAlarm,this, &MssSystem::receive_alarm_data);
}

MssSystem::~MssSystem()
{
    //**jc** vobc code begin
    MssVobcDestroyed();
    //**jc** vobc code end
    // ci destroy
    mssCiDestroyed();
    MssZcDestroyed();
    MssAtsDeInit();
#ifdef RSSPISIMULATETEST
    StopRsspSimulate();
#else
    StopRsspiThread();
#endif
    delete ui;
}

void MssSystem::MssAtsInit()
{
    qDebug("Entry");
    m_simulate_route_t = new SimulateDataService();
    m_sds_thread = new QThread(this);
    m_simulate_route_t->moveToThread(m_sds_thread);
    connect(m_sds_thread, &QThread::started, m_simulate_route_t, &SimulateDataService::start, Qt::AutoConnection);
    connect(m_sds_thread, &QThread::finished, m_simulate_route_t, &SimulateDataService::stop, Qt::AutoConnection);

    m_atsprocess = new AtsProcess();
    m_ats_thread = new QThread(this);
    m_atsprocess->moveToThread(m_ats_thread);
    connect(m_ats_thread, &QThread::started, m_atsprocess, &AtsProcess::start, Qt::AutoConnection);
    connect(m_ats_thread, &QThread::finished, m_atsprocess, &AtsProcess::stop, Qt::AutoConnection);

    connect(m_simulate_route_t, &SimulateDataService::dataReceived, m_atsprocess, &AtsProcess::onReceiveData, Qt::QueuedConnection);
    connect(m_simulate_route_t, &SimulateDataService::deviceDataReceived, m_atsprocess, &AtsProcess::onDeviceDataReceived, Qt::QueuedConnection);

    connect(m_atsprocess, &AtsProcess::deviceDataReceived, this,&MssSystem::DealFromAtsAlarmData);

    m_ats_thread->start();
    do {
        QThread::msleep(10);
    }while(!m_ats_thread->isRunning());
    m_sds_thread->start();
}

void MssSystem::MssAtsDeInit()
{
    qDebug("Entry");

    m_sds_thread->quit();
    m_sds_thread->wait();
    delete m_simulate_route_t;
    m_simulate_route_t = NULL;
    m_ats_thread->quit();
    m_ats_thread->wait();
    delete m_atsprocess;
    m_atsprocess = NULL;
}
//add by yhj 20170227 for power monitor system
void MssSystem::mssPowerInit()
{
#ifdef USE_UDP
    powerSimulateDataService = new PowerSimulateDataService();
    if(POWER_USE_UDP_RECEIVE)
    {
        powerProcess = new PowerProcess();
        powerThread = new QThread(this);
        powerProcess->moveToThread(powerThread);
        connect(powerSimulateDataService,&PowerSimulateDataService::sendPowerSimulateData,powerProcess, &PowerProcess::receiveDataByUDP, Qt::AutoConnection);
        //connect(mypsp,SIGNAL(send_alarm(alarm_t*)), this, SLOT(receiveAlarmData(alarm_t*)), Qt::AutoConnection);
        connect(powerThread, &QThread::started, powerProcess, &PowerProcess::start, Qt::QueuedConnection);
        //connect(power, SIGNAL(started()), powerSimulateDataService, SLOT(start()), Qt::QueuedConnection);
        powerThread->start();
    }

    if(POWER_USE_UDP_SIMULATE)
    {
        powerSimulateDataService->start();
    }
#else
    powerSimulateDataService = new powerMonitorSystem_sendData_service2();
    powerProcess = new powermonitorsystem2();
    powerThread = new QThread(this);
    powerProcess->moveToThread(powerThread);
    connect(powerSimulateDataService,&PowerSimulateDataService::sendPowerSimulateData,powerProcess, &PowerProcess::receiveData, Qt::AutoConnection);
    //connect(mypsp,SIGNAL(send_alarm(alarm_t*)), this, SLOT(receiveAlarmData(alarm_t*)), Qt::AutoConnection);
    connect(powerThread, &QThread::started, powerProcess, &PowerProcess::start, Qt::QueuedConnection);
    connect(powerProcess, &PowerProcess::started, powerSimulateDataService, &PowerSimulateDataService::start, Qt::QueuedConnection);
    powerThread->start();
#endif
}
//add end

void MssSystem::mssCiInit()
{
    if(CI_DEBUG) qDebug()<<"main threadid="<<QThread::currentThreadId();
    ciThread = new CiService();
    receiverThread = new QThread(this);
    ciThread->moveToThread(receiverThread);
    ciSimulate = new CiSimulate();
    simulateThread = new QThread(this);
    ciSimulate->moveToThread(simulateThread);
#ifdef RECEIVER_DIRECT
    connect(ciSimulate,&CiSimulate::sendCiRoute, ciThread, &CiService::receiveRouteData, Qt::QueuedConnection);
#endif
    connect(receiverThread, &QThread::started, ciThread, &CiService::start, Qt::QueuedConnection);
    receiverThread->start();
#ifdef SIMULATE
    connect(simulateThread, &QThread::started, ciSimulate, &CiSimulate::start, Qt::QueuedConnection);
    simulateThread->start();
#endif
}

void MssSystem::mssCiDestroyed()
{
#ifdef SIMULATE
    simulateThread->quit();
    simulateThread->wait();
#endif

    receiverThread->quit();
    receiverThread->wait();
}

void MssSystem::createMenus()
{


    rilMenu = menuBar()->addMenu(tr("&实时监测协议包"));
    rilMenu->addAction(atsAction);
    atsMenu = new QMenu();
    atsAction->setMenu(atsMenu);

    atsMenu->addAction(tr("VOBC系统"),this,&MssSystem::showAtsVobc);
    atsMenu->addAction(tr("ZC系统"),this,&MssSystem::showAtsZc);
    atsMenu->addAction(tr("CI系统"),this,&MssSystem::showAtsCi);

    rilMenu->addAction(ciAction);
    ciMenu = new QMenu();
    ciAction->setMenu(ciMenu);
    ciMenu->addAction(tr("ATS"),this,&MssSystem::showCiAts);
    ciMenu->addAction(tr("ZC"),this,&MssSystem::showCiZc);
    ciMenu->addAction(tr("VOBC"),this,&MssSystem::showCiVobc);

    rilMenu->addAction(zcAction);
    zcMenu = new QMenu();
    zcAction->setMenu(zcMenu);
//    zcMenu->addAction(mssatsAction);
//    zcMenu->addAction(mssciAction);
//    zcMenu->addAction(mssvobcAction);
//    zcMenu->addAction(mssAction);
    zcMenu->addAction(tr("ATS系统"),this,&MssSystem::showZcAts);
    zcMenu->addAction(tr("CI系统"),this,&MssSystem::showZcCi);
    zcMenu->addAction(tr("VOBC系统"),this,&MssSystem::showZcVobc);

    rilMenu->addAction(vobcAction);
    vobcMenu = new QMenu();
    vobcAction->setMenu(vobcMenu);
    vobcMenu->addAction(tr("ATS系统"),this,&MssSystem::showVobcAts);
    vobcMenu->addAction(tr("ZC系统"),this,&MssSystem::showVobcZc);
    vobcMenu->addAction(tr("CI系统"),this,&MssSystem::showVobcCi);
//    vobcMenu->addAction(mssatsAction);
//    vobcMenu->addAction(msszcAction);
//    vobcMenu->addAction(mssciAction);
//    vobcMenu->addAction(mssAction);

    warnMenu = menuBar()->addMenu(tr("&故障报警"));
    warnMenu->addAction(timeWarnAction);
    warnMenu->addAction(hisWarnAction);
    hisWarnMenu = new QMenu();
    hisWarnAction->setMenu(hisWarnMenu);
    hisWarnMenu->addAction(bjsjAction);
    hisWarnMenu->addAction(ddAction);
    hisWarnMenu->addAction(sszxtAction);
    //add alarm by subsystem
    QMenu *hisWarnMenuBySub=new QMenu(this);
    sszxtAction->setMenu(hisWarnMenuBySub);
    hisWarnMenuBySub->addAction(tr("VOBC"),this,&MssSystem::showVobcAlarm);
    hisWarnMenuBySub->addAction(tr("ZC"),this,&MssSystem::showZCWarning);
    hisWarnMenuBySub->addAction(tr("ATS"),this,&MssSystem::showAtsAlarm);
    hisWarnMenuBySub->addAction(tr("CI"),this,&MssSystem::showCiAlarm);
    hisWarnMenuBySub->addAction(tr("POWER"),this,&MssSystem::showPowerAlarm);
    hisWarnMenu->addAction(djAction);
    warnMenu->addAction(totWarnAction);
    totWarnMenu = new QMenu();
    totWarnAction->setMenu(totWarnMenu);
    totWarnMenu->addAction(sjdtjAction);
    totWarnMenu->addAction(xtlxtjAction);
    totWarnMenu->addAction(ddgztjAction);
    totWarnMenu->addAction(xczbtjAction);
    totWarnMenu->addAction(jtxhsbAction);

    mesgMenu = menuBar()->addMenu(tr("&信息管理"));
    mesgMenu->addAction(subsysAction);
    subsysMenu = new QMenu();
    subsysAction->setMenu(subsysMenu);
    subsysMenu->addAction(atsAction);
    subsysMenu->addAction(ciAction);
    subsysMenu->addAction(zcAction);
    subsysMenu->addAction(vobcAction);

    mesgMenu->addAction(sbxxAction);
    sbxxMenu = new QMenu();
    sbxxAction->setMenu(sbxxMenu);
    sbxxMenu->addAction(vobcxtsbAction);
    sbxxMenu->addAction(czlsAction);
    sbxxMenu->addAction(zyatsbAction);
    sbxxMenu->addAction(zcxtsbbAction);
    sbxxMenu->addAction(dysbAction);
    sbxxMenu->addAction(leusbAction);
    sbxxMenu->addAction(gpsbAction);

    gpsbMenu = new QMenu();
    gpsbAction->setMenu(gpsbMenu);
    gpsbMenu->addAction(jzqAction);
    gpsbMenu->addAction(zzjAction);
    gpsbMenu->addAction(xhjAction);
    gpsbMenu->addAction(pbmAction);
    gpsbMenu->addAction(jjtcanAction);
    //mesgMenu->addMenu(subsysMenu);

    vidMenu = menuBar()->addMenu(tr("&维护管理"));
    vidMenu->addAction(planAction);
    vidMenu->addAction(listAction);
    vidMenu->addAction(applyAction);
    vidMenu->addAction(advAction);

    replyMenu = menuBar()->addMenu(tr("&运营回放"));
    replyMenu->addAction(sbztAction);
    replyMenu->addAction(bjhfAction);
    replyMenu->addAction(jlqxAction);
    replyMenu->addAction(sjszAction);
    replyMenu->addAction(bfAction);
    replyMenu->addAction(sjccAction);

    funcMenu = menuBar()->addMenu(tr("&功能预警"));

    sysMenu = menuBar()->addMenu(tr("&系统管理"));
    sysMenu->addAction(qxglAction);
    sysMenu->addAction(rjpzAction);
    sysMenu->addAction(sztbAction);
    sysMenu->addAction(dyscAction);
    sysMenu->addAction(bzAction);

}

void MssSystem::createAction()
{
    timeWarnAction= new QAction(tr("实时报警"),this);
    hisWarnAction= new QAction(tr("历史报警查询"),this);
    totWarnAction= new QAction(tr("报警统计"),this);

    atsAction=new QAction(tr("ATS系统"),this);
    ciAction=new QAction(tr("CI系统"),this);
    zcAction=new QAction(tr("ZC系统"),this);
    vobcAction=new QAction(tr("VOBC系统"),this);
    mssAction=new QAction(tr("MSS系统"),this);
    mssatsAction=new QAction(tr("ATS系统"),this);
    mssciAction=new QAction(tr("CI系统"),this);
    msszcAction=new QAction(tr("ZC系统"),this);
    mssvobcAction=new QAction(tr("VOBC系统"),this);

    planAction=new QAction(tr("制定维护计划"),this);
    listAction=new QAction(tr("管理维护工单"),this);
    applyAction=new QAction(tr("管理维护申请"),this);
    advAction=new QAction(tr("管理维护指导"),this);

    sbztAction = new QAction(tr("&设备状态"), this);
    bjhfAction = new QAction(tr("&报警回放"), this);
    jlqxAction = new QAction(tr("&记录曲线"), this);
    sjszAction = new QAction(tr("&时间设置"), this);
    bfAction = new QAction(tr("&播放"), this);
    sjccAction = new QAction(tr("&数据存储"), this);

    qxglAction = new QAction(tr("&权限管理"), this);
    rjpzAction = new QAction(tr("&软件配置"), this);
    sztbAction = new QAction(tr("&时钟同步"), this);
    dyscAction = new QAction(tr("&打印输出"), this);
    bzAction = new QAction(tr("&帮助"), this);

    subsysAction = new QAction(tr("&子系统信息"), this);
    sbxxAction = new QAction(tr("&设备信息"), this);
    gpsbAction = new QAction(tr("&轨旁设备"), this);
    vobcxtsbAction = new QAction(tr("&VOBC系统设备"), this);
    czlsAction = new QAction(tr("&车站联锁系统设备"), this);
    zyatsbAction = new QAction(tr("&中央及车站ATS服务器和工作站"), this);
    zcxtsbbAction = new QAction(tr("&ZC系统设备"), this);
    dysbAction = new QAction(tr("&电源系统设备"), this);
    leusbAction = new QAction(tr("&应答器系统设备"), this);
    jzqAction = new QAction(tr("&记轴器"), this);
    zzjAction = new QAction(tr("&转辙机"), this);
    xhjAction = new QAction(tr("&信号机"), this);
    pbmAction = new QAction(tr("&屏蔽门"), this);
    jjtcanAction = new QAction(tr("&紧急停车按钮"), this);

    bjsjAction = new QAction(tr("&报警时间"), this);
    ddAction = new QAction(tr("&地点"), this);
    sszxtAction = new QAction(tr("&所属子系统"), this);
    djAction = new QAction(tr("&等级"), this);

    sjdtjAction = new QAction(tr("&按时间段故障报警统计"), this);
    xtlxtjAction = new QAction(tr("&按系统类型故障报警统计"), this);
    ddgztjAction = new QAction(tr("&按地点故障报警统计"), this);
    xczbtjAction = new QAction(tr("&行车指标统计"), this);
    jtxhsbAction = new QAction(tr("&选择具体信号设备"), this);
}

QGroupBox* MssSystem::createSubSys()
{
    subsysbox = new QGroupBox(tr("子系统信息"));

    QGridLayout *subsysLayout = new QGridLayout;
    subsysLayout->setMargin(15);
    subsysLayout->setColumnMinimumWidth(4,15);

   // btn_WJJC = new QPushButton(QWidget::tr("微机监测"), this);
   // btn_WJJC->setFixedSize(100,100);
    btn_ATS = new QPushButton(QWidget::tr("ATS系统"), this);
    btn_ATS->setFixedSize(100,100);
    btn_ATS->setObjectName("btn_ATS");
    btn_ATS->setStyleSheet("QPushButton#btn_ATS{background-color:red;color:blue}QPushButton#btn_ATS:hover{color:white}");
    connect(btn_ATS,SIGNAL(clicked()),this,SLOT(showAts()));

    btn_CI = new QPushButton(QWidget::tr("CI系统"), this);
    btn_CI->setFixedSize(100,100);
    btn_CI->setObjectName("btn_CI");
    btn_CI->setStyleSheet("QPushButton#btn_CI{background-color:red;color:blue}QPushButton#btn_CI:hover{color:white}");
    connect(btn_CI,SIGNAL(clicked()),this,SLOT(showCi()));
    //btn_JZ = new QPushButton(QWidget::tr("计轴"), this);
    //btn_JZ->setFixedSize(100,100);
    btn_VOBC = new QPushButton(QWidget::tr("VOBC"), this);
    btn_VOBC->setFixedSize(100,100);
    btn_VOBC->setObjectName("btn_VOBC");
    btn_VOBC->setStyleSheet("QPushButton#btn_VOBC{background-color:red;color:blue}QPushButton#btn_VOBC:hover{color:white}");
    connect(btn_VOBC,SIGNAL(clicked()),this,SLOT(showVobc()));
    //btn_LEU = new QPushButton(QWidget::tr("LEU"), this);
    //btn_LEU->setFixedSize(100,100);
    btn_DCS = new QPushButton(QWidget::tr("DCS"), this);
    btn_DCS->setFixedSize(100,100);
    btn_DCS->setObjectName("btn_DCS");
    btn_DCS->setStyleSheet("QPushButton#btn_DCS{background-color:red;color:blue}QPushButton#btn_DCS:hover{color:white}");

    btn_POWER = new QPushButton(QWidget::tr("电源监测系统"), this);
    btn_POWER->setFixedSize(100,100);
    btn_POWER->setObjectName("btn_POWER");
    btn_POWER->setStyleSheet("QPushButton#btn_POWER{background-color:red;color:blue}QPushButton#btn_POWER:hover{color:white}");
    connect(btn_POWER,SIGNAL(clicked()),this,SLOT(showPower()));

    btn_ZC = new QPushButton(QWidget::tr("ZC系统"), this);
    btn_ZC->setFixedSize(100,100);
    btn_ZC->setObjectName("btn_ZC");
    btn_ZC->setStyleSheet("QPushButton#btn_ZC{background-color:red;color:blue}QPushButton#btn_ZC:hover{color:white}");
    connect(btn_ZC,SIGNAL(clicked()),this,SLOT(showZc()));


   // subsysLayout->addWidget(btn_WJJC,0,0);
    subsysLayout->addWidget(btn_ATS,0,0);
    subsysLayout->addWidget(btn_CI,0,1);
    subsysLayout->addWidget(btn_VOBC,0,2);
   //subsysLayout->addWidget(btn_JZ,0,2);
   // subsysLayout->addWidget(btn_LEU,1,0);
    subsysLayout->addWidget(btn_DCS,1,0);
    subsysLayout->addWidget(btn_POWER,1,1);
    subsysLayout->addWidget(btn_ZC,1,2);

    subsysbox->setLayout(subsysLayout);

    return subsysbox;
}


void MssSystem::onAlarm()
{
    alarmWidget->setVisible(false);
    alarmDetailWidget->setVisible(true);
}

void MssSystem::addAlbum()
{
    subsysWidget->setVisible(false);

}

void MssSystem::deleteAlbum()
{
}

void MssSystem::totalAlarmAlbum()
{
}

void MssSystem::onAlarmBack()
{
    alarmWidget->setVisible(true);
    alarmDetailWidget->setVisible(false);
}

void MssSystem::onAlarm1CheckStateChanged(int state)
{
    qDebug()<<"alarm1 check state changed";
    switch (state)
    {
    case Qt::Unchecked:
        flag[0] = 0;
        tableWidget->clearContents();
        break;
    case Qt::Checked:
        flag[0] = 1;
        break;
    default:
        flag[0] = 0;
        tableWidget->clearContents();
        break;
    }
}

void MssSystem::onAlarm2CheckStateChanged(int state)
{
    qDebug()<<"alarm2 check state changed";
    switch (state)
    {
    case Qt::Unchecked:
        flag[1] = 0;
        tableWidget->clearContents();
        break;
    case Qt::Checked:
        flag[1] = 1;
        break;
    default:
        flag[1] = 0;
        tableWidget->clearContents();
        break;
    }
}

void MssSystem::onAlarm3CheckStateChanged(int state)
{
    qDebug()<<"alarm3 check state changed";
    switch (state)
    {
    case Qt::Unchecked:
        flag[2] = 0;
        tableWidget->clearContents();
        break;
    case Qt::Checked:
        flag[2] = 1;
        break;
    default:
        flag[2] = 0;
        tableWidget->clearContents();
        break;
    }
}

QGroupBox* MssSystem::createAlarm()
{
    alarmbox = new QGroupBox(tr("警报系统"));
    QHBoxLayout *bomLayout = new QHBoxLayout;

    QHBoxLayout *alarm1Layout = new QHBoxLayout;
    QHBoxLayout *alarm2Layout = new QHBoxLayout;
    QHBoxLayout *alarm3Layout = new QHBoxLayout;
    QHBoxLayout *alarm4Layout = new QHBoxLayout;

    QPushButton* alarm_1 = new QPushButton(this);
    alarm_1->setIcon(QIcon(":/images/alarm1.png"));
    alarm_1->setText(tr("一级警报"));
    alarm_1->setFlat(true);
    alarm_1->setObjectName("alarm_1");
    alarm_1->setStyleSheet("QPushButton#alarm_1{background:transparent;color:blue;}QPushButton#alarm_1:hover{color:red}");
    connect(alarm_1, &QPushButton::clicked, this, &MssSystem::showAlarm);

    QPushButton* alarm_2 = new QPushButton(this);
    alarm_2->setIcon(QIcon(":/images/alarm2.png"));
    alarm_2->setText(tr("二级警报"));
    alarm_2->setFlat(true);
    alarm_2->setObjectName("alarm_2");
    alarm_2->setStyleSheet("QPushButton#alarm_2{background:transparent;color:blue;}QPushButton#alarm_2:hover{color:red}");
    connect(alarm_2, &QPushButton::clicked, this, &MssSystem::showAlarm2);

    QPushButton* alarm_3 = new QPushButton(this);
    alarm_3->setIcon(QIcon(":/images/alarm3.png"));
    alarm_3->setText(tr("三级警报"));
    alarm_3->setFlat(true);
    alarm_3->setObjectName("alarm_3");
    alarm_3->setStyleSheet("QPushButton#alarm_3{background:transparent;color:blue;}QPushButton#alarm_3:hover{color:red}");
    connect(alarm_3, &QPushButton::clicked, this, &MssSystem::showAlarm3);

    QPushButton* alarm_all = new QPushButton(this);
    alarm_all->setIcon(QIcon(":/images/alarm1.png"));
    alarm_all->setText(tr("全部警报"));
    alarm_all->setFlat(true);
    alarm_all->setObjectName("alarm_all");
    alarm_all->setStyleSheet("QPushButton#alarm_all{background:transparent;color:blue;}QPushButton#alarm_all:hover{color:red}");
    connect(alarm_all, &QPushButton::clicked, this, &MssSystem::showAlarm4);

    //set alarm times
    alarm1_num = new QLabel(tr("：num1"));
    //alarm1_num->setText("20");
    alarm2_num = new QLabel(tr("：num2"));
    alarm3_num = new QLabel(tr("：num3"));
    alarm4_num = new QLabel(tr("：total"));

    alarm1Layout->addWidget(alarm_1);
    alarm1Layout->addWidget(alarm1_num);

    alarm2Layout->addWidget(alarm_2);
    alarm2Layout->addWidget(alarm2_num);

    alarm3Layout->addWidget(alarm_3);
    alarm3Layout->addWidget(alarm3_num);

    alarm4Layout->addWidget(alarm_all);
    alarm4Layout->addWidget(alarm4_num);

    bomLayout->addLayout(alarm1Layout);
    bomLayout->addStretch();
    bomLayout->addLayout(alarm2Layout);
    bomLayout->addStretch();
    bomLayout->addLayout(alarm3Layout);
    bomLayout->addStretch();
    bomLayout->addLayout(alarm4Layout);

    alarmbox->setLayout(bomLayout);
    return alarmbox;
}

QGroupBox* MssSystem::showAlarmDetail()
{
    alarmDetailbox = new QGroupBox(tr("详细警报系统"));
    QGridLayout *alarmDetailLayout = new QGridLayout;

    tableWidget = new QTableWidget(3,6);
    QStringList header;
    header<<"警报类型"<<"警报系统"<<"警报设备"<<"设备位置"<<"警报时间"<<"警报信息";

    tableWidget->setHorizontalHeaderLabels(header);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(tableWidget,&QTableWidget::customContextMenuRequested,
            this,&MssSystem::onTableWidgetCustomContextRuquested);

    alarm1_checkBox = new QCheckBox(tr("一级警报"));
    alarm2_checkBox = new QCheckBox(tr("二级警报"));
    alarm3_checkBox = new QCheckBox(tr("三级警报"));
    alarm4_checkBox = new QCheckBox(tr("预警"));

    connect(alarm1_checkBox,SIGNAL(stateChanged(int)),this,SLOT(onAlarm1CheckStateChanged(int)));
    connect(alarm2_checkBox,SIGNAL(stateChanged(int)),this,SLOT(onAlarm2CheckStateChanged(int)));
    connect(alarm3_checkBox,SIGNAL(stateChanged(int)),this,SLOT(onAlarm3CheckStateChanged(int)));

    alarmNo_checkBox = new QCheckBox(tr("报警静音"));
    alarmBack_checkBox = new QCheckBox(tr("隐藏报警"));
    alarmStop_checkBox = new QCheckBox(tr("暂停切换"));

    alarmDetailLayout->addWidget(alarm1_checkBox,0,0);
    alarmDetailLayout->addWidget(alarm2_checkBox,0,2);
    alarmDetailLayout->addWidget(alarm3_checkBox,0,4);
    alarmDetailLayout->addWidget(alarm4_checkBox,0,6);
    alarmDetailLayout->addWidget(alarmNo_checkBox,1,6);
    alarmDetailLayout->addWidget(alarmBack_checkBox,2,6);
    alarmDetailLayout->addWidget(alarmStop_checkBox,3,6);
    alarmDetailLayout->addWidget(tableWidget, 1, 0, 3, 6);

    connect(alarmBack_checkBox,SIGNAL(clicked()),this,SLOT(onAlarmBack()));
    alarmDetailbox->setLayout(alarmDetailLayout);
    return alarmDetailbox;
}

void MssSystem::showAlarm()
{
    alarmWidget->setVisible(false);
    alarmDetailWidget->setVisible(true);
    alarm1_checkBox->setChecked(true);
    alarm2_checkBox->setChecked(false);
    alarm3_checkBox->setChecked(false);
    alarmBack_checkBox->setChecked(false);
}

void MssSystem::showAlarm2()
{
    alarmWidget->setVisible(false);
    alarmDetailWidget->setVisible(true);
    alarm1_checkBox->setChecked(false);
    alarm2_checkBox->setChecked(true);
    alarm3_checkBox->setChecked(false);
    alarmBack_checkBox->setChecked(false);
}


void MssSystem::showAlarm3()
{
    alarmWidget->setVisible(false);
    alarmDetailWidget->setVisible(true);
    alarm1_checkBox->setChecked(false);
    alarm2_checkBox->setChecked(false);
    alarm3_checkBox->setChecked(true);
    alarmBack_checkBox->setChecked(false);
}

void MssSystem::showAlarm4()
{
    alarmWidget->setVisible(false);
    alarmDetailWidget->setVisible(true);
    alarm1_checkBox->setChecked(true);
    alarm2_checkBox->setChecked(true);
    alarm3_checkBox->setChecked(true);
    alarmBack_checkBox->setChecked(false);
}

void MssSystem::showAts(){
    if (hashChildWindow.contains("ats")) {
     //
    } else {
        showAtsWindow();
    }
    atsSystem->activateWindow();
    //-------------------------  MSS--->ATS
    emit sendEventToAts("ATSdeviceMap");
    //-------------------------
}

void MssSystem::showAtsWindow()
{
    hashChildWindow.insert("ats",atsSystem);
    atsSystem = new AtsSystem();
    atsSystem->show();

    // MSS-->ATS
    connect(this,&MssSystem::sendEventToAts,atsSystem,&AtsSystem::onEventFormMss);
    //ATS-->MSS
    connect(atsSystem,&AtsSystem::sendEventToMss,this,&MssSystem::onReceiveAtsEvent);
    //deal with db
    //connect(this,&MssSystem::sendThreadEventToAts,atsSystem,&AtsSystem::onThreadEventFromMss);

    connect(this,&MssSystem::sendEventToAtsUi,atsSystem,&AtsSystem::onAlarmFromMss);
}

void MssSystem::showAtsVobc()
{
    if(!hashChildWindow.contains("ats")){
        showAtsWindow();
    }
    atsSystem->activateWindow();
    emit sendEventToAts("showAtsVobc");
}

void MssSystem::showAtsZc()
{
    if(!hashChildWindow.contains("ats")){
        showAtsWindow();
    }
    atsSystem->activateWindow();
    emit sendEventToAts("showAtsZc");
}

void MssSystem::showAtsCi()
{
    if(!hashChildWindow.contains("ats")){
        showAtsWindow();
    }
    atsSystem->activateWindow();
    emit sendEventToAts("showAtsCi");
}

void MssSystem::showAtsAlarm(){
    if(!hashChildWindow.contains("ats")){
        showAtsWindow();
    }
    atsSystem->activateWindow();
    emit sendEventToAts("showAtsAlarm");
}

void MssSystem::DealFromAtsAlarmData(ats_mss_alarm_t *alarm_info)
{
    emit sendEventToAtsUi(alarm_info);
}

void MssSystem::onReceiveAtsEvent(const QString msg)
{
    // receiver quit message
   qDebug()<<"mss system msg : "<<msg;
   if (!msg.compare("quit")){
       hashChildWindow.remove("ats");
       atsSystem = NULL;
   }
}
//ats

void MssSystem::showCi(){
    if(hashChildWindow.contains("CI"))
    {

    }else
    {
       showCiWindow();
    }
    ciSystem->activateWindow();
    //connect ci thread to ci ui
    connect(ciThread, &CiService::sendToCiUi, ciSystem, &CiSystem::receiveCiAlarm);
    emit sendEventToCi("deviceMap");
}

void MssSystem::showCiWindow()
{
    hashChildWindow.insert("CI",ciSystem);
    ciSystem = new CiSystem();
    ciSystem->show();
    connect(this,&MssSystem::sendEventToCi,ciSystem,&CiSystem::onEventFromMss);
    connect(ciSystem,&CiSystem::sendEventToMss,this,&MssSystem::onReceiveEventFromCi);
}

void MssSystem::showCiAts()
{
    if(!hashChildWindow.contains("CI"))
    {
        showCiWindow();
    }
    ciSystem->activateWindow();
    emit sendEventToCi("showCiAts");
}

void MssSystem::showCiZc()
{
    if(!hashChildWindow.contains("CI"))
    {
        showCiWindow();
    }
    ciSystem->activateWindow();
    emit sendEventToCi("showCiZc");
}

void MssSystem::showCiVobc()
{
    if(!hashChildWindow.contains("CI"))
    {
        showCiWindow();
    }
    ciSystem->activateWindow();
    emit sendEventToCi("showCiVobc");
}

void MssSystem::showCiAlarm()
{
    if(!hashChildWindow.contains("CI"))
    {
        showCiWindow();
    }
    ciSystem->activateWindow();
    emit sendEventToCi("showCiAlarm");
}

void MssSystem::showCiMss()
{
    if(!hashChildWindow.contains("CI"))
    {
        showCiWindow();
    }
    ciSystem->activateWindow();
    emit sendEventToCi("showCiMss");
}

void MssSystem::showZCWarning(){
    if(!zchashChildWindow.contains("zc")){
        showZcWindow();
    }
    zcSystem->activateWindow();
    emit sendEventToZc("showZcAlarm");
}


void MssSystem::showZc(){
//    zcSystem = new ZcSystem();
//    zcSystem->show();
    if(zchashChildWindow.contains("zc")){
        qDebug()<<"zc window is not open";
    }else{
       showZcWindow();
    }
    zcSystem->activateWindow();
    emit  sendEventToZc("deviceMap");
}
void MssSystem::showZcWindow(){
    zchashChildWindow.insert("zc",zcSystem);
    zcSystem = new ZcSystem();
    zcSystem->show();
    connect(zcDataThread, &ZcDataThread::sendUiZcCiLs, zcSystem, &ZcSystem::receive_ui_zc_ci_ls);
    connect(this,&MssSystem::sendEventToZc,zcSystem,&ZcSystem::onEventFromMss);
    connect(zcSystem,&ZcSystem::sendEventToMss,this,&MssSystem::onReceiveZcEvent);
}

void MssSystem::onReceiveZcEvent(const QString msg){
    qDebug()<<"onReceiveZcEvent msg" <<msg;
    if(!msg.compare("quit")){
        zchashChildWindow.remove("zc");
        //disconnect(zcDataThread, SIGNAL(send_ui_zc_ci_ls(zc_header_t *, zc_ci_logical_section_t *)), zcSystem, SLOT(receive_ui_zc_ci_ls()));
        zcSystem=NULL;
    }else if(!msg.compare("ats")){
        showAts();
    }else if(!msg.compare("ci")){
        showCi();
    }else if(!msg.compare("vobc")){
        showVobc();
    }
}
void MssSystem::showZcAts()
{
    if(!zchashChildWindow.contains("zc")){
        showZcWindow();
    }
    zcSystem->activateWindow();
    emit sendEventToZc("showZCtoAts");
}

void MssSystem::showZcVobc()
{
    if(!zchashChildWindow.contains("zc")){
        showZcWindow();
    }
    zcSystem->activateWindow();
    emit sendEventToZc("showZCtoVobc");
}

void MssSystem::showZcCi()
{
    if(!zchashChildWindow.contains("zc")){
        showZcWindow();
    }
    zcSystem->activateWindow();
    emit sendEventToZc("showZCtoCi");
}
void MssSystem::showVobc(){
    if(hashChildWindow.contains("vobc")){
        //QMessageBox::warning(this,"warning","vobc has been opened");
    }else{
        showVobcWindow();
    }
    vobcSystem->activateWindow();
    emit sendEventToVobc("deviceMap");


}


void MssSystem::onReceiveVobcEvent(const QString msg)
{
    if(!msg.compare("quit")){
        hashChildWindow.remove("vobc");
        vobcSystem=NULL;
    }
}

void MssSystem::onReceiveVobcAlarm(vobc_subsys_msg_t AtsMsg)
{
    emit sendAlarmToVobc(AtsMsg);
}

void MssSystem::receive_alarm_data(vobc_subsys_msg_t msg)
{
//    qDebug()<<"receive alarm data:"<<msg.alarm_level<<" "
//           <<msg.alarm_subtype<<" "<<msg.alarm_type<<" "
//          <<msg.dev_id<<" "<<msg.dev_local<<" "
//         <<msg.dev_type<<" "<<msg.msg_type<<" "<<msg.sys_id<<" "
//        <<msg.alarm_code;
    bool canShow = false;
    QString strAlarmLevel;

    switch (msg.alarm_level) {
    case 1:
    {
        if(flag[0] == 1) canShow = true;
        strAlarmLevel = "一级警报";
    }
        break;
    case 2:
    {
        if(flag[1] == 1) canShow = true;
        strAlarmLevel = "二级警报";
    }
        break;
    case 3:
    {
        if(flag[2] == 1) canShow = true;
        strAlarmLevel = "三级警报";
    }
        break;
    default:
        strAlarmLevel = "未知警报";
        break;
    }

    if(!canShow) return;

//    QString subSysId;
//    switch (msg.id) {
//    case SUBSYS_ATS:
//        subSysId = "ATS";
//        break;
//    case SUBSYS_ZC:
//        subSysId = "ZC";
//        break;
//    case SUBSYS_VOBC:
//        subSysId = "VOBC";
//        break;
//    case SUBSYS_CI:
//        subSysId = "CI";
//        break;
//    default:
//        subSysId = "UNKNOWN";
//        break;
//    }

//    QString devLoc;
//    switch (msg.device_location) {
//    case LOCATE_INDOOR:
//        devLoc = "LOCATE_INDOOR";
//        break;
//    case LOCATE_OUTDOOR:
//        devLoc = "LOCATE_OUTDOOR";
//        break;
//    case LOCATE_GROUND:
//        devLoc = "LOCATE_GROUND";
//        break;
//    case LOCATE_VEHICLE:
//        devLoc = "LOCATE_VEHICLE";
//        break;
//    default:
//        devLoc = "LOCATE_UNKNOWN";
//        break;
//    }
    tableWidget->setItem(0,0,new QTableWidgetItem(strAlarmLevel));
    tableWidget->setItem(0,1,new QTableWidgetItem(QString::number(msg.sys_id)));
    tableWidget->setItem(0,2,new QTableWidgetItem(QString::number(msg.dev_id)));
    tableWidget->setItem(0,3,new QTableWidgetItem(QString::number(msg.dev_local)));
    tableWidget->setItem(0,4,new QTableWidgetItem(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")));
    tableWidget->setItem(0,5,new QTableWidgetItem(QString::number(msg.alarm_code)));

    tableWidget->show();
}

void MssSystem::onTableWidgetCustomContextRuquested(const QPoint&)
{
    alarmListMenu = new QMenu(tableWidget);
    alarmListMenu->addAction(tr("查看详情"),this,this->showAlarmInfoDlg);
    //alarmListMenu->addAction(tr("打印"),this,this->showAlarmInfoDlg);
    //alarmListMenu->addAction(tr("关闭"),this,this->showAlarmInfoDlg);
    alarmListMenu->exec(QCursor::pos());
}

void MssSystem::showAlarmInfoDlg()
{
    QList<QTableWidgetItem*> items = tableWidget->selectedItems();
    int count = items.count();
    QString displayText;
    QStringList strList;
    for(int i=0;i<count;i++){
        displayText = items.at(i)->text();
        strList<<displayText;
    }
    ShowDetailAlarm *alarmDetailBox = new ShowDetailAlarm(this);
    alarmDetailBox->fillData(strList);
    alarmDetailBox->show();
    return;
}

void MssSystem::showVobcWindow()
{
    hashChildWindow.insert("vobc",vobcSystem);
    vobcSystem = new VobcSystem();
    vobcSystem->show();
    connect(this,&MssSystem::sendEventToVobc,vobcSystem,&VobcSystem::onEventFromMss);
    connect(vobcSystem,&VobcSystem::sendEventToMss,this,&MssSystem::onReceiveVobcEvent);
    connect(this,&MssSystem::sendAlarmToVobc,vobcSystem,&VobcSystem::onAlarmFromMss);
}

void MssSystem::showVobcAts()
{
    if(!hashChildWindow.contains("vobc")){
        showVobcWindow();
    }
    vobcSystem->activateWindow();
    emit sendEventToVobc("showVobcAts");
}

void MssSystem::showVobcZc()
{
    if(!hashChildWindow.contains("vobc")){
        showVobcWindow();
    }
    vobcSystem->activateWindow();
    emit sendEventToVobc("showVobcZc");
}

void MssSystem::showVobcCi()
{
    if(!hashChildWindow.contains("vobc")){
        showVobcWindow();
    }
    vobcSystem->activateWindow();
    emit sendEventToVobc("showVobcCi");
}

void MssSystem::showVobcAlarm()
{
    if(!hashChildWindow.contains("vobc")){
        showVobcWindow();
    }
    vobcSystem->activateWindow();
    emit sendEventToVobc("showVobcAlarm");
}
void MssSystem::onReceiveEventFromCi(const QString msg)
{
    if(!msg.compare("close"))
    {
        hashChildWindow.remove("CI");
        //disconnect ci thread to ci ui
        disconnect(ciThread, &CiService::sendToCiUi, ciSystem, &CiSystem::receiveCiAlarm);
        ciSystem = NULL;
    }
}

//**jc** vobc code begin
void MssSystem::MssVobcInit()
{
    vobcDcsService = new VobcDcsService();
    vobcDcsThread = new QThread(this);
    vobcDcsService->moveToThread(vobcDcsThread);
    connect(vobcDcsThread, &QThread::finished, vobcDcsService, &QObject::deleteLater);
    connect(vobcDcsThread, &QThread::started, vobcDcsService, &VobcDcsService::startService);
    connect(vobcDcsThread, &QThread::finished, vobcDcsService, &VobcDcsService::stopService);

    vobcAtsService = new VobcAtsService();
    vobcAtsThread = new QThread(this);
    vobcAtsService->moveToThread(vobcAtsThread);
    connect(vobcAtsThread, &QThread::finished, vobcAtsService, &QObject::deleteLater);
    connect(vobcAtsThread, &QThread::started, vobcAtsService, &VobcAtsService::startService);
    connect(vobcAtsThread, &QThread::finished, vobcAtsService, &VobcAtsService::stopService);

    vobcDcsThread->start();
    vobcAtsThread->start();
}

void MssSystem::MssVobcDestroyed()
{
    vobcDcsThread->quit();
    vobcDcsThread->wait();
    vobcAtsThread->quit();
    vobcAtsThread->wait();
}

void MssSystem::SimulateDestroy()
{
    simulateService->setStopFlag(true);
    simulateService->quit();
    simulateService->wait();
}
//**jc** vobc code end

void MssSystem::showPower()
{
    if(!hashChildWindow.contains("power"))
    {
        showPowerWindow();
    }
    powerSystem->activateWindow();
}
void MssSystem::showPowerWindow(){
    hashChildWindow.insert("power",powerSystem);
    powerSystem = new PowerWindow();
    powerSystem->show();
    connect(this,&MssSystem::sendEventToPower,powerSystem,&PowerWindow::onEventForPower);
    connect(powerSystem,&PowerWindow::sendEventToMss,this,&MssSystem::onReceiveEventFromPower);
}

void MssSystem::showPowerAlarm()
{
    if(!hashChildWindow.contains("power"))
    {
        showPower();
    }
    powerSystem->activateWindow();
    int power_alarm =6;
    emit sendEventToPower(power_alarm,"power_alarm");
}

void MssSystem::onReceiveEventFromPower(const QString msg)
{
    if(!msg.compare("quit"))
    {
        hashChildWindow.remove("power");
        powerSystem = NULL;
    }
}

//add end
//add by halina
void MssSystem::MssZcInit()
{
    zcSimulateDataThread = new ZcSimulateDataThread();
    realZcSimulateDataThread = new QThread(this);
    zcSimulateDataThread->moveToThread(realZcSimulateDataThread);


    zcDataThread = new ZcDataThread("zcdbconn");
    realZcDataThread = new QThread(this);
    zcDataThread->moveToThread(realZcDataThread);
#ifdef RECEIVER_DIRECT
    connect(zcSimulateDataThread,&ZcSimulateDataThread::send_zc, zcDataThread, &ZcDataThread::receiveData, Qt::QueuedConnection);
#endif
    connect(realZcDataThread,&QThread::started, zcDataThread, &ZcDataThread::start, Qt::AutoConnection);
    realZcDataThread->start();
#ifdef SIMULATE
    connect(realZcSimulateDataThread,&QThread::started, zcSimulateDataThread, &ZcSimulateDataThread::start, Qt::AutoConnection);
    realZcSimulateDataThread->start();
#endif
}

void MssSystem::MssZcDestroyed()
{
#ifdef SIMULATE
    zcSimulateDataThread->isStop = true;
    realZcSimulateDataThread->quit();
    realZcSimulateDataThread->wait();
#endif
    realZcDataThread->quit();
    realZcDataThread->wait(); 
}
//end halina


//BYD flying.zhao 2017-2-20 Fix Rssp Begin
void MssSystem::MssRsspiInit()
{
    qDebug()<<"MssRsspiInit()";
    pRsspiSubThread = new RsspiThread;
    pRsspiRunThread = new QThread(this);
    pRsspiSubThread->moveToThread(pRsspiRunThread);
    connect(pRsspiRunThread,&QThread::started,pRsspiSubThread,&RsspiThread::BindReceiver);
#ifndef RECEIVER_DIRECT
    connect(pRsspiSubThread,&RsspiThread::SendToVobc,vobcDcsService, &VobcDcsService::handleDcsData);
    connect(pRsspiSubThread,&RsspiThread::SendToCI, ciThread, &CiService::receiveRouteData);
    connect(pRsspiSubThread,&RsspiThread::SendToZC, zcDataThread, &ZcDataThread::receiveData, Qt::QueuedConnection);
    connect(pRsspiSubThread,&RsspiThread::SendToATS,m_atsprocess, &AtsProcess::onReceiveData, Qt::QueuedConnection);
#endif
    pRsspiRunThread->start();
}
void MssSystem::StopRsspiThread()
{
    if(true == pRsspiRunThread->isRunning())
    {
        pRsspiRunThread->quit();
        pRsspiRunThread->wait();
        delete pRsspiRunThread;
        pRsspiRunThread = NULL;
        qDebug()<<"stop rsspithread!";
    }
}

void MssSystem::RsspiSimulateInit()
{
    qDebug()<<"RsspiSimulateInit()";
    pRsspiSimulate = new RsspiSimulate;
    pRsspiSimRunThread = new QThread(this);
    pRsspiSimulate->moveToThread(pRsspiSimRunThread);
    connect(pRsspiSimRunThread,&QThread::started,pRsspiSimulate,&RsspiSimulate::BindSend);

#ifdef SIMULATE
    connect(simulateService, &VobcSimulate::randomDcsData, pRsspiSimulate, &RsspiSimulate::SimulateMssRsspiData);
    connect(m_simulate_route_t, &SimulateDataService::msgPacked, pRsspiSimulate, &RsspiSimulate::SimulateMssRsspiData);
    connect(ciSimulate,&CiSimulate::sendCiRoute, pRsspiSimulate,&RsspiSimulate::SimulateMssRsspiData );
    connect(zcSimulateDataThread,&ZcSimulateDataThread::send_zc, pRsspiSimulate, &RsspiSimulate::SimulateMssRsspiData);
#endif

    pRsspiSimRunThread->start();
}

void MssSystem::StopRsspSimulate()
{
    if(true == pRsspiSimRunThread->isRunning())
    {
        pRsspiSimRunThread->quit();
        pRsspiSimRunThread->wait();
        delete pRsspiSimRunThread;
        pRsspiSimRunThread = NULL;
        qDebug()<<"stop rsspi simulate thread!";
    }

}

//BYD flying.zhao 2017-2-20 Fix Rssp End

/*
 * mysql_init is not thread-safe completely.
 * It's thread-safe only after a successful call.
 */
void MssSystem::MySqlDBInit()
{
    QString connectname;

    {
        QSqlDatabase db = QSqlDatabase::addDatabase(MSS_DB_DRIVER);
        connectname = db.connectionName();
        db.setHostName(MSS_DB_HOST_NAME);
        db.setPort(MSS_DB_PORT);
        db.setDatabaseName(MSS_DB_NAME);
        db.setUserName(MSS_DB_USER);
        db.setPassword(MSS_DB_PASSWORD);
        db.open();
        db.close();
    }

    QSqlDatabase::removeDatabase(connectname);
}

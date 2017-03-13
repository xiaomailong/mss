#ifndef MSSSYSTEM_H
#define MSSSYSTEM_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QThread>
#include <QGroupBox>
#include <QPushButton>
#include <QLayout>
#include <QCheckBox>
#include <QLabel>
#include <QTableWidget>
#include "atssystem.h"
#include "zcsystem.h"
#include "cisystem.h"
#include "vobcsystem.h"
#include "vobcdcsservice.h"
#include "vobcatsservice.h"
#include "vobc_data.h"

#include "SimulateDataService.h"
#include "atsprocess.h"
#include "ats_data.h"

#include "vobcsimulate.h"
#include "cisimulate.h"
#include "ciservice.h"
#include "zc/zcdayreport.h"
#include "zc/zcsimulatedatathread.h"
#include "zc/zcdatathread.h"
#include "zcsystem.h"

//add by yhj 20170211 for power monitor system
#include "power/ui/powerwindow.h"
#include "powerprocess.h"
#include "powersimulatedataservice.h"
//add end
#include "rsspithread.h"
#include "rsspisimulate.h"


//#define RSSPISIMULATETEST
//#define SIMULATE
//#define RECEIVER_DIRECT

namespace Ui {
class MssSystem;
}

class MssSystem : public QMainWindow
{
    Q_OBJECT

public:
    explicit MssSystem(QWidget *parent = 0);
    void createAction();
    void createMenus();
    ~MssSystem();
    void showVobcWindow();
    void showCiWindow();
    void showZcWindow();
    void showAtsWindow();

private:
    Ui::MssSystem *ui;
    QMenu *rilMenu;
    QMenu *warnMenu;
    QMenu *mesgMenu;
    QMenu *vidMenu;
    QMenu *replyMenu;
    QMenu *funcMenu;
    QMenu *sysMenu;
    QMenu *subsysMenu;
    QMenu *sbxxMenu;
    QMenu *gpsbMenu;
    QMenu *atsMenu;
    QMenu *ciMenu;
    QMenu *zcMenu;
    QMenu *vobcMenu;

    QMenu *hisWarnMenu;
    QMenu *totWarnMenu;

    QAction *timeWarnAction;
    QAction *hisWarnAction;
    QAction *totWarnAction;

    QAction *atsAction;
    QAction *ciAction;
    QAction *zcAction;
    QAction *vobcAction;
    QAction *mssatsAction;
    QAction *mssciAction;
    QAction *msszcAction;
    QAction *mssvobcAction;
    QAction *mssAction;

    QAction *planAction;
    QAction *listAction;
    QAction *applyAction;
    QAction *advAction;

    QAction *sbztAction;
    QAction *bjhfAction;
    QAction *jlqxAction;
    QAction *sjszAction;
    QAction *bfAction;
    QAction *sjccAction;

    QAction *qxglAction;
    QAction *rjpzAction;
    QAction *sztbAction;
    QAction *dyscAction;
    QAction *bzAction;

    QAction *subsysAction;
    QAction *sbxxAction;
    QAction *vobcxtsbAction;
    QAction *czlsAction;
    QAction *zyatsbAction;
    QAction *zcxtsbbAction;
    QAction *dysbAction;
    QAction *leusbAction;
    QAction *gpsbAction;

    QAction *jzqAction;
    QAction *zzjAction;
    QAction *xhjAction;
    QAction *pbmAction;
    QAction *jjtcanAction;

    QAction *bjsjAction;
    QAction *ddAction;
    QAction *sszxtAction;
    QAction *djAction;

    QAction *sjdtjAction;
    QAction *xtlxtjAction;
    QAction *ddgztjAction;
    QAction *xczbtjAction;
    QAction *jtxhsbAction;

    QWidget *widget;
    QWidget *subsysWidget;
    QWidget *alarmWidget;
    QWidget *alarmDetailWidget;
    QGroupBox *subsysbox;
    QGroupBox *alarmbox;
    QGroupBox *alarmDetailbox;
    QGroupBox *createSubSys();
    QGroupBox *createAlarm();
    QGroupBox *showAlarmDetail();

    QPushButton *btn_WJJC;
    QPushButton *btn_ATS;
    QPushButton *btn_CI;
    QPushButton *btn_JZ;
    QPushButton *btn_LEU;
    QPushButton *btn_DCS;
    QPushButton *btn_POWER;
    QPushButton *btn_ZC;
    QPushButton *btn_VOBC;

    //QMdiArea *mdiArea;
    void showAlarm();
    void showAlarm2();
    void showAlarm3();
    void showAlarm4();


    QAction *alarm_1;
    QAction *alarm_2;
    QAction *alarm_3;
    QAction *alarm_4;

    //报警按钮
    QCheckBox *alarm1_checkBox;
    QCheckBox *alarm2_checkBox;
    QCheckBox *alarm3_checkBox;
    QCheckBox *alarm4_checkBox;

    //报警次数
    QLabel *alarm1_num;
    QLabel *alarm2_num;
    QLabel *alarm3_num;
    QLabel *alarm4_num;

    QCheckBox *alarmNo_checkBox;
    QCheckBox *alarmBack_checkBox;
    QCheckBox *alarmStop_checkBox;

    //add by phy
    QTableWidget *tableWidget;
    QMenu *alarmListMenu;
    QLabel *mLabel;
    quint8 flag[3]={0,0,0};
    //end phy

    AtsSystem *atsSystem;
    CiSystem *ciSystem;
    ZcSystem *zcSystem;
    VobcSystem *vobcSystem;
    PowerWindow *powerSystem;

    QThread *realZcSimulateDataThread;
    ZcSimulateDataThread *zcSimulateDataThread;
    QThread *realZcDataThread;
    ZcDataThread *zcDataThread;
    void MssZcDestroyed();
    void MssZcInit();
    void MssAtsInit();
    void MssAtsDeInit();
    SimulateDataService *m_simulate_route_t;
    QThread *m_sds_thread;
    QThread *m_ats_thread;
    AtsProcess *m_atsprocess;

signals:
    void sendEventToVobc(const QString msg);
    void sendAlarmToVobc(vobc_subsys_msg_t AtsMsg);
    void sendEventToCi(const QString msg);
    void sendEventToZc(const QString msg);
    void sendEventToAts(const QString msg);

    void sendEventToAtsUi(ats_mss_alarm_t* alarm_info);
    void sendEventToPower(int type,QString actionName);

private slots:
    void onAlarm();
    void addAlbum();
    void totalAlarmAlbum();
    void deleteAlbum();
    void onAlarmBack();

public slots:
    void showAts();
    void showCi();
    void showZc();
    void showVobc();
    void onReceiveVobcEvent(const QString msg);
    void onReceiveVobcAlarm(vobc_subsys_msg_t AtsMsg);
    //add by phy
    void receive_alarm_data(vobc_subsys_msg_t msg);
    void onTableWidgetCustomContextRuquested(const QPoint&);
    void showAlarmInfoDlg();
    void onAlarm1CheckStateChanged(int state);
    void onAlarm2CheckStateChanged(int state);
    void onAlarm3CheckStateChanged(int state);
    //end phy
    void onReceiveEventFromCi(const QString msg);
    void  onReceiveAtsEvent(const QString msg);
    // ATS Parts
    void showAtsVobc();
    void showAtsZc();
    void showAtsCi();
    void showAtsAlarm();
    void DealFromAtsAlarmData(ats_mss_alarm_t* alarm_info);

    void showVobcAts();
    void showVobcZc();
    void showVobcCi();
    void showVobcAlarm();

    void showCiAts();
    void showCiZc();
    void showCiVobc();
    void showCiAlarm();
    void showCiMss();

    void showZcAts();
    void showZcCi();
    void showZcVobc();
    void onReceiveZcEvent(const QString msg);

    void showZCWarning();

public slots:
    void showPower();
    void showPowerWindow();
    void showPowerAlarm();
    void onReceiveEventFromPower(const QString msg);
private:
    QHash<QString, QMainWindow *> hashChildWindow;
    QHash<QString,QMainWindow *> zchashChildWindow;

    //**jc** vobc code begin
private:
    void MySqlDBInit();
    void MssVobcInit();
    void MssVobcDestroyed();

    //pVobcRilThread & pVobcRilService is for dealing with data from network switch
    QThread *vobcDcsThread;
    VobcDcsService *vobcDcsService;
    //pVobcAtsThread & pVobcAtsService is for dealing with data from ats system
    QThread *vobcAtsThread;
    VobcAtsService *vobcAtsService;

    VobcSimulate *simulateService;     //temp code

    //ci data background thread
    void mssCiDestroyed();
    void mssCiInit();
    CiSimulate* ciSimulate;
    CiService* ciThread;
    QThread* receiverThread;
    QThread* simulateThread;
private slots:
    void SimulateDestroy();
    //**jc** vobc code end

//BYD flying.zhao 2017-2-20 Fix Rssp Begin
private:
    RsspiThread *pRsspiSubThread;
    QThread *pRsspiRunThread;
    RsspiSimulate *pRsspiSimulate;
    QThread *pRsspiSimRunThread;

    void MssRsspiInit();
    void StopRsspiThread();
    void RsspiSimulateInit();
    void StopRsspSimulate();

//BYD flying.zhao 2017-2-20 Fix Rssp End
    //add by yhj 20170211 for power monitor system

private:
    void mssPowerInit();
    PowerProcess* powerProcess;
    QThread* powerThread;
    PowerSimulateDataService* powerSimulateDataService;
    QSqlRelationalTableModel *model;
    QMainWindow *realtimeReport;
    QTableView *tableView;
    QSqlQueryModel *model2;
    //add end
};

#endif // MSSSYSTEM_H

#ifndef SPLASH_H
#define SPLASH_H

#include <QSplashScreen>
#include <QCommandLinkButton>
#include "msssystem.h"


class Splash : public QSplashScreen
{
    Q_OBJECT

public:
    explicit Splash(QSplashScreen *parent = 0);
    ~Splash();

    void setBtnEnabled(bool);
    void SetSystemWidget(MssSystem* pWdgt);

private:
    QCommandLinkButton* enterBtn;
    MssSystem* m_pSysWidget;


public slots:
    void enterMssSystem();
};

#endif // SPLASH_H

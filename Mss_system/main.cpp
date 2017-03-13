#include "msssystem.h"
#include <QApplication>
#include <QSplashScreen>
#include <QPixmap>
#include "splash.h"

QString logPath="";

static bool willLogToConsole()
{
    bool ok = false;
    uint envcontrol = qgetenv("QT_LOGGING_TO_CONSOLE").toUInt(&ok);
    if (ok){
        return envcontrol;
    }
    return false;
}

bool qt_logging_to_console()
{
    static const bool logToConsole = willLogToConsole();
    return logToConsole;
}

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QMutex mutex;
    mutex.lock();

    QFile file(logPath);
    file.open(QIODevice::ReadWrite | QIODevice::Append);
    QTextStream stream(&file);
    stream << qFormatLogMessage(type,context,msg) << "\r\n";
    file.flush();
    file.close();

    mutex.unlock();
}
static void configLog(){
    qSetMessagePattern("[%{type}][%{time yyyy-MM-dd hh:mm:ss.zzz}][%{pid}:%{threadid}:%{qthreadptr}]%{if-debug}[%{file} %{line}]%{endif}[%{function}] - %{message}");

    if(qt_logging_to_console()){
        return;
    }
    QString strDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss");
    logPath=QDir::toNativeSeparators(QCoreApplication::applicationDirPath()+QDir::separator()+"log_"+strDateTime+".txt");
    qInstallMessageHandler(myMessageOutput);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    configLog();

    QPixmap pixmap(":/images/mss.png");
    QPixmap fitpixmap=pixmap.scaled(1440,900, Qt::IgnoreAspectRatio);

    Splash* splash = new Splash();
    splash->setPixmap(fitpixmap);
    splash->setWindowFlags(Qt::WindowStaysOnTopHint);
    splash->showFullScreen();
    splash->setBtnEnabled(false);
    splash->showMessage(QObject::tr("正在初始化数据..."),
                       Qt::AlignRight|Qt::AlignBottom);

    MssSystem sysWidget;
    splash->SetSystemWidget(&sysWidget);
    splash->showMessage(QObject::tr("初始化完毕"),
                       Qt::AlignRight|Qt::AlignBottom);

    splash->setBtnEnabled(true);

    return a.exec();
}

#ifndef VOBCUICOMMON_H
#define VOBCUICOMMON_H

#include <QDebug>

#define VOBC_DEBUG_ENABLED 1

#if VOBC_DEBUG_ENABLED
#define VOBC_DEBUG       qDebug
#define VOBC_INFO        qInfo
#define VOBC_WARN        qWarning
#define VOBC_FATAL       qFatal
#define VOBC_CRITICAL       qCritical
#else
#define VOBC_DEBUG       QT_NO_QDEBUG_MACRO
#define VOBC_INFO        QT_NO_QDEBUG_MACRO
#define VOBC_WARN        QT_NO_QDEBUG_MACRO
#define VOBC_FATAL    QT_NO_QDEBUG_MACRO
#define VOBC_CRITICAL    QT_NO_QDEBUG_MACRO
#endif


#endif // VOBCUICOMMON_H

#include <QCoreApplication>
#include <QDebug>

#include <QtCore/QCoreApplication>
#include <qcoreapplication.h>
#include <QDir>
#include <QProcess>
#include <iostream>
#include "mutex.h"
#include "log.h"
#include "AlarmLog.h"
#include "PreRtProduce.h"
#include "ServiceEIDSPreConfig.h"
#include "public_function_library.h"
#include "ErrorDef.h"

#define VERSION "2.0.0"

MutexLock g_oScanFile;

bool initMain(void)
{
    std::string strPath = PubOpt::SystemOpt::GetCurExePath();
    if (!SINGLETON(ServiceEIDSPreConfig)->initConfig(strPath + EIDS_CONFIG_FILE))
    {
        Aos_WriteLog("Initial Public Config Failure.");
        return false;
    }

    std::string strModeName = SINGLETON(ServiceEIDSPreConfig)->getModeName();
    bool bLogIsEnable = SINGLETON(ServiceEIDSPreConfig)->isShowLog();

    if (!SINGLETON(Log)->InitLog(strPath + "log/", strModeName, bLogIsEnable))
    {
        Aos_WriteLog("Initial LOG Environmental Failure.");
        return false;
    }

    Aos_WriteLog("Initial LOG Environmental Success.");
    return true;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int optch = 0;
    while((optch = getopt(argc, argv, "vV")) != -1)
    {
        // printf("optind: %d\n", optind); //下一个检索位置，即选项的参数位置
        switch (optch)
        {
        case 'V':
        case 'v':
            printf("version %s\n", VERSION);
            return 0;
        default:
            break;
        }
    }

    if (!initMain())
        return -1;

    PreRtProduce* m_pOpt = new PreRtProduce();
    if (m_pOpt->InitService())
        m_pOpt->ServiceStart();

    return a.exec();
}

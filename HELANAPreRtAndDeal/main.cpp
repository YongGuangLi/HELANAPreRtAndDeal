#include <QCoreApplication>
#include <QDebug>

#include <QtCore/QCoreApplication>
#include <qcoreapplication.h>
#include <QDir>

#include "mutex.h"
#include "log.h"
#include "AlarmLog.h"
#include "Count_service.h"
#include "ServiceEIDSPreConfig.h"
#include "public_function_library.h"
#include "ErrorDef.h"
#include <iostream>


MutexLock g_oScanFile;

bool initMain(void)
{
    std::string strPath = PubOpt::SystemOpt::GetCurExePath();
    if (!SINGLETON(ServiceEIDSPreConfig)->initConfig(strPath + EIDS_CONFIG_FILE))
    {
        std::cerr <<"Init Public Config Failed."<<std::endl;
        return false;
    }
    std::cerr <<strPath + EIDS_CONFIG_FILE<<std::endl;
    std::string strLogPath = SINGLETON(ServiceEIDSPreConfig)->getLogPath();
    std::string strModeName = SINGLETON(ServiceEIDSPreConfig)->getModeName();
    bool bLogIsEnable = SINGLETON(ServiceEIDSPreConfig)->isShowLog();

    if (!SINGLETON(Log)->InitLog(strLogPath, strModeName, bLogIsEnable))
    {
        std::cerr <<"Init Log Failed."<<std::endl;
        std::string strCmd = "echo Init Log Failed., >> D:/test.log";
        system(strCmd.c_str());
        return false;
    }
    Aos_WriteLog("Initial LOG Environmental Success.");
    return true;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if (!initMain())
    {
        return -1;
    }
    PreRtProduce* m_pOpt = new PreRtProduce("");
    if (m_pOpt->InitService())
    {
        m_pOpt->ServiceStart();
    }

    return a.exec();
}

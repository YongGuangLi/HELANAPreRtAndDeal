#include "log.h"
#include "Count_service.h"
#include "ServiceEIDSPreConfig.h"
//#include "alarm_adapter.h"
#include "ServiceEIDSPreConfig.h"
#include "public_function_library.h"

//定义全局变量
int gOnStop = HELA_SVR_START;

CountService::CountService(void)
{
    m_mapService.clear();
}

CountService::~CountService(void)
{
    DestoryFactoryService();
}

bool CountService::InitService(void)
{
	Aos_WriteLog("InitService START.");
    if (!InitRtaAlarm())            // 初始化告警环境
    {
        return false;
    }
	Aos_WriteLog("ConnectRtdbDB Start.");
    ConnectRtdbDB();           // 连接实时数据库
  
	Aos_WriteLog("InitFactoryService Start.");
    if (!InitFactoryService())      // 初始化电厂处理服务
    {
        return false;
    }
	Aos_WriteLog("InitService END.");
    return true;
}

bool CountService::InitRtaAlarm(void)
{
    /*if (!SINGLETON(AlarmAdapter)->Rta_InitAlarm())
    {
        return false;
    }
    AlarmInfo stAlarmInfo;
    stAlarmInfo.aAlarmID = RECOVER_ALARM_ID;
    stAlarmInfo.aAlarmLevel = ALL_NO_ALARM_LEVEL;
    if (!SINGLETON(AlarmAdapter)->Rta_SendAlarm(stAlarmInfo))
    {
        return false;
    }
    SINGLETON(Log)->WriteLog("Initial Rta Alarm Environmental Success.");*/
    return true;
}

bool CountService::ConnectRtdbDB(void)
{
//    std::string strFname = PubOpt::SystemOpt::GetCurExePath() + RTDB_CONFIG_FILE;
//    SINGLETON(RtdbAdapter)->RtdbInitial(strFname);
//	SINGLETON(RtdbAdapter)->m_strFname = strFname;
//    /*AlarmInfo stAlarmInfo;
//    stAlarmInfo.aAlarmID = RTDB_ALARM_ID;*/
//    if (!SINGLETON(RtdbAdapter)->RtdbConnect())
//    {
//        std::string strError = PubOpt::StringOpt::StringFormat(
//            "Connect Rtdb File: %s", strFname.c_str());
//        /*stAlarmInfo.aAlarmLevel = ERROR_ALARM_LEVEL;
//        stAlarmInfo.strDescribe = "Rtdb Connect Failed.";
//        SINGLETON(AlarmAdapter)->Rta_SendAlarm(stAlarmInfo);*/
//        SINGLETON(Log)->WriteLog(strError, true);
//        return false;
//    }
	//if (!SINGLETON(RtdbAdapter)->ReRtdbConnect())
	//{
	//	std::string strError = PubOpt::StringOpt::StringFormat(
 //           "Connect Rtdb File: %s", strFname.c_str());
 //       SINGLETON(Log)->WriteLog(strError, true);
 //       return false;
	//}
 //   /*stAlarmInfo.aAlarmLevel = NO_ALARM_LEVEL;
  //  SINGLETON(AlarmAdapter)->Rta_SendAlarm(stAlarmInfo);*/
    return true;
}

bool CountService::InitFactoryService(void)
{
	 std::string strFactoryCode;
    int nFactoryTotal = SINGLETON(ServiceEIDSPreConfig)->GetFactoryTotal();
	if(0==nFactoryTotal)
	{
		SINGLETON(Log)->WriteLog("Not GetFactory.");
		return false;
	}
    for (int i=0; i<nFactoryTotal; ++i)
    {
        strFactoryCode = SINGLETON(ServiceEIDSPreConfig)->GetFactoryIndexByIndex(i+1);
        m_mapService[strFactoryCode] = new PreRtProduce (strFactoryCode);
		m_mapService[strFactoryCode]->m_strFactoryCode = strFactoryCode;
		std::string strFactoryDateWay = SINGLETON(ServiceEIDSPreConfig)->GetFactoryDateWayByCode(strFactoryCode);
		if ("1"==strFactoryDateWay)
		{
			m_mapService[strFactoryCode]->mGetDateWay = eFromRtdb;
		}
		else
		{
			m_mapService[strFactoryCode]->mGetDateWay = eFromDir;
		}
		/*if (0==i)
		{
			if(!m_mapService[strFactoryCode]->initBasicInformation())
				SINGLETON(Log)->WriteLog("initBasicInformation ALL Factory init Failed.");
		}*/
        if (!m_mapService[strFactoryCode]->InitService())
        {
            SINGLETON(Log)->WriteLog(
                PubOpt::StringOpt::StringFormat("Init [%s] Factory Service Failed.", 
                strFactoryCode.c_str()));
            return false;
        }
		SINGLETON(Log)->WriteLog(PubOpt::StringOpt::StringFormat("Init [%s] Factory  Success.",strFactoryCode.c_str()));
    }
    SINGLETON(Log)->WriteLog("Init Service Success.");
    return true;
}

void CountService::ServiceStart(void)
{
    Thread::Start();
    SINGLETON(Log)->WriteLog("Start Service Success.");
	
}

void 
CountService::Run(void)
{
	StartFactoryService();
}

void CountService::StartFactoryService(void)
{
	if (gOnStop == HEAL_SVR_STOP) return;
	PreRtProduce* pCountOpt;
    std::map<std::string, PreRtProduce*>::iterator iter = m_mapService.begin();
    for (; iter != m_mapService.end(); ++iter)
    {
        pCountOpt = iter->second;
        if (NULL != pCountOpt)
        {
            pCountOpt->ServiceStart();
        }
    }

	while (!gOnStop)
	{
		PubOpt::SystemOpt::SleepWait(1000);
	}

	//检测是否停止 
	if (gOnStop)
	{
		for (iter = m_mapService.begin(); iter != m_mapService.end(); ++iter)
		{
			pCountOpt = iter->second;
			pCountOpt->StopService();
		}
		gOnStop = HEAL_SVR_STOP;
		PubOpt::SystemOpt::SleepWait(2000);
	}
	//Thread::SetTimeOut(100);
}

void CountService::StopService(void)
{
    StopFactoryService();

	gOnStop = HEAL_SVR_STOPING;
	while(gOnStop == HEAL_SVR_STOP)
	{
		PubOpt::SystemOpt::SleepWait(1000);
		Aos_WriteLog("Stop Wait");
	}
    SINGLETON(Log)->WriteLog("Stop Service Success.");
   /* AlarmInfo stAlarmInfo;
    stAlarmInfo.aAlarmID = STOP_ALARM_ID;
    stAlarmInfo.aAlarmLevel = STOP_ALARM_LEVEL;
    SINGLETON(AlarmAdapter)->Rta_SendAlarm(stAlarmInfo);*/
	Aos_WriteLog("DisConnect Oracle Data Base Success.");
    SINGLETON(Log)->WriteLog("Send Service Stop Alarm Success.");
//    SINGLETON(RtdbAdapter)->RtdbDisConnect();
    SINGLETON(Log)->WriteLog("DisConnect Rtdb Data Base Success.");
    //SINGLETON(AlarmAdapter)->Rta_ReleaseAlarm();
    SINGLETON(Log)->WriteLog("Release Rta Alarm Environmental Success.");
}

void CountService::StopFactoryService(void)
{
    std::map<std::string, PreRtProduce*>::iterator iter = m_mapService.begin();
    for (; iter != m_mapService.end(); ++iter)
    {
        PreRtProduce* pCountOpt = iter->second;
        if (NULL != pCountOpt)
        {
            pCountOpt->StopService();
        }
    }
	
}

void CountService::DestoryFactoryService(void)
{
    /*std::map<std::string, CountFactoryService*>::iterator iter = m_mapService.begin();
    for (; iter != m_mapService.end(); ++iter)
    {
        CountFactoryService* pCountOpt = iter->second;
        if (NULL != pCountOpt)
        {
            delete pCountOpt;
            pCountOpt = NULL;
        }
    }*/
    m_mapService.clear();
}

/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: PreRtProduce.cpp
* 文件描述: 电厂处理管理类
*  作  者 : %王凯%，
* 创建日期: 2016-1-12 10:26:37
*******************************************************************************/
#include "log.h"
#include "PreRtProduce.h"
//#include "mutex.h"
//#include "buff_points.h"
#include "public_function_library.h"
#include "AlarmLog.h"
//#include "StartupServer.h"
#include "Util.h"
#include <vector>

PreRtProduce::PreRtProduce(const std::string &strFactoryCode)
:mStopWait(false)
,m_strFactoryCode(strFactoryCode)
{
	mStartSvr = new StartupServer();
}

PreRtProduce::~PreRtProduce(void)
{
	if (mStartSvr != NULL) delete mStartSvr;
}

bool PreRtProduce::InitService(void)
{
	bool rslt ;
	//Aos_Assert_R(rslt, false);
	mStartSvr->m_strSerivceName = SINGLETON(ServiceEIDSPreConfig)->getModeName();
	mStartSvr->m_strFactoryCode = m_strFactoryCode;
	mStartSvr->mHisGetNum = SINGLETON(ServiceEIDSPreConfig)->GetHisNum();
	mStartSvr->mHisToRtDevMin = SINGLETON(ServiceEIDSPreConfig)->GetHisToRtDev();
	int iSysType= SINGLETON(ServiceEIDSPreConfig)->GetSysType();
    if (1 == iSysType)
	{
		rslt = mStartSvr->initial(eFromRtdb,mGetDateWay);
	}
	else
	{
		rslt = mStartSvr->initial(eFromDir,mGetDateWay);
	}
	
	//if (eFromDir==mGetDateWay)//系统采集数据方式为从文件目录读文件，则初始化文件采集
	//{
	//	std::string strPath = SINGLETON(ServiceEIDSPreConfig)->GetFactoryPathByCode(m_strFactoryCode);
	//	if (strPath.empty())
	//	{
	//		SINGLETON(Log)->WriteLog(PubOpt::StringOpt::StringFormat(
	//			"Count [%s] Factory Path Failed.", m_strFactoryCode.c_str()), true);
	//		return false;
	//	}
	//	if (!m_pPointOpt->InitPoints(strPath, m_strFactoryCode))
	//	{
	//		SINGLETON(Log)->WriteLog(PubOpt::StringOpt::StringFormat(
	//			"Init Points Path [%s], Factory [%s] Failed.", strPath.c_str(), m_strFactoryCode.c_str()), true);
	//		return false;
	//	}
	//	SINGLETON(Log)->WriteLog(PubOpt::StringOpt::StringFormat(
	//		"Init Points Path [%s], Factory [%s] Success.", strPath.c_str(), m_strFactoryCode.c_str()));
	//}
	//if (eFromRtdb==iSysType)//子站系统初始化文件发送
	//{
	//	Aos_Assert_R(InitSendBufferOpt(), false);
	//}
	return rslt;
}

//bool   PreRtProduce::InitSendBufferOpt(void)
//{
//	int nFactoryTotal = SINGLETON(ServiceEIDSPreConfig)->GetFactorySentTotal(m_strFactoryCode);
//	for (int i=0; i<nFactoryTotal; ++i)
//	{
//		std::string strPath = SINGLETON(ServiceEIDSPreConfig)->GetFactorySentPathByCode(m_strFactoryCode,i+1);
//		if (strPath.empty()) continue;
//		BuffPoints *buffWrite = new BuffPoints();
//
//		if(!buffWrite->InitBuff(strPath,"",2)) 
//		{
//			delete buffWrite;
//			continue;
//		}
//		m_mapSendOpt.insert(make_pair(strPath,buffWrite));
//	}
//	return true;
//}

void PreRtProduce::ServiceStart(void)
{
    Thread::Start();
    //Aos_WriteLog("Start Service Success.");
	std::string strLog = PubOpt::StringOpt::StringFormat("Start Thread Success %s;", mStartSvr->m_strFactoryCode.c_str());
	Aos_WriteLog(strLog.c_str());
}


void PreRtProduce::Run()
{
	mStartSvr->m_strFactoryCode = m_strFactoryCode;
	mStartSvr->calculate();	
	if (mStopWait)
	{
		mStartSvr->stop();
		mStopWait = false;
        PubOpt::SystemOpt::SleepWait(2000);
    }
	Thread::SetTimeOut(100);
}


void PreRtProduce::StopService(void)
{
    Aos_WriteLog("Start Stop Service");
    if(mStartSvr != NULL)
	{
		mStopWait = true;
		mStartSvr->destory();
	}
	while(mStopWait)
	{
		PubOpt::SystemOpt::SleepWait(1000);
		Aos_WriteLog("Stop Wait");
	}
	Thread::Stop();
    //Aos_WriteLog("Stop Service Success..");
	std::string strLog = PubOpt::StringOpt::StringFormat("Stop Thread Success %s;", mStartSvr->m_strFactoryCode.c_str());
	Aos_WriteLog(strLog.c_str());
}


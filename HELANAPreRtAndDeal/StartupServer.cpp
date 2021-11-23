/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: StartupServer.cpp
* 文件描述: 主控类
*  作  者 : %王凯%，
* 创建日期: 2016-1-12 10:56:06
*******************************************************************************/

#include "StartupServer.h"
#include "AlarmLog.h"
#include "BasicMgr.h"
#include "Util.h"
#include "PointPreCal.h"
#include "AlarmSetInfo.h"
#include "public_function_library.h"
#include "RecursiveCalculateIndex.h"
#include "compiler.h"

bool StartupServer::smDestory = false;
bool StartupServer::smSanityCheck = true;
bool StartupServer::smIsStartDelay = false;

StartupServer::StartupServer(void)
    :
      mFirstCal(true),
      mModConf(true),
      mSeCalCycSec(0),
      mSeLastTime(0),
      mCurSeCalTime(0),
      mBaseMgr(NULL)
{
    mInit = true;
    mHisGetNum = 6;
    mHisToRtDevMin = 5;
    m_strSerivceName = "HELANAPreRtAndDeal";
}

StartupServer::~StartupServer(void)
{
    if (mBaseMgr != NULL) delete mBaseMgr;
    if (mPointPreCal !=NULL) delete mPointPreCal;
}

bool
StartupServer::initial(const GetDateWay iSysType,const GetDateWay GetWay)
{
    mBaseMgr = new BasicMgr(m_strFactoryCode);
    mCalculateIndex = new RecursiveCalculateIndex();
    mPointPreCal = new PointPreCal(mCalculateIndex);
    //if (!mBaseMgr->initialRtdb()) return false;
    mSeCalCycSec = SINGLETON(ServiceEIDSPreConfig)->getServiceCalCycSec();
    //mBaseMgr->m_strFactoryCode = m_strFactoryCode;
    Aos_Assert_R(mBaseMgr->BuffInitial(iSysType,GetWay), false);
    return true;
}

void
StartupServer::destory()
{
    smDestory = true;
}

void
StartupServer::stop()
{
    //SINGLETON(RtdbAdapter)->RtdbDisConnect();
    Aos_WriteLog("DisConnect Rtdb Data Base Success.");

    //SINGLETON(RsdbAdapter)->OtlDisConnect();
    mBaseMgr->mQtOpt->QtDisConnect();
    Aos_WriteLog("DisConnect Oracle Data Base Success.");
}   


bool
StartupServer::calculate()
{
    bool rslt = mBaseMgr->loadConfigInfo(mFirstCal,mModConf,mCurSeCalTime);
    Aos_Assert_R(rslt, false);

    realtimeCal();
    return true;
}

void   StartupServer::realtimeCal()
{
    long lastSeCalTime = 0;
    while (true)
    {
        long nowTime = Util::getNowTime();

        if (nowTime  - lastSeCalTime >= mSeCalCycSec)
        {
            mBaseMgr->loadPointData(mCurSeCalTime, mNowTime);

            mBaseMgr->CleanMapWrite();

            //计算机组、系统、模型的Eps
            mCalculateIndex->startCalculate(mBaseMgr->getIndexConfInfo(), mBaseMgr->getPointData(), mBaseMgr->getmMapWrite(), mCurSeCalTime);

            //计算模型的Con
            mPointPreCal->CalculateAllModeCon(mBaseMgr->getmMapSetInfo(),mBaseMgr->getPointData(), mBaseMgr->getIndexConfInfo(),mBaseMgr->getmMapWrite());

            mBaseMgr->SetAllMothAvgData();

            //计算机组 系统 模型 SIM 健康度
            mPointPreCal->CalData(mBaseMgr->getMapModleNameStatus(),
                                  mBaseMgr->getmMapSetInfo(),
                                  mBaseMgr->getmMapModeMethodAvg(),
                                  mBaseMgr->getPointData(),
                                  mBaseMgr->getIndexConfInfo(),
                                  mBaseMgr->getmMapWrite(),
                                  mBaseMgr->msysType);

            mBaseMgr->WriteBuffer(mCurSeCalTime);

            mBaseMgr->WriteToRtdb(mCurSeCalTime);

            mBaseMgr->WriteRsdb(mCurSeCalTime);


            lastSeCalTime =  Util::getNowTime();;
        }
        PubOpt::SystemOpt::SleepWait(2000);
    }
}

void StartupServer::SetModelPointValues(MapStringToSetCfg	&mMapSetInfo,
                                        MapStringToPointData &mMapPointData,
                                        MapStringToString &pPointSourceName,
                                        const CMonmentDatas* monment)
{
    MapStringToSetCfg_It iter_set;
    MapStringToSysCfg_It iter_sys;
    MapStringToDataMode_It iter_m;
    MapStringToPointGroup_It iter_group;
    MapStringToPointData_It  iter_allp;
    MapStringToMDataValueInfo_It p_iter;
    MapMonmentPoint_const_It iter_Mp;

    MapStringToString_It iter;
    SetCfg * setcf;
    SysCfg * syscf;
    DataMode * mode_info;
    PointGroup* model_group;

    //MapStringToMDataValueInfo_It d_itr;

    std::vector<VarParam>::iterator pcf_iter;
    bool rslt;
    std::vector<std::string> lstRet;
    std::map<std::string,PointInfo*>::const_iterator mon_iter;
    mon_iter = monment->m_mapPointInfo.begin();
    for(;mon_iter != monment->m_mapPointInfo.end();mon_iter++)
    {
        iter = pPointSourceName.find(mon_iter->first);
        if (iter == pPointSourceName.end()) continue;

        lstRet.clear();
        rslt = Util::StringSplit(iter->second, lstRet, ",");
        if(!rslt) continue;
        for (unsigned int j = 0; j < lstRet.size(); j++)
        {
            if ("D3_FLN02AM"==lstRet[j])
                int itemp =100;
            iter_allp = mMapPointData.find(lstRet[j]);
            if (iter_allp!=mMapPointData.end())
            {
                iter_allp->second->setCurrVar(mon_iter->second->dValue);
                iter_allp->second->m_IsGetValue = true;
            }
        }
    }
    iter_set = mMapSetInfo.begin();
    for (;iter_set!=mMapSetInfo.end();++iter_set)
    {
        setcf = iter_set->second;
        iter_sys = setcf->mMapSys.begin();
        for (;iter_sys!=setcf->mMapSys.end();++iter_sys)
        {
            syscf = iter_sys->second;

            iter_m = syscf->mMapModles.begin();
            for(;iter_m!=syscf->mMapModles.end();++iter_m)
            {
                mode_info=iter_m->second;
                iter_group = mode_info->mMapGroup.begin();
                for (;iter_group!=mode_info->mMapGroup.end();++iter_group)
                {
                    model_group = iter_group->second;
                    p_iter = model_group->mMapGroupPoint.begin();
                    for(;p_iter !=  model_group->mMapGroupPoint.end();++p_iter)
                    {
                        p_iter->second->m_IsGetOrigValue  = false;
                        p_iter->second->m_IsGetPreValue = false;
                        p_iter->second->m_IsGetSimValue = false;
                        iter_Mp = monment->m_mapPointInfo.find(p_iter->second->mPOrigSource);
                        if (iter_Mp==monment->m_mapPointInfo.end()) continue;

                        p_iter->second->setCurrVar(iter_Mp->second->dValue,1);
                        p_iter->second->m_IsGetOrigValue  = true;
                        if("D3_FLN02AM"==p_iter->second->mPointId)
                            int icet  = 100;
                        iter_allp = mMapPointData.find(p_iter->second->mPointId);
                        if (iter_allp!=mMapPointData.end())
                        {
                            iter_allp->second->setCurrVar(iter_Mp->second->dValue);
                        }
                    }

                }
            }

        }
    }
    mCurSeCalTime = monment->lTimeStamp;
}

void  StartupServer::CalMonment(MapMonmentDatas	&mMapMonment)
{
    bool rslt;
    MapMonmentDatas_It it_m,it_m2;
    CMonmentDatas* monment;
    std::string strCalTime;
    it_m = mMapMonment.begin();
    for (;it_m!=mMapMonment.end();)
    {
        monment = it_m->second;
        if (!monment->m_isOk)
        {
            mBaseMgr->UpdateServiceVersion(m_strSerivceName,"v1.0.0",SINGLETON(Log)->getLogPath());
            continue;
        }
        mCurSeCalTime = it_m->first;
        strCalTime = PubOpt::SystemOpt::DateTmToStr(mCurSeCalTime);
        mBaseMgr->CleanMapWrite();
        SetModelPointValues(mBaseMgr->getmMapSetInfo(),mBaseMgr->getPointData(),mBaseMgr->getMapPointSourceName(),monment);
        delete monment;
        monment = NULL;
        mMapMonment.erase(it_m++);

        mCalculateIndex->startCalculate(mBaseMgr->getIndexConfInfo(),
                                        mBaseMgr->getPointData(),
                                        mBaseMgr->getmMapWrite(),
                                        mCurSeCalTime);
        mPointPreCal->CalculateAllModeCon(mBaseMgr->getmMapSetInfo(),mBaseMgr->getPointData(),
                                          mBaseMgr->getIndexConfInfo(),mBaseMgr->getmMapWrite());
        mBaseMgr->SetAllMothAvgData();

        mPointPreCal->CalData(mBaseMgr->getMapModleNameStatus(),
                              mBaseMgr->getmMapSetInfo(),
                              mBaseMgr->getmMapModeMethodAvg(),
                              mBaseMgr->getPointData(),
                              mBaseMgr->getIndexConfInfo(),
                              mBaseMgr->getmMapWrite(),
                              mBaseMgr->msysType);

        //将点值回写实时数据库
        //Aos_Assert_S("His WriteBuffer start.");
        mBaseMgr->WriteBuffer(getServerCalTime());

        rslt = mBaseMgr->WriteToRtdb(getServerCalTime());
        //将点值写入关系数据库中
        //Aos_Assert_S("His WriteRsdb start.");
        if(rslt)
            mBaseMgr->WriteRsdb(mCurSeCalTime);
        //Aos_Assert_S("His WriteRsdb end.");
        mBaseMgr->UpdataCalTime(strCalTime,1);
        mBaseMgr->UpdateServiceVersion(m_strSerivceName,"v1.0.0",SINGLETON(Log)->getLogPath());

    }
}
void  StartupServer::HisCal(long StartTime,long EndTime)
{
    if (EndTime-StartTime<=0) return;
    int hourtSum = (EndTime-StartTime)/3600;
    if (hourtSum>0)
    {
        for (int i=0;i<hourtSum;i++)
        {
            if(!mBaseMgr->loadHisPointData(StartTime,StartTime+60*60))
                continue;
            CalMonment(mBaseMgr->getMapMonment());
            StartTime += 60*60;
        }
    }
    else if (0==hourtSum)
    {
        if(!mBaseMgr->loadHisPointData(StartTime,EndTime))
            return;
        CalMonment(mBaseMgr->getMapMonment());
    }
}
void
StartupServer::run()
{
    //    bool is_Recal = false;
    //    long nowTime;
    //    nowTime = Util::getNowTime();
    //SINGLETON(RtdbAdapter)->RtdbGetCurrentTime(&nowTime);
    //	if(!mBaseMgr->rtdbGetRtTagTime(nowTime))
    //		SINGLETON(RtdbAdapter)->RtdbGetCurrentTime(&nowTime);

    ///	mBaseMgr->loadHisPointData(nowTime-3600,nowTime);
    //if (nowTime-mCurSeCalTime>120&&nowTime-mCurSeCalTime<mHisGetNum*60*60)
    //	std::string strNow =  PubOpt::SystemOpt::DateTmToStr(nowTime);
    //	std::string strCur =  PubOpt::SystemOpt::DateTmToStr(mCurSeCalTime);
    //	if (nowTime-mCurSeCalTime>mHisToRtDevMin*60)
    //	{
    //		is_Recal = true;
    //	}
    //	else
    //	{
    //		is_Recal = false;
    //	}
    //    if(is_Recal && eFromRtdb==mBaseMgr->msysType)
    //	{
    //		if (nowTime-mCurSeCalTime<=mHisGetNum*60*60)
    //			HisCal(mCurSeCalTime,nowTime);
    //		else
    //			HisCal(nowTime-mHisGetNum*60*60,nowTime);
    //	}
    //	else
    //	{
}



long
StartupServer::getServerCalTime()
{
    if (!smIsStartDelay)
        return mCurSeCalTime;
    if (mServerCalTimes.empty())
        return mCurSeCalTime;
    return  mServerCalTimes.front();
}

void
StartupServer::sanityCheck(const int flag)
{
    if (!smSanityCheck) return ;
    if (flag == 3)
        Aos_WriteLog(PubOpt::StringOpt::StringFormat("nowtime - servertime = %ld",Util::getNowTime() - mSeLastTime).c_str());

}


void
StartupServer::testPretreat()
{
    //    mBaseMgr->loadPointData(mCurSeCalTime);
}


void
StartupServer::testCal()
{	
    //mBaseMgr->loadPointData(mCurSeCalTime);
    //mBaseMgr->printMapDataValueInfo("D");
    Aos_WriteLog_D("=============================================");
    /*SINGLETON(RecursiveCalculateIndex)->startCalculate(
        mBaseMgr->getIndexConfInfo(),
        mBaseMgr->getMapPubSetInfo(),
        mBaseMgr->getDataValueInfo(),
        getServerCalTime());*/

    //mBaseMgr->printMapDataValueInfo("M");

    //pretreatCalMPoint();
    //mBaseMgr->saveIndexValue(mServerCalTime);
    //mBaseMgr->saveToMemCached(mServerCalTime);
}

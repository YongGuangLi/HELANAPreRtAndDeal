/*******************************************************************************
 * Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
 * 文 件 名: BasicMgr.cpp
 * 文件描述: 基础配置管理类
 *  作  者 : %王凯%，
 * 创建日期: 2016-1-12 16:13:42
 *******************************************************************************/

#include "BasicMgr.h"

#include "Util.h"
#include "AlarmLog.h"
#include "public_function_library.h"
#include "ServiceEIDSPreConfig.h"
#include "RDbOperationSimple.h"
#include "ErrorDef.h"
#include "TbDfhCfg.h"
#include "TbPubSetToPoint.h"
#include "TbPubModeMethodAvg.h"
#include "PointPreCal.h"
#include "StartupServer.h"

#include "LoadConfg.h"
#include "pub_index_data.h"

//#include "PPubPointValue.h"
//#include "Communal.h"


#include <string>
#include <iostream>

bool    BasicMgr::smSanityCheck = true;
BasicMgr::BasicMgr(void)
    :
      mIsExistMaunalPoint(false),ismDealAlarm(true),
      mSimpleOpt(NULL),
      mcountPoints(10000),
      m_pRecOpt(NULL)
{
    mQtOpt = new RsdbAdapter();
    mSimpleOpt = new RDbOperationSimple(mQtOpt);
    mAlarmdate = new AlarmSetDeal(mQtOpt,m_strFactoryCode);
    mDCNo = 0;
    //mInit = true;
}
BasicMgr::BasicMgr(const std::string &strFactoryId)
    :
      mIsExistMaunalPoint(false),ismDealAlarm(true),
      mSimpleOpt(NULL),
      mcountPoints(10000),
      m_pRecOpt(NULL),
      m_strFactoryCode(strFactoryId)
{
    std::string mThreadId = PubOpt::StringOpt::StringFormat(HELA_THREAD_ID_FACTORY_CAL, m_strFactoryCode.c_str());

    mQtOpt = new RsdbAdapter(mThreadId);
    mSimpleOpt = new RDbOperationSimple(mQtOpt);
    mAlarmdate = new AlarmSetDeal(mQtOpt,m_strFactoryCode);
    mDCNo = 0;
    //mInit = true;

    //Liyg
    pubPointValue = new PubPointValue(mQtOpt, m_strFactoryCode);
}
BasicMgr::~BasicMgr(void)
{
    mQtOpt->QtDisConnect();
    if(mSimpleOpt != NULL) delete mSimpleOpt;
    if (m_pRecOpt != NULL) delete m_pRecOpt;
    if (mAlarmdate != NULL) delete mAlarmdate;
    std::map<std::string, BuffPoints* >::iterator it = m_mapSendOpt.begin();
    for (; it !=m_mapSendOpt.end();++it)
    {
        delete it->second;
    }
    m_mapSendOpt.clear();

    if (NULL != m_pRecOpt)
    {
        delete m_pRecOpt;
        m_pRecOpt = NULL;
    }

    cleanVar();
    cleanAlarmVar();
}

bool BasicMgr::BuffInitial(const GetDateWay iSysType,const GetDateWay GetWay)
{
    msysType = iSysType;
    mGetDateType = GetWay;
    if (eFromDir==GetWay)//系统采集数据方式为从文件目录读文件，则初始化文件采集
    {
        std::string strPath = SINGLETON(ServiceEIDSPreConfig)->GetFactoryPathByCode(m_strFactoryCode);
        if (strPath.empty())
        {
            SINGLETON(Log)->WriteLog(PubOpt::StringOpt::StringFormat(
                                         "Count [%s] Factory Path Failed.", m_strFactoryCode.c_str()), true);
            return false;
        }
        m_pRecOpt = new BuffPoints();
        if (!m_pRecOpt->InitPoints(strPath, m_strFactoryCode))
        {
            SINGLETON(Log)->WriteLog(PubOpt::StringOpt::StringFormat(
                                         "Init Points Path [%s], Factory [%s] Failed.", strPath.c_str(), m_strFactoryCode.c_str()), true);
            return false;
        }
        SINGLETON(Log)->WriteLog(PubOpt::StringOpt::StringFormat(
                                     "Init Points Path [%s], Factory [%s] Success.", strPath.c_str(), m_strFactoryCode.c_str()));
    }
    if (eFromRtdb==msysType)//子站系统初始化文件发送
    {
        Aos_Assert_R(InitSendBufferOpt(), false);
    }
    return true;
}
bool   BasicMgr::InitSendBufferOpt(void)
{
    int nFactoryTotal = SINGLETON(ServiceEIDSPreConfig)->GetFactorySentTotal(m_strFactoryCode);
    for (int i=0; i<nFactoryTotal; ++i)
    {
        std::string strPath = SINGLETON(ServiceEIDSPreConfig)->GetFactorySentPathByCode(m_strFactoryCode,i+1);
        if (strPath.empty()) continue;
        BuffPoints *buffWrite = new BuffPoints();

        if(!buffWrite->InitBuff(strPath,"",2))
        {
            delete buffWrite;
            continue;
        }
        m_mapSendOpt.insert(make_pair(strPath,buffWrite));
    }
    return true;
}
bool	
BasicMgr::loadAlarmSetData()
{
    LoadConfg * opt= new LoadConfg();
    bool rslt = opt->loadAlarmInf(mMapAlarmSet,mVectorAlarmScore);
    delete opt;
    Aos_Assert_ERS(!mMapAlarmSet.empty(), false, Rsdb_ERROR_ALARMMODEINFO);
    return true;
}
bool
BasicMgr::loadIndex()
{

    pub_index_data *opter = new pub_index_data(mQtOpt);
    bool rslt = opter->loadDB(m_mapIndexConfInfo, mMapPointData, m_strFactoryCode);
    delete opter;
    Aos_Assert_ERS(!m_mapIndexConfInfo.empty(), false, Rsdb_ERROR_PUBINDEX);
    return rslt;
}
bool
BasicMgr::loadModeData()
{
    TbPubSetToPoint *opter = new TbPubSetToPoint(mQtOpt);
    bool rslt = opter->loadDB(mMapSetInfo, mMapModleNameStatus, m_strFactoryCode);
    opter->loadDBPoint(mMapAllPointSourceName, m_strFactoryCode);
    delete opter;
    Aos_Assert_ERS(!mMapSetInfo.empty(), false, Rsdb_ERROR_PUBMODEINFO);
    return rslt;
}
bool
BasicMgr::loadFhnlData()
{

    TbDfhCfg *opter = new TbDfhCfg(mQtOpt);
    bool rslt = opter->loadDB(mMapSetInfo,m_strFactoryCode);
    delete opter;
    return rslt;
}
bool 
BasicMgr::loadModeMuFun()
{
    TbPubModeMethodAvg* opt=new TbPubModeMethodAvg(mQtOpt);
    bool rslt = opt->loadDB(mMapModleNameStatus, mMapModeMethodAvg, mMapPointSourceName, m_strFactoryCode);
    delete opt;
    opt = NULL;
    Aos_Assert_ERS(!mMapModeMethodAvg.empty(), false, Rsdb_ERROR_PUBMODEFUNINFO);
    return rslt;
}

bool BasicMgr::UpdataCalTime(std::string strcalTime,const int itype)
{
    return mSimpleOpt->UpdataCalTime(m_strFactoryCode,strcalTime,itype);
}
bool
BasicMgr::loadConfigInfo()
{
    //select index_code, set_code, index_type, source_id, concat(out_var,out_var_func) out_var,local_var, expression,is_write_back,full_index_code ,is_clear_zero,is_steady_cal, min_value, \
    //max_value, default_value from v_pub_index t order by full_index_code asc

    Aos_WriteLog_D("Start loadIndex()");
    Aos_Assert_R(loadIndex(), false);
    Aos_WriteLog_D("End loadIndex()");

    //读入等配置信息
    Aos_WriteLog_D("Start loadModeData()");
    //select * from v_eids_model_monit_point_all
    //select point_code,source_id_original,set_code,full_point_code  from tb_pub_point
    Aos_Assert_R(loadModeData(), false);
    Aos_WriteLog_D("End loadModeData()");

    //select t.model_id,t.model_condition_id,t.similar_limit,t.monit_point_id, t.ma_value,t.model_value,t.model_value_relation \
    from  tb_eids_model_method_avg t left join  v_eids_model_all p  on t.model_id=p.model_id order by model_id,model_condition_id

            Aos_WriteLog_D("Start loadModeMuFun()");
    Aos_Assert_R(loadModeMuFun(), false);
    Aos_WriteLog_D("End loadModeMuFun()");

    Aos_WriteLog_D("Start GetNeedPoint()");
    GetNeedPoint();

    Aos_WriteLog_D("Start CheckModelAvgPointFitInfPointOnly()");
    CheckModelAvgPointFitInfPointOnly();

    Aos_WriteLog("checkWriteBackCodeRtdb begin.");
    Aos_Assert_R(checkWriteBackCodeRtdbIsExist(),false);
    Aos_Assert_R(checkReadSourceIdRtdbIsExist(), false);
    Aos_Assert_R(checkIndexSourceIdRtdbIsExist(), false);
    Aos_WriteLog("checkWriteBackCodeRtdb finish.");

    return true;
}

void
BasicMgr::cleanVar()
{
    MapStringToSetCfg_It iter = mMapSetInfo.begin();
    for (;iter !=mMapSetInfo.end();++iter)
    {
        delete iter->second;
    }
    mMapSetInfo.clear();
    /*MapStringToDataMode_It iter=mMapModeInfo.begin();
    for (;iter!=mMapModeInfo.end();++iter)
    {
        delete iter->second;
    }
    mMapModeInfo.clear();*/
    MapStringToMethodAvg_It iter_f;
    MapStringToModeMethodAvg_It iter_c=mMapModeMethodAvg.begin();
    for(;iter_c!=mMapModeMethodAvg.end();++iter_c)
    {
        delete iter_c->second;
    }
    mMapModeMethodAvg.clear();

    MapStringToIndexConfInfo_It iter_m = m_mapIndexConfInfo.begin();
    for (;iter_m!= m_mapIndexConfInfo.end();++iter_m)
    {
        delete iter_m->second;
    }
    m_mapIndexConfInfo.clear();
    MapStringToPointData_It it_p = mMapPointData.begin();
    for (;it_p !=mMapPointData.end();++it_p)
    {
        delete it_p->second;
    }
    mMapPointData.clear();

    mMapPointSourceName.clear();
    mMapWrite.clear();

    mMapAllPointSourceName.clear();

    mVectorAlarmScore.clear();
}

void
BasicMgr::cleanAlarmVar()
{
    MapStringToAlarmSetInfo_It		it_set;
    MapStringToAlarmSetSys_It		it_sys;
    MapStringToAlarmModel_It		it_model;
    MapStringToAlaramModelGroup_It	it_group;
    MapStringToAlarmPointInfo_It	it_point;
    for (it_set = mMapAlarmSet.begin();it_set!=mMapAlarmSet.end();++it_set)
    {
        for (it_sys = it_set->second->mapSys.begin();it_sys!= it_set->second->mapSys.end();++it_sys)
        {
            for (it_model = it_sys->second->mapAlarmMode.begin();it_model!= it_sys->second->mapAlarmMode.end();++it_model)
            {
                for (it_group = it_model->second->mapAlarmGroup.begin();it_group != it_model->second->mapAlarmGroup.end();++it_group)
                {
                    for (it_point = it_group->second->mapPointInfo.begin();it_point!=it_group->second->mapPointInfo.end();++it_point)
                    {
                        delete it_point->second;
                    }
                    it_group->second->mapPointInfo.clear();
                    delete it_group->second;
                }
                it_model->second->mapAlarmGroup.clear();
                delete it_model->second;
            }
            it_sys->second->mapAlarmMode.clear();
            delete it_sys->second;
        }
        it_set->second->mapSys.clear();
        delete it_set->second;
    }
    mMapAlarmSet.clear();
}
bool  BasicMgr::RecBuffer( long &lTimeStamp,
                           const long nowTime,
                           MapStringToSetCfg &mMapSetInfo,
                           MapStringToString &mMapPointSourceName,
                           MapStringToPointData &mPointData)
{
    //bool rslt;
    SetCfg *  setcf;
    SysCfg *  syscf;
    DataMode* mode_info;
    PointGroup* group_p;
    DataValueInfo* point_info;
    //DataInfo*   dpoint;
    MapStringToSetCfg_It   set_iter;
    MapStringToSysCfg_It   sys_iter;
    MapStringToDataMode_It m_iter;
    MapStringToPointGroup_It g_iter;
    MapStringToMDataValueInfo_It p_iter;
    MapStringToPointData_It      dp_iter;
    MapStringToString_It	     ps_iter;
    std::map<std::string , ModelPackageValue*> mapPoint;
    std::map<std::string , ModelPackageValue*>::iterator bufp_iter;
    ModelPackageValue* pPoint;
    std::vector<std::string> lstRet;
    bool rslt = true ;
    if (eFromDir!=mGetDateType)
    {
        return false;
    }
    //liyg
    //	if(!SINGLETON(RtdbOpt)->RtdbIsConnect())
    //	{
    //		rslt = SINGLETON(RtdbAdapter)->RtdbConnect();
    //		rslt = SINGLETON(RtdbAdapter)->RtdbIsConnect();
    //	}
    if(!rslt)
        return false;
    int num = m_pRecOpt->GetBuffFileCount();
    Aos_Assert_R(m_pRecOpt->ReadBuffFile(), false);
    int nTotal = m_pRecOpt->GetPointCount();
    std::cout<<nTotal<<std::endl;
    std::string strtemp = m_pRecOpt->GetPacketDTime();
    lTimeStamp = PubOpt::SystemOpt::StrToDateTm(m_pRecOpt->GetPacketDTime());
    lTimeStamp = m_pRecOpt->m_stPoints.PackTime;
    for (int i=0; i<nTotal; ++i)
    {
        pPoint = m_pRecOpt->GetPointsValueEx(i,nTotal);
        if (NULL == pPoint)
        {
            continue;
        }
        std::string strCode = PubOpt::StringOpt::TrimString(pPoint->Name);
        if("D4_FLN02AM"==strCode)
            int itemp = 100;
        //std::cout<<i<<std::endl;
        //std::cout<<strCode<<std::endl;
        mapPoint.insert(make_pair(strCode,pPoint));

        dp_iter = mMapPointData.find(strCode);
        if (dp_iter!=mMapPointData.end())
        {
            dp_iter->second->setCurrVar(pPoint->Value);
            dp_iter->second->m_IsGetValue = true;
        }

    }
    //	Aos_WriteLog_D(PubOpt::StringOpt::StringFormat("factory: %s RecBuffer 7",m_strFactoryCode.c_str()).c_str());
    /*for (dp_iter = mMapPointData.begin();dp_iter!=mMapPointData.end();++dp_iter)
    {
        bufp_iter = mapPoint.find(dp_iter->second->mPointId);
        if (bufp_iter!=mapPoint.end())
        {
            dp_iter->second->setCurrVar(bufp_iter->second->Value);
            dp_iter->second->m_IsGetValue = true;
        }
        else
        {
            dp_iter->second->m_IsGetValue = false;
        }
    }*/
    set_iter = mMapSetInfo.begin();
    for(;set_iter!= mMapSetInfo.end();++set_iter)
    {
        setcf = set_iter->second;
        sys_iter = setcf->mMapSys.begin();
        for (;sys_iter!=setcf->mMapSys.end();++sys_iter)
        {
            syscf = sys_iter->second;
            m_iter = syscf->mMapModles.begin();
            for (;m_iter!=syscf->mMapModles.end();++m_iter)
            {
                mode_info = m_iter->second;
                mode_info->m_IsCalOk = true;
                g_iter = mode_info->mMapGroup.begin();
                for (;g_iter!=mode_info->mMapGroup.end();++g_iter)
                {
                    group_p = g_iter->second;
                    p_iter = group_p->mMapGroupPoint.begin();
                    for (;p_iter!=group_p->mMapGroupPoint.end();++p_iter)
                    {
                        point_info = p_iter->second;
                        //bufp_iter = mapPoint.find(point_info->mPointId);
                        bufp_iter = mapPoint.find(point_info->mMonitPointId);
                        if (bufp_iter==mapPoint.end())
                        {
                            point_info ->m_IsGetOrigValue = false;
                            point_info->m_IsGetPreValue = false;
                            point_info->m_IsGetSimValue = false;
                            mode_info->m_IsCalOk = false;
                            continue;
                        }
                        pPoint = bufp_iter->second;

                        dp_iter = mMapPointData.find(point_info->mPointId);
                        if (dp_iter!=mMapPointData.end())
                        {
                            dp_iter->second->setCurrVar(pPoint->Value);
                            dp_iter->second->m_IsGetValue = true;
                        }
                        /*else
                        {
                            dp_iter->second->m_IsGetValue = false;
                        }*/
                        if ('0'==pPoint->PointType)
                        {
                            point_info->setCurrVar(pPoint->Value,1);
                            point_info ->m_IsGetOrigValue = true;
                            point_info->m_IsGetPreValue = false;
                            point_info->m_IsGetSimValue = false;

                        }
                        else if ('1'==pPoint->PointType)
                        {
                            point_info->setCurrVar(pPoint->Value,1);
                            point_info->setCurrVar(pPoint->ExpectVal,2);
                            point_info->setCurrVar(pPoint->HealthVal,3);
                            point_info ->m_IsGetOrigValue = true;
                            point_info->m_IsGetPreValue = true;
                            point_info->m_IsGetSimValue = true;
                        }
                    }
                }
            }
        }
    }
    //	Aos_WriteLog_D(PubOpt::StringOpt::StringFormat("factory: %s RecBuffer 8",m_strFactoryCode.c_str()).c_str());
    return true;
}
void BasicMgr::BuffIntoData(BuffPoints *buffWrite)
{
    //std::string err;
    SetCfg *  setcf;
    SysCfg *  syscf;
    DataMode* mode_info;
    //ModelCondition* mode_condtion;
    PointGroup* group_p;
    DataValueInfo* point_info;

    MapStringToSetCfg_It   set_iter;
    MapStringToSysCfg_It   sys_iter;
    MapStringToDataMode_It m_iter;
    //MapStringToModeCond_It c_iter;
    MapStringToPointGroup_It g_iter;
    MapStringToMDataValueInfo_It p_iter;

    Dfhnl * dfh;
    MapStringToDfhnl_It    d_iter;
    MapStringToPointData_It p2_iter;
    DataInfo* point;
    int iPointNum = 0; //点的个数
    set_iter = mMapSetInfo.begin();
    for(;set_iter!= mMapSetInfo.end();++set_iter)
    {
        setcf = set_iter->second;
        sys_iter = setcf->mMapSys.begin();
        for (;sys_iter!=setcf->mMapSys.end();++sys_iter)
        {
            syscf = sys_iter->second;
            d_iter = syscf->mMapSysDfhnl.begin();
            for(;d_iter!=syscf->mMapSysDfhnl.end();++d_iter)
            {
                dfh = d_iter->second;
                p2_iter = mMapPointData.find(dfh->m_code);
                if (p2_iter==mMapPointData.end())
                {
                    continue;
                }
                point = p2_iter->second;
                if (point->mPointId=="D4_FLN02AM")
                    int ter =100;
                strcpy(buffWrite->m_stPoints.MPValues[iPointNum].SetCode,setcf->mSetCode.c_str());//机组号
                //strcpy(buffWrite->m_stPoints.MPValues[iPointNum].Name,point_info->mPointId.c_str()); //点名称
                strcpy(buffWrite->m_stPoints.MPValues[iPointNum].Name,point->mPointId.c_str()); //点名称
                buffWrite->m_stPoints.MPValues[iPointNum].State = '1';				   //状态
                buffWrite->m_stPoints.MPValues[iPointNum].Time = buffWrite->m_stPoints.PackTime;
                buffWrite->m_stPoints.MPValues[iPointNum].Value = point->getCurrVar(1); //当前值
                buffWrite->m_stPoints.MPValues[iPointNum].PointType = '0';
                iPointNum += 1;
                /*err = PubOpt::StringOpt::StringFormat("mPointId :%s Value:%f",point->mPointId.c_str(),point->getCurrVar(1));
                Aos_Assert_S(err.c_str());*/
            }
            m_iter = syscf->mMapModles.begin();
            for (;m_iter!=syscf->mMapModles.end();++m_iter)
            {
                mode_info = m_iter->second;
                if(mode_info->mModeId=="ZZ_3_qb")
                    int pio = 100;
                g_iter = mode_info->mMapGroup.begin();
                for (;g_iter!=mode_info->mMapGroup.end();++g_iter)
                {
                    group_p = g_iter->second;
                    p_iter = group_p->mMapGroupPoint.begin();
                    for (;p_iter!=group_p->mMapGroupPoint.end();++p_iter)
                    {
                        point_info = p_iter->second;
                        if (!point_info->m_IsGetOrigValue) continue;

                        if(iPointNum==1972)
                            int ibreak = 100;
                        /*p2_iter = mMapPointData.find(point_info->mPointId);
                        if (p2_iter!=mMapPointData.end())
                            p2_iter->second->mIsWriteRtdb = true;*/
                        //buffWrite->m_stPoints.Points[iPointNum].SetCode = setcf->mSet;    //机组号
                        strcpy(buffWrite->m_stPoints.MPValues[iPointNum].SetCode,setcf->mSetCode.c_str());//机组号
                        //strcpy(buffWrite->m_stPoints.MPValues[iPointNum].Name,point_info->mPointId.c_str()); //点名称
                        strcpy(buffWrite->m_stPoints.MPValues[iPointNum].Name,point_info->mMonitPointId.c_str()); //点名称
                        buffWrite->m_stPoints.MPValues[iPointNum].State = '1';				   //状态
                        buffWrite->m_stPoints.MPValues[iPointNum].Time = buffWrite->m_stPoints.PackTime;
                        buffWrite->m_stPoints.MPValues[iPointNum].Value = point_info->getCurrVar(1); //当前值
                        if (point_info->m_IsGetPreValue&&point_info->m_IsGetSimValue)
                        {
                            buffWrite->m_stPoints.MPValues[iPointNum].PointType = '1';
                            buffWrite->m_stPoints.MPValues[iPointNum].ExpectVal = point_info->getCurrVar(2); //期望值
                            buffWrite->m_stPoints.MPValues[iPointNum].HealthVal = point_info->getCurrVar(3); //健康度值
                            /*err = PubOpt::StringOpt::StringFormat("mPointId :%s Value:%f Value2:%f Value3:%f",point_info->mMonitPointId.c_str(),point->getCurrVar(1),point->getCurrVar(2),point->getCurrVar(3));
                            Aos_Assert_S(err.c_str());*/
                        }
                        else
                        {
                            buffWrite->m_stPoints.MPValues[iPointNum].PointType = '0';
                            /*err = PubOpt::StringOpt::StringFormat("mPointId :%s Value:%f",point_info->mMonitPointId.c_str(),point_info->getCurrVar(1));
                            Aos_Assert_S(err.c_str());*/
                        }
                        iPointNum += 1;
                    }
                }
            }
        }
    }
    for(p2_iter = mMapPointData.begin();p2_iter!=mMapPointData.end();++p2_iter)
    {
        point = p2_iter->second;
        if("D4_FLN02AM"==point->mPointId||"D3_MPN04AM"==point->mPointId)
            int ipt =100;
        if (eRealTimeOrgDPoint==point->mPointType&&point->mNotInMedlePoints)
        {
            if(!point->m_IsGetValue)
                continue;
            strcpy(buffWrite->m_stPoints.MPValues[iPointNum].SetCode,point->mSet.c_str());//机组号
            //strcpy(buffWrite->m_stPoints.MPValues[iPointNum].Name,point_info->mPointId.c_str()); //点名称
            strcpy(buffWrite->m_stPoints.MPValues[iPointNum].Name,point->mPointId.c_str()); //点名称
            buffWrite->m_stPoints.MPValues[iPointNum].State = '1';				   //状态
            buffWrite->m_stPoints.MPValues[iPointNum].Time = buffWrite->m_stPoints.PackTime;
            buffWrite->m_stPoints.MPValues[iPointNum].Value = point->getCurrVar(1); //当前值
            buffWrite->m_stPoints.MPValues[iPointNum].PointType = '0';
            iPointNum += 1;
            /*err = PubOpt::StringOpt::StringFormat("mPointId :%s Value:%f",point->mPointId.c_str(),point->getCurrVar(1));
            Aos_Assert_S(err.c_str());*/
        }
    }
    buffWrite->m_stPoints.Count = iPointNum;
}
void BasicMgr::WriteRsdb(const long mCurSeCalTime)
{
    QFile fileHandler(QString::fromStdString( PubOpt::SystemOpt::GetCurExePath()) + "sql.txt.tmp");
    if(fileHandler.open(QIODevice::Append))
    {
        QTextStream stream(&fileHandler);

        stream<<"begin;"<<'\n';

        stream<<"delete from tb_pub_point_value_cur;"<<'\n';

        QList<stCurPointValue> listCurPointValue = pubPointValue->listCurPointValue;
        for(int i = 0; i < listCurPointValue.size(); ++i)
        {
            stCurPointValue curPointValue = listCurPointValue.at(i);
            QString strInsertSQL = QString(SQL_INSERT_PUB_POINT_VALUE_CUR).arg(curPointValue.full_point_code.c_str()).arg(curPointValue.point_value).arg(curPointValue.timestamp.toString("yyyy-MM-dd hh:mm:ss"));
            stream<<strInsertSQL<<'\n';
        }

        fileHandler.close();
    }

    mAlarmdate->WriteRsdb(mMapSetInfo,mMapPointData,m_strFactoryCode,mCurSeCalTime);

    if(fileHandler.open(QIODevice::Append))
    {
        QTextStream stream(&fileHandler);
        std::string strSQL =  PubOpt::StringOpt::StringFormat(g_strUpdateSysCalTimeSQL.c_str(),PubOpt::SystemOpt::DateTmToStr(mCurSeCalTime).c_str(), 1);
        stream<<QString::fromStdString(strSQL)<<'\n';
        stream<<"commit;"<<'\n';
        fileHandler.close();
    }

    if(QFile::exists(QString::fromStdString( PubOpt::SystemOpt::GetCurExePath()) + "sql.txt"))
        QFile::remove(QString::fromStdString( PubOpt::SystemOpt::GetCurExePath()) + "sql.txt");

    QFile::rename(QString::fromStdString( PubOpt::SystemOpt::GetCurExePath()) + "sql.txt.tmp", QString::fromStdString( PubOpt::SystemOpt::GetCurExePath()) + "sql.txt");
}
bool BasicMgr::UpdateServiceVersion(std::string strServiceName,std::string strVersion,std::string strLog)
{
    return mAlarmdate->UpdateServiceVersion(strServiceName,strVersion,strLog);
}
void BasicMgr::WriteBuffer(long mCurSeCalTime)
{
    if (eFromRtdb!=msysType) return;     //不是子站直接返回

    mapBuffPoints_It itsent;
    BuffPoints *buffWrite = NULL;
    extern MutexLock g_oScanFile;
    AutoLock oAutoLock(g_oScanFile);
    if (0==m_mapSendOpt.size()||0==mcountPoints)
    {
        return;
    }
    itsent = m_mapSendOpt.begin();
    for (;itsent!=m_mapSendOpt.end();++itsent)
    {
        buffWrite = itsent->second;
        buffWrite->CreatePointData(mcountPoints);
        buffWrite->m_stPoints.DCNo = mDCNo;					    //电厂序号
        buffWrite->m_stPoints.ID = false;														//包中没有点ID号
        buffWrite->m_stPoints.Name = true;														//包中有点名
        buffWrite->m_stPoints.No = 1;															//包序号
        buffWrite->m_stPoints.NodeNo = 64;														//节点号(值固定)
        buffWrite->m_stPoints.PackTime = mCurSeCalTime;								//包发送时间(作为点时间)
        buffWrite->m_stPoints.SetCode = true;													//包中有点机组号
        buffWrite->m_stPoints.State = true;													    //包中有点状态
        buffWrite->m_stPoints.Time = true;
        buffWrite->m_stPoints.Count = 0;
    }
    itsent = m_mapSendOpt.begin();
    for (;itsent!=m_mapSendOpt.end();++itsent)
    {
        buffWrite = itsent->second;
        Aos_Assert_S("BuffIntoData.");
        BuffIntoData(buffWrite);//buffWrite赋值
        //发送数据
        if (buffWrite->m_stPoints.Count > 0)
        {
            Aos_Assert_S("SentPointData.");
            buffWrite->SentPointData();
        }
        //释放内存
        Aos_Assert_S("DestoryPoints.");
        buffWrite->DestoryPoints();
    }
};
void
BasicMgr::checkWritePointRtdbIsExist(MapStringToMDataValueInfo &mapPoints)
{
    MapStringToMDataValueInfo_It p_itr;
    DataValueInfo * point;
    p_itr = mapPoints.begin();
    //liyg
    //	for (;p_itr!=mapPoints.end();++p_itr)
    //	{
    //		point = p_itr->second;
    //		if (eFromRtdb==msysType)
    //		{
    //			point->mRtdbPOrigSourceIsExist = true;
    //			if (!SINGLETON(RtdbAdapter)->RtdbIsExistPoint(point->mPOrigSource,NOExitOrg)||point->mPOrigSource.empty())
    //			{
    //				point->mRtdbPOrigSourceIsExist = false;
    //				continue;
    //			}
    //			mcountPoints++;
    //		}
    //		point->mRtdbPointSourceIsExist = true;
    //		if (!SINGLETON(RtdbAdapter)->RtdbIsExistPoint(point->mPointSource,NOExitOrg)||point->mPointSource.empty())
    //		{
    //			point->mRtdbPointSourceIsExist = false;
    //		}
    //		point->mRtdbPreSourceIsExist = true;
    //		if (!SINGLETON(RtdbAdapter)->RtdbIsExistPoint(point->mPreSource,NOExitPre)||point->mPreSource.empty())
    //		{
    //			point->mRtdbPreSourceIsExist = false;
    //		}

    //		point->mRtdbSimSourceIsExist = true;
    //		if (!SINGLETON(RtdbAdapter)->RtdbIsExistPoint(point->mSimSource,NOExitSim)||point->mSimSource.empty())
    //		{
    //			point->mRtdbSimSourceIsExist = false;
    //		}
    //	}
}
bool
BasicMgr::checkWriteBackCodeRtdbIsExist()
{
    sanityCheck(1);
    Aos_WriteLog_D("checkWriteBackCodeRtdbIsExist start!");
    //	if (!Util::connectRtdbDB())
    //        return false;
    std::string source_id;
    //MapStringToPointData_It itr_p;
    //MapStringToMDataValueInfo_It p_itr;
    MapStringToPointGroup_It g_itr;
    MapStringToDataMode_It m_itr;
    MapStringToSysCfg_It sys_itr;
    MapStringToSetCfg_It set_itr;
    SetCfg *setobj;
    SysCfg *sysobj;
    DataMode *model;
    PointGroup *groupobj;
    //DataValueInfo * point;

    set_itr = mMapSetInfo.begin();
    for (;set_itr!=mMapSetInfo.end();++set_itr)
    {
        setobj = set_itr->second;
        setobj->mRtdbSetJkdIsExist = true;

        //        if (!SINGLETON(RtdbAdapter)->RtdbIsExistPoint(setobj->mSetJkd, NOExitSetJkd) ||setobj->mSetJkd.empty())
        //        {
        //            setobj->mRtdbSetJkdIsExist = false;
        //            Aos_Assert_S("*************");
        //            Aos_WriteLog_D(PubOpt::StringOpt::StringFormat("名为:%s的原始值回写点配置错误!", source_id.c_str()).c_str());
        //        }
        setobj->mRtdbSetDfhIsExist = true;

        //        if (!SINGLETON(RtdbAdapter)->RtdbIsExistPoint(setobj->mSetDfh,NOExitSetDfh)||setobj->mSetDfh.empty())
        //        {
        //            setobj->mRtdbSetDfhIsExist = false;
        //        }

        sys_itr = setobj->mMapSys.begin();
        for (;sys_itr!=setobj->mMapSys.end();++sys_itr)
        {
            sysobj =sys_itr->second;
            sysobj->mRtdbSysJkdIsExist = true;
            //            if (!SINGLETON(RtdbAdapter)->RtdbIsExistPoint(sysobj->mSysJkd,NOExitSysJkd)||sysobj->mSysJkd.empty())
            //            {
            //                sysobj->mRtdbSysJkdIsExist = false;
            //            }
            sysobj->mRtdbSysDfhIsExist = true;
            //            if (!SINGLETON(RtdbAdapter)->RtdbIsExistPoint(sysobj->mSysDfh,NOExitSysDfh)||sysobj->mSysDfh.empty())
            //            {
            //                sysobj->mRtdbSysDfhIsExist = false;
            //            }
            m_itr = sysobj->mMapModles.begin();
            for (;m_itr!=sysobj->mMapModles.end();++m_itr)
            {
                model = m_itr->second;
                model->mRtdbSimModleIsWrite = true;
                //                if (!SINGLETON(RtdbAdapter)->RtdbIsExistPoint(model->mSimPoint,NOExitModSim) || model->mSimPoint.empty())
                //                {
                //                    model->mRtdbSimModleIsWrite = false;
                //                }

                model->mRtdbModleConIsWrite = true;
                //                if (!SINGLETON(RtdbAdapter)->RtdbIsExistPoint(model->mCondIdSource,NOExitModCon)||model->mCondIdSource.empty())
                //                {
                //                    model->mRtdbModleConIsWrite = false;
                //                }
                g_itr = model->mMapGroup.begin();

                for (;g_itr!=model->mMapGroup.end();++g_itr)
                {
                    groupobj = g_itr->second;
                    groupobj->mRtdbGroupJkdIsExist = true;
                    //                    if (!SINGLETON(RtdbAdapter)->RtdbIsExistPoint(groupobj->m_GroupJkd,NOExitGroupSim)||groupobj->m_GroupJkd.empty())
                    //                    {
                    //                        groupobj->mRtdbGroupJkdIsExist = false;
                    //                    }
                    checkWritePointRtdbIsExist(groupobj->mMapGroupPoint);
                }

            }
        }
    }

    sanityCheck(2, "checkWriteBackCodeRtdbIsExist cost time: %ld;");
    Aos_WriteLog_D("checkWriteBackCodeRtdbIsExist end!");
    return true;
}




bool
BasicMgr::checkIndexSourceIdRtdbIsExist()
{
    sanityCheck(1);
    Aos_WriteLog_D("checkIndexSourceIdRtdbIsExist start!");
    //	if (!Util::connectRtdbDB())
    //        return false;
    //	std::string source_id;
    //	//MapStringToString_It itr;
    //	MapStringToIndexConfInfo_It itr;
    //	IndexConfigInfo* index_conf_info = NULL;
    //	for (itr  = m_mapIndexConfInfo.begin(); itr != m_mapIndexConfInfo.end();++itr)
    //	{
    //		if (StartupServer::smDestory)  return true;
    //		index_conf_info = itr->second;
    //		if (!index_conf_info->mIsWriteRdtb)
    //			continue;
    //		source_id = index_conf_info->mWriteBackCode;
    //		if(source_id.empty()||""==source_id)
    //		{
    //			Aos_WriteLog_D(PubOpt::StringOpt::StringFormat("指标名为:%s的sourceId为空!", index_conf_info->mIndexCode.c_str()).c_str());
    //			index_conf_info->mIsWriteRdtb = false;
    //			continue;
    //		}
    //		if (!SINGLETON(RtdbAdapter)->RtdbIsExistPoint(source_id,NOExitOrg))
    //		{
    //			Aos_WriteLog_D(PubOpt::StringOpt::StringFormat("指标名为:%s的sourceId 配置错误!", index_conf_info->mIndexCode.c_str()).c_str());
    //			index_conf_info->mIsWriteRdtb = false;
    //		}
    //		/*else
    //		{
    //			mcountPoints++;
    //		}*/
    //	}
    //	sanityCheck(2, "checkIndexSourceIdRtdbIsExist cost time: %ld;");
    //	Aos_WriteLog_D("checkIndexSourceIdRtdbIsExist end!");
    return true;
}

bool
BasicMgr::checkReadSourceIdRtdbIsExist()
{
    sanityCheck(1);
    Aos_WriteLog_D("checkReadSourceIdRtdbIsExist start!");
    //liyg
    //	if (!Util::connectRtdbDB())
    //        return false;
    //	std::string source_id;
    //	MapStringToString_It itr;
    //	for (itr  = mMapPointSourceName.begin(); itr != mMapPointSourceName.end();)
    //	{
    //		if (StartupServer::smDestory)  return true;
    //		source_id = itr->first;
    //		if (!SINGLETON(RtdbAdapter)->RtdbIsExistPoint(source_id,NOExitOrg))
    //		{
    //			Aos_WriteLog_D(PubOpt::StringOpt::StringFormat("指标名为:%s的sourceId 配置错误!", itr->first.c_str()).c_str());
    //			mMapPointSourceName.erase(itr++);
    //		}
    //		else
    //		{
    //			++itr;
    //		}
    //	}
    sanityCheck(2, "checkReadSourceIdRtdbIsExist cost time: %ld;");
    Aos_WriteLog_D("checkReadSourceIdRtdbIsExist end!");
    return true;
}
//void BasicMgr::SetModelPointValues(long &lTimeStamp,const CMonmentDatas* monment,
//								  const int iCount)
//{
//	MapStringToSetCfg_It iter_set;
//	MapStringToSysCfg_It iter_sys;
//	MapStringToDataMode_It iter_m;
//	MapStringToPointGroup_It iter_group;
//	MapStringToPointData_It  iter_allp;
//	MapMonmentPoint_It iter_Mp;
//	SetCfg * setcf;
//	SysCfg * syscf;
//	DataMode * mode_info;
//	PointGroup* model_group;
//
//	std::vector<std::string> lstRet;
//	//MapStringToMDataValueInfo_It d_itr;
//	MapStringToMDataValueInfo_It p_iter;
//
//	std::vector<VarParam>::iterator pcf_iter;
//	bool rslt;
//
//	MapStringToString_It iter = mMapPointSourceName.begin();
//	iter_set = mMapSetInfo.begin();
//	for (;iter_set!=mMapSetInfo.end();++iter_set)
//	{
//		setcf = iter_set->second;
//		iter_sys = setcf->mMapSys.begin();
//		for (;iter_sys!=setcf->mMapSys.end();++iter_sys)
//		{
//			syscf = iter_sys->second;
//
//			iter_m = syscf->mMapModles.begin();
//			for(;iter_m!=syscf->mMapModles.end();++iter_m)
//			{
//				mode_info=iter_m->second;
//				for (iter_Mp = monment->m_mapPointInfo.begin();iter_Mp!=monment->m_mapPointInfo.end();++iter_Mp)
//				{
//					iter_Mp->second->strCode
//					iter = mMapPointSourceName.find(iter_Mp->second->strCode);
//					if (iter == mMapPointSourceName.end()) continue;
//
//					//sanityCheck(2, paTags[i].szName);
//
//					lstRet.clear();
//					rslt = Util::StringSplit(iter->second, lstRet, ",");
//					if(!rslt) continue;
//					for (unsigned int j = 0; j < lstRet.size(); j++)
//					{
//						iter_allp = mMapPointData.find(lstRet[j]);
//						if (iter_allp!=mMapPointData.end())
//						{
//							iter_allp->second->setCurrVar(iter_Mp->second->dValue);
//						}
//						iter_group = mode_info->mMapGroup.begin();
//						for (;iter_group!=mode_info->mMapGroup.end();++iter_group)
//						{
//							model_group = iter_group->second;
//							p_iter = model_group->mMapGroupPoint.find(lstRet[j]);
//							if (p_iter !=  model_group->mMapGroupPoint.end())
//							{
//								p_iter->second->m_IsGetOrigValue  = false;
//								p_iter->second->m_IsGetPreValue = false;
//								p_iter->second->m_IsGetSimValue = false;
//								p_iter->second->setCurrVar(iter_Mp->second->dValue,1);
//								//p_iter->second->mGoodState = paTags[i].lState;
//								//取所有指标最大时间作为服务的当前计算时间
//								//if (lTimeStamp <= monment->lTimeStamp)
//									lTimeStamp = monment->lTimeStamp;
//								break;
//							}
//						}
//					}
//				}
//			}
//
//		}
//	}
//
//}
//bool BasicMgr::CalMonment()
//{
//	MapMonmentDatas_It it_m;
//	CMonmentDatas* monment;
//	it_m = mMapMonment.begin();
//	for (;it_m!=mMapMonment.end();++it_m)
//	{
//		monment = it_m->second;
//	}
//}

void BasicMgr::ClearMapMonmentDatasnop(long strKey)
{
    MapMonmentDatas_It m_iter = mMapMonment.find(strKey);
    if (m_iter!=mMapMonment.end())
    {
        delete m_iter->second;
        mMapMonment.erase(strKey);
    }

}
void BasicMgr::ClearMapMonmentDatas()
{
    MapMonmentDatas_It m_iter = mMapMonment.begin();
    for (;m_iter!=mMapMonment.end();++m_iter)
    {
        delete m_iter->second;
    }
    mMapMonment.clear();
}
bool BasicMgr::loadHisPointData(const long StartTime,const long EndTime)
{
    ClearMapMonmentDatas();
    /*bool rslt = true ;
    if(!SINGLETON(RtdbOpt)->RtdbIsConnect())
    {
        rslt = SINGLETON(RtdbAdapter)->RtdbConnect();
        rslt = SINGLETON(RtdbAdapter)->RtdbIsConnect();
    }
    if(!rslt)
        return false;*/
    //	if (!Util::connectRtdbDB()) return false;
    //	if(!SINGLETON(RtdbOpt)->rtdbGetHisValue(getMapMonment(),StartTime,EndTime,60,getMapPointSourceName()))
    //	{
    //		ClearMapMonmentDatas();
    //		return false;
    //	}
    return true;
}
bool
BasicMgr::rtdbGetRtTagTime(long &lTimeStamp)
{
    if (eFromRtdb==msysType)
    {
        //Aos_Assert_R(SINGLETON(RtdbOpt)->rtdbGetRtTagTime(lTimeStamp,mMapPointSourceName), false);
    }
    return true;
}


bool
BasicMgr::loadPointData(long &lTimeStamp)
{
    pubPointValue->checkModelModifyStatus();

    pubPointValue->loadDB(lTimeStamp, mMapPointSourceName, mMapPointData);
    pubPointValue->SetModelPointValues(mMapSetInfo, mMapPointData);
    return true;
}

void BasicMgr::CheckModelAvgPointFitInfPoint()
{
    MapStringToSetCfg_It iter_set;
    MapStringToSysCfg_It iter_sys;
    DataMode* mode_info;
    ModeMethodAvg* mode_fun;
    MethodAvg* mModeMethodAvg;
    MapStringToDataMode_It iter_m;
    MapStringToModeMethodAvg_It fun_iter;
    MapStringToMethodAvg_It		con_iter;
    MapStringToModeCond_It c_iter;
    MapStringToCondParamCfgs_It  cp_iter;
    SetCfg *setcf;
    SysCfg *syscf;
    std::vector<VarParam>::iterator pcf_iter;
    std::vector<VarParam> tempVec,tempVec2;
    iter_set = mMapSetInfo.begin();
    for (;iter_set!=mMapSetInfo.end();++iter_set)
    {
        setcf = iter_set->second;
        iter_sys = setcf->mMapSys.begin();
        for (;iter_sys!=setcf->mMapSys.end();++iter_sys)
        {
            syscf = iter_sys->second;
            iter_m = syscf->mMapModles.begin();
            for (;iter_m!=syscf->mMapModles.end();++iter_m)
            {
                /*if(iter_m->second->mModeId=="3_qljgw"||iter_m->second->mModeId=="4_zc")
                    int i=100;*/
                mode_info = iter_m->second;
                c_iter = mode_info->mMapModeCond.begin();
                for (;c_iter!=mode_info->mMapModeCond.end();++c_iter)
                {
                    //std::vector<VarParam> varp;
                    tempVec.clear();
                    fun_iter=mMapModeMethodAvg.find(c_iter->second->m_ModelConditionId);
                    if(fun_iter==mMapModeMethodAvg.end())
                    {
                        iter_m->second->m_IsDeal=false;
                        continue;
                    }
                    mode_fun=fun_iter->second;
                    con_iter=mode_fun->mMapmethodavg.find(c_iter->second->m_ModelConditionId);
                    if (con_iter==mode_fun->mMapmethodavg.end())
                    {
                        continue;
                    }
                    mModeMethodAvg = con_iter->second;
                    for (int i=0;i<mModeMethodAvg->mVectorModePoint.size();++i)
                    {
                        for (int j = 0;j<mode_info->mVectorParamCfgs.size();++j)
                        {
                            if (mode_info->mVectorParamCfgs[j].mPoint ==mModeMethodAvg->mVectorModePoint[i])
                            {
                                tempVec.push_back(mode_info->mVectorParamCfgs[j]);
                            }
                        }

                    }
                    mode_info->mMapCondParamCfgs.insert(make_pair(c_iter->second->m_ModelConditionId,tempVec));
                }

            }
        }
    }
}
void BasicMgr::CheckModelAvgPointFitInfPointOnly()
{
    MapStringToSetCfg_It iter_set;
    MapStringToSysCfg_It iter_sys;
    DataMode* mode_info;
    ModeMethodAvg* mode_fun;
    MethodAvg* mModeMethodAvg;
    MapStringToDataMode_It iter_m;
    MapStringToModeMethodAvg_It fun_iter;
    MapStringToMethodAvg_It		con_iter;
    MapStringToModeCond_It c_iter;
    MapStringToCondParamCfgs_It  cp_iter;
    SetCfg *setcf;
    SysCfg *syscf;
    std::vector<VarParam>::iterator pcf_iter;
    std::vector<VarParam> tempVec,tempVec2;
    iter_set = mMapSetInfo.begin();
    for (;iter_set!=mMapSetInfo.end();++iter_set)
    {
        setcf = iter_set->second;
        iter_sys = setcf->mMapSys.begin();
        for (;iter_sys!=setcf->mMapSys.end();++iter_sys)
        {
            syscf = iter_sys->second;
            iter_m = syscf->mMapModles.begin();
            for (;iter_m!=syscf->mMapModles.end();++iter_m)
            {
                if(iter_m->second->mModeId=="ZZ2_3_1gj"||iter_m->second->mModeId=="4_zc")
                    int i=100;
                fun_iter=mMapModeMethodAvg.find(iter_m->second->mModeId);
                if(fun_iter==mMapModeMethodAvg.end())
                {
                    iter_m->second->m_IsDeal=false;
                    continue;
                }
                mode_info=iter_m->second;
                mode_fun=fun_iter->second;
                con_iter=mode_fun->mMapmethodavg.begin();
                for(;con_iter!=mode_fun->mMapmethodavg.end();++con_iter)
                {
                    if (0==con_iter->second->mVectorModePoint.size())
                        continue;
                    mModeMethodAvg = con_iter->second;
                    tempVec2.swap(mode_info->mVectorParamCfgs);
                    for(int i = 0;i < mModeMethodAvg->mVectorModePoint.size();++i)
                    {
                        for(int j = 0;j<tempVec2.size();++j)
                        {
                            if (mModeMethodAvg->mVectorModePoint[i] == tempVec2[j].mPoint)
                            {
                                tempVec.push_back(tempVec2[j]);
                                break;
                            }
                        }
                    }
                    mode_info->mVectorParamCfgs.clear();
                    mode_info->mVectorParamCfgs.swap(tempVec);
                    tempVec2.clear();
                    if (!mModeMethodAvg->mIsOk || mode_info->mVectorParamCfgs.size() != mModeMethodAvg->mVectorModePoint.size())
                    {
                        mode_info->m_IsDeal=false;
                    }
                    break;
                }
            }
        }
    }
}
void BasicMgr::SetAllMothAvgData()
{
    MapStringToSetCfg_It iter_set = mMapSetInfo.begin();
    for (;iter_set!=mMapSetInfo.end();++iter_set)
    {
        SetCfg *setcf = iter_set->second;
        MapStringToSysCfg_It iter_sys = setcf->mMapSys.begin();
        for (;iter_sys != setcf->mMapSys.end(); ++iter_sys)
        {
            SetMothAvgData(iter_sys->second->mMapModles);
        }
    }
}
void
BasicMgr::SetMothAvgData(MapStringToDataMode &mapModeInfo)
{
    MapStringToDataMode_It iter_m=mapModeInfo.begin();
    for (;iter_m!=mapModeInfo.end();++iter_m)
    {
        if((!iter_m->second->m_IsDeal) || iter_m->second->mCondId.empty())
            continue;

        MapStringToModeMethodAvg_It fun_iter=mMapModeMethodAvg.find(iter_m->second->mModeId);
        if(fun_iter==mMapModeMethodAvg.end())
        {
            iter_m->second->m_IsDeal=false;
            continue;
        }

        DataMode* mode_info = iter_m->second;
        ModeMethodAvg* mode_fun = fun_iter->second;
        MapStringToMethodAvg_It con_iter = mode_fun->mMapmethodavg.find(mode_info->mCondId);
        if (con_iter == mode_fun->mMapmethodavg.end())
            continue;

        mode_info->mDModeSim = con_iter->second->mDSimLimit;

        SetFunRtValue(mode_info, con_iter->second);
    }
}

void
BasicMgr::SetFunRtValue(DataMode* mModeInfo, MethodAvg* mModeMethodAvg)
{
    int inum = 0;
    mModeInfo->mVectorPValues.clear();
    for(int i = 0;i < mModeInfo->mVectorParamCfgs.size(); i++)
    {
        for(MapStringToPointGroup_It iter_group = mModeInfo->mMapGroup.begin() ;iter_group!=mModeInfo->mMapGroup.end();++iter_group)
        {
            PointGroup* model_group = iter_group->second;
            MapStringToMDataValueInfo_It point_iter = model_group->mMapGroupPoint.find(mModeInfo->mVectorParamCfgs[i].mPoint);
            if(point_iter!=model_group->mMapGroupPoint.end())
            {
                DataValueInfo* point_info = point_iter->second;
                mModeInfo->mVectorPValues.push_back(point_info->mDOrigValue);
                mModeInfo->mVectorParamCfgs[i].mCurValue = point_info->mDOrigValue;
                //mModeInfo->m_IsDeal = true;
                inum++;
                break;
            }
        }
    }

    if (mModeMethodAvg->mIsOk && inum == mModeMethodAvg->mVectorModePoint.size())
        mModeInfo->m_IsDeal = true;
    else
        mModeInfo->m_IsDeal = false;
}
//void
//RtdbOpt::SetFunRtValue(DataMode* mModeInfo,
//                       MethodAvg* mModeMethodAvg)
//{
//    DataValueInfo* point_info;
//    MapStringToPointData_It p_iter;
//    MapStringToMDataValueInfo_It point_iter;
//	PointGroup* model_group;
//	MapStringToPointGroup_It iter_group;
//	/*std::vector<VarParam>::iterator pcf_iter;
//	for(pcf_iter = mModeInfo->mVectorParamCfgs;pcf_iter!=mModeInfo->mVectorParamCfgs.end();++pcf_iter)
//	{
//		*pcf_iter->mPoint="";
//	}*/
//	mModeInfo->mVectorPValues.clear();
//    for (int i=0;i<mModeMethodAvg->mVectorModePoint.size();++i)
//    {
//		iter_group = mModeInfo->mMapGroup.begin();
//		for (;iter_group!=mModeInfo->mMapGroup.end();++iter_group)
//		{
//			model_group = iter_group->second;
//			point_iter = model_group->mMapGroupPoint.find(mModeMethodAvg->mVectorModePoint[i]);
//			if(point_iter!=model_group->mMapGroupPoint.end())
//			{
//				point_info = point_iter->second;
//				mModeInfo->mVectorPValues.push_back(point_info->mDOrigValue);
//				mModeInfo->mVectorParamCfgs[i].mCurValue = point_info->mDOrigValue;
//				mModeInfo->m_IsDeal = true;
//				break;
//			}
//		}
//    }
//	if (!mModeMethodAvg->mIsOk)
//	{
//		 mModeInfo->m_IsDeal=false;
//	}
//}

//void
//BasicMgr::CalMode()
//{
//    SINGLETON(PointPreCal)->CalculatePre(mMapSetInfo,mMapModeMethodAvg,mMapWrite);
//
//}

char crcTail( char* data, int length )
{
    ///计算检查和
    char cursor = 0;
    for( int i = 0 ; i < length ; i++ )
        cursor += data[i];
    cursor += cursor;
    return cursor;
}

bool
BasicMgr::WriteToRtdb(const long &lCalTimeStamp)
{
    QFile outFile(QString::fromStdString(PubOpt::SystemOpt::GetCurExePath()) + "pubPointValue.csv.tmp");
    if (outFile.open(QIODevice::WriteOnly))
    {
        MapStringToDouble_It it = mMapWrite.begin();
        for(; it != mMapWrite.end(); ++it)
        {
            outFile.write(QString::fromStdString(it->first).toStdString().c_str());
            outFile.write(",");
            outFile.write(QString::number(it->second).toStdString().c_str());
            outFile.write(",");
            outFile.write(QString::number(lCalTimeStamp).toStdString().c_str());
            outFile.write("\n");
        }
    }
    outFile.close();

    if(QFile::exists(QString::fromStdString(PubOpt::SystemOpt::GetCurExePath()) + "pubPointValue.csv"))
        QFile::remove(QString::fromStdString(PubOpt::SystemOpt::GetCurExePath()) + "pubPointValue.csv");
    QFile::rename(QString::fromStdString(PubOpt::SystemOpt::GetCurExePath()) + "pubPointValue.csv.tmp", QString::fromStdString(PubOpt::SystemOpt::GetCurExePath()) + "pubPointValue.csv");
    return true;
}

void
BasicMgr::printMapModeConfInfo()
{
    //MapStringToIndexConfInfo_It itr;
    //for (itr = mMapIndexConfigInfo.begin(); itr != mMapIndexConfigInfo.end(); ++itr)
    //{
    //	Aos_WriteLog_D(itr->second->toString().c_str());
    //}
}



void
BasicMgr::printMapPointSourceName()
{
    MapStringToString_It itr;
    for(itr = mMapPointSourceName.begin(); itr != mMapPointSourceName.end(); ++itr)
    {
        std::string strInfo = PubOpt::StringOpt::StringFormat(
                    "SourceName first:%s, second:%s;",
                    itr->first.c_str(), itr->second.c_str());
        Aos_WriteLog_D(strInfo.c_str());
    }
}

bool
BasicMgr::saveToRdb(const long &lCalTimeStamp)
{
    return true;
}


void
BasicMgr::sanityCheck(const int flag, const std::string &strmsg)
{
    if (!smSanityCheck) return ;
    static long s_time = 0;
    if (flag == 1)
        s_time = Util::getNowTime();
    if (flag == 2)
        Aos_WriteLog(PubOpt::StringOpt::StringFormat(strmsg.c_str(), Util::getNowTime() - s_time).c_str());

}

void
BasicMgr::sanityCheck1(const int flag, const std::string &prefix)
{
    if (!smSanityCheck) return ;
    static long s_time;
    if (flag == 1) s_time = Util::getNowTime();
    if (flag == 2)
        Aos_WriteLog(PubOpt::StringOpt::StringFormat("pretreat%sPoint  cost time: %ld;", prefix.c_str(), Util::getNowTime() - s_time).c_str());

}

void BasicMgr::InsertMapStringToPointData(std::string strPoint,std::string strSouce,std::string strSet,PointType itype,std::string strFullPointId)
{
    DataInfo* point_data;
    MapStringToPointData_It p_iter;
    if (strPoint.empty()) return;
    if(itype==eInvalid)
        int i = 100;
    p_iter = mMapPointData.find(strPoint);
    if (p_iter==mMapPointData.end())
    {
        point_data = new DataInfo();
        mMapPointData.insert(make_pair(strPoint,point_data));
        point_data->mPointId = strPoint;
        point_data->mFullPointId = strFullPointId;
        point_data->mPSource = strSouce;
        point_data->mPointType = itype;
        point_data->mSet = strSet;
        /*if ("M"==strPoint.substr(1)&&eDfhCome==itype)
        {
            point_data->mPointType = eIndex;
        }*/
        point_data->mIsWriteRtdb = true;
        /*if ("D2_zfzqyl"==strPoint)
        {  std::string errmsg;
            Aos_Assert_S("***********************************");
            errmsg = PubOpt::StringOpt::StringFormat("测点：%s 类型：%d",strPoint.c_str(),itype);
            Aos_Assert_S(errmsg.c_str());
        }*/
    }
    else
    {
        p_iter->second->mPointType = itype;
    }

}

void BasicMgr::FhnlToPointData(MapStringToDfhnl& sysMapDfhnl,std::string strSet)
{
    //DataInfo* point_data;
    MapStringToPointData_It point_data_it;
    MapStringToDfhnl_It    p_iter;
    MapStringToString_It	p_it2;
    std::string strCode;
    Dfhnl* dfh;
    for (p_iter = sysMapDfhnl.begin();p_iter!= sysMapDfhnl.end();++p_iter)
    {
        strCode = p_iter->first;
        dfh = p_iter->second;
        mcountPoints++;
        if (5==dfh->m_icategory)
        {
            p_it2=mMapPointSourceName.find(dfh->m_SourceCode);
            if(p_it2==mMapPointSourceName.end())
            {
                mMapPointSourceName.insert(make_pair(dfh->m_SourceCode,dfh->m_code));
            }
            else
            {
                if(std::string::npos!=p_it2->second.find(dfh->m_code))
                    continue;
                if (p_it2->second.substr(p_it2->second.size()-1,1)!=",")
                {
                    p_it2->second += ",";
                }
                p_it2->second += dfh->m_code;
            }
            if("D"==dfh->m_code.substr(0,1))
                InsertMapStringToPointData(dfh->m_code,dfh->m_SourceCode,strSet,eRealTimeOrgDPoint,dfh->m_Fullcode);
            if("M"==dfh->m_code.substr(0,1))
                InsertMapStringToPointData(dfh->m_code,dfh->m_SourceCode,strSet,eIndex,dfh->m_Fullcode);
        }
        else
            InsertMapStringToPointData(dfh->m_code,dfh->m_SourceCode,strSet,eDfhCome);

    }
}
void BasicMgr::ModelFunCheck(VectorString &condtionPoints,MapStringToPointGroup &modelGroups)
{
    MapStringToPointGroup_It g_iter;
    MapStringToMDataValueInfo_It p_iter;
    MapStringToString_It s_itr;
    for(VectorString_It it=condtionPoints.begin();it!=condtionPoints.end();++it)
    {
        std::string str1;
        str1=*it;
        g_iter = modelGroups.begin();
        for (;g_iter !=modelGroups.end();++g_iter)
        {
            PointGroup* pointg = g_iter->second;
            p_iter = pointg->mMapGroupPoint.find(*it);
            if (p_iter != pointg->mMapGroupPoint.end())
            {
                p_iter->second->mRsdbPointIdIsExist=true;
                //s_itr = pPointSourceName.find(*it);
                str1=p_iter->second->mPOrigSource;
                if(p_iter->second->mPOrigSource.empty()) continue;
                s_itr = mMapPointSourceName.find(p_iter->second->mPOrigSource);
                str1=p_iter->second->mPOrigSource;
                if (s_itr == mMapPointSourceName.end())
                {
                    //pPointSourceName.insert(make_pair(*it, p_iter->second->mPointId));
                    mMapPointSourceName.insert(make_pair(p_iter->second->mPOrigSource, p_iter->second->mPointId));
                }
                else
                {
                    if (std::string::npos != s_itr->second.find(p_iter->second->mPointId)) continue;
                    std::string pName = s_itr->second;
                    pName = pName +  ",";
                    pName = pName + p_iter->second->mPointId;
                    s_itr->second = pName;
                }
                break;
            }
        }
    }
}
void
BasicMgr::GetNeedPoint()
{
    std::string strSouce,strCode,strFullPointId;
    SetCfg *  setcf;
    SysCfg *  syscf;
    //ModelCondition* mode_condtion;
    MapStringToSetCfg_It   set_iter;
    MapStringToSysCfg_It   sys_iter;
    //MapStringToString_It p_it1,p_it2;
    MapStringToString_It p_it2;
    MapStringTostrEX_It p_it1;
    DataMode* mode_info;
    PointGroup* group_p;
    DataInfo* point_data;
    DataValueInfo* point_info;
    MapStringToDataMode_It iter;
    MapStringToModeCond_It c_iter;
    MapStringToPointGroup_It g_iter;
    MapStringToPointData_It point_data_it;
    MapStringToMDataValueInfo_It mp_iter;
    MapStringToDataMode_It m_iter;
    MapStringToBool_It ms_iter;
    VectorString_It			cp_iter;
    MapStringToModeMethodAvg_It fun_iter;
    MapStringToMethodAvg_It modCon_iter;
    mcountPoints = 0;
    //int modPointNum = 0;
    GetIndexPoint();
    Aos_WriteLog_D("end GetIndexPoint()");
    for (set_iter = mMapSetInfo.begin();set_iter != mMapSetInfo.end();++set_iter)
    {
        setcf = set_iter->second;
        InsertMapStringToPointData(setcf->mSetJkd,setcf->mSetJkd,setcf->mSetCode,eSim);
        InsertMapStringToPointData(setcf->mSetDfh,setcf->mSetDfh,setcf->mSetCode,eDfh);
        for(sys_iter = setcf->mMapSys.begin();sys_iter!=setcf->mMapSys.end();++sys_iter )
        {
            syscf = sys_iter->second;
            InsertMapStringToPointData(syscf->mSysJkd,setcf->mSetJkd,setcf->mSetCode,eSim);
            InsertMapStringToPointData(syscf->mSysDfh,syscf->mSysDfh,setcf->mSetCode,eDfh);

            FhnlToPointData(syscf->mMapSysDfhnl,setcf->mSetCode);
            m_iter = syscf->mMapModles.begin();
            for (;m_iter!= syscf->mMapModles.end();++m_iter)
            {
                mode_info = m_iter->second;
                /*if(mode_info->mModeId =="ZZ_3_jzjjx")
                    int i = 100;*/
                fun_iter = mMapModeMethodAvg.find(mode_info->mModeId);
                if (fun_iter!=mMapModeMethodAvg.end())
                {
                    ModeMethodAvg* mode_fun = fun_iter->second;
                    modCon_iter = mode_fun->mMapmethodavg.begin();
                    for (;modCon_iter!=mode_fun->mMapmethodavg.end();++modCon_iter)
                    {
                        ModelFunCheck(modCon_iter->second->mVectorModePoint,mode_info->mMapGroup);
                    }

                }
                ms_iter = mMapModleNameStatus.find(mode_info->mModeId);
                if (ms_iter!=mMapModleNameStatus.end())
                {
                    mode_info->m_IsDeal = ms_iter->second;
                }
                InsertMapStringToPointData(mode_info->mSimPoint,mode_info->mSimPoint,setcf->mSetCode,eSim);
                InsertMapStringToPointData(mode_info->mStatus,mode_info->mStatusSource,setcf->mSetCode,eMstatus);
                InsertMapStringToPointData(mode_info->mCondIdSource,mode_info->mCondIdSource,setcf->mSetCode,eMcond);
                g_iter = mode_info->mMapGroup.begin();
                for (;g_iter!=mode_info->mMapGroup.end();++g_iter)
                {
                    group_p = g_iter->second;
                    InsertMapStringToPointData(group_p->m_GroupJkd,group_p->m_GroupJkd,setcf->mSetCode,eSim);
                    mp_iter = group_p->mMapGroupPoint.begin();
                    for (;mp_iter!= group_p->mMapGroupPoint.end();++mp_iter)
                    {
                        point_info = mp_iter->second;
                        if (point_info->mMonitPointId=="D4_MPN04AM")
                            int i =100;
                        //std::cout<<point_info->mPointId<<std::endl;
                        if (point_info->mRtdbPOrigSourceIsExist)
                        {
                            mcountPoints++;
                            //modPointNum++;
                            p_it1= mMapAllPointSourceName.find(point_info->mPointId);
                            if(p_it1!=mMapAllPointSourceName.end())
                            {
                                strFullPointId = p_it1->second.strFullCode;
                            }
                            else
                            {
                                strFullPointId = m_strFactoryCode+"_"+point_info->mPointId;
                            }
                            InsertMapStringToPointData(point_info->mPointId,point_info->mPOrigSource,setcf->mSetCode,eRealTimeOrgDPoint,strFullPointId);
                        }
                        if (point_info->mRtdbPointSourceIsExist)
                        {
                            InsertMapStringToPointData(point_info->mPointSource,point_info->mPointSource,setcf->mSetCode,eRealTimeDPoint);
                        }
                        if (point_info->mRtdbPreSourceIsExist)
                        {
                            InsertMapStringToPointData(point_info->mPreSource,point_info->mPreSource,setcf->mSetCode,ePreDPoint);
                        }
                        if (point_info->mRtdbSimSourceIsExist)
                        {
                            InsertMapStringToPointData(point_info->mSimSource,point_info->mSimSource,setcf->mSetCode,eSimDPoint);
                        }
                        strCode = mp_iter->second->mPointId;
                        if(strCode.empty())
                            continue;
                        strSouce = mp_iter->second->mPOrigSource;
                        p_it2=mMapPointSourceName.find(strSouce);
                        if(p_it2==mMapPointSourceName.end())
                        {
                            mMapPointSourceName.insert(make_pair(strSouce,strCode));
                        }
                        else
                        {
                            /*if(std::string::npos!=p_it2->second.find(strCode))
                                continue;*/
                            if(std::string::npos==p_it2->second.find(strCode))
                            {
                                if (p_it2->second.substr(p_it2->second.size()-1,1)!=",")
                                {
                                    p_it2->second+=",";
                                }
                                p_it2->second+=strCode;
                            }
                        }
                        strCode = mp_iter->second->mMonitPointId;
                        strSouce = mp_iter->second->mPOrigSource;
                        p_it2=mMapPointSourceName.find(strSouce);
                        if(p_it2==mMapPointSourceName.end())
                        {
                            mMapPointSourceName.insert(make_pair(strSouce,strCode));
                        }
                        else
                        {
                            if(std::string::npos==p_it2->second.find(strCode))
                            {
                                if (p_it2->second.substr(p_it2->second.size()-1,1)!=",")
                                {
                                    p_it2->second+=",";
                                }
                                p_it2->second+=strCode;
                            }

                        }
                    }
                }
                if("ZZ2_4_ycfj1bt"==mode_info->mModeId)
                    int ipt =100;
                cp_iter = mode_info->mCondPointVector.begin();
                for (;cp_iter!=mode_info->mCondPointVector.end();++cp_iter)
                {
                    strCode = "";
                    strSouce = "";
                    strCode = *cp_iter;
                    p_it1= mMapAllPointSourceName.find(strCode);
                    if (p_it1!= mMapAllPointSourceName.end())
                    {
                        strSouce = p_it1->second.str1;
                        strFullPointId = p_it1->second.strFullCode;
                        p_it2=mMapPointSourceName.find(strSouce);
                        if(p_it2==mMapPointSourceName.end())
                        {
                            mMapPointSourceName.insert(make_pair(strSouce,strCode));
                        }
                        else
                        {
                            if(std::string::npos!=p_it2->second.find(strCode))
                            {
                                point_data_it = mMapPointData.find(strCode);
                                if (point_data_it==mMapPointData.end())
                                {
                                    mcountPoints++;
                                    point_data= new DataInfo();
                                    mMapPointData.insert(make_pair(strCode,point_data));
                                    point_data->mPointId=strCode;
                                    point_data->mPSource=strSouce;
                                    point_data->mSet = setcf->mSetCode;
                                    point_data->mNotInMedlePoints = true;
                                    if (strCode=="D4_FLN02AM")
                                        int i =100;
                                    if ("D"==strCode.substr(0,1))
                                    {
                                        point_data->mPointType = eRealTimeOrgDPoint;
                                        point_data->mFullPointId = strFullPointId;
                                    }
                                    else if ("M"==strCode.substr(0,1))
                                    {
                                        point_data->mPointType = eIndex;
                                        point_data->mFullPointId = strFullPointId;
                                    }
                                    else
                                    {
                                        point_data->mPointType = eInvalid;
                                    }
                                }

                                if (p_it2->second.substr(p_it2->second.size()-1,1)!=",")
                                {
                                    p_it2->second+=",";
                                }
                                p_it2->second+=strCode;
                                continue;
                            }
                            /*if (p_it2->second.substr(p_it2->second.size()-1,1)!=",")
                            {
                                p_it2->second+=",";
                            }
                            p_it2->second+=strCode;*/
                        }
                    }
                }
            }
        }
    }
    //modPointNum+=1;
    int inum=0;
    for(point_data_it=mMapPointData.begin();point_data_it!=mMapPointData.end();++point_data_it)
    {
        if (eRealTimeOrgDPoint==point_data_it->second->mPointType&&point_data_it->second->mNotInMedlePoints)
        {
            inum++;
            mcountPoints++;
            //std::cout<<point_data_it->second->mPointId<<"机组号："<< point_data_it->second->mSet<<std::endl;
        }
        if (eInvalid==point_data_it->second->mPointType)
            std::cout<<point_data_it->second->mPointId<<"机组号："<< point_data_it->second->mSet<<std::endl;
    }
    mcountPoints += 1;
}

void BasicMgr::GetIndexPoint()
{
    std::string strSouce,strCode;
    MapStringToPointData_It point_data_it;
    DataInfo* point_data;
    MapStringTostrEX_It p_it1;
    MapStringToString_It p_it2;
    int inum=0;
    IndexConfigInfo *index_conf_info = NULL;
    IndexConfigInfo *index_conf_info_f = NULL;
    MapStringToIndexConfInfo_It itr_Index_f;
    MapStringToIndexConfInfo_It itrIndex = m_mapIndexConfInfo.begin();
    for (; itrIndex != m_mapIndexConfInfo.end(); ++itrIndex)
    {
        index_conf_info = itrIndex->second;
        unsigned long size = index_conf_info->mOutFuncVarArray.size();
        for (unsigned long i = 0; i < size; i++)
        {
            strCode = index_conf_info->mOutFuncVarArray[i];
            if (strCode.empty()) continue;
            //if (strCode.substr(0,1) != "D") continue;
            /*if (strCode=="D4_MPN04AM")
                int ipt =100;*/
            point_data_it = mMapPointData.find(strCode);
            if (point_data_it != mMapPointData.end())continue;

            /*point_data = new DataInfo();
            point_data->mPointId = strCode;
            point_data->mPSource = "";
            point_data->mPointType = eRealTimeOrgDPoint;

            mMapPointData.insert(make_pair(strCode,point_data));*/
            if (strCode.substr(0,1)=="D")
            {
                /*if ("D1_tjjyl"==strCode)
                {std::string errmsg;
                    Aos_Assert_S("***********************************");
                    errmsg = PubOpt::StringOpt::StringFormat("测点：%s 类型：%d",strCode.c_str());
                    Aos_Assert_S(errmsg.c_str());
                }*/
                p_it1= mMapAllPointSourceName.find(strCode);
                if (p_it1!= mMapAllPointSourceName.end())
                {
                    mcountPoints++;
                    point_data = new DataInfo();
                    point_data->mPointId = strCode;
                    point_data->mFullPointId = p_it1->second.strFullCode;
                    point_data->mPSource = p_it1->second.str1;
                    point_data->mPointType = eRealTimeOrgDPoint;
                    point_data->mNotInMedlePoints = true;
                    point_data->mSet = p_it1->second.str2;
                    strSouce = p_it1->second.str1;
                    mMapPointData.insert(make_pair(strCode,point_data));

                    p_it2=mMapPointSourceName.find(strSouce);
                    if(p_it2==mMapPointSourceName.end())
                    {
                        mMapPointSourceName.insert(make_pair(strSouce,strCode));
                    }
                    else
                    {
                        if(std::string::npos==p_it2->second.find(strCode))
                        {
                            if (p_it2->second.substr(p_it2->second.size()-1,1)!=",")
                            {
                                p_it2->second+=",";
                            }
                            p_it2->second+=strCode;
                        }
                    }
                }
                else
                {
                    Aos_WriteLog_D(PubOpt::StringOpt::StringFormat("factory: %s point:%s not in tb_pub_point",m_strFactoryCode.c_str(),strCode.c_str()).c_str());
                }
            }
            else if (strCode.substr(0,1)=="M")
            {
                itr_Index_f = m_mapIndexConfInfo.find(strCode);
                if (itr_Index_f==m_mapIndexConfInfo.end())
                {
                    Aos_WriteLog_D(PubOpt::StringOpt::StringFormat("factory: %s point:%s not in tb_index",m_strFactoryCode.c_str(),strCode.c_str()).c_str());
                }
                else
                {
                    point_data = new DataInfo();
                    point_data->mPointId = itr_Index_f->second->mIndexCode;
                    point_data->mFullPointId = itr_Index_f->second->mFullIndexCode;
                    point_data->mPSource = itr_Index_f->second->mWriteBackCode;
                    point_data->mSet = itr_Index_f->second->mSetCode;
                    point_data->mPointType = eIndex;
                    point_data->mNotInMedlePoints = true;
                    mMapPointData.insert(make_pair(strCode,point_data));
                }
            }
        }
    }
}

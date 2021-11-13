#include "AlarmSetDeal.h"
#include "AlarmSetInfo.h"

AlarmSetDeal::AlarmSetDeal(void)
    :
      RDbOperationComplex()
{
    mBufferSize = CON_SET_DEAL_SIZE;
    misFirstCal = true;
    mModConf = true;
    mXsdLimit  = 0;
}
AlarmSetDeal::AlarmSetDeal(RsdbAdapter * QtOpt,std::string strFactory)   
    :
      RDbOperationComplex(QtOpt)
{
    m_strFactoryCode = strFactory;
}
AlarmSetDeal::~AlarmSetDeal(void)
{
}
void 
AlarmSetDeal::SetFirstDev(const bool isFirstCal,const bool isModConf,VectorAlarmScore *AlarmScore,long lCalTimeStamp)
{
    misFirstCal = isFirstCal;
    mModConf = isModConf;
    mVectorAlarmScore = AlarmScore;
    mlCalTimeStamp = lCalTimeStamp;
    if(isFirstCal)
        mXsdLimit = SINGLETON(ServiceEIDSPreConfig)->getXsdLimit();
}

void 
AlarmSetDeal::WriteRsdb()
{
    WriteAlarmPointToRsdb();
    WriteAlarmGroupToRsdb();
    WriteAlarmModeltoSetToRsdb();
    WriteAlarmModelCondtionToRsdb();
    WriteAlarmModelCosineToRsdb();
}
bool AlarmSetDeal::WriteAlarmPointToRsdb()
{
    bool nErr = false;
    ///Util::UtilsanityCheck(1);
    //Aos_WriteLog_D("RsltPointUpValuesRsdb start!");
    nErr = RsltPointUpValuesRsdb();
    /*Util::UtilsanityCheck(2, "RsltPointUpValuesRsdb cost time: %ld;");
    Aos_WriteLog_D("RsltPointUpValuesRsdb end!");*/

    //Util::UtilsanityCheck(1);
    //Aos_WriteLog_D("RsltPointUpFrontInsToRsdb start!");
    nErr = RsltPointUpFrontInsToRsdb();
    //Util::UtilsanityCheck(2, "RsltPointUpFrontInsToRsdb cost time: %ld;");
    //Aos_WriteLog_D("RsltPointUpFrontInsToRsdb end!");

    //qDebug()<<"RsltPointInToRsdb";
    //Util::UtilsanityCheck(1);
    //Aos_WriteLog_D("RsltPointInToRsdb start!");
    nErr = RsltPointInToRsdb();
    //Util::UtilsanityCheck(2, "RsltPointInToRsdb cost time: %ld;");
    //Aos_WriteLog_D("RsltPointInToRsdb end!");

    //qDebug()<<"___-------------RsltPointUpBackInRsdb";
    //Util::UtilsanityCheck(1);
    //Aos_WriteLog_D("RsltPointUpBackInRsdb start!");
    nErr = RsltPointUpBackInRsdb();
    //Util::UtilsanityCheck(2, "RsltPointUpBackInRsdb cost time: %ld;");
    //Aos_WriteLog_D("RsltPointUpBackInRsdb end!");
    return nErr;
}
bool AlarmSetDeal::WriteAlarmGroupToRsdb()
{
    bool nErr = false;

    //Util::UtilsanityCheck(1);
    //Aos_WriteLog_D("RsltGroupUpFrontInsToRsdb start!");
    nErr = RsltGroupUpFrontInsToRsdb();
    //Util::UtilsanityCheck(2, "RsltGroupUpFrontInsToRsdb cost time: %ld;");
    //Aos_WriteLog_D("RsltGroupUpFrontInsToRsdb end!");

    //qDebug()<<"RsltGroupInToRsdb";
    //Util::UtilsanityCheck(1);
    //Aos_WriteLog_D("RsltGroupInToRsdb start!");
    nErr = RsltGroupInToRsdb();
    //Util::UtilsanityCheck(2, "RsltGroupInToRsdb cost time: %ld;");
    //Aos_WriteLog_D("RsltGroupInToRsdb end!");

    //qDebug()<<"RsltGroupUpBackInRsdb";
    //Util::UtilsanityCheck(1);
    //Aos_WriteLog_D("RsltGroupUpBackInRsdb start!");
    nErr = RsltGroupUpBackInRsdb();
    //Util::UtilsanityCheck(2, "RsltGroupUpBackInRsdb cost time: %ld;");
    //Aos_WriteLog_D("RsltGroupUpBackInRsdb end!");
    return nErr;
}
bool AlarmSetDeal::WriteAlarmModeltoSetToRsdb()
{
    bool nErr = false;
    //Util::UtilsanityCheck(1);
    //Aos_WriteLog_D("RsltModelToSetUpFrontInsToRsdb start!");
    nErr = RsltModelToSetUpFrontInsToRsdb();
    //Util::UtilsanityCheck(2, "RsltModelToSetUpFrontInsToRsdb cost time: %ld;");
    //Aos_WriteLog_D("RsltModelToSetUpFrontInsToRsdb end!");

    //qDebug()<<"RsltModelToSetInToRsdb";
    //Util::UtilsanityCheck(1);
    //Aos_WriteLog_D("RsltModelToSetInToRsdb start!");
    nErr = RsltModelToSetInToRsdb();
    //Util::UtilsanityCheck(2, "RsltModelToSetInToRsdb cost time: %ld;");
    //Aos_WriteLog_D("RsltModelToSetInToRsdb end!");

    //qDebug()<<"RsltModelToSetUpBackInRsdb";
    //Util::UtilsanityCheck(1);
    //Aos_WriteLog_D("RsltModelToSetUpBackInRsdb start!");
    nErr = RsltModelToSetUpBackInRsdb();
    //Util::UtilsanityCheck(2, "RsltModelToSetUpBackInRsdb cost time: %ld;");
    //Aos_WriteLog_D("RsltModelToSetUpBackInRsdb end!");

    return nErr;
}
bool AlarmSetDeal::WriteAlarmModelCondtionToRsdb()
{
    bool nErr = false;
    //Aos_WriteLog_D("WriteAlarmModelCondtionToRsdb start!");
    nErr = RsltModelConditionUpFrontInsToRsdb();
    //Aos_WriteLog_D("RsltModelConditionInToRsdb start!");
    nErr = RsltModelConditionInToRsdb();
    //Aos_WriteLog_D("RsltModelConditionUpBackInRsdb start!");
    nErr = RsltModelConditionUpBackInRsdb();
    //Aos_WriteLog_D("WriteAlarmModelCondtionToRsdb end!");
    return nErr;
}

bool AlarmSetDeal::WriteAlarmModelCosineToRsdb()
{
    bool nErr = false;
    //Aos_WriteLog_D("RsltModelCosineInToRsdb start!");
    nErr = RsltModelCosineInToRsdb();
    //Aos_WriteLog_D("RsltModelCosineInToRsdb end!");
    nErr = RsltModelCosineUpBackInRsdb();
    //Aos_WriteLog_D("RsltModelCosineUpBackInRsdb end!");
    return nErr;
}
void AlarmSetDeal::RollbackPoint(int ipos)
{
    MapStringToAlarmPointRst_It it;
    AlarmPointRst * rslt_point = NULL;
    int icount = 0;
    it = mMapAlarmPointRst.begin();
    if (ipos<=CON_RSLT_SIZE)
    {
        for (;it!= mMapAlarmPointRst.end();++it)
        {
            rslt_point = it->second;
            rslt_point ->mDate->m_init = rslt_point->mDate->m_initBack;
            rslt_point->mDate->m_isInto = rslt_point->mDate->m_isIntoBack;
            rslt_point->mDate->m_lastisInto = rslt_point->mDate->m_lastisIntoBack;
            rslt_point->mDate->m_perId = rslt_point->mDate->m_perIdBack;
            rslt_point->mDate->m_perValue = rslt_point->mDate->m_perValueBack;
            rslt_point->mDate->m_perStartTime = rslt_point->mDate->m_perStartTimeBack;
            rslt_point->mDate->m_perEndTime = rslt_point->mDate->m_perEndTimeBack;
        }
    }
    else
    {
        for (;it!= mMapAlarmPointRst.end();++it)
        {
            icount++;
            if (icount>=ipos-CON_RSLT_SIZE&&icount<=ipos)
            {
                rslt_point = it->second;
                rslt_point ->mDate->m_init = rslt_point->mDate->m_initBack;
                rslt_point->mDate->m_isInto = rslt_point->mDate->m_isIntoBack;
                rslt_point->mDate->m_lastisInto = rslt_point->mDate->m_lastisIntoBack;
                rslt_point->mDate->m_perId = rslt_point->mDate->m_perIdBack;
                rslt_point->mDate->m_perValue = rslt_point->mDate->m_perValueBack;
                rslt_point->mDate->m_perStartTime = rslt_point->mDate->m_perStartTimeBack;
                rslt_point->mDate->m_perEndTime = rslt_point->mDate->m_perEndTimeBack;
            }
        }
    }
}
void AlarmSetDeal::RollbackGroup(int ipos)
{
    MapStringToAlarmGrouRst_It it;
    AlarmGrouRst * rslt = NULL;
    int icount = 0;
    it = mMapAlarmGrouRst.begin();
    if (ipos<=CON_RSLT_SIZE)
    {
        for (;it!= mMapAlarmGrouRst.end();++it)
        {
            rslt = it->second;
            rslt ->mDate->m_init = rslt->mDate->m_initBack;
            rslt->mDate->m_isInto = rslt->mDate->m_isIntoBack;
            rslt->mDate->m_lastisInto = rslt->mDate->m_lastisIntoBack;
            rslt->mDate->m_perId = rslt->mDate->m_perIdBack;
            rslt->mDate->m_perValue = rslt->mDate->m_perValueBack;
            rslt->mDate->m_perStartTime = rslt->mDate->m_perStartTimeBack;
            rslt->mDate->m_perEndTime = rslt->mDate->m_perEndTimeBack;
        }
    }
    else
    {
        for (;it!= mMapAlarmGrouRst.end();++it)
        {
            icount++;
            if (icount>=ipos-CON_RSLT_SIZE&&icount<=ipos)
            {
                rslt = it->second;
                rslt ->mDate->m_init = rslt->mDate->m_initBack;
                rslt->mDate->m_isInto = rslt->mDate->m_isIntoBack;
                rslt->mDate->m_lastisInto = rslt->mDate->m_lastisIntoBack;
                rslt->mDate->m_perId = rslt->mDate->m_perIdBack;
                rslt->mDate->m_perValue = rslt->mDate->m_perValueBack;
                rslt->mDate->m_perStartTime = rslt->mDate->m_perStartTimeBack;
                rslt->mDate->m_perEndTime = rslt->mDate->m_perEndTimeBack;
            }
        }
    }
}
void AlarmSetDeal::RollbackCondition(int ipos)
{
    MapStringToAlarmModelConditionRst_It it;
    AlarmModelConditionRst * rslt = NULL;
    int icount = 0;
    it = mMapAlarmModelConditionRst.begin();
    if (ipos<=CON_RSLT_SIZE)
    {
        for (;it!= mMapAlarmModelConditionRst.end();++it)
        {
            rslt = it->second;
            rslt->mCondtionDate->m_isInto = rslt->mCondtionDate->m_isIntoBack;
            rslt->mCondtionDate->m_lastisInto = rslt->mCondtionDate->m_lastisIntoBack;
            rslt->mCondtionDate->m_perId = rslt->mCondtionDate->m_perIdBack;
            rslt->mCondtionDate->m_perValue = rslt->mCondtionDate->m_perValueBack;
            rslt->mCondtionDate->m_perStartTime = rslt->mCondtionDate->m_perStartTimeBack;
            rslt->mCondtionDate->m_perEndTime = rslt->mCondtionDate->m_perEndTimeBack;
        }
    }
    else
    {
        for (;it!= mMapAlarmModelConditionRst.end();++it)
        {
            icount++;
            if (icount>=ipos-CON_RSLT_SIZE&&icount<=ipos)
            {
                rslt = it->second;
                rslt->mCondtionDate->m_isInto = rslt->mCondtionDate->m_isIntoBack;
                rslt->mCondtionDate->m_lastisInto = rslt->mCondtionDate->m_lastisIntoBack;
                rslt->mCondtionDate->m_perId = rslt->mCondtionDate->m_perIdBack;
                rslt->mCondtionDate->m_perValue = rslt->mCondtionDate->m_perValueBack;
                rslt->mCondtionDate->m_perStartTime = rslt->mCondtionDate->m_perStartTimeBack;
                rslt->mCondtionDate->m_perEndTime = rslt->mCondtionDate->m_perEndTimeBack;
            }
        }
    }
}

void AlarmSetDeal::RollbackCosione(int ipos)
{
    MapStringToAlarmModelCosineRst_It it;
    AlarmModelCosineRst * rslt = NULL;
    int icount = 0;
    it = mMapAlarmModelCosineRst.begin();
    if (ipos<=CON_RSLT_SIZE)
    {
        for (;it!= mMapAlarmModelCosineRst.end();++it)
        {
            rslt = it->second;
            rslt->mCosineDate->m_isInto = rslt->mCosineDate->m_isIntoBack;
            rslt->mCosineDate->m_lastisInto = rslt->mCosineDate->m_lastisIntoBack;
            rslt->mCosineDate->m_perId = rslt->mCosineDate->m_perIdBack;
            rslt->mCosineDate->m_perValue = rslt->mCosineDate->m_perValueBack;
            rslt->mCosineDate->m_perStartTime = rslt->mCosineDate->m_perStartTimeBack;
            rslt->mCosineDate->m_perEndTime = rslt->mCosineDate->m_perEndTimeBack;
        }
    }
    else
    {
        for (;it!= mMapAlarmModelCosineRst.end();++it)
        {
            icount++;
            if (icount>=ipos-CON_RSLT_SIZE&&icount<=ipos)
            {
                rslt = it->second;
                rslt->mCosineDate->m_isInto = rslt->mCosineDate->m_isIntoBack;
                rslt->mCosineDate->m_lastisInto = rslt->mCosineDate->m_lastisIntoBack;
                rslt->mCosineDate->m_perId = rslt->mCosineDate->m_perIdBack;
                rslt->mCosineDate->m_perValue = rslt->mCosineDate->m_perValueBack;
                rslt->mCosineDate->m_perStartTime = rslt->mCosineDate->m_perStartTimeBack;
                rslt->mCosineDate->m_perEndTime = rslt->mCosineDate->m_perEndTimeBack;
            }
        }
    }
}

void AlarmSetDeal::RollbackModelToSet(int ipos)
{
    MapStringToAlarmModeltoSetRst_It it;
    AlarmModeltoSetRst * rslt = NULL;
    int icount = 0;
    it = mMapAlarmModeltoSetRst.begin();
    if (ipos<=CON_RSLT_SIZE)
    {
        for (;it!= mMapAlarmModeltoSetRst.end();++it)
        {
            rslt = it->second;
            rslt ->mDate->m_init = rslt->mDate->m_initBack;
            rslt->mDate->m_isInto = rslt->mDate->m_isIntoBack;
            rslt->mDate->m_lastisInto = rslt->mDate->m_lastisIntoBack;
            rslt->mDate->m_perId = rslt->mDate->m_perIdBack;
            rslt->mDate->m_perValue = rslt->mDate->m_perValueBack;
            rslt->mDate->m_perStartTime = rslt->mDate->m_perStartTimeBack;
            rslt->mDate->m_perEndTime = rslt->mDate->m_perEndTimeBack;
        }
    }
    else
    {
        for (;it!= mMapAlarmModeltoSetRst.end();++it)
        {
            icount++;
            if (icount>=ipos-CON_RSLT_SIZE&&icount<=ipos)
            {
                rslt = it->second;
                rslt ->mDate->m_init = rslt->mDate->m_initBack;
                rslt->mDate->m_isInto = rslt->mDate->m_isIntoBack;
                rslt->mDate->m_lastisInto = rslt->mDate->m_lastisIntoBack;
                rslt->mDate->m_perId = rslt->mDate->m_perIdBack;
                rslt->mDate->m_perValue = rslt->mDate->m_perValueBack;
                rslt->mDate->m_perStartTime = rslt->mDate->m_perStartTimeBack;
                rslt->mDate->m_perEndTime = rslt->mDate->m_perEndTimeBack;
            }
        }
    }
}


bool AlarmSetDeal::RsltPointUpFrontInsToRsdb()
{
    bool nErr = true;
    MapStringToAlarmPointRst_It it;
    AlarmPointRst * rslt_point = NULL;
    int icount = 0;
    Aos_Assert_R(Util::QtConnect(mQtOpt), false);
    Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_POINT),false);
    Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_POINT, g_strRsltPointUpFrontInsSQL), false);
    it = mMapAlarmPointRst.begin();
    for (;it!= mMapAlarmPointRst.end();++it)
    {
        rslt_point = it->second;
        if ((rslt_point->mDate->m_curValue ==rslt_point->mDate->m_lastValue
             &&rslt_point->mDate->m_isInto
             &&rslt_point->mDate->m_TimeLong >=rslt_point->mDate->m_deaBand)
                ||(rslt_point->mDate->m_curValue !=rslt_point->mDate->m_lastValue
                   &&rslt_point->mDate->m_lastisInto
                   &&rslt_point->mDate->m_LastTimeLong >=rslt_point->mDate->m_deaBand)||misFirstCal)
        {

            mQtOpt->QtbindValue(0,QString::fromLocal8Bit(rslt_point->mStrModelId.c_str()));

            mQtOpt->QtbindValue(1,QString::fromLocal8Bit(rslt_point->mStrGroupId.c_str()));

            mQtOpt->QtbindValue(2,QString::fromLocal8Bit(rslt_point->mStrPointId.c_str()));

            mQtOpt->QtExec();
            icount++;

            if (CON_RSLT_SIZE==icount)
            {
                nErr = stmtHandSubmit(CON_SET_DEAL_POINT);
                if(!nErr)
                    mQtOpt->QtRollback();
                //mQtOpt->QtQueryClear();
                stmtHandCloseStream(CON_SET_DEAL_POINT);
                Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_POINT),false);
                Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_POINT, g_strRsltPointUpFrontInsSQL), false);

                icount = 0;
            }
        }

    }
    if (0!=icount)
    {
        nErr = stmtHandSubmit(CON_SET_DEAL_POINT);
        if(!nErr)
            stmtTransRollback(CON_SET_DEAL_GROUP);
        icount = 0;
    }
    nErr = stmtHandSubmit(CON_SET_DEAL_POINT);
    stmtHandCloseStream(CON_SET_DEAL_POINT);
    return nErr;
}
bool AlarmSetDeal::UpdateServiceVersion(std::string strServiceName,std::string strVersion,std::string strLog)
{
    char mPszOutputBuff[50] ;
    memset(mPszOutputBuff, 48, 50-1);
    memset(&mPszOutputBuff[49], 0, 1);
    Aos_Assert_R(Util::QtConnect(mQtOpt), false);
    Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_POINT_RT, g_strUpdateServiceVersionSQL), false);
    mQtOpt->QtbindValue(0, QString(strServiceName.c_str()));
    mQtOpt->QtbindValue(1, QString(strVersion.c_str()));
    mQtOpt->QtbindValue(2, QString(strLog.c_str()));
    mQtOpt->QtbindOutValue(3, QString(mPszOutputBuff));
    Aos_Assert_R(mQtOpt->QtExec(), false);

    std::string  strOutput = mQtOpt->GetOutputStrBoundValueByPos(3);
    if (strcmp(strOutput.c_str(), "true") != 0)
    {
        Aos_Assert_S(PubOpt::StringOpt::StringFormat(
                         "P_SYS_Update_VersionNumber SQL ERROR: V_RESULT,%s;",
                         mPszOutputBuff).c_str());
        return false;
    }

    return true;
}
bool AlarmSetDeal::RsltPointRtValuesRsdb(MapStringToSetCfg &mMapSetInfo)
{
    bool nErr = true;
    DataValueInfo * point;
    PointGroup* model_group;
    DataMode* mode_info;
    SysCfg * sysobj;
    SetCfg * setobj;
    MapStringToMDataValueInfo_It iter_p;
    MapStringToPointGroup_It iter_group;
    MapStringToDataMode_It iter_m;
    MapStringToSysCfg_It sys_iter;
    MapStringToSetCfg_It set_iter;

    QVariantList listId,listUptime;
    QVariantList listValue,listPerValue,listSim;

    std::string UpTime;
    int icount = 0;

    UpTime = PubOpt::SystemOpt::DateTmToStr(mlCalTimeStamp, 0);

    for (set_iter = mMapSetInfo.begin();set_iter!=mMapSetInfo.end();++set_iter)
    {
        setobj = set_iter->second;
        sys_iter = setobj->mMapSys.begin();
        for (;sys_iter!=setobj->mMapSys.end();++sys_iter)
        {
            sysobj = sys_iter->second;
            iter_m = sysobj->mMapModles.begin();
            for (;iter_m!=sysobj->mMapModles.end();++iter_m)
            {
                mode_info = iter_m->second;
                iter_group = mode_info->mMapGroup.begin();
                for (;iter_group!= mode_info->mMapGroup.end();++iter_group)
                {
                    model_group = iter_group->second;
                    iter_p = model_group->mMapGroupPoint.begin();
                    for (;iter_p!=model_group->mMapGroupPoint.end();++iter_p)
                    {
                        point = iter_p->second;
                        if (point->m_IsGetOrigValue)
                        {
                            listValue<<point->mDOrigValue;
                            listUptime<<QString(UpTime.c_str());
                            listId<<QString(point->mMonitPointId.c_str());
                            icount++;
                        }
                        else
                        {
                            continue;
                        }
                        if (point->m_IsGetPreValue)
                        {
                            listPerValue<<point->mDPreValue;
                        }
                        else
                        {
                            //listPerValue<<QVariant(QVariant::Double);
                            listPerValue<<0;
                        }
                        if (point->m_IsGetSimValue)
                        {
                            listSim<<point->mDSimValue;
                        }
                        else
                        {
                            //listSim<<QVariant(QVariant::Double);
                            listSim<<0;
                        }
                    }
                }

            }
        }

    }

    for(int i = 0; i < icount; ++i)
    {
        QFile fileHandler(QString::fromStdString( PubOpt::SystemOpt::GetCurExePath()) + "sql.txt.tmp");
        if(fileHandler.open(QIODevice::Append))
        {
            QTextStream stream(&fileHandler);

            QString sqlText = QString::fromStdString(g_strRsltPointRtValuesSQL).arg(listValue.at(i).toDouble()).arg(listPerValue.at(i).toDouble()).arg(listSim.at(i).toDouble()).arg(listUptime.at(i).toString()).arg(listId.at(i).toString());

            stream<<sqlText<<'\n';

            fileHandler.close();
        }
    }
    return nErr;
}
bool AlarmSetDeal::RsltPointGroupRtValuesRsdb(MapStringToSetCfg &mMapSetInfo)
{
    bool nErr = true;

    PointGroup* model_group;
    DataMode* mode_info;
    SysCfg * sysobj;
    SetCfg * setobj;
    MapStringToPointGroup_It iter_group;
    MapStringToDataMode_It iter_m;
    MapStringToSysCfg_It sys_iter;
    MapStringToSetCfg_It set_iter;

    QVariantList listId,listUptime;
    QVariantList listValue;

    std::string UpTime;
    int icount = 0;

    UpTime = PubOpt::SystemOpt::DateTmToStr(mlCalTimeStamp,0);

    for (set_iter = mMapSetInfo.begin();set_iter!=mMapSetInfo.end();++set_iter)
    {
        setobj = set_iter->second;
        sys_iter = setobj->mMapSys.begin();
        for (;sys_iter != setobj->mMapSys.end(); ++sys_iter)
        {
            sysobj = sys_iter->second;
            iter_m = sysobj->mMapModles.begin();
            for (;iter_m != sysobj->mMapModles.end(); ++iter_m)
            {
                mode_info = iter_m->second;
                iter_group = mode_info->mMapGroup.begin();
                for (;iter_group!= mode_info->mMapGroup.end();++iter_group)
                {
                    model_group = iter_group->second;
                    if (!model_group->m_GroupJkd.empty() && mode_info->m_IsCalOk)
                    {
                        listValue<<model_group->m_JkdValue;
                        listUptime<<QString(UpTime.c_str());
                        listId<<QString(model_group->m_Group.c_str());
                        icount++;
                    }
                }

            }
        }
        //listValue<<QVariant(QVariant::Double);
    }

    for(int i = 0; i < icount; ++i)
    {
        QFile fileHandler(QString::fromStdString( PubOpt::SystemOpt::GetCurExePath()) + "sql.txt.tmp");
        if(fileHandler.open(QIODevice::Append))
        {
            QTextStream stream(&fileHandler);

            QString sqlText = QString::fromStdString(g_strRsltGroupRtValuesSQL).arg(listValue.at(i).toDouble()).arg(listUptime.at(i).toString()).arg(listId.at(i).toString());

            stream<<sqlText<<'\n';

            fileHandler.close();
        }
    }

    return nErr;
}
bool AlarmSetDeal::RsltModleRtValuesRsdb(MapStringToSetCfg &mMapSetInfo)
{
    bool nErr = true;
    DataMode* mode_info;
    SysCfg * sysobj;
    SetCfg * setobj;
    MapStringToDataMode_It iter_m;
    MapStringToSysCfg_It sys_iter;
    MapStringToSetCfg_It set_iter;

    QVariantList listId,listUptime;
    QVariantList listValue,listConValue,listFdnlValue;

    std::string UpTime;
    int icount = 0;

    UpTime = PubOpt::SystemOpt::DateTmToStr(mlCalTimeStamp,0);

    for (set_iter = mMapSetInfo.begin();set_iter!=mMapSetInfo.end();++set_iter)
    {
        setobj = set_iter->second;
        if (!setobj->mSetJkd.empty())
        {
            listUptime<<QString(UpTime.c_str());
            listValue<<setobj->mSetJkdValue;
            listFdnlValue<<setobj->mSetDfhValue;
            listId<<QString(setobj->mSet.c_str());
            listConValue<<QVariant(QVariant::Double);
            icount++;
        }
        sys_iter = setobj->mMapSys.begin();
        for (;sys_iter!=setobj->mMapSys.end();++sys_iter)
        {
            sysobj = sys_iter->second;
            if (!sysobj->mSysJkd.empty())
            {
                listUptime<<QString(UpTime.c_str());
                listValue<<sysobj->mSysJkdValue;
                listFdnlValue<<sysobj->mSysDfhValue;
                listId<<QString(sysobj->mSys.c_str());
                listConValue<<QVariant(QVariant::Double);
                icount++;
            }
            iter_m = sysobj->mMapModles.begin();
            for (;iter_m!=sysobj->mMapModles.end();++iter_m)
            {
                mode_info = iter_m->second;
                if (mode_info->m_IsCalOk)
                {
                    listUptime<<QString(UpTime.c_str());
                    listValue<<mode_info->mDModeSim;
                    listFdnlValue<<QVariant(QVariant::Double);
                    listId<<QString(mode_info->mModeId.c_str());
                    listConValue<<mode_info->mCondValue;
                    icount++;
                }
            }
        }
        //listValue<<QVariant(QVariant::Double);
    }

    for(int i = 0; i < icount; ++i)
    {
        QFile fileHandler(QString::fromStdString( PubOpt::SystemOpt::GetCurExePath()) + "sql.txt.tmp");
        if(fileHandler.open(QIODevice::Append))
        {
            QTextStream stream(&fileHandler);

            QString sqlText = QString::fromStdString(g_strRsltModleRtValuesSQL).arg(listUptime.at(i).toString()).arg(listValue.at(i).toDouble()).arg(listFdnlValue.at(i).toDouble()).arg(listConValue.at(i).toDouble()).arg(listId.at(i).toString());

            stream<<sqlText<<'\n';

            fileHandler.close();
        }
    }
    return nErr;
}
bool AlarmSetDeal::RsltIndexRtValuesRsdb(IN MapStringToPointData &mMapPointData,const std::string strFactory)
{
    bool nErr;
    int icount = 0;
    QVariantList listId,listUptime,listUptime_c;
    QVariantList listValue;

    std::string UpTime = PubOpt::SystemOpt::DateTmToStr(mlCalTimeStamp,0);
    std::string UpTime2 = PubOpt::SystemOpt::DateTmToStr(Util::getNowTime());

    MapStringToPointData_It it = mMapPointData.begin();
    for (; it != mMapPointData.end(); ++it)
    {
        DataInfo* objp = it->second;
        if (eIndex != objp->mPointType)
            continue;
        /*std::cout<<objp->mPointId<<std::endl;
        Aos_WriteLog_D(objp->mPointId.c_str());*/

        listUptime<<QString(UpTime.c_str());
        listUptime_c<<QString(UpTime2.c_str());
        listValue<<objp->mDValue;
        //listId<<QString((strFactory+"_"+objp->mPointId).c_str());
        listId<<QString(objp->mFullPointId.c_str());
        icount++;
    }

    for(int i = 0; i < icount; ++i)
    {
        QFile fileHandler(QString::fromStdString( PubOpt::SystemOpt::GetCurExePath()) + "sql.txt.tmp");
        if(fileHandler.open(QIODevice::Append))
        {
            QTextStream stream(&fileHandler);

            QString sqlText = QString::fromStdString(g_strRsltIndexRtValuesSQL).arg(listValue.at(i).toDouble()).arg(listUptime.at(i).toString()).arg(listUptime.at(i).toString()).arg(listId.at(i).toString());

            stream<<sqlText<<'\n';

            fileHandler.close();
        }
    }



    if(QFile::exists(QString::fromStdString( PubOpt::SystemOpt::GetCurExePath()) + "sql.txt"))
        QFile::remove(QString::fromStdString( PubOpt::SystemOpt::GetCurExePath()) + "sql.txt");

    QFile::rename(QString::fromStdString( PubOpt::SystemOpt::GetCurExePath()) + "sql.txt.tmp", QString::fromStdString( PubOpt::SystemOpt::GetCurExePath()) + "sql.txt");

    return nErr;
}
bool AlarmSetDeal::RsltDpointRtValuesRsdb(IN MapStringToPointData &mMapPointData,const std::string strFactory)
{
    bool nErr = true;
    DataInfo* objp;
    MapStringToPointData_It it;
    std::string UpTime,UpTime2;
    int icount = 0;
    QVariantList listId,listUptime;
    QVariantList listValue;


    UpTime = PubOpt::SystemOpt::DateTmToStr(mlCalTimeStamp,0);

    it = mMapPointData.begin();
    for (;it!=mMapPointData.end();++it)
    {
        objp = it->second;
        /*if ("D2_zfzqyl"==objp->mPointId)
        {  std::string errmsg;
            Aos_Assert_S("***********************************");
            errmsg = PubOpt::StringOpt::StringFormat("RsltDpointRtValuesRsdb测点：%s %s 类型：%d，值：%f",objp->mFullPointId.c_str(),objp->mPointId.c_str(),objp->mPointType,objp->mDValue);
            Aos_Assert_S(errmsg.c_str());
        }*/
        //if (eRealTimeOrgDPoint!=objp->mPointType&&eInvalid!=objp->mPointType&&"D"==objp->mPointId.substr(0))
        if (eRealTimeOrgDPoint!=objp->mPointType)
            continue;
        if("D4_FLN02AM"==objp->mPointId||"DDM"==objp->mPointId.substr(3))
            int imo = 100;

        //Aos_WriteLog_D(objp->mPointId);
        //std::cout<<objp->mPointId<<std::endl;
        listUptime<<QString(UpTime.c_str());
        listValue<<objp->mDValue;
        //listId<<QString((strFactory+"_"+objp->mPointId).c_str());
        listId<<QString(objp->mFullPointId.c_str());
        icount++;
    }

    for(int i = 0; i < icount; ++i)
    {
        QFile fileHandler(QString::fromStdString( PubOpt::SystemOpt::GetCurExePath()) + "sql.txt.tmp");
        if(fileHandler.open(QIODevice::Append))
        {
            QTextStream stream(&fileHandler);

            QString sqlText = QString::fromStdString(g_strRsltDpointRtValuesSQL).arg(listUptime.at(i).toString()).arg(listValue.at(i).toDouble()).arg(listId.at(i).toString());

            stream<<sqlText<<'\n';

            fileHandler.close();
        }
    }

    return nErr;
}
void AlarmSetDeal::WriteRsdb(MapStringToSetCfg &mMapSetInfo,MapStringToPointData &mMapPointData,
                             const std::string strFactory,long mCurSeCalTime)
{
    mlCalTimeStamp = mCurSeCalTime;

    RsltPointRtValuesRsdb(mMapSetInfo);
    RsltPointGroupRtValuesRsdb(mMapSetInfo);
    RsltModleRtValuesRsdb(mMapSetInfo);
    RsltDpointRtValuesRsdb(mMapPointData,strFactory);
    RsltIndexRtValuesRsdb(mMapPointData,strFactory);
}

bool AlarmSetDeal::RsltPointUpValuesRsdb()
{
    bool nErr = true;
    MapStringToAlarmPointRst_It it;
    AlarmPointRst * rslt_point = NULL;
    std::string guId;
    QVariantList listCategoryId,listPointId,listUptime;
    QVariantList listValue,listPerValue,listSimValue,listAlarmLevel;

    std::string UpTime;
    std::string maxValue,minValue,avgValue;
    std::string permaxValue,perminValue,peravgValue,avgSimilar;
    int icount = 0,ipos=0;
    Aos_Assert_R(Util::QtConnect(mQtOpt), false);
    Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_POINT),false);
    Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_POINT, g_strRsltPointUpValuesSQL), false);
    it = mMapAlarmPointRst.begin();
    for (;it!= mMapAlarmPointRst.end();++it)
    {
        rslt_point = it->second;
        listAlarmLevel<<rslt_point->mDate->m_curValue;
        UpTime = PubOpt::SystemOpt::DateTmToStr(mlCalTimeStamp,0);
        listUptime<<QString(UpTime.c_str());
        if (rslt_point->mIsGetCurVale)
        {
            listValue<<rslt_point->mDcurValue;

        }
        else
        {
            if (rslt_point->mIsInitCurVale)
            {
                listValue<<rslt_point->mDcurValue;
            }
            else
            {
                listValue<<QVariant(QVariant::Double);
            }
        }
        if (rslt_point->mIsGetPreVale)
        {
            listPerValue<<rslt_point->mDpreValue;
        }
        else
        {
            if (rslt_point->mIsInitPreVale)
            {
                listPerValue<<rslt_point->mDpreValue;

            }
            else
            {
                listPerValue<<QVariant(QVariant::Double);
            }
        }
        if (rslt_point->mIsGetSimVale)
        {
            listSimValue<<rslt_point->mDsim;
        }
        else
        {
            if (rslt_point->mIsInitSimVale)
            {
                listSimValue<<rslt_point->mDsim;
            }
            else
            {
                listSimValue<<QVariant(QVariant::Double);
            }
        }
        listCategoryId<<QString(rslt_point->mStrGroupId.c_str());
        listPointId<<QString(rslt_point->mStrPointId.c_str());

        icount++;
        ipos++;
        /*qDebug()<<QString(rslt_point->mStrPointId.c_str())<<" mDcurValue:"<<rslt_point->mDcurValue
                <<" mDpreValue:"<<rslt_point->mDpreValue
                <<" mDsim:"<<rslt_point->mDsim;*/
        if (CON_RSLT_SIZE==icount)
        {
            mQtOpt->QtbindValue(0,listAlarmLevel);
            mQtOpt->QtbindValue(1,listUptime);
            mQtOpt->QtbindValue(2,listValue);
            mQtOpt->QtbindValue(3,listPerValue);
            mQtOpt->QtbindValue(4,listSimValue);
            mQtOpt->QtbindValue(5,listCategoryId);
            mQtOpt->QtbindValue(6,listPointId);
            if(!mQtOpt->QtExecBatch())
                int i =100;
            nErr = stmtHandSubmit(CON_SET_DEAL_POINT);
            if(!nErr)
            {
                nErr = stmtTransRollback(CON_SET_DEAL_POINT);//回滚数据库记录
            }

            listAlarmLevel.clear();listUptime.clear();
            listValue.clear();listPerValue.clear();
            listSimValue.clear();listCategoryId.clear();
            listPointId.clear();
            Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_POINT),false); //重新打开事务
            icount = 0;
        }
    }
    if (0!=icount)
    {
        mQtOpt->QtbindValue(0,listAlarmLevel);
        mQtOpt->QtbindValue(1,listUptime);
        mQtOpt->QtbindValue(2,listValue);
        mQtOpt->QtbindValue(3,listPerValue);
        mQtOpt->QtbindValue(4,listSimValue);
        mQtOpt->QtbindValue(5,listCategoryId);
        mQtOpt->QtbindValue(6,listPointId);
        mQtOpt->QtExecBatch();
        nErr = stmtHandSubmit(CON_SET_DEAL_POINT);
        if(!nErr)
        {
            nErr = stmtTransRollback(CON_SET_DEAL_POINT);//回滚数据库记录
        }
        icount = 0;
    }
    qDebug()<<"updateValues num"<<ipos;
    return nErr;
}

bool AlarmSetDeal::RsltPointInToRsdb()
{
    bool nErr = false;
    MapStringToAlarmPointRst_It it;
    AlarmPointRst * rslt_point = NULL;
    std::string guId;
    //std::string modelId,conditionId,categoryId,pointId;
    std::string beginTime,endTime,conditionId;
    QVariantList listGuId,listModelId,listConId,listCategoryId,listPointId,listBtime,listEndTime;
    QVariantList listMaxValue,listMinValue,listAvgValue,listPerMaxValue,listPerMinValue,listPerAvgValue;
    QVariantList listAvgSimValue,listAlarmLevel,listAlarmType,listIsHistory;
    //otl_value<otl_datetime> endTime;
    //std::string maxValue,minValue,avgValue;
    //std::string permaxValue,perminValue,peravgValue,avgSimilar;
    int alarmLevel,alarmType,isHistory = 0;
    int icount = 0;
    int ipos = 0,ipos2=0;
    Aos_Assert_R(Util::QtConnect(mQtOpt), false);
    Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_POINT),false);
    if (SQL_SERVERCE==mQtOpt->m_strRsdbType)
    {
        Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_POINT, g_strRsltPointInSQL), false);
    }
    else if (ORACLE==mQtOpt->m_strRsdbType)
    {
        Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_POINT, g_strOrcRsltPointInSQL), false);
    }
    else
    {
        Aos_Assert_S("关系数据库没配对应类型");
        stmtHandCloseStream(CON_SET_DEAL_POINT);
        return false;
    }
    //Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_POINT, g_strRsltPointInSQL), false);
    it = mMapAlarmPointRst.begin();
    for (;it!= mMapAlarmPointRst.end();++it)
    {
        ipos++;
        rslt_point = it->second;

        if ((rslt_point->mDate->m_curValue ==rslt_point->mDate->m_lastValue
             &&rslt_point->mDate->m_isInto
             &&rslt_point->mDate->m_TimeLong >=rslt_point->mDate->m_deaBand)
                ||(rslt_point->mDate->m_curValue !=rslt_point->mDate->m_lastValue
                   &&rslt_point->mDate->m_lastisInto
                   &&rslt_point->mDate->m_LastTimeLong >=rslt_point->mDate->m_deaBand))
        {
            if(rslt_point->mDate->m_curValue ==rslt_point->mDate->m_lastValue
                    &&rslt_point->mDate->m_isInto
                    &&rslt_point->mDate->m_TimeLong >=rslt_point->mDate->m_deaBand)
            {
                guId = rslt_point->mDate->m_id;

                beginTime = PubOpt::SystemOpt::DateTmToStr(rslt_point->mDate->m_StartTime,0);
                endTime = PubOpt::SystemOpt::DateTmToStr(rslt_point->mDate->m_EndTime,0);
                alarmLevel = rslt_point->mDate->m_curValue;
                alarmType = rslt_point->mDate->m_alarmType;
            }
            else
            {
                guId = rslt_point->mDate->m_lastId;
                beginTime = PubOpt::SystemOpt::DateTmToStr(rslt_point->mDate->m_LastStartTime,0);
                endTime = PubOpt::SystemOpt::DateTmToStr(rslt_point->mDate->m_LastEndTime,0);
                alarmLevel = rslt_point->mDate->m_lastValue;
                alarmType = rslt_point->mDate->m_lastAlarmType;
            }
            if(listGuId.contains(QString(guId.c_str())))
                continue;


            listGuId<<QString(guId.c_str());
            listModelId<<QString::fromLocal8Bit(rslt_point->mStrModelId.c_str());
            listCategoryId<<QString::fromLocal8Bit(rslt_point->mStrGroupId.c_str());
            if (rslt_point->mStrCondId.empty())
            {
                listConId<<QVariant(QVariant::String);
            }
            else
                listConId<<(rslt_point->mStrCondId.c_str());


            listPointId<<QString::fromLocal8Bit(rslt_point->mStrPointId.c_str());
            listBtime<<QString(beginTime.c_str());
            listEndTime<<QString(endTime.c_str());
            if (rslt_point->mIsGetCurVale)
            {
                listMaxValue<<rslt_point->m_maxValue;
                listMinValue<<rslt_point->m_minValue;
                listAvgValue<<rslt_point->m_avgValue;

            }
            else
            {
                if (rslt_point->mIsInitCurVale)
                {
                    listMaxValue<<rslt_point->m_maxValue;
                    listMinValue<<rslt_point->m_minValue;
                    listAvgValue<<rslt_point->m_avgValue;
                }
                else
                {
                    listMaxValue<<QVariant(QVariant::Double);
                    listMinValue<<QVariant(QVariant::Double);
                    listAvgValue<<QVariant(QVariant::Double);
                }
            }
            if (rslt_point->mIsGetPreVale)
            {
                listPerMaxValue<<rslt_point->m_pmaxValue;
                listPerMinValue<<rslt_point->m_pminValue;
                listPerAvgValue<<rslt_point->m_pavgValue;
            }
            else
            {
                if (rslt_point->mIsInitPreVale)
                {
                    listPerMaxValue<<rslt_point->m_pmaxValue;
                    listPerMinValue<<rslt_point->m_pminValue;
                    listPerAvgValue<<rslt_point->m_pavgValue;
                }
                else
                {
                    listPerMaxValue<<QVariant(QVariant::Double);
                    listPerMinValue<<QVariant(QVariant::Double);
                    listPerAvgValue<<QVariant(QVariant::Double);
                }
            }
            listAlarmLevel<<alarmLevel;
            listIsHistory<<isHistory;

            if (rslt_point->mIsGetSimVale)
            {
                /*if (rslt_point->mStrPointId=="mmj_4mmjbt_20HFC40CT001"||rslt_point->mStrPointId=="mmj_5mmjbt_20HFC50CT001")
                {
                    Aos_WriteLog((PubOpt::StringOpt::StringFormat("$$1RsltPointInToRsdb 模型：%s 点名：%s guid：%s m_savgValue:%f",
                        rslt_point->mStrModelId.c_str(),rslt_point->mStrPointId.c_str(),guId.c_str(),
                        rslt_point->m_savgValue)).c_str());
                }*/
                listAvgSimValue<<rslt_point->m_savgValue;
            }
            else
            {
                if (rslt_point->mIsInitSimVale)
                {
                    /*if (rslt_point->mStrPointId=="mmj_4mmjbt_20HFC40CT001"||rslt_point->mStrPointId=="mmj_5mmjbt_20HFC50CT001")
                    {
                        Aos_WriteLog((PubOpt::StringOpt::StringFormat("$$12RsltPointInToRsdb 模型：%s 点名：%s guid：%s m_savgValue:%f",
                            rslt_point->mStrModelId.c_str(),rslt_point->mStrPointId.c_str(),guId.c_str(),
                            rslt_point->m_savgValue)).c_str());
                    }*/
                    listAvgSimValue<<rslt_point->m_savgValue;
                }
                else
                {
                    /*if (rslt_point->mStrPointId=="mmj_4mmjbt_20HFC40CT001"||rslt_point->mStrPointId=="mmj_5mmjbt_20HFC50CT001")
                    {
                        Aos_WriteLog((PubOpt::StringOpt::StringFormat("$$13RsltPointInToRsdb 模型：%s 点名：%s guid：%s m_savgValue:%f",
                            rslt_point->mStrModelId.c_str(),rslt_point->mStrPointId.c_str(),guId.c_str(),
                            rslt_point->m_savgValue)).c_str());
                    }*/
                    listAvgSimValue<<QVariant(QVariant::Double);
                }
            }
            //listAvgSimValue<<QVariant(QVariant::Double);
            listAlarmType<<alarmType;
            rslt_point->mDate->m_init = true;

            if(rslt_point->mDate->m_curValue ==rslt_point->mDate->m_lastValue
                    &&rslt_point->mDate->m_isInto
                    &&rslt_point->mDate->m_TimeLong >=rslt_point->mDate->m_deaBand)
            {
                rslt_point->mDate->m_perId = rslt_point->mDate->m_id;  //插入新纪录,上条记录更新
                rslt_point->mDate->m_perValue = rslt_point->mDate->m_curValue;
                rslt_point->mDate->m_perStartTime = rslt_point->mDate->m_StartTime;
                rslt_point->mDate->m_perEndTime = rslt_point->mDate->m_EndTime;
                rslt_point->mDate->m_isInto = false;
            }
            else
            {
                rslt_point->mDate->m_perId = rslt_point->mDate->m_lastId;   //插入新纪录,上条记录更新
                rslt_point->mDate->m_perValue = rslt_point->mDate->m_lastValue;
                rslt_point->mDate->m_perStartTime = rslt_point->mDate->m_LastStartTime;
                rslt_point->mDate->m_perEndTime = rslt_point->mDate->m_LastEndTime;
                rslt_point->mDate->m_lastisInto = false;
            }
            icount++;
            ipos2++;
            if (CON_RSLT_SIZE==icount) //CON_RSLT_SIZE
            {
                mQtOpt->QtbindValue(0,listGuId);
                mQtOpt->QtbindValue(1,listModelId);
                mQtOpt->QtbindValue(2,listCategoryId);
                mQtOpt->QtbindValue(3,listConId);
                mQtOpt->QtbindValue(4,listPointId);
                mQtOpt->QtbindValue(5,listBtime);
                mQtOpt->QtbindValue(6,listEndTime);
                mQtOpt->QtbindValue(7,listMaxValue);
                mQtOpt->QtbindValue(8,listMinValue);
                mQtOpt->QtbindValue(9,listAvgValue);
                mQtOpt->QtbindValue(10,listPerMaxValue);
                mQtOpt->QtbindValue(11,listPerMinValue);
                mQtOpt->QtbindValue(12,listPerAvgValue);
                mQtOpt->QtbindValue(13,listAlarmLevel);
                mQtOpt->QtbindValue(14,listIsHistory);
                mQtOpt->QtbindValue(15,listAvgSimValue);
                mQtOpt->QtbindValue(16,listAlarmType);

                //qDebug()<<"_____________________________________________"<<ipos2;
                //qDebug()<<"&&&&&&&&&&&&&&&&&&&&&&&&&&$$$$$$$$$$$$$$$$$$"<<ipos2;

                //Aos_WriteLog_D("2000RsltModelToSetInToRsdb start &&&&&&&&&&&&&&&&&&&&&&&&&&$$$$$$$$$$$$$$$$$$!");
                //Aos_WriteLog_D(guId.c_str());Aos_WriteLog_D(rslt_point->mStrModelId.c_str());Aos_WriteLog_D(rslt_point->mStrGroupId.c_str());
                //Aos_WriteLog_D(rslt_point->mStrPointId.c_str());Aos_WriteLog_D(beginTime.c_str());Aos_WriteLog_D(endTime.c_str());
                icount = 0;
                nErr = mQtOpt->QtExecBatch();
                if(!nErr)
                {
                    //qDebug()<<mQtOpt->m_query->lastError();
                    Aos_WriteLog_D("2000QtExecBatch err!");
                    Aos_WriteLog_D(rslt_point->mStrPointId.c_str());
                    Aos_WriteLog_D(mQtOpt->m_strErrorMessage.c_str());
                }
                nErr = stmtHandSubmit(CON_SET_DEAL_POINT);
                if(!nErr)
                {
                    Aos_WriteLog_D("2000RsltPointInToRsdb err!");
                    /*Aos_WriteLog_D(guId.c_str());Aos_WriteLog_D(rslt_point->mStrModelId.c_str());
                    Aos_WriteLog_D(rslt_point->mStrGroupId.c_str());
                    Aos_WriteLog_D(rslt_point->mStrPointId.c_str());
                    Aos_WriteLog_D(beginTime.c_str());
                    Aos_WriteLog_D(endTime.c_str());*/
                    //回滚内存记录
                    nErr = stmtTransRollback(CON_SET_DEAL_POINT);//回滚数据库记录
                }
                /*qDebug()<<listGuId[0];
                qDebug()<<listModelId[0];qDebug()<<listCategoryId[0];qDebug()<<listConId[0];
                qDebug()<<listPointId[0];qDebug()<<listBtime[0];qDebug()<<listEndTime[0];
                qDebug()<<listMaxValue[0];qDebug()<<listMinValue[0];qDebug()<<listAvgValue[0];
                qDebug()<<listPerMaxValue[0];qDebug()<<listPerMinValue[0];qDebug()<<listPerAvgValue[0];
                qDebug()<<listAlarmLevel[0];qDebug()<<listIsHistory[0];qDebug()<<listAvgSimValue[0];
                qDebug()<<listAlarmType[0];*/
                stmtHandCloseStream(CON_SET_DEAL_POINT);
                Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_POINT),false);
                if (SQL_SERVERCE==mQtOpt->m_strRsdbType)
                {
                    Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_POINT, g_strRsltPointInSQL), false);
                }
                else if (ORACLE==mQtOpt->m_strRsdbType)
                {
                    Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_POINT, g_strOrcRsltPointInSQL), false);
                }
                else
                {
                    Aos_Assert_S("关系数据库没配对应类型");
                    stmtHandCloseStream(CON_SET_DEAL_POINT);
                    return false;
                }
                listGuId.clear(); listModelId.clear();
                listCategoryId.clear();listConId.clear();
                listPointId.clear();listBtime.clear();
                listEndTime.clear();listMaxValue.clear();
                listMinValue.clear();listAvgValue.clear();
                listPerMaxValue.clear();listPerMinValue.clear();
                listPerAvgValue.clear();listAlarmLevel.clear();
                listIsHistory.clear();listAvgSimValue.clear();
                listAlarmType.clear();
                //mQtOpt->QtQueryClear();
                Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_POINT),false); //重新打开事务
                icount = 0;
            }
        }
    }
    if (0!=icount)
    {
        mQtOpt->QtbindValue(0,listGuId);
        mQtOpt->QtbindValue(1,listModelId);
        mQtOpt->QtbindValue(2,listCategoryId);
        mQtOpt->QtbindValue(3,listConId);
        mQtOpt->QtbindValue(4,listPointId);
        mQtOpt->QtbindValue(5,listBtime);
        mQtOpt->QtbindValue(6,listEndTime);
        mQtOpt->QtbindValue(7,listMaxValue);
        mQtOpt->QtbindValue(8,listMinValue);
        mQtOpt->QtbindValue(9,listAvgValue);
        mQtOpt->QtbindValue(10,listPerMaxValue);
        mQtOpt->QtbindValue(11,listPerMinValue);
        mQtOpt->QtbindValue(12,listPerAvgValue);
        mQtOpt->QtbindValue(13,listAlarmLevel);
        mQtOpt->QtbindValue(14,listIsHistory);
        mQtOpt->QtbindValue(15,listAvgSimValue);
        mQtOpt->QtbindValue(16,listAlarmType);

        //qDebug()<<"_____________________________________________"<<ipos2;
        //qDebug()<<"&&&&&&&&&&&&&&&&&&&&&&&&&&$$$$$$$$$$$$$$$$$$"<<ipos2;
        //Aos_WriteLog_D("RsltModelToSetInToRsdb start &&&&&&&&&&&&&&&&&&&&&&&&&&$$$$$$$$$$$$$$$$$$!");
        nErr = mQtOpt->QtExecBatch();

        if(!nErr)
        {
            Aos_WriteLog_D("tExecBatch err!");
            Aos_WriteLog_D(rslt_point->mStrPointId.c_str());
            Aos_WriteLog_D(mQtOpt->m_strErrorMessage.c_str());
        }
        nErr = stmtHandSubmit(CON_SET_DEAL_POINT);
        if(!nErr)
        {
            Aos_WriteLog_D("RsltPointInToRsdb err!");
            RollbackPoint(ipos);   //回滚内存记录
            nErr = stmtTransRollback(CON_SET_DEAL_POINT);//回滚数据库记录
        }
        stmtHandCloseStream(CON_SET_DEAL_POINT);
        icount = 0;
    }
    nErr = stmtHandSubmit(CON_SET_DEAL_POINT);
    stmtHandCloseStream(CON_SET_DEAL_POINT);
    //qDebug()<<"insert num"<<ipos2;
    return nErr;
}
//bool AlarmSetDeal::RsltPointInToRsdb()
//{
//	bool nErr = true;
//	MapStringToAlarmPointRst_It it;
//	AlarmPointRst * rslt_point = NULL;
//	std::string guId,modelId,conditionId,categoryId,pointId;
//	std::string beginTime,endTime;
//	//otl_value<otl_datetime> endTime;
//	std::string maxValue,minValue,avgValue;
//	std::string permaxValue,perminValue,peravgValue,avgSimilar;
//	int alarmLevel,alarmType,isHistory = 0;
//	int icount = 0;
//	int ipos = 0,ipos2 = 0;
//	Aos_Assert_R(Util::QtConnect(mQtOpt), false);
//	Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_POINT),false);
//	//Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_POINT, g_strRsltPointInSQL), false);
//	it = mMapAlarmPointRst.begin();
//	for (;it!= mMapAlarmPointRst.end();++it)
//	{
//		ipos++;
//		QString SQL = QString::fromStdString(g_strRsltPointInSQL);
//		rslt_point = it->second;
//		if("3_1gj"==rslt_point->mStrModelId)
//			int i = 100;
//		if (rslt_point->mStrPointId=="gjcyxt_1gj_D3_3AIFB07")
//			int i =100;
//		if ((rslt_point->mDate->m_curValue ==rslt_point->mDate->m_lastValue
//			&&rslt_point->mDate->m_isInto
//			&&rslt_point->mDate->m_TimeLong >=rslt_point->mDate->m_deaBand)
//			||(rslt_point->mDate->m_curValue !=rslt_point->mDate->m_lastValue
//			&&rslt_point->mDate->m_lastisInto
//			&&rslt_point->mDate->m_LastTimeLong >=rslt_point->mDate->m_deaBand))
//		{
//			if (rslt_point->mStrCondId.empty())
//			{
//				rslt_point->mStrCondId = "null";
//			}
//			else
//				rslt_point->mStrCondId = "'"+rslt_point->mStrCondId+"'";
//			if(rslt_point->mDate->m_curValue ==rslt_point->mDate->m_lastValue
//				&&rslt_point->mDate->m_isInto
//				&&rslt_point->mDate->m_TimeLong >=rslt_point->mDate->m_deaBand)
//			{
//				guId = rslt_point->mDate->m_id;
//				
//				beginTime = PubOpt::SystemOpt::DateTmToStr(rslt_point->mDate->m_StartTime,0);
//				endTime = PubOpt::SystemOpt::DateTmToStr(rslt_point->mDate->m_EndTime,0);
//				alarmLevel = rslt_point->mDate->m_curValue;
//				alarmType = rslt_point->mDate->m_alarmType;
//			}
//			else 
//			{
//				guId = rslt_point->mDate->m_lastId;
//				beginTime = PubOpt::SystemOpt::DateTmToStr(rslt_point->mDate->m_LastStartTime,0);
//				endTime = PubOpt::SystemOpt::DateTmToStr(rslt_point->mDate->m_LastEndTime,0);
//				alarmLevel = rslt_point->mDate->m_lastValue;
//				alarmType = rslt_point->mDate->m_lastAlarmType;
//			}
//
//			if (rslt_point->mIsGetCurVale)
//			{
//				maxValue = Util::Number2String(rslt_point->m_maxValue);
//				minValue = Util::Number2String(rslt_point->m_minValue);
//				avgValue = Util::Number2String(rslt_point->m_avgValue);
//
//			}
//			else
//			{
//				if (rslt_point->mIsInitCurVale)
//				{
//					maxValue = Util::Number2String(rslt_point->m_maxValue);
//					minValue = Util::Number2String(rslt_point->m_minValue);
//					avgValue = Util::Number2String(rslt_point->m_avgValue);
//				}
//				else
//				{
//					maxValue = "null";
//					minValue = "null";
//					avgValue = "null";
//				}
//				//continue;
//			}
//			if (rslt_point->mIsGetPreVale)
//			{
//				permaxValue = Util::Number2String(rslt_point->m_pmaxValue);
//				perminValue = Util::Number2String(rslt_point->m_pminValue);
//				peravgValue = Util::Number2String(rslt_point->m_pavgValue);
//			}
//			else
//			{
//				if (rslt_point->mIsInitPreVale)
//				{
//					permaxValue = Util::Number2String(rslt_point->m_pmaxValue);
//					perminValue = Util::Number2String(rslt_point->m_pminValue);
//					peravgValue = Util::Number2String(rslt_point->m_pavgValue);
//				}
//				else
//				{
//					permaxValue = "null";
//					perminValue = "null";
//					peravgValue = "null";
//				}
//			}
//			if (rslt_point->mIsGetSimVale)
//			{
//				avgSimilar = Util::Number2String(rslt_point->m_savgValue);
//			} 
//			else
//			{
//				if (rslt_point->mIsInitSimVale)
//				{
//					avgSimilar = Util::Number2String(rslt_point->m_savgValue);
//				}
//				else
//				{
//					avgSimilar = "null";
//				}
//			}
//			rslt_point->mDate->m_init = true;
//			SQL = SQL.arg(QString::fromStdString(guId))
//				.arg(QString::fromStdString(rslt_point->mStrModelId))
//				.arg(QString::fromStdString(rslt_point->mStrGroupId))
//				.arg(QString::fromStdString(rslt_point->mStrCondId))
//				.arg(QString::fromStdString(rslt_point->mStrPointId))
//				.arg(QString::fromStdString(beginTime))
//				.arg(QString::fromStdString(endTime))
//				.arg(QString::fromStdString(maxValue))
//				.arg(QString::fromStdString(minValue))
//				.arg(QString::fromStdString(avgValue))
//				.arg(QString::fromStdString(permaxValue))
//				.arg(QString::fromStdString(perminValue))
//				.arg(QString::fromStdString(peravgValue))
//				.arg(alarmLevel)
//				.arg(isHistory)
//				.arg(QString::fromStdString(avgSimilar))
//				.arg(alarmType);
//			mQtOpt->QtQueryPrepare(SQL);
//			qDebug()<<SQL;
//			//mQtOpt->QtExec();
//			if (!mQtOpt->QtExec())
//			{
//				std::string strtemp = mQtOpt->QtErr();
//				Aos_Assert_S(strtemp.c_str());
//			}
//			if(rslt_point->mDate->m_curValue ==rslt_point->mDate->m_lastValue
//				&&rslt_point->mDate->m_isInto
//				&&rslt_point->mDate->m_TimeLong >=rslt_point->mDate->m_deaBand)
//			{
//				rslt_point->mDate->m_perId = rslt_point->mDate->m_id;  //插入新纪录,上条记录更新
//				rslt_point->mDate->m_perValue = rslt_point->mDate->m_curValue;
//				rslt_point->mDate->m_perStartTime = rslt_point->mDate->m_StartTime;
//				rslt_point->mDate->m_perEndTime = rslt_point->mDate->m_EndTime;
//				rslt_point->mDate->m_isInto = false;
//			}
//			else
//			{
//				rslt_point->mDate->m_perId = rslt_point->mDate->m_lastId;   //插入新纪录,上条记录更新
//				rslt_point->mDate->m_perValue = rslt_point->mDate->m_lastValue;
//				rslt_point->mDate->m_perStartTime = rslt_point->mDate->m_LastStartTime;
//				rslt_point->mDate->m_perEndTime = rslt_point->mDate->m_LastEndTime;
//				rslt_point->mDate->m_lastisInto = false;
//			}
//			icount++;
//			ipos2++;
//			if (CON_RSLT_SIZE==icount)
//			{
//				nErr = stmtHandSubmit(CON_SET_DEAL_POINT);
//				if(!nErr)
//					RollbackPoint(ipos);   //回滚内存记录
//				Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_POINT),false);
//				icount = 0;
//			}
//		}
//	}
//	if (0!=icount)
//	{
//		nErr = stmtHandSubmit(CON_SET_DEAL_POINT);
//		if(!nErr)
//		{
//			RollbackPoint(ipos);  //回滚内存记录
//			stmtTransRollback(CON_SET_DEAL_POINT);
//		}
//		icount = 0;
//	}
//	qDebug()<<"insert num"<<ipos2;
//	//nErr = stmtHandCloseStream(CON_SET_DEAL_POINT);
//	return nErr;
//}
bool AlarmSetDeal::RsltPointUpBackInRsdb()
{
    bool nErr = true;
    MapStringToAlarmPointRst_It it;
    AlarmPointRst * rslt_point = NULL;
    std::string guId;
    QVariantList listGuId,listModelId,listConId,listCategoryId,listPointId,listBtime,listEndTime;
    QVariantList listMaxValue,listMinValue,listAvgValue,listPerMaxValue,listPerMinValue,listPerAvgValue;
    QVariantList listAvgSimValue,listAlarmLevel,listAlarmType,listIsHistory;
    std::string endTime;
    std::string maxValue,minValue,avgValue;
    std::string permaxValue,perminValue,peravgValue,avgSimilar;
    int icount = 0,ipos=0;
    Aos_Assert_R(Util::QtConnect(mQtOpt), false);
    Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_POINT),false);
    //Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_POINT, g_strRsltPointUpBackInSQL), false);
    if (SQL_SERVERCE==mQtOpt->m_strRsdbType)
    {
        Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_POINT, g_strRsltPointUpBackInSQL), false);
    }
    else if (ORACLE==mQtOpt->m_strRsdbType)
    {
        Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_POINT, g_strOrcRsltPointUpBackInSQL), false);
    }
    else
    {
        Aos_Assert_S("关系数据库没配对应类型");
        stmtHandCloseStream(CON_SET_DEAL_POINT);
        return false;
    }
    it = mMapAlarmPointRst.begin();
    for (;it!= mMapAlarmPointRst.end();++it)
    {
        //QString SQL = QString(g_strRsltPointUpBackInSQL.c_str());
        rslt_point = it->second;
        /*if("4_zc"!=rslt_point->mStrModelId)
            continue;*/
        if ((rslt_point->mDate->m_curValue ==rslt_point->mDate->m_lastValue
             &&!(rslt_point->mDate->m_isInto)
             &&rslt_point->mDate->m_TimeLong >=rslt_point->mDate->m_deaBand)
                ||(rslt_point->mDate->m_curValue !=rslt_point->mDate->m_lastValue
                   &&rslt_point->mDate->m_LastTimeLong <rslt_point->mDate->m_deaBand)
                ||(rslt_point->mDate->m_curValue !=rslt_point->mDate->m_lastValue
                   &&rslt_point->mDate->m_LastTimeLong >=rslt_point->mDate->m_deaBand)
                &&(!rslt_point->mDate->m_lastisInto))
        {


            if(rslt_point->mDate->m_curValue ==rslt_point->mDate->m_lastValue
                    &&!rslt_point->mDate->m_isInto
                    &&rslt_point->mDate->m_TimeLong >=rslt_point->mDate->m_deaBand)
            {
                guId = rslt_point->mDate->m_id;
                endTime = PubOpt::SystemOpt::DateTmToStr(rslt_point->mDate->m_EndTime,0);
                //SetOtlDatetime(endTime,rslt_point->mDate->m_EndTime);

            }
            else if ((rslt_point->mDate->m_curValue !=rslt_point->mDate->m_lastValue
                      &&rslt_point->mDate->m_LastTimeLong <rslt_point->mDate->m_deaBand))
            {
                guId = rslt_point->mDate->m_perId;
                endTime = PubOpt::SystemOpt::DateTmToStr(rslt_point->mDate->m_EndTime,0);
                if (rslt_point->mDate->m_curValue==rslt_point->mDate->m_perValue)
                {
                    rslt_point->mDate->m_id = rslt_point->mDate->m_perId;
                    rslt_point->mDate->m_isInto=false;
                }
            }
            else if (rslt_point->mDate->m_curValue !=rslt_point->mDate->m_lastValue
                     &&rslt_point->mDate->m_LastTimeLong >=rslt_point->mDate->m_deaBand
                     &&(!rslt_point->mDate->m_lastisInto))
            {
                guId = rslt_point->mDate->m_perId;
                endTime = PubOpt::SystemOpt::DateTmToStr(rslt_point->mDate->m_LastEndTime,0);
            }
            if(guId.empty()) continue;


            listEndTime<<QString(endTime.c_str());
            if (rslt_point->mIsGetCurVale)
            {
                listMaxValue<<rslt_point->m_maxValue;
                listMinValue<<rslt_point->m_minValue;
                listAvgValue<<rslt_point->m_avgValue;

            }
            else
            {
                if (rslt_point->mIsInitCurVale)
                {
                    listMaxValue<<rslt_point->m_maxValue;
                    listMinValue<<rslt_point->m_minValue;
                    listAvgValue<<rslt_point->m_avgValue;
                }
                else
                {
                    listMaxValue<<QVariant(QVariant::Double);
                    listMinValue<<QVariant(QVariant::Double);
                    listAvgValue<<QVariant(QVariant::Double);
                }
            }
            if (rslt_point->mIsGetPreVale)
            {
                listPerMaxValue<<rslt_point->m_pmaxValue;
                listPerMinValue<<rslt_point->m_pminValue;
                listPerAvgValue<<rslt_point->m_pavgValue;
            }
            else
            {
                if (rslt_point->mIsInitPreVale)
                {
                    listPerMaxValue<<rslt_point->m_pmaxValue;
                    listPerMinValue<<rslt_point->m_pminValue;
                    listPerAvgValue<<rslt_point->m_pavgValue;
                }
                else
                {
                    listPerMaxValue<<QVariant(QVariant::Double);
                    listPerMinValue<<QVariant(QVariant::Double);
                    listPerAvgValue<<QVariant(QVariant::Double);
                }
            }
            if (rslt_point->mIsGetSimVale)
            {
                listAvgSimValue<<rslt_point->m_savgValue;
            }
            else
            {
                if (rslt_point->mIsInitSimVale)
                {
                    listAvgSimValue<<rslt_point->m_savgValue;
                }
                else
                {
                    listAvgSimValue<<QVariant(QVariant::Double);
                }
            }
            listGuId<<QString(guId.c_str());

            icount++;
            ipos++;
            if (CON_RSLT_SIZE==icount)
            {
                //Aos_WriteLog_D("2000RsltPointUpBackInRsdb QtExecBatch!");
                mQtOpt->QtbindValue(0,listEndTime);
                mQtOpt->QtbindValue(1,listMaxValue);
                mQtOpt->QtbindValue(2,listMinValue);
                mQtOpt->QtbindValue(3,listAvgValue);
                mQtOpt->QtbindValue(4,listPerMaxValue);
                mQtOpt->QtbindValue(5,listPerMinValue);
                mQtOpt->QtbindValue(6,listPerAvgValue);
                mQtOpt->QtbindValue(7,listAvgSimValue);
                mQtOpt->QtbindValue(8,listGuId);
                mQtOpt->QtExecBatch();
                nErr = stmtHandSubmit(CON_SET_DEAL_POINT);
                if(!nErr)
                {
                    Aos_WriteLog_D("2000RsltPointUpBackInRsdb err!");
                    nErr = stmtTransRollback(CON_SET_DEAL_POINT);//回滚数据库记录
                }
                stmtHandCloseStream(CON_SET_DEAL_POINT);
                Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_POINT),false); //重新打开事务
                if (SQL_SERVERCE==mQtOpt->m_strRsdbType)
                {
                    Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_POINT, g_strRsltPointUpBackInSQL), false);
                }
                else if (ORACLE==mQtOpt->m_strRsdbType)
                {
                    Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_POINT, g_strOrcRsltPointUpBackInSQL), false);
                }
                else
                {
                    Aos_Assert_S("关系数据库没配对应类型");
                    stmtHandCloseStream(CON_SET_DEAL_POINT);
                    return false;
                }
                listEndTime.clear();listMaxValue.clear();
                listMinValue.clear();listAvgValue.clear();
                listPerMaxValue.clear();listPerMinValue.clear();
                listPerAvgValue.clear();listAvgSimValue.clear();
                listGuId.clear();
                icount = 0;
            }
        }
    }
    if (0!=icount)
    {
        //Aos_WriteLog_D("RsltPointUpBackInRsdb QtExecBatch!");
        mQtOpt->QtbindValue(0,listEndTime);
        mQtOpt->QtbindValue(1,listMaxValue);
        mQtOpt->QtbindValue(2,listMinValue);
        mQtOpt->QtbindValue(3,listAvgValue);
        mQtOpt->QtbindValue(4,listPerMaxValue);
        mQtOpt->QtbindValue(5,listPerMinValue);
        mQtOpt->QtbindValue(6,listPerAvgValue);
        mQtOpt->QtbindValue(7,listAvgSimValue);
        mQtOpt->QtbindValue(8,listGuId);
        mQtOpt->QtExecBatch();
        nErr = stmtHandSubmit(CON_SET_DEAL_POINT);
        if(!nErr)
        {
            Aos_WriteLog_D("RsltPointUpBackInRsdb err!");
            nErr = stmtTransRollback(CON_SET_DEAL_POINT);//回滚数据库记录
        }
        stmtHandCloseStream(CON_SET_DEAL_POINT);
        icount = 0;
    }
    nErr = stmtHandSubmit(CON_SET_DEAL_POINT);
    stmtHandCloseStream(CON_SET_DEAL_POINT);
    //qDebug()<<"update num"<<ipos;
    return nErr;
}

//bool AlarmSetDeal::RsltPointUpBackInRsdb()
//{
//	bool nErr = true;
//	MapStringToAlarmPointRst_It it;
//	AlarmPointRst * rslt_point = NULL;
//	std::string guId;
//
//	std::string endTime;
//	std::string maxValue,minValue,avgValue;
//	std::string permaxValue,perminValue,peravgValue,avgSimilar;
//	int icount = 0,ipos=0;
//	Aos_Assert_R(Util::QtConnect(mQtOpt), false);
//	Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_POINT),false);
//	//Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_POINT, g_strRsltPointUpBackInSQL), false);
//	it = mMapAlarmPointRst.begin();
//	for (;it!= mMapAlarmPointRst.end();++it)
//	{
//		QString SQL = QString::fromStdString(g_strRsltPointUpBackInSQL);
//		rslt_point = it->second;
//		if ((rslt_point->mDate->m_curValue ==rslt_point->mDate->m_lastValue
//			&&!(rslt_point->mDate->m_isInto)
//			&&rslt_point->mDate->m_TimeLong >=rslt_point->mDate->m_deaBand)
//			||(rslt_point->mDate->m_curValue !=rslt_point->mDate->m_lastValue
//			&&rslt_point->mDate->m_LastTimeLong <rslt_point->mDate->m_deaBand)
//			||(rslt_point->mDate->m_curValue !=rslt_point->mDate->m_lastValue
//			&&rslt_point->mDate->m_LastTimeLong >=rslt_point->mDate->m_deaBand)
//			&&(!rslt_point->mDate->m_lastisInto))
//		{
//
//
//			if(rslt_point->mDate->m_curValue ==rslt_point->mDate->m_lastValue
//				&&!rslt_point->mDate->m_isInto
//				&&rslt_point->mDate->m_TimeLong >=rslt_point->mDate->m_deaBand)
//			{
//				guId = rslt_point->mDate->m_id;
//				endTime = PubOpt::SystemOpt::DateTmToStr(rslt_point->mDate->m_EndTime,0);
//				//SetOtlDatetime(endTime,rslt_point->mDate->m_EndTime);
//
//			}
//			else if ((rslt_point->mDate->m_curValue !=rslt_point->mDate->m_lastValue
//				&&rslt_point->mDate->m_LastTimeLong <rslt_point->mDate->m_deaBand))
//			{
//				guId = rslt_point->mDate->m_perId;
//				endTime = PubOpt::SystemOpt::DateTmToStr(rslt_point->mDate->m_EndTime,0);
//				if (rslt_point->mDate->m_curValue==rslt_point->mDate->m_perValue)
//				{
//					rslt_point->mDate->m_id = rslt_point->mDate->m_perId;
//					rslt_point->mDate->m_isInto=false;
//				}
//			}
//			else if (rslt_point->mDate->m_curValue !=rslt_point->mDate->m_lastValue
//				&&rslt_point->mDate->m_LastTimeLong >=rslt_point->mDate->m_deaBand
//				&&(!rslt_point->mDate->m_lastisInto))
//			{
//				guId = rslt_point->mDate->m_perId;
//				endTime = PubOpt::SystemOpt::DateTmToStr(rslt_point->mDate->m_LastEndTime,0);
//			}
//			
//			if (rslt_point->mIsGetCurVale)
//			{
//				maxValue = Util::Number2String(rslt_point->m_maxValue);
//				minValue = Util::Number2String(rslt_point->m_minValue);
//				avgValue = Util::Number2String(rslt_point->m_avgValue);
//
//			}
//			else
//			{
//				if (rslt_point->mIsInitCurVale)
//				{
//					maxValue = Util::Number2String(rslt_point->m_maxValue);
//					minValue = Util::Number2String(rslt_point->m_minValue);
//					avgValue = Util::Number2String(rslt_point->m_avgValue);
//				}
//				else
//				{
//					maxValue = "null";
//					minValue = "null";
//					avgValue = "null";
//				}
//			}
//			if (rslt_point->mIsGetPreVale)
//			{
//				permaxValue = Util::Number2String(rslt_point->m_pmaxValue);
//				perminValue = Util::Number2String(rslt_point->m_pminValue);
//				peravgValue = Util::Number2String(rslt_point->m_pavgValue);
//			}
//			else
//			{
//				if (rslt_point->mIsInitPreVale)
//				{
//					permaxValue = Util::Number2String(rslt_point->m_pmaxValue);
//					perminValue = Util::Number2String(rslt_point->m_pminValue);
//					peravgValue = Util::Number2String(rslt_point->m_pavgValue);
//				}
//				else
//				{
//					permaxValue = "null";
//					perminValue = "null";
//					peravgValue = "null";
//				}
//
//			}
//			if (rslt_point->mIsGetSimVale)
//			{
//				avgSimilar = Util::Number2String(rslt_point->m_savgValue);
//			} 
//			else
//			{
//				if (rslt_point->mIsInitSimVale)
//				{
//					avgSimilar = Util::Number2String(rslt_point->m_savgValue);
//				}
//				else
//				{
//					avgSimilar = "null";
//				}
//			}
//			if(guId.empty()) continue;
//			SQL = SQL.arg(QString::fromStdString(endTime))
//				.arg(QString::fromStdString(maxValue))
//				.arg(QString::fromStdString(minValue))
//				.arg(QString::fromStdString(avgValue))
//				.arg(QString::fromStdString(permaxValue))
//				.arg(QString::fromStdString(perminValue))
//				.arg(QString::fromStdString(peravgValue))
//				.arg(QString::fromStdString(avgSimilar))
//				.arg(QString::fromStdString(guId));
//
//			mQtOpt->QtQueryPrepare(SQL);
//			mQtOpt->QtExec();
//
//			/*nErr = mQtOpt->BindHandInputByName(endTime);
//			Aos_Assert_CB(nErr);
//
//			nErr = mQtOpt->BindHandInputByName(maxValue);
//			Aos_Assert_CB(nErr);
//
//			nErr = mQtOpt->BindHandInputByName(minValue);
//			Aos_Assert_CB(nErr);
//
//			nErr = mQtOpt->BindHandInputByName(avgValue);
//			Aos_Assert_CB(nErr);
//
//			nErr = mQtOpt->BindHandInputByName(permaxValue);
//			Aos_Assert_CB(nErr);
//
//			nErr = mQtOpt->BindHandInputByName(perminValue);
//			Aos_Assert_CB(nErr);
//
//			nErr = mQtOpt->BindHandInputByName(peravgValue);
//			Aos_Assert_CB(nErr);
//
//
//			nErr = mQtOpt->BindHandInputByName(avgSimilar);
//			Aos_Assert_CB(nErr);
//
//			nErr = mQtOpt->BindHandInputByName(guId);
//			Aos_Assert_CB(nErr);*/
//
//			icount++;
//			ipos++;
//			if (CON_RSLT_SIZE==icount)
//			{
//				nErr = stmtHandSubmit(CON_SET_DEAL_POINT);
//				if(!nErr)
//				{
//					stmtTransRollback(CON_SET_DEAL_POINT);  //回滚记录
//				}
//				Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_POINT),false);
//				icount = 0;
//			}
//		}
//	}
//	if (0!=icount)
//	{
//		nErr = stmtHandSubmit(CON_SET_DEAL_POINT);
//		icount = 0;
//	}
//	qDebug()<<"update num"<<ipos;
//	return nErr;
//}

bool AlarmSetDeal::RsltGroupUpFrontInsToRsdb()
{
    bool nErr = true;
    MapStringToAlarmGrouRst_It it;
    AlarmGrouRst  * rslt_group = NULL;
    //std::string categoryId;
    int icount = 0;
    QVariantList list1;
    Aos_Assert_R(Util::QtConnect(mQtOpt), false);
    Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_GROUP),false);
    Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_GROUP, g_strRsltGroupUpFrontInsSQL), false);
    it = mMapAlarmGrouRst.begin();
    for (;it!= mMapAlarmGrouRst.end();++it)
    {
        rslt_group = it->second;
        /*if (rslt_group->mStrGroupId=="4_fl_1gjsdc")
        {
            Aos_WriteLog(PubOpt::StringOpt::StringFormat("4_fl_1gjsdc:%d",rslt_group->mDate->m_deaBand).c_str());
        }*/
        if ((rslt_group->mDate->m_curValue ==rslt_group->mDate->m_lastValue
             &&rslt_group->mDate->m_isInto
             &&rslt_group->mDate->m_TimeLong >=rslt_group->mDate->m_deaBand)
                ||(rslt_group->mDate->m_curValue !=rslt_group->mDate->m_lastValue
                   &&rslt_group->mDate->m_lastisInto
                   &&rslt_group->mDate->m_LastTimeLong >=rslt_group->mDate->m_deaBand)||misFirstCal)
        {

            //mQtOpt->QtbindValue(0,QString::fromStdString(rslt_group->mStrGroupId));
            list1<<QString::fromLocal8Bit(rslt_group->mStrGroupId.c_str());
            icount++;
            if (CON_RSLT_SIZE==icount)
            {
                mQtOpt->QtbindValue(0,list1);
                mQtOpt->QtExecBatch();
                nErr = stmtHandSubmit(CON_SET_DEAL_GROUP);
                if(!nErr)
                    stmtTransRollback(CON_SET_DEAL_GROUP);

                stmtHandCloseStream(CON_SET_DEAL_GROUP);
                Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_GROUP),false);
                Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_GROUP, g_strRsltGroupUpFrontInsSQL), false);
                icount = 0;
                list1.clear();
            }
        }

    }
    if (0!=icount)
    {
        mQtOpt->QtbindValue(0,list1);
        mQtOpt->QtExecBatch();
        nErr = stmtHandSubmit(CON_SET_DEAL_GROUP);
        icount = 0;
    }
    nErr = stmtHandSubmit(CON_SET_DEAL_GROUP);
    stmtHandCloseStream(CON_SET_DEAL_GROUP);
    return nErr;
}

bool AlarmSetDeal::RsltGroupInToRsdb()
{
    bool nErr = true;
    MapStringToAlarmGrouRst_It it;
    AlarmGrouRst  * rslt_group = NULL;
    int alarmLevel,isHistory = 0;
    double alarmScore = 0;
    std::string guId,beginTime,endTime;
    QVariantList listGuId,listCategoryId,listBeginTime,listEndTime;
    QVariantList listLevel,listScore,listIsHistory;
    int icount = 0;
    int ipos = 0,ipos2=0;
    Aos_Assert_R(Util::QtConnect(mQtOpt), false);
    Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_GROUP),false);
    //Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_GROUP, g_strRsltGroupInSQL), false);
    if (SQL_SERVERCE==mQtOpt->m_strRsdbType)
    {
        Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_GROUP, g_strRsltGroupInSQL), false);
    }
    else if (ORACLE==mQtOpt->m_strRsdbType)
    {
        Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_GROUP, g_strOrcRsltGroupInSQL), false);
    }
    else
    {
        Aos_Assert_S("关系数据库没配对应类型");
        stmtHandCloseStream(CON_SET_DEAL_GROUP);
        return false;
    }
    it = mMapAlarmGrouRst.begin();
    for (;it!= mMapAlarmGrouRst.end();++it)
    {
        ipos++;
        rslt_group = it->second;
        if ((rslt_group->mDate->m_curValue ==rslt_group->mDate->m_lastValue
             &&rslt_group->mDate->m_isInto
             &&rslt_group->mDate->m_TimeLong >=rslt_group->mDate->m_deaBand)
                ||(rslt_group->mDate->m_curValue !=rslt_group->mDate->m_lastValue
                   &&rslt_group->mDate->m_lastisInto
                   &&rslt_group->mDate->m_LastTimeLong >=rslt_group->mDate->m_deaBand))
        {
            if(rslt_group->mDate->m_curValue ==rslt_group->mDate->m_lastValue
                    &&rslt_group->mDate->m_isInto
                    &&rslt_group->mDate->m_TimeLong >=rslt_group->mDate->m_deaBand)
            {
                guId = rslt_group->mDate->m_id;
                beginTime = PubOpt::SystemOpt::DateTmToStr(rslt_group->mDate->m_StartTime,0);
                endTime = PubOpt::SystemOpt::DateTmToStr(rslt_group->mDate->m_EndTime,0);
                alarmLevel = rslt_group->mDate->m_curValue;
                alarmScore = rslt_group->mDate->m_alarmScore;
            }
            else
            {
                guId = rslt_group->mDate->m_lastId;
                beginTime = PubOpt::SystemOpt::DateTmToStr(rslt_group->mDate->m_LastStartTime,0);
                endTime = PubOpt::SystemOpt::DateTmToStr(rslt_group->mDate->m_LastEndTime,0);
                alarmLevel = rslt_group->mDate->m_lastValue;
                alarmScore = rslt_group->mDate->m_alarmLastScore;
            }
            if(listGuId.contains(QString(guId.c_str())))
                continue;
            if(guId.empty()) continue;
            listGuId<<QString(guId.c_str());
            listCategoryId<<QString::fromLocal8Bit(rslt_group->mStrGroupId.c_str());
            listBeginTime<<QString(beginTime.c_str());
            listEndTime<<QString(endTime.c_str());
            listLevel<<alarmLevel;
            listScore<<alarmScore;
            listIsHistory<<isHistory;

            if(rslt_group->mDate->m_curValue ==rslt_group->mDate->m_lastValue
                    &&rslt_group->mDate->m_isInto
                    &&rslt_group->mDate->m_TimeLong >=rslt_group->mDate->m_deaBand)
            {
                rslt_group->mDate->m_perId = rslt_group->mDate->m_id;  //插入新纪录,上条记录更新
                rslt_group->mDate->m_perValue = rslt_group->mDate->m_curValue;
                rslt_group->mDate->m_perStartTime = rslt_group->mDate->m_StartTime;
                rslt_group->mDate->m_perEndTime = rslt_group->mDate->m_EndTime;
                rslt_group->mDate->m_isInto = false;
            }
            else
            {
                rslt_group->mDate->m_perId = rslt_group->mDate->m_lastId;   //插入新纪录,上条记录更新
                rslt_group->mDate->m_perValue = rslt_group->mDate->m_lastValue;
                rslt_group->mDate->m_perStartTime = rslt_group->mDate->m_LastStartTime;
                rslt_group->mDate->m_perEndTime = rslt_group->mDate->m_LastEndTime;
                rslt_group->mDate->m_lastisInto = false;
            }
            icount++;
            ipos2++;
            if (CON_RSLT_SIZE==icount)
            {
                mQtOpt->QtbindValue(0,listGuId);
                mQtOpt->QtbindValue(1,listCategoryId);
                mQtOpt->QtbindValue(2,listBeginTime);
                mQtOpt->QtbindValue(3,listEndTime);
                mQtOpt->QtbindValue(4,listLevel);
                mQtOpt->QtbindValue(5,listScore);
                mQtOpt->QtbindValue(6,listIsHistory);
                nErr = mQtOpt->QtExecBatch();
                if(!nErr)
                {
                    Aos_WriteLog_D("2000RsltGroupInToRsdb err!");
                    nErr = stmtTransRollback(CON_SET_DEAL_GROUP);//回滚数据库记录
                }
                nErr = stmtHandSubmit(CON_SET_DEAL_GROUP);
                if(!nErr)
                {
                    RollbackGroup(ipos);   //回滚内存记录
                    stmtTransRollback(CON_SET_DEAL_GROUP);//回滚数据库记录
                }
                stmtHandCloseStream(CON_SET_DEAL_GROUP);
                Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_GROUP),false); //重新打开事务
                if (SQL_SERVERCE==mQtOpt->m_strRsdbType)
                {
                    Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_GROUP, g_strRsltGroupInSQL), false);
                }
                else if (ORACLE==mQtOpt->m_strRsdbType)
                {
                    Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_GROUP, g_strOrcRsltGroupInSQL), false);
                }
                else
                {
                    Aos_Assert_S("关系数据库没配对应类型");
                    stmtHandCloseStream(CON_SET_DEAL_GROUP);
                    return false;
                }
                icount = 0;
                listGuId.clear();listCategoryId.clear();listBeginTime.clear();
                listEndTime.clear();listLevel.clear();listScore.clear();listIsHistory.clear();
            }
        }
    }
    if (0!=icount)
    {
        mQtOpt->QtbindValue(0,listGuId);
        mQtOpt->QtbindValue(1,listCategoryId);
        mQtOpt->QtbindValue(2,listBeginTime);
        mQtOpt->QtbindValue(3,listEndTime);
        mQtOpt->QtbindValue(4,listLevel);
        mQtOpt->QtbindValue(5,listScore);
        mQtOpt->QtbindValue(6,listIsHistory);
        nErr = mQtOpt->QtExecBatch();
        if(!nErr)
        {
            Aos_WriteLog_D("RsltGroupInToRsdb err!");
            nErr = stmtTransRollback(CON_SET_DEAL_GROUP);//回滚数据库记录
        }
        nErr = stmtHandSubmit(CON_SET_DEAL_GROUP);
        if(!nErr)
        {
            RollbackGroup(ipos);   //回滚内存记录
            stmtTransRollback(CON_SET_DEAL_GROUP);//回滚数据库记录
        }
        stmtHandCloseStream(CON_SET_DEAL_GROUP);
        icount = 0;
    }
    nErr = stmtHandSubmit(CON_SET_DEAL_GROUP);
    stmtHandCloseStream(CON_SET_DEAL_GROUP);
    //qDebug()<<"insert group num"<<ipos2;
    return nErr;
}
bool AlarmSetDeal::RsltGroupUpBackInRsdb()
{
    bool nErr = true;
    MapStringToAlarmGrouRst_It it;
    AlarmGrouRst  * rslt = NULL;
    std::string guId,endTime;
    QVariantList listGuId,listEndTime;
    int icount = 0,ipos2 = 0;
    Aos_Assert_R(Util::QtConnect(mQtOpt), false);
    Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_GROUP),false);
    //Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_GROUP, g_strRsltGroupUpBackInSQL), false);
    if (SQL_SERVERCE==mQtOpt->m_strRsdbType)
    {
        Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_GROUP, g_strRsltGroupUpBackInSQL), false);
    }
    else if (ORACLE==mQtOpt->m_strRsdbType)
    {
        Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_GROUP, g_strOrcRsltGroupUpBackInSQL), false);
    }
    else
    {
        Aos_Assert_S("关系数据库没配对应类型");
        stmtHandCloseStream(CON_SET_DEAL_GROUP);
        return false;
    }
    it = mMapAlarmGrouRst.begin();
    for (;it!= mMapAlarmGrouRst.end();++it)
    {
        rslt = it->second;
        if ((rslt->mDate->m_curValue ==rslt->mDate->m_lastValue
             &&!(rslt->mDate->m_isInto)
             &&rslt->mDate->m_TimeLong >=rslt->mDate->m_deaBand)
                ||(rslt->mDate->m_curValue !=rslt->mDate->m_lastValue
                   &&rslt->mDate->m_LastTimeLong <rslt->mDate->m_deaBand)
                ||(rslt->mDate->m_curValue !=rslt->mDate->m_lastValue
                   &&rslt->mDate->m_LastTimeLong >=rslt->mDate->m_deaBand)
                &&(!rslt->mDate->m_lastisInto))
        {


            if(rslt->mDate->m_curValue ==rslt->mDate->m_lastValue
                    &&!rslt->mDate->m_isInto
                    &&rslt->mDate->m_TimeLong >=rslt->mDate->m_deaBand)
            {
                guId = rslt->mDate->m_id;
                endTime = PubOpt::SystemOpt::DateTmToStr(rslt->mDate->m_EndTime,0);

            }
            else if ((rslt->mDate->m_curValue !=rslt->mDate->m_lastValue
                      &&rslt->mDate->m_LastTimeLong <rslt->mDate->m_deaBand
                      &&rslt->mDate->m_LastTimeLong > 0))
            {
                guId = rslt->mDate->m_perId;
                endTime = PubOpt::SystemOpt::DateTmToStr(rslt->mDate->m_EndTime,0);

                if (rslt->mDate->m_curValue==rslt->mDate->m_perValue)
                {
                    rslt->mDate->m_id = rslt->mDate->m_perId;
                    rslt->mDate->m_isInto=false;
                }
            }
            else if (rslt->mDate->m_curValue !=rslt->mDate->m_lastValue
                     &&rslt->mDate->m_LastTimeLong >=rslt->mDate->m_deaBand
                     &&(!rslt->mDate->m_lastisInto))
            {
                guId = rslt->mDate->m_perId;
                endTime = PubOpt::SystemOpt::DateTmToStr(rslt->mDate->m_LastEndTime,0);
            }
            listEndTime<<QString(endTime.c_str());
            listGuId<<QString(guId.c_str());

            icount++;
            ipos2++;
            if (CON_RSLT_SIZE==icount)
            {
                mQtOpt->QtbindValue(0,listEndTime);
                mQtOpt->QtbindValue(1,listGuId);
                nErr = mQtOpt->QtExecBatch();
                if(!nErr)
                {
                    Aos_WriteLog_D("2000RsltGroupUpBackInRsdb err!");
                    nErr = stmtTransRollback(CON_SET_DEAL_GROUP);//回滚数据库记录
                }
                nErr = stmtHandSubmit(CON_SET_DEAL_GROUP);
                if(!nErr)
                {
                    //RollbackGroup(ipos);   //回滚内存记录
                    nErr = stmtTransRollback(CON_SET_DEAL_GROUP);//回滚数据库记录
                }
                stmtHandCloseStream(CON_SET_DEAL_GROUP);
                Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_GROUP),false); //重新打开事务
                if (SQL_SERVERCE==mQtOpt->m_strRsdbType)
                {
                    Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_GROUP, g_strRsltGroupUpBackInSQL), false);
                }
                else if (ORACLE==mQtOpt->m_strRsdbType)
                {
                    Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_GROUP, g_strOrcRsltGroupUpBackInSQL), false);
                }
                else
                {
                    Aos_Assert_S("关系数据库没配对应类型");
                    stmtHandCloseStream(CON_SET_DEAL_GROUP);
                    return false;
                }
                icount = 0;

                listEndTime.clear();listGuId.clear();
            }
        }
    }
    if (0!=icount)
    {
        mQtOpt->QtbindValue(0,listEndTime);
        mQtOpt->QtbindValue(1,listGuId);
        nErr = mQtOpt->QtExecBatch();
        if(!nErr)
        {
            Aos_WriteLog_D("RsltGroupUpBackInRsdb err!");
            nErr = stmtTransRollback(CON_SET_DEAL_GROUP);//回滚数据库记录
        }
        nErr = stmtHandSubmit(CON_SET_DEAL_GROUP);
        if(!nErr)
        {
            //RollbackGroup(ipos);   //回滚内存记录
            nErr = stmtTransRollback(CON_SET_DEAL_GROUP);//回滚数据库记录
        }
        stmtHandCloseStream(CON_SET_DEAL_GROUP);
        icount = 0;
    }
    nErr = stmtHandSubmit(CON_SET_DEAL_GROUP);
    stmtHandCloseStream(CON_SET_DEAL_GROUP);
    //qDebug()<<"update grou num"<<ipos2;
    return nErr;
}

bool AlarmSetDeal::RsltModelToSetUpFrontInsToRsdb()
{
    bool nErr = true;
    MapStringToAlarmModeltoSetRst_It it;
    AlarmModeltoSetRst  * rslt = NULL;
    //char modelId[64];
    QVariantList listModleId;
    int icount = 0;
    Aos_Assert_R(Util::QtConnect(mQtOpt), false);
    Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_MODELTOSET),false);
    Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELTOSET, g_strRsltModelUpFrontInsSQL), false);
    it = mMapAlarmModeltoSetRst.begin();
    for (;it!= mMapAlarmModeltoSetRst.end();++it)
    {
        rslt = it->second;
        /*if("67c25ae4-64ce-4e9a-9ed8-095a27fc9dcd"==rslt->mStrId||"19096b38-9f32-47eb-9b54-095bc6fbe4e3"==rslt->mStrId)
            continue;*/
        if ((rslt->mDate->m_curValue ==rslt->mDate->m_lastValue
             &&rslt->mDate->m_isInto
             &&rslt->mDate->m_TimeLong >=rslt->mDate->m_deaBand)
                ||(rslt->mDate->m_curValue !=rslt->mDate->m_lastValue
                   &&rslt->mDate->m_lastisInto
                   &&rslt->mDate->m_LastTimeLong >=rslt->mDate->m_deaBand)||misFirstCal)
        {
            listModleId<<QString::fromLocal8Bit(rslt->mStrId.c_str());
            icount++;

            if (CON_RSLT_SIZE==icount)
            {
                mQtOpt->QtbindValue(0,listModleId);
                mQtOpt->QtExecBatch();
                nErr = stmtHandSubmit(CON_SET_DEAL_MODELTOSET);
                if(!nErr)
                {
                    nErr = stmtTransRollback(CON_SET_DEAL_MODELTOSET);//回滚数据库记录
                }
                stmtHandCloseStream(CON_SET_DEAL_MODELTOSET);
                Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_MODELTOSET),false); //重新打开事务
                Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELTOSET, g_strRsltModelUpFrontInsSQL), false);
                icount = 0;
                listModleId.clear();
            }
        }

    }
    if (0!=icount)
    {
        mQtOpt->QtbindValue(0,listModleId);
        mQtOpt->QtExecBatch();
        nErr = stmtHandSubmit(CON_SET_DEAL_MODELTOSET);
        if(!nErr)
        {
            nErr = stmtTransRollback(CON_SET_DEAL_MODELTOSET);//回滚数据库记录
        }
        stmtHandCloseStream(CON_SET_DEAL_MODELTOSET);
        icount = 0;
    }
    nErr = stmtHandSubmit(CON_SET_DEAL_MODELTOSET);
    stmtHandCloseStream(CON_SET_DEAL_MODELTOSET);
    return nErr;
}

bool AlarmSetDeal::RsltModelToSetInToRsdb()
{
    bool nErr = true;
    MapStringToAlarmModeltoSetRst_It it;
    AlarmModeltoSetRst  * rslt = NULL;

    std::string guId,beginTime,endTime;
    QVariantList listGuId,listModleId,listBeginTime,listEndTime;
    QVariantList listLevel,listScore,listIsHistory;
    int alarmLevel,isHistory = 0;
    double alarmScore = 0;
    int icount = 0;
    int ipos = 0;
    Aos_Assert_R(Util::QtConnect(mQtOpt), false);
    Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_MODELTOSET),false);
    //Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELTOSET, g_strRsltModelInSQL), false);
    if (SQL_SERVERCE==mQtOpt->m_strRsdbType)
    {
        Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELTOSET, g_strRsltModelInSQL), false);
    }
    else if (ORACLE==mQtOpt->m_strRsdbType)
    {
        Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELTOSET, g_strOrcRsltModelInSQL), false);
    }
    else
    {
        Aos_Assert_S("关系数据库没配对应类型");
        stmtHandCloseStream(CON_SET_DEAL_MODELTOSET);
        return false;
    }
    it = mMapAlarmModeltoSetRst.begin();
    for (;it!= mMapAlarmModeltoSetRst.end();++it)
    {
        ipos++;
        rslt = it->second;
        //if("3_zc"!=rslt->mStrId) continue;
        //if("3_zc"==rslt->mStrId||"4_1gj"==rslt->mStrId||"4_3gj"==rslt->mStrId)//
        /*if("67c25ae4-64ce-4e9a-9ed8-095a27fc9dcd"==rslt->mStrId||"19096b38-9f32-47eb-9b54-095bc6fbe4e3"==rslt->mStrId)
            continue;*/
        int i = 100;
        //Aos_Assert_S(rslt->mStrId.c_str());
        if ((rslt->mDate->m_curValue ==rslt->mDate->m_lastValue
             &&rslt->mDate->m_isInto
             &&rslt->mDate->m_TimeLong >=rslt->mDate->m_deaBand)
                ||(rslt->mDate->m_curValue !=rslt->mDate->m_lastValue
                   &&rslt->mDate->m_lastisInto
                   &&rslt->mDate->m_LastTimeLong >=rslt->mDate->m_deaBand))
        {
            if(rslt->mDate->m_curValue ==rslt->mDate->m_lastValue
                    &&rslt->mDate->m_isInto
                    &&rslt->mDate->m_TimeLong >=rslt->mDate->m_deaBand)
            {
                guId = rslt->mDate->m_id;
                beginTime = PubOpt::SystemOpt::DateTmToStr(rslt->mDate->m_StartTime,0);
                endTime = PubOpt::SystemOpt::DateTmToStr(rslt->mDate->m_EndTime,0);
                alarmLevel = rslt->mDate->m_curValue;
                alarmScore = rslt->mDate->m_alarmScore;
            }
            else
            {
                guId = rslt->mDate->m_lastId;
                beginTime = PubOpt::SystemOpt::DateTmToStr(rslt->mDate->m_LastStartTime,0);
                endTime = PubOpt::SystemOpt::DateTmToStr(rslt->mDate->m_LastEndTime,0);
                alarmLevel = rslt->mDate->m_lastValue;
                alarmScore = rslt->mDate->m_alarmLastScore;
            }
            if(guId.empty()) continue;
            listGuId<<QString(guId.c_str());
            listModleId<<QString::fromLocal8Bit(rslt->mStrId.c_str());
            listBeginTime<<QString(beginTime.c_str());
            listEndTime<<QString(endTime.c_str());
            listLevel<<alarmLevel;
            listScore<<alarmScore;
            listIsHistory<<isHistory;

            if(rslt->mDate->m_curValue ==rslt->mDate->m_lastValue
                    &&rslt->mDate->m_isInto
                    &&rslt->mDate->m_TimeLong >=rslt->mDate->m_deaBand)
            {
                rslt->mDate->m_perId = rslt->mDate->m_id;  //插入新纪录,上条记录更新
                rslt->mDate->m_perValue = rslt->mDate->m_curValue;
                rslt->mDate->m_perStartTime = rslt->mDate->m_StartTime;
                rslt->mDate->m_perEndTime = rslt->mDate->m_EndTime;
                rslt->mDate->m_isInto = false;
            }
            else
            {
                rslt->mDate->m_perId = rslt->mDate->m_lastId;   //插入新纪录,上条记录更新
                rslt->mDate->m_perValue = rslt->mDate->m_lastValue;
                rslt->mDate->m_perStartTime = rslt->mDate->m_LastStartTime;
                rslt->mDate->m_perEndTime = rslt->mDate->m_LastEndTime;
                rslt->mDate->m_lastisInto = false;
            }
            icount++;
            if (CON_RSLT_SIZE==icount) //CON_RSLT_SIZE
            {
                mQtOpt->QtbindValue(0,listGuId);
                mQtOpt->QtbindValue(1,listModleId);
                mQtOpt->QtbindValue(2,listBeginTime);
                mQtOpt->QtbindValue(3,listEndTime);
                mQtOpt->QtbindValue(4,listLevel);
                mQtOpt->QtbindValue(5,listScore);
                mQtOpt->QtbindValue(6,listIsHistory);
                nErr = mQtOpt->QtExecBatch();
                if(!nErr)
                {
                    Aos_WriteLog_D("2000RsltModelToSetInToRsdb err!");
                    nErr = stmtTransRollback(CON_SET_DEAL_MODELTOSET);//回滚数据库记录
                }
                nErr = stmtHandSubmit(CON_SET_DEAL_MODELTOSET);
                if(!nErr)
                {
                    Aos_WriteLog_D("2000RsltModelToSetInToRsdb err!");
                    RollbackModelToSet(ipos);   //回滚内存记录
                    stmtTransRollback(CON_SET_DEAL_MODELTOSET);//回滚数据库记录
                }
                stmtHandCloseStream(CON_SET_DEAL_MODELTOSET);
                Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_MODELTOSET),false); //重新打开事务
                if (SQL_SERVERCE==mQtOpt->m_strRsdbType)
                {
                    Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELTOSET, g_strRsltModelInSQL), false);
                }
                else if (ORACLE==mQtOpt->m_strRsdbType)
                {
                    Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELTOSET, g_strOrcRsltModelInSQL), false);
                }
                else
                {
                    Aos_Assert_S("关系数据库没配对应类型");
                    stmtHandCloseStream(CON_SET_DEAL_MODELTOSET);
                    return false;
                }
                icount = 0;
                listGuId.clear(); listModleId.clear(); listBeginTime.clear();
                listEndTime.clear(); listLevel.clear(); listScore.clear();
                listIsHistory.clear();
            }
        }
    }
    if (0!=icount)
    {
        mQtOpt->QtbindValue(0,listGuId);
        mQtOpt->QtbindValue(1,listModleId);
        mQtOpt->QtbindValue(2,listBeginTime);
        mQtOpt->QtbindValue(3,listEndTime);
        mQtOpt->QtbindValue(4,listLevel);
        mQtOpt->QtbindValue(5,listScore);
        mQtOpt->QtbindValue(6,listIsHistory);
        nErr = mQtOpt->QtExecBatch();
        if(!nErr)
        {
            Aos_WriteLog_D("RsltModelToSetInToRsdb err!");
            nErr = stmtTransRollback(CON_SET_DEAL_MODELTOSET);//回滚数据库记录
        }
        nErr = stmtHandSubmit(CON_SET_DEAL_MODELTOSET);
        if(!nErr)
        {
            RollbackModelToSet(ipos);   //回滚内存记录
            stmtTransRollback(CON_SET_DEAL_MODELTOSET);//回滚数据库记录
        }
        Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_MODELTOSET),false); //重新打开事务
        stmtHandCloseStream(CON_SET_DEAL_MODELTOSET);
        icount = 0;
    }
    nErr = stmtHandSubmit(CON_SET_DEAL_MODELTOSET);
    stmtHandCloseStream(CON_SET_DEAL_MODELTOSET);
    return nErr;
}

bool AlarmSetDeal::RsltModelToSetUpBackInRsdb()
{
    bool nErr = true;
    MapStringToAlarmModeltoSetRst_It it;
    AlarmModeltoSetRst  * rslt = NULL;
    std::string guId,endTime;
    QVariantList listGuId,listEndTime;
    int icount = 0,ipos=0;
    Aos_Assert_R(Util::QtConnect(mQtOpt), false);
    //Aos_Assert_S("oo1g_strOrcRsltModelUpBackInSQL");
    Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_MODELTOSET),false);
    //Aos_Assert_S("oo2g_strOrcRsltModelUpBackInSQL");
    //Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELTOSET, g_strRsltModelUpBackInSQL), false);
    if (SQL_SERVERCE==mQtOpt->m_strRsdbType)
    {
        Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELTOSET, g_strRsltModelUpBackInSQL), false);
    }
    else if (ORACLE==mQtOpt->m_strRsdbType)
    {
        Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELTOSET, g_strOrcRsltModelUpBackInSQL), false);
    }
    else
    {
        Aos_Assert_S("关系数据库没配对应类型");
        stmtHandCloseStream(CON_SET_DEAL_MODELTOSET);
        return false;
    }
    //Aos_Assert_S("oo3g_strOrcRsltModelUpBackInSQL");
    it = mMapAlarmModeltoSetRst.begin();
    for (;it!= mMapAlarmModeltoSetRst.end();++it)
    {
        rslt = it->second;
        //if("3_zc"!=rslt->mStrId) continue;
        /*if("67c25ae4-64ce-4e9a-9ed8-095a27fc9dcd"==rslt->mStrId||"19096b38-9f32-47eb-9b54-095bc6fbe4e3"==rslt->mStrId)
            continue;*/
        int i = 100;
        //Aos_Assert_S("oo4g_strOrcRsltModelUpBackInSQL");
        //Aos_Assert_S(rslt->mStrId.c_str());
        if ((rslt->mDate->m_curValue ==rslt->mDate->m_lastValue
             &&!(rslt->mDate->m_isInto)
             &&rslt->mDate->m_TimeLong >rslt->mDate->m_deaBand)
                ||(rslt->mDate->m_curValue !=rslt->mDate->m_lastValue
                   &&rslt->mDate->m_LastTimeLong <rslt->mDate->m_deaBand)
                ||(rslt->mDate->m_curValue !=rslt->mDate->m_lastValue
                   &&rslt->mDate->m_LastTimeLong >rslt->mDate->m_deaBand)
                &&(!rslt->mDate->m_lastisInto))
        {//m_isPPDChange
            if(rslt->mDate->m_curValue ==rslt->mDate->m_lastValue
                    &&!rslt->mDate->m_isInto
                    &&rslt->mDate->m_TimeLong >rslt->mDate->m_deaBand)
            {
                guId = rslt->mDate->m_id;
                //Aos_Assert_S("115g_strOrcRsltModelUpBackInSQL");
                //SINGLETON(Log)->WriteLog(SINGLETON(Log)->StringFormat("[时间：%d]",rslt->mDate->m_EndTime));
                endTime = PubOpt::SystemOpt::DateTmToStr(rslt->mDate->m_EndTime,0);
                //Aos_Assert_S("116g_strOrcRsltModelUpBackInSQL");
            }
            else if ((rslt->mDate->m_curValue !=rslt->mDate->m_lastValue
                      &&rslt->mDate->m_LastTimeLong <rslt->mDate->m_deaBand
                      &&rslt->mDate->m_LastTimeLong > 0))
            {
                guId = rslt->mDate->m_perId;
                //Aos_Assert_S("oo5g_strOrcRsltModelUpBackInSQL");
                //SINGLETON(Log)->WriteLog(SINGLETON(Log)->StringFormat("[时间：%d]",rslt->mDate->m_EndTime));
                endTime = PubOpt::SystemOpt::DateTmToStr(rslt->mDate->m_EndTime,0);
                //Aos_Assert_S("oo6g_strOrcRsltModelUpBackInSQL");
                if (rslt->mDate->m_curValue==rslt->mDate->m_perValue)
                {
                    rslt->mDate->m_id = rslt->mDate->m_perId;
                    rslt->mDate->m_isInto=false;
                }
            }
            else if (rslt->mDate->m_curValue !=rslt->mDate->m_lastValue
                     &&rslt->mDate->m_LastTimeLong >rslt->mDate->m_deaBand
                     &&(!rslt->mDate->m_lastisInto))
            {
                guId = rslt->mDate->m_perId;
                //Aos_Assert_S("oo6g_strOrcRsltModelUpBackInSQL");
                //SINGLETON(Log)->WriteLog(SINGLETON(Log)->StringFormat("[时间：%d]",rslt->mDate->m_EndTime));
                endTime = PubOpt::SystemOpt::DateTmToStr(rslt->mDate->m_LastEndTime,0);
            }
            //Aos_Assert_S("oo7g_strOrcRsltModelUpBackInSQL");
            //SINGLETON(Log)->WriteLog(SINGLETON(Log)->StringFormat("[时间：%s]",endTime.c_str()));
            //SINGLETON(Log)->WriteLog(SINGLETON(Log)->StringFormat("[guId：%s]",guId.c_str()));
            if(guId.empty()) continue;
            listEndTime<<QString(endTime.c_str());
            //Aos_Assert_S("oo8g_strOrcRsltModelUpBackInSQL");
            listGuId<<QString(guId.c_str());
            //Aos_Assert_S("oo9g_strOrcRsltModelUpBackInSQL");

            icount++;
            ipos++;
            //Aos_Assert_S(rslt->mStrId.c_str());
            if (CON_RSLT_SIZE==icount)  //CON_RSLT_SIZE
            {
                //Aos_Assert_S(rslt->mStrId.c_str());
                mQtOpt->QtbindValue(0,listEndTime);
                mQtOpt->QtbindValue(1,listGuId);
                //Aos_Assert_S("1111112g_strOrcRsltModelUpBackInSQL");
                nErr = mQtOpt->QtExecBatch();
                if(!nErr)
                {
                    Aos_WriteLog_D("2000RsltModelToSetUpBackInRsdb err!");
                    nErr = stmtTransRollback(CON_SET_DEAL_MODELTOSET);//回滚数据库记录
                }
                nErr = stmtHandSubmit(CON_SET_DEAL_MODELTOSET);
                if(!nErr)
                {
                    RollbackModelToSet(ipos);   //回滚内存记录
                    stmtTransRollback(CON_SET_DEAL_MODELTOSET);//回滚数据库记录
                }
                stmtHandCloseStream(CON_SET_DEAL_MODELTOSET);
                Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_MODELTOSET),false);
                if (SQL_SERVERCE==mQtOpt->m_strRsdbType)
                {
                    Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELTOSET, g_strRsltModelUpBackInSQL), false);
                }
                else if (ORACLE==mQtOpt->m_strRsdbType)
                {
                    Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELTOSET, g_strOrcRsltModelUpBackInSQL), false);
                }
                else
                {
                    Aos_Assert_S("关系数据库没配对应类型");
                    stmtHandCloseStream(CON_SET_DEAL_MODELTOSET);
                    return false;
                }

                icount = 0;
                listEndTime.clear(); listGuId.clear();
            }
        }
    }
    if (0!=icount)
    {
        //Aos_Assert_S("QtbindValue1 listEndTime");
        mQtOpt->QtbindValue(0,listEndTime);
        //Aos_Assert_S("QtbindValue2 listEndTime");
        mQtOpt->QtbindValue(1,listGuId);
        //Aos_Assert_S("QtbindValue3 listEndTime");
        nErr = mQtOpt->QtExecBatch();
        //Aos_Assert_S("QtbindValue4 listEndTime");
        if(!nErr)
        {
            Aos_WriteLog_D("RsltModelToSetUpBackInRsdb err!");
            RollbackModelToSet(ipos);   //回滚内存记录
            nErr = stmtTransRollback(CON_SET_DEAL_MODELTOSET);//回滚数据库记录
            stmtHandCloseStream(CON_SET_DEAL_MODELTOSET);
            return nErr;
        }
        nErr = stmtHandSubmit(CON_SET_DEAL_MODELTOSET);
        //Aos_Assert_S("QtbindValue5 listEndTime");
        if(!nErr)
        {
            //RollbackModelToSet(ipos);   //回滚内存记录
            stmtTransRollback(CON_SET_DEAL_MODELTOSET);//回滚数据库记录

        }
        stmtHandCloseStream(CON_SET_DEAL_MODELTOSET);
        icount = 0;
        listEndTime.clear(); listGuId.clear();
    }
    nErr = stmtHandSubmit(CON_SET_DEAL_MODELTOSET);
    //Aos_Assert_S("QtbindValue58 listEndTime");
    stmtHandCloseStream(CON_SET_DEAL_MODELTOSET);
    //Aos_Assert_S("QtbindValue6 listEndTime");
    return nErr;
}
bool AlarmSetDeal::RsltModelConditionUpFrontInsToRsdb()
{
    bool nErr = true;
    MapStringToAlarmModelConditionRst_It it;
    AlarmModelConditionRst  * rslt = NULL;
    //char conditionId[64];
    QVariantList listConId;
    int icount = 0;
    Aos_Assert_R(Util::QtConnect(mQtOpt), false);
    if(misFirstCal)
    {
        Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELCONDTION, g_strRsltConditionUpFrontInsSQLfirst), false);
        return mQtOpt->QtExec();
    }
    Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_MODELCONDTION),false);
    Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELCONDTION, g_strRsltConditionUpFrontInsSQL), false);
    it = mMapAlarmModelConditionRst.begin();
    for (;it!= mMapAlarmModelConditionRst.end();++it)
    {
        rslt = it->second;
        if ((rslt->mCondtionDate->m_curValue ==rslt->mCondtionDate->m_lastValue
             &&rslt->mCondtionDate->m_isInto
             &&rslt->mCondtionDate->m_TimeLong >=rslt->mCondtionDate->m_deaBand)
                ||(rslt->mCondtionDate->m_curValue !=rslt->mCondtionDate->m_lastValue
                   &&rslt->mCondtionDate->m_lastisInto
                   &&rslt->mCondtionDate->m_LastTimeLong >=rslt->mCondtionDate->m_deaBand))
        {
            if (rslt->mCondId.empty())
            {
                //listConId<<QVariant(QVariant::String);
                continue;
            }
            listConId<<QString(rslt->mCondId.c_str());
            icount++;

            if (CON_RSLT_SIZE==icount)
            {
                mQtOpt->QtbindValue(0,listConId);
                mQtOpt->QtExecBatch();
                nErr = stmtHandSubmit(CON_SET_DEAL_MODELCONDTION);
                if(!nErr)
                {
                    stmtTransRollback(CON_SET_DEAL_MODELCONDTION);//回滚数据库记录
                }
                stmtHandCloseStream(CON_SET_DEAL_MODELCONDTION);
                Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_MODELCONDTION),false);
                Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELCONDTION, g_strRsltConditionUpFrontInsSQL), false);
                icount = 0;
                listConId.clear();
            }
        }

    }
    if (0!=icount)
    {
        mQtOpt->QtbindValue(0,listConId);
        mQtOpt->QtExecBatch();
        nErr = stmtHandSubmit(CON_SET_DEAL_MODELCONDTION);
        if(!nErr)
        {
            stmtTransRollback(CON_SET_DEAL_MODELCONDTION);//回滚数据库记录
        }
        stmtHandCloseStream(CON_SET_DEAL_MODELCONDTION);
        icount = 0;
    }
    nErr = stmtHandSubmit(CON_SET_DEAL_MODELCONDTION);
    stmtHandCloseStream(CON_SET_DEAL_MODELCONDTION);
    return nErr;
}
//bool AlarmSetDeal::RsltModelConditionInToRsdb()
//{
//	bool nErr = true;
//	MapStringToAlarmModelConditionRst_It it;
//	AlarmModelConditionRst  * rslt = NULL;
//
//	std::string guId,beginTime,endTime;
//	QVariantList listGuId,listConId,listBeginTime,listEndTime,listDuration,listIsHistory;
//	int isHistory = 0;
//	double duration = 0;
//	int icount = 0;
//	int ipos = 0;
//	Aos_Assert_R(Util::QtConnect(mQtOpt), false);
//	Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_MODELCONDTION),false);
//	Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELCONDTION, g_strRsltConditionInSQL), false);
//	it = mMapAlarmModelConditionRst.begin();
//	for (;it!= mMapAlarmModelConditionRst.end();++it)
//	{
//		ipos++;
//		rslt = it->second;
//		if(rslt->mModelIdTest=="4_1gj")
//			int i=100;
//		/*if(rslt->mModelIdTest!="4_1gj")
//			continue;*/
//		if ((rslt->mCondtionDate->m_curValue ==rslt->mCondtionDate->m_lastValue
//			&&rslt->mCondtionDate->m_isInto
//			&&rslt->mCondtionDate->m_TimeLong >=rslt->mCondtionDate->m_deaBand)
//			||(rslt->mCondtionDate->m_curValue !=rslt->mCondtionDate->m_lastValue
//			&&rslt->mCondtionDate->m_lastisInto
//			&&rslt->mCondtionDate->m_LastTimeLong >=rslt->mCondtionDate->m_deaBand))
//		{
//			if(rslt->mCondtionDate->m_curValue ==rslt->mCondtionDate->m_lastValue
//				&&rslt->mCondtionDate->m_isInto
//				&&rslt->mCondtionDate->m_TimeLong >=rslt->mCondtionDate->m_deaBand)
//			{
//				guId = rslt->mCondtionDate->m_id;
//				beginTime = PubOpt::SystemOpt::DateTmToStr(rslt->mCondtionDate->m_StartTime,0);
//				endTime = PubOpt::SystemOpt::DateTmToStr(rslt->mCondtionDate->m_EndTime,0);
//				duration = rslt->mCondtionDate->m_TimeLong;
//			}
//			else 
//			{
//				guId = rslt->mCondtionDate->m_lastId;
//				beginTime = PubOpt::SystemOpt::DateTmToStr(rslt->mCondtionDate->m_LastStartTime,0);
//				endTime = PubOpt::SystemOpt::DateTmToStr(rslt->mCondtionDate->m_LastEndTime,0);
//				duration = rslt->mCondtionDate->m_TimeLong;
//				duration = rslt->mCondtionDate->m_LastTimeLong;
//			}
//			if (rslt->mCondId.empty())
//			{
//				//listConId<<QVariant(QVariant::String);
//				continue;
//			}
//			if(guId.empty()) continue;
//			listConId<<QString(rslt->mCondId.c_str());
//			listGuId<<QString(guId.c_str());
//			listBeginTime<<QString(beginTime.c_str());
//			listEndTime<<QString(endTime.c_str());
//			listDuration<<duration;
//			listIsHistory<<isHistory;
//
//			if(rslt->mCondtionDate->m_curValue ==rslt->mCondtionDate->m_lastValue
//				&&rslt->mCondtionDate->m_isInto
//				&&rslt->mCondtionDate->m_TimeLong >=rslt->mCondtionDate->m_deaBand)
//			{
//				rslt->mCondtionDate->m_perId = rslt->mCondtionDate->m_id;  //插入新纪录,上条记录更新
//				rslt->mCondtionDate->m_perValue = rslt->mCondtionDate->m_curValue;
//				rslt->mCondtionDate->m_perStartTime = rslt->mCondtionDate->m_StartTime;
//				rslt->mCondtionDate->m_perEndTime = rslt->mCondtionDate->m_EndTime;
//				rslt->mCondtionDate->m_isInto = false;
//			}
//			else
//			{
//				rslt->mCondtionDate->m_perId = rslt->mCondtionDate->m_lastId;   //插入新纪录,上条记录更新
//				rslt->mCondtionDate->m_perValue = rslt->mCondtionDate->m_lastValue;
//				rslt->mCondtionDate->m_perStartTime = rslt->mCondtionDate->m_LastStartTime;
//				rslt->mCondtionDate->m_perEndTime = rslt->mCondtionDate->m_LastEndTime;
//				rslt->mCondtionDate->m_lastisInto = false;
//			}
//			icount++;
//			if (CON_RSLT_SIZE==icount)
//			{
//				mQtOpt->QtbindValue(0,listGuId);
//				mQtOpt->QtbindValue(1,listConId);
//				mQtOpt->QtbindValue(2,listBeginTime);
//				mQtOpt->QtbindValue(3,listEndTime);
//				mQtOpt->QtbindValue(4,listDuration);
//				mQtOpt->QtbindValue(5,listIsHistory);
//				nErr = mQtOpt->QtExecBatch();
//				if(!nErr)
//				{
//					Aos_WriteLog_D("2000RsltModelConditionInToRsdb err!");
//					nErr = stmtTransRollback(CON_SET_DEAL_MODELCONDTION);//回滚数据库记录
//				}
//				nErr = stmtHandSubmit(CON_SET_DEAL_MODELCONDTION);
//				if(!nErr)
//				{
//					RollbackCondition(ipos);   //回滚内存记录
//					stmtTransRollback(CON_SET_DEAL_MODELCONDTION);//回滚数据库记录
//				}
//				Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_MODELCONDTION),false); 
//				icount = 0;
//				listGuId.clear(); listConId.clear(); listBeginTime.clear();
//				listEndTime.clear(); listDuration.clear(); listIsHistory.clear();
//			}
//		}
//	}
//	if (0!=icount)
//	{
//		mQtOpt->QtbindValue(0,listGuId);
//		mQtOpt->QtbindValue(1,listConId);
//		mQtOpt->QtbindValue(2,listBeginTime);
//		mQtOpt->QtbindValue(3,listEndTime);
//		mQtOpt->QtbindValue(4,listDuration);
//		mQtOpt->QtbindValue(5,listIsHistory);
//		nErr = mQtOpt->QtExecBatch();
//		if(!nErr)
//		{
//			Aos_WriteLog_D("RsltModelConditionInToRsdb err!");
//			nErr = stmtTransRollback(CON_SET_DEAL_MODELCONDTION);//回滚数据库记录
//		}
//		nErr = stmtHandSubmit(CON_SET_DEAL_MODELCONDTION);
//		if(!nErr)
//		{
//			RollbackCondition(ipos);   //回滚内存记录
//			stmtTransRollback(CON_SET_DEAL_MODELCONDTION);//回滚数据库记录
//		}
//		icount = 0;
//	}
//
//	return nErr;
//}
//
//bool AlarmSetDeal::RsltModelConditionUpBackInRsdb()
//{
//	bool nErr = true;
//	MapStringToAlarmModelConditionRst_It it;
//	AlarmModelConditionRst  * rslt = NULL;
//
//	std::string guId,endTime;
//	QVariantList listGuId,listEndTime,listDuration;
//	double duration = 0;
//	int icount = 0;
//	Aos_Assert_R(Util::QtConnect(mQtOpt), false);
//	Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_MODELCONDTION),false);
//	Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELCONDTION, g_strRsltConditionUpBackInSQL), false);
//	it = mMapAlarmModelConditionRst.begin();
//	for (;it!= mMapAlarmModelConditionRst.end();++it)
//	{
//		rslt = it->second;
//		if(rslt->mCondId=="4_zc_yxms")
//			int i=100;
//		if(rslt->mModelIdTest=="4_1gj")
//			int i=100;
//		/*if(rslt->mModelIdTest!="4_1gj")
//			continue;*/
//		if ((rslt->mCondtionDate->m_curValue ==rslt->mCondtionDate->m_lastValue
//			&&!(rslt->mCondtionDate->m_isInto)
//			&&rslt->mCondtionDate->m_TimeLong >=rslt->mCondtionDate->m_deaBand)
//			||(rslt->mCondtionDate->m_curValue !=rslt->mCondtionDate->m_lastValue
//			&&rslt->mCondtionDate->m_LastTimeLong <rslt->mCondtionDate->m_deaBand)
//			||(rslt->mCondtionDate->m_curValue !=rslt->mCondtionDate->m_lastValue
//			&&rslt->mCondtionDate->m_LastTimeLong >=rslt->mCondtionDate->m_deaBand)
//			&&(!rslt->mCondtionDate->m_lastisInto))
//		{
//
//
//			if(rslt->mCondtionDate->m_curValue ==rslt->mCondtionDate->m_lastValue
//				&&!rslt->mCondtionDate->m_isInto
//				&&rslt->mCondtionDate->m_TimeLong >=rslt->mCondtionDate->m_deaBand)
//			{
//				if (rslt->mCondtionDate->m_curValue=="")
//					continue;
//				guId = rslt->mCondtionDate->m_id;
//				endTime = PubOpt::SystemOpt::DateTmToStr(rslt->mCondtionDate->m_EndTime,0);
//				duration = rslt->mCondtionDate->m_TimeLong;
//
//			}
//			else if ((rslt->mCondtionDate->m_curValue !=rslt->mCondtionDate->m_lastValue
//				&&rslt->mCondtionDate->m_LastTimeLong <rslt->mCondtionDate->m_deaBand
//				&&rslt->mCondtionDate->m_LastTimeLong >= 0))
//			{
//				guId = rslt->mCondtionDate->m_perId;
//				endTime = PubOpt::SystemOpt::DateTmToStr(rslt->mCondtionDate->m_EndTime,0);
//
//				if (rslt->mCondtionDate->m_curValue==rslt->mCondtionDate->m_perValue)
//				{
//					rslt->mCondtionDate->m_id = rslt->mCondtionDate->m_perId;
//					rslt->mCondtionDate->m_isInto=false;
//					duration = rslt->mCondtionDate->m_EndTime-rslt->mCondtionDate->m_perStartTime;
//				}
//				else
//					duration = rslt->mCondtionDate->m_TimeLong;
//			}
//			else if (rslt->mCondtionDate->m_curValue !=rslt->mCondtionDate->m_lastValue
//				&&rslt->mCondtionDate->m_LastTimeLong >=rslt->mCondtionDate->m_deaBand
//				&&(!rslt->mCondtionDate->m_lastisInto))
//			{
//				if (rslt->mCondtionDate->m_lastValue=="")
//					continue;
//				guId = rslt->mCondtionDate->m_perId;
//				endTime = PubOpt::SystemOpt::DateTmToStr(rslt->mCondtionDate->m_LastEndTime,0);
//				duration = rslt->mCondtionDate->m_EndTime-rslt->mCondtionDate->m_perStartTime;
//			}
//			
//			listEndTime<<QString(endTime.c_str());
//			listDuration<<duration;
//			listGuId<<QString(guId.c_str());
//			icount++;
//			if (CON_RSLT_SIZE==icount)
//			{
//				mQtOpt->QtbindValue(0,listEndTime);
//				mQtOpt->QtbindValue(1,listDuration);
//				mQtOpt->QtbindValue(2,listGuId);
//				nErr = mQtOpt->QtExecBatch();
//				if(!nErr)
//				{
//					Aos_WriteLog_D("2000RsltModelConditionUpBackInRsdb err!");
//					nErr = stmtTransRollback(CON_SET_DEAL_MODELCONDTION);//回滚数据库记录
//				}
//				nErr = stmtHandSubmit(CON_SET_DEAL_MODELCONDTION);
//				if(!nErr)
//				{
//					stmtTransRollback(CON_SET_DEAL_MODELCONDTION);//回滚数据库记录
//				}
//				Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_MODELCONDTION),false); 
//				icount = 0;
//				listEndTime.clear(); listDuration.clear(); listGuId.clear();
//			}
//		}
//	}
//	if (0!=icount)
//	{
//		mQtOpt->QtbindValue(0,listEndTime);
//		mQtOpt->QtbindValue(1,listDuration);
//		mQtOpt->QtbindValue(2,listGuId);
//		nErr = mQtOpt->QtExecBatch();
//		if(!nErr)
//		{
//			Aos_WriteLog_D("RsltModelConditionUpBackInRsdb err!");
//			nErr = stmtTransRollback(CON_SET_DEAL_MODELCONDTION);//回滚数据库记录
//		}
//		nErr = stmtHandSubmit(CON_SET_DEAL_MODELCONDTION);
//		if(!nErr)
//		{
//			stmtTransRollback(CON_SET_DEAL_MODELCONDTION);//回滚数据库记录
//		}
//		icount = 0;
//	}
//
//	return nErr;
//}
bool AlarmSetDeal::RsltModelConditionInToRsdb()
{
    bool nErr = true;
    MapStringToAlarmModelConditionRst_It it;
    AlarmModelConditionRst  * rslt = NULL;

    std::string guId,beginTime,endTime;
    QVariantList listGuId,listConId,listBeginTime,listEndTime,listDuration,listIsHistory;
    int isHistory = 0;
    double duration = 0;
    int icount = 0;
    int ipos = 0;
    Aos_Assert_R(Util::QtConnect(mQtOpt), false);
    Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_MODELCONDTION),false);
    //Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELCONDTION, g_strRsltConditionInSQL), false);
    if (SQL_SERVERCE==mQtOpt->m_strRsdbType)
    {
        Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELCONDTION, g_strRsltConditionInSQL), false);
    }
    else if (ORACLE==mQtOpt->m_strRsdbType)
    {
        Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELCONDTION, g_strOrcRsltConditionInSQL), false);
    }
    else
    {
        Aos_Assert_S("关系数据库没配对应类型");
        stmtHandCloseStream(CON_SET_DEAL_MODELCONDTION);
        return false;
    }
    it = mMapAlarmModelConditionRst.begin();
    for (;it!= mMapAlarmModelConditionRst.end();++it)
    {
        ipos++;
        rslt = it->second;
        if(rslt->mModelIdTest=="4_1gj")
            int i=100;
        /*if(rslt->mModelIdTest!="4_1gj")
            continue;*/
        if ((rslt->mCondtionDate->m_curValue ==rslt->mCondtionDate->m_lastValue
             &&rslt->mCondtionDate->m_isInto
             &&rslt->mCondtionDate->m_TimeLong >=rslt->mCondtionDate->m_deaBand)
                ||(rslt->mCondtionDate->m_curValue !=rslt->mCondtionDate->m_lastValue
                   &&rslt->mCondtionDate->m_lastisInto
                   &&rslt->mCondtionDate->m_LastTimeLong >=rslt->mCondtionDate->m_deaBand))
        {
            if(rslt->mCondtionDate->m_curValue ==rslt->mCondtionDate->m_lastValue
                    &&rslt->mCondtionDate->m_isInto
                    &&rslt->mCondtionDate->m_TimeLong >=rslt->mCondtionDate->m_deaBand)
            {
                guId = rslt->mCondtionDate->m_id;
                beginTime = PubOpt::SystemOpt::DateTmToStr(rslt->mCondtionDate->m_StartTime,0);
                endTime = PubOpt::SystemOpt::DateTmToStr(rslt->mCondtionDate->m_EndTime,0);
                duration = rslt->mCondtionDate->m_TimeLong;
            }
            else
            {
                guId = rslt->mCondtionDate->m_lastId;
                beginTime = PubOpt::SystemOpt::DateTmToStr(rslt->mCondtionDate->m_LastStartTime,0);
                endTime = PubOpt::SystemOpt::DateTmToStr(rslt->mCondtionDate->m_LastEndTime,0);
                duration = rslt->mCondtionDate->m_TimeLong;
                duration = rslt->mCondtionDate->m_LastTimeLong;
            }
            if (rslt->mCondId.empty())
            {
                //listConId<<QVariant(QVariant::String);
                continue;
            }
            if(guId.empty()) continue;
            listConId<<QString(rslt->mCondId.c_str());
            listGuId<<QString(guId.c_str());
            listBeginTime<<QString(beginTime.c_str());
            listEndTime<<QString(endTime.c_str());
            listDuration<<duration;
            listIsHistory<<isHistory;

            if(rslt->mCondtionDate->m_curValue ==rslt->mCondtionDate->m_lastValue
                    &&rslt->mCondtionDate->m_isInto
                    &&rslt->mCondtionDate->m_TimeLong >=rslt->mCondtionDate->m_deaBand)
            {
                rslt->mCondtionDate->m_perId = rslt->mCondtionDate->m_id;  //插入新纪录,上条记录更新
                rslt->mCondtionDate->m_perValue = rslt->mCondtionDate->m_curValue;
                rslt->mCondtionDate->m_perStartTime = rslt->mCondtionDate->m_StartTime;
                rslt->mCondtionDate->m_perEndTime = rslt->mCondtionDate->m_EndTime;
                rslt->mCondtionDate->m_isInto = false;
            }
            else
            {
                rslt->mCondtionDate->m_perId = rslt->mCondtionDate->m_lastId;   //插入新纪录,上条记录更新
                rslt->mCondtionDate->m_perValue = rslt->mCondtionDate->m_lastValue;
                rslt->mCondtionDate->m_perStartTime = rslt->mCondtionDate->m_LastStartTime;
                rslt->mCondtionDate->m_perEndTime = rslt->mCondtionDate->m_LastEndTime;
                rslt->mCondtionDate->m_lastisInto = false;
            }
            icount++;
            if (CON_RSLT_SIZE==icount)
            {
                mQtOpt->QtbindValue(0,listGuId);
                mQtOpt->QtbindValue(1,listConId);
                mQtOpt->QtbindValue(2,listBeginTime);
                mQtOpt->QtbindValue(3,listEndTime);
                mQtOpt->QtbindValue(4,listDuration);
                mQtOpt->QtbindValue(5,listIsHistory);
                nErr = mQtOpt->QtExecBatch();
                if(!nErr)
                {
                    Aos_WriteLog_D("2000RsltModelConditionInToRsdb err!");
                    nErr = stmtTransRollback(CON_SET_DEAL_MODELCONDTION);//回滚数据库记录
                }
                nErr = stmtHandSubmit(CON_SET_DEAL_MODELCONDTION);
                if(!nErr)
                {
                    RollbackCondition(ipos);   //回滚内存记录
                    stmtTransRollback(CON_SET_DEAL_MODELCONDTION);//回滚数据库记录
                }
                stmtHandCloseStream(CON_SET_DEAL_MODELCONDTION);
                Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_MODELCONDTION),false);
                if (SQL_SERVERCE==mQtOpt->m_strRsdbType)
                {
                    Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELCONDTION, g_strRsltConditionInSQL), false);
                }
                else if (ORACLE==mQtOpt->m_strRsdbType)
                {
                    Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELCONDTION, g_strOrcRsltConditionInSQL), false);
                }
                else
                {
                    Aos_Assert_S("关系数据库没配对应类型");
                    stmtHandCloseStream(CON_SET_DEAL_MODELCONDTION);
                    return false;
                }
                icount = 0;
                listGuId.clear(); listConId.clear(); listBeginTime.clear();
                listEndTime.clear(); listDuration.clear(); listIsHistory.clear();
            }
        }
    }
    if (0!=icount)
    {
        mQtOpt->QtbindValue(0,listGuId);
        mQtOpt->QtbindValue(1,listConId);
        mQtOpt->QtbindValue(2,listBeginTime);
        mQtOpt->QtbindValue(3,listEndTime);
        mQtOpt->QtbindValue(4,listDuration);
        mQtOpt->QtbindValue(5,listIsHistory);
        nErr = mQtOpt->QtExecBatch();
        if(!nErr)
        {
            Aos_WriteLog_D("RsltModelConditionInToRsdb err!");
            nErr = stmtTransRollback(CON_SET_DEAL_MODELCONDTION);//回滚数据库记录
        }
        nErr = stmtHandSubmit(CON_SET_DEAL_MODELCONDTION);
        if(!nErr)
        {
            RollbackCondition(ipos);   //回滚内存记录
            stmtTransRollback(CON_SET_DEAL_MODELCONDTION);//回滚数据库记录
        }
        stmtHandCloseStream(CON_SET_DEAL_MODELCONDTION);
        icount = 0;
    }
    nErr = stmtHandSubmit(CON_SET_DEAL_MODELCONDTION);
    stmtHandCloseStream(CON_SET_DEAL_MODELCONDTION);
    return nErr;
}

bool AlarmSetDeal::RsltModelConditionUpBackInRsdb()
{
    bool nErr = true;
    MapStringToAlarmModelConditionRst_It it;
    AlarmModelConditionRst  * rslt = NULL;

    std::string guId,endTime,strerr;
    std::vector<std::string> vecguId,vecendTime,vecCondId;
    QVariantList listGuId,listEndTime,listDuration;
    double duration = 0;
    int icount = 0;
    Aos_Assert_R(Util::QtConnect(mQtOpt), false);
    Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_MODELCONDTION),false);
    //Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELCONDTION, g_strRsltConditionUpBackInSQL), false);
    if (SQL_SERVERCE==mQtOpt->m_strRsdbType)
    {
        Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELCONDTION, g_strRsltConditionUpBackInSQL), false);
    }
    else if (ORACLE==mQtOpt->m_strRsdbType)
    {
        Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELCONDTION, g_strOrcRsltConditionUpBackInSQL), false);
    }
    else
    {
        Aos_Assert_S("关系数据库没配对应类型");
        stmtHandCloseStream(CON_SET_DEAL_MODELCONDTION);
        return false;
    }
    it = mMapAlarmModelConditionRst.begin();
    for (;it!= mMapAlarmModelConditionRst.end();++it)
    {
        rslt = it->second;
        if(rslt->mCondId=="4_zc_yxms")
            int i=100;
        if(rslt->mModelIdTest=="4_1gj")
            int i=100;
        /*if(rslt->mModelIdTest!="4_1gj")
            continue;*/
        if ((rslt->mCondtionDate->m_curValue ==rslt->mCondtionDate->m_lastValue
             &&!(rslt->mCondtionDate->m_isInto)
             &&rslt->mCondtionDate->m_TimeLong >=rslt->mCondtionDate->m_deaBand)
                ||(rslt->mCondtionDate->m_curValue !=rslt->mCondtionDate->m_lastValue
                   &&rslt->mCondtionDate->m_LastTimeLong <rslt->mCondtionDate->m_deaBand)
                ||(rslt->mCondtionDate->m_curValue !=rslt->mCondtionDate->m_lastValue
                   &&rslt->mCondtionDate->m_LastTimeLong >=rslt->mCondtionDate->m_deaBand)
                &&(!rslt->mCondtionDate->m_lastisInto))
        {


            if(rslt->mCondtionDate->m_curValue ==rslt->mCondtionDate->m_lastValue
                    &&!rslt->mCondtionDate->m_isInto
                    &&rslt->mCondtionDate->m_TimeLong >=rslt->mCondtionDate->m_deaBand)
            {
                if (rslt->mCondtionDate->m_curValue=="")
                    continue;
                guId = rslt->mCondtionDate->m_id;
                endTime = PubOpt::SystemOpt::DateTmToStr(rslt->mCondtionDate->m_EndTime,0);
                duration = rslt->mCondtionDate->m_TimeLong;
                strerr=PubOpt::StringOpt::StringFormat("1mCondId:%s,guId:%s,endTime:%s,duration:%f",rslt->mCondId.c_str(),guId.c_str(),endTime.c_str(),duration);

            }
            else if ((rslt->mCondtionDate->m_curValue !=rslt->mCondtionDate->m_lastValue
                      &&rslt->mCondtionDate->m_LastTimeLong <rslt->mCondtionDate->m_deaBand
                      &&rslt->mCondtionDate->m_LastTimeLong >= 0))
            {
                guId = rslt->mCondtionDate->m_perId;
                endTime = PubOpt::SystemOpt::DateTmToStr(rslt->mCondtionDate->m_EndTime,0);

                if (rslt->mCondtionDate->m_curValue==rslt->mCondtionDate->m_perValue)
                {
                    rslt->mCondtionDate->m_id = rslt->mCondtionDate->m_perId;
                    rslt->mCondtionDate->m_isInto=false;
                    duration = rslt->mCondtionDate->m_EndTime-rslt->mCondtionDate->m_perStartTime;
                    strerr=PubOpt::StringOpt::StringFormat("2mCondId:%s,guId:%s,endTime:%s,duration:%f",rslt->mCondId.c_str(),guId.c_str(),endTime.c_str(),duration);
                }
                else
                {
                    //duration = rslt->mCondtionDate->m_TimeLong;
                    duration = rslt->mCondtionDate->m_LastTimeLong;
                    strerr=PubOpt::StringOpt::StringFormat("mCondId:%s,guId:%s,endTime:%s,duration:%f",rslt->mCondId.c_str(),guId.c_str(),endTime.c_str(),duration);
                }
            }
            else if (rslt->mCondtionDate->m_curValue !=rslt->mCondtionDate->m_lastValue
                     &&rslt->mCondtionDate->m_LastTimeLong >=rslt->mCondtionDate->m_deaBand
                     &&(!rslt->mCondtionDate->m_lastisInto))
            {
                if (rslt->mCondtionDate->m_lastValue=="")
                    continue;
                guId = rslt->mCondtionDate->m_perId;
                endTime = PubOpt::SystemOpt::DateTmToStr(rslt->mCondtionDate->m_LastEndTime,0);
                duration = rslt->mCondtionDate->m_EndTime-rslt->mCondtionDate->m_perStartTime;
                strerr=PubOpt::StringOpt::StringFormat("4mCondId:%s,guId:%s,endTime:%s,duration:%f,m_EndTime:%d,m_perStartTime:%d",rslt->mCondId.c_str(),guId.c_str(),endTime.c_str(),duration,rslt->mCondtionDate->m_EndTime,rslt->mCondtionDate->m_perStartTime);
            }

            listEndTime<<QString(endTime.c_str());
            listDuration<<duration;
            listGuId<<QString(guId.c_str());
            icount++;
            if (duration<0)
            {
                Aos_Assert_S("duration异常");
                strerr=PubOpt::StringOpt::StringFormat("@@@mCondId:%s,guId:%s,endTime:%s,duration:%f,m_EndTime:%s,m_perStartTime:%s",rslt->mCondId.c_str(),guId.c_str(),endTime.c_str(),duration);
            }
            //vecguId.push_back(guId);
            //vecendTime.push_back(endTime);
            strerr=PubOpt::StringOpt::StringFormat("mCondId:%s,guId:%s,endTime:%s,duration:%f",rslt->mCondId.c_str(),guId.c_str(),endTime.c_str(),duration);
            vecCondId.push_back(strerr);
            //if (CON_RSLT_SIZE==icount)
            if (1==icount)
            {
                mQtOpt->QtbindValue(0,listEndTime);
                mQtOpt->QtbindValue(1,listDuration);
                mQtOpt->QtbindValue(2,listGuId);
                nErr = mQtOpt->QtExecBatch();
                if(!nErr)
                {
                    Aos_WriteLog_D("2000RsltModelConditionUpBackInRsdb err!");
                    for (std::vector<std::string>::iterator it=vecCondId.begin();it!=vecCondId.end();it++)
                    {
                        std::string strtmp;
                        strtmp = *it;
                        Aos_WriteLog_D(strtmp.c_str());
                    }
                    vecCondId.clear();
                    nErr = stmtTransRollback(CON_SET_DEAL_MODELCONDTION);//回滚数据库记录
                }
                nErr = stmtHandSubmit(CON_SET_DEAL_MODELCONDTION);
                if(!nErr)
                {
                    stmtTransRollback(CON_SET_DEAL_MODELCONDTION);//回滚数据库记录
                }
                stmtHandCloseStream(CON_SET_DEAL_MODELCONDTION);
                Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_MODELCONDTION),false);
                if (SQL_SERVERCE==mQtOpt->m_strRsdbType)
                {
                    Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELCONDTION, g_strRsltConditionUpBackInSQL), false);
                }
                else if (ORACLE==mQtOpt->m_strRsdbType)
                {
                    Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELCONDTION, g_strOrcRsltConditionUpBackInSQL), false);
                }
                else
                {
                    Aos_Assert_S("关系数据库没配对应类型");
                    stmtHandCloseStream(CON_SET_DEAL_MODELCONDTION);
                    return false;
                }
                icount = 0;
                listEndTime.clear(); listDuration.clear(); listGuId.clear();
            }
        }
    }
    if (0!=icount)
    {
        mQtOpt->QtbindValue(0,listEndTime);
        mQtOpt->QtbindValue(1,listDuration);
        mQtOpt->QtbindValue(2,listGuId);
        nErr = mQtOpt->QtExecBatch();
        if(!nErr)
        {
            Aos_WriteLog_D("RsltModelConditionUpBackInRsdb err!");
            Aos_WriteLog_D(mQtOpt->GetErrorMessage().c_str());
            for (std::vector<std::string>::iterator it=vecCondId.begin();it!=vecCondId.end();it++)
            {
                std::string strtmp;
                strtmp = *it;
                Aos_WriteLog_D(strtmp.c_str());
            }
            nErr = stmtTransRollback(CON_SET_DEAL_MODELCONDTION);//回滚数据库记录
        }
        nErr = stmtHandSubmit(CON_SET_DEAL_MODELCONDTION);
        if(!nErr)
        {
            stmtTransRollback(CON_SET_DEAL_MODELCONDTION);//回滚数据库记录
        }
        stmtHandCloseStream(CON_SET_DEAL_MODELCONDTION);
        icount = 0;
    }
    nErr = stmtHandSubmit(CON_SET_DEAL_MODELCONDTION);
    stmtHandCloseStream(CON_SET_DEAL_MODELCONDTION);
    return nErr;
}
bool AlarmSetDeal::RsltModelCosineInToRsdb()
{
    bool nErr = true;
    MapStringToAlarmModelCosineRst_It it;
    AlarmModelCosineRst  * rslt = NULL;
    CDCosineCfg* cfg_Cosine = NULL;
    MapStringToAlaramCosineCfg_It cfg_it;

    std::string guId,faultId,modelId,faultName,faultCauses,faultAnalyse,faultGuide,faultCode,faultType,beginTime,endTime;
    std::string eventState;
    QVariantList listGuId,listFaultId,listModelId,listFaultName,listFaultCauses,listFaultAnalyse,listXds,listEventState;
    QVariantList listFaultGuide,listFaultCode,listFaultType,listBeginTime,listEndTime,listDuration,listIsHistory;
    double duration = 0,xds=0;
    int icount = 0;
    int ipos = 0;
    Aos_Assert_R(Util::QtConnect(mQtOpt), false);
    Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_MODELCOSINE),false);
    //Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELCOSINE, g_strRsltCosineInSQL), false);
    if (SQL_SERVERCE==mQtOpt->m_strRsdbType)
    {
        Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELCOSINE, g_strRsltCosineInSQL), false);
    }
    else if (ORACLE==mQtOpt->m_strRsdbType)
    {
        Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELCOSINE, g_strOrcRsltCosineInSQL), false);
    }
    else
    {
        Aos_Assert_S("关系数据库没配对应类型");
        stmtHandCloseStream(CON_SET_DEAL_MODELCOSINE);
        return false;
    }
    it = mMapAlarmModelCosineRst.begin();
    for (;it!= mMapAlarmModelCosineRst.end();++it)
    {
        ipos++;
        rslt = it->second;
        /*if (rslt->mStrModelId =="67c25ae4-64ce-4e9a-9ed8-095a27fc9dcd")
        {
            int temp=100;
        }
        else
        {
            continue;
        }*/
        if(rslt->mapRlstAlarmCosineCfg.size()==0)
            continue;
        if ((rslt->mCosineDate->m_curValue ==rslt->mCosineDate->m_lastValue
             &&rslt->mCosineDate->m_isInto
             &&rslt->mCosineDate->m_TimeLong >=rslt->mCosineDate->m_deaBand)
                ||(rslt->mCosineDate->m_curValue !=rslt->mCosineDate->m_lastValue
                   &&rslt->mCosineDate->m_lastisInto
                   &&rslt->mCosineDate->m_LastTimeLong >=rslt->mCosineDate->m_deaBand))
        {
            modelId = rslt->mStrModelId;
            //xds = rslt->mXsd;
            if(rslt->mCosineDate->m_curValue ==rslt->mCosineDate->m_lastValue
                    &&rslt->mCosineDate->m_isInto
                    &&rslt->mCosineDate->m_TimeLong >=rslt->mCosineDate->m_deaBand)
            {
                if(rslt->mCosineDate->m_curValue=="")
                {
                    rslt->mCosineDate->m_perId = "";
                    rslt->mCosineDate->m_isInto = false;
                    continue;
                }
                /*Aos_WriteLog_D("001!");
                Aos_WriteLog(PubOpt::StringOpt::StringFormat("m_curValue:%s",rslt->mCosineDate->m_curValue.c_str()).c_str());
                Aos_WriteLog(PubOpt::StringOpt::StringFormat("m_StartTime:%ld",rslt->mCosineDate->m_StartTime ).c_str());
                Aos_WriteLog(PubOpt::StringOpt::StringFormat("m_EndTime:%ld",rslt->mCosineDate->m_EndTime ).c_str());
                Aos_WriteLog(PubOpt::StringOpt::StringFormat("guId:%s",rslt->mCosineDate->m_id.c_str() ).c_str());*/
                guId = rslt->mCosineDate->m_id;
                beginTime = PubOpt::SystemOpt::DateTmToStr(rslt->mCosineDate->m_StartTime,0);
                endTime = PubOpt::SystemOpt::DateTmToStr(rslt->mCosineDate->m_EndTime,0);
                duration = rslt->mCosineDate->m_TimeLong;
                xds = rslt->mCosineDate->m_curxsd;
                //rslt->mCosineDate->m_xsd = xds;
                //Aos_WriteLog(PubOpt::StringOpt::StringFormat("StartTime:%s",beginTime.c_str()).c_str());
                //Aos_WriteLog(PubOpt::StringOpt::StringFormat("EndTime:%s",endTime.c_str()).c_str());
                if (NO_ALARM==rslt->mCosineId)
                {
                    faultId = "";
                    faultName = "";
                    faultCauses = "";
                    faultAnalyse = "";
                    faultGuide = "";
                    faultCode = "";
                }
                else
                {
                    cfg_it = rslt->mapRlstAlarmCosineCfg.find(rslt->mCosineId);
                    if (cfg_it!=rslt->mapRlstAlarmCosineCfg.end())
                    {
                        cfg_Cosine = cfg_it->second;
                        faultId = cfg_Cosine->mId;
                        faultName = cfg_Cosine->mName;
                        faultCauses = cfg_Cosine->mCauses;
                        faultAnalyse = cfg_Cosine->mAnalye;
                        faultGuide = cfg_Cosine->mGuid;
                    }
                    else
                    {
                        faultId = "";
                        faultName = "";
                        faultCauses = "";
                        faultAnalyse = "";
                        faultGuide = "";
                        faultCode = "";
                    }
                }
                faultCode = rslt->mstrSn + PubOpt::SystemOpt::DateTmToStr(rslt->mCosineDate->m_StartTime,1);
            }
            else
            {
                if(rslt->mCosineDate->m_lastValue=="")
                {
                    rslt->mCosineDate->m_perId = "";
                    rslt->mCosineDate->m_lastisInto = false;
                    continue;
                }
                Aos_WriteLog_D("002!");
                Aos_WriteLog(PubOpt::StringOpt::StringFormat("m_curValue:%s",rslt->mCosineDate->m_curValue.c_str()).c_str());
                Aos_WriteLog(PubOpt::StringOpt::StringFormat("m_lastValue:%s",rslt->mCosineDate->m_lastValue.c_str()).c_str());
                Aos_WriteLog(PubOpt::StringOpt::StringFormat("m_StartTime:%ld",rslt->mCosineDate->m_LastStartTime ).c_str());
                Aos_WriteLog(PubOpt::StringOpt::StringFormat("m_EndTime:%ld",rslt->mCosineDate->m_LastEndTime ).c_str());
                Aos_WriteLog(PubOpt::StringOpt::StringFormat("guId:%s",rslt->mCosineDate->m_lastId.c_str()).c_str());
                guId = rslt->mCosineDate->m_lastId;
                beginTime = PubOpt::SystemOpt::DateTmToStr(rslt->mCosineDate->m_LastStartTime,0);
                endTime = PubOpt::SystemOpt::DateTmToStr(rslt->mCosineDate->m_LastEndTime,0);
                duration = rslt->mCosineDate->m_LastTimeLong;
                xds = rslt->mCosineDate->m_lastxsd;
                //rslt->mCosineDate->m_xsd = xds;
                Aos_WriteLog(PubOpt::StringOpt::StringFormat("StartTime:%s",beginTime.c_str()).c_str());
                Aos_WriteLog(PubOpt::StringOpt::StringFormat("EndTime:%s",endTime.c_str()).c_str());
                if (NO_ALARM==rslt->mLastCosineId)
                {
                    faultId = "";
                    faultName = "";
                    faultCauses = "";
                    faultAnalyse = "";
                    faultGuide = "";
                    faultCode = "";
                }
                else
                {
                    cfg_it = rslt->mapRlstAlarmCosineCfg.find(rslt->mLastCosineId);
                    if (cfg_it!=rslt->mapRlstAlarmCosineCfg.end())
                    {
                        cfg_Cosine = cfg_it->second;
                        faultId = cfg_Cosine->mId;
                        faultName = cfg_Cosine->mName;
                        faultCauses = cfg_Cosine->mCauses;
                        faultAnalyse = cfg_Cosine->mAnalye;
                        faultGuide = cfg_Cosine->mGuid;
                    }
                    else
                    {
                        faultId = "";
                        faultName = "";
                        faultCauses = "";
                        faultAnalyse = "";
                        faultGuide = "";
                        faultCode = "";
                    }
                    /*faultId = rslt->mlastConsine->mId;
                    faultName = rslt->mlastConsine->mName;
                    faultCauses = rslt->mlastConsine->mCauses;
                    faultAnalyse = rslt->mlastConsine->mAnalye;
                    faultGuide = rslt->mlastConsine->mGuid;*/
                    //faultCode = rslt->mstrSn + PubOpt::SystemOpt::DateTmToStr(rslt->mCosineDate->m_LastStartTime,1);
                }
                faultCode = rslt->mstrSn + PubOpt::SystemOpt::DateTmToStr(rslt->mCosineDate->m_LastStartTime,1);
                //Aos_WriteLog_D("0022!");
            }

            if (NO_ALARM==rslt->mCosineId)
            {
                faultType = "未关联疑似故障";
                eventState = "0";
            }
            else
            {
                faultType = "疑似故障";
                eventState = "1";
            }
            if(guId.empty()) continue;
            //Aos_WriteLog_D("003!");
            listGuId<<QString::fromLocal8Bit(guId.c_str());
            if (faultId.empty())
            {
                listFaultId<<QVariant(QVariant::String);
            }
            else
            {
                listFaultId<<QString::fromLocal8Bit(faultId.c_str());
            }

            listModelId<<QString::fromLocal8Bit(modelId.c_str());
            if(faultName.empty())
                listFaultName<<QVariant(QVariant::String);
            else
                listFaultName<<QString::fromLocal8Bit(faultName.c_str());

            listBeginTime<<QString(beginTime.c_str());
            listEndTime<<QString(endTime.c_str());
            listDuration<<duration;

            if(faultCauses.empty())
                listFaultCauses<<QVariant(QVariant::String);
            else
                listFaultCauses<<QString::fromLocal8Bit(faultCauses.c_str());

            if(faultAnalyse.empty())
                listFaultAnalyse<<QVariant(QVariant::String);
            else
                listFaultAnalyse<<QString::fromLocal8Bit(faultAnalyse.c_str());

            if(faultGuide.empty())
                listFaultGuide<<QVariant(QVariant::String);
            else
                listFaultGuide<<QString::fromLocal8Bit(faultGuide.c_str());

            if(faultCode.empty())
                listFaultCode<<QVariant(QVariant::String);
            else
                listFaultCode<<QString::fromLocal8Bit(faultCode.c_str());

            if(xds<0)
                listXds<<QVariant(QVariant::Double);
            else
                listXds<<xds;

            if(faultType.empty())
                listFaultType<<QVariant(QVariant::String);
            else
                listFaultType<<QString::fromLocal8Bit(faultType.c_str());

            listEventState<<QString::fromLocal8Bit(eventState.c_str());

            icount++;
            //Aos_WriteLog_D("004!");
            if(rslt->mCosineDate->m_curValue ==rslt->mCosineDate->m_lastValue
                    &&rslt->mCosineDate->m_isInto
                    &&rslt->mCosineDate->m_TimeLong >=rslt->mCosineDate->m_deaBand)
            {
                rslt->mCosineDate->m_perId = rslt->mCosineDate->m_id;  //插入新纪录,上条记录更新
                rslt->mCosineDate->m_perValue = rslt->mCosineDate->m_curValue;
                rslt->mCosineDate->m_perStartTime = rslt->mCosineDate->m_StartTime;
                rslt->mCosineDate->m_perEndTime = rslt->mCosineDate->m_EndTime;
                rslt->mCosineDate->m_isInto = false;
            }
            else
            {
                rslt->mCosineDate->m_perId = rslt->mCosineDate->m_lastId;   //插入新纪录,上条记录更新
                rslt->mCosineDate->m_perValue = rslt->mCosineDate->m_lastValue;
                rslt->mCosineDate->m_perStartTime = rslt->mCosineDate->m_LastStartTime;
                rslt->mCosineDate->m_perEndTime = rslt->mCosineDate->m_LastEndTime;
                rslt->mCosineDate->m_lastisInto = false;
            }
            //icount++;
            if (CON_RSLT_SIZE==icount)  //CON_RSLT_SIZE
            {
                mQtOpt->QtbindValue(0,listGuId);
                mQtOpt->QtbindValue(1,listFaultId);
                mQtOpt->QtbindValue(2,listModelId);
                mQtOpt->QtbindValue(3,listFaultName);
                mQtOpt->QtbindValue(4,listBeginTime);
                mQtOpt->QtbindValue(5,listEndTime);
                mQtOpt->QtbindValue(6,listDuration);
                mQtOpt->QtbindValue(7,listFaultCauses);
                mQtOpt->QtbindValue(8,listFaultAnalyse);
                mQtOpt->QtbindValue(9,listFaultGuide);
                mQtOpt->QtbindValue(10,listEventState);
                mQtOpt->QtbindValue(11,listFaultCode);
                mQtOpt->QtbindValue(12,listXds);
                mQtOpt->QtbindValue(13,listFaultType);
                Aos_WriteLog_D("005!");
                mQtOpt->QtExecBatch();
                nErr = mQtOpt->QtExecBatch();
                if(!nErr)
                {
                    Aos_WriteLog_D("2000RsltModelCosineInToRsdb err!");
                    nErr = stmtTransRollback(CON_SET_DEAL_MODELCOSINE);//回滚数据库记录
                }
                nErr = stmtHandSubmit(CON_SET_DEAL_MODELCOSINE);
                if(!nErr)
                {
                    RollbackCosione(ipos);   //回滚内存记录
                    stmtTransRollback(CON_SET_DEAL_MODELCOSINE);//回滚数据库记录
                }
                stmtHandCloseStream(CON_SET_DEAL_MODELCOSINE);
                Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_MODELCOSINE),false);
                if (SQL_SERVERCE==mQtOpt->m_strRsdbType)
                {
                    Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELCOSINE, g_strRsltCosineInSQL), false);
                }
                else if (ORACLE==mQtOpt->m_strRsdbType)
                {
                    Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELCOSINE, g_strOrcRsltCosineInSQL), false);
                }
                else
                {
                    Aos_Assert_S("关系数据库没配对应类型");
                    stmtHandCloseStream(CON_SET_DEAL_MODELCOSINE);
                    return false;
                }
                icount = 0;
                listGuId.clear(); listFaultId.clear(); listModelId.clear();
                listFaultName.clear(); listBeginTime.clear(); listEndTime.clear();
                listDuration.clear(); listFaultCauses.clear(); listFaultAnalyse.clear();
                listFaultGuide.clear(); listFaultCode.clear(); listXds.clear();
                listFaultType.clear();
            }
        }
    }
    if (0!=icount)
    {
        mQtOpt->QtbindValue(0,listGuId);
        mQtOpt->QtbindValue(1,listFaultId);
        mQtOpt->QtbindValue(2,listModelId);
        mQtOpt->QtbindValue(3,listFaultName);
        mQtOpt->QtbindValue(4,listBeginTime);
        mQtOpt->QtbindValue(5,listEndTime);
        mQtOpt->QtbindValue(6,listDuration);
        mQtOpt->QtbindValue(7,listFaultCauses);
        mQtOpt->QtbindValue(8,listFaultAnalyse);
        mQtOpt->QtbindValue(9,listFaultGuide);
        mQtOpt->QtbindValue(10,listEventState);
        mQtOpt->QtbindValue(11,listFaultCode);
        mQtOpt->QtbindValue(12,listXds);
        mQtOpt->QtbindValue(13,listFaultType);
        nErr = mQtOpt->QtExecBatch();
        if(!nErr)
        {
            Aos_WriteLog_D("RsltModelCosineInToRsdb err!");
            nErr = stmtTransRollback(CON_SET_DEAL_MODELCOSINE);//回滚数据库记录
        }
        nErr = stmtHandSubmit(CON_SET_DEAL_MODELCOSINE);
        if(!nErr)
        {
            RollbackCosione(ipos);   //回滚内存记录
            stmtTransRollback(CON_SET_DEAL_MODELCOSINE);//回滚数据库记录
        }
        stmtHandCloseStream(CON_SET_DEAL_MODELCOSINE);
        icount = 0;
    }
    nErr = stmtHandSubmit(CON_SET_DEAL_MODELCOSINE);
    stmtHandCloseStream(CON_SET_DEAL_MODELCOSINE);
    return nErr;
}

bool AlarmSetDeal::RsltModelCosineUpBackInRsdb()
{
    bool nErr = true;
    MapStringToAlarmModelCosineRst_It it;
    AlarmModelCosineRst  * rslt = NULL;
    //char conditionId[64];
    double duration = 0;
    std::string endTime,guId;
    QVariantList listDuration,listEndTime,listGuId;
    int icount = 0,ipos=0;
    Aos_Assert_R(Util::QtConnect(mQtOpt), false);
    Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_MODELCOSINE),false);
    //Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELCOSINE, g_strRslCosineUpBackInSQL), false);
    if (SQL_SERVERCE==mQtOpt->m_strRsdbType)
    {
        Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELCOSINE, g_strRslCosineUpBackInSQL), false);
    }
    else if (ORACLE==mQtOpt->m_strRsdbType)
    {
        Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELCOSINE, g_strOrcRslCosineUpBackInSQL), false);
    }
    else
    {
        Aos_Assert_S("关系数据库没配对应类型");
        stmtHandCloseStream(CON_SET_DEAL_MODELCOSINE);
        return false;
    }
    it = mMapAlarmModelCosineRst.begin();
    for (;it!= mMapAlarmModelCosineRst.end();++it)
    {
        rslt = it->second;
        if (rslt->mStrModelId =="4_ycfj1bt")
        {
            int temp=100;
        }
        /*else
        {
            continue;
        }*/
        if(rslt->mapRlstAlarmCosineCfg.size()==0)
            continue;

        if(rslt->mCosineDate->m_curValue ==rslt->mCosineDate->m_lastValue
                &&(!rslt->mCosineDate->m_isInto))

        {
            if (rslt->mCosineDate->m_curValue=="")
            {
                continue;
            }
            guId = rslt->mCosineDate->m_id;
            endTime = PubOpt::SystemOpt::DateTmToStr(rslt->mCosineDate->m_EndTime,0);
            duration = rslt->mCosineDate->m_TimeLong;

        }
        else if ((rslt->mCosineDate->m_curValue !=rslt->mCosineDate->m_lastValue)
                 &&(rslt->mCosineDate->m_LastTimeLong <rslt->mCosineDate->m_deaBand))
        {
            if (""==rslt->mCosineDate->m_perId)
            {
                continue;
            }
            guId = rslt->mCosineDate->m_perId;
            endTime = PubOpt::SystemOpt::DateTmToStr(rslt->mCosineDate->m_EndTime,0);
            if ((rslt->mCosineDate->m_curValue==rslt->mCosineDate->m_perValue)
                    &&(rslt->mCosineDate->m_xsd ==rslt->mCosineDate->m_curxsd))
            {
                rslt->mCosineDate->m_id = rslt->mCosineDate->m_perId;
                rslt->mCosineDate->m_isInto=false;
                duration = rslt->mCosineDate->m_EndTime-rslt->mCosineDate->m_perStartTime;
                rslt->mCosineDate->m_StartTime = rslt->mCosineDate->m_perStartTime;
            }
            else
                duration = rslt->mCosineDate->m_EndTime-rslt->mCosineDate->m_perStartTime;
        }
        else if ((rslt->mCosineDate->m_curValue ==rslt->mCosineDate->m_lastValue
                  &&rslt->mCosineDate->m_lastxsd!=rslt->mCosineDate->m_curxsd)
                 &&(rslt->mCosineDate->m_LastTimeLong <rslt->mCosineDate->m_deaBand))
        {
            if (""==rslt->mCosineDate->m_perId)
            {
                continue;
            }
            if (rslt->mCosineDate->m_lastValue=="")
            {
                continue;
            }
            guId = rslt->mCosineDate->m_perId;
            endTime = PubOpt::SystemOpt::DateTmToStr(rslt->mCosineDate->m_EndTime,0);
            if ((rslt->mCosineDate->m_curValue==rslt->mCosineDate->m_perValue)
                    &&(rslt->mCosineDate->m_xsd ==rslt->mCosineDate->m_curxsd))
            {
                rslt->mCosineDate->m_id = rslt->mCosineDate->m_perId;
                rslt->mCosineDate->m_isInto=false;
                duration = rslt->mCosineDate->m_EndTime-rslt->mCosineDate->m_perStartTime;
                rslt->mCosineDate->m_StartTime = rslt->mCosineDate->m_perStartTime;
            }
            else
                duration = rslt->mCosineDate->m_EndTime-rslt->mCosineDate->m_perStartTime;
        }
        /*else if ((rslt->mCosineDate->m_curValue ==rslt->mCosineDate->m_lastValue
            &&rslt->mCosineDate->m_lastxsd!=rslt->mCosineDate->m_curxsd)
            &&(rslt->mCosineDate->m_LastTimeLong >rslt->mCosineDate->m_deaBand))
        {
            if (rslt->mCosineDate->m_lastValue=="")
            {
                continue;
            }
            if (""==rslt->mCosineDate->m_perId)
            {
                continue;
            }
            guId = rslt->mCosineDate->m_perId;
            endTime = PubOpt::SystemOpt::DateTmToStr(rslt->mCosineDate->m_EndTime,0);
            duration = rslt->mCosineDate->m_EndTime-rslt->mCosineDate->m_perStartTime;
        }*/

        else
        {
            if (rslt->mCosineDate->m_lastValue=="")
            {
                continue;
            }
            if (""==rslt->mCosineDate->m_perId)
            {
                continue;
            }
            if (rslt->mCosineDate->m_isInto==true&&
                    (rslt->mCosineDate->m_curValue ==rslt->mCosineDate->m_lastValue)
                    &&(rslt->mCosineDate->m_lastxsd ==rslt->mCosineDate->m_curxsd))//&&(rslt->mCosineDate->m_lastxsd ==rslt->mCosineDate->m_curxsd)
            {
                continue;
            }
            /*if ((rslt->mCosineDate->m_curValue !=rslt->mCosineDate->m_lastValue)
                &&(rslt->mCosineDate->m_LastTimeLong >rslt->mCosineDate->m_deaBand))
            {
                if (""==rslt->mCosineDate->m_lastValue)
                {
                    continue;
                }
            }*/
            guId = rslt->mCosineDate->m_perId;
            endTime = PubOpt::SystemOpt::DateTmToStr(rslt->mCosineDate->m_EndTime,0);
            duration = rslt->mCosineDate->m_EndTime-rslt->mCosineDate->m_perStartTime;
        }
        //else if (rslt->mCosineDate->m_curValue !=rslt->mCosineDate->m_lastValue
        //	&&rslt->mCosineDate->m_LastTimeLong >=rslt->mCosineDate->m_deaBand
        //	&&(!rslt->mCosineDate->m_lastisInto))
        //{
        //	if (rslt->mCosineDate->m_lastValue=="")
        //	{
        //		continue;
        //	}
        //	guId = rslt->mCosineDate->m_perId;
        //	endTime = PubOpt::SystemOpt::DateTmToStr(rslt->mCosineDate->m_LastEndTime,0);
        //	duration = rslt->mCosineDate->m_EndTime-rslt->mCosineDate->m_perStartTime;
        //}
        //else if ((rslt->mCosineDate->m_curValue ==rslt->mCosineDate->m_lastValue
        //	&&(rslt->mCosineDate->m_isPPDChange)))
        //	//&&rslt->mCosineDate->m_LastTimeLong >=rslt->mCosineDate->m_deaBand)&&(!rslt->mCosineDate->m_lastisInto)
        //{
        //	if (rslt->mCosineDate->m_curValue=="")
        //	{
        //		continue;
        //	}
        //	if ((rslt->mCosineDate->m_LastTimeLong >=rslt->mCosineDate->m_deaBand)
        //		&&(!rslt->mCosineDate->m_lastisInto))
        //	{
        //		guId = rslt->mCosineDate->m_perId;
        //		endTime = PubOpt::SystemOpt::DateTmToStr(rslt->mCosineDate->m_LastEndTime,0);
        //		duration = rslt->mCosineDate->m_EndTime-rslt->mCosineDate->m_perStartTime;
        //	}
        //	else if (rslt->mCosineDate->m_LastTimeLong <rslt->mCosineDate->m_deaBand)
        //	{
        //		if(rslt->mCosineDate->m_perId.empty()) continue;
        //		guId = rslt->mCosineDate->m_perId;
        //		endTime = PubOpt::SystemOpt::DateTmToStr(rslt->mCosineDate->m_LastEndTime,0);
        //		duration = rslt->mCosineDate->m_EndTime-rslt->mCosineDate->m_perStartTime;
        //	}
        //	else
        //		continue;
        //	rslt->mCosineDate->m_isPPDChange = false;
        //}
        listEndTime<<QString(endTime.c_str());
        listDuration<<duration;
        listGuId<<QString(guId.c_str());

        icount++;
        ipos++;
        if (CON_RSLT_SIZE==icount)
        {
            mQtOpt->QtbindValue(0,listEndTime);
            mQtOpt->QtbindValue(1,listDuration);
            mQtOpt->QtbindValue(2,listGuId);
            mQtOpt->QtExecBatch();
            nErr = stmtHandSubmit(CON_SET_DEAL_MODELCOSINE);
            if(!nErr)
            {
                RollbackCosione(ipos);   //回滚内存记录
                stmtTransRollback(CON_SET_DEAL_MODELCOSINE);//回滚数据库记录
            }
            stmtHandCloseStream(CON_SET_DEAL_MODELCOSINE);
            Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_MODELCOSINE),false);
            if (SQL_SERVERCE==mQtOpt->m_strRsdbType)
            {
                Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELCOSINE, g_strRslCosineUpBackInSQL), false);
            }
            else if (ORACLE==mQtOpt->m_strRsdbType)
            {
                Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELCOSINE, g_strOrcRslCosineUpBackInSQL), false);
            }
            else
            {
                Aos_Assert_S("关系数据库没配对应类型");
                stmtHandCloseStream(CON_SET_DEAL_MODELCOSINE);
                return false;
            }

            icount = 0;
            listEndTime.clear(); listDuration.clear(); listGuId.clear();
        }
    }
    if (0!=icount)
    {
        mQtOpt->QtbindValue(0,listEndTime);
        mQtOpt->QtbindValue(1,listDuration);
        mQtOpt->QtbindValue(2,listGuId);
        mQtOpt->QtExecBatch();
        nErr = stmtHandSubmit(CON_SET_DEAL_MODELCOSINE);
        if(!nErr)
        {
            RollbackCosione(ipos);   //回滚内存记录
            stmtTransRollback(CON_SET_DEAL_MODELCOSINE);//回滚数据库记录
        }
        stmtHandCloseStream(CON_SET_DEAL_MODELCOSINE);
        icount = 0;
    }
    nErr = stmtHandSubmit(CON_SET_DEAL_MODELCOSINE);
    stmtHandCloseStream(CON_SET_DEAL_MODELCOSINE);
    return nErr;
}
//bool AlarmSetDeal::RsltModelCosineInToRsdb()
//{
//	bool nErr = true;
//	MapStringToAlarmModelCosineRst_It it;
//	AlarmModelCosineRst  * rslt = NULL;
//	CDCosineCfg* cfg_Cosine = NULL;
//	MapStringToAlaramCosineCfg_It cfg_it;
//
//	std::string guId,faultId,modelId,faultName,faultCauses,faultAnalyse,faultGuide,faultCode,faultType,beginTime,endTime;
//	std::string eventState;
//	QVariantList listGuId,listFaultId,listModelId,listFaultName,listFaultCauses,listFaultAnalyse,listXds,listEventState;
//	QVariantList listFaultGuide,listFaultCode,listFaultType,listBeginTime,listEndTime,listDuration,listIsHistory;
//	double duration = 0,xds=0;
//	int icount = 0;
//	int ipos = 0;
//	Aos_Assert_R(Util::QtConnect(mQtOpt), false);
//	Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_MODELCOSINE),false);
//	Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELCOSINE, g_strRsltCosineInSQL), false);
//	it = mMapAlarmModelCosineRst.begin();
//	for (;it!= mMapAlarmModelCosineRst.end();++it)
//	{
//		ipos++;
//		rslt = it->second;
//		if (rslt->mStrModelId =="4_zc")
//		{
//			int temp=100;
//		}
//		else
//		{
//			continue;
//		}
//		if(rslt->mCosineDate->m_curValue==""||rslt->mCosineDate->m_lastValue==""||rslt->mapRlstAlarmCosineCfg.size()==0)
//			continue;
//		if ((rslt->mCosineDate->m_curValue ==rslt->mCosineDate->m_lastValue
//			&&rslt->mCosineDate->m_isInto
//			&&rslt->mCosineDate->m_TimeLong >=rslt->mCosineDate->m_deaBand)
//			||(rslt->mCosineDate->m_curValue !=rslt->mCosineDate->m_lastValue
//			&&rslt->mCosineDate->m_lastisInto
//			&&rslt->mCosineDate->m_LastTimeLong >=rslt->mCosineDate->m_deaBand))
//		{
//			modelId = rslt->mStrModelId;
//			xds = rslt->mXsd;
//			if(rslt->mCosineDate->m_curValue ==rslt->mCosineDate->m_lastValue
//				&&rslt->mCosineDate->m_isInto
//				&&rslt->mCosineDate->m_TimeLong >=rslt->mCosineDate->m_deaBand)
//			{
//				Aos_WriteLog_D("001!");
//				Aos_WriteLog(PubOpt::StringOpt::StringFormat("m_curValue:%s",rslt->mCosineDate->m_curValue.c_str()).c_str());
//				Aos_WriteLog(PubOpt::StringOpt::StringFormat("m_StartTime:%ld",rslt->mCosineDate->m_StartTime ).c_str());
//				Aos_WriteLog(PubOpt::StringOpt::StringFormat("m_EndTime:%ld",rslt->mCosineDate->m_EndTime ).c_str());
//				Aos_WriteLog(PubOpt::StringOpt::StringFormat("guId:%s",rslt->mCosineDate->m_id.c_str() ).c_str());
//				guId = rslt->mCosineDate->m_id;
//				beginTime = PubOpt::SystemOpt::DateTmToStr(rslt->mCosineDate->m_StartTime,0);
//				endTime = PubOpt::SystemOpt::DateTmToStr(rslt->mCosineDate->m_EndTime,0);
//				duration = rslt->mCosineDate->m_TimeLong;
//				Aos_WriteLog(PubOpt::StringOpt::StringFormat("StartTime:%s",beginTime.c_str()).c_str());
//				Aos_WriteLog(PubOpt::StringOpt::StringFormat("EndTime:%s",endTime.c_str()).c_str());
//				if (NO_ALARM==rslt->mCosineId)
//				{
//					faultId = "";
//					faultName = "";
//					faultCauses = "";
//					faultAnalyse = "";
//					faultGuide = "";
//					faultCode = "";
//				}
//				else
//				{
//					cfg_it = rslt->mapRlstAlarmCosineCfg.find(rslt->mCosineId);
//					if (cfg_it!=rslt->mapRlstAlarmCosineCfg.end())
//					{
//						cfg_Cosine = cfg_it->second;
//						faultId = cfg_Cosine->mId;
//						faultName = cfg_Cosine->mName;
//						faultCauses = cfg_Cosine->mCauses;
//						faultAnalyse = cfg_Cosine->mAnalye;
//						faultGuide = cfg_Cosine->mGuid;
//					}
//					else
//					{
//						faultId = "";
//						faultName = "";
//						faultCauses = "";
//						faultAnalyse = "";
//						faultGuide = "";
//						faultCode = "";
//					}
//
//					/*faultId = rslt->mConsine->mId;
//					faultName = rslt->mConsine->mName;
//					faultCauses = rslt->mConsine->mCauses;
//					faultAnalyse = rslt->mConsine->mAnalye;
//					faultGuide = rslt->mConsine->mGuid;*/
//					faultCode = rslt->mstrSn + PubOpt::SystemOpt::DateTmToStr(rslt->mCosineDate->m_StartTime,1);
//				}
//				
//
//			}
//			else 
//			{
//				Aos_WriteLog_D("002!");
//				Aos_WriteLog(PubOpt::StringOpt::StringFormat("m_curValue:%s",rslt->mCosineDate->m_curValue.c_str()).c_str());
//				Aos_WriteLog(PubOpt::StringOpt::StringFormat("m_lastValue:%s",rslt->mCosineDate->m_lastValue.c_str()).c_str());
//				Aos_WriteLog(PubOpt::StringOpt::StringFormat("m_StartTime:%ld",rslt->mCosineDate->m_LastStartTime ).c_str());
//				Aos_WriteLog(PubOpt::StringOpt::StringFormat("m_EndTime:%ld",rslt->mCosineDate->m_LastEndTime ).c_str());
//				Aos_WriteLog(PubOpt::StringOpt::StringFormat("guId:%s",rslt->mCosineDate->m_lastId.c_str()).c_str());
//				guId = rslt->mCosineDate->m_lastId;
//				beginTime = PubOpt::SystemOpt::DateTmToStr(rslt->mCosineDate->m_LastStartTime,0);
//				endTime = PubOpt::SystemOpt::DateTmToStr(rslt->mCosineDate->m_LastEndTime,0);
//				duration = rslt->mCosineDate->m_LastTimeLong;
//
//				Aos_WriteLog(PubOpt::StringOpt::StringFormat("StartTime:%s",beginTime.c_str()).c_str());
//				Aos_WriteLog(PubOpt::StringOpt::StringFormat("EndTime:%s",endTime.c_str()).c_str());
//				if (NO_ALARM==rslt->mLastCosineId)
//				{
//					faultId = "";
//					faultName = "";
//					faultCauses = "";
//					faultAnalyse = "";
//					faultGuide = "";
//					faultCode = "";
//				}
//				else
//				{
//					cfg_it = rslt->mapRlstAlarmCosineCfg.find(rslt->mLastCosineId);
//					if (cfg_it!=rslt->mapRlstAlarmCosineCfg.end())
//					{
//						cfg_Cosine = cfg_it->second;
//						faultId = cfg_Cosine->mId;
//						faultName = cfg_Cosine->mName;
//						faultCauses = cfg_Cosine->mCauses;
//						faultAnalyse = cfg_Cosine->mAnalye;
//						faultGuide = cfg_Cosine->mGuid;
//					}
//					else
//					{
//						faultId = "";
//						faultName = "";
//						faultCauses = "";
//						faultAnalyse = "";
//						faultGuide = "";
//						faultCode = "";
//					}
//					/*faultId = rslt->mlastConsine->mId;
//					faultName = rslt->mlastConsine->mName;
//					faultCauses = rslt->mlastConsine->mCauses;
//					faultAnalyse = rslt->mlastConsine->mAnalye;
//					faultGuide = rslt->mlastConsine->mGuid;*/
//					faultCode = rslt->mstrSn + PubOpt::SystemOpt::DateTmToStr(rslt->mCosineDate->m_LastStartTime,1);
//				}
//				
//Aos_WriteLog_D("0022!");
//			}
//			
//			if (NO_ALARM==rslt->mCosineId)  
//			{
//				faultType = "未关联疑似故障";
//				eventState = "0";
//			}
//			else
//			{
//				faultType = "疑似故障";
//				eventState = "1";
//			}
//			if(guId.empty()) continue;
//			Aos_WriteLog_D("003!");
//			listGuId<<QString::fromLocal8Bit(guId.c_str());
//			if (faultId.empty())
//			{
//				listFaultId<<QVariant(QVariant::String);
//			}
//			else
//			{
//				listFaultId<<QString::fromLocal8Bit(faultId.c_str());
//			}
//			
//			listModelId<<QString::fromLocal8Bit(modelId.c_str());
//			if(faultName.empty())
//				listFaultName<<QVariant(QVariant::String);
//			else
//				listFaultName<<QString::fromLocal8Bit(faultName.c_str());
//
//			listBeginTime<<QString(beginTime.c_str());
//			listEndTime<<QString(endTime.c_str());
//			listDuration<<duration;
//
//			if(faultCauses.empty())
//				listFaultCauses<<QVariant(QVariant::String);
//			else
//				listFaultCauses<<QString::fromLocal8Bit(faultCauses.c_str());
//
//			if(faultAnalyse.empty())
//				listFaultAnalyse<<QVariant(QVariant::String);
//			else
//				listFaultAnalyse<<QString::fromLocal8Bit(faultAnalyse.c_str());
//
//			if(faultGuide.empty())
//				listFaultGuide<<QVariant(QVariant::String);
//			else
//				listFaultGuide<<QString::fromLocal8Bit(faultGuide.c_str());
//
//			if(faultCode.empty())
//				listFaultCode<<QVariant(QVariant::String);
//			else
//				listFaultCode<<QString::fromLocal8Bit(faultCode.c_str());
//
//			if(xds<0)
//				listXds<<QVariant(QVariant::Double);
//			else
//				listXds<<xds;
//
//			if(faultType.empty())
//				listFaultType<<QVariant(QVariant::String);
//			else
//				listFaultType<<QString::fromLocal8Bit(faultType.c_str());
//
//			listEventState<<QString::fromLocal8Bit(eventState.c_str());
//			
//			icount++;
//Aos_WriteLog_D("004!");
//			if(rslt->mCosineDate->m_curValue ==rslt->mCosineDate->m_lastValue
//				&&rslt->mCosineDate->m_isInto
//				&&rslt->mCosineDate->m_TimeLong >=rslt->mCosineDate->m_deaBand)
//			{
//				rslt->mCosineDate->m_perId = rslt->mCosineDate->m_id;  //插入新纪录,上条记录更新
//				rslt->mCosineDate->m_perValue = rslt->mCosineDate->m_curValue;
//				rslt->mCosineDate->m_perStartTime = rslt->mCosineDate->m_StartTime;
//				rslt->mCosineDate->m_perEndTime = rslt->mCosineDate->m_EndTime;
//				rslt->mCosineDate->m_isInto = false;
//			}
//			else
//			{
//				rslt->mCosineDate->m_perId = rslt->mCosineDate->m_lastId;   //插入新纪录,上条记录更新
//				rslt->mCosineDate->m_perValue = rslt->mCosineDate->m_lastValue;
//				rslt->mCosineDate->m_perStartTime = rslt->mCosineDate->m_LastStartTime;
//				rslt->mCosineDate->m_perEndTime = rslt->mCosineDate->m_LastEndTime;
//				rslt->mCosineDate->m_lastisInto = false;
//			}
//			//icount++;
//			if (CON_RSLT_SIZE==icount)  //CON_RSLT_SIZE
//			{
//				mQtOpt->QtbindValue(0,listGuId);
//				mQtOpt->QtbindValue(1,listFaultId);
//				mQtOpt->QtbindValue(2,listModelId);
//				mQtOpt->QtbindValue(3,listFaultName);
//				mQtOpt->QtbindValue(4,listBeginTime);
//				mQtOpt->QtbindValue(5,listEndTime);
//				mQtOpt->QtbindValue(6,listDuration);
//				mQtOpt->QtbindValue(7,listFaultCauses);
//				mQtOpt->QtbindValue(8,listFaultAnalyse);
//				mQtOpt->QtbindValue(9,listFaultGuide);
//				mQtOpt->QtbindValue(10,listEventState);
//				mQtOpt->QtbindValue(11,listFaultCode);
//				mQtOpt->QtbindValue(12,listXds);
//				mQtOpt->QtbindValue(13,listFaultType);
//				Aos_WriteLog_D("005!");
//				mQtOpt->QtExecBatch();
//				nErr = mQtOpt->QtExecBatch();
//				if(!nErr)
//				{
//					Aos_WriteLog_D("2000RsltModelCosineInToRsdb err!");
//					nErr = stmtTransRollback(CON_SET_DEAL_MODELCOSINE);//回滚数据库记录
//				}
//				nErr = stmtHandSubmit(CON_SET_DEAL_MODELCOSINE);
//				if(!nErr)
//				{
//					RollbackCosione(ipos);   //回滚内存记录
//					stmtTransRollback(CON_SET_DEAL_MODELCOSINE);//回滚数据库记录
//				}
//				Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_MODELCOSINE),false);
//				icount = 0;
//				listGuId.clear(); listFaultId.clear(); listModelId.clear();
//				listFaultName.clear(); listBeginTime.clear(); listEndTime.clear();
//				listDuration.clear(); listFaultCauses.clear(); listFaultAnalyse.clear();
//				listFaultGuide.clear(); listFaultCode.clear(); listXds.clear();
//				listFaultType.clear();
//			}
//		}
//	}
//	if (0!=icount)
//	{
//		mQtOpt->QtbindValue(0,listGuId);
//		mQtOpt->QtbindValue(1,listFaultId);
//		mQtOpt->QtbindValue(2,listModelId);
//		mQtOpt->QtbindValue(3,listFaultName);
//		mQtOpt->QtbindValue(4,listBeginTime);
//		mQtOpt->QtbindValue(5,listEndTime);
//		mQtOpt->QtbindValue(6,listDuration);
//		mQtOpt->QtbindValue(7,listFaultCauses);
//		mQtOpt->QtbindValue(8,listFaultAnalyse);
//		mQtOpt->QtbindValue(9,listFaultGuide);
//		mQtOpt->QtbindValue(10,listEventState);
//		mQtOpt->QtbindValue(11,listFaultCode);
//		mQtOpt->QtbindValue(12,listXds);
//		mQtOpt->QtbindValue(13,listFaultType);
//		nErr = mQtOpt->QtExecBatch();
//		if(!nErr)
//		{
//			Aos_WriteLog_D("RsltModelCosineInToRsdb err!");
//			nErr = stmtTransRollback(CON_SET_DEAL_MODELCOSINE);//回滚数据库记录
//		}
//		nErr = stmtHandSubmit(CON_SET_DEAL_MODELCOSINE);
//		if(!nErr)
//		{
//			RollbackCosione(ipos);   //回滚内存记录
//			stmtTransRollback(CON_SET_DEAL_MODELCOSINE);//回滚数据库记录
//		}
//		icount = 0;
//	}
//
//	return nErr;
//}
//
//bool AlarmSetDeal::RsltModelCosineUpBackInRsdb()
//{
//	bool nErr = true;
//	MapStringToAlarmModelCosineRst_It it;
//	AlarmModelCosineRst  * rslt = NULL;
//	//char conditionId[64];
//	double duration = 0;
//	std::string endTime,guId;
//	QVariantList listDuration,listEndTime,listGuId;
//	int icount = 0,ipos=0;
//	Aos_Assert_R(Util::QtConnect(mQtOpt), false);
//	Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_MODELCOSINE),false);
//	Aos_Assert_R(stmtHandPrepare(CON_SET_DEAL_MODELCOSINE, g_strRslCosineUpBackInSQL), false);
//	it = mMapAlarmModelCosineRst.begin();
//	for (;it!= mMapAlarmModelCosineRst.end();++it)
//	{
//		rslt = it->second;
//		if ((rslt->mCosineDate->m_curValue ==rslt->mCosineDate->m_lastValue
//			&&!(rslt->mCosineDate->m_isInto)
//			&&rslt->mCosineDate->m_TimeLong >=rslt->mCosineDate->m_deaBand)
//			||(rslt->mCosineDate->m_curValue !=rslt->mCosineDate->m_lastValue
//			&&rslt->mCosineDate->m_LastTimeLong <rslt->mCosineDate->m_deaBand)
//			||(rslt->mCosineDate->m_curValue !=rslt->mCosineDate->m_lastValue
//			&&rslt->mCosineDate->m_LastTimeLong >=rslt->mCosineDate->m_deaBand)
//			&&(!rslt->mCosineDate->m_lastisInto)
//			||(rslt->mCosineDate->m_curValue ==rslt->mCosineDate->m_lastValue)
//			&&(rslt->mCosineDate->m_isPPDChange))   
//			//&&rslt->mCosineDate->m_LastTimeLong >=rslt->mCosineDate->m_deaBand)&&(!rslt->mCosineDate->m_lastisInto)
//		{
//
//
//			if(rslt->mCosineDate->m_curValue ==rslt->mCosineDate->m_lastValue
//				&&!rslt->mCosineDate->m_isInto
//				&&rslt->mCosineDate->m_TimeLong >rslt->mCosineDate->m_deaBand)
//			{
//				if (rslt->mCosineDate->m_curValue=="")
//				{
//					continue;
//				}
//				guId = rslt->mCosineDate->m_id;
//				endTime = PubOpt::SystemOpt::DateTmToStr(rslt->mCosineDate->m_EndTime,0);
//				duration = rslt->mCosineDate->m_TimeLong;
//
//			}
//			else if ((rslt->mCosineDate->m_curValue !=rslt->mCosineDate->m_lastValue
//				&&rslt->mCosineDate->m_LastTimeLong <rslt->mCosineDate->m_deaBand
//				&&rslt->mCosineDate->m_LastTimeLong >= 0))
//			{
//				guId = rslt->mCosineDate->m_perId;
//				endTime = PubOpt::SystemOpt::DateTmToStr(rslt->mCosineDate->m_EndTime,0);
//				if (rslt->mCosineDate->m_curValue==rslt->mCosineDate->m_perValue)
//				{
//					rslt->mCosineDate->m_id = rslt->mCosineDate->m_perId;
//					rslt->mCosineDate->m_isInto=false;
//					duration = rslt->mCosineDate->m_EndTime-rslt->mCosineDate->m_perStartTime;
//				}
//				else
//					duration = rslt->mCosineDate->m_EndTime-rslt->mCosineDate->m_StartTime;
//			}
//			else if (rslt->mCosineDate->m_curValue !=rslt->mCosineDate->m_lastValue
//				&&rslt->mCosineDate->m_LastTimeLong >=rslt->mCosineDate->m_deaBand
//				&&(!rslt->mCosineDate->m_lastisInto))
//			{
//				if (rslt->mCosineDate->m_lastValue=="")
//				{
//					continue;
//				}
//				guId = rslt->mCosineDate->m_perId;
//				endTime = PubOpt::SystemOpt::DateTmToStr(rslt->mCosineDate->m_LastEndTime,0);
//				duration = rslt->mCosineDate->m_EndTime-rslt->mCosineDate->m_perStartTime;
//			}
//			else if ((rslt->mCosineDate->m_curValue ==rslt->mCosineDate->m_lastValue
//				&&(rslt->mCosineDate->m_isPPDChange)))
//				//&&rslt->mCosineDate->m_LastTimeLong >=rslt->mCosineDate->m_deaBand)&&(!rslt->mCosineDate->m_lastisInto)
//			{
//				if (rslt->mCosineDate->m_curValue=="")
//				{
//					continue;
//				}
//				if ((rslt->mCosineDate->m_LastTimeLong >=rslt->mCosineDate->m_deaBand)
//					&&(!rslt->mCosineDate->m_lastisInto))
//				{
//					guId = rslt->mCosineDate->m_perId;
//					endTime = PubOpt::SystemOpt::DateTmToStr(rslt->mCosineDate->m_LastEndTime,0);
//					duration = rslt->mCosineDate->m_EndTime-rslt->mCosineDate->m_perStartTime;
//				}
//				else if (rslt->mCosineDate->m_LastTimeLong <rslt->mCosineDate->m_deaBand)
//				{
//					if(rslt->mCosineDate->m_perId.empty()) continue;
//					guId = rslt->mCosineDate->m_perId;
//					endTime = PubOpt::SystemOpt::DateTmToStr(rslt->mCosineDate->m_LastEndTime,0);
//					duration = rslt->mCosineDate->m_EndTime-rslt->mCosineDate->m_perStartTime;
//				}
//				else
//					continue;
//				rslt->mCosineDate->m_isPPDChange = false;
//			}
//			listEndTime<<QString(endTime.c_str());
//			listDuration<<duration;
//			listGuId<<QString(guId.c_str());
//
//			icount++;
//			ipos++;
//			if (CON_RSLT_SIZE==icount)
//			{
//				mQtOpt->QtbindValue(0,listEndTime);
//				mQtOpt->QtbindValue(1,listDuration);
//				mQtOpt->QtbindValue(2,listGuId);
//				mQtOpt->QtExecBatch();
//				nErr = stmtHandSubmit(CON_SET_DEAL_MODELCOSINE);
//				if(!nErr)
//				{
//					RollbackCosione(ipos);   //回滚内存记录
//					stmtTransRollback(CON_SET_DEAL_MODELCOSINE);//回滚数据库记录
//				}
//				Aos_Assert_R(stmtHandTransaction(CON_SET_DEAL_MODELCOSINE),false);
//				icount = 0;
//				listEndTime.clear(); listDuration.clear(); listGuId.clear();
//			}
//		}
//	}
//	if (0!=icount)
//	{
//		mQtOpt->QtbindValue(0,listEndTime);
//		mQtOpt->QtbindValue(1,listDuration);
//		mQtOpt->QtbindValue(2,listGuId);
//		mQtOpt->QtExecBatch();
//		nErr = stmtHandSubmit(CON_SET_DEAL_MODELCOSINE);
//		if(!nErr)
//		{
//			RollbackCosione(ipos);   //回滚内存记录
//			stmtTransRollback(CON_SET_DEAL_MODELCOSINE);//回滚数据库记录
//		}
//		icount = 0;
//	}
//
//	return nErr;
//}
void AlarmSetDeal::CalAralm(MapStringToAlarmSetInfo &mMapAlarmSet)
{
    MapStringToAlarmSetInfo_It		it_set;
    AlarmSetInfo * pset= NULL;
    MapStringToAlarmModeltoSetRst_It it_rslt_modeltoset;
    AlarmModeltoSetRst * rslt_modeltoset = NULL;
    /*MapStringToAlarmSetSys_It		it_sys;
    AlarmSetSys	* psys=		NULL;
    MapStringToAlarmModel_It		it_model;
    AlarmModel	* pmodel =	NULL;
    MapStringToAlaramModelGroup_It	it_group;
    MapStringToAlarmPointInfo_It	it_point;
    AlaramModelGroup *pgroup = NULL;
    AlarmPointInfo * ppoint	= NULL;*/

    //stmtHandPrepare();
    it_set= mMapAlarmSet.begin();
    for (;it_set!= mMapAlarmSet.end();++it_set)
    {
        pset = it_set->second;
        DealSetAlarm(pset);

        it_rslt_modeltoset = mMapAlarmModeltoSetRst.find(pset->mSet);
        if (it_rslt_modeltoset==mMapAlarmModeltoSetRst.end())
        {
            rslt_modeltoset = new AlarmModeltoSetRst();
            mMapAlarmModeltoSetRst.insert(make_pair(pset->mSet,rslt_modeltoset));
        }
        else
        {
            rslt_modeltoset = it_rslt_modeltoset->second;
        }
        rslt_modeltoset->mStrId = pset->mSet;
        rslt_modeltoset->mDate = &pset->mDate;
        /*it_sys = pset->mapSys.begin();
        for (;it_sys!= pset->mapSys.end();++it_sys)
        {
            psys = it_sys->second;
            it_model= psys->mapAlarmMode.begin();
            for (;it_model!= psys->mapAlarmMode.end();++it_model)
            {
                pmodel= it_model->second;
                it_group = pmodel->mapAlarmGroup.begin();
                for (;it_group != pmodel->mapAlarmGroup.end();++it_group)
                {
                    pgroup = it_group->second;
                    it_point = pgroup->mapPointInfo.begin();
                    for (;it_point != pgroup->mapPointInfo.end();++it_point)
                    {
                        ;
                    }
                }
            }

        }*/
    }
    //AlarmToRsdb(MapStringToAlarmSetInfo &mMapAlarmSet);
}
void
AlarmSetDeal::DealSetAlarm(AlarmSetInfo * pset)
{
    std::string strInfo;
    MapStringToAlarmSetSys_It		it_sys;
    AlarmSetSys	* psys=		NULL;
    MapStringToAlarmModeltoSetRst_It it_rslt_modeltoset;
    AlarmModeltoSetRst * rslt_modeltoset = NULL;
    double sumScore,sumDev;
    sumScore = 0;
    sumDev = 0;
    //add by wk 2017-12-20 debug
    //strInfo = PubOpt::StringOpt::StringFormat("开始计算机组:%s", pset->mSet.c_str());
    //Aos_WriteLog_D(strInfo.c_str());
    //end add
    it_sys = pset->mapSys.begin();
    for (;it_sys!= pset->mapSys.end();++it_sys)
    {
        psys = it_sys->second;
        DealSysAlarm(psys);
        sumDev+= psys->mWeight;
        CalSoreMolWeight(psys->mDate.m_curValue,psys->mWeight,sumScore);

        it_rslt_modeltoset = mMapAlarmModeltoSetRst.find(psys->mSys);
        if (it_rslt_modeltoset==mMapAlarmModeltoSetRst.end())
        {
            rslt_modeltoset = new AlarmModeltoSetRst();
            mMapAlarmModeltoSetRst.insert(make_pair(psys->mSys,rslt_modeltoset));
        }
        else
        {
            rslt_modeltoset = it_rslt_modeltoset->second;
        }
        rslt_modeltoset->mStrId = psys->mSys;
        rslt_modeltoset->mDate = &psys->mDate;
    }
    if(0!=sumDev)
        sumScore=sumScore/sumDev;
    //add by wk 2017-12-20 debug
    //strInfo = PubOpt::StringOpt::StringFormat("机组:%s, sumScore:%f;", pset->mSet.c_str(), sumScore);
    //Aos_WriteLog_D(strInfo.c_str());
    //end add
    SetSoreAlarmValue(pset->mDate.m_lastValue,pset->mDate.m_curValue,pset->mDate.m_alarmScore,
                      pset->mDate.m_alarmLastScore,sumScore,pset->mDate.m_isInto);

    pset->mDate.DataDeal(misFirstCal,false,pset->miBand,mlCalTimeStamp);
}
void
AlarmSetDeal:: DealSysAlarm(AlarmSetSys * psys)
{
    double sumScore,sumDev;
    MapStringToAlarmModel_It		it_model;
    AlarmModel	* pmodel =	NULL;

    sumScore= 0;
    sumDev = 0;
    it_model= psys->mapAlarmMode.begin();
    for (;it_model!= psys->mapAlarmMode.end();++it_model)
    {

        pmodel= it_model->second;
        /*if (pmodel->mstrModelId =="67c25ae4-64ce-4e9a-9ed8-095a27fc9dcd"
            ||pmodel->mstrModelId =="19096b38-9f32-47eb-9b54-095bc6fbe4e3")
            continue;*/
        DealModelAlarm(pmodel);
        DealModelPCAlarm(pmodel);
        sumDev+= pmodel->mWeight;
        CalSoreMolWeight(pmodel->mDate.m_curValue,pmodel->mWeight,sumScore);

        SetAlarmModelRslt(pmodel);
    }
    if(0!=sumDev)
        sumScore=sumScore/sumDev;

    //add by wk 2017-12-20 debug
    //std::string strInfo = PubOpt::StringOpt::StringFormat("系统:%s, sumScore:%f;", psys->mSys.c_str(), sumScore);
    //Aos_WriteLog_D(strInfo.c_str());
    //end add
    SetSoreAlarmValue(psys->mDate.m_lastValue,psys->mDate.m_curValue,psys->mDate.m_alarmScore,
                      psys->mDate.m_alarmLastScore,sumScore,psys->mDate.m_isInto);
    //add by wk 2017-12-20 debug
    //strInfo = PubOpt::StringOpt::StringFormat("计算系统:%s, sumScore:%f;",
    //	psys->mSys.c_str(), psys->mDate.m_alarmScore);
    //Aos_WriteLog_D(strInfo.c_str());
    //end add
    psys->mDate.DataDeal(misFirstCal,false,psys->miBand,mlCalTimeStamp);
}
void AlarmSetDeal::clearn()
{
    MapStringToAlarmModeltoSetRst_It it_rslt_modeltoset;
    MapStringToAlarmModelConditionRst_It it_rslt_condtion;
    MapStringToAlarmModelCosineRst_It it_rslt_Cosine;
    for (it_rslt_modeltoset=mMapAlarmModeltoSetRst.begin();it_rslt_modeltoset!=mMapAlarmModeltoSetRst.end();++it_rslt_modeltoset)
    {
        delete it_rslt_modeltoset->second;
    }
    mMapAlarmModeltoSetRst.clear();
    for (it_rslt_condtion=mMapAlarmModelConditionRst.begin();it_rslt_condtion!=mMapAlarmModelConditionRst.end();++it_rslt_condtion)
    {
        delete it_rslt_condtion->second;
    }
    mMapAlarmModelConditionRst.clear();
    for (it_rslt_Cosine== mMapAlarmModelCosineRst.begin();it_rslt_Cosine != mMapAlarmModelCosineRst.end();++it_rslt_Cosine)
    {
        delete it_rslt_Cosine->second;
    }
    mMapAlarmModelCosineRst.clear();
}
void AlarmSetDeal::SetAlarmModelRslt(AlarmModel	* pmodel)
{
    MapStringToAlarmModeltoSetRst_It it_rslt_modeltoset;
    AlarmModeltoSetRst * rslt_modeltoset = NULL;
    MapStringToAlarmModelConditionRst_It it_rslt_condtion;
    AlarmModelConditionRst * rslt_condtion = NULL;
    MapStringToAlarmModelCosineRst_It it_rslt_Cosine;
    AlarmModelCosineRst * rslt_Cosine = NULL;
    CDCosineCfg * cfg_Cosine = NULL;
    //CDCosine* cosine=NULL;
    MapStringToAlaramCosine_It it;

    it_rslt_modeltoset = mMapAlarmModeltoSetRst.find(pmodel->mstrModelId);
    if (it_rslt_modeltoset==mMapAlarmModeltoSetRst.end())
    {
        rslt_modeltoset = new AlarmModeltoSetRst();
        mMapAlarmModeltoSetRst.insert(make_pair(pmodel->mstrModelId,rslt_modeltoset));
    }
    else
    {
        rslt_modeltoset = it_rslt_modeltoset->second;
    }
    rslt_modeltoset->mStrId = pmodel->mstrModelId;
    rslt_modeltoset->mDate = &pmodel->mDate;

    //it_rslt_condtion = mMapAlarmModelConditionRst.find(pmodel->mCondId);
    it_rslt_condtion = mMapAlarmModelConditionRst.find(pmodel->mstrModelId);
    if (it_rslt_condtion==mMapAlarmModelConditionRst.end())
    {
        rslt_condtion = new AlarmModelConditionRst();
        mMapAlarmModelConditionRst.insert(make_pair(pmodel->mstrModelId,rslt_condtion));
        rslt_condtion->mCondtionDate = &pmodel->mCondtionDate;
    }
    else
    {
        rslt_condtion = it_rslt_condtion->second;
    }
    if ("67c25ae4-64ce-4e9a-9ed8-095a27fc9dcd"==pmodel->mstrModelId)
        int i =100;
    rslt_condtion->mCondId = pmodel->mCondId;
    rslt_condtion->mModelIdTest = pmodel->mstrModelId;
    //rslt_condtion->mCondtionDate = &pmodel->mCondtionDate;

    it_rslt_Cosine = mMapAlarmModelCosineRst.find(pmodel->mstrModelId);
    if (it_rslt_Cosine==mMapAlarmModelCosineRst.end())
    {
        rslt_Cosine = new AlarmModelCosineRst();
        mMapAlarmModelCosineRst.insert(make_pair(pmodel->mstrModelId,rslt_Cosine));
        for (MapStringToAlaramCosine_It it = pmodel->mapAlarmCosine.begin();it != pmodel->mapAlarmCosine.end();++it)
        {
            if (rslt_Cosine->mapRlstAlarmCosineCfg.find(it->second->mId)==rslt_Cosine->mapRlstAlarmCosineCfg.end())
            {
                cfg_Cosine = new CDCosineCfg();
                rslt_Cosine->mapRlstAlarmCosineCfg.insert(make_pair(it->second->mId,cfg_Cosine));
                cfg_Cosine->mId = it->second->mId;
                cfg_Cosine->mAnalye =it->second->mAnalye;
                cfg_Cosine->mCauses = it->second->mCauses;
                cfg_Cosine->mGuid = it->second->mGuid;
                cfg_Cosine->mName = it->second->mName;
            }

        }
    }
    else
    {
        rslt_Cosine = it_rslt_Cosine->second;
        if (mModConf)
        {
            for (MapStringToAlaramCosine_It it = pmodel->mapAlarmCosine.begin();it != pmodel->mapAlarmCosine.end();++it)
            {
                if (rslt_Cosine->mapRlstAlarmCosineCfg.find(it->second->mId)==rslt_Cosine->mapRlstAlarmCosineCfg.end())
                {
                    cfg_Cosine = new CDCosineCfg();
                    rslt_Cosine->mapRlstAlarmCosineCfg.insert(make_pair(it->second->mId,cfg_Cosine));
                    cfg_Cosine->mId = it->second->mId;
                    cfg_Cosine->mAnalye =it->second->mAnalye;
                    cfg_Cosine->mCauses = it->second->mCauses;
                    cfg_Cosine->mGuid = it->second->mGuid;
                    cfg_Cosine->mName = it->second->mName;
                }

            }
        }
    }
    rslt_Cosine->mLastCosineId = pmodel->mLastCosineId;
    rslt_Cosine->mCosineId = pmodel->mCosineId;
    rslt_Cosine->mStrModelId = pmodel->mstrModelId;
    rslt_Cosine->mstrSn = pmodel->mstrSn;
    rslt_Cosine->mXsd = pmodel->mXsd;
    //rslt_Cosine->mConsine = pmodel->mConsine;
    /*if (!pmodel->mCosineDate.m_lastId.empty())
    {
        it = pmodel->mapAlarmCosine.find(pmodel->mCosineDate.m_lastId);
        if(it != pmodel->mapAlarmCosine.end())
            rslt_Cosine->mlastConsine = it->second;
    }*/

    rslt_Cosine->mCosineDate= &pmodel->mCosineDate;
}
bool
AlarmSetDeal::CompSim (AlarmModel	* pmodel)
{
    bool is_ok;
    if (0==(pmodel->mLastSumAlram+pmodel->mSumAlram))  //上次和本次所有测点都不告警
    {
        pmodel->mCosineDate.m_isChange = false;
        pmodel->mCosineDate.m_isCalCycOk = false;
        is_ok = false;
    }
    else
    {
        if (0==(pmodel->mLastSumAlram*pmodel->mSumAlram))
        {
            if(0!=pmodel->mSumAlram)
            {
                pmodel->mCosineDate.m_isChange = true;
                pmodel->mCosineDate.m_isCalCycOk = true;
                is_ok = true;
            }
            else
            {
                pmodel->mCosineDate.m_isChange = false;
                pmodel->mCosineDate.m_isCalCycOk = false;
                is_ok = false;
            }

        }
        else
        {
            pmodel->mCosineDate.m_isCalCycOk = true;
            pmodel->mDevPPD = pmodel->mDevFabsSum/(pmodel->mLastSumAlram*pmodel->mSumAlram);
            if (abs(pmodel->mDevPPD-100)<0.0001)
            {
                pmodel->mDevPPD = 100;
            }
            if (100==pmodel->mDevPPD)
            {
                pmodel->mCosineDate.m_isChange = false;
                is_ok = false;
            }
            else
            {
                pmodel->mCosineDate.m_isChange = true;
                is_ok = true;
            }
        }
    }
    return is_ok;
}
void
AlarmSetDeal::DealModelPCAlarm(AlarmModel	* pmodel)
{
    MapStringToAlaramCosine_It it;
    CDCosine* cosine=NULL;
    bool is_Cal = false;
    pmodel->mCosineDate.m_Time= mlCalTimeStamp;
    pmodel->mCosineDate.m_lastValue = pmodel->mCosineDate.m_curValue;
    pmodel->mLastCosineId = pmodel->mCosineId;  //上条报警cosineId
    /*pmodel->mCosineId = NO_ALARM;
    pmodel->mXsd = -200;*/   //cosine->m_pValue的数据范围[-100,100],所以model->m_xsd初始化应小于-1

    if ("67c25ae4-64ce-4e9a-9ed8-095a27fc9dcd"==pmodel->mstrModelId)  //||"4_ycfj1bt"==pmodel->mstrModelId
    {
        int i =100;
    }
    is_Cal = CompSim(pmodel);
    if(0!=pmodel->mSumAlram&&is_Cal)    //模型下面有测点告警
    {
        pmodel->mCosineId = NO_ALARM;
        pmodel->mXsd = -100;   //cosine->m_pValue的数据范围[-100,100],所以model->m_xsd初始化应小于-1
        pmodel->mCosineDate.m_lastValue = pmodel->mCosineDate.m_curValue;
        pmodel->mCosineDate.m_Time = mlCalTimeStamp;
        it = pmodel->mapAlarmCosine.begin();
        for (;it!=pmodel->mapAlarmCosine.end();++it)
        {
            cosine = it->second;
            /*cosine->mDate.m_lastValue = cosine->mDate.m_curValue;
            cosine->mDate.m_curValue = 0;
            cosine->mDate.m_Time = mlCalTimeStamp;*/
            if(!cosine->isMok) continue;
            CalPCAlarm(cosine,pmodel->mapAlarmGroup,pmodel->mSumAlram);

            if (pmodel->mXsd<=cosine->mPValue)
            {
                pmodel->mXsd = cosine->mPValue;
                pmodel->mCosineId = cosine->mId;
                pmodel->mConsine = cosine;
            }
        }
        if (mXsdLimit<=0)
        {
            if (pmodel->mXsd<= 0)
            {
                pmodel->mCosineId= NO_ALARM;
                pmodel->mXsd = 0;
            }
        }
        else
        {
            if (pmodel->mXsd<mXsdLimit)
            {
                pmodel->mCosineId= NO_ALARM;
                pmodel->mXsd = 0;
            }
        }
        pmodel->mCosineDate.m_curValue = "";
        pmodel->mCosineDate.m_curValue = pmodel->mCosineId;
    }
    else if(0==pmodel->mSumAlram)
    {
        pmodel->mCosineDate.m_curValue = "";
        pmodel->mXsd = 0;
    }
    if ("67c25ae4-64ce-4e9a-9ed8-095a27fc9dcd"==pmodel->mstrModelId)  //||"4_ycfj1bt"==pmodel->mstrModelId
    {
        int i =100;
    }
    pmodel->mCosineDate.m_Time = mlCalTimeStamp;
    pmodel->mCosineDate.DataDealConsine(misFirstCal,pmodel->miBand,mlCalTimeStamp,pmodel->mXsd);

}
void
AlarmSetDeal::CalPCAlarm(CDCosine* cosine,const MapStringToAlaramModelGroup &mapModelCategory,const double sumAlram)
{
    int ivalue;
    std::string strPointKey;
    double sum=0;
    MapStringToAlaramModelGroupConst_It group_it;
    MapStringToAlarmPointInfo_It   point_it;
    std::map<std::string , int>::iterator it;
    AlaramModelGroup * modelcategory=NULL;
    AlarmPointInfo * point = NULL;
    for (it=cosine->mMapCosine.begin();it!=cosine->mMapCosine.end();++it)
    {
        //icount++;
        if (0==it->second) continue;
        //icount2++;
        strPointKey = it->first;
        ivalue=it->second;
        group_it = mapModelCategory.begin();
        for (;group_it!=mapModelCategory.end();++group_it)
        {
            modelcategory = group_it->second;
            point_it = modelcategory->mapPointInfo.find(strPointKey);
            if (point_it!=modelcategory->mapPointInfo.end())
            {
                point = point_it->second;
                if (point->mDate.m_PcValue==0)
                {
                    continue;
                }
                sum+=ivalue*point->mDate.m_PcValue;
                break;
            }
        }
    }
    if(0==cosine->mMoValue*sumAlram)
        cosine->mPValue = 0;
    cosine->mPValue = sum*100/(cosine->mMoValue*sumAlram);

}
void
AlarmSetDeal:: DealModelAlarm(AlarmModel	* pmodel)
{
    MapStringToAlaramModelGroup_It	it_group;
    MapStringToAlarmPointInfo_It	it_point;
    MapStringToAlarmPointRst_It     it_rslt_point;
    MapStringToAlarmGrouRst_It      it_rslt_group;
    AlarmPointRst *  rsltPoint = NULL;
    AlarmGrouRst  *  rsltGroup = NULL;
    AlaramModelGroup *pgroup = NULL;
    AlarmPointInfo * ppoint	= NULL;
    int sim = 0;
    bool isWatch;
    //bool isOk;
    double sumScore,sumDev;
    //VecetorAlarmScore_It it_score;
    pmodel->mSumAlram = 0 ;
    pmodel->mLastSumAlram = 0;
    pmodel->mDevFabsSum = 0;
    if (pmodel->mstrModelId == "4_zc"||"4_1gj"==pmodel->mstrModelId)
        int i=100;
    pmodel->mCondtionDate.DataDeal(misFirstCal,pmodel->miBand,mlCalTimeStamp);
    if (!pmodel->mCondId.empty())
    {
        isWatch = true;
    }
    else
    {
        isWatch = false;
    }
    sumScore= 0;
    sumDev = 0;
    it_group = pmodel->mapAlarmGroup.begin();
    for (;it_group != pmodel->mapAlarmGroup.end();++it_group)
    {
        pgroup = it_group->second;
        pgroup->mDate.m_lastValue = pgroup->mDate.m_curValue;
        pgroup->mDate.m_curValue = -2;
        it_point = pgroup->mapPointInfo.begin();
        //if("4_zc"==pmodel->mstrModelId||"4_1gj"==pmodel->mstrModelId||"4_3gj"==pmodel->mstrModelId)//
        if("4_ycfj1bt"==pmodel->mstrModelId||"acb0c645-4ac1-4d6d-a354-153a5be3f111"==pmodel->mstrModelId)
            int i = 100;
        for (;it_point != pgroup->mapPointInfo.end();++it_point)
        {
            ppoint= it_point->second;
            if(pmodel->mIsSimAlarm&&(ppoint->mDsim<pmodel->mdSimLimit)&&ppoint->mIsGetSimVale)
                sim = 1;
            else
                sim = 0;
            if("4_ycfj1bt"==pmodel->mstrModelId)//
                int i = 100;
            DealPointlAlarm(ppoint,isWatch,pmodel->m_IsChangeCondition,sim);
            //if("4_zc"==pmodel->mstrModelId)
            //Aos_WriteLog(PubOpt::StringOpt::StringFormat("点名：%s,告警值：%d",ppoint->mStrPointId.c_str(),ppoint->mDate.m_curValue).c_str());
            pmodel->mSumAlram += pow((double)ppoint->mDate.m_PcValue,2);
            pmodel->mLastSumAlram += pow((double)ppoint->mDate.m_LastPcValue,2);
            pmodel->mDevFabsSum +=fabs((double)ppoint->mDate.m_LastPcValue)*fabs((double)ppoint->mDate.m_PcValue);
            if(pgroup->mDate.m_curValue<ppoint->mDate.m_curValue)
                pgroup->mDate.m_curValue = ppoint->mDate.m_curValue;
            if (ppoint->mStrPointId=="gjcyxt_1gj_D3_3AIFB07")
            {
                int i =100;
            }
            it_rslt_point = mMapAlarmPointRst.find(ppoint->mStrPointId);
            if (it_rslt_point==mMapAlarmPointRst.end())
            {
                rsltPoint = new AlarmPointRst();
                mMapAlarmPointRst.insert(make_pair(ppoint->mStrPointId,rsltPoint));
            }
            else
                rsltPoint = it_rslt_point->second;
            if (ppoint->mStrPointId=="gjcyxt_1gj_D3_3AIFB07")
            {
                int i =100;
            }
            //if(misFirstCal)
            //{
            //	Aos_WriteLog((PubOpt::StringOpt::StringFormat("%s", ppoint->mStrPointId.c_str())).c_str());
            //}
            rsltPoint->mStrModelId = pmodel->mstrModelId;
            rsltPoint->mStrGroupId = pgroup->mStrGroupId;
            rsltPoint->mStrCondId  = pmodel->mCondId;
            rsltPoint->mStrPointId = ppoint->mStrPointId;
            rsltPoint->mDcurValue  = ppoint->mDcurValue;
            rsltPoint->m_maxValue = ppoint->m_maxValue;
            rsltPoint->m_minValue = ppoint->m_minValue;
            rsltPoint->m_avgValue = ppoint->m_avgValue;
            rsltPoint->mDpreValue = ppoint->mDpreValue;
            rsltPoint->m_pmaxValue = ppoint->m_pmaxValue;
            rsltPoint->m_pminValue = ppoint->m_pminValue;
            rsltPoint->m_pavgValue = ppoint->m_pavgValue;
            rsltPoint->mIsInitCurVale = ppoint->mIsInitCurVale;
            rsltPoint->mIsInitPreVale = ppoint->mIsInitPreVale;
            rsltPoint->mIsInitSimVale = ppoint->mIsInitSimVale;
            rsltPoint->mIsGetCurVale = ppoint->mIsGetCurVale;
            rsltPoint->mIsGetPreVale = ppoint->mIsGetPreVale;
            rsltPoint->mIsGetSimVale = ppoint->mIsGetSimVale;
            rsltPoint->mDsim = ppoint->mDsim;
            rsltPoint->mDsim = ppoint->mDsim;
            rsltPoint->m_savgValue = ppoint->m_savgValue;
            rsltPoint->mDate = &ppoint->mDate;
        }

        pgroup->mDate.DataDeal(misFirstCal,pmodel->m_IsChangeCondition,pgroup->miBand,mlCalTimeStamp);
        VecetorAlarmScore_It it_score;
        for (it_score = mVectorAlarmScore->begin();it_score!= mVectorAlarmScore->end();++it_score)
        {
            if(!pgroup->mDate.m_isInto)
                break;
            if (it_score->mAlarmLevel==pgroup->mDate.m_curValue)
            {
                pgroup->mDate.m_alarmLastScore = pgroup->mDate.m_alarmScore;
                pgroup->mDate.m_alarmScore = it_score->mAlarmScore;
                break;
            }
        }

        it_rslt_group = mMapAlarmGrouRst.find(pgroup->mStrGroupId);
        if (it_rslt_group==mMapAlarmGrouRst.end())
        {
            rsltGroup = new AlarmGrouRst();
            mMapAlarmGrouRst.insert(make_pair(pgroup->mStrGroupId,rsltGroup));
        }
        else
            rsltGroup = it_rslt_group->second;

        rsltGroup->mStrGroupId = pgroup->mStrGroupId;
        rsltGroup->mDate= &pgroup->mDate;

        sumDev+= pgroup->mWeight;
        /*isOk = false;
        for (it_score = mVectorAlarmScore->begin();it_score!= mVectorAlarmScore->end();++it_score)
        {
            if(it_score->mAlarmLevel==pgroup->mDate.m_curValue)
            {
                sumScore+= pgroup->mWeight*it_score->mVectorAlarmScore;
                isOk = true;
                break;
            }
        }
        if (!isOk)
        {
            sumScore+= pgroup->mWeight*(-1);
        }*/
        CalSoreMolWeight(pgroup->mDate.m_curValue,pgroup->mWeight,sumScore);
    }

    pmodel->mSumAlram = sqrt(pmodel->mSumAlram);

    pmodel->mLastSumAlram = sqrt(pmodel->mLastSumAlram);

    pmodel->mDevFabsSum = 100*pmodel->mDevFabsSum;
    if(0!= sumDev)
        sumScore=sumScore/sumDev;
    /*isOk = false;
    for (it_score = mVectorAlarmScore->begin();it_score!= mVectorAlarmScore->end();++it_score)
    {
        if(it_score->mUpper>=sumScore&&it_score->mLower<=sumScore)
        {
            pmodel->mDate.m_lastValue = pmodel->mDate.m_curValue;
            pmodel->mDate.m_curValue = it_score->mAlarmLevel;
            isOk = true;
            break;
        }
    }
    if (!isOk)
    {
        pmodel->mDate.m_curValue = -1;
    }*/

    //int i = sumScore*1000;
    //sumScore = (double)i/1000;
    SetSoreAlarmValue(pmodel->mDate.m_lastValue,pmodel->mDate.m_curValue,pmodel->mDate.m_alarmScore,
                      pmodel->mDate.m_alarmLastScore,sumScore,pmodel->mDate.m_isInto);

    if("4_zc"==pmodel->mstrModelId)//
        int i = 100;
    pmodel->mDate.DataDeal(misFirstCal,false,pmodel->miBand,mlCalTimeStamp);
}
void AlarmSetDeal::SetSoreAlarmValue(int &lastValue,int &curValue,double & alarmScore,double & alarmLastScore,
                                     double & sumScore,const bool & is_score)
{
    VecetorAlarmScore_It it_score;
    bool isOk= false;
    double dlow,dup;
    lastValue = curValue;
    //add by wk 2017-12-20
    if(0==sumScore)
    {
        alarmScore = 0.2;
        return;
    }
    //end add
    for (it_score = mVectorAlarmScore->begin();it_score!= mVectorAlarmScore->end();++it_score)
    {
        dlow = it_score->mLower;
        dup= it_score->mUpper;
        if (abs(dup-sumScore)<0.0001)
        {
            sumScore = dup;
        }
        //if(it_score->mUpper>=sumScore&&it_score->mLower<sumScore)
        if(dup>=sumScore&&dlow<sumScore)
        {
            //lastValue = curValue;
            curValue = it_score->mAlarmLevel;
            if(is_score)
            {
                alarmLastScore = alarmScore;
                alarmScore = it_score->mAlarmScore;
            }
            isOk = true;
            break;
        }
    }
    if (!isOk)
    {
        curValue = -0.2;
    }
}
void AlarmSetDeal::CalSoreMolWeight(const int &curValue,const double &weight,double &sumScore)
{
    VecetorAlarmScore_It it_score;
    bool isOk= false;
    double temp;
    int item;
    for (it_score = mVectorAlarmScore->begin();it_score!= mVectorAlarmScore->end();++it_score)
    {
        item = it_score->mAlarmLevel;
        if(it_score->mAlarmLevel==curValue)
        {
            temp = it_score->mAlarmScore;
            sumScore+= weight*it_score->mAlarmScore;
            sumScore = sumScore*100;
            sumScore = sumScore/100;
            isOk = true;
            break;
        }
    }
    if (!isOk)
    {
        sumScore+= weight*(-1);
    }
}
//void AlarmSetDeal::CalSoreMolWeight(const int lastStause,const int curStause,)
void AlarmSetDeal::DealPointlAlarm(AlarmPointInfo * ppoint,bool isWatch,bool isChangeContion,int simValue)
{
    double zoneValue=0;
    bool isAlarm = false;
    std::vector<AlarmPointZone>::iterator it;
    ppoint->mDate.m_lastAlarmType = ppoint->mDate.m_alarmType;
    ppoint->mDate.m_alarmType = 0;
    ppoint->mDate.m_LastPcValue = ppoint->mDate.m_PcValue;
    ppoint->mDate.m_PcValue = 0;
    if (isWatch)
    {
        if(0==ppoint->mVectZone.size())
        {
            ppoint->mDate.m_lastValue = ppoint->mDate.m_curValue;
            ppoint->mDate.m_curValue = simValue;
            if (1==simValue)
            {
                if(ppoint->mDcurValue-ppoint->mDpreValue>0)
                    ppoint->mDate.m_PcValue = 1;
                else if(ppoint->mDcurValue-ppoint->mDpreValue<0)
                    ppoint->mDate.m_PcValue = -1;
                else if(ppoint->mDcurValue-ppoint->mDpreValue==0)
                    ppoint->mDate.m_PcValue = 0;

                ppoint->mDate.m_alarmType = 3;
                //isAlarm  = true;
            }
            else
            {
                ppoint->mDate.m_PcValue = 0;
            }
        }
        else
        {
            it = ppoint->mVectZone.begin();
            for (;it!= ppoint->mVectZone.end();++it)
            {

                if (0==it->mIAlarmType)//期望值告警
                {
                    if (ppoint->mIsGetCurVale&&ppoint->mIsGetPreVale)
                    {
                        zoneValue= 0;
                        zoneValue = ppoint->mDcurValue-ppoint->mDpreValue;
                        if ((zoneValue<it->mDAlarmLower&&it->mLowExist)||(zoneValue>it->mDAlarmUpper&&it->mUperExist))
                        {
                            if(1==simValue)
                                ppoint->mDate.m_alarmType = 4;
                            else
                                ppoint->mDate.m_alarmType = 2;
                        }
                    }
                    else
                    {
                        continue;
                    }
                }
                else if (1==it->mIAlarmType)//原始值告警
                {
                    if (ppoint->mIsGetCurVale)
                    {
                        zoneValue=0;
                        zoneValue=ppoint->mDcurValue;
                        if((zoneValue<it->mDAlarmLower)&&(it->mLowExist)||(zoneValue>=it->mDAlarmUpper)&&(it->mUperExist))
                        {
                            if(1==simValue)
                                ppoint->mDate.m_alarmType=4;
                            else
                                ppoint->mDate.m_alarmType=1;
                        }
                    }
                    else//没有取到原始值，则不判断此区间告警
                    {
                        continue;
                    }
                }
                if (zoneValue<it->mDAlarmLower&&it->mLowExist)//都是区间外告警，满足告警条件
                {
                    ppoint->mDate.m_lastValue= ppoint->mDate.m_curValue;
                    ppoint->mDate.m_curValue= it->mIAlarmLevel;
                    ppoint->mDate.m_PcValue= -1;
                    isAlarm= true;
                    break;
                }
                if (zoneValue>=it->mDAlarmUpper&&it->mUperExist)//都是区间外告警，满足告警条件
                {
                    //zone->m_date.m_curValue=1;
                    ppoint->mDate.m_lastValue= ppoint->mDate.m_curValue;
                    ppoint->mDate.m_curValue=it->mIAlarmLevel;
                    ppoint->mDate.m_PcValue=1;
                    isAlarm=true;
                    break;
                }
            }
            if (!isAlarm)//不告警
            {
                ppoint->mDate.m_lastValue= ppoint->mDate.m_curValue;
                if (simValue>= ppoint->mDate.m_curValue)
                    ppoint->mDate.m_curValue= simValue;
                else
                    ppoint->mDate.m_curValue= 0;		//不告警

                if(1==simValue)
                {
                    if(ppoint->mDcurValue-ppoint->mDpreValue>0)
                        ppoint->mDate.m_PcValue = 1;
                    else if(ppoint->mDcurValue-ppoint->mDpreValue<0)
                        ppoint->mDate.m_PcValue = -1;
                    else if(ppoint->mDcurValue-ppoint->mDpreValue==0)
                        ppoint->mDate.m_PcValue = 0;

                    ppoint->mDate.m_alarmType=3;
                }
                else
                    ppoint->mDate.m_PcValue=0;
            }
        }
    }
    else
    {
        ppoint->mDate.m_lastValue= ppoint->mDate.m_curValue;
        ppoint->mDate.m_curValue= -1;//非监视状态
        ppoint->mDate.m_PcValue= 0;
    }
    if("qlj_zc_D3_LP1GNT"==ppoint->mStrPointId)
        int i =100;
    ppoint->mDate.DataDeal(misFirstCal,isChangeContion,ppoint->miBand,mlCalTimeStamp);
}
void
AlarmSetDeal::SetRtPointValue(const MapStringToDataMode  &mMapModeInfo,MapStringToAlarmSetInfo &mMapAlarmSet)
{
    MapStringToAlarmSetInfo_It		it_set;
    MapStringToAlarmSetSys_It		it_sys;
    MapStringToAlarmModel_It		it_model;
    MapStringToAlaramModelGroup_It	it_group;
    MapStringToAlarmPointInfo_It	it_point;
    AlarmSetInfo * pset=		NULL;
    AlarmSetSys	* psys=		NULL;
    AlarmModel	* pmodel =	NULL;
    AlaramModelGroup *pgroup = NULL;
    AlarmPointInfo * ppoint	= NULL;

    MapStringToDataMode_const_It iter_pre_model;
    MapStringToMDataValueInfo_It p_iter;
    MapStringToPointGroup_It g_iter;
    DataMode* mode_info = NULL;

    it_set= mMapAlarmSet.begin();
    for (;it_set!= mMapAlarmSet.end();++it_set)
    {
        pset= it_set->second;
        it_sys = pset->mapSys.begin();
        for (;it_sys!= pset->mapSys.end();++it_sys)
        {
            psys= it_sys->second;
            it_model= psys->mapAlarmMode.begin();
            for (;it_model!= psys->mapAlarmMode.end();++it_model)
            {
                pmodel= it_model->second;
                if ("3_1gj"==pmodel->mstrModelId)
                {
                    int i =100;
                }
                iter_pre_model= mMapModeInfo.find(pmodel->mstrModelId);
                if (iter_pre_model== mMapModeInfo.end())
                {
                    pmodel->mIsDeal = false;
                    continue;
                }
                mode_info = iter_pre_model->second;
                pmodel->mIsDeal = mode_info->m_IsCalOk;
                pmodel->mIsSimAlarm = mode_info->mIsSimAlarm;
                pmodel->mdSimLimit= mode_info->mSimLimit;

                if(pmodel->mstrModelId=="4_zc"||"4_1gj"==pmodel->mstrModelId)
                    int i =100;
                pmodel->mCondId= mode_info->mCondId;

                pmodel->mCondtionDate.m_lastValue = pmodel->mCondtionDate.m_curValue;
                pmodel->mCondtionDate.m_curValue = mode_info->mCondId;
                //pmodel->mCondtionDate.m_Time = mlCalTimeStamp;
                //pmodel->mCondtionDate.DataDeal(misFirstCal,pmodel->miBand,mlCalTimeStamp);
                if((pmodel->mCondtionDate.m_lastValue != pmodel->mCondtionDate.m_curValue)
                        &&(!pmodel->mCondtionDate.m_curValue.empty()))
                {
                    pmodel->mCondtionDate.m_isChange = true;
                    pmodel->m_IsChangeCondition = true;
                }
                else
                {
                    pmodel->mCondtionDate.m_isChange = false;
                    pmodel->m_IsChangeCondition = false;
                }
                if ("3_1gj"==pmodel->mstrModelId)
                {
                    int i =100;
                }
                it_group = pmodel->mapAlarmGroup.begin();
                for (;it_group != pmodel->mapAlarmGroup.end();++it_group)
                {
                    pgroup = it_group->second;
                    it_point = pgroup->mapPointInfo.begin();
                    for (;it_point != pgroup->mapPointInfo.end();++it_point)
                    {
                        ppoint = it_point->second;
                        ppoint->mIsGetCurVale = false;
                        ppoint->mIsGetPreVale = false;
                        ppoint->mIsGetSimVale = false;
                        g_iter = mode_info->mMapGroup.begin();
                        for (;g_iter!=mode_info->mMapGroup.end();++g_iter)
                        {
                            p_iter = g_iter->second->mMapGroupPoint.find(ppoint->mStrPointId);
                            if (p_iter == g_iter->second->mMapGroupPoint.end())
                            {
                                continue;
                            }
                            else
                            {
                                if (mode_info->m_IsCalOk)
                                {
                                    if (p_iter->second->m_IsGetOrigValue)
                                    {
                                        ppoint->mDcurValue = p_iter->second->getCurrVar(1);
                                        ppoint->mIsGetCurVale = true;
                                    }
                                    if (p_iter->second->m_IsGetPreValue)
                                    {
                                        ppoint->mDpreValue = p_iter->second->getCurrVar(2);
                                        ppoint->mIsGetPreVale = true;
                                    }
                                    if (p_iter->second->m_IsGetSimValue)
                                    {
                                        ppoint->mDsim= p_iter->second->getCurrVar(3);
                                        ppoint->mIsGetSimVale = true;
                                    }
                                }
                                else
                                {
                                    if (p_iter->second->m_IsGetOrigValue)
                                    {
                                        ppoint->mDcurValue = p_iter->second->getCurrVar(1);
                                        ppoint->mIsGetCurVale = true;
                                    }
                                    else
                                        ppoint->mIsGetCurVale = false;
                                }
                                break;
                            }
                        }
                        /*p_iter = mode_info->mMapModePoint.find(ppoint->mStrPointId);
                        if (p_iter == mode_info->mMapModePoint.end())
                        {
                            continue;
                        }
                        if (mode_info->m_IsCalOk)
                        {
                            if (p_iter->second->m_IsGetOrigValue)
                            {
                                ppoint->mDcurValue = p_iter->second->getCurrVar(1);
                                ppoint->mIsGetCurVale = true;
                            }
                            if (p_iter->second->m_IsGetPreValue)
                            {
                                ppoint->mDpreValue = p_iter->second->getCurrVar(2);
                                ppoint->mIsGetPreVale = true;
                            }
                            if (p_iter->second->m_IsGetSimValue)
                            {
                                ppoint->mDsim= p_iter->second->getCurrVar(3);
                                ppoint->mIsGetSimVale = true;
                            }
                        }
                        else
                        {
                            if (p_iter->second->m_IsGetOrigValue)
                            {
                                ppoint->mDcurValue = p_iter->second->getCurrVar(1);
                                ppoint->mIsGetCurVale = true;
                            }
                            else
                                ppoint->mIsGetCurVale = false;
                        }*/
                        SetMaxMinArv(ppoint);
                    }
                }
            }
        }
    }
}
void AlarmSetDeal::SetMaxMinArv(AlarmPointInfo* point)
{
    if (point->mStrPointId=="gjcyxt_1gj_D3_3AIFB07")
        int i =100;
    if (point->mDate.m_init)
    {
        point->mIsInitCurVale = false;
        point->mIsInitPreVale = false;
        point->mIsInitSimVale = false;
        if (point->mIsGetCurVale)
        {
            point->m_iCount = 1;
            point->m_maxValue = point->mDcurValue;
            point->m_minValue = point->mDcurValue;
            point->m_avgValue = point->mDcurValue;
            point->mDate.m_init = false;
            point->mIsInitCurVale = true;
        }
        else
            return;

        if (point->mIsGetPreVale)
        {
            point->m_pmaxValue = point->mDpreValue;
            point->m_pminValue = point->mDpreValue;
            point->m_pavgValue = point->mDpreValue;
            point->mIsInitPreVale = true;
        }
        if (point->mIsGetSimVale)
        {
            point->m_savgValue = point->mDsim;
            point->mIsInitSimVale = true;
        }
    }
    else
    {
        if (point->mIsGetCurVale)
        {
            if (point->m_maxValue<point->mDcurValue)
            {
                point->m_maxValue = point->mDcurValue;
            }
            if (point->m_minValue>point->mDcurValue)
            {
                point->m_minValue = point->mDcurValue;
            }
            point->m_avgValue=(point->m_avgValue*point->m_iCount+point->mDcurValue)/(point->m_iCount+1);
            point->m_iCount+=1;
            point->mIsInitCurVale = true;
        }
        if (point->mIsGetPreVale)
        {
            if (point->m_pmaxValue<point->mDpreValue)
            {
                point->m_pmaxValue = point->mDpreValue;
            }
            if (point->m_pminValue>point->mDpreValue)
            {
                point->m_pminValue = point->mDpreValue;
            }
            point->m_pavgValue=(point->m_pavgValue*point->m_iCount+point->mDpreValue)/(point->m_iCount+1);
            point->mIsInitPreVale = true;
        }
        if (point->mIsGetSimVale)
        {
            point->m_savgValue=(point->m_savgValue*point->m_iCount+point->mDsim)/(point->m_iCount+1);
            point->mIsInitSimVale = true;
        }
    }
}
//bool 
//SetDeal::loadDB(MapStringToSetInfo &mMapSetInfo)
//{
//	Aos_Assert_R(Util::OtlIsConnect(), false);
//
//	Aos_Assert_R(stmtPrepare(CON_SET_DEAL, g_strSetSQL, mBufferSize), false);
//	Aos_Assert_R(loadValue(mMapSetInfo), false);
//	Aos_Assert_R(stmtCloseStream(CON_SET_DEAL), false); 
//	return true;
//}
//
//bool 
//SetDeal::loadValue(MapStringToSetInfo &mMapSetInfo)
//{
//	bool nErr = false;
//	/*while (!mQtOpt->SQLStmtFetch())
//	{			
//		int nNumber = 0;
//		PubSetInfo  *pSet = new PubSetInfo();
//		nErr = mQtOpt->BindOutputByName(pSelection->mModelId);
//		Aos_Assert_R(nErr, false);
//
//		nErr = mQtOpt->BindOutputByName(pSelection->mOriginalSTimeInfo->mSampleTimeId);
//		Aos_Assert_R(nErr, false);
//
//		std::string strStartDate;
//		nErr = mQtOpt->BindOutputByName(strStartDate);
//		Aos_Assert_R(nErr, false);
//		if (!strStartDate.empty()) 
//		{
//			pSelection->mOriginalSTimeInfo->mStartTime = PubOpt::SystemOpt::StrToDateTm(strStartDate);
//		}
//
//		std::string strEndDate;
//		nErr = mQtOpt->BindOutputByName(strEndDate);
//		Aos_Assert_R(nErr, false);
//		if (!strEndDate.empty()) 
//		{
//			pSelection->mOriginalSTimeInfo->mEndTime = PubOpt::SystemOpt::StrToDateTm(strEndDate);
//		}
//
//		nErr = mQtOpt->BindOutputByName(pSelection->mOriginalSTimeInfo->mStep);
//		Aos_Assert_R(nErr, false);
//		pVectorModelSelection.push_back(pSelection);
//	}
//	Aos_WriteLog(PubOpt::StringOpt::StringFormat("Load %s Info Total: %d",
//		CON_SET_DEAL, pVectorModelSelection.size()).c_str());*/
//	return true;
//}

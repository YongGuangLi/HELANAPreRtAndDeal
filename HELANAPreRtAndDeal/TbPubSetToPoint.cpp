#include "TbPubSetToPoint.h"

#include "AlarmLog.h"
#include "Util.h"
#include "public_function_library.h"

TbPubSetToPoint::TbPubSetToPoint()
    :
      RDbOperationComplex()
{
}
TbPubSetToPoint::TbPubSetToPoint(RsdbAdapter * QtOpt)   
    :
      RDbOperationComplex(QtOpt)
{
}
TbPubSetToPoint::~TbPubSetToPoint(void)
{

}
bool 
TbPubSetToPoint::loadDB(MapStringToSetCfg &SetInfo,MapStringToBool &mMapModleNameStatus,std::string strCon)
{
    Aos_Assert_R(Util::QtConnect(mQtOpt,strCon), false);
    std::string strSql = PubOpt::StringOpt::StringFormat(g_strSetToPointSQL.c_str(),strCon.c_str());
    Aos_Assert_R(stmtPrepare(CFG_CONFIG, strSql), false);
    //mQtOpt->QtQuerySelect(g_strModeSQL);
    bool is_ok=loadValue(SetInfo,mMapModleNameStatus);
    stmtCloseStream();
    return is_ok;
}
bool TbPubSetToPoint::loadValue(MapStringToSetCfg &mapSetInfo,MapStringToBool &mMapModleNameStatus)
{
    std::string strSet,strSetCode,strSetJkd,strSys,strSysJkd,strModel,strModelJkd,strStatus,strStatusRtdb,strCondSouce,strCondtionId,strConLocal,strOutVar,strFun,strExp;
    std::string strGroup,strGroupJkd,strMoint,strModelSource,strPoint,strSourceIdOr,strSourceId,strSourceIdPer,strSimilarId;
    std::string strSetJkdValue,strSysJkdValue,strModelJkdValue,strGroupJkdValue,strPointJkdValue;
    std::string strAid;
    std::string errmsg;
    double sysWeight,modelWeight,groupWeight,aSource,CondtionValue,ValueType,ValueNum;
    std::string aMax,aMin,aCap,aValue;
    SetCfg *  setcf;
    SysCfg *  syscf;
    DataMode* mode_info;
    ModelCondition* mode_condtion;
    PointGroup* group_p;
    DataValueInfo* point_info;

    MapStringToSetCfg_It   set_iter;
    MapStringToSysCfg_It   sys_iter;
    MapStringToDataMode_It iter;
    MapStringToModeCond_It c_iter;
    MapStringToPointGroup_It g_iter;
    MapStringToMDataValueInfo_It p_iter;
    //VectorString_It v_it;
    MapStringToBool_It v_it;

    if(mQtOpt->QtGetResultIsValid())
        return false;

    while (mQtOpt->SQLStmtFetch())
    {
        strSet = std::string(mQtOpt->m_query->value(0).toString().toLocal8Bit());
        strSetCode =  std::string(mQtOpt->m_query->value(1).toString().toLocal8Bit());
        strSetJkd = std::string(mQtOpt->m_query->value(2).toString().toLocal8Bit());
        strSys = std::string(mQtOpt->m_query->value(3).toString().toLocal8Bit());
        strSysJkd = std::string(mQtOpt->m_query->value(4).toString().toLocal8Bit());
        sysWeight = mQtOpt->m_query->value(5).toDouble();

        strModel = std::string(mQtOpt->m_query->value(6).toString().toLocal8Bit());
        strModelJkd = std::string(mQtOpt->m_query->value(7).toString().toLocal8Bit());
        modelWeight = mQtOpt->m_query->value(8).toDouble();

        strStatus = std::string(mQtOpt->m_query->value(9).toString().toLocal8Bit());
        strStatusRtdb = std::string(mQtOpt->m_query->value(10).toString().toLocal8Bit());

        strCondSouce = std::string(mQtOpt->m_query->value(11).toString().toLocal8Bit());
        strCondtionId = std::string(mQtOpt->m_query->value(12).toString().toLocal8Bit());
        CondtionValue = mQtOpt->m_query->value(13).toDouble();
        strConLocal = std::string(mQtOpt->m_query->value(14).toString().toLocal8Bit());
        strOutVar = std::string(mQtOpt->m_query->value(15).toString().toLocal8Bit());
        strFun = std::string(mQtOpt->m_query->value(16).toString().toLocal8Bit());
        strExp = std::string(mQtOpt->m_query->value(17).toString().toLocal8Bit());

        strGroup = std::string(mQtOpt->m_query->value(18).toString().toLocal8Bit());
        strGroupJkd = std::string(mQtOpt->m_query->value(19).toString().toLocal8Bit());
        groupWeight = mQtOpt->m_query->value(20).toDouble();
        ValueType = mQtOpt->m_query->value(21).toInt();
        ValueNum = mQtOpt->m_query->value(22).toInt();

        strPoint = std::string(mQtOpt->m_query->value(23).toString().toLocal8Bit());
        strMoint = std::string(mQtOpt->m_query->value(24).toString().toLocal8Bit());
        strSourceIdOr = std::string(mQtOpt->m_query->value(25).toString().toLocal8Bit());
        strSourceId = std::string(mQtOpt->m_query->value(26).toString().toLocal8Bit());
        strSourceIdPer = std::string(mQtOpt->m_query->value(27).toString().toLocal8Bit());
        strSimilarId = std::string(mQtOpt->m_query->value(28).toString().toLocal8Bit());

        strAid = std::string(mQtOpt->m_query->value(29).toString().toLocal8Bit());
        aMax = std::string(mQtOpt->m_query->value(30).toString().toLocal8Bit());
        aMin = std::string(mQtOpt->m_query->value(31).toString().toLocal8Bit());
        aCap = std::string(mQtOpt->m_query->value(32).toString().toLocal8Bit());
        aSource = mQtOpt->m_query->value(33).toDouble();
        aValue = std::string(mQtOpt->m_query->value(34).toString().toLocal8Bit());

        strSetJkdValue = std::string(mQtOpt->m_query->value(35).toString().toLocal8Bit());
        strSysJkdValue = std::string(mQtOpt->m_query->value(36).toString().toLocal8Bit());
        strModelJkdValue = std::string(mQtOpt->m_query->value(37).toString().toLocal8Bit());
        strGroupJkdValue = std::string(mQtOpt->m_query->value(38).toString().toLocal8Bit());
        strPointJkdValue = std::string(mQtOpt->m_query->value(39).toString().toLocal8Bit());

        if (strSet.empty())
        {
            Aos_Assert_S("机组编号是空");
            continue;
        }
        set_iter = mapSetInfo.find(strSet);
        if (set_iter == mapSetInfo.end())
        {
            setcf = new SetCfg();
            mapSetInfo.insert(make_pair(strSet, setcf));
            setcf->mSet = strSet;
            setcf->mSetCode = strSetCode;
        }
        else
        {
            setcf = set_iter->second;
        }
        if(!strSetJkd.empty())
        {
            setcf->mSetJkd  = strSetJkd;
            if(!strSetJkdValue.empty())
                setcf->mSetJkdValue = Util::CharPointerConvert2Number<double>(strSetJkdValue.c_str());
            else
                setcf->mSetJkdValue = 0;
        }
        else
        {
            setcf->mSetJkd  = "";
        }
        if (strSys.empty())
        {
            Aos_Assert_S("系统编号是空");
            continue;
        }
        sys_iter = setcf->mMapSys.find(strSys);
        if (sys_iter==setcf->mMapSys.end())
        {
            syscf = new SysCfg();
            setcf->mMapSys.insert(make_pair(strSys,syscf));
            syscf->mSys = strSys;
            if (!strSysJkd.empty())
            {
                syscf->mSysJkd = strSysJkd;
                if(!strSysJkdValue.empty())
                    syscf->mSysJkdValue = Util::CharPointerConvert2Number<double>(strSysJkdValue.c_str());
                else
                    syscf->mSysJkdValue = 0;
            }
            else
            {
                syscf->mSysJkd = "";
            }
            syscf->mSysWeight = sysWeight;
        }
        else
        {
            syscf = sys_iter->second;
        }

        if (strModel.empty())
        {
            Aos_Assert_S("模型编号是空");
            continue;
        }

        iter=syscf->mMapModles.find(strModel);
        if (iter==syscf->mMapModles.end())
        {
            mode_info = new DataMode();
            syscf->mMapModles.insert(make_pair(strModel,mode_info));
            mode_info->mModeId = strModel;
            mode_info->mSimPoint = strModelJkd;
            if (!strModelJkd.empty())
            {
                if(!strModelJkdValue.empty())
                    mode_info->mDModeSim = Util::CharPointerConvert2Number<double>(strModelJkdValue.c_str());
                else
                    mode_info->mDModeSim = 0;
            }

            mode_info->mDModeWeight = modelWeight;
            mode_info->mStatus = strStatus;
            mode_info->mStatusSource = strStatusRtdb;
            mode_info->mCondIdSource = strCondSouce;

            v_it = mMapModleNameStatus.find(strModel);
            if(v_it == mMapModleNameStatus.end())
            {
                mMapModleNameStatus.insert(make_pair(strModel,false));
            }

        }
        else
            mode_info = iter->second;

        //获取模型的模式
        if (strCondtionId.empty())
        {
            errmsg=PubOpt::StringOpt::StringFormat("mode'id：%s include empty CondtionId",strModel.c_str());
            Aos_Assert_S(errmsg.c_str());
            continue;
        }
        c_iter=mode_info->mMapModeCond.find(strCondtionId);
        if (c_iter==mode_info->mMapModeCond.end())
        {
            mode_condtion= new ModelCondition();
            mode_info->mMapModeCond.insert(make_pair(strCondtionId,mode_condtion));
        }
        else
            mode_condtion= c_iter->second;

        mode_condtion->m_ModelConditionId= strCondtionId;
        mode_condtion->m_ModelConditionValue = CondtionValue;
        mode_condtion->m_modelId= mode_info->mModeId;
        mode_condtion->m_strLocalVar= strConLocal;
        mode_condtion->m_strOutVar= strOutVar;
        mode_condtion->m_strOutVarFun = strFun;
        mode_condtion->m_Exp = strExp;

        if (c_iter==mode_info->mMapModeCond.end())
        {
            setOutVarAndFunc(mode_condtion->m_strOutVar,mode_info->mCondPointVector);

            mode_condtion->setOutVarAndFunc();
        }
        if(strGroup.empty())
        {
            Aos_Assert_S("分类编号是空");
            continue;
        }
        g_iter = mode_info->mMapGroup.find(strGroup);
        if (g_iter== mode_info->mMapGroup.end())
        {
            group_p = new PointGroup();
            mode_info->mMapGroup.insert(make_pair(strGroup,group_p));
            group_p->m_Group = strGroup;
            group_p->m_GroupJkd = strGroupJkd;
            if (!strGroupJkd.empty())
            {
                if(!strGroupJkdValue.empty())
                    group_p->m_JkdValue = Util::CharPointerConvert2Number<double>(strGroupJkdValue.c_str());
                else
                    group_p->m_JkdValue = 0;
            }
            group_p->m_GroupWeight = groupWeight;
            group_p->m_ValueType = ValueType;
            group_p->m_ValueNum = ValueNum;
        }
        else
        {
            group_p = g_iter->second;
        }

        p_iter=group_p->mMapGroupPoint.find(strPoint);
        if (p_iter==group_p->mMapGroupPoint.end())
        {
            point_info=new DataValueInfo();
            //group_p->mMapGroupPoint.insert(make_pair(strPoint,point_info));
            group_p->mMapGroupPoint.insert(make_pair(strMoint,point_info));
        }
        else
            point_info=p_iter->second;

        point_info->mPointId=strPoint;
        point_info->mMonitPointId = strMoint;
        point_info->mPOrigSource = strSourceIdOr;
        if(!point_info->mPOrigSource.empty()) point_info->mRtdbPOrigSourceIsExist=true;

        point_info->mPointSource = strSourceId;
        if(!point_info->mPointSource.empty()) point_info->mRtdbPointSourceIsExist=true;

        point_info->mPreSource = strSourceIdPer;
        if(!point_info->mPreSource.empty()) point_info->mRtdbPreSourceIsExist=true;

        point_info->mSimSource = strSimilarId;
        if(!point_info->mSimSource.empty()) point_info->mRtdbSimSourceIsExist=true;
        if (!strSimilarId.empty())
        {
            if(!strPointJkdValue.empty())
                point_info->mDSimValue = Util::CharPointerConvert2Number<double>(strPointJkdValue.c_str());
            else
                point_info->mDSimValue = 0;
        }
        //loadAparam(mode_info->mVectorParamCfgs,strPoint,aSource,aCap,aValue,aMax,aMin);
        loadAparam(mode_info->mVectorParamCfgs,strMoint,aSource,aCap,aValue,aMax,aMin);

    }
    return true;
}
void TbPubSetToPoint::loadAparam(std::vector<VarParam>& mVectorParamCfgs,std::string& strPoint,double& aSource,
                                 std::string& aCap,std::string& aValue,std::string& aMax,std::string& aMin)
{
    for (int i = 0;i < mVectorParamCfgs.size(); i++)
    {
        if(mVectorParamCfgs[i].mPoint == strPoint)
            return;
    }
    VarParam aCfg;
    aCfg.mPoint = strPoint;
    aCfg.m_iParamSource = aSource;
    if (aCap.empty())
    {
        aCfg.m_iType = 3;
    }
    else
    {
        aCfg.m_iType = atoi(aCap.c_str());
        aCfg.m_iType = Util::CharPointerConvert2Number<int>(aCap.c_str());
    }
    if (aValue.empty())
    {
        aCfg.m_ParamValue = 0;
    }
    else
    {
        aCfg.m_ParamValue = Util::CharPointerConvert2Number<double>(aValue.c_str());
    }
    if (aMax.empty())
    {
        aCfg.m_Interval.m_IsUpLimit = false;
    }
    else
    {
        aCfg.m_Interval.m_IsUpLimit = true;
        aCfg.m_Interval.m_UpLimit = Util::CharPointerConvert2Number<double>(aMax.c_str());
    }
    if (aMin.empty())
    {
        aCfg.m_Interval.m_IsLowLimit = false;
    }
    else
    {
        aCfg.m_Interval.m_IsLowLimit = true;
        aCfg.m_Interval.m_LowLimit = Util::CharPointerConvert2Number<double>(aMin.c_str());
    }
    mVectorParamCfgs.push_back(aCfg);
}

void  
TbPubSetToPoint::setOutVarAndFunc(const std::string strParse,VectorString  &mVectorConPoint)
{
    std::string strOutVar;
    bool rslt;
    strOutVar=strParse;
    if (strOutVar.empty()) return;										//输出变量
    if (!strOutVar.empty())
    {
        /*if(strOutVar.substr(strOutVar.size()-1,1) != ",")
        {
            strOutVar = strOutVar + "," ;
        }*/
        if(strOutVar.substr(0,1) == ",")
        {

            strOutVar = strOutVar.substr(1,strOutVar.size()-1);
        }
    }
    rslt = Util::StringSplit(strOutVar, mVectorConPoint, ",");
}
bool 
TbPubSetToPoint::loadDBPoint(MapStringTostrEX &mMapPointSourceName,std::string strCon)
{
    Aos_Assert_R(Util::QtConnect(mQtOpt), false);
    //Aos_Assert_R(stmtPrepare(CFG_CONFIG, g_strAllPointSQL), false);
    std::string strSql = PubOpt::StringOpt::StringFormat(g_strAllPointSQL.c_str(),strCon.c_str());
    Aos_Assert_R(stmtPrepare(CFG_CONFIG, strSql), false);
    bool is_ok = loadValue(mMapPointSourceName);
    stmtCloseStream();
    return is_ok;
}


bool 
TbPubSetToPoint::loadValue(MapStringTostrEX &mMapAllPointSourceName)
{
    std::string strCode,strSouce,strSet,strFullCode;

    if(mQtOpt->QtGetResultIsValid())
        return false;

    while (mQtOpt->SQLStmtFetch())
    {
        //qDebug()<<mQtOpt->m_query->value(0).toString()<<nNumber;
        strCode = std::string(mQtOpt->m_query->value(0).toString().toLocal8Bit());
        strSouce = std::string(mQtOpt->m_query->value(1).toString().toLocal8Bit());
        strSet =  std::string(mQtOpt->m_query->value(2).toString().toLocal8Bit());
        strFullCode =  std::string(mQtOpt->m_query->value(3).toString().toLocal8Bit());
        if(mMapAllPointSourceName.find(strCode) == mMapAllPointSourceName.end()&&!strSouce.empty())
        {
            strEX strDev;
            strDev.str1 =  strSouce;
            strDev.str2 = strSet;
            strDev.strFullCode = strFullCode;
            mMapAllPointSourceName.insert(make_pair(strCode,strDev));
        }
    }
    return true;
}

void TbPubSetToPoint::InsertMapStringToPointData(MapStringToPointData& mMapPointData,
                                                 std::string strPoint,std::string strSouce,std::string strSet,PointType itype)
{
    DataInfo* point_data;
    MapStringToPointData_It p_iter;
    p_iter = mMapPointData.find(strPoint);
    if (p_iter==mMapPointData.end())
    {
        point_data = new DataInfo();
        mMapPointData.insert(make_pair(strPoint,point_data));
        point_data->mPointId = strPoint;
        point_data->mPSource = strSouce;
        point_data->mSet = strSet;
        point_data->mPointType = itype;
    }
}
void 
TbPubSetToPoint::GetNeedPoint(MapStringToString &mMapAllPointSourceName,MapStringToString &mMapPointSourceName,
                              MapStringToSetCfg &SetInfo,MapStringToPointData& mMapPointData)
{
    std::string strSouce,strCode;
    SetCfg *  setcf;
    SysCfg *  syscf;
    //ModelCondition* mode_condtion;
    MapStringToSetCfg_It   set_iter;
    MapStringToSysCfg_It   sys_iter;
    MapStringToString_It p_it1,p_it2;
    DataMode* mode_info;
    PointGroup* group_p;
    DataInfo* point_data;
    DataValueInfo* point_info;
    MapStringToDataMode_It iter;
    MapStringToModeCond_It c_iter;
    MapStringToPointGroup_It g_iter;
    MapStringToPointData_It point_data_it;
    MapStringToMDataValueInfo_It p_iter;

    //MapStringToPointData_It p_iter;
    MapStringToDataMode_It m_iter;
    VectorString_It			cp_iter;
    for (set_iter = SetInfo.begin();set_iter != SetInfo.end();++set_iter)
    {
        setcf = set_iter->second;
        InsertMapStringToPointData(mMapPointData,setcf->mSetJkd,setcf->mSetJkd,setcf->mSetCode,eSim);
        InsertMapStringToPointData(mMapPointData,setcf->mSetDfh,setcf->mSetDfh,setcf->mSetCode,eDfh);
        for(sys_iter = setcf->mMapSys.begin();sys_iter!=setcf->mMapSys.end();++sys_iter )
        {
            syscf = sys_iter->second;
            InsertMapStringToPointData(mMapPointData,syscf->mSysJkd,syscf->mSysJkd,setcf->mSetCode,eSim);
            InsertMapStringToPointData(mMapPointData,syscf->mSysDfh,syscf->mSysDfh,setcf->mSetCode,eDfh);
            m_iter = syscf->mMapModles.begin();
            for (;m_iter!= syscf->mMapModles.end();++m_iter)
            {
                mode_info = m_iter->second;
                InsertMapStringToPointData(mMapPointData,mode_info->mSimPoint,mode_info->mSimPoint,setcf->mSetCode,eSim);
                g_iter = mode_info->mMapGroup.begin();
                for (;g_iter!=mode_info->mMapGroup.end();++g_iter)
                {
                    group_p = g_iter->second;
                    InsertMapStringToPointData(mMapPointData,group_p->m_GroupJkd,group_p->m_GroupJkd,setcf->mSetCode,eSim);
                    p_iter = group_p->mMapGroupPoint.begin();
                    for (;p_iter!= group_p->mMapGroupPoint.end();++p_iter)
                    {
                        point_info = p_iter->second;
                        if (point_info->mRtdbPOrigSourceIsExist)
                        {
                            InsertMapStringToPointData(mMapPointData,point_info->mPointId,point_info->mPOrigSource,setcf->mSetCode,eRealTimeDPoint);
                        }
                        if (point_info->mRtdbPointSourceIsExist)
                        {
                            InsertMapStringToPointData(mMapPointData,point_info->mPointSource,point_info->mPointSource,setcf->mSetCode,eRealTimeDPoint);
                        }
                        if (point_info->mRtdbPreSourceIsExist)
                        {
                            InsertMapStringToPointData(mMapPointData,point_info->mPreSource,point_info->mPreSource,setcf->mSetCode,ePreDPoint);
                        }
                        if (point_info->mRtdbSimSourceIsExist)
                        {
                            InsertMapStringToPointData(mMapPointData,point_info->mSimSource,point_info->mSimSource,setcf->mSetCode,eSimDPoint);
                        }
                        strCode=p_iter->second->mPointId;
                        strSouce=p_iter->second->mPOrigSource;
                        p_it2=mMapPointSourceName.find(strSouce);
                        if(p_it2==mMapPointSourceName.end())
                        {
                            mMapPointSourceName.insert(make_pair(strSouce,strCode));
                        }
                        else
                        {
                            if(std::string::npos!=p_it2->second.find(strCode))
                                continue;
                            if (p_it2->second.substr(p_it2->second.size()-1,1)!=",")
                            {
                                p_it2->second+=",";
                            }
                            p_it2->second+=strCode;
                        }
                    }
                }
                cp_iter = mode_info->mCondPointVector.begin();
                for (;cp_iter!=mode_info->mCondPointVector.end();++cp_iter)
                {
                    strCode = "";
                    strSouce = "";
                    strCode = *cp_iter;
                    p_it1= mMapAllPointSourceName.find(strCode);
                    if (p_it1!= mMapAllPointSourceName.end())
                    {
                        strSouce = p_it1->second;
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
                                    point_data= new DataInfo();
                                    mMapPointData.insert(make_pair(strCode,point_data));
                                    point_data->mPointId=strCode;
                                    point_data->mPSource=strSouce;
                                    point_data->mSet = setcf->mSet;
                                    if ("D"==strCode.substr(0))
                                    {
                                        point_data->mPointType = eRealTimeDPoint;
                                    }
                                    else if ("M"==strCode.substr(0))
                                    {
                                        point_data->mPointType = eIndex;
                                    }
                                    else
                                    {
                                        point_data->mPointType = eInvalid;
                                    }
                                }
                                continue;
                            }
                            if (p_it2->second.substr(p_it2->second.size()-1,1)!=",")
                            {
                                p_it2->second+=",";
                            }
                            p_it2->second+=strCode;
                        }
                    }
                }
            }
        }
    }
}

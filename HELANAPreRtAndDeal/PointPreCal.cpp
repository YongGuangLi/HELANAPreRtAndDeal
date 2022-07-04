#include <algorithm>
#include <vector>
#include "PointPreCal.h"
#include "public_function_library.h"
#include "AlarmLog.h"
#include "../funlib/AlgoFunc.h"
#include "RecursiveCalculateIndex.h"
#include "Util.h"
#include "mutex.h"
//#pragma  comment(lib,"DiagAlgorithmLib.lib")
//#include "..\fun\dll\Debug\AlgoFunc.h"

//IMPLEMENT_SINGLETON(PointPreCal)

PointPreCal::PointPreCal(void)
    :
      m_pMutexLock(NULL),
      mCalculateIndex(NULL)
{
    //Init();
    //SetStdWasp(97);
    m_pMutexLock = new MutexLock();
}

PointPreCal::PointPreCal(RecursiveCalculateIndex *pCalculateIndex):m_pMutexLock(NULL)
{
    mCalculateIndex = pCalculateIndex;
    m_pMutexLock = new MutexLock();
}

PointPreCal::~PointPreCal(void)
{
    if (NULL != m_pMutexLock)
    {
        delete m_pMutexLock;
        m_pMutexLock = NULL;
    }
    pm.clear();
    mt.clear();
    //Destory();
}

void PointPreCal::CalData(MapStringToBool &mMapModleNameStatus,
                          MapStringToSetCfg &mMapSetInfo,
                          MapStringToModeMethodAvg &mModeMethodAvg,
                          MapStringToPointData	&mMapPointData,
                          MapStringToIndexConfInfo &pMapIndexConfInfo,
                          MapStringToDouble &mMapWrite,
                          GetDateWay itype)
{
    CalculatePre(mMapModleNameStatus, mMapSetInfo, mModeMethodAvg, mMapWrite, itype);
}

void PointPreCal::CalculateAllModeCon(MapStringToSetCfg &mMapSetInfo,
                                      MapStringToPointData	&mMapPointData,
                                      MapStringToIndexConfInfo &pMapIndexConfInfo,
                                      MapStringToDouble &mMapWrite)
{
    MapStringToSetCfg_It    iter_set;
    MapStringToSysCfg_It	iter_sys;
    SetCfg * setobj;
    SysCfg * sysobj;
    AutoLock autoLock(*m_pMutexLock);
    iter_set = mMapSetInfo.begin();
    for (;iter_set!=mMapSetInfo.end();++iter_set)
    {
        setobj = iter_set->second;
        iter_sys = setobj->mMapSys.begin();
        for (;iter_sys!=setobj->mMapSys.end();++iter_sys)
        {
            sysobj = iter_sys->second;
            CalculateModeCon(sysobj->mMapModles,mMapPointData,pMapIndexConfInfo,mMapWrite);
        }
    }
}
void PointPreCal::CalculateModeCon(MapStringToDataMode &mModeInfo,
                                   MapStringToPointData	&mMapPointData,
                                   MapStringToIndexConfInfo &pMapIndexConfInfo,
                                   MapStringToDouble &mMapWrite)
{
    double fValue;

    for (MapStringToDataMode_It iter_m = mModeInfo.begin(); iter_m != mModeInfo.end(); ++iter_m)
    {
        DataMode* mode_info = iter_m->second;
        mode_info->mCondValue = -1;

        for (MapStringToModeCond_It iter_con = mode_info->mMapModeCond.begin();iter_con != mode_info->mMapModeCond.end();++iter_con)
        {
            ModelCondition *mode_con=iter_con->second;
            std::string strLocVar = mode_con->m_strLocalVar;
            if (!strLocVar.empty() && strLocVar.substr(strLocVar.size() - 1, 1) == ",")
            {
                strLocVar = strLocVar.substr(0, strLocVar.size() - 1);
            }
            if (strLocVar.substr(0, 1) == ",")
            {
                strLocVar = strLocVar.substr(1, strLocVar.size() - 1);
            }
            strLocVar= PubOpt::StringOpt::TrimString(strLocVar);

            std::string strExp = PubOpt::StringOpt::TrimString(mode_con->m_Exp);

            std::string strOutVarVal = "";
            for(unsigned int i = 0; i< mode_con->m_OutFuncVarArray.size(); i++)             //外部变量+外部函数变量
            {
                std::string strTemp = mode_con->m_OutFuncVarArray[i];
                std::string strICode = strTemp;
                int iIndex = strTemp.find("@");
                if (iIndex != -1)
                    strICode = PubOpt::StringOpt::StringReplace(strICode,"@","_");

                strOutVarVal += strICode;
                strOutVarVal += "=";
                //strValue = getParamValue(mode_con->m_ModelConditionId,strTemp,mMapPointData);
                std::string strValue = mCalculateIndex->getParamValue(pMapIndexConfInfo, mMapPointData, mode_con->m_ModelConditionId, strTemp);
                strOutVarVal += strValue;
                strOutVarVal += ",";
            }
            if (!strOutVarVal.empty())
            {
                strOutVarVal = strOutVarVal.substr(0,strOutVarVal.size() - 1);     //外部变量
            }

            try
            {
                if(!strExp.empty())
                {
                    fValue = mCalculateIndex->calEngine(mode_con->m_ModelConditionId,  mode_con->m_strTranOutVarFun, strLocVar, strOutVarVal, strExp);
                    //std::string tt = PubOpt::StringOpt::StringFormat("calEngine value %s=%f;",pIndexConfInfo->mIndexCode.c_str(), fValue);
                    //Aos_WriteLog_D(tt.c_str());

                    std::string tt = PubOpt::StringOpt::StringFormat("calEngine strExp:%s mTranOutVarAndFun:%s strOutVarVal:%s value:%f;",
                                                                     strExp.c_str(),
                                                                     mode_con->m_strTranOutVarFun.c_str(),
                                                                     strOutVarVal.c_str(),
                                                                     fValue);
                    Aos_WriteLog_D(tt.c_str());
                }

            }
            catch (...)
            {
                std::string strInfo = PubOpt::StringOpt::StringFormat("调用计算引擎计算错误,公式验证错误,请检查指标的配置公式,模式ID:%s", mode_con->m_ModelConditionId.c_str());
                Aos_Assert_S(strInfo.c_str());
            }

            if(1 == fValue)
            {
                mode_info->m_IsDeal = true;
                mode_info->mCondValue = mode_con->m_ModelConditionValue;
                mode_info->mCondId = mode_con->m_ModelConditionId;
                break;
            }
            else
            {
                mode_info->m_IsDeal = false;
                mode_info->mCondId = NonMonitoring;
                mode_info->mCondValue = -1;
            }
        }

        MapStringToDouble_It rw_iter = mMapWrite.find(mode_info->mCondIdSource);
        if (rw_iter == mMapWrite.end())
            mMapWrite.insert(make_pair(mode_info->mCondIdSource, mode_info->mCondValue));
        else
            rw_iter->second = mode_info->mCondValue;
    }
}
//double 
//PointPreCal::calEngine(std::string szICode,
//								   std::string szEngOutVar,
//								   std::string szEngLocVar,
//								   std::string szEngEvalVar,
//								   std::string szEngExp)
//{
//	double fVal = 0;
//
//	static char*CbTag=NULL;
//	static char* CbError=NULL;
//
//	try
//	{
//		PROGRAM(const_cast<char*>(szEngOutVar.c_str()),const_cast<char*>(szEngLocVar.c_str()),const_cast<char*>(szEngExp.c_str()),&CbTag,&CbError);
//	}
//	catch(...)
//	{
//		std::string strInfo = PubOpt::StringOpt::StringFormat("调用计算引擎申请计算错误,公式验证错误,请检查指标的配置公式,指标ID:%s", szICode.c_str());
//		Aos_Assert_S(strInfo.c_str());
//	}
//
//	if (CbTag == NULL)
//	{
//		std::string strInfo = PubOpt::StringOpt::StringFormat("调用计算引擎申请计算错误,公式验证错误,请检查指标的配置公式,指标ID:%s", szICode.c_str());
//		Aos_Assert_S(strInfo.c_str());
//		return 0;
//	}
//
//	try
//	{
//		CALCULATE(CbTag,const_cast<char*>(szEngEvalVar.c_str()),&fVal,&CbError);
//	}
//	catch(...)
//	{
//		std::string strInfo = PubOpt::StringOpt::StringFormat("调用计算引擎计算指标错误 指标ID:%s;", szICode.c_str());
//		Aos_Assert_S(strInfo.c_str());
//	}
//
//	RealseRec(CbTag,CbError);
//	if (CbTag != NULL)
//	{
//		delete []CbTag;
//		CbTag = NULL;
//	}
//	if (CbError != NULL)
//	{
//		delete []CbError;
//		CbError = NULL;
//	}
//	return fVal;
//}
//
//std::string 
//PointPreCal::getParamValue(const std::string szParentId,const std::string szChildId,MapStringToPointData &mMapPointData)
//{
//	//MapStringToMDataValueInfo_It it;
//	MapStringToPointData_It  it;
//	double fValue = 0;
//	std::string strValue, strTemp, strICode, strInfo;
//	std::string strEleUpper;
//	std::string strFirParam, strSecParam,strTarType;
//
//	std::string strUpperParam = szChildId;
//	strUpperParam = PubOpt::StringOpt::StringUpper(strUpperParam);
//	strUpperParam = PubOpt::StringOpt::TrimString(strUpperParam);
//
//	std::string strLocalParam = szChildId;
//	strLocalParam = PubOpt::StringOpt::TrimString(strLocalParam);
//
//	if (strLocalParam.empty())                                   
//	{
//		strValue = "0";
//		return strValue;
//	}
//
//	int iIndex = strLocalParam.find("@");
//	if (iIndex != -1)  //外部函数变量为实时点、耗差指标、手工指标、绩效指标	
//	{
//		//if(M_NOW == strUpperParam.substr(0,4))
//		//{
//		//	//NOW(0)表示当前时间
//		//	//系统时间 "小时.分"
//		//	t = mCnPeriodDateTm;
//		//	fValue = PubOpt::SystemOpt::GetHour(t);
//		//	fTemp = PubOpt::SystemOpt::GetMinute(t);
//		//	fValue = fValue + fTemp/100;
//		//}
//		////YEAR(0)表示当前时间的年，MONTH(0)表示当前时间的月，DAY(0)表示当前时间的日
//		//else if(M_YEAR == strUpperParam.substr(0,5))
//		//{
//		//	t = mCnPeriodDateTm;
//		//	fValue = PubOpt::SystemOpt::GetYear(t);
//		//}
//		//else if(M_MONTH == strUpperParam.substr(0,6))
//		//{
//		//	t = mCnPeriodDateTm;
//		//	fValue = PubOpt::SystemOpt::GetMonth(t);
//		//}
//		//else if(M_WEEK == strUpperParam.substr(0,5))
//		//{
//		//	t = mCnPeriodDateTm;
//		//	fValue = PubOpt::SystemOpt::GetDayOfWeek(t);         // 1:礼拜天 2:礼拜一 。。。7:礼拜六
//		//}
//		//else if(M_DAY == strUpperParam.substr(0,4))
//		//{
//		//	t = mCnPeriodDateTm;
//		//	fValue = PubOpt::SystemOpt::GetDay(t);
//		//}
//		strValue = PubOpt::StringOpt::StringFormat("%.06f",fValue);
//	}
//	else
//	{
//		strValue = "0";
//		it = mMapPointData.find(strLocalParam);
//		if (it==mMapPointData.end())
//		{
//			std::string strInfo = PubOpt::StringOpt::StringFormat("没有取到%s的元素的值,元素指标%s的值用当前指标值或实时值代替,函数组合体%s",
//				strLocalParam.c_str(), strLocalParam.c_str(), strLocalParam.c_str());  
//			//Aos_Assert_S(strInfo.c_str());
//			
//			return strValue;
//		}
//		strValue = PubOpt::StringOpt::StringFormat("%.06f", it->second->getCurrVar(1));
//	}
//	return strValue;
//}
void PointPreCal::CalDfhPoint(IN const double defFh,IN const double RtimeFh,
                              IN const double dValue, IN  MapStringToIntervalEX &mMapInterval,
                              OUT double &fValue,const bool is_tj)
{
    double devValue,rtValue;
    IntervalEX inter;
    devValue = defFh;
    if (is_tj)
    {
        fValue = devValue;
        return;
    }
    MapStringToIntervalEX_It it = mMapInterval.begin();
    for (;it!=mMapInterval.end();++it)
    {
        inter = it->second;
        switch (inter.m_DataType)
        {
        case -1:
            fValue = defFh;
            break;
        case 1:
            rtValue = inter.m_value;
            break;
        case 0:
            rtValue = RtimeFh;
            break;
        default:
            fValue = RtimeFh;
            break;
        }
        if (0==inter.m_DataType||1==inter.m_DataType)
        {
            if(inter.m_interval.m_IsLowLimit&&inter.m_interval.m_IsUpLimit)
            {
                if(dValue<inter.m_interval.m_LowLimit||dValue>inter.m_interval.m_UpLimit)
                    fValue = rtValue;
                else
                    fValue = defFh;
            }
            if(inter.m_interval.m_IsLowLimit&&!inter.m_interval.m_IsUpLimit)
            {
                if(dValue<inter.m_interval.m_LowLimit)
                    fValue = rtValue;
                else
                    fValue = defFh;
            }
            if(!inter.m_interval.m_IsLowLimit&&inter.m_interval.m_IsUpLimit)
            {
                if(dValue>inter.m_interval.m_UpLimit)
                    fValue = rtValue;
                else
                    fValue = defFh;
            }
            if(!inter.m_interval.m_IsLowLimit&&!inter.m_interval.m_IsUpLimit)
            {
                fValue = defFh;
            }
        }


        devValue =(devValue<=fValue)?devValue:fValue;
    }
    fValue = devValue;
}
void PointPreCal::GetPointToMapWrite(MapStringToDouble &mMapWrite,MapStringToPointData	&mMapPointData)
{
    DataInfo* point;
    MapStringToPointData_It p_iter;
    MapStringToDouble_It  it_rw;
    p_iter = mMapPointData.begin();
    for (;p_iter!=mMapPointData.end();++p_iter)
    {
        if(eRealTimeOrgDPoint !=p_iter->second->mPointType)
            continue;
        point = p_iter->second;
        it_rw = mMapWrite.find(point->mPSource);
        if (it_rw==mMapWrite.end())
        {
            mMapWrite.insert(make_pair(point->mPSource,point->mDValue));
        }
        else
            it_rw->second = point->mDValue;
    }
}
void PointPreCal::CalDfh(MapStringToSetCfg &mMapSetInfo,MapStringToPointData &mMapPointData,MapStringToDouble &mMapWrite)
{
    bool is_TJ;
    SysCfg * sysobj;
    SetCfg * setobj;
    Dfhnl * dfh;
    DataInfo* point;
    MapStringToSetCfg_It set_iter;
    MapStringToSysCfg_It sys_iter;
    MapStringToDfhnl_It    d_iter;
    MapStringToPointData_It p_iter;
    MapStringToDouble_It  it_rw;
    set_iter = mMapSetInfo.begin();
    //double setsum,setsumw;
    for (;set_iter!=mMapSetInfo.end();++set_iter)
    {
        setobj = set_iter->second;
        setobj->mSetDfhValue = setobj->mSetDefFh;
        p_iter = mMapPointData.find(setobj->mSetFh);
        if (p_iter!=mMapPointData.end())
        {
            setobj->mSetRfFh = p_iter->second->getCurrVar(1);
        }
        is_TJ = false;
        MapStringToPointData_It  dp_iter = mMapPointData.find(setobj->mSetTJ);
        if (dp_iter!=mMapPointData.end())
        {
            is_TJ = (0==dp_iter->second->getCurrVar(1))?true:false;
        }
        sys_iter = setobj->mMapSys.begin();
        for (;sys_iter!=setobj->mMapSys.end();++sys_iter)
        {
            sysobj = sys_iter->second;
            sysobj->mSysDfhValue = setobj->mSetDefFh;
            if(sysobj->mSys=="ZZ_3_gjcyq")
                int tre =100;
            d_iter = sysobj->mMapSysDfhnl.begin();
            for(;d_iter!=sysobj->mMapSysDfhnl.end();++d_iter)
            {
                dfh = d_iter->second;
                p_iter = mMapPointData.find(dfh->m_code);
                if (p_iter == mMapPointData.end())
                {
                    sysobj->mSysDfhValue = setobj->mSetDefFh;
                    continue;
                }
                point = p_iter->second;
                if (point->mPointId=="D3_POTE32")
                    int ter =100;
                CalDfhPoint(setobj->mSetDefFh,setobj->mSetRfFh,point->mDValue,dfh->m_VectorDfhInterval,dfh->m_dfhValue,is_TJ);
                sysobj->mSysDfhValue = sysobj->mSysDfhValue<=dfh->m_dfhValue?sysobj->mSysDfhValue:dfh->m_dfhValue;
            }
            if (!sysobj->mSysDfh.empty()||""!=sysobj->mSysDfh)
            {
                p_iter = mMapPointData.find(sysobj->mSysDfh);
                if (p_iter != mMapPointData.end())
                {
                    p_iter->second->mDValue = sysobj->mSysDfhValue;
                }
                it_rw=mMapWrite.find(sysobj->mSysDfh);
                if(it_rw==mMapWrite.end())
                    mMapWrite.insert(make_pair(sysobj->mSysDfh,sysobj->mSysDfhValue));
                else
                    it_rw->second = sysobj->mSysDfhValue;
                setobj->mSetDfhValue = setobj->mSetDfhValue<=sysobj->mSysDfhValue?setobj->mSetDfhValue:sysobj->mSysDfhValue;
            }

        }
        p_iter = mMapPointData.find(setobj->mSetDfh);
        if (p_iter!=mMapPointData.end())
        {
            p_iter->second->mDValue = setobj->mSetDfhValue;
        }
        it_rw = mMapWrite.find(setobj->mSetDfh);
        if(it_rw == mMapWrite.end())
            mMapWrite.insert(make_pair(setobj->mSetDfh, setobj->mSetDfhValue));
        else
            it_rw->second = setobj->mSetDfhValue;
    }
}
void PointPreCal::CalculatePre(MapStringToBool &mMapModleNameStatus,MapStringToSetCfg &mMapSetInfo,
                               MapStringToModeMethodAvg &mModeMethodAvg,
                               MapStringToDouble &mMapWrite,GetDateWay itype)
{
    for ( MapStringToSetCfg_It set_iter = mMapSetInfo.begin(); set_iter != mMapSetInfo.end(); ++set_iter)
    {
        double setsum = 0;
        double setsumw = 0;
        SetCfg * setobj = set_iter->second;
        MapStringToSysCfg_It sys_iter = setobj->mMapSys.begin();
        for (;sys_iter != setobj->mMapSys.end(); ++sys_iter)
        {
            double sum = 0;
            double sumw = 0;
            SysCfg * sysobj = sys_iter->second;
            for (MapStringToDataMode_It iter_m = sysobj->mMapModles.begin(); iter_m != sysobj->mMapModles.end(); ++iter_m)
            {
                DataMode* mode_info = iter_m->second;
                mode_info->m_IsCalOk= false;

                //LINXIAOYU   mMapModleNameStatus 在avg表里有模型数据
                MapStringToBool_It it_ok = mMapModleNameStatus.find(mode_info->mModeId);
                if (it_ok == mMapModleNameStatus.end())
                    mode_info->m_IsDeal = false;
                else
                    mode_info->m_IsDeal = it_ok->second;

                DcPreDeal(mode_info, mModeMethodAvg, mMapWrite, sum, sumw);
            }

            sysobj->mSysJkdValue = sum;

            if(sysobj->mRtdbSysJkdIsExist && 0 != sysobj->mSysWeight && 0 != sysobj->mSysJkdValue)
            {
                MapStringToDouble_It it_rw = mMapWrite.find(sysobj->mSysJkd);
                if(it_rw == mMapWrite.end())
                    mMapWrite.insert(make_pair(sysobj->mSysJkd, sysobj->mSysJkdValue));
                else
                    it_rw->second = sysobj->mSysJkdValue;
            }

            if(0 != sysobj->mSysWeight && 0 != sysobj->mSysJkdValue)
            {
                //setsumw += sysobj->mSysWeight;
                //setsum += sysobj->mSysWeight/sysobj->mSysJkdValue;
                //                setsumw += pow(sysobj->mSysWeight, 2) / sysobj->mSysJkdValue;
                //                setsum += pow(sysobj->mSysWeight / sysobj->mSysJkdValue, 2);
                setsum += sysobj->mSysWeight * sysobj->mSysJkdValue;
            }

        }

        if (0 == setsum)
            setobj->mSetJkdValue = 0;
        else
            setobj->mSetJkdValue = setsum;  // setobj->mSetJkdValue = setsumw / setsum;

        if (setobj->mRtdbSetJkdIsExist && 0 != setobj->mSetJkdValue)
        {
            MapStringToDouble_It it_rw = mMapWrite.find(setobj->mSetJkd);
            if(it_rw==mMapWrite.end())
                mMapWrite.insert(make_pair(setobj->mSetJkd,setobj->mSetJkdValue));
            else
                it_rw->second = setobj->mSetJkdValue;
        }
    }
}
void PointPreCal::DcPreDeal(DataMode* mode_info,MapStringToModeMethodAvg &mModeMethodAvg,
                            MapStringToDouble &mMapWrite,double  &sum,double &sumw)
{
    MethodAvg* mode_fun;
    MapStringToDouble_It  it_rw;
    double msim = 0;

    mode_info->m_IsCalOk= false;
    MapStringToModeMethodAvg_It con_iter = mModeMethodAvg.find(mode_info->mModeId);
    if(con_iter == mModeMethodAvg.end() || !mode_info->m_IsDeal)
    {
        if(mode_info->mRtdbSimModleIsWrite)
        {
            it_rw = mMapWrite.find(mode_info->mSimPoint);
            if(it_rw==mMapWrite.end())
            {
                mMapWrite.insert(make_pair(mode_info->mSimPoint, mode_info->mDModeSim));
            }
            else
            {
                it_rw->second = mode_info->mDModeSim;
            }
        }

        MapStringToPointGroup_It iter_g = mode_info->mMapGroup.begin();
        for (;iter_g!=mode_info->mMapGroup.end();++iter_g)
        {
            PointGroup* model_group = iter_g->second;
            if (model_group->mRtdbGroupJkdIsExist)
            {
                it_rw = mMapWrite.find(model_group->m_GroupJkd);
                if(it_rw==mMapWrite.end())
                {
                    if(0!=model_group->m_JkdValue)
                        mMapWrite.insert(make_pair(model_group->m_GroupJkd,model_group->m_JkdValue));
                }
                else
                {
                    if(0!=model_group->m_JkdValue)
                        it_rw->second = model_group->m_JkdValue;
                }
            }

            MapStringToMDataValueInfo_It it = model_group->mMapGroupPoint.begin();
            for (;it!=model_group->mMapGroupPoint.end();++it)
            {
                if(!it->second->mRtdbPointSourceIsExist) continue;
                it_rw=mMapWrite.find(it->second->mPointSource);
                if(it_rw==mMapWrite.end())
                {
                    if(0!=it->second->getCurrVar(1))
                        mMapWrite.insert(make_pair(it->second->mPointSource,it->second->getCurrVar(1)));
                }
                else
                {
                    if(0!=it->second->getCurrVar(1))
                        it_rw->second=it->second->getCurrVar(1);
                }
            }

        }
        mode_info->mDModeSim = 0;
        return;
    }

    ModeMethodAvg* mMethodAvg = con_iter->second;
    MapStringToMethodAvg_It fun_iter = mMethodAvg->mMapmethodavg.find(mode_info->mCondId);
    if(fun_iter == mMethodAvg->mMapmethodavg.end() || !mode_info->m_IsDeal)
    {
//        MapStringToPointGroup_It iter_g = mode_info->mMapGroup.begin();
//        for (;iter_g != mode_info->mMapGroup.end(); ++iter_g)
//        {
//            PointGroup* model_group = iter_g->second;
//            MapStringToMDataValueInfo_It it = model_group->mMapGroupPoint.begin();
//            for (;it!=model_group->mMapGroupPoint.end();++it)
//            {
//                PreValueToMapWrite(it->second, mMapWrite, true);
//            }
//        }
//        CalGroupSim(mode_info, mMapWrite);
//        if(0 == mode_info->mDModeWeight || 0 == mode_info->mDModeSim)
//            return;
//        sumw += pow(mode_info->mDModeWeight, 2) / mode_info->mDModeSim;
//        sum += pow(mode_info->mDModeWeight / mode_info->mDModeSim, 2);
//        mode_info->mDModeSim;
        sum += 0;
        return;
    }

    mode_fun = fun_iter->second;
    pm.clear();
    mt.clear();

    if(0 == mode_info->mVectorParamCfgs.size() || 0 == mode_fun->mVectorRelationValue.size())
        return;

    if(!SIMROWDealEx(mode_info->mVectorParamCfgs,mode_fun->mVectorRelationValue,mode_fun->mVectorMaValue,mode_fun->mVectorFunValue, msim, pm, mt, err))
    {
        std::string errMessge = PubOpt::StringOpt::StringFormat("模型%s计算期望值失败,失败原因：%s",mode_info->mModeId.c_str(),err.c_str());
        Aos_WriteLog(errMessge.c_str());
        return;
    }
    mode_info->m_IsCalOk= true;

    SetPreValue(mode_info, mode_fun, msim, pm, mt, mMapWrite);

    //LiyG 修改jkd算法
//    if(0 == mode_info->mDModeWeight || 0 == mode_info->mDModeSim)
//        return;
//    sumw += pow(mode_info->mDModeWeight, 2) / mode_info->mDModeSim;
//    sum += pow(mode_info->mDModeWeight / mode_info->mDModeSim, 2);

    sum += mode_info->mDModeWeight * mode_info->mDModeSim;

}

void PointPreCal::DwPreDeal(DataMode* mode_info,MapStringToDouble &mMapWrite,double  &sum,double &sumw)
{
    PointGroup* model_group;
    MapStringToPointGroup_It iter_g;
    MapStringToModeMethodAvg_It con_iter;
    MapStringToMethodAvg_It fun_iter;
    MapStringToMDataValueInfo_It it;
    MapStringToDouble_It  it_rw;
    double msim = 0;
    std::string errMessge;

    if(mode_info->mModeId=="4_zc"||mode_info->mModeId=="4_zc")
        int i=100;
    mode_info->m_IsCalOk= false;
    pm.clear();
    mt.clear();
    mode_info->mDModeSim = 0;
    if(mode_info->m_IsDeal)
    {
        iter_g = mode_info->mMapGroup.begin();
        for (;iter_g!=mode_info->mMapGroup.end();++iter_g)
        {
            model_group = iter_g->second;
            it = model_group->mMapGroupPoint.begin();
            for (;it!=model_group->mMapGroupPoint.end();++it)
            {
                if ("DDM.ZZEIDS.D4_FLN02AM"==it->second->mPointSource)
                    int itemp = 100;
                if(!it->second->mRtdbPointSourceIsExist) continue;
                PreValueToMapWrite(it->second,mMapWrite);
                if(it->second->mRtdbPreSourceIsExist)
                {
                    pm.push_back(it->second->getCurrVar(2));
                    /*Aos_WriteLog(PubOpt::StringOpt::StringFormat("点名： %s 点值: %f",
                            str1.c_str(), m_v).c_str()); */
                }
                if(it->second->mRtdbSimSourceIsExist)
                {
                    mt.push_back(it->second->getCurrVar(3));
                }
            }

        }
        CalGroupSim(mode_info,mMapWrite);
    }

    mode_info->m_IsCalOk= true;
    if(0==mode_info->mDModeWeight||0==mode_info->mDModeSim)
        return;
    //sumw += mode_info->mDModeWeight;
    //sum += mode_info->mDModeWeight/mode_info->mDModeSim;

    sumw += pow(mode_info->mDModeWeight,2)/mode_info->mDModeSim;
    sum += pow(mode_info->mDModeWeight/mode_info->mDModeSim,2);
}
void PointPreCal::SetPreValue(DataMode* mode_info,MethodAvg* mode_fun,const double sim,
                              const std::vector<double> pm,const std::vector<double> mt,
                              MapStringToDouble &mMapWrite)
{
    MapStringToMDataValueInfo_It it;
    MapStringToDouble_It  it_rw;

    PointGroup* pgroup;
    MapStringToPointGroup_It it_g;
    std::string err;
    /*mode_info->mDModeSim=sim;
   mode_info->mSimLimit = mode_fun->mDSimLimit;
   if ("4_zc"==mode_info->mModeId)
   {
       int i = 100;
   }
   if(mode_info->mDModeSim<mode_fun->mDSimLimit)
        mode_info->mIsSimAlarm = true;
   else
        mode_info->mIsSimAlarm = false;

   if(mode_info->mRtdbSimModleIsWrite)
   {
        it_rw=mMapWrite.find(mode_info->mSimSource);
        if(it_rw==mMapWrite.end())
           mMapWrite.insert(make_pair(mode_info->mSimSource,mode_info->mDModeSim));
        else
           it_rw->second=mode_info->mDModeSim;

   }*/
    if (mode_fun->mVectorModePoint.size()==pm.size()&&mode_fun->mVectorModePoint.size()==mt.size())
    {
        //std::string str1;double m_v;
        for(int i=0;i<mode_fun->mVectorModePoint.size();++i)
        {
            it_g = mode_info->mMapGroup.begin();
            for (;it_g!=mode_info->mMapGroup.end();++it_g)
            {
                pgroup = it_g->second;
                it = pgroup->mMapGroupPoint.find(mode_fun->mVectorModePoint[i]);
                if(it!=pgroup->mMapGroupPoint.end())
                {
                    it->second->setCurrVar(mt[i],2);
                    it->second->m_IsGetPreValue = true;
                    it->second->setCurrVar(pm[i],3);
                    it->second->m_IsGetSimValue = true;
                    PreValueToMapWrite(it->second,mMapWrite);
                    break;
                }
            }
        }

    }
    else
    {
        err = PubOpt::StringOpt::StringFormat("模型%s计算期望值集合与模型测点个数不匹配！",mode_info->mModeId.c_str());
        Aos_WriteLog(err.c_str());
    }
    it_g = mode_info->mMapGroup.begin();
    for (;it_g != mode_info->mMapGroup.end(); ++it_g)
    {
        pgroup = it_g->second;
        it = pgroup->mMapGroupPoint.begin();
        for(;it != pgroup->mMapGroupPoint.end(); ++it)   //模型有些点可能不参与训练原始值还是要回写，比如一个模型下有50个点，但训练的只有40个点
        {
            if(!it->second->mRtdbPointSourceIsExist) continue;
            it_rw = mMapWrite.find(it->second->mPointSource);
            if(it_rw == mMapWrite.end())
            {
                mMapWrite.insert(make_pair(it->second->mPointSource,it->second->getCurrVar(1)));
            }
        }
    }
    CalGroupSim(mode_info,mMapWrite);
}
void PointPreCal::CalGroupSim(DataMode* mode_info,MapStringToDouble &mMapWrite)
{
    double sum = 0;
    double sumw = 0;
    MapStringToPointGroup_It it_g = mode_info->mMapGroup.begin();
    for (;it_g!=mode_info->mMapGroup.end();++it_g)
    {
        std::vector<double> vecdev;
        PointGroup* pgroup = it_g->second;

        MapStringToMDataValueInfo_It it = pgroup->mMapGroupPoint.begin();
        for (;it!=pgroup->mMapGroupPoint.end();++it)
        {
            vecdev.push_back(it->second->getCurrVar(3));
        }
        sort(vecdev.begin(),vecdev.end());
        int num = vecdev.size();
        //add by wk 2018-7-3 参数类去尾操作
        if ((1 == pgroup->m_ValueType) && (0 != pgroup->m_ValueNum) && (pgroup->m_ValueNum < vecdev.size()))
        {
            for(int i = 0;i < pgroup->m_ValueNum; i++)
            {
                vecdev.erase(vecdev.begin());
            }
            num = vecdev.size();
            pgroup->m_JkdValue = vecdev[0];
        }
        //end by wk 2018-7-3 参数类去尾操作
        else
        {
            if (num % 2 == 0)
            {
                pgroup->m_JkdValue = (vecdev[num / 2 - 1] + vecdev[num / 2]) / 2;
            }
            else
            {
                pgroup->m_JkdValue = vecdev[num / 2];
            }
        }

        if(0 == pgroup->m_GroupWeight || 0 == pgroup->m_JkdValue)
            continue;

        if(pgroup->mRtdbGroupJkdIsExist)
        {
            MapStringToDouble_It it_rw = mMapWrite.find(pgroup->m_GroupJkd);
            if(it_rw == mMapWrite.end())
            {
                mMapWrite.insert(make_pair(pgroup->m_GroupJkd,pgroup->m_JkdValue));
            }
            else
            {
                it_rw->second = pgroup->m_JkdValue;
            }

        }

        //sumw += pgroup->m_GroupWeight;
        //sum += pgroup->m_GroupWeight/pgroup->m_JkdValue;

        sumw += pow(pgroup->m_GroupWeight,2) / pgroup->m_JkdValue;
        sum += pow(pgroup->m_GroupWeight / pgroup->m_JkdValue,2);
    }

    if (0 == sum)
    {
        mode_info->mDModeSim = 0;
    }
    else
    {
        mode_info->mDModeSim = sumw / sum;
    }

    if(mode_info->mRtdbSimModleIsWrite)
    {
        //add by wk 2018-7-19
        if (0 == mode_info->mDModeSim)
            return;

        //end add
        MapStringToDouble_It it_rw = mMapWrite.find(mode_info->mSimPoint);
        if(it_rw==mMapWrite.end())
        {
            mMapWrite.insert(make_pair(mode_info->mSimPoint,mode_info->mDModeSim));
        }
        else
        {
            it_rw->second = mode_info->mDModeSim;
        }
    }

}
void PointPreCal::PreValueToMapWrite(DataValueInfo *pointData,MapStringToDouble &mMapWrite,bool isGetLast)
{
    MapStringToDouble_It  it_rw;
    if (isGetLast)
    {
        pointData->m_IsGetSimValue = true;
    }
    if(pointData->m_IsGetOrigValue)
    {
        it_rw=mMapWrite.find(pointData->mPointSource);
        if(it_rw==mMapWrite.end())
        {
            //if(0!=pointData->getCurrVar(1))
            mMapWrite.insert(make_pair(pointData->mPointSource, pointData->getCurrVar(1)));
        }
        else
        {
            //if(0!=pointData->getCurrVar(1))
            it_rw->second = pointData->getCurrVar(1);
        }
    }
    
    if(pointData->m_IsGetPreValue)
        //if(pointData->mRtdbPreSourceIsExist)
    {
        it_rw = mMapWrite.find(pointData->mPreSource);
        if(it_rw==mMapWrite.end())
        {
            //if(0!=pointData->getCurrVar(2))
            mMapWrite.insert(make_pair(pointData->mPreSource,pointData->getCurrVar(2)));
        }
        else
        {
            //if(0!=pointData->getCurrVar(2))
            it_rw->second = pointData->getCurrVar(2);
        }
        
        /*Aos_WriteLog(PubOpt::StringOpt::StringFormat("点名： %s 点值: %f",
            str1.c_str(), m_v).c_str()); */
    }

    if(pointData->m_IsGetSimValue)
    {
        it_rw = mMapWrite.find(pointData->mSimSource);
        if(it_rw==mMapWrite.end())
        {
            //if(0!=pointData->getCurrVar(3))
            mMapWrite.insert(make_pair(pointData->mSimSource,pointData->getCurrVar(3)));
        }
        else
        {
            //if(0!=pointData->getCurrVar(3))
            it_rw->second = pointData->getCurrVar(3);
        }
    }
}

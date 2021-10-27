/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: RecursiveCalculateIndex.cpp
* 文件描述: 递归计算指标实现类
*  作  者 : %林晓雨%，
* 创建日期: 2015-7-9 16:24:38
*******************************************************************************/

#include "RecursiveCalculateIndex.h"
#include "AlarmLog.h"
#include "public_function_library.h"
#include "mutex.h"

#include <math.h>
#include <iostream>

//IMPLEMENT_SINGLETON(RecursiveCalculateIndex)

MutexLock*   RecursiveCalculateIndex::smMutexLock = new MutexLock();

RecursiveCalculateIndex::RecursiveCalculateIndex()
{
    mCnPeriodDateTm = 0;
    mPeriodTime = SINGLETON(ServiceEIDSPreConfig)->getServiceCalCycSec();
    mFirstCal = false;
    mElefTime = 0;
    mElefFrontTime = 0;
    //	Init();
    //	SetStdWasp(97);
}


RecursiveCalculateIndex::~RecursiveCalculateIndex()
{
}


bool
RecursiveCalculateIndex::startCalculate(
        MapStringToIndexConfInfo &pMapIndexConfInfo,
        MapStringToPointData &pMapDataValue,
        MapStringToDouble &mMapWrite,
        const long &pRtdbTime)
{
    //std::cout << pMapIndexConfInfo.size() << ":" << pMapPubSetInfo.size() << ":" << pMapDataValueInfo.size() << ";"<< std::endl;
    Aos_Assert_R(!pMapDataValue.empty(), false);
    //Aos_Assert_R(!pMapPubSetInfo.empty(), false);
    Aos_Assert_R(!pMapIndexConfInfo.empty(), false);
    Aos_Assert_R(pRtdbTime > 0, false);

    //mCnPeriodDateTm = (time_t)lTime;
    calculateSetCondition(pMapIndexConfInfo, pMapDataValue);
    calculateIndex(pMapIndexConfInfo, pMapDataValue,mMapWrite);
    //sanityCheck(pMapDataValueInfo);
    /*sanityCheck1(pMapDataValueInfo);
    sanityCheck2(pMapDataValueInfo);
    sanityCheck3(pMapDataValueInfo);*/
    return true;
}

// 功能描述:
void
RecursiveCalculateIndex::calculateSetCondition(
        MapStringToIndexConfInfo &pMapIndexConfInfo,
        MapStringToPointData &pMapDataValueInfo)
{

    //MapStringToIndexConfInfo_It i_itr;

    //calIndexParam(pMapIndexConfInfo, pMapDataValueInfo, i_itr->second);

}



/*---------------------------------------------------------------------------------*/
//	函数名称:	RecursiveCalculateIndex::calculateIndex
//	功能描述:	计算指标的指标值
//	输入参数:	
//				void
//	返回值:		
//				void                   
/*---------------------------------------------------------------------------------*/
void 
RecursiveCalculateIndex::calculateIndex(
        MapStringToIndexConfInfo &pMapIndexConfInfo,
        MapStringToPointData &pMapDataValueInfo,
        MapStringToDouble &mMapWrite)
{
    MapStringToIndexConfInfo_It iter;

    MapStringToPointData_It  dp_iter;
    MapStringToDouble_It	 rw_iter;
    IndexConfigInfo* index_conf_info = NULL;

    //开始计算指标
    for(iter = pMapIndexConfInfo.begin(); iter != pMapIndexConfInfo.end(); ++iter)
    {
        //获取指标指针和ID
        index_conf_info = iter->second;
        if(!index_conf_info->mNew)                 //此指标没有计算
        {
            calIndexParam(pMapIndexConfInfo,pMapDataValueInfo, index_conf_info);
        }

        if (!index_conf_info->mIsWriteRdtb)
        {
            std::string strLog = PubOpt::StringOpt::StringFormat("%s is_write_back = 0.",index_conf_info->mIndexCode.c_str());
            Aos_WriteLog_D(strLog.c_str());
            continue;
        }

        dp_iter = pMapDataValueInfo.find(index_conf_info->mIndexCode);
        if (dp_iter !=pMapDataValueInfo.end())   //回写插入启停指标
        {
            rw_iter = mMapWrite.find(dp_iter->second->mPSource);
            if (rw_iter==mMapWrite.end())
                mMapWrite.insert(make_pair(dp_iter->second->mPSource,dp_iter->second->getCurrVar(1)));
            else
                rw_iter->second = dp_iter->second->getCurrVar(1);
        }
    }

}



/*---------------------------------------------------------------------------------*/
//	函数名称:	RecursiveCalculateIndex::calIndexParam
//	功能描述:	计算煤耗指标的所有成员,包括指标值
//	输入参数:	
//				IndexConfigInfo* pIndexConfInfo        指标类信息
//				PubSetInfo* pPubSetInfo       机组状态类信息
//	返回值:		
//				void                   
/*---------------------------------------------------------------------------------*/
void 
RecursiveCalculateIndex::calIndexParam(
        MapStringToIndexConfInfo &pMapIndexConfInfo,
        MapStringToPointData &pMapDataValueInfo,
        IndexConfigInfo* pIndexConfInfo)
{
    //用计算引擎计算配置公式
    mForeIndexForUsed.clear();
    mForeIndexForUsed.push_back(pIndexConfInfo->mIndexCode);
    calculateArith(pMapIndexConfInfo,pMapDataValueInfo, pIndexConfInfo);    //根据指标的计算公式进行指标计算，得到指标值

    mForeIndexForUsed.clear();
}


/*----------------------------------------------------------------------------*/
//	函数名称:	RecursiveCalculateIndex::calculateArith
//	功能描述:	调用计算引擎计算耗差指标值
//	输入参数:	
//				IndexConfigInfo* pIndexConfInfo     指标信息类
//	返回值:		
//				void
/*----------------------------------------------------------------------------*/
void 
RecursiveCalculateIndex::calculateArith(
        MapStringToIndexConfInfo &pMapIndexConfInfo,
        MapStringToPointData &pMapDataValueInfo,
        IndexConfigInfo* pIndexConfInfo)
{
    pIndexConfInfo->mIsCalState = 1;           //绩效指标当前正在计算

    std::string strLocVar = pIndexConfInfo->mLocalVar;                  //本地变量
    if (!strLocVar.empty()&&strLocVar.substr(strLocVar.size()-1,1) == ",")
    {
        strLocVar = strLocVar.substr(0,strLocVar.size()-1);
    }
    if (strLocVar.substr(0,1) == ",")
    {
        strLocVar = strLocVar.substr(1,strLocVar.size()-1);
    }
    strLocVar= PubOpt::StringOpt::TrimString(strLocVar);

    std::string strExp = pIndexConfInfo->mExpression;
    strExp= PubOpt::StringOpt::TrimString(strExp);

    int iIndex = 0;
    std::string strOutVarVal = "";
    std::string strTemp, strICode, strValue;
    for(unsigned int i = 0; i< pIndexConfInfo->mOutFuncVarArray.size(); i++)             //外部变量+外部函数变量
    {
        strTemp = pIndexConfInfo->mOutFuncVarArray[i];
        strICode = strTemp;
        iIndex = strTemp.find("@");
        if (iIndex != -1)
        {
            strICode = PubOpt::StringOpt::StringReplace(strICode,"@","_");
        }

        strOutVarVal += strICode;
        strOutVarVal += "=";
        strValue = getParamValue(pMapIndexConfInfo, pMapDataValueInfo, pIndexConfInfo->mIndexCode,strTemp);
        strOutVarVal += strValue;
        strOutVarVal += ",";
    }
    //去掉最后的","(逗号)
    if (!strOutVarVal.empty())
    {
        strOutVarVal = strOutVarVal.substr(0,strOutVarVal.size()-1);     //外部变量
    }

    ////此指标配置有机组才计算
    /*if(pMapPubSetInfo.find(pIndexConfInfo->mSetCode) == pMapPubSetInfo.end())
    {
        return;
    }*/
    //if (pIndexConfInfo->mIndexCode=="M3_FH"||pIndexConfInfo->mIndexCode=="M4_FH")
    //	int tep = 100;
    double fValue = 0;
    try
    {
        if(!strExp.empty())
        {
            fValue = calEngine(pIndexConfInfo->mIndexCode, pIndexConfInfo->mTranOutVarAndFun, strLocVar, strOutVarVal, strExp);
            //if (pIndexConfInfo->mIndexCode == "M3_2yhtpfqdhgbz" || pIndexConfInfo->mIndexCode == "M1_SWDL")
            //{
            //std::string tt = PubOpt::StringOpt::StringFormat(
            //	"calEngine mTranOutVarAndFun:%s,strLocVar:%s,strOutVarVal:%s,value %s=%f;",
            // pIndexConfInfo->mTranOutVarAndFun.c_str(),
            // strLocVar.c_str(),
            // strOutVarVal.c_str(),
            // pIndexConfInfo->mIndexCode.c_str(),
            //fValue);
            //Aos_WriteLog_D(tt.c_str());
            //}
        }
        
    }
    catch (...)
    {
        MapStringToPointData_It iter = pMapDataValueInfo.find(pIndexConfInfo->mIndexCode);
        if(iter != pMapDataValueInfo.end())
        {
            iter->second->mError = 0;
        }
        
        std::string strInfo;
        if (pIndexConfInfo->mExpression.size() > 400)
        {
            strInfo = PubOpt::StringOpt::StringFormat(IDS_INDEX_CONFVAR_ERROR, pIndexConfInfo->mIndexCode.c_str(), "公式字符过长", pIndexConfInfo->mTranOutVarAndFun.c_str());
        }
        else
        {
            strInfo = PubOpt::StringOpt::StringFormat(
                        IDS_INDEX_CONFIG_ERROR, pIndexConfInfo->mIndexCode.c_str(),
                        pIndexConfInfo->mExpression.c_str(),pIndexConfInfo->mFDefaultVal);
        }
        
        Aos_Assert_S(strInfo.c_str());
        fValue = pIndexConfInfo->mFDefaultVal;
    }

    checkIndexValue(pMapIndexConfInfo, pMapDataValueInfo, pIndexConfInfo, pIndexConfInfo->mIndexCode, fValue, pIndexConfInfo->mFDefaultVal);
    pIndexConfInfo->mNew = true;							//计算此指标后，此标志设置为真
    pIndexConfInfo->mIsCalState = 0;						//指标当前没有计算
}



/*----------------------------------------------------------------------------*/
//	函数名称:	RecursiveCalculateIndex::calEngine
//	功能描述:	调用计算引擎计算指标的指标值或得分区间百分比
//	输入参数:	
//				CString szICode				  绩效指标名称
//				CString szEngOutVar		      引擎的外部变量
//				CString szEngLocVar           引擎的内部变量
//				CString szEngEvalVar          引擎赋值的外部变量
//				CString szEngExp              引擎的公式表达式
//	返回值:		
//				void
/*----------------------------------------------------------------------------*/
double 
RecursiveCalculateIndex::calEngine(std::string szICode,
                                   std::string szEngOutVar,
                                   std::string szEngLocVar,
                                   std::string szEngEvalVar,
                                   std::string szEngExp)
{
    AutoLock autoLock(*smMutexLock);
    double fVal = 0;

    static char*CbTag=NULL;
    static char* CbError=NULL;
    //    try
    //    {
    //		PROGRAM(const_cast<char*>(szEngOutVar.c_str()),const_cast<char*>(szEngLocVar.c_str()),const_cast<char*>(szEngExp.c_str()),&CbTag,&CbError);
    //    }
    //    catch(...)
    //    {
    //		std::string strInfo = PubOpt::StringOpt::StringFormat(IDS_PROGRAM, szICode.c_str());
    //		Aos_Assert_S(strInfo.c_str());
    //    }

    if (CbTag == NULL)
    {
        std::string strInfo = PubOpt::StringOpt::StringFormat(IDS_PROGRAM, szICode.c_str());
        //LINXIAOYU
        //Aos_Assert_S(strInfo.c_str());
        return 0;
    }

    //    try
    //    {
    //        CALCULATE(CbTag,const_cast<char*>(szEngEvalVar.c_str()),&fVal,&CbError);
    //    }
    //    catch(...)
    //    {
    //		std::string strInfo = PubOpt::StringOpt::StringFormat(IDS_CALCULATE, szICode.c_str());
    //		Aos_Assert_S(strInfo.c_str());
    //    }
    //	if (CbTag != NULL)
    //		RealseRec(CbTag,CbError);

    if (CbTag != NULL)
    {
        delete []CbTag;
        CbTag = NULL;
    }
    if (CbError != NULL)
    {
        delete []CbError;
        CbError = NULL;
    }
    return fVal;
}

/*----------------------------------------------------------------------------*/
//	函数名称:	RecursiveCalculateIndex::checkIndexValue
//	功能描述:	检查指标值的正确性,并保存指标值到计算结果map内存中
//	输入参数:	
//				CString szICode           指标编号ID
//              double fIndexVal          指标值
//              double fDefaultVal        指标默认值
//				CIndexBase* pIBase        指标信息类
//	返回值:		
//				void
/*----------------------------------------------------------------------------*/
void 
RecursiveCalculateIndex::checkIndexValue(
        MapStringToIndexConfInfo &pMapIndexConfInfo,
        MapStringToPointData &pMapDataValueInfo,
        IndexConfigInfo* pIndexConfInfo,
        std::string szICode,
        double fIndexVal,
        double fDefaultVal)
{
    //double fMinVal = 0;
    //double fMaxVal = 0;
    double fValue = 0;
    //double fFhVal = 0;
    //double fJqVal = 0;
    // double fFhAddVal = 0;
    DataInfo* data_value_info ;
    MapStringToPointData_It iter = pMapDataValueInfo.find(szICode);
    if(iter!= pMapDataValueInfo.end())
    {
        data_value_info = iter->second;
    }
    else
    {
        data_value_info = new DataInfo();
        data_value_info->mPointId = szICode;
        data_value_info->setCurrVar(fIndexVal);
        pMapDataValueInfo.insert(make_pair(szICode,data_value_info));
        Aos_Assert_S(PubOpt::StringOpt::StringFormat("%s不存在于DataValueInfo重新生成插入;", szICode.c_str()).c_str());
    }
    data_value_info->mForeVal = data_value_info->getCurrVar(true);   //保存上一个周期的值

    if (!judgeIsExcept(fIndexVal))
    {
        std::string strInfo;
        if (pIndexConfInfo->mExpression.size() > 400)
        {
            strInfo = PubOpt::StringOpt::StringFormat(IDS_INDEX_CONFVAR_ERROR, szICode.c_str(), "公式字符过长", pIndexConfInfo->mTranOutVarAndFun.c_str());
        }
        else
        {
            strInfo = PubOpt::StringOpt::StringFormat(IDS_INDEX_CONFVAR_ERROR, szICode.c_str(), pIndexConfInfo->mExpression.c_str(), pIndexConfInfo->mTranOutVarAndFun.c_str());
        }
        data_value_info->mError = 0;
        fValue = fDefaultVal;
    }
    else
    {
        data_value_info->mForeVal = data_value_info->getCurrVar(true);   //保存上一个周期的值
        data_value_info->mError = 1;
        fValue = fIndexVal;
    }
    //将指标值更新到内存
    data_value_info->setCurrVar(fValue);
}

/*----------------------------------------------------------------------------*/
//	函数名称:	RecursiveCalculateIndex::getParamValue
//	功能描述:	计算并取得耗差指标值、实时点值、手工点值、耗差目标值
//	输入参数:	
//				CString szParentId          父指标ID
//				CString szChildId           被包含在父指标ID里面的，需要取出值的指标ID
//	返回值:		
//				CString                     指标的值
/*----------------------------------------------------------------------------*/
std::string 
RecursiveCalculateIndex::getParamValue(
        MapStringToIndexConfInfo &pMapIndexConfInfo,
        MapStringToPointData &pMapDataValueInfo,
        std::string szParentId,
        std::string szChildId)
{
    double fValue = 0;
    double fTemp = 0;
    double fFirParam = 0;
    double fSecParam = 0;
    std::string strValue, strTemp, strICode, strInfo;
    time_t t;

    std::string strEleUpper;
    std::string strFirParam, strSecParam,strTarType;

    std::string strUpperParam = szChildId;
    strUpperParam = PubOpt::StringOpt::StringUpper(strUpperParam);
    strUpperParam = PubOpt::StringOpt::TrimString(strUpperParam);

    std::string strLocalParam = szChildId;
    strLocalParam = PubOpt::StringOpt::TrimString(strLocalParam);

    if (strLocalParam.empty())
    {
        strValue = "0";
        return strValue;
    }

    int iIndex = strLocalParam.find("@");
    if (iIndex != -1)  //外部函数变量为实时点、耗差指标、手工指标、绩效指标
    {
        if(M_SUB == strUpperParam.substr(0,4))    //自减函数	SUB(M1_FH) SUB@M1_FH  SUB_M1_FH
        {
            //AfxExtractSubString(strICode,strLocalParam,1,'@');			//自减指标id
            strICode = PubOpt::StringOpt::StringSplit(strLocalParam, 1, "@");
            strEleUpper = PubOpt::StringOpt::TrimString(strICode);
            if (strEleUpper.substr(0,1)=="M")
            {
                MapStringToIndexConfInfo_It iter = pMapIndexConfInfo.find(strICode);
                if(iter == pMapIndexConfInfo.end())
                {
                    if (mFirstCal)
                    {
                        std::string strInfo = PubOpt::StringOpt::StringFormat("没有取到父指标%s的元素指标%s的值,元素指标%s的值用当前指标值或实时值代替,函数组合体%s !",
                                                                              szParentId.c_str(), strICode.c_str(), strICode.c_str(), strLocalParam.c_str());
                        Aos_Assert_S(strInfo.c_str());
                    }
                }
                else
                {
                    IndexConfigInfo * index_conf_info = iter->second;
                    aheadCalIndex(pMapIndexConfInfo, pMapDataValueInfo, index_conf_info,szParentId, strICode);
                }
            }
            //SUB函数中指标当前值
            fSecParam = getDasValue(pMapDataValueInfo, strICode);
            //SUB函数中指标上一周期值
            fFirParam = getForeValue(pMapDataValueInfo,strICode);
            //指标值
            fValue = fSecParam - fFirParam;
        }
        else if(M_NOW == strUpperParam.substr(0,4))
        {
            //NOW(0)表示当前时间
            //系统时间 "小时.分"
            t = mCnPeriodDateTm;
            fValue = PubOpt::SystemOpt::GetHour(t);
            fTemp = PubOpt::SystemOpt::GetMinute(t);
            fValue = fValue + fTemp/100;
        }
        //YEAR(0)表示当前时间的年，MONTH(0)表示当前时间的月，DAY(0)表示当前时间的日
        else if(M_YEAR == strUpperParam.substr(0,5))
        {
            t = mCnPeriodDateTm;
            fValue = PubOpt::SystemOpt::GetYear(t);
        }
        else if(M_MONTH == strUpperParam.substr(0,6))
        {
            t = mCnPeriodDateTm;
            fValue = PubOpt::SystemOpt::GetMonth(t);
        }
        else if(M_WEEK == strUpperParam.substr(0,5))
        {
            t = mCnPeriodDateTm;
            fValue = PubOpt::SystemOpt::GetDayOfWeek(t);         // 1:礼拜天 2:礼拜一 。。。7:礼拜六
        }
        else if(M_DAY == strUpperParam.substr(0,4))
        {
            t = mCnPeriodDateTm;
            fValue = PubOpt::SystemOpt::GetDay(t);
        }

        //PERIODTIME(0)  最后一次计算周期与上一次计算的时间差 秒为单位
        //系统实时计算周期 单位秒
        else if(M_PERIODTIME == strUpperParam.substr(0,11))
        {
            fValue = mPeriodTime;
        }

        else if(M_LOG==strUpperParam.substr(0,4))
        {
            //AfxExtractSubString(strICode.c_str(),strLocalParam.c_str(),1,'@');           //指标id
            strICode = PubOpt::StringOpt::StringSplit(strLocalParam, 1, "@");
            getDasValue(pMapDataValueInfo, strICode, strValue);
            fTemp = atof(strValue.c_str());
            fValue = log(fTemp);
        }
        else if(M_PRE ==strUpperParam.substr(0,4))
        {
            //         //预测值函数 PRE(M1_FH) PRE@M1_FH PRE_M1_FH
            //         //AfxExtractSubString(strICode,strLocalParam,1,'@');			//预测指标id
            //         strICode = PubOpt::StringOpt::StringSplit(strLocalParam, 1, "@");
            //// Linda Linda Linda
            //         fValue = GetPreValue(strICode.c_str());
            Aos_Assert_S("预测指标");
        }
        else if(M_FILT ==strUpperParam.substr(0,5))
        {
            //         //滤波（平滑）值函数 FILT(M1_FH)  FILT@M1_FH  FILT_M1_FH
            //         //AfxExtractSubString(strICode,strLocalParam,1,'@');			//过滤指标id
            //         strICode = PubOpt::StringOpt::StringSplit(strLocalParam, 1, "@");
            ////Linda Linda Linda
            //         fValue	= GetFiltValue(strICode);
            Aos_Assert_S("过滤指标");
        }
        else if(M_AIMU3D == strUpperParam.substr(0,7) ||
                M_AIMU2D == strUpperParam.substr(0,7) ||
                M_MAX == strUpperParam.substr(0,4))
        {
            ////上限值函数
            ////AfxExtractSubString(strICode,strLocalParam,1,'@');			//最大值指标id
            //strICode = PubOpt::StringOpt::StringSplit(strLocalParam, 1, "@");
            //fValue = GetMaxValue(strICode);
            Aos_Assert_S("max Index");
        }
        else if(M_AIMD3D == strUpperParam.substr(0,7) ||
                M_AIMD2D == strUpperParam.substr(0,7) ||
                M_MIN == strUpperParam.substr(0,4))
        {
            ////下限值函数
            ////AfxExtractSubString(strICode,strLocalParam,1,'@');			//最小值指标id
            //strICode = PubOpt::StringOpt::StringSplit(strLocalParam, 1, "@");
            //fValue = GetMinValue(strICode)
            Aos_Assert_S("min index");
        }

        strValue = PubOpt::StringOpt::StringFormat("%.06f",fValue);
    }
    else      //外部变量中
    {
        //D--实时点打头库  H--手工指标打头
        if((strUpperParam.substr(0,1) == "D") ||
                (strUpperParam.substr(0,1) == "H")) //如果打头是D、M、H的参数
        {
            if (!getDasValue(pMapDataValueInfo,strLocalParam, strValue))
            {
                std::string strInfo = PubOpt::StringOpt::StringFormat("没有取到父指标%s的元素指标%s的值,元素指标%s的值用当前指标值或实时值代替,函数组合体%s",
                                                                      szParentId.c_str(), strLocalParam.c_str(), strLocalParam.c_str(), strLocalParam.c_str());
                //LINXIAOYU,2018/07/11
                //Aos_Assert_S(strInfo.c_str());
            }
        }
        else if(strUpperParam.substr(0,1) == "M") //如果打头是M的参数
        {
            strICode = strLocalParam;
            MapStringToIndexConfInfo_It iter = pMapIndexConfInfo.find(strICode);
            if(iter == pMapIndexConfInfo.end())
            {
                strValue = "0";
                if (mFirstCal)
                {
                    std::string strInfo = PubOpt::StringOpt::StringFormat("没有取到父指标%s的元素指标%s的值,元素指标%s的值用当前指标值或实时值代替,函数组合体%s !",
                                                                          szParentId.c_str(), strICode.c_str(), strICode.c_str(), strICode.c_str());
                    Aos_Assert_S(strInfo.c_str());
                }
            }
            else
            {
                IndexConfigInfo* index_conf_info = iter->second;
                aheadCalIndex(pMapIndexConfInfo, pMapDataValueInfo, index_conf_info,szParentId, strICode);
                getDasValue(pMapDataValueInfo,strICode,strValue);
            }
        }
    }
    return strValue;
}


/*----------------------------------------------------------------------------*/
//	函数名称:	RecursiveCalculateIndex::aheadCalIndex
//	功能描述:	当在绩效指标A中引用了绩效指标B，而B还没有计算，哪就计算出B
//	输入参数:
//				CString szPareID          父耗差指标ID
//				CString szParamID         子耗差指标ID
//				IndexConfigInfo* pIndexConfInfo     耗差指标信息类
//	返回值:		
//				void                       
/*----------------------------------------------------------------------------*/
void 
RecursiveCalculateIndex::aheadCalIndex(
        MapStringToIndexConfInfo &pMapIndexConfInfo,
        MapStringToPointData &pMapDataValueInfo,
        IndexConfigInfo* pIndexConfInfo,
        std::string szPareID,
        std::string szParamID)
{
    int iInner=0;
    //PubSetInfo* pTemp = NULL;
    if (szPareID == szParamID) return;
    if ((pIndexConfInfo->mNew))    //此指标在本轮周期里面已经计算
    {
        return;
    }
    else
    {
        //获取父指标对应的信息
        MapStringToIndexConfInfo_It iter = pMapIndexConfInfo.find(szPareID);
        if (iter == pMapIndexConfInfo.end())
        {
            return;
        }
        else
        {
            IndexConfigInfo* pare_index_conf_info = iter->second;
        }

        //获取当前指标对应的机组状态信息

        //查看该指标是否已经在当前循环中
        for(iInner=0;iInner<mForeIndexForUsed.size();iInner++)
        {
            if(mForeIndexForUsed[iInner]==szParamID)
            {
                break;														//指标正在计算本身
            }
        }
        if(iInner==mForeIndexForUsed.size())                            //此指标没有计算
        {
            mForeIndexForUsed.push_back(szParamID);							    //将此指标保存在当前循环中
            //如果此指标本轮没有计算，那么就计算
            if(!pIndexConfInfo->mNew)
            {
                switch(pIndexConfInfo->mIsCalState) {
                case 0:
                {
                    if (!isExistState(pMapIndexConfInfo, szParamID,szPareID))          //要计算子指标
                    {
                        calIndexParam(pMapIndexConfInfo,pMapDataValueInfo, pIndexConfInfo);
                    }
                }
                    break;
                case 1:
                    break;
                default:
                    break;
                }
            }
        }
    }
}



/*----------------------------------------------------------------------------------------------------------*/
//	函数名称:	RecursiveCalculateIndex::isExistState
//	功能描述:	当指标A中引用了指标B时,并且B又引用了A时,
//			    当开始算A时,不能继续算B;当开始算B时,不能继续算A
//	输入参数:
//				CString szFatherID  父指标ID
//				CString szSunID     子指标ID
//	返回值:		
//				bool                      
//									true - 在子指标ID的外部函数或外部变量里面找到父指标ID,不计算子指标
//									false - 在子指标ID的外部函数或外部变量里面没有找到父指标ID,要计算子指标
/*----------------------------------------------------------------------------------------------------------*/
//说明:        指标A中引用了指标B,并且指标B又引用了指标A的情况分以下几种:
//		        第一种: A引用B的属性,B引用A的属性;
//		        第二种: A引用B的属性及指标值,B引用A的属性;
//		        第三种: A引用B的指标值,B引用A的属性;
//		        第四种: A引用B的属性及指标值,B引用A的指标值;
//		        第五种: A引用B的指标值,B引用A的指标值;
//		        第六种: A引用B的属性及指标值,B引用A的属性及指标值;
//
/*---------------------------------------------------------------------------------------*/
bool 
RecursiveCalculateIndex::isExistState(
        MapStringToIndexConfInfo &pMapIndexConfInfo,
        std::string szFatherID,
        std::string szSunID)
{
    int iNum = 0;
    int iIndex = 0;
    bool bState = true;
    std::string strUpper,strTemp;
    strUpper = szSunID;
    strUpper = PubOpt::StringOpt::StringUpper(strUpper);
    if (strUpper[0] == 'M')
    {
        MapStringToIndexConfInfo_It iter = pMapIndexConfInfo.find(szFatherID);
        if( iter != pMapIndexConfInfo.end())
        {
            IndexConfigInfo* index_conf_info = iter->second;
            iNum = (int)index_conf_info->mOutFuncVarArray.size();
            if (iNum > 0)
            {
                for(unsigned int i=0;i<index_conf_info->mOutFuncVarArray.size();i++)     //外部变量
                {
                    strTemp = index_conf_info->mOutFuncVarArray[i];
                    iIndex = strTemp.find("@");
                    if (iIndex != -1)     //在外部函数中到
                    {
                        if (strTemp.find(szSunID) != -1)  //找到
                        {
                            bState = true;
                            break;
                        }
                        else                              //没有找到
                        {
                            bState = false;
                            continue;
                        }
                    }
                    else				   //在外部变量中找到
                    {
                        if (strTemp == szSunID)
                        {
                            bState = true;
                            break;
                        }
                        else
                        {
                            bState = false;
                            continue;
                        }
                    }
                }
            }
            else if (iNum == 0)
            {
                bState = false;
            }
        }
        else     //没有找到此指标
        {
            bState = true;
        }
    }
    return bState;
}

/*---------------------------------------------------------------------------------*/
//	函数名称:	RecursiveCalculateIndex::judgeIsExcept
//	功能描述:	异常处理计算出来的对象结果值，如果是异常数，就赋值为0
//	输入参数:	
//				double fExceptVal		      异常的值
//	返回值:		
//				BOOL                          TRUE --- 非异常 FALSE --- 是异常值 
/*---------------------------------------------------------------------------------*/
bool 
RecursiveCalculateIndex::judgeIsExcept(double fExceptVal)
{
    bool bExcept = true;
    std::string strTemp;
    strTemp= PubOpt::StringOpt::StringFormat("%f",fExceptVal);
    if (strcmp(strTemp.c_str(),"1.#QNAN0")==0||strcmp(strTemp.c_str(),"-1.#INF00")==0||
            strcmp(strTemp.c_str(),"1.#INF00")==0||strcmp(strTemp.c_str(),"1.#SNAN0")==0||
            strcmp(strTemp.c_str(),"-1.#IND00")==0||strcmp(strTemp.c_str(),"-nan")==0)
    {
        bExcept = false;
    }
    return bExcept;
}


/*----------------------------------------------------------------------------*/
//	函数名称:	RecursiveCalculateIndex::GetDasValue
//	功能描述:	从内存里面取得实时点值\手工指标值\M指标的值
//	输入参数:	
//				CString szID		实时点、耗差指标或手工指标的ID
//	返回值:		
//				bool				true -- 取得   false -- 没有取得
/*----------------------------------------------------------------------------*/
bool 
RecursiveCalculateIndex::getDasValue(MapStringToPointData &pMapDataValueInfo, std::string szID,std::string& szValue)
{
    bool b = false;
    std::string strValue = "0";
    MapStringToPointData_It iter = pMapDataValueInfo.find(szID);
    if (iter != pMapDataValueInfo.end())
    {
        b = true;
        strValue = PubOpt::StringOpt::StringFormat("%.06f", iter->second->getCurrVar(true));
    }
    szValue = strValue;
    return b;
}


/*----------------------------------------------------------------------------*/
//	函数名称:	RecursiveCalculateIndex::getDasValue
//	功能描述:	从内存里面取得实时点值\手工指标值\M上一个周期的值
//	输入参数:	
//				CString szID		实时点、耗差指标或手工指标的ID
//	返回值:		
//				double				上一个周期的值
/*----------------------------------------------------------------------------*/
double 
RecursiveCalculateIndex::getForeValue(MapStringToPointData &pMapDataValueInfo, std::string szID)
{
    double fValue = 0;
    MapStringToPointData_It iter = pMapDataValueInfo.find(szID);
    if (iter != pMapDataValueInfo.end())
    {
        fValue = iter->second->mForeVal;
    }

    return fValue;
}



/*----------------------------------------------------------------------------*/
//	函数名称:	RecursiveCalculateIndex::getDasValue
//	功能描述:	从内存里面取得实时点值\手工指标值\M指标的值
//	输入参数:	
//				CString szID		实时点、耗差指标或手工指标的ID
//	返回值:		
//				double				指标值
/*----------------------------------------------------------------------------*/
double 
RecursiveCalculateIndex::getDasValue(MapStringToPointData &pMapDataValueInfo, std::string szID)
{
    double fValue = 0;
    MapStringToPointData_It iter = pMapDataValueInfo.find(szID);
    if (iter != pMapDataValueInfo.end())
    {
        fValue = iter->second->getCurrVar(true);
    }
    return fValue;
}


bool
RecursiveCalculateIndex::sanityCheck(MapStringToPointData &pMapDataValueInfo)
{
    //M4_1kyqrkecfwzcz {{a=28;return a;}}
    std::string pointId = "M4_1kyqrkecfwzcz";
    MapStringToPointData_It itr = pMapDataValueInfo.find(pointId);
    Aos_Assert_R(itr != pMapDataValueInfo.end(), false);
    double vv = itr->second->getCurrVar(true);
    Aos_Assert_R(vv == 28, false);

    // M4_kyqqjdmbz {{a=1;return a;}}
    pointId = "M4_kyqqjdmbz";
    itr = pMapDataValueInfo.find(pointId);
    Aos_Assert_R(itr != pMapDataValueInfo.end(), false);
    vv = itr->second->getCurrVar(true);
    Aos_Assert_R(vv == 1, false);

    //M3_glxlsjz {{ return 91.7;}}
    pointId = "M3_glxlsjz";
    itr = pMapDataValueInfo.find(pointId);
    Aos_Assert_R(itr != pMapDataValueInfo.end(), false);
    vv = itr->second->getCurrVar(true);
    Aos_Assert_R(vv == 91.7, false);

    //M3_zrwdmbz {{a=537;return a;}}
    pointId = "M3_zrwdmbz";
    itr = pMapDataValueInfo.find(pointId);
    Aos_Assert_R(itr != pMapDataValueInfo.end(), false);
    vv = itr->second->getCurrVar(true);
    Aos_Assert_R(vv == 537, false);
    return true;
}


bool
RecursiveCalculateIndex::sanityCheck1(MapStringToPointData &pMapDataValueInfo)
{
    //D3_glzgswd
    std::string pointId = "D3_glzgswd";
    MapStringToPointData_It itr = pMapDataValueInfo.find(pointId);
    Aos_Assert_R(itr != pMapDataValueInfo.end(), false);
    double a = itr->second->getCurrVar(true);

    //M3_zzgswd {{a=D3_glzgswd;return a;}}
    pointId = "M3_zzgswd";
    itr = pMapDataValueInfo.find(pointId);
    Aos_Assert_R(itr != pMapDataValueInfo.end(), false);
    double vv = itr->second->getCurrVar(true);

    int v11 = vv;// * 100;
    int a11 = a ;//* 100;
    Aos_Assert_R(v11 == a11, false);

    //D3_1kyqrkhyl1
    pointId = "D3_1kyqrkhyl1";
    itr = pMapDataValueInfo.find(pointId);
    Aos_Assert_R(itr != pMapDataValueInfo.end(), false);
    a = itr->second->getCurrVar(true);

    //M3_1kyqrkhyl {a=D3_1kyqrkhyl1;return a;}}
    pointId = "M3_1kyqrkhyl";
    itr = pMapDataValueInfo.find(pointId);
    Aos_Assert_R(itr != pMapDataValueInfo.end(), false);
    vv = itr->second->getCurrVar(true);
    v11 = vv * 100;
    a11 = a * 100;
    Aos_Assert_R(v11 == a11, false);


    //D3_1kyqckhyl
    pointId = "D3_1kyqckhyl";
    itr = pMapDataValueInfo.find(pointId);
    Aos_Assert_R(itr != pMapDataValueInfo.end(), false);
    a = itr->second->getCurrVar(true);

    //M3_1ckglxs  {{a=21/(21-D3_1kyqckhyl);return a;}}
    pointId = "M3_1ckglxs";
    itr = pMapDataValueInfo.find(pointId);
    Aos_Assert_R(itr != pMapDataValueInfo.end(), false);
    vv = itr->second->getCurrVar(true);
    double a1 = 21/(21 - a);
    if ((int)a != 20)
    {
        v11 = vv * 100;
        a11 = a1 * 100;
        Aos_Assert_R(v11 == a11, false);
    }

    //H4_Mar
    pointId = "H4_Mar";
    itr = pMapDataValueInfo.find(pointId);
    Aos_Assert_R(itr != pMapDataValueInfo.end(), false);
    a = itr->second->getCurrVar(true);

    //M4_Mar {{a=H4_Mar;return a;}}
    pointId = "M4_Mar";
    itr = pMapDataValueInfo.find(pointId);
    Aos_Assert_R(itr != pMapDataValueInfo.end(), false);
    vv = itr->second->getCurrVar(true);
    v11 = vv * 100;
    a11 = a * 100;
    Aos_Assert_R(v11 == a11, false);
    return true;
}




bool
RecursiveCalculateIndex::sanityCheck2(MapStringToPointData &pMapDataValueInfo)
{
    //D3_5djsswd
    std::string pointId = "D3_5djsswd";
    MapStringToPointData_It itr = pMapDataValueInfo.find(pointId);
    Aos_Assert_R(itr != pMapDataValueInfo.end(), false);
    double a = itr->second->getCurrVar(true);

    //D3_6djcknjswd
    pointId = "D3_6djcknjswd";
    itr = pMapDataValueInfo.find(pointId);
    Aos_Assert_R(itr != pMapDataValueInfo.end(), false);
    double b = itr->second->getCurrVar(true);

    //M3_5djxdc  "{{a=D3_5djsswd-D3_6djcknjswd;return a;}}"
    pointId = "M3_5djxdc";
    itr = pMapDataValueInfo.find(pointId);
    Aos_Assert_R(itr != pMapDataValueInfo.end(), false);
    double vv = itr->second->getCurrVar(true);

    int v11 = vv * 100;
    int a11 = (a - b) * 100;
    Aos_Assert_R(v11 == a11, false);

    //D3_LPxhsjswd1
    pointId = "D3_LPxhsjswd1";
    itr = pMapDataValueInfo.find(pointId);
    Aos_Assert_R(itr != pMapDataValueInfo.end(), false);
    a = itr->second->getCurrVar(true);

    //D3_LPxhsjswd2
    pointId = "D3_LPxhsjswd2";
    itr = pMapDataValueInfo.find(pointId);
    Aos_Assert_R(itr != pMapDataValueInfo.end(), false);
    b = itr->second->getCurrVar(true);

    //M3_WT {a=(D3_LPxhsjswd1+D3_LPxhsjswd2)/2;return a;}}
    pointId = "M3_WT";
    itr = pMapDataValueInfo.find(pointId);
    Aos_Assert_R(itr != pMapDataValueInfo.end(), false);
    vv = itr->second->getCurrVar(true);

    v11 = vv * 100;
    a11 = ((a + b)/2) * 100;
    Aos_Assert_R(v11 == a11, false);

    //D3_zzqwdL
    pointId = "D3_zzqwdL";
    itr = pMapDataValueInfo.find(pointId);
    Aos_Assert_R(itr != pMapDataValueInfo.end(), false);
    a = itr->second->getCurrVar(true);

    //D3_zzqwdR
    pointId = "D3_zzqwdR";
    itr = pMapDataValueInfo.find(pointId);
    Aos_Assert_R(itr != pMapDataValueInfo.end(), false);
    b = itr->second->getCurrVar(true);

    //M3_zzqwd {{a=(D3_zzqwdL+D3_zzqwdR)/2;return a;}}
    pointId = "M3_zzqwd";
    itr = pMapDataValueInfo.find(pointId);
    Aos_Assert_R(itr != pMapDataValueInfo.end(), false);
    vv = itr->second->getCurrVar(true);

    v11 = vv * 100;
    a11 = ((a + b)/2) * 100;
    Aos_Assert_R(v11 == a11, false);
    return true;
}


bool
RecursiveCalculateIndex::sanityCheck3(MapStringToPointData &pMapDataValueInfo)
{
    //H4_Sad
    std::string pointId = "H4_Sad";
    MapStringToPointData_It itr = pMapDataValueInfo.find(pointId);
    Aos_Assert_R(itr != pMapDataValueInfo.end(), false);
    double a = itr->second->getCurrVar(true);

    //H4_Mar
    pointId = "H4_Mar";
    itr = pMapDataValueInfo.find(pointId);
    Aos_Assert_R(itr != pMapDataValueInfo.end(), false);
    double b = itr->second->getCurrVar(true);

    //H4_Mad
    pointId = "H4_Mad";
    itr = pMapDataValueInfo.find(pointId);
    Aos_Assert_R(itr != pMapDataValueInfo.end(), false);
    double c = itr->second->getCurrVar(true);

    //M4_Sar  {{a=H4_Sad*(100-H4_Mar)/(100-H4_Mad);return a;}}
    pointId = "M4_Sar";
    itr = pMapDataValueInfo.find(pointId);
    Aos_Assert_R(itr != pMapDataValueInfo.end(), false);
    double vv = itr->second->getCurrVar(true);

    int v11 = vv * 100;
    int a11 = (a*(100-b)/(100-c)) * 100;
    Aos_Assert_R(v11 == a11, false);
    return true;
}

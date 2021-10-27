/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: TbPubModeMethodAvg.cpp
* 文件描述: 查询模型期望值方法配置
*  作  者 : %王凯%，
* 创建日期: 2016-1-15 15:50:33
*******************************************************************************/
#include "TbPubModeMethodAvg.h"
#include "DataValueInfo.h"
#include "AlarmLog.h"
#include "RsdbAdapter.h"
#include "Util.h"
#include "public_function_library.h"

TbPubModeMethodAvg::TbPubModeMethodAvg()
    :
      RDbOperationComplex()
{

}
TbPubModeMethodAvg::TbPubModeMethodAvg(RsdbAdapter * QtOpt)   
    :
      RDbOperationComplex(QtOpt)
{
}
TbPubModeMethodAvg::~TbPubModeMethodAvg(void)
{

}

bool 
TbPubModeMethodAvg::loadDB(MapStringToBool &mMapModleNameStatus,
                           MapStringToModeMethodAvg &pModeFunInfo,
                           MapStringToString &pPointSourceName,
                           std::string strCon)
{
    Aos_Assert_R(Util::QtConnect(mQtOpt), false);
    std::string strSql = PubOpt::StringOpt::StringFormat(g_strModeMuConfSQL.c_str(),strCon.c_str());
    Aos_Assert_R(stmtPrepare(MODEFUN_CONFIG, strSql), false);

    bool is_ok = loadValue(mMapModleNameStatus, pModeFunInfo, pPointSourceName);
    stmtCloseStream();
    return is_ok;
}

bool 
TbPubModeMethodAvg::GetMuValue(std::vector<std::string>& tempVec,MethodAvg* condtion_fun,const int num,const int typeVec)
{
    bool rslt;
    int i = tempVec.size();
    if (1 == typeVec)
    {
        condtion_fun->mVectorFunValue.clear();
    }
    else if (2 == typeVec)
    {
        condtion_fun->mVectorRelationValue.clear();
    }
    for (std::vector<std::string>::iterator it=tempVec.begin();it!=tempVec.end();++it)
    {
        if('@'==(*it).at(0)) (*it)=(*it).substr(1,(*it).size());
        condtion_fun->mVectorTempValue.clear();
        rslt=Util::StringSplit(*it,condtion_fun->mVectorTempValue, ",",false);
        if (!rslt||condtion_fun->mVectorTempValue.size()!=num)
            return false;
        if(!condtion_fun->CheckIntoFunValue(typeVec))
            return false;
        condtion_fun->mVectorTempValue.clear();
    }
    return true;
}

bool 
TbPubModeMethodAvg::loadValue(MapStringToBool &mMapModleNameStatus,MapStringToModeMethodAvg &pModeFunInfo,MapStringToString	&pPointSourceName)
{
    std::string strModel,strConditionId,strSimLimit,strPointList,strMalist,strModelValue,strModelValueRelation,errmsg;

    MethodAvg* condtion_fun;
    ModeMethodAvg* mode_fun;
    MapStringToModeMethodAvg_It fun_iter;
    MapStringToMethodAvg_It modCon_iter;
    MapStringToBool_It m_iter;
    std::vector<std::string> tempVec;

    if(mQtOpt->QtGetResultIsValid())
        return false;

    while (mQtOpt->SQLStmtFetch())
    {
        strModel = std::string(mQtOpt->m_query->value(0).toString().toLocal8Bit());
        strConditionId = std::string(mQtOpt->m_query->value(1).toString().toLocal8Bit());
        strSimLimit = std::string(mQtOpt->m_query->value(2).toString().toLocal8Bit());
        strPointList = std::string(mQtOpt->m_query->value(3).toString().toLocal8Bit());
        strMalist = std::string(mQtOpt->m_query->value(4).toString().toLocal8Bit());
        strModelValue = std::string(mQtOpt->m_query->value(5).toString().toLocal8Bit());
        strModelValueRelation = std::string(mQtOpt->m_query->value(6).toString().toLocal8Bit());

        if (strModel.empty())
        {
            Aos_Assert_S("模型方法配置的模型编号是空");
            continue;
        }
        if(strModel=="4_zc"||strModel=="3_zc")
            int i=100;

        m_iter = mMapModleNameStatus.find(strModel);
        if (m_iter == mMapModleNameStatus.end())
        {
            errmsg=PubOpt::StringOpt::StringFormat("model's ID not exit,id：%s",strModel.c_str());
            Aos_Assert_S(errmsg.c_str());
            continue;
        }

        m_iter->second = true;
        fun_iter = pModeFunInfo.find(strModel);
        if (fun_iter==pModeFunInfo.end())
        {
            mode_fun=new ModeMethodAvg();
            pModeFunInfo.insert(make_pair(strModel,mode_fun));
        }
        else
            mode_fun=fun_iter->second;

        mode_fun->mModeId = strModel;

        if(strConditionId.empty()) continue;
        modCon_iter=mode_fun->mMapmethodavg.find(strConditionId);
        if (modCon_iter==mode_fun->mMapmethodavg.end())
        {
            condtion_fun=new MethodAvg();
            condtion_fun->mCondId = strConditionId;
            mode_fun->mMapmethodavg.insert(make_pair(strConditionId,condtion_fun));
        }
        else
            condtion_fun=modCon_iter->second;

        condtion_fun->mDSimLimit = Util::CharPointerConvert2Number<double>(strSimLimit.c_str());

        if (strPointList.empty())
        {
            condtion_fun->mIsOk= false;
            continue;
        }
        if('@' == strPointList.at(0))
            strPointList = strPointList.substr(1, strPointList.size());

        bool nErr = Util::StringSplit(strPointList,condtion_fun->mVectorModePoint, "@");
        if(!nErr)
        {
            condtion_fun->mIsOk=false;
            condtion_fun->cleanVar();
            errmsg=PubOpt::StringOpt::StringFormat("mode's funcPointNames err,id：%s",strModel.c_str());
            Aos_Assert_S(errmsg.c_str());
            strPointList.clear();
            continue;
        }
        if (strMalist.empty())
        {
            condtion_fun->mIsOk= false;
            continue;
        }
        if('@' == strMalist.at(0))
            strMalist=strMalist.substr(1,strMalist.size());
        tempVec.clear();

        nErr = Util::StringSplit(strMalist, tempVec, "@", false);
        if(!nErr)
        {
            condtion_fun->mIsOk = false;
            condtion_fun->cleanVar();
            strMalist.clear();
            tempVec.clear();
            errmsg = PubOpt::StringOpt::StringFormat("mode's funcPointNames err,id：%s",strModel.c_str());
            Aos_Assert_S(errmsg.c_str());
            continue;
        }
        condtion_fun->mVectorMaValue.clear();
        for (int i = 0; i < tempVec.size(); ++i)
        {
            condtion_fun->mVectorMaValue.push_back(Util::CharPointerConvert2Number<double>(tempVec[i].c_str()));
        }
        strMalist.clear();
        tempVec.clear();
        if (strModelValue.empty())
        {
            condtion_fun->mIsOk = false;
            continue;
        }
        if('@'==strModelValue.at(0))
            strModelValue= strModelValue.substr(1,strModelValue.size());
        nErr = Util::StringSplit(strModelValue, tempVec, "@",false);
        if(!nErr)
        {
            condtion_fun->mIsOk=false;
            condtion_fun->cleanVar();
            strModelValue.clear();
            errmsg=PubOpt::StringOpt::StringFormat("mode's tempVec err,id：%s",strModel.c_str());
            Aos_Assert_S(errmsg.c_str());
            continue;
        }
        if(strModel=="4_zc"||strModel=="3_zc")
            int i=100;
        if(!GetMuValue(tempVec,condtion_fun,condtion_fun->mVectorModePoint.size(),1))
        {
            condtion_fun->mIsOk=false;
            strModelValue.clear();
            tempVec.clear();
            errmsg=PubOpt::StringOpt::StringFormat("model's ModelValue err,id：%s",strModel.c_str());
            Aos_Assert_S(errmsg.c_str());
            continue;
        }
        ////新加均值相关值G
        strModelValue.clear();
        tempVec.clear();

        //Aos_Assert_S("TbPubModeMethodAvg::loadValue**G12")
        if(strModelValueRelation.empty())
        {
            condtion_fun->mIsOk=false;
            condtion_fun->cleanVar();
            errmsg=PubOpt::StringOpt::StringFormat("mode's G empty err,id：%s",strModel.c_str());
            Aos_Assert_S(errmsg.c_str());
            continue;
        }
        if('@'==strModelValueRelation.at(0))
            strModelValueRelation= strModelValueRelation.substr(1,strModelValueRelation.size());
        //Aos_Assert_S("TbPubModeMethodAvg::loadValue**G13")
        //Aos_Assert_S("TbPubModeMethodAvg::loadValue**G2")
        nErr = Util::StringSplit(strModelValueRelation, tempVec, "@",false);
        if(!nErr)
        {
            condtion_fun->mIsOk=false;
            condtion_fun->cleanVar();
            strModelValueRelation.clear();
            tempVec.clear();
            errmsg=PubOpt::StringOpt::StringFormat("mode's tempVec err,id：%s",strModel.c_str());
            Aos_Assert_S(errmsg.c_str());
            continue;
        }
        //Aos_Assert_S("TbPubModeMethodAvg::loadValue**G3")
        if(strModel == "4_zc"||strModel == "3_zc")
            int i=100;

        if(!GetMuValue(tempVec,condtion_fun,condtion_fun->mVectorFunValue.size(),2))
        {
            condtion_fun->mIsOk=false;
            strModelValueRelation.clear();
            tempVec.clear();
            errmsg=PubOpt::StringOpt::StringFormat("mode's ModelValueRelation err,id：%s",strModel.c_str());
            Aos_Assert_S(errmsg.c_str());
            continue;
        }
        //Aos_Assert_S("TbPubModeMethodAvg::loadValue**G4")
        if(0 == condtion_fun->mVectorRelationValue.size())
            condtion_fun->mIsOk = false;

        //std::string str1;
        //for(VectorString_It it=condtion_fun->mVectorModePoint.begin();it!=condtion_fun->mVectorModePoint.end();++it)
        //{
        //    str1=*it;
        //    p_iter=mode_info->mMapModePoint.find(*it);
        //    if (p_iter!=mode_info->mMapModePoint.end())
        //    {
        //        p_iter->second->mRsdbPointIdIsExist=true;
        //              //s_itr = pPointSourceName.find(*it);
        //              str1=p_iter->second->mPOrigSource;
        //              if(p_iter->second->mPOrigSource.empty()) continue;
        //              s_itr = pPointSourceName.find(p_iter->second->mPOrigSource);
        //              str1=p_iter->second->mPOrigSource;
        //              if (s_itr == pPointSourceName.end())
        //              {
        //                  //pPointSourceName.insert(make_pair(*it, p_iter->second->mPointId));
        //                  pPointSourceName.insert(make_pair(p_iter->second->mPOrigSource, p_iter->second->mPointId));
        //              }
        //              else
        //              {
        //                  if (std::string::npos != s_itr->second.find(p_iter->second->mPointId)) continue;
        //                  std::string pName = s_itr->second;
        //                  pName = pName +  ",";
        //                  pName = pName + p_iter->second->mPointId;
        //                  s_itr->second = pName;
        //              }
        //    }
        //}
        //Aos_Assert_S("TbPubModeMethodAvg::loadValue**2")
    }
    Aos_WriteLog(PubOpt::StringOpt::StringFormat("Load %s Info Total: %d", MODEFUN_CONFIG, pModeFunInfo.size()).c_str());
    return true;
}



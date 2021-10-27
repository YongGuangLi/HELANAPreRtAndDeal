#include "TbDfhCfg.h"

TbDfhCfg::TbDfhCfg(void)
    :
      RDbOperationComplex()
{
}
TbDfhCfg::TbDfhCfg(RsdbAdapter * QtOpt)   
    :
      RDbOperationComplex(QtOpt)
{
}

TbDfhCfg::~TbDfhCfg(void)
{
}
bool TbDfhCfg::loadDB(MapStringToSetCfg &SetInfo,std::string strCon)
{
    Aos_Assert_R(Util::QtConnect(mQtOpt), false);
    std::string strSql = PubOpt::StringOpt::StringFormat(g_strDfhSQL.c_str(),strCon.c_str());
    Aos_Assert_R(stmtPrepare(CFG_DFH, strSql), false);
    //mQtOpt->QtQuerySelect(g_strModeSQL);
    bool is_ok = loadValue(SetInfo);
    stmtCloseStream();
    return is_ok;
}

bool TbDfhCfg::loadValue(MapStringToSetCfg &mapSetInfo)
{
    std::string strSet,strSetCode,strSetDfh,strSys,strSysDfh,strFullCode,strCode,strSource,strId,strType,strMax,strMin,strDefValue;
    std::string errmsg;
    int itype,icategory;
    double dcapacity;
    SetCfg *  setcf;
    SysCfg *  syscf;
    Dfhnl*	dfh;
    MapStringToSetCfg_It   set_iter;
    MapStringToSysCfg_It   sys_iter;
    MapStringToDfhnl_It    p_iter;

    if(mQtOpt->QtGetResultIsValid())
        return false;

    while (mQtOpt->SQLStmtFetch())
    {
        strSet = std::string(mQtOpt->m_query->value(0).toString().toLocal8Bit());
        strSetCode = std::string(mQtOpt->m_query->value(1).toString().toLocal8Bit());
        strSetDfh = std::string(mQtOpt->m_query->value(2).toString().toLocal8Bit());
        dcapacity = mQtOpt->m_query->value(3).toDouble();;
        strSys = std::string(mQtOpt->m_query->value(4).toString().toLocal8Bit());
        strSysDfh = std::string(mQtOpt->m_query->value(5).toString().toLocal8Bit());
        strCode = std::string(mQtOpt->m_query->value(6).toString().toLocal8Bit());
        strFullCode = std::string(mQtOpt->m_query->value(7).toString().toLocal8Bit());
        strSource = std::string(mQtOpt->m_query->value(8).toString().toLocal8Bit());
        strId = std::string(mQtOpt->m_query->value(9).toString().toLocal8Bit());
        strMax = std::string(mQtOpt->m_query->value(10).toString().toLocal8Bit());
        strMin = std::string(mQtOpt->m_query->value(11).toString().toLocal8Bit());
        strDefValue = std::string(mQtOpt->m_query->value(12).toString().toLocal8Bit());
        strType = std::string(mQtOpt->m_query->value(13).toString().toLocal8Bit());
        icategory = mQtOpt->m_query->value(14).toInt();

        if ("" == strType)
        {
            itype = -1;
        }
        else
        {
            itype = Util::CharPointerConvert2Number<double>(strType.c_str());
        }
        if (strSet.empty())
        {
            Aos_Assert_S("机组编号是空");
            continue;
        }
        if (strSetDfh.empty())
        {
            Aos_Assert_S("机组带负荷能力编号是空");
            continue;
        }
        set_iter = mapSetInfo.find(strSet);
        if (set_iter == mapSetInfo.end())
        {
            Aos_Assert_S("机组在mapSetInfo不存在");
            continue;
        }
        setcf = set_iter->second;
        setcf->mSet = strSet;
        setcf->mSetDfh = strSetDfh;
        setcf->mSetDefFh = dcapacity;
        setcf->mSetRfFh = setcf->mSetDefFh;
        setcf->mSetFh = "M"+setcf->mSet+"_FH";
        setcf->mSetTJ = "M"+setcf->mSet+"_jzyxzt";
        if (strSys.empty())
        {
            Aos_Assert_S("系统是空");
            continue;
        }
        if (strSysDfh.empty())
        {
            Aos_Assert_S("系统带负荷能力编号是空");
            continue;
        }
        if(strSys.empty())
            continue;
        sys_iter = setcf->mMapSys.find(strSys);
        if (sys_iter == setcf->mMapSys.end())
        {
            errmsg = PubOpt::StringOpt::StringFormat("机组:%s的系统在mMapSys不存在模型",strSet.c_str());
            Aos_Assert_S(errmsg.c_str());
            syscf = new SysCfg();
            setcf->mMapSys.insert(make_pair(strSys,syscf));
            //continue;
        }
        else
        {
            syscf = sys_iter->second;
        }
        syscf->mSys = strSys;
        if (syscf->mSys=="TS_1_qlj")
            int i = 100;
        syscf->mSysDfh = strSysDfh;
        if (strCode.empty()) continue;
        p_iter = syscf->mMapSysDfhnl.find(strCode);
        if (p_iter==syscf->mMapSysDfhnl.end())
        {
            dfh = new Dfhnl();
            syscf->mMapSysDfhnl.insert(make_pair(strCode,dfh));
            dfh->m_code = strCode;
            dfh->m_Fullcode = strFullCode;
            dfh->m_SourceCode = strSource;
            dfh->m_icategory = icategory;
            if ("D2_zfzqyl"==strCode)
            {
                Aos_Assert_S("***********************************");
                errmsg = PubOpt::StringOpt::StringFormat("机组:%s的系统%s在mMapSysDfhnl测点：%s 类型：%d",strSet.c_str(),syscf->mSys.c_str(),strCode.c_str(),dfh->m_icategory);
                Aos_Assert_S(errmsg.c_str());
            }
        }
        else
            dfh = p_iter->second;

        if (dfh->m_VectorDfhInterval.find(strId)==dfh->m_VectorDfhInterval.end())
        {
            IntervalEX inter;
            inter.m_DataType = itype;
            if (strMax.empty())
            {
                inter.m_interval.m_IsUpLimit = false;
            }
            else
            {
                inter.m_interval.m_IsUpLimit = true;
                inter.m_interval.m_UpLimit = Util::CharPointerConvert2Number<double>(strMax.c_str());
            }
            if (strMin.empty())
            {
                inter.m_interval.m_IsLowLimit = false;
            }
            else
            {
                inter.m_interval.m_IsLowLimit = true;
                inter.m_interval.m_LowLimit = Util::CharPointerConvert2Number<double>(strMin.c_str());
            }
            if (strDefValue.empty())
            {
                inter.m_value =  0;
            }
            else
            {
                inter.m_value =  Util::CharPointerConvert2Number<double>(strDefValue.c_str());
            }
            dfh->m_VectorDfhInterval.insert(make_pair(strId,inter));
        }
    }
    return true;
}

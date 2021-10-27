#include "pub_index_data.h"

pub_index_data::pub_index_data(void)
    :
      RDbOperationComplex()
{
}
pub_index_data::pub_index_data(RsdbAdapter * QtOpt)
    :
      RDbOperationComplex(QtOpt)
{

}
pub_index_data::~pub_index_data(void)
{
}

bool pub_index_data::loadDB(MapStringToIndexConfInfo& m_mapIndexConfInfo,MapStringToPointData& mMapPointData,std::string strCon)
{
    Aos_Assert_R(Util::QtConnect(mQtOpt), false);

    std::string strSql = PubOpt::StringOpt::StringFormat(g_strIndexSQL.c_str(),strCon.c_str());
    Aos_Assert_R(stmtPrepare(INDEX_CFG, strSql), false);

    bool is_ok = loadValue(m_mapIndexConfInfo, mMapPointData);
    stmtCloseStream();
    return is_ok;
}

bool pub_index_data::loadValue(MapStringToIndexConfInfo& m_mapIndexConfInfo,MapStringToPointData& mMapPointData)
{
    std::string strFullCode, strCode,strSet,strSource,strOutVarAndFunc,strLocalVar,strExpression;
    int iIndexType, isWriteBack;
    DataInfo* point_data;
    MapStringToPointData_It point_data_it;
    IndexConfigInfo* index_conf_info;
    MapStringToIndexConfInfo_It iter;

    if(mQtOpt->QtGetResultIsValid())
        return false;

    while (mQtOpt->SQLStmtFetch())
    {
        strCode = std::string(mQtOpt->m_query->value(0).toString().toLocal8Bit());
        strSet = std::string(mQtOpt->m_query->value(1).toString().toLocal8Bit());
        iIndexType  = mQtOpt->m_query->value(2).toInt();
        strSource = std::string(mQtOpt->m_query->value(3).toString().toLocal8Bit());
        strOutVarAndFunc = std::string(mQtOpt->m_query->value(4).toString().toLocal8Bit());
        strLocalVar = std::string(mQtOpt->m_query->value(5).toString().toLocal8Bit());
        strExpression = std::string(mQtOpt->m_query->value(6).toString().toLocal8Bit());
        isWriteBack = mQtOpt->m_query->value(7).toInt();
        strFullCode = std::string(mQtOpt->m_query->value(8).toString().toLocal8Bit());

        if(strCode.empty())
        {
            Aos_Assert_S("指标编号空");
            delete index_conf_info;
            continue;
        }
        index_conf_info = new IndexConfigInfo();
        iter = m_mapIndexConfInfo.find(strCode);
        if(iter != m_mapIndexConfInfo.end())
        {
            delete index_conf_info;
            continue;
        }
        m_mapIndexConfInfo.insert(make_pair(strCode, index_conf_info));
        index_conf_info->mIndexCode = strCode;
        index_conf_info->mFullIndexCode = strFullCode;
        index_conf_info->mSetCode = strSet;
        index_conf_info->mWriteBackCode = strSource;
        index_conf_info->mType = iIndexType;
        index_conf_info->setOutVarAndFunc(strOutVarAndFunc);
        index_conf_info->mLocalVar = strLocalVar;
        index_conf_info->mExpression = strExpression;
        index_conf_info->mIsWriteRdtb = isWriteBack;
        point_data_it = mMapPointData.find(strCode);
        if (point_data_it==mMapPointData.end())
        {
            point_data = new DataInfo();
            point_data->mFullPointId = strFullCode;
            point_data->mPointId = strCode;
            point_data->mPSource = strSource;
            point_data->mSet = strSet;
            point_data->mPointType = eIndex;
            point_data->mIsWriteRtdb = isWriteBack;
            mMapPointData.insert(make_pair(strCode,point_data));
        }
    }
    return true;
}

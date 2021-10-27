#include "pubpointvalue.h"

PubPointValue::PubPointValue(RsdbAdapter *QtOpt, std::string strCon) :
     RDbOperationComplex(QtOpt)
{

}




//liyg
void PubPointValue::SetModelPointValues(MapStringToSetCfg	&mMapSetInfo, MapStringToPointData &mMapPointData)
{
    MapStringToSetCfg_It iter_set;
    MapStringToSysCfg_It iter_sys;
    MapStringToDataMode_It iter_m;
    MapStringToPointGroup_It iter_group;
    MapStringToPointData_It  iter_allp;
    MapStringToMDataValueInfo_It p_iter;
    SetCfg * setcf;
    SysCfg * syscf;
    DataMode * mode_info;
    PointGroup* model_group;
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
                if (mode_info->mModeId=="ZZ_3_qb")
                  int tep1 = 100;
                iter_group = mode_info->mMapGroup.begin();
                for (;iter_group!=mode_info->mMapGroup.end();++iter_group)
                {
                    model_group = iter_group->second;
                    p_iter = model_group->mMapGroupPoint.begin();
                    for (;p_iter !=  model_group->mMapGroupPoint.end();++p_iter)
                    {
                        p_iter->second->m_IsGetOrigValue  = false;
                        p_iter->second->m_IsGetPreValue = false;
                        p_iter->second->m_IsGetSimValue = false;
                        iter_allp = mMapPointData.find(p_iter->second->mPointId);
                        if(iter_allp==mMapPointData.end()) continue;
                        p_iter->second->setCurrVar(iter_allp->second->mDValue,1);
                        p_iter->second->m_IsGetOrigValue  = true;
                        //p_iter->second->mGoodState = paTags[i].lState;
                    }
                }
            }
        }
    }
}


bool PubPointValue::loadDB(long &lTimeStamp, const long nowTime, MapStringToSetCfg &mMapSetInfo, MapStringToString &pPointSourceName, MapStringToPointData &mMapPointData, std::string strCon)
{
    Aos_Assert_R(Util::QtConnect(mQtOpt, strCon), false);

    Aos_Assert_R(stmtPrepare(PUBPOINTVALUE, SQL_PUB_POINT_VALUE_CUR), false);


    MapStringToSetCfg_It iter_set;
    MapStringToSysCfg_It iter_sys;
    MapStringToDataMode_It iter_m;
    MapStringToPointGroup_It iter_group;
    MapStringToPointData_It  iter_allp;
    SetCfg * setcf;
    SysCfg * syscf;
    DataMode * mode_info;
    PointGroup* model_group;

    std::vector<std::string> lstRet;
    //MapStringToMDataValueInfo_It d_itr;
    MapStringToMDataValueInfo_It p_iter;

    std::vector<VarParam>::iterator pcf_iter;
    bool rslt;

    MapStringToString_It iter = pPointSourceName.begin();

    while (mQtOpt->SQLStmtFetch())
    {
        std::string full_point_code = mQtOpt->m_query->value(0).toString().toStdString();
        double point_value = mQtOpt->m_query->value(1).toDouble();
        uint timestamp = mQtOpt->m_query->value(2).toDateTime().toTime_t();

        iter = pPointSourceName.find(full_point_code);
        if (iter == pPointSourceName.end())
            continue;

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
                iter_allp->second->setCurrVar(point_value);
            }
        }
        if (lTimeStamp < timestamp)
            lTimeStamp = timestamp;

    }

    stmtCloseStream();
    return true;
}

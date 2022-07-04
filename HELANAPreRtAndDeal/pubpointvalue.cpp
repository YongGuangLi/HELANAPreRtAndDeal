#include "pubpointvalue.h"

PubPointValue::PubPointValue(RsdbAdapter *QtOpt, std::string strCon) :
     RDbOperationComplex(QtOpt)
{

}

bool PubPointValue::checkModelModifyStatus()
{
    Aos_Assert_R(Util::QtConnect(mQtOpt), false);
    Aos_Assert_R(stmtPrepare(PUBPOINTVALUE, SQL_MODEL_CONFIG_STATUS), false);

    while(mQtOpt->SQLStmtFetch())
    {
        int status = mQtOpt->m_query->value(0).toInt();
        if(status == 1)
        {
            Aos_Assert_S("MODEL_IS_MODIFY, Process Exit!");
            sleep(5);
            Aos_Assert_R(stmtPrepare(PUBPOINTVALUE, SQL_UPDATE_MODEL_CONFIG_STATUS), false);
            qApp->exit(0);
        }
    }

    stmtCloseStream();
}




void PubPointValue::SetModelPointValues(MapStringToSetCfg	&mMapSetInfo, MapStringToPointData &mMapPointData)
{
    for (MapStringToSetCfg_It iter_set = mMapSetInfo.begin(); iter_set!=mMapSetInfo.end();++iter_set)
    {
        SetCfg *setcf = iter_set->second;
        MapStringToSysCfg_It iter_sys = setcf->mMapSys.begin();
        for (; iter_sys!=setcf->mMapSys.end();++iter_sys)
        {
            SysCfg * syscf = iter_sys->second;
            MapStringToDataMode_It iter_m = syscf->mMapModles.begin();
            for(; iter_m!=syscf->mMapModles.end();++iter_m)
            {
                DataMode *mode_info=iter_m->second;
                MapStringToPointGroup_It iter_group = mode_info->mMapGroup.begin();
                for (; iter_group!=mode_info->mMapGroup.end(); ++iter_group)
                {
                    PointGroup* model_group = iter_group->second;
                    MapStringToMDataValueInfo_It p_iter = model_group->mMapGroupPoint.begin();
                    for (; p_iter !=  model_group->mMapGroupPoint.end();++p_iter)
                    {
                        p_iter->second->m_IsGetOrigValue  = false;
                        p_iter->second->m_IsGetPreValue = false;
                        p_iter->second->m_IsGetSimValue = false;

                        MapStringToPointData_It iter_allp = mMapPointData.find(p_iter->second->mPointId);
                        if(iter_allp==mMapPointData.end())
                            continue;
                        p_iter->second->setCurrVar(iter_allp->second->mDValue,1);
                        p_iter->second->m_IsGetOrigValue  = true;
                    }
                }
            }
        }
    }
}


bool PubPointValue::loadDB(long &lTimeStamp, MapStringToString &pPointSourceName, MapStringToPointData &mMapPointData, std::string strCon)
{
    Aos_Assert_R(Util::QtConnect(mQtOpt, strCon), false);

    Aos_Assert_R(stmtPrepare(PUBPOINTVALUE, SQL_PUB_POINT_VALUE_CUR), false);

    listCurPointValue.clear();
    while (mQtOpt->SQLStmtFetch())
    {
        std::string full_point_code = mQtOpt->m_query->value(0).toString().toStdString();
        double point_value = mQtOpt->m_query->value(1).toDouble();
        QDateTime timestamp = mQtOpt->m_query->value(2).toDateTime();

        stCurPointValue curPointValue;
        curPointValue.full_point_code = full_point_code;
        curPointValue.point_value = point_value;
        curPointValue.timestamp = timestamp;

        listCurPointValue.push_back(curPointValue);

        MapStringToString_It iter = pPointSourceName.find(full_point_code);
        if (iter == pPointSourceName.end())
            continue;

        std::vector<std::string> lstRet;
        bool rslt = Util::StringSplit(iter->second, lstRet, ",");
        if(!rslt)
            continue;

        for (unsigned int j = 0; j < lstRet.size(); j++)
        {
            MapStringToPointData_It iter_allp = mMapPointData.find(lstRet[j]);
            if (iter_allp != mMapPointData.end())
            {
                iter_allp->second->setCurrVar(point_value);
            }
        }

        if (timestamp.isValid() && lTimeStamp < timestamp.toTime_t())
            lTimeStamp = timestamp.toTime_t();

    }

    stmtCloseStream();
    return true;
}

#include "LoadConfg.h"
#include "Util.h"
//#include <iostream>
//#include <sstream>
#include <string>
#include <QtMath>

LoadConfg::LoadConfg(void)
{
}

LoadConfg::~LoadConfg(void)
{
}
bool 
LoadConfg::loadAlarmInf(MapStringToAlarmSetInfo &mapAlarmSetInfo,VectorAlarmScore &mVectorAlarmScore)
{
    cleanVar(mapAlarmSetInfo);
    Aos_Assert_R(loadAlarmSetToPoint(mapAlarmSetInfo), false);
    Aos_Assert_R(loadAlarmModelCosine(mapAlarmSetInfo), false);
    Aos_Assert_R(loadAlarmScore(mVectorAlarmScore), false);
    return true;
}

bool 
LoadConfg:: loadAlarmScore(VectorAlarmScore &mVectorAlarmScore)
{
    std::string strSql;
    if (SQL_SERVERCE==mQtOpt->m_strRsdbType)
    {
        strSql = g_strAlarmScoreSQL;
    }
    else if (ORACLE==mQtOpt->m_strRsdbType)
    {
        strSql = g_strOrcAlarmScoreSQL;
    }
    Aos_Assert_R(Util::QtConnect(mQtOpt), false);
    Aos_Assert_R(stmtPrepare(LOAD_CONFG, strSql), false);
    Aos_Assert_R(loadAlarmScoreValue(mVectorAlarmScore), false);
    stmtCloseStream();
    return true;
}
bool 
LoadConfg:: loadAlarmScoreValue(VectorAlarmScore &mVectorAlarmScore)
{
    bool nErr = false;
    AlarmScore  alarmscore;
    std::string strKey;
    VecetorAlarmScore_It it;
    std::string aLevel,aSore,upLimit,lowLimit;
    double alarm_level=0,alarm_score=0,upper_limit=0,lower_limit=0;
    if(mQtOpt->QtGetResultIsValid())
        return false;

    while (mQtOpt->SQLStmtFetch())
    {
        strKey = std::string(mQtOpt->m_query->value(0).toString().toLocal8Bit());
        alarm_level = mQtOpt->m_query->value(1).toDouble();
        alarm_score = mQtOpt->m_query->value(2).toDouble();
        upper_limit = mQtOpt->m_query->value(3).toDouble();
        lower_limit = mQtOpt->m_query->value(4).toDouble();

        alarm_score = (double)qFloor(alarm_score * 10) / 10;
        upper_limit = (double)qFloor(upper_limit * 10) / 10;
        lower_limit = (double)qFloor(lower_limit * 10) / 10;
        aLevel = std::string(mQtOpt->m_query->value(1).toString().toLocal8Bit());
        aSore = std::string(mQtOpt->m_query->value(2).toString().toLocal8Bit());
        upLimit = std::string(mQtOpt->m_query->value(3).toString().toLocal8Bit());
        lowLimit = std::string(mQtOpt->m_query->value(4).toString().toLocal8Bit());

        alarm_level = Util::CharPointerConvert2Number<double>(aLevel.c_str());
        alarm_score = Util::CharPointerConvert2Number<double>(aSore.c_str());
        upper_limit = Util::CharPointerConvert2Number<double>(upLimit.c_str());
        lower_limit = Util::CharPointerConvert2Number<double>(lowLimit.c_str());

        alarmscore.mStrKey= strKey;
        alarmscore.mAlarmLevel= alarm_level;
        alarmscore.mAlarmScore= alarm_score;
        alarmscore.mUpper= upper_limit;
        alarmscore.mLower = lower_limit;
        mVectorAlarmScore.push_back(alarmscore);
    }
    return nErr;
}
bool 
LoadConfg:: loadAlarmModelCosine(MapStringToAlarmSetInfo &mapAlarmSetInfo)
{
    Aos_Assert_R(Util::QtConnect(mQtOpt), false);
    Aos_Assert_R(stmtPrepare(LOAD_CONFG, g_strAlarmCosineSQL), false);
    Aos_Assert_R(loadModelCosineValue(mapAlarmSetInfo), false);
    stmtCloseStream();
    return true;
}

void LoadConfg::clearConsineCfg(MapStringToAlaramCosine &mapAlarmCosine)
{
    MapStringToAlaramCosine_It it;
    it = mapAlarmCosine.begin();
    for (;it!= mapAlarmCosine.end();++it)
    {
        delete it->second;
    }
    mapAlarmCosine.clear();
}
bool 
LoadConfg::loadModelCosineValue(MapStringToAlarmSetInfo &mapAlarmSetInfo)
{
    AlarmSetInfo		*pSet= NULL;
    AlarmSetSys			*pSys= NULL;
    AlarmModel			*model= NULL;
    CDCosine			*cosine= NULL;

    std::string  strSet,strSys,strModel,strSn,strCosineId,strFaultName,strRelatedParam;
    std::string  strFaultCauses,strFaultAnalyse,strFaultGuide;

    MapStringToAlarmSetInfo_It		it_set;
    MapStringToAlarmSetSys_It		it_sys;
    MapStringToAlarmModel_It		it_model;
    MapStringToAlaramCosine_It		it_cosine;
    if(mQtOpt->QtGetResultIsValid())
        return false;

    while (mQtOpt->SQLStmtFetch())
    {
        strSet = std::string(mQtOpt->m_query->value(0).toString().toLocal8Bit());
        strSys = std::string(mQtOpt->m_query->value(1).toString().toLocal8Bit());
        strModel = std::string(mQtOpt->m_query->value(2).toString().toLocal8Bit());
        strSn = std::string(mQtOpt->m_query->value(3).toString().toLocal8Bit());
        strCosineId = std::string(mQtOpt->m_query->value(4).toString().toLocal8Bit());
        strFaultName = std::string(mQtOpt->m_query->value(5).toString().toLocal8Bit());
        strRelatedParam = std::string(mQtOpt->m_query->value(6).toString().toLocal8Bit());
        strFaultCauses = std::string(mQtOpt->m_query->value(7).toString().toLocal8Bit());
        strFaultAnalyse = std::string(mQtOpt->m_query->value(8).toString().toLocal8Bit());
        strFaultGuide = std::string(mQtOpt->m_query->value(9).toString().toLocal8Bit());

        if (strSet.empty()) continue;
        if(pSet == NULL||pSet->mSet!= strSet)
        {
            it_set= mapAlarmSetInfo.find(strSet);
            if (it_set==mapAlarmSetInfo.end()) continue;
            pSet= it_set->second;
        }

        if (strSys.empty()) continue;
        if (pSys == NULL||pSys->mSys!=strSet)
        {
            it_sys= pSet->mapSys.find(strSys);
            if (it_sys == pSet->mapSys.end()) continue;
            pSys = it_sys->second;
        }

        if (strModel.empty()) continue;
        if (model == NULL||model->mstrModelId!= strModel)
        {
            it_model= pSys->mapAlarmMode.find(strModel);
            if (it_model==pSys->mapAlarmMode.end()) continue;
            model= it_model->second;
        }
        model->mstrSn = strSn;

        if (strCosineId.empty()) continue;

        it_cosine= model->mapAlarmCosine.find(strCosineId);
        if (it_cosine== model->mapAlarmCosine.end())
        {
            cosine= new CDCosine();
            model->mapAlarmCosine.insert(make_pair(strCosineId,cosine));
            cosine->mId = strCosineId;
        }
        else
            cosine=it_cosine->second;

        cosine->mName= strFaultName;
        cosine->StringSplit(strRelatedParam,";");

        cosine->mCauses = strFaultCauses;
        cosine->mAnalye = strFaultAnalyse;
        cosine->mGuid = strFaultGuide;

    }
    return true;
}
bool 
LoadConfg::loadAlarmSetToPoint(MapStringToAlarmSetInfo &mapAlarmSetInfo)
{
    std::string strSql;
    strSql = mQtOpt->m_strRsdbType;
    if (SQL_SERVERCE==mQtOpt->m_strRsdbType)
    {
        strSql = g_strAlarmSetSQL;
    }
    else if (ORACLE==mQtOpt->m_strRsdbType)
    {
        strSql = g_strOrcAlarmSetSQL;
    }
    Aos_Assert_R(Util::QtConnect(mQtOpt), false);

    Aos_Assert_R(stmtPrepare(LOAD_CONFG, strSql), false);
    Aos_Assert_R(loadAlarmSetToPointValue(mapAlarmSetInfo), false);
    stmtCloseStream();
    return true;
}

bool 
LoadConfg::loadAlarmSetToPointValue(MapStringToAlarmSetInfo &mapAlarmSetInfo)
{
    bool nErr = false;
    AlarmSetInfo		*pSet= NULL;
    AlarmSetSys			*pSys= NULL;
    AlarmModel			*model= NULL;
    AlaramModelGroup	*group= NULL;
    AlarmPointInfo		*point=	NULL;
    AlarmPointZone      zone;
    std::string  strSet,strSys,strModel,strGroup,strPoint,strinterval;
    MapStringToAlarmSetInfo_It		it_set;
    MapStringToAlarmSetSys_It		it_sys;
    MapStringToAlarmModel_It		it_model;
    MapStringToAlaramModelGroup_It	it_group;
    MapStringToAlarmPointInfo_It	it_point;
    double dSysWeight,dModelWeight,dGrouWeight;
    int  iPointBand;
    std::string strLow,strUper;
    if(mQtOpt->QtGetResultIsValid())
        return false;
    int nNumber = 0;
    while (mQtOpt->SQLStmtFetch())
    {
        nNumber++;
        //qDebug()<<mQtOpt->m_query->value(0).toString()<<nNumber;
        strSet = std::string(mQtOpt->m_query->value(0).toString().toLocal8Bit());
        strSys = std::string(mQtOpt->m_query->value(1).toString().toLocal8Bit());
        dSysWeight = mQtOpt->m_query->value(2).toDouble();
        strModel = std::string(mQtOpt->m_query->value(3).toString().toLocal8Bit());
        dModelWeight = mQtOpt->m_query->value(4).toDouble();
        strGroup = std::string(mQtOpt->m_query->value(5).toString().toLocal8Bit());
        dGrouWeight = mQtOpt->m_query->value(6).toDouble();
        strPoint = std::string(mQtOpt->m_query->value(7).toString().toLocal8Bit());
        iPointBand = mQtOpt->m_query->value(8).toInt();
        zone.mStrZoneID = std::string(mQtOpt->m_query->value(9).toString().toLocal8Bit());
        zone.mIAlarmLevel = mQtOpt->m_query->value(10).toInt();
        zone.mIAlarmType = mQtOpt->m_query->value(11).toInt();
        strLow = std::string(mQtOpt->m_query->value(12).toString().toLocal8Bit());
        strUper = std::string(mQtOpt->m_query->value(13).toString().toLocal8Bit());

        if (!strLow.empty())
        {
            zone.mDAlarmLower = Util::CharPointerConvert2Number<double>(strLow.c_str());
            zone.mLowExist= true;
        }
        else
        {
            zone.mLowExist= false;
        }

        if (!strUper.empty())
        {
            zone.mDAlarmUpper = Util::CharPointerConvert2Number<double>(strUper.c_str());
            zone.mUperExist = true;
        }
        else
        {
            zone.mUperExist = false;
        }
        if (strSet.empty()) continue;
        it_set= mapAlarmSetInfo.find(strSet);
        if (it_set==mapAlarmSetInfo.end())
        {
            pSet = new AlarmSetInfo();
            mapAlarmSetInfo.insert(make_pair(strSet,pSet));
        }
        else
            pSet= it_set->second;

        pSet->mSet=strSet;

        if (strSys.empty())
            continue;

        it_sys= pSet->mapSys.find(strSys);
        if (it_sys == pSet->mapSys.end())
        {
            pSys = new AlarmSetSys();
            pSet->mapSys.insert(make_pair(strSys,pSys));
        }
        else
            pSys = it_sys->second;

        pSys->mSys= strSys;

        pSys->mWeight = dSysWeight;

        if (strModel.empty()) continue;

        it_model= pSys->mapAlarmMode.find(strModel);
        if (it_model==pSys->mapAlarmMode.end())
        {
            model= new AlarmModel();
            pSys->mapAlarmMode.insert(make_pair(strModel,model));
        }
        else
        {
            model=it_model->second;
        }
        model->mstrModelId = strModel;

        model->mWeight = dModelWeight;

        if (strGroup.empty())
            continue;

        it_group= model->mapAlarmGroup.find(strGroup);
        if (it_group== model->mapAlarmGroup.end())
        {
            group= new AlaramModelGroup();
            model->mapAlarmGroup.insert(make_pair(strGroup,group));
        }
        else
            group=it_group->second;

        group->mStrGroupId = strGroup;

        group->mWeight = dGrouWeight;

        if (strPoint.empty())
            continue;
        /*if ("lg_gz_D1_BPTE146"==strPoint)
            int testp=100;*/

        it_point= group->mapPointInfo.find(strPoint);
        if (it_point== group->mapPointInfo.end())
        {
            point = new AlarmPointInfo();
            group->mapPointInfo.insert(make_pair(strPoint,point));
        }
        else
        {
            point = it_point->second;
        }
        point->mStrPointId = strPoint;

        point->miBand = iPointBand;

        if(group->miBand<point->miBand) group->miBand=point->miBand;
        if(model->miBand<point->miBand) model->miBand=point->miBand;
        if(pSys->miBand<point->miBand)	pSys->miBand=point->miBand;
        if(pSet->miBand<point->miBand)	pSet->miBand=point->miBand;


        if(zone.mStrZoneID.empty())
            continue;

        point->mVectZone.push_back(zone);
    }
    Aos_WriteLog(PubOpt::StringOpt::StringFormat("Load %s SetInfo Total: %d",
                                                 LOAD_CONFG, mapAlarmSetInfo.size()).c_str());
    return true;
}


void LoadConfg::cleanVar(MapStringToAlarmSetInfo &mapAlarmSetInfo)
{
    MapStringToAlarmSetInfo_It		it_set;
    MapStringToAlarmSetSys_It		it_sys;
    MapStringToAlarmModel_It		it_model;
    MapStringToAlaramModelGroup_It	it_group;
    MapStringToAlarmPointInfo_It	it_point;

    AlarmSetInfo		*pSet= NULL;
    AlarmSetSys			*pSys= NULL;
    AlarmModel			*model= NULL;
    AlaramModelGroup	*group= NULL;
    AlarmPointInfo		*point=	NULL;
    for (it_set = mapAlarmSetInfo.begin();it_set!=mapAlarmSetInfo.end();++it_set)
    {
        pSet = it_set->second;
        pSet->miBand = 0;
        for (it_sys = pSet->mapSys.begin();it_sys!=pSet->mapSys.end();++it_sys)
        {
            pSys = it_sys->second;
            pSys->miBand = 0;
            for (it_model =pSys->mapAlarmMode.begin();it_model!=pSys->mapAlarmMode.end();++it_model)
            {
                model = it_model->second;
                model->miBand = 0;
                clearConsineCfg(model->mapAlarmCosine);
                for (it_group = model->mapAlarmGroup.begin();it_group!=model->mapAlarmGroup.end();++it_group)
                {
                    group = it_group->second;
                    group->miBand = 0;
                    for (it_point = group->mapPointInfo.begin();it_point!= group->mapPointInfo.end();++it_point)
                    {
                        it_point ->second->mVectZone.clear();
                    }
                }
            }
        }
    }
}

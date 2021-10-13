/*******************************************************************************
/*******************************************************************************
* Copyright（C）,2016-2020,DTXY Tech .Co.Ltd;
* 文 件 名: PubSetInfo.h
* 文件描述: 机组到测点告警结构数据配置及带负荷
*  作  者 : %王凯%，
* 创建日期: 2016-10-25 10:08:08
*******************************************************************************/

#ifndef __PUBSETINFO_H__
#define __PUBSETINFO_H__
#include "Util.h"
#include "DataValueInfo.h"
#include <math.h>

//告警得分区间配置
struct AlarmScore
{
    std::string     mStrKey;
    int				mAlarmLevel;
    double			mAlarmScore;
    double			mUpper;
    double			mLower;
};
//测点告警区间
struct AlarmPointZone  
{
    std::string			mStrZoneID;			//测点区间编号
    int					mIAlarmType;			//告警类型(0:偏差值告警 1:实际值告警)
    int					mIAlarmLevel;			//告警级别
    double				mDAlarmLower;			//告警下限
    double				mDAlarmUpper;			//告警上限
    bool                mLowExist;              //告警下限是否存在 true：存在 false：不存在
    bool                mUperExist;				//告警上限是否存在 true：存在 false：不存在

};
// 测点
struct AlarmPointInfo
{
    std::string   mStrPointId;
    double        mDcurValue;     //原始值
    double        mDpreValue;	  //期望值
    double        mDsim;          //测点健康度值
    bool		  mIsGetPreVale;//期望值是否取到
    bool          mIsGetCurVale;//原始值是否取到
    bool		  mIsGetSimVale;//健康度是否取到
    bool		  mIsInitPreVale;//期望值是否取到
    bool          mIsInitCurVale;//原始值是否取到
    bool		  mIsInitSimVale;//健康度是否取到
    PublicDate	  mDate;
    int           miBand;   //死区时间
    double		  m_minValue;    //告警时间段最小值
    double		  m_maxValue;    //告警时间段最大值
    double		  m_avgValue;    //告警时间段平均值
    double		  m_pminValue;    //告警时间段期望值最小值
    double		  m_pmaxValue;    //告警时间段期望值最大值
    double		  m_pavgValue;    //告警时间段期望值平均值
    double		  m_savgValue;    //告警时间段健康度平均值
    int			  m_iCount;	   //告警周期中取数周期统计次数

    std::vector<AlarmPointZone>   mVectZone;	//测点告警区间集合

    AlarmPointInfo()
    {
        mIsInitPreVale = false;
        mIsInitCurVale = false;
        mIsInitSimVale = false;
        m_minValue = 0;
        m_maxValue = 0;
        m_avgValue = 0;
        m_pminValue = 0;
        m_pmaxValue = 0;
        m_pavgValue = 0;
        m_savgValue = 0;
        mDcurValue = 0;
        mDpreValue = 0;
        mDsim = 0;
        if(0!=mVectZone.size())
            clear();
    }
    ~AlarmPointInfo()
    {
        clear();
    }
private:
    void clear()
    {
        mVectZone.clear();
    }
};
typedef std::map<std::string,AlarmPointInfo *> MapStringToAlarmPointInfo;
typedef	MapStringToAlarmPointInfo::iterator    MapStringToAlarmPointInfo_It;
struct AlaramModelGroup
{
    std::string							mStrGroupId;
    PublicDate							mDate;
    int									miBand;   //死区时间
    double								mWeight;  //权重
    std::map<std::string,AlarmPointInfo *>   mapPointInfo;

    AlaramModelGroup()
    {

    }
    ~AlaramModelGroup()
    {
        clear();
    }
    void clear()
    {
        MapStringToAlarmPointInfo_It it=mapPointInfo.begin();
        for (;it!=mapPointInfo.end();++it)
        {
            if (NULL!=it->second)
            {
                delete it->second;
                it->second=NULL;
            }
        }
        mapPointInfo.clear();
    }
};
typedef std::map<std::string,AlaramModelGroup *> MapStringToAlaramModelGroup;
typedef	MapStringToAlaramModelGroup::iterator    MapStringToAlaramModelGroup_It;
typedef	MapStringToAlaramModelGroup::const_iterator   MapStringToAlaramModelGroupConst_It;

struct CDCosine
{
public:
    std::string			mId;
    std::string			mName;
    std::string			mCauses;
    std::string			mAnalye;
    std::string			mGuid;
    bool				isMok;
    double				mPValue;
    double				mMoValue;
    std::map<std::string , int>	mMapCosine;
    //PublicDate		mDate;
public:
    CDCosine()
    {
        isMok=true;
        mMoValue = 0;
        mPValue = 0;
    }
    ~CDCosine()
    {
        mMapCosine.clear();
    }
    bool StringSplit(const std::string &strSrc,const std::string &strSplit)
    {
        if (strSplit.empty()||strSrc.empty())
        {
            return false;
        }
        double dValue;
        std::string strSrcBak = strSrc;
        std::string strPoints,strValues,strp,strv;
        size_t siFind = 0;
        siFind = strSrcBak.find(strSplit);
        if (std::string::npos == siFind)
            return false;
        strPoints.clear();
        strValues.clear();
        strPoints= strSrcBak.substr(0, siFind);
        strValues= strSrcBak.substr(siFind+1,strSrcBak.length()-siFind-1);
        if(','!= strPoints.at(strPoints.length()-1)) strPoints +=",";
        if(','!= strValues.at(strValues.length()-1)) strValues +=",";
        if(strPoints.empty()||strValues.empty())
        {
            return false;
        }
        while(!strPoints.empty())
        {
            siFind = strPoints.find(",");
            strp= strPoints.substr(0, siFind);
            strPoints = strPoints.substr(siFind+1);
            siFind = strValues.find(",");
            strv= strValues.substr(0,siFind);
            strValues = strValues.substr(siFind+1);

            dValue = Util::CharPointerConvert2Number<double>(strv.c_str());
            mMapCosine.insert(make_pair(strp,dValue));
            mMoValue+= pow(dValue,2);
        }
        mMoValue= sqrt(mMoValue);
        return true;
    }
};
typedef std::map<std::string ,CDCosine *>    MapStringToAlaramCosine;
typedef MapStringToAlaramCosine::iterator    MapStringToAlaramCosine_It;
struct CDCosineCfg
{
public:
    std::string			mId;
    std::string			mName;
    std::string			mCauses;
    std::string			mAnalye;
    std::string			mGuid;
};
typedef std::map<std::string ,CDCosineCfg *>    MapStringToAlaramCosineCfg;
typedef MapStringToAlaramCosineCfg::iterator    MapStringToAlaramCosineCfg_It;
struct AlarmModel
{

public:
    std::string					mstrModelId;
    std::string					mstrSn;
    std::string					mCondId;			//当前满足的模式ID
    PublicDate					mDate;
    PublicConditionDate			mCondtionDate;		//模式记录数据

    std::string					mLastCosineId;  //上条报警cosineId
    std::string					mCosineId;  //报警cosineId
    PublicConditionDate			mCosineDate;	//故障定位记录数据
    CDCosine*					mConsine;       //当前满足的故障的配置描述
    double						mXsd;
    double						mSumAlram;  //本周期下属所有测点的cosine报警值平方和再开平方
    double						mLastSumAlram;  //上周期下属所有测点的cosine报警值平方和再开平方
    double						mDevPPD;    //上个计算周期和本周期测点告警序列的匹配度
    double						mDevFabsSum; //上个计算周期测点偏差值的绝对值和本计算周期对应测点偏差值的绝对值相乘后求总和

    bool						m_IsChangeCondition;
    int							miBand;   //死区时间
    double						mWeight;  //权重
    //DataMode	mode_info;
    //MethodAvg	mode_fun;
    bool						mIsDeal;	//模型是否处理 true ：处理 false ：不处理
    double						mdSimLimit;
    bool						mIsSimAlarm;
    MapStringToAlaramModelGroup mapAlarmGroup;
    MapStringToAlaramCosine		mapAlarmCosine;
public:
    AlarmModel()
    {
        mLastCosineId = NO_ALARM;
        mCosineId = NO_ALARM;
        mSumAlram= 0;
        mLastSumAlram = 0;
        mDevPPD = 0;
        mDevFabsSum = 0;
        mWeight= 0;
        miBand= 1;
        mIsDeal= false;
    }
    ~AlarmModel()
    {
        clear();
    }
    void clear()
    {
        MapStringToAlaramModelGroup_It it=mapAlarmGroup.begin();
        for (;it!= mapAlarmGroup.end();++it)
        {
            if (NULL!= it->second)
            {
                delete it->second;
                it->second= NULL;
            }
        }
        mapAlarmGroup.clear();
        MapStringToAlaramCosine_It it_consine= mapAlarmCosine.begin();
        for (;it_consine!= mapAlarmCosine.end();++it_consine)
        {
            if (NULL!= it_consine->second)
            {
                delete it_consine->second;
                it_consine->second = NULL;
            }
        }
        mapAlarmCosine.clear();
    }
};
typedef std::map<std::string, AlarmModel *>		    MapStringToAlarmModel;
typedef MapStringToAlarmModel::iterator			    MapStringToAlarmModel_It;


struct AlarmSetSys
{
public:
    AlarmSetSys()
    {
        mSys="";
        miBand=0;
    }
    virtual ~AlarmSetSys()
    {
        clear();
    }
public:
    std::string mSys;
    PublicDate  mDate;
    int         miBand;   //死区时间
    double      mWeight;  //权重
    std::map<std::string, AlarmModel *>	 mapAlarmMode;      //系统下的模型集合
    std::map<std::string,Dfhnl*>          mapDfhnl;			//带负荷能力配置集合
private:
    void clear()
    {
        std::map<std::string, AlarmModel *>::iterator	 it=mapAlarmMode.begin();
        for (;it!= mapAlarmMode.end();++it)
        {
            if (NULL!= it->second)
            {
                delete it->second;
                it->second=NULL;
            }
        }
        mapAlarmMode.clear();

        std::map<std::string,Dfhnl*> ::iterator it_dfh = mapDfhnl.begin();
        for (;it_dfh!=mapDfhnl.end();++it_dfh)
        {

            if (NULL!= it_dfh->second)
            {
                delete it_dfh->second;
                it_dfh->second=NULL;
            }
        }
        mapDfhnl.clear();
    }

};
typedef std::map<std::string, AlarmSetSys *>		        MapStringToAlarmSetSys;
typedef MapStringToAlarmSetSys::iterator			        MapStringToAlarmSetSys_It;
struct AlarmSetInfo
{
public:
    AlarmSetInfo(void)
    {
        mSet="";
        miBand=0;
    }
    ~AlarmSetInfo(void)
    {
        clear();
    }

public:
    std::string mSet;
    PublicDate  mDate;
    int         miBand;   //死区时间
    MapStringToAlarmSetSys mapSys;    //机组系统集合
    void clear()
    {
        MapStringToAlarmSetSys_It it= mapSys.begin();
        for (;it!= mapSys.end();++it)
        {
            if (NULL!= it->second)
            {
                delete it->second;
                it->second=NULL;
            }
        }
        mapSys.clear();
    }
};
typedef std::map<std::string, AlarmSetInfo *>		    MapStringToAlarmSetInfo;
typedef MapStringToAlarmSetInfo::iterator			    MapStringToAlarmSetInfo_It;

typedef std::vector<AlarmScore >                       VectorAlarmScore;
typedef VectorAlarmScore::iterator					   VecetorAlarmScore_It;

struct AlarmPointRst
{
    std::string   mStrModelId;
    std::string   mStrGroupId;
    std::string   mStrCondId;
    std::string   mStrPointId;
    double        mDcurValue;     //原始值
    double        mDpreValue;	  //期望值
    double        mDsim;          //测点健康度值
    bool		  mIsGetPreVale;//期望值是否取到
    bool          mIsGetCurVale;//原始值是否取到
    bool		  mIsGetSimVale;//健康度是否取到
    bool		  mIsInitPreVale;//期望值是否取到
    bool          mIsInitCurVale;//原始值是否取到
    bool		  mIsInitSimVale;//健康度是否取到
    PublicDate*	  mDate;
    //int           miBand;   //死区时间
    double		  m_minValue;    //告警时间段最小值
    double		  m_maxValue;    //告警时间段最大值
    double		  m_avgValue;    //告警时间段平均值
    double		  m_pminValue;    //告警时间段期望值最小值
    double		  m_pmaxValue;    //告警时间段期望值最大值
    double		  m_pavgValue;    //告警时间段期望值平均值
    double		  m_savgValue;    //告警时间段健康度平均值

    AlarmPointRst()
    {
        mIsGetPreVale = false;
        mIsGetCurVale = false;
        mIsGetSimVale = false;
        mIsInitPreVale = false;
        mIsInitCurVale = false;
        mIsInitSimVale = false;
        mStrCondId = "";
        m_minValue = 0;
        m_maxValue = 0;
        m_avgValue = 0;
        m_pminValue = 0;
        m_pmaxValue = 0;
        m_pavgValue = 0;
        m_savgValue = 0;
        mDcurValue = 0;
        mDpreValue = 0;
        mDsim = 0;
    }
};

struct  AlarmGrouRst
{
    std::string					mStrGroupId;
    PublicDate*					mDate;
    //int							miBand;   //死区时间
};
struct  AlarmModeltoSetRst
{
    std::string					mStrId;             //模型id、系统id或机组id
    PublicDate*					mDate;
    //int							miBand;   //死区时间
};
struct  AlarmModelConditionRst
{
    std::string					mModelIdTest;//测试零时
    std::string					mCondId;			//当前满足的模式ID
    PublicConditionDate*		mCondtionDate;
    //int							miBand;   //死区时间
};
struct  AlarmModelCosineRst
{
    std::string					mStrModelId;
    std::string					mstrSn;
    std::string					mLastCosineId;  //上条报警cosineId
    std::string					mCosineId;  //报警cosineId
    PublicConditionDate*		mCosineDate;	//故障定位记录数据
    CDCosine*					mConsine;
    //CDCosine*					mlastConsine;
    MapStringToAlaramCosineCfg	mapRlstAlarmCosineCfg;
    //int							miBand;   //死区时间
    double						mXsd;
    AlarmModelCosineRst()
    {
        mXsd = 0;
    }
    ~AlarmModelCosineRst()
    {
        for (MapStringToAlaramCosineCfg_It it = mapRlstAlarmCosineCfg.begin();it != mapRlstAlarmCosineCfg.end();++it)
        {
            delete it->second;
        }
        mapRlstAlarmCosineCfg.clear();
    }
};
typedef std::map<std::string,AlarmPointRst *>			MapStringToAlarmPointRst;
typedef MapStringToAlarmPointRst::iterator				MapStringToAlarmPointRst_It;
typedef std::map<std::string,AlarmGrouRst *>			MapStringToAlarmGrouRst;
typedef MapStringToAlarmGrouRst::iterator				MapStringToAlarmGrouRst_It;
typedef std::map<std::string,AlarmModeltoSetRst *>		MapStringToAlarmModeltoSetRst;
typedef MapStringToAlarmModeltoSetRst::iterator			MapStringToAlarmModeltoSetRst_It;
typedef std::map<std::string,AlarmModelConditionRst *>	MapStringToAlarmModelConditionRst;
typedef MapStringToAlarmModelConditionRst::iterator		MapStringToAlarmModelConditionRst_It;
typedef std::map<std::string,AlarmModelCosineRst *>		MapStringToAlarmModelCosineRst;
typedef MapStringToAlarmModelCosineRst::iterator		MapStringToAlarmModelCosineRst_It;
#endif 

/*******************************************************************************
* Copyright（C）,2016-2021,DTXY Tech .Co.Ltd;
* 文 件 名: SetDeal.h
* 文件描述: 测点到机组的告警处理类
*  作  者 : %王凯%，15802613961
* 创建日期: 2016-10-11 16:05:28
*******************************************************************************/

#ifndef __SETDEAL_H__
#define __SETDEAL_H__


#include <QFile>
#include "Util.h"
#include "TypeDef.h"
#include "singleton.h"
#include "RDbOperationComplex.h"
#include "AlarmSetInfo.h"
#include "public_function_library.h"
#define CON_DPOINT_RT				 "RsltDpointRtValuesRsdb"
#define CON_INDEX_RT				 "RsltIndexRtValuesRsdb"
#define CON_SET_DEAL_POINT_RT				 "RsltPointRtValuesRsdb"
#define CON_SET_DEAL_GROUP_RT				 "RsltPointGroupRtValuesRsdb"
#define CON_SET_DEAL_MODLE_RT				 "RsltModleRtValuesRsdb"
#define CON_SET_DEAL						 "AlarmSetDeal"
#define CON_SET_DEAL_POINT					 "AlarmSetDealUpdatePoint"
#define CON_SET_DEAL_GROUP					 "AlarmSetDealUpdateGroup"
#define CON_SET_DEAL_MODELTOSET				 "AlarmSetDealUpdateModelToSet"
#define CON_SET_DEAL_MODELCONDTION			 "AlarmSetDealUpdateModelCondtion"
#define CON_SET_DEAL_MODELCOSINE			  "AlarmSetDealUpdateModelCosine"
#define CON_SET_DEAL_SIZE						5
#define CON_RSLT_SIZE						3000
//#define CON_RSLT_SIZE						1
class AlarmSetDeal:public RDbOperationComplex
{
    //DECLARE_SINGLETON_INIT(AlarmSetDeal)
public:
    AlarmSetDeal(void);
    AlarmSetDeal(RsdbAdapter * QtOpt,std::string strFactory);
    ~AlarmSetDeal(void);
public:
    MapStringToAlarmPointRst  mMapAlarmPointRst;
    MapStringToAlarmGrouRst	  mMapAlarmGrouRst;
    MapStringToAlarmModeltoSetRst mMapAlarmModeltoSetRst;
    MapStringToAlarmModelConditionRst mMapAlarmModelConditionRst;
    MapStringToAlarmModelCosineRst mMapAlarmModelCosineRst;
public:
    void SetRtPointValue(const MapStringToDataMode  &mMapModeInfo,MapStringToAlarmSetInfo &mMapAlarmSet);
    void CalAralm(MapStringToAlarmSetInfo &mMapAlarmSet);
    void SetFirstDev(const bool isFirstCal,const bool isModConf,VectorAlarmScore *AlarmScore,long lCalTimeStamp);
    void WriteRsdb();
    void WriteRsdb(MapStringToSetCfg &mMapSetInfo,MapStringToPointData &mMapPointData,
                   const std::string strFactory,long mCurSeCalTime);
    bool UpdateServiceVersion(std::string strServiceName,std::string strVersion,std::string strLog);
private:
    bool TbPubPointValueCurToTxt();
    bool RsltPointRtValuesRsdb(MapStringToSetCfg &mMapSetInfo);
    bool RsltPointGroupRtValuesRsdb(MapStringToSetCfg &mMapSetInfo);
    bool RsltModelRtValuesRsdb(MapStringToSetCfg &mMapSetInfo);

    bool RsltIndexRtValuesRsdb(IN MapStringToPointData &mMapPointData,const std::string strFactory);
    bool RsltDpointRtValuesRsdb(IN MapStringToPointData &mMapPointData,const std::string strFactory);
private:
    int				mXsdLimit;				//判断故障匹配度为0的限值
    int				mBufferSize;              // OCI绑定查询缓存定义
    bool			misFirstCal;
    bool			mModConf;                //配置是否修改
    long			mlCalTimeStamp;
    VectorAlarmScore *mVectorAlarmScore;

    std::string							m_strFactoryCode;//电厂编号
private:

    /*******************************************************************************
* 函 数 名: 
* 函数描述: 插入新的测点告警记录前更新测点当前的告警记录
* 参数说明: 
*    入 参: 
*    出 参: 
* 返 回 值:
*    成 功:
*    失 败:	
*  作  者 : %王凯%，15802613961
* 创建日期: 2016-12-23 15:35:14
*******************************************************************************/
    bool RsltPointUpFrontInsToRsdb();
    /*******************************************************************************
* 函 数 名: 
* 函数描述: 插入新的测点告警记录
* 参数说明: 
*    入 参: 
*    出 参: 
* 返 回 值:
*    成 功:
*    失 败:	
*  作  者 : %王凯%，15802613961
* 创建日期: 2016-12-23 15:36:10
*******************************************************************************/
    bool RsltPointInToRsdb();
    /*******************************************************************************
* 函 数 名: 
* 函数描述: 更新测点告警记录
* 参数说明: 
*    入 参: 
*    出 参: 
* 返 回 值:
*    成 功:
*    失 败:	
*  作  者 : %王凯%，15802613961
* 创建日期: 2016-12-23 15:36:42
*******************************************************************************/
    bool RsltPointUpBackInRsdb();
    /*******************************************************************************
* 函 数 名: 
* 函数描述: 更新测点实时值
* 参数说明: 
*    入 参: 
*    出 参: 
* 返 回 值:
*    成 功:
*    失 败:	
*  作  者 : %王凯%，15802613961
* 创建日期: 2017-1-23 15:29:29
*******************************************************************************/
    bool RsltPointUpValuesRsdb();
    /*******************************************************************************
* 函 数 名: 
* 函数描述: 测点记录插入失败时回滚内存记录
* 参数说明: 
*    入 参: int ipos 回滚记录位置
*    出 参: 
* 返 回 值:
*    成 功:
*    失 败:	
*  作  者 : %王凯%，15802613961
* 创建日期: 2016-12-23 10:23:57
*******************************************************************************/
    void RollbackPoint(int ipos);
    void RollbackGroup(int ipos);
    void RollbackModelToSet(int ipos);
    void RollbackCondition(int ipos);
    void RollbackCosione(int ipos);
    bool RsltGroupUpFrontInsToRsdb();
    bool RsltGroupInToRsdb();
    bool RsltGroupUpBackInRsdb();
    bool WriteAlarmGroupToRsdb();

    bool RsltModelToSetUpFrontInsToRsdb();
    bool RsltModelToSetInToRsdb();
    bool RsltModelToSetUpBackInRsdb();

    bool RsltModelConditionUpFrontInsToRsdb();
    bool RsltModelConditionInToRsdb();
    bool RsltModelConditionUpBackInRsdb();

    //bool RsltModelCosineUpFrontInsToRsdb();
    bool RsltModelCosineInToRsdb();
    bool RsltModelCosineUpBackInRsdb();

    bool WriteAlarmPointToRsdb();
    bool WriteAlarmModelGroupToRsdb();
    bool WriteAlarmModeltoSetToRsdb();
    bool WriteAlarmModelCondtionToRsdb();
    bool WriteAlarmModelCosineToRsdb();

    /*******************************************************************************
* 函 数 名: DealModelPCAlarm
* 函数描述: 模型故障定位处理
* 参数说明: 
*    入 参: AlarmModel	* pmodel 模型对象
*    出 参: 
* 返 回 值:
*    成 功:
*    失 败:	
*  作  者 : %王凯%，15802613961
* 创建日期: 2016-12-7 16:30:51
*******************************************************************************/
    void DealModelPCAlarm(AlarmModel	* pmodel);
    bool CompSim (AlarmModel	* pmodel);
    void CalPCAlarm(CDCosine* cosine,const MapStringToAlaramModelGroup &mapModelCategory,const double sumAlram);
    /*******************************************************************************
* 函 数 名: CalSoreMolWeight
* 函数描述: 计算加权得分
* 参数说明: 
*    入 参: const int &curValue 告警值 const double &weight 权重 double &sumScore 得分
*    出 参: 
* 返 回 值:
*    成 功:
*    失 败:	
*  作  者 : %王凯%，15802613961
* 创建日期: 2016-12-7 16:09:46
*******************************************************************************/
    void CalSoreMolWeight(const int &curValue,const double &weight,double &sumScore);
    /*******************************************************************************
* 函 数 名: SetSoreAlarmValue
* 函数描述: 根据得分设置告警级别
* 参数说明: 
*    入 参: int &lastValue 上次值 int &curValue 本次值 const double & sumScore 得分
*    出 参: 
* 返 回 值:
*    成 功:
*    失 败:	
*  作  者 : %王凯%，15802613961
* 创建日期: 2016-12-7 16:10:25
*******************************************************************************/
    void SetSoreAlarmValue(int &lastValue,int &curValue,double & alarmScore,double & alarmLastScore,
                           double & sumScore,const bool & is_score);
    void DealPointlAlarm(AlarmPointInfo * ppoint,bool isWatch,bool isChangeContion,int simValue);
    //bool loadValue(MapStringToSetInfo &mMapSetInfo);
    void SetMaxMinArv(AlarmPointInfo* point);
    void DealSetAlarm(AlarmSetInfo * pset);
    bool SetAlarmToRsdb();

    void DealSysAlarm(AlarmSetSys * psys);
    void DealModelAlarm(AlarmModel	* pmodel);
    void SetAlarmModelRslt(AlarmModel	* pmodel);
    void clearn();
};

#endif//__SETDEAL_H__


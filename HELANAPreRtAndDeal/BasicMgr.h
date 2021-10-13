/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: BasicMgr.h
* 文件描述: 基础配置管理类
*  作  者 : %王凯%，
* 创建日期: 2015-5-27 16:14:00
*******************************************************************************/

#ifndef __BASICMGR_H__
#define __BASICMGR_H__

#include <map>
#include <vector>
#include <string>
#include <iostream>

#include "TypeDef.h"
#include "AlarmSetDeal.h"
#include "mutex.h"
//#include "buff_points.h"
//class BuffPoints;
#define HELA_THREAD_ID_FACTORY_CAL			"FactoryCalThread%s"		//电厂计算线程ID
class RDbOperationSimple;

class BasicMgr
{
private:
    VectorAlarmScore					mVectorAlarmScore;
    MapStringToAlarmSetInfo            mMapAlarmSet;//机组告警map

    MapMonmentDatas					mMapMonment;			 //历史追算数据存储集合
    // VectorString                       mVectorConPoint;       //模型模式计算条件所有引用测点集合
    MapStringToString					mMapPointSourceName;		//实时数据库或DCS点标识映射D点名
    //MapStringToString					mMapAllPointSourceName;   //所有测点集合
    MapStringTostrEX					mMapAllPointSourceName;   //所有测点集合
    //MapStringToModelAllPointSource		mMapAllPointSourceName;   //所有测点集合
    MapStringToMDataValueInfo			mMapDataValueInfo;			//点值集合
    IN MapStringToPointData			mMapPointData;
    IN MapStringToIndexConfInfo		m_mapIndexConfInfo;    // 存放指定的电厂编号名称对应指标配制信息
    IN MapStringToBool					mMapModleNameStatus;	   //所有获取模型的模型id集合
    IN MapStringToSetCfg				mMapSetInfo;
    MapStringToDataMode                mMapModeInfo;
    MapStringToModeMethodAvg           mMapModeMethodAvg;    //模型模式训练样本
    MapStringToDouble                  mMapWrite;                 //回写实时数据库数据集合
    bool								mIsExistMaunalPoint;

    RDbOperationSimple *				mSimpleOpt;
    static bool						smSanityCheck;

    bool                               ismDealAlarm;
    int								mcountPoints;//写文件个数
public:
    GetDateWay							msysType;                //系统类型1：子站系统  2：主站系统
    GetDateWay							mGetDateType;            //获取数据类型1：从实时数据库获取数据 2：从目录获取数据
    unsigned short						mDCNo;					 //电厂编号
    std::string							m_strFactoryCode;        //电厂编号
    BuffPoints*							m_pRecOpt;               // Buff读取文件操作对象
    std::map<std::string, BuffPoints* > m_mapSendOpt;	         //发送数据目录操作集合

    RsdbAdapter*					mQtOpt;		                //QT关系数据库适配器对象
    std::string						mTheadId;
    AlarmSetDeal*					mAlarmdate;
    //bool                                mInit;         //重新初始化
public:
    BasicMgr(void);
    BasicMgr(const std::string &strFactoryId);
    virtual ~BasicMgr(void);

    void WriteRsdb(const long mCurSeCalTime);
    
    bool BuffInitial(const GetDateWay  iSysType,const GetDateWay GetWay);

    void WriteBuffer(long mCurSeCalTime);    //写文件
    bool RecBuffer( long &lTimeStamp,
                    const long nowTime,
                    MapStringToSetCfg &mMapSetInfo,
                    MapStringToString &mMapPointSourceName,
                    MapStringToPointData &mPointData);		//读取解析文件
    /*
     * 功能描述:  初始化实时数据库
     * 输入参数: 无
     * 输出参数: 无
     * 返回值: true(成功)、false(失败)
    */
    //bool	initialRtdb();


    /*
     * 功能描述:  分别从实时数据库与关系数据库中读入采集原始值D点与手工值H点
     * 输入参数: 无
     * 输出参数: 无
     * 返回值: true(成功)、false(失败)
    */
    bool	loadPointData(long &lTimeStamp,const long nowTime);

    bool	loadHisPointData(const long StartTime,const long EndTime);
    void    ClearMapMonmentDatas();
    void	ClearMapMonmentDatasnop(long strKey);
    void	SetAllMothAvgData();

    bool rtdbGetRtTagTime(long &lTimeStamp);
    /*
     * 功能描述:  导入配置信息
     * 输入参数: 无
     * 输出参数: 无
     * 返回值: true(成功)、false(失败)
    */
    bool loadConfigInfo(const bool isFirstCal,bool &ModConf,long &mCurSeCalTime);

    bool UpdataCalTime(std::string strcalTime,const int itype);
    bool UpdateServiceVersion(std::string strServiceName,std::string strVersion,std::string strLog);
    /*
     * 功能描述:  回写实时数据库
     * 输入参数: 无
     * 输出参数: 无
     * 返回值: true(成功)、false(失败)
    */
    bool WriteToRtdb(const long &lCalTimeStamp);
    /*
     * 功能描述:  将指标M点回写实时数据库
     * 输入参数: 无
     * 输出参数: 无
     * 返回值: true(成功)、false(失败)
    */

    /*
     * 功能描述:  将指标M点值写入缓存中
     * 输入参数: 无
     * 输出参数: 无
     * 返回值: true(成功)、false(失败)
    */
    bool	saveToRdb(const long &lCalTimeStamp);
    // 功能描述: 计算模型
    /*******************************************************************************
    * 函 数 名: .CalMode
    * 函数描述: 模型计算
    * 参数说明:
    *    入 参:
    *    出 参:
    * 返 回 值:
    *    成 功:
    *    失 败:
    *  作  者 : 王凯，15802613961
    * 创建日期: 2016-1-21 15:43:54
    *******************************************************************************/
    
    //void    CalMode();
    MapStringToBool	&getMapModleNameStatus()   { return mMapModleNameStatus;}
    MapStringToAlarmSetInfo &getmMapAlarmSetInfo()   {return  mMapAlarmSet;}
    MapStringToDataMode &getmMapModeInfo(){return mMapModeInfo;}
    MapStringToSetCfg &getmMapSetInfo(){return mMapSetInfo;}
    MapStringToModeMethodAvg &getmMapModeMethodAvg(){return mMapModeMethodAvg;}
    MapStringToDouble &getmMapWrite() {return mMapWrite;}
    VectorAlarmScore  *getmVectorAlarmScore()	{return &mVectorAlarmScore;}
    MapStringToPointData&  getPointData() {return mMapPointData;}
    MapStringToIndexConfInfo & getIndexConfInfo() {return m_mapIndexConfInfo;}
    MapStringToString		& getMapPointSourceName() {return mMapPointSourceName;}
    MapMonmentDatas			& getMapMonment() {return mMapMonment;}
    // 功能描述: 从关系数据库中机组及系统信息
    bool loadAlarmSetData();
    void  CleanMapWrite();

private:
    void  BuffIntoData(BuffPoints *buffWrite);
    //bool CalMonment();
    //void SetModelPointValues(long &lTimeStamp,const CMonmentDatas* monment,const int iCount);
    void	CheckModelAvgPointFitInfPoint();
    void	CheckModelAvgPointFitInfPointOnly();
    bool    InitSendBufferOpt();
    void	SetMothAvgData(MapStringToDataMode &mapModeInfo);

    // 功能描述: 从关系数据库中模型信息
    bool	loadModeData();
    
    //从关系数据库读取模型处理方法配置
    bool    loadModeMuFun();

    //从关系数据库读取带负荷能力配置
    bool loadFhnlData();

    //从关系数据库读取指标配置
    bool loadIndex();

    // 功能描述: 检查耗差指标回写指标点是否在实时数据库
    bool checkWriteBackCodeRtdbIsExist();
    void checkWritePointRtdbIsExist(MapStringToMDataValueInfo &mapPoints);
    bool checkReadSourceIdRtdbIsExist();
    bool checkIndexSourceIdRtdbIsExist();

    // 功能描述: 从实时数据库中读取采集原始值D点
    //bool	loadDPointValue(long &lTimeStamp,MapStringToMDataValueInfo mMapDataValueInfo);

    void	printMapModeConfInfo();
    void	printMapPointSourceName();

    // 功能描述: 清空所有配置信息
    void	cleanVar();
    void	cleanAlarmVar();

    void	sanityCheck(const int flag, const std::string &strmsg="");
    void	sanityCheck1(const int flag, const std::string &prefix="");

    void InsertMapStringToPointData(std::string strPoint,std::string strSouce,std::string strSet,PointType itype,std::string strFullPointId="");
    /*******************************************************************************
* 函 数 名: FhnlToPointData
* 函数描述: 发电能力引用测点/指标解析
* 参数说明: 
*    入 参: MapStringToDfhnl& sysMapDfhnl
*    出 参: 
* 返 回 值:
*    成 功:
*    失 败:	
*  作  者 : %王凯%，18569558896
* 创建日期: 2018-5-7 9:49:13
*******************************************************************************/
    void  FhnlToPointData(MapStringToDfhnl& sysMapDfhnl,std::string strSet);
    /*******************************************************************************
* 函 数 名: GetNeedPoint
* 函数描述: 解析所应用的测点、指标到结果集
* 参数说明: 
*    入 参: 
*    出 参: 
* 返 回 值:
*    成 功:
*    失 败:	
*  作  者 : %王凯%，18569558896
* 创建日期: 2018-5-7 9:50:33
*******************************************************************************/
    void GetNeedPoint();

    void GetIndexPoint();

    void  ModelFunCheck(VectorString &condtionPoints,MapStringToPointGroup &modelGroups);

};
#endif

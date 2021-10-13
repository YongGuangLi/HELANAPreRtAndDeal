/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: StartupServer.h
* 文件描述: 主控类
*  作  者 : 王凯，
* 创建日期: 2016-1-12 11:23:42
*******************************************************************************/

#ifndef __STARTUPSERVER_H__
#define __STARTUPSERVER_H__

#include <list>
#include "BasicMgr.h"
#include "PointPreCal.h"
//class BasicMgr;
class StartupServer
{
private:
    bool							mInit;
    bool							mFirstCal;				 //服务开始标志
    bool							mModConf;                //配置是否修改
    BasicMgr *						mBaseMgr;
    PointPreCal*                    mPointPreCal;
    long 							mSeCalCycSec;			 //服务计算周期
    long							mSeLastTime;			 //服务计算周期上一次计算时间
    long							mCurSeCalTime;			 //当前正在进行计算的采集原始值D点数据时间
    long                            mNowTime;                //当前应用服务器系统时间
    std::list<double>				mServerCalTimes;		 //延时数据列表
    RecursiveCalculateIndex*		mCalculateIndex;		//计算指标


public:
    static bool						smIsStartDelay;			 //正在延时计算标识
    static bool						smDestory;				 //停止信号标识
    static bool						smSanityCheck;
    std::string						m_strFactoryCode;        //电厂编号
    int								mHisGetNum;              //电厂追加补算多少小时

    int								mHisToRtDevMin;          //电厂追加补算切换到实时计算间隔时间 分钟

    std::string						m_strSerivceName;        //服务名称
public:
    StartupServer(void);
    ~StartupServer(void);

    /*
     * 功能描述:  初始化变量
     * 输入参数: 无
     * 输出参数: 无
     * 返回值: true(成功)、false(失败)
    */
    //bool	initial();
    bool	initial(const GetDateWay iSysType,const GetDateWay GetDateWay);
    /*
     * 功能描述:  传递服务停止信号
     * 输入参数: 无
     * 输出参数: 无
     * 返回值: true(成功)、false(失败)
    */

    void	destory();

    /*
     * 功能描述:  服务停止释放资源
     * 输入参数: 无
     * 输出参数: 无
     * 返回值: true(成功)、false(失败)
    */
    void	stop();

    /*
     * 功能描述:  导入所有配置信息并开始计算
     * 输入参数: 无
     * 输出参数: 无
     * 返回值: true(成功)、false(失败)
    */
    bool	calculate();

private:

    //bool   InitSendBufferOpt(void);
    // 功能描述: 周期计算各指标
    void	run();

    void    RtimeCal();		//实时计算
    void    HisCal(long StartTime,long EndTime);		//历史追算
    void	CalMonment(MapMonmentDatas	&mMapMonment);
    void	SetModelPointValues(MapStringToSetCfg	&mMapSetInfo,
                                MapStringToPointData &mMapPointData,
                                MapStringToString &pPointSourceName,
                                const CMonmentDatas* monment);

    /*void	SetModelPointValues(MapStringToSetCfg	&mMapSetInfo,MapStringToString &mMapPointSourceName,
        MapStringToPointData &mMapPointData,const CMonmentDatas* monment);*/
    // 功能描述: 获取当前正在进行计算的D点数据时间
    long	getServerCalTime();



    void	sanityCheck(const int flag);

    void	testPretreat();

    void	testCal();
};

#endif

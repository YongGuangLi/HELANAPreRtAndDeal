/*******************************************************************************
* Copyright（C）,2018-2023,DTXY Tech .Co.Ltd;
* 文 件 名: RecursiveCalculateIndex.h
* 文件描述: 递归计算指标实现类
*  作  者 : 王凯，18569558896
* 创建日期: 2018-2-23 11:52:12
*******************************************************************************/
#ifndef __RECURSIVECALCULATEINDEX_H__
#define __RECURSIVECALCULATEINDEX_H__

#include "TypeDef.h"
#include "singleton.h"
#include "DataValueInfo.h"
//#include "dw_hcfx_head.h"
#define IDS_INDEX_CONFVAR_ERROR "计算指标[指标编号:%s]出错,可能是变量串中的对象不存在或者计算公式配置错误造成,请检查指标公式配置,该指标值已用其默认值代替 \n [指标计算公式:]%s \n [指标变量串:]%s"
#define IDS_INDEX_CONFIG_ERROR  "计算指标[指标编号:%s]出错,可能是变量串中的对象不存在或者计算公式配置错误造成,请检查指标公式配置,该指标值已用其默认值代替 \n [指标计算公式:]%s \n [指标变量串赋值:]%s"
#define IDS_PROGRAM             "调用计算引擎申请计算错误,公式验证错误,请检查指标的配置公式,指标ID:%s;"
#define IDS_CALCULATE           "调用计算引擎计算指标错误 指标ID:%s;"
#define IDS_NOT_CONFIG_SETS     "指标没有配置机组号,指标编号:%s;"
#define M_SET_GMH            "_gdbmF"                       //机组的供电标煤耗
#define M_SET_FMH            "_fdbmF"                       //机组的发电标煤耗
#define M_SUB                "SUB@"							//自减函数函数名称，当前值减上一个周期的值预测值函数
#define M_NOW   			 "NOW@"						    //表示当前时间,系统时间 "小时.分"函数名称
#define M_YEAR               "YEAR@"						//当前时间的年函数名称
#define M_MONTH              "MONTH@"						//当前时间的月函数名称
#define M_WEEK				 "WEEK@"						//当前时间的周函数名称
#define M_DAY                "DAY@"							//当前时间的日函数名称
#define M_PERIODTIME         "PERIODTIME@"					//系统实时计算周期 单位秒的函数名称
#define M_LOG				 "LOG@"						    //LOG函数名称
#define M_PRE                "PRE@"						    //预测值函数的函数名称
#define M_FILT				 "FILT@"						//滤波（平滑）值函数的函数名称

#define M_AIMU3D			 "AIMU3D@"						//上限值函数函数名称
#define M_AIMU2D			 "AIMU2D@"						//上限值函数函数名称
#define M_MAX			     "MAX@"						    //(最大值)上限值函数函数名称
#define M_AIMD3D             "AIMD3D@"						//下限值函数函数名称
#define M_AIMD2D             "AIMD2D@"						//下限值函数函数名称
#define M_MIN                "MIN@"						    //最小值函数名称

struct PubSetInfo;
struct DataInfo;
struct IndexConfigInfo;
class MutexLock;

class RecursiveCalculateIndex
{
public:
	//DECLARE_SINGLETON_INIT(RecursiveCalculateIndex)
	RecursiveCalculateIndex();
	~RecursiveCalculateIndex();
private:
	std::vector<std::string> 		mForeIndexForUsed;  //嵌套指标数组
	time_t              			mCnPeriodDateTm;     //子站计算周期的服务日期
	double              			mPeriodTime;		  //计算周期间隔时间--单位为(秒)
	bool							mFirstCal;
	long							mElefTime;
	long							mElefFrontTime;
	static MutexLock*				smMutexLock;
public:
	bool	startCalculate(
				MapStringToIndexConfInfo &pMapIndexConfInfo, 
				MapStringToPointData &pMapDataValueInfo,
				MapStringToDouble &mMapWrite,
				const long &pRtdbTime);
	double 	calEngine(
		std::string szICode,
		std::string szEngOutVar,
		std::string szEngLocVar,
		std::string szEngEvalVar,
		std::string szEngExp);

	std::string getParamValue(
		MapStringToIndexConfInfo &pMapIndexConfInfo, 
		MapStringToPointData &pMapDataValueInfo,
		std::string szParentId, 
		std::string szChildId);
private:
	void	calculateSetCondition(
				MapStringToIndexConfInfo &pMapIndexConfInfo, 
				MapStringToPointData &pMapDataValueInfo);

	void 	calculateIndex(
				MapStringToIndexConfInfo &pMapIndexConfInfo, 
				MapStringToPointData &pMapDataValueInfo,
				MapStringToDouble &mMapWrite);


	void 	calIndexParam(
				MapStringToIndexConfInfo &pMapIndexConfInfo, 
				MapStringToPointData &pMapDataValueInfo,
				IndexConfigInfo* pIndexConfInfo); 

	void 	calculateArith(
				MapStringToIndexConfInfo &pMapIndexConfInfo, 
				MapStringToPointData &pMapDataValueInfo,
				IndexConfigInfo* pIndexConfInfo);

	

	void 	checkIndexValue(
				MapStringToIndexConfInfo &pMapIndexConfInfo, 
				MapStringToPointData &pMapDataValueInfo,
				IndexConfigInfo* pIndexConfInfo,
				std::string szICode,
				double fIndexVal,
				double fDefaultVal);

	

	void 	aheadCalIndex(
				MapStringToIndexConfInfo &pMapIndexConfInfo, 
				MapStringToPointData &pMapDataValueInfo,
				IndexConfigInfo* pIndexConfInfo,
				std::string szPareID,
				std::string szParamID);

	bool 	isExistState(
				MapStringToIndexConfInfo &pMapIndexConfInfo, 
				std::string szFatherID,
				std::string szSunID);

	bool	judgeIsExcept(double fExceptVal);

	bool	getDasValue(MapStringToPointData &pMapDataValueInfo, std::string szID,std::string& szValue);

	double	getForeValue(MapStringToPointData &pMapDataValueInfo, std::string szID);

	double  getDasValue(MapStringToPointData &pMapDataValueInfo, std::string szID);


	bool sanityCheck(MapStringToPointData &pMapDataValueInfo);
	bool sanityCheck1(MapStringToPointData &pMapDataValueInfo);
	bool sanityCheck2(MapStringToPointData &pMapDataValueInfo);
	bool sanityCheck3(MapStringToPointData &pMapDataValueInfo);
};

#endif

#ifndef __POINTPRECAL_H__
#define __POINTPRECAL_H__

#include "TypeDef.h"
#include "DataValueInfo.h"
#define NonMonitoring			 "NonMonitoring"

class MutexLock;
class RecursiveCalculateIndex;
class PointPreCal
{
    //DECLARE_SINGLETON_INIT(PointPreCal)
public:
	PointPreCal();
	PointPreCal(RecursiveCalculateIndex *pCalculateIndex);
	~PointPreCal();
public:
    void CalData(MapStringToBool &mMapModleNameStatus,
							  MapStringToSetCfg &mMapSetInfo,
							  MapStringToModeMethodAvg &mModeMethodAvg,
							  MapStringToPointData	&mMapPointData,
							  MapStringToIndexConfInfo &pMapIndexConfInfo,
							  MapStringToDouble &mMapWrite,
							  GetDateWay itype);

    void CalculatePre(MapStringToBool &mMapModleNameStatus,MapStringToSetCfg &mMapSetInfo,
					  MapStringToModeMethodAvg &mModeMethodAvg,
					  MapStringToDouble &mMapWrite,GetDateWay itype);
	void CalDfh(MapStringToSetCfg &mMapSetInfo,MapStringToPointData &mMapPointData,MapStringToDouble &mMapWrite);

	void CalculateAllModeCon(MapStringToSetCfg &mMapSetInfo,
							 MapStringToPointData &mMapPointData,
							 MapStringToIndexConfInfo &pMapIndexConfInfo,
							 MapStringToDouble &mMapWrite);
private:

	void GetPointToMapWrite(MapStringToDouble &mMapWrite,MapStringToPointData &mMapPointData);
	void DcPreDeal(DataMode* mode_info,MapStringToModeMethodAvg &mModeMethodAvg,
		MapStringToDouble &mMapWrite,double  &sum,double &sumw);

	void DwPreDeal(DataMode* mode_info,MapStringToDouble &mMapWrite,double  &sum,double &sumw);

    void CalculateModeCon( MapStringToDataMode &mModeInfo,
										MapStringToPointData	&mMapPointData,
										MapStringToIndexConfInfo &pMapIndexConfInfo,
										MapStringToDouble &mMapWrite);
/*******************************************************************************
* 函 数 名: 
* 函数描述: 计算区间带负荷
* 参数说明: 
*    入 参: IN const double defFh 机组额定功率,IN const double RtimeFh 机组实时功率,IN const double dValue 测点值
*			MapStringToIntervalEX &mMapInterval 区间配置
*    出 参: OUT double &fValue 区间计算得到的带负荷能力值
* 返 回 值:
*    成 功:
*    失 败:	
*  作  者 : %王凯%，18569558896
* 创建日期: 2018-5-17 17:08:38
*******************************************************************************/
	void CalDfhPoint(IN const double defFh,IN const double RtimeFh,
					IN const double dValue, IN  MapStringToIntervalEX &mMapInterval,
					OUT double &fValue,const bool is_tj);
	void  PreValueToMapWrite(DataValueInfo *pointData,MapStringToDouble &mMapWrite,bool isGetLast = false);
    void  SetPreValue(DataMode* mode_info,MethodAvg* mode_fun,const double sim,const std::vector<double> pm,const std::vector<double> mt,MapStringToDouble &mMapWrite);  
	void  CalGroupSim(DataMode* mode_info,MapStringToDouble &mMapWrite);
	/*std::string getParamValue(const std::string szParentId,const std::string szChildId,MapStringToPointData	&mMapPointData);
	double calEngine(std::string szICode,
		std::string szEngOutVar,
		std::string szEngLocVar,
		std::string szEngEvalVar,
		std::string szEngExp);*/
public:
    std::vector<double> pm,mt; 
    std::string err;   
private:
	MutexLock*					m_pMutexLock;
	RecursiveCalculateIndex*	mCalculateIndex;
	//int itest;
};
#endif//__POINTPRECAL_H__


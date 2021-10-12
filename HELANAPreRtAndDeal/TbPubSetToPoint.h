/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: TbPubSetToPoint.h
* 文件描述: 查询机组到测点配置
*  作  者 : %王凯%，
* 创建日期: 2016-1-15 15:50:33
*******************************************************************************/
#ifndef __TBPUBSETTOPOINT_H__
#define __TBPUBSETTOPOINT_H__

#include "TypeDef.h"
#include "RDbOperationComplex.h"
#include "../funlib/FunPublic.h"

#define CFG_OUTPUT_TOTAL                 11
#define CFG_VALUE_SIZE                   50
#define CFG_EXP_SIZE					  1000
#define CFG_CONFIG						"TbPubSetToPoint"
class TbPubSetToPoint:public RDbOperationComplex
{
private: 

	void setOutVarAndFunc(const std::string strParse,VectorString  &VectorConPoint);

	bool loadValue(MapStringToSetCfg &mapSetInfo,MapStringToBool &mMapModleNameStatus);

	bool loadValue(MapStringTostrEX &mapAllPointSourceName);

	void loadAparam(std::vector<VarParam>& mVectorParamCfgs,std::string& strPoint,double& aSource,
		std::string& aCap,std::string& aValue,std::string& aMax,std::string& aMin);
	void InsertMapStringToPointData(MapStringToPointData& mMapPointData,
		std::string strPoint,std::string strSouce,std::string strSet,PointType itype);
public:
	TbPubSetToPoint(void);
	TbPubSetToPoint(RsdbAdapter * QtOpt); 
	~TbPubSetToPoint(void);
	bool loadDB(MapStringToSetCfg &SetInfo,MapStringToBool &mMapModleNameStatus,std::string strCon);
	bool loadDBPoint(MapStringTostrEX &mMapPointSourceName,std::string strCon);

	void GetNeedPoint(MapStringToString &mMapAllPointSourceName,MapStringToString &mMapPointSourceName,
		MapStringToSetCfg &SetInfo,MapStringToPointData& mMapPointData);
};

#endif//__TBPUBSETTOPOINT_H__

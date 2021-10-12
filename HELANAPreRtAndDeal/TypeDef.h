/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: TypeDef.h
* 文件描述: 
*  作  者 : %wk%，
* 创建日期: 2016-1-15 9:13:12
*******************************************************************************/														 
#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#include <vector>
#include <map>
#include "DataValueInfo.h"
#include "ModeMethodAvgConfig.h"
#include "AlarmSetInfo.h"
#include "IndexConfigInfo.h"
#include "buff_points.h"

#define IN
#define OUT
#define HELA_SVR_START						0
#define HEAL_SVR_STOPING					1
#define HEAL_SVR_STOP						2

#define  NOExitOrg                      "(回写测点原始值的测点在rtdb不存在或点名为空)"
#define  NOExitPre                      "(回写测点期望值的测点在rtdb不存在或点名为空)"
#define  NOExitSim                      "(回写测点健康度值的测点在rtdb不存在或点名为空)"
#define  NOExitGroupSim                 "(回写分类健康度值的测点在rtdb不存在或点名为空)"
#define  NOExitModCon                   "(回写模型模式值的测点在rtdb不存在或点名为空)"
#define  NOExitModSim                   "(回写模型健康度值的测点在rtdb不存在或点名为空)"
#define  NOExitSetJkd					"(回写机组健康度值的测点在rtdb不存在或点名为空)"
#define  NOExitSetDfh					"(回写机组带负荷的测点在rtdb不存在或点名为空)"
#define  NOExitSysJkd					"(回写系统健康度值的测点在rtdb不存在或点名为空)"
#define  NOExitSysDfh					"(回写系统带负荷的测点在rtdb不存在或点名为空)"

struct strEX
{
	std::string str1;
	std::string str2;
	std::string strFullCode;
};
typedef  std::map<std::string, strEX>					MapStringTostrEX;
typedef  MapStringTostrEX::iterator						MapStringTostrEX_It;

typedef  std::vector<std::string>						VectorString;
typedef  VectorString::iterator							VectorString_It;
typedef  std::map<std::string, std::string>				MapStringToString;
typedef  MapStringToString::iterator					MapStringToString_It;

typedef std::map<std::string, IndexConfigInfo*>			MapStringToIndexConfInfo;
typedef MapStringToIndexConfInfo::iterator				MapStringToIndexConfInfo_It;

typedef  std::map<std::string,mModelAllPointSource *>	MapStringToModelAllPointSource;
typedef  MapStringToModelAllPointSource::iterator		MapStringToModelAllPointSource_It;


typedef std::map<std::string, double>					MapStringToDouble;
typedef MapStringToDouble::iterator						MapStringToDouble_It;

typedef std::map<std::string, bool>						MapStringToBool;
typedef MapStringToBool::iterator						MapStringToBool_It;

typedef std::map<std::string, SysCfg *>					MapStringToSysCfg;
typedef MapStringToSysCfg::iterator						MapStringToSysCfg_It;
typedef MapStringToSysCfg::const_iterator				MapStringToSysCfg_const_It;

typedef std::map<std::string, SetCfg *>					MapStringToSetCfg;
typedef MapStringToSetCfg::iterator						MapStringToSetCfg_It;
typedef MapStringToSetCfg::const_iterator				MapStringToSetCfg_const_It;

typedef std::map<std::string, DataMode *>		        MapStringToDataMode;
typedef MapStringToDataMode::iterator			        MapStringToDataMode_It;
typedef MapStringToDataMode::const_iterator             MapStringToDataMode_const_It;

typedef std::map<std::string, ModelCondition *>		    MapStringToModeCond;
typedef MapStringToModeCond::iterator					MapStringToModeCond_It;

typedef std::map<std::string, MethodAvg *>		        MapStringToMethodAvg;
typedef MapStringToMethodAvg::iterator		            MapStringToMethodAvg_It;

typedef std::map<std::string,ModeMethodAvg*>		    MapStringToModeMethodAvg;
typedef MapStringToModeMethodAvg::iterator		        MapStringToModeMethodAvg_It;



typedef std::map<std::string, BuffPoints* >::iterator mapBuffPoints_It;
#endif//__TYPEDEF_H__

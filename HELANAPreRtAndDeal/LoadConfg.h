/*******************************************************************************
* Copyright（C）,2016-2021,DTXY Tech .Co.Ltd;
* 文 件 名: LoadConfg.h
* 文件描述: 读取基础配置
*  作  者 : %王凯%，15802613961
* 创建日期: 2016-10-18 17:36:25
*******************************************************************************/
#ifndef __LOADCONFG_H__
#define __LOADCONFG_H__

#include "Util.h"
#include "AlarmSetInfo.h"
#include "RDbOperationComplex.h"

#define  LOAD_CONFG   "loadConfg"
class LoadConfg:public RDbOperationComplex
{
public:
	LoadConfg(void);
	virtual ~LoadConfg(void);
	bool loadAlarmInf(MapStringToAlarmSetInfo &mapAlarmSetInfo,VectorAlarmScore &mVectorAlarmScore);
	void cleanVar(MapStringToAlarmSetInfo &mapAlarmSetInfo);
	void clearConsineCfg(MapStringToAlaramCosine &mapAlarmCosine);
private:
	bool loadAlarmSetToPoint(MapStringToAlarmSetInfo &mapAlarmSetInfo);
	bool loadAlarmSetToPointValue(MapStringToAlarmSetInfo &mapAlarmSetInfo);

	bool loadAlarmModelCosine(MapStringToAlarmSetInfo &mapAlarmSetInfo);
	bool loadModelCosineValue(MapStringToAlarmSetInfo &mapAlarmSetInfo);

	bool loadAlarmScore(VectorAlarmScore &mVectorAlarmScore);
	bool loadAlarmScoreValue(VectorAlarmScore &mVectorAlarmScore);
};

#endif//__LOADCONFG_H__



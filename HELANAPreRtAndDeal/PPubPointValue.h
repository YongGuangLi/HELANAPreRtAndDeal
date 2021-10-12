/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: PPubPointValue.h
* 文件描述: 存储测点实时值、预测值、健康度
*  作  者 : %林晓雨%，
* 创建日期: 2015-7-27 11:53:59
*******************************************************************************/

#ifndef __PPUBPOINTVALUE_H__
#define __PPUBPOINTVALUE_H__

#include "RDbOperationComplex.h"
//#include "PreAlarmRsltInfo.h"
#include "DataValueInfo.h"
#include "TypeDef.h"

#define PPOINT_VALUE			"PPubPointValue"

class PPubPointValue : public RDbOperationComplex
{
public:
    PPubPointValue();
    virtual ~PPubPointValue(void);
public:
    // 功能描述: 执行存储过程接口函数
    bool ExecPPubPointValue(const long &lCalTimeStamp, MapStringToDataMode &mMapModeInfo);
private:
    //bool BindPPubPointValue();
private:
	//char		mPointId[ROW_COUNT][in1_SIZE];
	//char		mUpdateDate[ROW_COUNT][in1_SIZE];

	//char**		mPointIdPtr;	//点编号
	//char**		mUpdateDatePtr; //更新时刻

	//double*		mSimValue;		//健康度值

};

#endif

/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: test_data_parser.h
* 文件描述: 数据解析测试程序
*  作  者 : %林晓雨%，18942552977
* 创建日期: 2014-9-22 10:19:07
*******************************************************************************/
#ifndef __TEST_DATA_PARSER_H__
#define __TEST_DATA_PARSER_H__

#include "data_def.h"
#include <iostream>

class DataMgr;
class TestDataParser
{
	DataMgr *			mSendData;
	DataMgr	*			mReData;
	int					mNum;
public:
	TestDataParser(void);
	~TestDataParser(void);
	bool config();
	bool run();
private:
	bool createPublicPointData(PointDatas * pPoints);
	bool createDCPointData(PointDatas* pPoints);
	bool createDiscPointData(PointDatas* pPoints);
	bool checkPublicPointData(const PointDatas &pLhs, const PointDatas &pRhs);
	bool checkDCPointData(const PointDatas &pLhs, const PointDatas &pRhs);
	bool checkDiscPointData(const PointDatas &pLhs, const PointDatas &pRhs);
	bool alarm();
	std::string randNameStr();
	std::string randTimeStr();
	std::string randMsgStr();
};
#endif

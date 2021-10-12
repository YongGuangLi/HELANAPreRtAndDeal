/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: dc_buff_parser.h
* 文件描述: 媒耗、脱硫、脱硝数据文件解析
*  作  者 : %林晓雨%，18942552977
* 创建日期: 2014-9-10 16:03:40
*******************************************************************************/
#ifndef __DC_BUFF_PARSER_H__
#define __DC_BUFF_PARSER_H__

#include "data_parser.h"
#include <iostream>
#include <vector>

class DCBuffParser :public DataParser
{
public:
	DCBuffParser();
	~DCBuffParser(void);

	//功能描述: 创建一个数据包
	virtual void  CreatePrivatePointValue(PointDatas* aPoints,unsigned long lPointCount);

	//功能描述:	数据打包成字符串数据
	virtual bool  PackPrivatePointDataToStr(PointDatas aPoints, std::string& strData);

	//功能描述:	从字符串中解包
	virtual bool  UnpackPrivatePointDataFromStr(PointDatas* pPoints, std::vector<std::string> &strSplits, std::vector<std::string>::iterator &i);

	//功能描述:	数据打包
	virtual void  PackPrivatePointData(PointDatas aPoints, char* &pTem);

	//功能描述: 数据解包
	virtual bool  UnpackPrivatePointData(const char* pTem, PointDatas* pPoints, long nPointCount);

	//功能描述:	获取点需要打包的包数据长度
	virtual bool  GetPointPackLen(PointDatas aPoints,long* pLen); 

	//功能描述:	 获取点数据打包的文本长度
	virtual bool  GetPointPackTxtLen(PointDatas aPoints,long* pLen);

	//功能描述:	获取包数据的类型
 	virtual bool  GetPackDataType(const void* pData, PackDataType* peDataType);

	//功能描述:	 获取点需要打包的点数据长度
	virtual bool  GetPointDataLen(PointDatas aPoints,long* pLen);

	//功能描述: 释放一个数据包
	virtual void  DeletePointData(PointDatas* aPoints);
};
#endif

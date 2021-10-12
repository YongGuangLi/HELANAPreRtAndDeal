/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: model_package_buff_parser.h
* 文件描述: 模型数据包通讯传输协议解析实现类
*  作  者 : %刘毅%，
* 创建日期: 2018-5-15 14:58:24
*******************************************************************************/
#ifndef __MODEL_PACKAGE_BUFF_PARSER_H__
#define __MODEL_PACKAGE_BUFF_PARSER_H__

#include "data_parser.h"
#include <iostream>
#include <vector>

class ModelPackageBuffParser :public DataParser
{
private:
	unsigned long 	mLPointCount;
public:
	ModelPackageBuffParser(void);
	~ModelPackageBuffParser(void);

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

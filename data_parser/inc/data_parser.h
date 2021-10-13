/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: data_format.h
* 文件描述: 数据解析接口类
*  作  者 : %林晓雨%，18942552977
* 创建日期: 2014-9-10 14:23:03
*******************************************************************************/

#ifndef __DATA_PARSER_H__
#define __DATA_PARSER_H__

#include "data_def.h"
#include <iostream>
#include <vector>

#include "file_buff.h"

class DataParser
{
private:
	ParserType		mType;
	FileBuff *		mFileBuff;
	RemoteDataType	mDataType;

protected:
	std::string		mStrError;
public:
	DataParser(const ParserType type);

	virtual ~DataParser(void);

	void config(
		const RemoteDataType &data_type,
		const std::string &path,
		const std::string &point_fname_prefix);

	//功能描述: 打开通讯
	bool rt_Open();

	//功能描述: 关闭通讯
	void rt_Close();

	//功能描述: 释放一个数据包
	virtual void  DeletePointData(PointDatas* aPoints) = 0;

	//功能描述: 创建一个数据包
	void CreatePointData(PointDatas* aPoints, unsigned long lPointCount);

	//功能描述: 接收数据
	bool  rt_Receive(PointDatas* pPoints);

	//功能描述:发送数据
	bool  rt_Send(const PointDatas& aPoints);

	//功能描述: 获取错误信息
	std::string  getError();
//功能描述:获取目录文件总个数  add by wk 2018-7-10
	int getDirFileNum();
private:
	//功能描述: 创建一个数据包
	virtual void  CreatePrivatePointValue(PointDatas* aPoints,unsigned long lPointCount) = 0;

	//功能描述:	数据打包成字符串数据
	virtual bool  PackPrivatePointDataToStr(PointDatas aPoints, std::string& strData) = 0;

	//功能描述:	从字符串中解包
	virtual bool  UnpackPrivatePointDataFromStr(PointDatas* pPoints, std::vector<std::string> &strSplits,std::vector<std::string>::iterator &i) = 0;

	//功能描述:	数据打包
	virtual void  PackPrivatePointData(PointDatas aPoints, char* &pTem) = 0;

	//功能描述: 数据解包
	virtual bool  UnpackPrivatePointData(const char* pTem, PointDatas* pPoints, long nPointCount) = 0;

	//功能描述:	获取点需要打包的包数据长度
	virtual bool  GetPointPackLen(PointDatas aPoints,long* pLen) = 0; 

	//功能描述:	 获取点数据打包的文本长度
	virtual bool  GetPointPackTxtLen(PointDatas aPoints,long* pLen) = 0;

	//功能描述:	获取包数据的类型
 	virtual bool  GetPackDataType(const void* pData, PackDataType* peDataType) = 0;

	//功能描述:	 获取点需要打包的点数据长度
	virtual bool  GetPointDataLen(PointDatas aPoints,long* pLen) = 0;
private:
	//功能描述:	 数据打包成字符串数据
	bool  PackPointDataToStr(PointDatas aPoints, std::string& strData);
	//功能描述:	 从字符串中解包
	bool  UnpackPointDataFromStr(const std::string& strData,PointDatas* pPoints);
	//功能描述:	 数据打包
	bool  PackPointData(PointDatas aPoints,void* pData,long* pDataLen);
	//功能描述:	 数据解包
	bool  UnpackPointData(const void* pData,long pDataLen, PointDatas* pPoints);
	//功能描述: 16位校验和
	unsigned short int  CheckSum16(unsigned char* pData,long pLen);

};
#endif

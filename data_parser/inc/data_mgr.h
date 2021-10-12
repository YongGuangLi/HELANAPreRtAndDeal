/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: data_mgr.h
* 文件描述: 外部操作实现类
*  作  者 : %林晓雨%，18942552977
* 创建日期: 2014-9-16 15:33:44
*******************************************************************************/
#ifndef __DATA_MGR_H__
#define __DATA_MGR_H__

#include "data_def.h"
#include <iostream>

class DataParser;

class DataMgr
{
	DataParser *	mParser;
public:
	DataMgr(void);
	~DataMgr(void);

	/* 
	* 功能描述: 创建一个数据包
	* 输入参数: 长整型数值 
	* 输出参数: 数据包信息
	* 返回值: 无
	*/
	void  CreatePointData(PointDatas* aPoints,unsigned long lPointCount);

	/* 
	* 功能描述: 释放一个数据包
	* 输入参数: 数据包信息 
	* 输出参数: 无
	* 返回值: 无
	*/
	void  DeletePointData(PointDatas* aPoints);
	
	/* 
	* 功能描述: 初始化服务
	* 输入参数: 需解析的数据协议， 数据格式， 目标目录 
	* 输出参数: 无
	* 返回值: 无
	*/
	void  rt_Initial(	
			const ParserType &type,
			const RemoteDataType &data_type,
			const std::string &dir_path,
			const std::string &point_fname_prefix);

	/* 
	* 功能描述: 卸载服务
	* 输入参数: 无 
	* 输出参数: 无
	* 返回值: 无
	*/
	void  rt_Uninitial();

	/* 
	* 功能描述: 打开通讯
	* 输入参数: 无 
	* 输出参数: 无
	* 返回值: 无
	*/
	bool  rt_Open();

	/* 
	* 功能描述: 关闭通讯
	* 输入参数: 无 
	* 输出参数: 无
	* 返回值: 无
	*/
	void  rt_Close();

	/* 
	* 功能描述:接收数据 
	* 输入参数: 无 
	* 输出参数:接收到的数据值
	* 返回值: 无
	*/
	bool  rt_Receive(PointDatas* pPoints);

	/* 
	* 功能描述:发送数据 
	* 输入参数:需发送的数据 
	* 输出参数: 无
	* 返回值: 无
	*/
	bool  rt_Send(const PointDatas& aPoints);

	/* 
	* 功能描述:获取错误信息
	* 输入参数:无 
	* 输出参数:错误信息 
	* 返回值: 无
	*/
	std::string GetError();

	//功能描述:获取目录文件总个数  add by wk 2018-7-10
	int getDirFileNum();
};
#endif

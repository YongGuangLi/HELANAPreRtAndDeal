/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: data_mgr.cpp
* 文件描述: 外部操作实现类
*  作  者 : %林晓雨%，18942552977
* 创建日期: 2014-9-16 15:35:41
*******************************************************************************/

#include "data_mgr.h"
#include "data_parser.h"
#include "dc_buff_parser.h"
#include "disc_alarm_buff_parser.h"
#include "model_package_buff_parser.h"
#include "pub_def.h"

#include <iostream>

using namespace std;

DataMgr::DataMgr(void)
:
mParser(NULL)
{
}


DataMgr::~DataMgr(void)
{
	if (mParser != NULL) delete mParser;
}


void
DataMgr::CreatePointData(PointDatas* aPoints,unsigned long lPointCount)
{
	if (mParser != NULL) mParser->CreatePointData(aPoints, lPointCount);
}


void  
DataMgr::DeletePointData(PointDatas* aPoints)
{
	if (mParser != NULL) mParser->DeletePointData(aPoints);
}



void  
DataMgr::rt_Initial(
		const ParserType &type,
		const RemoteDataType &data_type,
		const string &dir_path,
		const std::string &point_fname_prefix)
{
	switch (type)	
	{
	case DCPoint:
		 mParser = new DCBuffParser();
		 mParser->config(data_type, dir_path, point_fname_prefix);
		 break;
	
	case DiscAlarm:
		 mParser = new DiscAlarmBuffParser();
		 mParser->config(data_type, dir_path, point_fname_prefix);
		 break;

	case ModelPackage:
		mParser = new ModelPackageBuffParser();
		mParser->config(data_type, dir_path, point_fname_prefix);
		break;

	default:
		 return;
	}
}


void  
DataMgr::rt_Uninitial()
{
	if (mParser == NULL) return;
	delete mParser;
	mParser = NULL;
}


bool  
DataMgr::rt_Open()
{
	if (mParser == NULL) return false;
	return mParser->rt_Open();
}


void  
DataMgr::rt_Close()
{
	if (mParser != NULL)  mParser->rt_Close();
}


bool  
DataMgr::rt_Receive(PointDatas* pPoints)
{
	if (mParser == NULL) return false;
	return mParser->rt_Receive(pPoints);
	return true;
}


bool  
DataMgr::rt_Send(const PointDatas& aPoints)
{
	if (mParser == NULL) return false;
	return mParser->rt_Send(aPoints);
}
int DataMgr::getDirFileNum()
{
	if (mParser == NULL) return 0;
	return mParser->getDirFileNum();
}

string
DataMgr::GetError()
{
	if (mParser == NULL) return static_cast<std::string>(STRING_EMPTY);
	return mParser->getError();
}

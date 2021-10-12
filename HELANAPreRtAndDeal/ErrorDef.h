/*******************************************************************************
* Copyright（C）,2010-2015,DTXY.Tech .Co.Ltd;
* 文 件 名:	ErrorDef.h
* 文件描述: 报警信息
*  作  者 : %王凯%，
* 创建日期: 2016-1-12 10:49:28
*******************************************************************************/

#ifndef __ERROR_DEF_H__
#define __ERROR_DEF_H__

#define	 Rtdb_ERROR_POINTSOURCE				"实时数据库全点名为空"
#define  Rtdb_ERROR_RTDB_CONF				"实始化实时数据库失败,请检查配置文件%s:"
#define  Rsdb_ERROR_PUBMODEINFO				"获取模型配置失败"
#define  Rsdb_ERROR_PUBMODEFUNINFO          "获取模型计算方法配置失败"
#define  Rsdb_ERROR_ALARMMODEINFO			"获取诊断告警配置失败"
#define  Rsdb_ERROR_PUBINDEX				"获取指标配置失败"


// Internal name of the service
#define SERVICE_NAME             "HELANAPreRtAndDeal"

// Displayed name of the service
#define SERVICE_DISPLAY_NAME     "HELANAPreRtAndDeal"

// Service start options.
#define SERVICE_START_TYPE       SERVICE_DEMAND_START

// List of service dependencies - "dep1\0dep2\0\0"
#define SERVICE_DEPENDENCIES     ""

// The name of the account under which the service should run
#define SERVICE_ACCOUNT          NULL

// The password to the service account name
#define SERVICE_PASSWORD         NULL

#endif


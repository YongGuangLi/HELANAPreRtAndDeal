/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: error_def.h
* 文件描述: 错误定义类
*  作  者 : %林晓雨%，18942552977
* 创建日期: 2014-9-12 9:21:53
*******************************************************************************/

#ifndef __ERROR_DEF_H__
#define __ERROR_DEF_H__

////包含头文件
#include <string>
//错误常量定义
//指针为空
#define IDS_NULL_POINT					"指针为空"
//缓冲区太小
#define IDS_BUFFER_SMALL				"缓冲区太小"
//错误包
#define IDS_ERROR_PACK					"错误包数据"
//错误的点数据包
#define IDS_ERROR_POINT_PACK			"错误的点数据包"
//校验和错误
#define IDS_ERROR_CHECK_SUM				"校验和错误"
//包头错误
#define IDS_PACK_HEAD_ERROR				"包头错误"
//数据为空
#define IDS_DATA_NULL					"数据为空！"
//非法文件
#define IDS_ERROR_BUFFER_FILE			"非法文件！"
//目录不存在
#define IDS_DIR_ISEXIST					"目录不存在"
//扫描目录失败
#define IDS_SCANFILE_ERROR				"扫描目录失败"
//文件太大
#define IDS_BIG_DATA_ERROR				"文件太大"	
//读入失败
#define IDS_READ_FILE_ERROR				"读入失败"
//写入失败
#define IDS_WRITE_FILE_ERROR			"写入失败"
//数据错误
#define IDS_ERROR_DATA					"数据错误"
//目录下没有包文件
#define ID_DIR_NULL						"目录下没有包文件!"
#endif

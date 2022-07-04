/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: RDbOperationSimple.h
* 文件描述: 关系数据库简单操作实现类
*  作  者 : %林晓雨%，
* 创建日期: 2015-5-28 9:40:41
*******************************************************************************/

#ifndef __RDBOPERATIONSIMPLE_H__
#define __RDBOPERATIONSIMPLE_H__

#include "AlarmLog.h"
#include "RDbHead.h"
#include "TypeDef.h"
#include "DataValueInfo.h"
#include "RsdbAdapter.h"
#define ALL_VALUE_SIZE					50
//#define FETCH_NO_DATA                   100

class RDbOperationSimple
{
protected:
	std::string mStrErrorMessage;  
	RsdbAdapter * mQtOpt;
public:
	RDbOperationSimple(void);
	RDbOperationSimple(RsdbAdapter * QtOpt);
	~RDbOperationSimple(void);
	bool getFactoryNo(std::string strFactoryCode,unsigned short &DcNum);
	// 功能描述: 获取服务配置修改标识
	bool getIndexConfigStatus(std::string strFactoryCode);
	// 功能描述: 更新服务配置修改标识
	bool updateIndexConfigStatus(const int &status,std::string strFactory);
	
	//获取电厂计算更新的时间
    bool getIndexUpdataTime(long &calTime);
    bool UpdataCalTime(std::string strFactoryCode,std::string strcalTime,const int itype);
	bool isSaveTemp(const std::string pointId, const std::string setCode);

		/* 
	 * 功能描述:   执行查询SQL语句
	 * 输入参数: 无
	 * 输出参数: 无
	 * 返回值: true(成功)、false(失败)
	*/
	void stmtCloseStream();

	/* 
	 * 功能描述:  绑定查询SQL语句
	 * 输入参数: 无
	 * 输出参数: 无
	 * 返回值: true(成功)、false(失败)
	*/
	bool stmtPrepare(const std::string &classname, const std::string &str_sql);
};
#endif

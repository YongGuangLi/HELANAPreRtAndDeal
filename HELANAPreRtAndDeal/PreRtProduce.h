/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: PreRtProduce.h
* 文件描述: 服务管理类
*  作  者 : 林晓雨，18942552977
* 创建日期: 2015-05-14 15:38:21
*******************************************************************************/

#ifndef __SERVICE_HCXNJS_H__
#define __SERVICE_HCXNJS_H__

#include <map>
#include <string>
#include "thread.h"
#include "StartupServer.h"

class PreRtProduce : public Thread
{
public:
    PreRtProduce(const std::string &strFactoryCode);
    virtual ~PreRtProduce(void);
public:
    // 功能描述: 初始化计算服务
    bool InitService(void);
    // 功能描述: 启动计算服务
    void ServiceStart(void);
    // 功能描述: 停止计算服务
    void StopService(void);

private:
    // 功能描述: 初始化实时数据库连接
    bool connectRtdbDB(void);
    virtual void Run(void);

private:
	StartupServer * mStartSvr;
public:
    bool	mStopWait;
	GetDateWay					mGetDateWay;				//获取数据方式
    std::string m_strFactoryCode;                          // 当前处理的电厂编号
};

#endif

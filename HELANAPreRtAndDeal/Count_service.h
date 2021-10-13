/*******************************************************************************
* Copyright（C）,2018-2023,DTXY Tech .Co.Ltd;
* 文 件 名: count_service.h
* 文件描述: 中心处理服务，服务管理类
*  作  者 : 王凯，18569558896
* 创建日期: 2018-1-10 10:35:28
*******************************************************************************/

#ifndef __COUNT_SERVICE_H__
#define __COUNT_SERVICE_H__

#include <map>
#include <string>
#include "thread.h"
#include "PreRtProduce.h"

class CountService: public Thread
{
public:
    CountService(void);
    virtual ~CountService(void);
public:
    // 功能描述: 初始化中心处理服务
    bool InitService(void);
    // 功能描述: 启动中心处理服务
    void ServiceStart(void);
    // 功能描述: 停止中心处理服务
    void StopService(void);
    // 功能描述: 启动各电厂执行线程
    virtual void Run(void);

private:
    // 功能描述: 初始化告警环境
    bool InitRtaAlarm(void);
    // 功能描述: 初始化实时数据库连接
    bool ConnectRtdbDB(void);

    // 功能描述:  初始化电厂处理服务
    bool InitFactoryService(void);
    // 功能描述: 启动电厂处理服务
    void StartFactoryService(void);
    // 功能描述: 停止电厂处理服务
    void StopFactoryService(void);
    // 功能描述: 释放电厂处理服务
    void DestoryFactoryService(void);
private:
    std::map<std::string, PreRtProduce*> m_mapService;       // 电厂处理服务信息
};

#endif//__COUNT_SERVICE_H__

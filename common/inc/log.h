/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: log.h
* 文件描述: 日志组件操作接口
*  作  者 : 汤卫波，13730895608
* 创建日期: 2014-9-4 14:47:20
*******************************************************************************/

#ifndef __LOG_H__
#define __LOG_H__

#include "singleton.h"

#include <string>

class MutexLock;

#define MAX_LOG_FILE_SIZE      (5*1024*1024)

class Log
{
    DECLARE_SINGLETON_INIT(Log)
public:
    // 功能描述: 初始化日志信息
    bool InitLog(const std::string &strPath, const std::string &strMode, const bool &bWrite);
    // 功能描述：格式化指定的信息数据
    std::string StringFormat(const char* pszFormat, ...);
    // 功能描述: 写日志接口
    void WriteLog(const std::string &strLogMessage, const bool &bWrite = false);

    std::string getLogPath(){return m_strPath;}
private:
    std::string GetLogFileName(void);
    bool OpenFile(const std::string &strFname);
    long GetFileSize(void);
private:
    std::string m_strPath;
    std::string m_strMode;
    std::string m_strLogFile;   // 日志文件名
    bool m_bWrite;              // 日志开关
    FILE* m_pFile;              // 文件操作句柄
    MutexLock* m_pLock;
};

#endif//__LOG_H__

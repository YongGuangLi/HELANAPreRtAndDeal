/*******************************************************************************
* Copyright（C）,2014-2020,DTXY Tech .Co.Ltd;
* 文 件 名: scan_path_file.h
* 文件描述: 扫描目录文件，功能实现类
*  作  者 : 汤卫波，13739072308
* 创建日期: 2014-8-16 14:57:38
*******************************************************************************/

#ifndef __SCAN_PATH_FILE_H__
#define __SCAN_PATH_FILE_H__

#include <list>
#include <string>

#define MAX_SCAN_DEPTH        10      // 最大扫描深度

typedef enum ScanType                 // 扫描类型定义
{
    FILE_TYPE = 0,    // 文件
    DIRECTORY_TYPE,   // 目录
    UnKnown_Error     // 未知错误
}*P_SCAN_TYPE;

class ScanPathFile
{
public:
    /*
    * 功能描述：目录扫描条件构造函数
    * 输入参数：扫描类型，FILE_TYPE(文件类型)、DIRECTORY_TYPE(目录类型)
    * 输入参数：多级目录扫描层次，注：最大支持10级目录扫描
    */
    ScanPathFile(const ScanType nType = FILE_TYPE, const int &nDepth = MAX_SCAN_DEPTH);
    virtual ~ScanPathFile(void);
public:
    /*
    * 功能描述：目录扫描执行函数
    * 输出参数：扫描的文件列表
    * 返回值：true(成功)、false(失败)
    */
    bool ScanFile(const std::string &strScanPath, std::list<std::string> &lstFile);
private:
    // 功能描述：判断是否为目录
    bool IsDirectory(const std::string &strDirectory);
    // 功能描述：执行文件扫描
    bool DoRunScanFile(std::list<std::string> &lstFile);
private:
    int m_nDepth;                     // 扫描深度
    ScanType m_enType;                // 扫描类型
    std::string m_strScanPath;        // 扫描文件目录
};

#endif//__SCAN_PATH_FILE_H__

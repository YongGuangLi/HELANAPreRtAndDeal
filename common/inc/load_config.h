/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: load_config.h
* 文件描述: 配制文件加载功能类
*  作  者 : 汤卫波，13730895608
* 创建日期: 2014-9-4 13:37:55
*******************************************************************************/

#ifndef __LOAD_CONFIG_H__
#define __LOAD_CONFIG_H__

#include <map>
#include <list>
#include <string>

class LoadConfig
{
public:
    LoadConfig(void);
    virtual ~LoadConfig(void);
public:
    /* 
    * 功能描述: 解析加载配制文件数据信息
    * 输入参数: 配制文件名
    * 输出参数: 无
    * 返 回 值: 成功返回true，失败返回false
    */
    bool ParseConfig(const std::string &strCfgFile);
    /* 
    * 功能描述: 获取指定的配制数据信息
    * 输入参数: 配制项名称
    * 输入参数: 配制键值名称
    * 输出参数: 无
    * 返 回 值: 成功返回配制信息，失败返回空字符串
    */
    std::string GetValueByKey(const std::string &strConfig, const std::string &strKey);
private:
    // 功能描述: 加载配制文件信息行数据
    bool LoadConfigFile(const std::string &strCfgFile);
    // 功能描述: 解析配制内存数据信息
    bool ParseConfigMemory(void);
private:
    std::map<std::string, std::map<std::string, std::string> > m_mapConfig;     // 配制信息
    std::list<std::string> m_lstFileDB;                 // 配制文件信息行

    std::string m_strConfig;                            // 当前配制项数据信息
    std::map<std::string, std::string> m_mapConfigDB;   // 当前配制项配制数据
};

#endif//__LOAD_CONFIG_H__

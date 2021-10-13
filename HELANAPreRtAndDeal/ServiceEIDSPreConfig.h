/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名:  ServiceEIDSPreConfig.cpp
* 文件描述: 耗差性能计算配置文件管理类
*  作  者 : 林晓雨，18942552977
* 创建日期: 2015-05-12 16:03:33
*******************************************************************************/

#ifndef __SERVICEHCXNJSCONFIG_H__
#define __SERVICEHCXNJSCONFIG_H__


#include "singleton.h"

#define EIDS_CONFIG_FILE               ("eids_service_preValue_config.cfg")
#define RTDB_CONFIG_FILE                ("rtdb.ini")
#define COUNT_FACTORY_PATH_KEY          "FactoryPath_%s"

#define BASE_CONFIG								"Base"
#define BASE_MODE_NAME_KEY						"ModeName"
#define BASE_MODE_NAME_DEFAULT_VALUE			"HELANAPreRtAndDeal" 

#define ORACLE_CONFIG							"RSDB"
#define ORACLE_SESSION_NAME_KEY					"SessionName"
#define ORACLE_USER_NAME_KEY					"UserName"
#define ORACLE_PASSWD_KEY						"PassWD"
#define IP										"Ip" 
#define PORT									 "Port"
#define ORACLE_TYPE							    "RsdbType"
#define ORACLE_TYPE_DEFAULT_VALUE               "ORACLE"
#define ORACLE_SESSION_NAME_DEFAULT_VALUE		"ORCL190"
#define ORACLE_USER_NAME_DEFAULT_VALUE          "ECD"
#define ORACLE_PASSWD_DEFAULT_VALUE             "ECD"

#define LOG_CONFIG								"Log"
#define LOG_PATH_KEY							"Path"
#define LOG_IS_SHOW								"IsShow"
#define LOG_PATH_DEFAULT_VALUE					"D:/log"

#define EIDS_CONFIG							    "EIDSPreValue"
#define EIDS_SERVICE_CAL_CYC					"ServiceCalCyc"
#define XSDLIMIT								"XsdLimit"

#define SERVICE_CAL_CYC_DEFVALUE			"60"	//秒  计算周期

#define COUNT_CONFIG        "COUNT"
#define GET_HISNUM        "GetHisNum"
#define GET_HISTORTDEV     "GetHisToRtDevMin"
#define	DATA_BASE_IS_LONG_NAME_KEY				"Is_Long_Name"
#define	DATA_BASE_SYS_TYPE			"SysType"
#define COUNT_MODE_NAME_KEY         "ModeName"
#define COUNT_WRITE_CYC_KEY         "WriteCyc"
#define COUNT_RTDB_HEAD_KEY         "RtdbDevi"
#define COUNT_FILTER_HEAD_KEY       "FilterHead"
#define COUNT_FACTORY_PATH_KEY      "FactoryPath_%s"
#define COUNT_FACTORY_SENT_PATH_TOTAL "FactorySentPathTotal_%s"
#define COUNT_FACTORY_SENT_PATH		"FactorySentPath%d_%s"
#define COUNT_FACTORY_DTAE_WAY      "GetDateWay_%s"
#define COUNT_FACTORY_TOTAL_KEY     "FactoryTotal"
#define COUNT_FACTORY_CODE_KEY      "FactoryCode%d"
#define COUNT_WRITE_CYC_DEFAULT_VALUE       3
#define COUNT_MODE_NAME_DEFAULT_VALUE       "count_data"
#define COUNT_RTDB_HEAD_DEFAULT_VALUE       "DW.GX."
#define COUNT_FILTER_HEAD_DEFAULT_VALUE     "MH"




#define BUFF_CONFIG         "BUFF"
#define BUFF_FILE_TYPE_KEY          "FileType"
#define BUFF_DATA_TYPE_KEY          "DataType"

#define SENTBUFF_FILE_TYPE_KEY          "SentFileType"
#define SENTBUFF_DATA_TYPE_KEY          "SentDataType"
#define BUFF_FILE_TYPE_DEFAULT_VALUE         3
#define BUFF_DATA_TYPE_DEFAULT_VALUE		 1

#include <string>

class LoadConfig;

class ServiceEIDSPreConfig
{
    DECLARE_SINGLETON_INIT(ServiceEIDSPreConfig)
    public:
        // 功能描述：初始化公共配制信息
        bool initConfig(const std::string &strFname);
public:
    // 功能描述: 获取OCI连接会话名称
    std::string getOciSessionName(void);
    // 功能描述: 获取OCI连接用户名
    std::string getOciUserName(void);
    // 功能描述: 获取OCI连接密码
    std::string getOciPassWD(void);
    // 功能描述: 获取数据库类型
    std::string getRsdbType(void);
    std::string getRsdbIp(void);
    std::string getRsdbPort(void);
public:
    // 功能描述：获取日志路径
    std::string getLogPath(void);

    // 功能描述: 获取日志开关
    bool isShowLog(void);

    std::string getModeName(void);

    // 功能描述: 获取服务计算周期
    int getServiceCalCycSec();

    //功能描述: 获取服务计算故障定位匹配度为零的限值
    int getXsdLimit(void);

    int getRtdbIsLongNameType(void) const;

    std::string  GetRtdbHead(void);

    // 功能描述: 获取处理的电厂个数
    int GetFactoryTotal(void);

    int  GetSysType(void);

    //功能描述: 获取电厂历史数据补算最长时长
    int GetHisNum(void);

    //电厂追加补算切换到实时计算间隔时间 单位：分钟
    int GetHisToRtDev(void);

    //获取数据方式 1：实时数据库 2 文件
    std::string  GetFactoryDateWayByCode(const std::string &strFactoryCode);

    // 功能描述: 获取指定电厂序号的电厂名称
    std::string GetFactoryIndexByIndex(const int &nFactoryIndex);

    // 功能描述: 获取数据存放路径
    std::string GetFactoryPathByCode(const std::string &strFactoryCode);

    int GetFactorySentTotal(const std::string &strFactoryCode);

    // 功能描述: 获取数据存放路径
    std::string GetFactorySentPathByCode(const std::string &strFactoryCode,const int &num);

    // 功能描述: 获取Buff文件类型
    int GetBuffFileType(void);

    // 功能描述: 获取Buff文件存储类型
    int GetBuffDataType(void);

    // 功能描述: 发送Buff文件类型
    int GetSentBuffFileType(void);

    // 功能描述: 发送Buff文件存储类型
    int GetSentBuffDataType(void);
private:
    LoadConfig* m_pConfigOpt;           // 配制文件操作对象
public:
    int  m_sysType;
};

#endif//__SERVICEHCXNJSCONFIG_H__

/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: ServiceEIDSPreConfig.cpp
* 文件描述: 诊断期望值计算配置文件管理类
*  作  者 : %王凯%，158
* 创建日期: 2016-1-12 10:23:37
*******************************************************************************/
#include "load_config.h"
#include "ServiceEIDSPreConfig.h"
#include "public_function_library.h"
#include "ErrorDef.h"

IMPLEMENT_SINGLETON(ServiceEIDSPreConfig)

ServiceEIDSPreConfig::ServiceEIDSPreConfig(void)
    : m_pConfigOpt(NULL)
{
    m_pConfigOpt = new LoadConfig();
}

ServiceEIDSPreConfig::~ServiceEIDSPreConfig(void)
{
    if (NULL != m_pConfigOpt)
    {
        delete m_pConfigOpt;
        m_pConfigOpt = NULL;
    }
}

bool ServiceEIDSPreConfig::initConfig(const std::string &strFname)
{
    if (!m_pConfigOpt->ParseConfig(strFname))
    {
        return false;
    }
    return true;
}


std::string ServiceEIDSPreConfig::getOciSessionName(void)
{
    std::string strSessionName = m_pConfigOpt->GetValueByKey(ORACLE_CONFIG, ORACLE_SESSION_NAME_KEY);
    if (strSessionName.empty())
    {
        return ORACLE_SESSION_NAME_DEFAULT_VALUE;
    }
    return strSessionName;
}

std::string ServiceEIDSPreConfig::getOciUserName(void)
{
    std::string strUserName = m_pConfigOpt->GetValueByKey(ORACLE_CONFIG, ORACLE_USER_NAME_KEY);
    if (strUserName.empty())
    {
        return ORACLE_USER_NAME_DEFAULT_VALUE;
    }
    return strUserName;
}

std::string ServiceEIDSPreConfig::getOciPassWD(void)
{
    std::string strPassWD = m_pConfigOpt->GetValueByKey(ORACLE_CONFIG, ORACLE_PASSWD_KEY);
    if (strPassWD.empty())
    {
        return ORACLE_PASSWD_DEFAULT_VALUE;
    }
    return strPassWD;
}
std::string ServiceEIDSPreConfig::getRsdbType(void)
{
    std::string strType = m_pConfigOpt->GetValueByKey(ORACLE_CONFIG, ORACLE_TYPE);
    if (strType.empty())
    {
        return ORACLE_TYPE_DEFAULT_VALUE;
    }
    return strType;
}
std::string ServiceEIDSPreConfig::getRsdbIp(void)
{
    std::string strReturn = m_pConfigOpt->GetValueByKey(ORACLE_CONFIG, IP);
    return strReturn;
}
std::string ServiceEIDSPreConfig::getRsdbPort(void)
{
    std::string strReturn = m_pConfigOpt->GetValueByKey(ORACLE_CONFIG, PORT);

    return strReturn;
}
std::string ServiceEIDSPreConfig::getLogPath(void)
{
    std::string strPath = m_pConfigOpt->GetValueByKey(LOG_CONFIG, LOG_PATH_KEY);

    return strPath;
}

bool ServiceEIDSPreConfig::isShowLog(void)
{
    std::string strIsEnable = m_pConfigOpt->GetValueByKey(LOG_CONFIG, LOG_IS_SHOW);
    if ("1" != strIsEnable)
        return false;

    return true;
}


std::string ServiceEIDSPreConfig::getModeName(void)
{
    std::string strModeName = m_pConfigOpt->GetValueByKey(BASE_CONFIG, BASE_MODE_NAME_KEY);
    if (strModeName.empty())
        return BASE_MODE_NAME_DEFAULT_VALUE;

    return strModeName;
}

int ServiceEIDSPreConfig::getServiceCalCycSec()
{
    std::string str = m_pConfigOpt->GetValueByKey(EIDS_CONFIG, EIDS_SERVICE_CAL_CYC);
    if (str.empty()) str = SERVICE_CAL_CYC_DEFVALUE;
    return atol(str.c_str());
}

int ServiceEIDSPreConfig::getXsdLimit(void)
{
    std::string xsdLimit = m_pConfigOpt->GetValueByKey(EIDS_CONFIG, XSDLIMIT);
    if (xsdLimit.empty()) xsdLimit = SERVICE_CAL_CYC_DEFVALUE;
    return atol(xsdLimit.c_str());

}

int ServiceEIDSPreConfig::getRtdbIsLongNameType(void) const
{
    std::string strValue = m_pConfigOpt->GetValueByKey(COUNT_CONFIG, DATA_BASE_IS_LONG_NAME_KEY);
    if(strValue.empty())
    {
        return 0;
    }
    return atoi(strValue.c_str());
}

std::string ServiceEIDSPreConfig::GetRtdbHead(void)
{
    std::string strRtdbHead = m_pConfigOpt->GetValueByKey(COUNT_CONFIG, COUNT_RTDB_HEAD_KEY);
    if (strRtdbHead.empty())
    {
        return COUNT_RTDB_HEAD_DEFAULT_VALUE;
    }
    return strRtdbHead;
}

int ServiceEIDSPreConfig::GetFactoryTotal(void)
{
    std::string strFactoryTotal = m_pConfigOpt->GetValueByKey(COUNT_CONFIG, COUNT_FACTORY_TOTAL_KEY);
    if (strFactoryTotal.empty())
    {
        m_sysType = 0;
        return 0;
    }
    m_sysType = atoi(strFactoryTotal.c_str());
    return atoi(strFactoryTotal.c_str());
}
int ServiceEIDSPreConfig::GetSysType(void)
{
    std::string strFactoryTotal = m_pConfigOpt->GetValueByKey(COUNT_CONFIG, DATA_BASE_SYS_TYPE);
    if (strFactoryTotal.empty())
    {
        return 1;
    }
    return atoi(strFactoryTotal.c_str());
}
int ServiceEIDSPreConfig::GetHisNum(void)
{
    std::string strNum = m_pConfigOpt->GetValueByKey(COUNT_CONFIG, GET_HISNUM);
    if (strNum.empty())
    {
        return 6;
    }
    return atoi(strNum.c_str());
}

int ServiceEIDSPreConfig::GetHisToRtDev(void)
{
    std::string strNum = m_pConfigOpt->GetValueByKey(COUNT_CONFIG, GET_HISTORTDEV);
    if (strNum.empty())
    {
        return 5;
    }
    return atoi(strNum.c_str());
}
std::string ServiceEIDSPreConfig::GetFactoryIndexByIndex(const int &nFactoryIndex)
{
    std::string strKey = PubOpt::StringOpt::StringFormat(COUNT_FACTORY_CODE_KEY, nFactoryIndex);
    std::string strFactoryCode = m_pConfigOpt->GetValueByKey(COUNT_CONFIG, strKey);
    if (strFactoryCode.empty())
    {
        return std::string();
    }
    return strFactoryCode;
}

std::string ServiceEIDSPreConfig::GetFactoryDateWayByCode(const std::string &strFactoryCode)
{
    std::string strKey = PubOpt::StringOpt::StringFormat(COUNT_FACTORY_DTAE_WAY,
                                                         strFactoryCode.c_str());
    std::string strWay = m_pConfigOpt->GetValueByKey(COUNT_CONFIG, strKey);
    if (strWay.empty())
    {
        //return std::string();
        return "1";
    }
    return strWay;
}

std::string ServiceEIDSPreConfig::GetFactoryPathByCode(const std::string &strFactoryCode)
{
    std::string strKey = PubOpt::StringOpt::StringFormat(COUNT_FACTORY_PATH_KEY,
                                                         strFactoryCode.c_str());
    std::string strPath = m_pConfigOpt->GetValueByKey(COUNT_CONFIG, strKey);
    if (strPath.empty())
    {
        return std::string();
    }
    return strPath;
}
int ServiceEIDSPreConfig::GetFactorySentTotal(const std::string &strFactoryCode)
{
    std::string strKey = PubOpt::StringOpt::StringFormat(COUNT_FACTORY_SENT_PATH_TOTAL,
                                                         strFactoryCode.c_str());

    std::string strFactoryTotal = m_pConfigOpt->GetValueByKey(COUNT_CONFIG, strKey);
    if (strFactoryTotal.empty())
    {
        return 0;
    }
    return atoi(strFactoryTotal.c_str());
}
std::string ServiceEIDSPreConfig::GetFactorySentPathByCode(const std::string &strFactoryCode,const int &num)
{	
    std::string strKey = PubOpt::StringOpt::StringFormat(COUNT_FACTORY_SENT_PATH, num,
                                                         strFactoryCode.c_str());
    std::string strPath = m_pConfigOpt->GetValueByKey(COUNT_CONFIG, strKey);
    if (strPath.empty())
    {
        return std::string();
    }
    return strPath;
}


int ServiceEIDSPreConfig::GetBuffFileType(void)
{
    std::string strFileType = m_pConfigOpt->GetValueByKey(BUFF_CONFIG, BUFF_FILE_TYPE_KEY);
    if (strFileType.empty())
    {
        return BUFF_FILE_TYPE_DEFAULT_VALUE;
    }
    return atoi(strFileType.c_str());
}

int ServiceEIDSPreConfig::GetBuffDataType(void)
{
    std::string strSaveType = m_pConfigOpt->GetValueByKey(BUFF_CONFIG, BUFF_DATA_TYPE_KEY);
    if (strSaveType.empty())
    {
        return BUFF_DATA_TYPE_DEFAULT_VALUE;
    }
    return atoi(strSaveType.c_str());
}
int ServiceEIDSPreConfig::GetSentBuffFileType(void)
{
    std::string strFileType = m_pConfigOpt->GetValueByKey(BUFF_CONFIG, SENTBUFF_FILE_TYPE_KEY);
    if (strFileType.empty())
    {
        return BUFF_FILE_TYPE_DEFAULT_VALUE;
    }
    return atoi(strFileType.c_str());
}

int ServiceEIDSPreConfig::GetSentBuffDataType(void)
{
    std::string strSaveType = m_pConfigOpt->GetValueByKey(BUFF_CONFIG, SENTBUFF_DATA_TYPE_KEY);
    if (strSaveType.empty())
    {
        return BUFF_DATA_TYPE_DEFAULT_VALUE;
    }
    return atoi(strSaveType.c_str());
}
//
//std::string
//ServiceEIDSPreConfig::getMemCachedAddr()
//{
//	return m_pConfigOpt->GetValueByKey(MEM_CONFIG, MEM_ADDR);
//}
//
//int
//ServiceEIDSPreConfig::getMemCachedPort()
//{
//	std::string str = m_pConfigOpt->GetValueByKey(MEM_CONFIG, MEM_PORT);
//	if (str.empty()) return 11212;
//	return atol(str.c_str());
//}
//

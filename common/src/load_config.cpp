#include "load_config.h"
#include "public_function_library.h"

#include <stdio.h>

LoadConfig::LoadConfig(void)
{
    // empty
}

LoadConfig::~LoadConfig(void)
{
    // empty
}

bool LoadConfig::ParseConfig(const std::string &strCfgFile)
{
    if (!LoadConfigFile(strCfgFile))
    {
        return false;
    }
    if (!ParseConfigMemory())
    {
        return false;
    }
    return true;
}

std::string LoadConfig::GetValueByKey(const std::string &strConfig, const std::string &strKey)
{
    std::map<std::string, std::map<std::string, std::string> >::iterator 
        iter = m_mapConfig.find(strConfig);
    if (iter == m_mapConfig.end())
    {
        return std::string();
    }
    std::map<std::string, std::string>::iterator iter_key = iter->second.find(strKey);
    if (iter_key == iter->second.end())
    {
        return std::string();
    }
    return iter_key->second;
}

bool LoadConfig::LoadConfigFile(const std::string &strCfgFile)
{
    m_lstFileDB.clear();
#ifdef WIN32
    FILE* pFile = NULL;
    fopen_s(&pFile, strCfgFile.c_str(), "rb");
#else
    FILE* pFile = fopen(strCfgFile.c_str(), "rb");
#endif
    if (NULL == pFile)
    {
        return false;
    }
    char szReadBuff[1024];
    while (NULL != fgets(szReadBuff, 1024, pFile))
    {
        std::string strLine = PubOpt::StringOpt::StringReplace(szReadBuff, "\t", "    ");
        size_t siFind = strLine.find("#");
        if (std::string::npos != siFind)
        {
            strLine = strLine.substr(0, siFind);
        }
        if (std::string::npos == strLine.find_first_not_of(' '))
        {
            continue;
        }
        strLine = strLine.substr(strLine.find_first_not_of(' '), 
            strLine.find_last_not_of(' ')-strLine.find_first_not_of(' ')+1);
        if (std::string::npos != strLine.rfind('\r'))
        {
            strLine = strLine.substr(0, strLine.rfind('\r'));
        }
        if (std::string::npos != strLine.rfind('\n'))
        {
            strLine = strLine.substr(0, strLine.rfind('\n'));
        }
        if (!strLine.empty())
        {
            m_lstFileDB.push_back(strLine);
        }
    }
    fclose(pFile);
    return true;
}

bool LoadConfig::ParseConfigMemory(void)
{
    std::list<std::string>::iterator iter = m_lstFileDB.begin();
    for (; iter != m_lstFileDB.end(); ++iter)
    {
        if (std::string::npos != iter->find("[") 
            && std::string::npos != iter->rfind("]")
            &&iter->find("[") < iter->rfind("]"))
        {
            if (!m_mapConfigDB.empty() 
                && !m_strConfig.empty())
            {
                m_mapConfig[m_strConfig] = m_mapConfigDB;
            }
            m_strConfig = iter->substr(iter->find("[")+1, iter->rfind("]")-1);
            if (m_mapConfig.find(m_strConfig) != m_mapConfig.end())
            {
                return false;
            }
            m_mapConfigDB.clear();
        } 
		else if (iter->find("=") != std::string::npos)
		{
            std::string strKey = iter->substr(0, iter->find("="));
            if (std::string::npos != strKey.find_first_not_of(' '))
            {
                strKey = strKey.substr(strKey.find_first_not_of(' '), 
                    strKey.find_last_not_of(' ')-strKey.find_first_not_of(' ')+1);
            } else {
                return false;
            }
            std::string strValue = iter->substr(iter->find("=") + 1);
            if (std::string::npos != strValue.find_first_not_of(' '))
            {
                strValue = strValue.substr(strValue.find_first_not_of(' '), 
                    strValue.find_last_not_of(' ')-strValue.find_first_not_of(' ')+1);
            } else {
                strValue.clear();
            }
            m_mapConfigDB[strKey] = strValue;
        } 
		else
        {
            return false;
        }
    }
    if (!m_strConfig.empty() && !m_mapConfigDB.empty())
    {
        m_mapConfig[m_strConfig] = m_mapConfigDB;
    }
    return true;
}

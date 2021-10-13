
#include "log.h"
#include "mutex.h"
#include "public_function_library.h"

#include <stdio.h>
#include <stdarg.h>

IMPLEMENT_SINGLETON(Log)

Log::Log(void)
: m_pFile(NULL)
, m_pLock(NULL)
{
    m_pLock = new MutexLock();
}

Log::~Log(void)
{
    fclose(m_pFile);
	m_pFile = NULL;
    if (NULL != m_pLock)
    {
        delete m_pLock;
        m_pLock = NULL;
    }
}

bool Log::InitLog(const std::string &strPath, const std::string &strMode, const bool &bWrite)
{
    m_strPath = strPath;
    m_strMode = strMode;

    if (!PubOpt::FileOpt::IsFindFile(m_strPath))
    {
        PubOpt::FileOpt::NewDirect(m_strPath);
    }

    m_strLogFile = GetLogFileName();

    m_bWrite = bWrite;
    return OpenFile(m_strLogFile);
}

std::string Log::GetLogFileName(void)
{
    std::string strTime = PubOpt::SystemOpt::GetSystemDateTime();
    strTime = PubOpt::StringOpt::StringReplace(strTime, "-", "");
    strTime = PubOpt::StringOpt::StringReplace(strTime, ":", "");
    strTime = PubOpt::StringOpt::StringReplace(strTime, " ", "");
    m_strLogFile = m_strPath + m_strMode + "_" + strTime + ".log";
    return m_strLogFile;
}

bool Log::OpenFile(const std::string &strFname)
{
    if (NULL != m_pFile)
    {
        fclose(m_pFile);
		m_pFile = NULL;
    }
#ifdef WIN32
    fopen_s(&m_pFile, m_strLogFile.c_str(), "a");
#else
    m_pFile = fopen(m_strLogFile.c_str(), "a");
#endif
    if (NULL == m_pFile)
    {
        return false;
    }
    return true;
}

std::string Log::StringFormat(const char* pszFormat, ...)
{
    std::string strRet;
    if (NULL == pszFormat)
    {
        return strRet;
    }
    char szTmp[1024] = {0};
    va_list val;
    va_start(val, pszFormat);
#ifdef WIN32
    if (0 > vsnprintf_s(szTmp, 1024, 1024, pszFormat, val))
#else
    if (0 > vsnprintf(szTmp, 1024, pszFormat, val))
#endif
    {
        return strRet;
    }
    va_end(val);
    strRet = static_cast<std::string>(szTmp);
    return strRet;
}

void Log::WriteLog(const std::string &strLogMessage, const bool &bWrite)
{
    AutoLock oAutoLock(*m_pLock);
	OpenFile(m_strLogFile);
    if (strLogMessage.empty())
    {
        return ;
    }
    if (GetFileSize() >= MAX_LOG_FILE_SIZE)
    {
        m_strLogFile = GetLogFileName();
        OpenFile(m_strLogFile);
    }
    std::string strLog = PubOpt::SystemOpt::GetSystemDateTime() + " " + strLogMessage + "\n";
    if (m_bWrite)
    {
        fwrite(strLog.c_str(), strLog.size(), 1, m_pFile);
        fflush(m_pFile);
		fclose(m_pFile);
		m_pFile = NULL;
        return;
    }
    if (bWrite)
    {
        fwrite(strLog.c_str(), strLog.size(), 1, m_pFile);
        fflush(m_pFile);
		fclose(m_pFile);
		m_pFile = NULL;
    }
}

long Log::GetFileSize(void)
{
    if (NULL == m_pFile)
    {
        return 0;
    }
    if (-1 == fseek(m_pFile, 0L, SEEK_END))
    {
        return 0;
    }
    long lFileSize = ftell(m_pFile);
    rewind(m_pFile);
    return lFileSize;
}

#include "public_function_library.h"

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <vector>
#ifdef WIN32
#include <io.h>
#include <direct.h>
#include <windows.h>
#else
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#endif

#ifdef WIN32
#pragma comment(lib, "ws2_32.lib")
#endif

namespace PubOpt
{
    namespace TypeOpt
    {
        std::string UInt32ToChar4(const unsigned int &ulInt32)
        {
            unsigned int ulNum = htonl(ulInt32);
            char szMsg[4] = {0};
            memcpy(szMsg, (char*)&ulNum, sizeof(ulNum));
            std::string strRet(szMsg, sizeof(ulNum));
            return strRet;
        }

        unsigned int Char4ToUInt32(const std::string &strUInt32)
        {
            unsigned int ulNum = 0;
            memcpy(&ulNum, (unsigned int*)strUInt32.c_str(), sizeof(unsigned int));
            ulNum = ntohl(ulNum);
            return ulNum;
        }

		double CharPointerConvert2Number(const char * t)
		{
			if (strlen(t) == 0)
			{
				return 0;
			}
			double result;
			std::stringstream stream;
			stream << t;
			stream >> result;
			return result;
		}
    }

    namespace StringOpt
    {
        std::string LeftTrim(const std::string &strMsg)
        {
            std::string strRet = strMsg;
            size_t siFind = strRet.find_first_not_of(" ");
            if (std::string::npos == siFind)
            {
                strRet = std::string();
            } else
            {
                strRet = strRet.substr(siFind);
            }
            return strRet;
        }

        std::string RightTrim(const std::string &strMsg)
        {
            std::string strRet = strMsg;
            size_t siFind  = strRet.find_last_not_of(" ");
            if (std::string::npos == siFind)
            {
                strRet = std::string();
            } else
            {
                strRet = strRet.substr(0, siFind + 1);
            }
            return strRet;
        }

        std::string TrimString(const std::string &strMsg)
        {
            return RightTrim(LeftTrim(strMsg));
        }

        std::string StringUpper(const std::string &strMsg)
        {
            if (strMsg.empty())
            {
                return std::string();
            }
            std::string strRet;
            std::string::const_iterator iter = strMsg.begin();
            for (; iter != strMsg.end(); ++iter)
            {
                strRet += toupper(*iter);
            }
            return strRet;
        }

        std::string StringLower(const std::string &strMsg)
        {
            if (strMsg.empty())
            {
                return std::string();
            }
            std::string strRet;
            std::string::const_iterator iter = strMsg.begin();
            for (; iter != strMsg.end(); ++iter)
            {
                strRet += tolower(*iter);
            }
            return strRet;
        }

        std::string StringFormat(const char* pszFormat, ...)
        {
            std::string strRet;
            if (NULL == pszFormat)
            {
                return strRet;
            }
            //char szTmp[1024] = {0};
			char szTmp[2048] = {0};
            va_list val;
            va_start(val, pszFormat);
#ifdef WIN32
            //if (0 > vsnprintf_s(szTmp, 1024, 1024, pszFormat, val))
			if (0 > vsnprintf_s(szTmp, 2048, 2048, pszFormat, val))
#else
            //if (0 > vsnprintf(szTmp, 1024, pszFormat, val))
			if (0 > vsnprintf(szTmp, 2048, pszFormat, val))
#endif
            {
                return strRet;
            }
            va_end(val);
            strRet = static_cast<std::string>(szTmp);
            return strRet;
        }

        bool StringSplit(const std::string &strSrc, 
            std::list<std::string> &lstRet, 
            const std::string &strSplit)
        {
            if (strSplit.empty())
            {
                return false;
            }
            std::string strSrcBak = strSrc;
            size_t siFind = 0;
            while(!strSrcBak.empty())
            {
                siFind = strSrcBak.find(strSplit);
                if (std::string::npos == siFind)
                {
                    lstRet.push_back(strSrcBak);
                    strSrcBak.clear();
                    continue;
                }
                lstRet.push_back(strSrcBak.substr(0, siFind));
                strSrcBak = strSrcBak.substr(siFind + strSplit.size());
            }
            return true;
        }

        std::string StringSplit(const std::string &strSrc, 
            const int &nBit, 
            const std::string &strSplit)
        {
            if (strSplit.empty())
            {
                return false;
            }
            std::string strSrcBak = strSrc;
            size_t siFind = 0;
            std::vector<std::string> lstRet;
            while(!strSrcBak.empty())
            {
                siFind = strSrcBak.find(strSplit);
                if (std::string::npos == siFind)
                {
                    lstRet.push_back(strSrcBak);
                    strSrcBak.clear();
                    continue;
                }
                lstRet.push_back(strSrcBak.substr(0, siFind));
                strSrcBak = strSrcBak.substr(siFind + strSplit.size());
            }
            if (static_cast<int>(lstRet.size()) <= nBit)
            {
                return std::string();
            }
            return lstRet[nBit];
        }

		bool StringSplit(const std::string &strSrc, std::vector<std::string> &lstRet, const std::string &strSplit)
		{
			if (strSplit.empty())
			{
				return false;
			}
			std::string strSrcBak = strSrc;
			size_t siFind = 0;
			while(!strSrcBak.empty())
			{
				siFind = strSrcBak.find(strSplit);
				if (std::string::npos == siFind)
				{
					lstRet.push_back(strSrcBak);
					strSrcBak.clear();
					continue;
				}
				lstRet.push_back(strSrcBak.substr(0, siFind));
				strSrcBak = strSrcBak.substr(siFind + strSplit.size());
			}
			return true;
		}

        std::string StringReplace(const std::string &strSrc, 
            const std::string &strRepSrc, const std::string &strRepSnk)
        {
            std::string strRet = strSrc;
            if (strRet.empty() || strRepSrc.empty())
            {
                return strRet;
            }
            size_t siFind = strRet.find(strRepSrc);
            if (std::string::npos == siFind)
            {
                return strRet;
            }
            strRet = strRet.replace(siFind, strRepSrc.size(), strRepSnk.c_str());
            return StringReplace(strRet, strRepSrc, strRepSnk);
        }
    }

    namespace FileOpt
    {
        bool IsFindFile(const std::string &strFileAll)
        {
#ifdef WIN32
            if (_access(strFileAll.c_str(), 0) != 0) return false;
#else
            if (access(strFileAll.c_str(), F_OK) != 0) return false;
#endif
            return true;
        }

        bool RemoveFile(const std::string &strFname)
        {
            if (::remove(strFname.c_str()) != 0)
            {
                return false;
            }
            return true;
        }

        bool NewDirect(const std::string &strPath)
        {
            int iLen = strPath.length(); 
            char* pszDir = strdup(strPath.c_str());

            for (int i = 0;i < iLen;i ++)
            {
                if (pszDir[i] == '\\' || pszDir[i] == '/')
                { 
					if (i == 0) continue;
                    pszDir[i] = '\0';
                    //如果不存在,创建
                    bool ret = IsFindFile(pszDir);
                    if (!ret)
                    { 
#ifdef WIN32
                        if (_mkdir(pszDir) != 0)
                        {
                            free(pszDir);
                            return false;
                        }
#else
                        if (mkdir(pszDir, 0755) != 0)
                        {
                            free(pszDir);
                            return false;
                        }
#endif
                    } 
                    //支持linux,将所有\换成/  
                    pszDir[i] = '/';  
                }
            }

#ifdef WIN32
            if (_mkdir(pszDir) != 0)
            {
                free(pszDir); 
                return false;	
            }
#else
            if (mkdir(pszDir, 0755) != 0)
            {
                free(pszDir); 
                return false;
            }
#endif
            free(pszDir); 
            return true;
        }

        std::string GetFileName(const std::string &strFileAll)
        {
            std::string strName = strFileAll;
            std::list<std::string> ltRet;
#ifdef _WIN32
            std::string strSplit("\\");
#else
            std::string strSplit("/");
#endif
            if (!StringOpt::StringSplit(strName, ltRet, strSplit))
            {
                return std::string();
            }

            if (ltRet.size() == 0)
            {
                return std::string();
            }

            size_t size = ltRet.size();
            if (size != 1)
            {
                return ltRet.back();
            }

            return strName;
        }


        std::string GetNameByFile(const std::string &strFname)
        {
            std::string strName = GetFileName(strFname);
            size_t siFind = strName.rfind(".");
            if (std::string::npos != siFind)
            {
                strName = strName.substr(0, siFind);
            }
            return strName;
        }

		std::string GetExeFileName(void)
		{
			std::string strPath;
		#ifdef WIN32
			char szPath[1024];
			GetModuleFileName(NULL, szPath, 1024);
			strPath = szPath;
		#else
			strPath = program_invocation_name;
		#endif
			return  GetFileName(strPath);
		}

        bool GetFileSize(const std::string &strFileName, int &nFileSize)
        {
            if (!IsFindFile(strFileName))
            {
                return false;
            }
#ifdef WIN32
            FILE* pFile = NULL;
            fopen_s(&pFile, strFileName.c_str(), "r");
#else
            FILE* pFile = fopen(strFileName.c_str(), "r");
#endif
            if (NULL == pFile)
            {
                return false;
            }
            if (-1 == fseek(pFile, 0L, SEEK_END))
            {
                return false;
            }
            nFileSize = ftell(pFile);
            fclose(pFile);
            return true;
        }
    }

    namespace SystemOpt
    {
        void SleepWait(const int &ulMilliTime)
        {
#ifdef WIN32 
            Sleep(ulMilliTime);
#else
            sleep(ulMilliTime/1000);
#endif
        }

#ifdef WIN32
        std::string GetSystemDateTime(void)
        {
            std::string strDataTime;
            SYSTEMTIME time;
            GetLocalTime(&time);
            strDataTime = StringOpt::StringFormat("%04d-%02d-%02d %02d:%02d:%02d.%03d", 
                time.wYear, time.wMonth, time.wDay, 
                time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
            return strDataTime;
        }
#else
        std::string GetSystemDateTime(void)
        {
            std::string strRet;
            struct timeval tv;
            int iRet = gettimeofday(&tv, NULL);
            if (0 != iRet)
            {
                return strRet;
            }
            struct tm* timeinfo = localtime(&tv.tv_sec);
            if (NULL == timeinfo)
            {
                return strRet;
            }
            strRet = StringOpt::StringFormat("%04d-%02d-%02d %02d:%02d:%02d.%03d", 
                timeinfo->tm_year + 1900, (timeinfo->tm_mon + 1) % 13, timeinfo->tm_mday, 
                timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, tv.tv_usec/1000);
            return strRet;
        }
#endif

        std::string GetSystemHostName(void)
        {
#ifdef WIN32
            WSADATA wsadata;
            WSAStartup(MAKEWORD(2, 2), &wsadata);
#endif
            char szHostName[256];
            if (0 != gethostname(szHostName, 256))
            {
                return std::string();
            }
#ifdef WIN32
            WSACleanup();
#endif
            std::string strHostName = static_cast<std::string>(szHostName);
            return strHostName;
        }
        
        int GetYear(const time_t & c_time)
        {
            int year;
            struct tm *timeinfo; 
            timeinfo = localtime(&c_time);
            year=timeinfo->tm_year + 1900;
            return year;
        }

        int GetMonth(const time_t & c_time)
        {
            int tm_mon;
            struct tm *timeinfo; 
            timeinfo = localtime(&c_time);
            tm_mon= timeinfo->tm_mon + 1;
            return tm_mon;
        }
        int GetDay(const time_t & c_time)
        {
            int tm_mday;
            struct tm *timeinfo; 
            timeinfo = localtime(&c_time);
            tm_mday= timeinfo->tm_mday;
            return tm_mday;
        }
        int GetHour(const time_t & c_time)
        {
            int tm_hour;
            struct tm *timeinfo; 
            timeinfo = localtime(&c_time);
            tm_hour= timeinfo->tm_hour;
            return tm_hour;
        }
        int GetMinute(const time_t & c_time)
        {
            int tm_min;
            struct tm *timeinfo; 
            timeinfo = localtime(&c_time);
            tm_min= timeinfo->tm_min + 1;
            return tm_min;
        }
		int GetSecond(const time_t & c_time)
		{
			int tm_min;
			struct tm *timeinfo; 
			timeinfo = localtime(&c_time);
			tm_min= timeinfo->tm_sec;
			return tm_min;
		}
        int GetDayOfWeek(const time_t & c_time)
        {
            int tm_wday;
            struct tm *timeinfo; 
            timeinfo = localtime(&c_time);
            tm_wday= timeinfo->tm_wday;
            return tm_wday;
        }

        time_t StrToDateTm(const std::string & time_string)
        {  
            struct tm tm1;  
            time_t time1;  
            std::string time_stringr;
            time_stringr = StringOpt::StringReplace(time_string,"/","-");
            int i = sscanf(time_stringr.c_str(), "%d-%d-%d %d:%d:%d" ,       
                &(tm1.tm_year),   
                &(tm1.tm_mon),   
                &(tm1.tm_mday),  
                &(tm1.tm_hour),  
                &(tm1.tm_min),  
                &(tm1.tm_sec));  

            tm1.tm_year -= 1900;  
            tm1.tm_mon = tm1.tm_mon-1;  
            tm1.tm_isdst = 0;  
            time1 = mktime(&tm1);  

            return time1;  
        }

        std::string DateTmToStr(const time_t & c_time)
        {
			int year, month, day, hour, minute, second;
            std::string strRet;
            //time_t tmp_time;
            struct tm *timeinfo; 
            //tmp_time=c_time;
            timeinfo = localtime(&c_time);  
            year = timeinfo->tm_year + 1900;  
            month = timeinfo->tm_mon+1;  
			day = timeinfo->tm_mday;
			hour = timeinfo->tm_hour;
			minute = timeinfo->tm_min;
			second = timeinfo->tm_sec;
            strRet = StringOpt::StringFormat("%04d-%02d-%02d %02d:%02d:%02d", 
                year, month, day, hour, minute, second);

            return strRet;
        }
		std::string DateTmToStr(const time_t & c_time,int itype)
		{
			std::string strRet;
			//time_t tmp_time;
			struct tm *timeinfo; 
			//tmp_time=c_time;
			timeinfo = localtime(&c_time);  
			timeinfo->tm_year = timeinfo->tm_year + 1900;  
			timeinfo->tm_mon = timeinfo->tm_mon;  
			if(0==itype)
				strRet = StringOpt::StringFormat("%04d-%02d-%02d %02d:%02d:%02d", 
				timeinfo->tm_year, (timeinfo->tm_mon + 1), timeinfo->tm_mday, 
				timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
			else
				strRet = StringOpt::StringFormat("%04d%02d%02d %02d:%02d:%02d", 
				timeinfo->tm_year, (timeinfo->tm_mon + 1), timeinfo->tm_mday, 
				timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
			return strRet;
		}
  
        double GetDevHour(std::string szCurrDate,std::string szFrontDate)
        {
            double ReValue=0;
            //time_t c_time1,c_time2;
            ReValue = static_cast<double>(StrToDateTm(szCurrDate)-StrToDateTm(szFrontDate))/3600;
            return ReValue;
        }

        std::string GetCurExePath(void)
        {
            std::string strPath;
#ifdef WIN32
            char szPath[1024];
            GetModuleFileName(NULL, szPath, 1024);
            strPath = szPath;
            strPath = strPath.substr(0, strPath.rfind("\\") + 1);
#else
            strPath = program_invocation_name;
            strPath = strPath.substr(0, strPath.rfind("/") + 1);
#endif
            return strPath;
        }
    }
}

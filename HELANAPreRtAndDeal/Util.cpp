﻿/*******************************************************************************
* Copyright（C）,2016-2020,DTXY Tech .Co.Ltd;
* 文 件 名: Util.cpp
* 文件描述: 基础函数类
*  作  者 : %王凯%，
* 创建日期: 2016-10-10 16:33:09
*******************************************************************************/

#include "Util.h"
#include "PreRtProduce.h"
#include "public_function_library.h"
#include "AlarmLog.h"
#include <time.h>
#include <algorithm>

//声名全局变量
extern int gOnStop;
namespace Util
{
	bool QtConnect(RsdbAdapter* pQtOpt,std::string strFactoryCode)
	{
		while(!QtConnectOnce(pQtOpt,strFactoryCode))
		{
			if (gOnStop) return false;
			PubOpt::SystemOpt::SleepWait(2000);
		}
		return true;
	}

	bool QtConnectOnce(RsdbAdapter* pQtOpt,std::string strFactoryCode)
	{
        if (pQtOpt->QtIsConnect())
            return true;

		std::string strConn,strSessionName,strUserName,strPasswd;
		std::string strError;
		DBServerInfo stServerInfo;
		stServerInfo.strSessionName = SINGLETON(ServiceEIDSPreConfig)->getOciSessionName();
		stServerInfo.strUserName = SINGLETON(ServiceEIDSPreConfig)->getOciUserName();
		stServerInfo.strPasswd = SINGLETON(ServiceEIDSPreConfig)->getOciPassWD();
		stServerInfo.strRsdbType = SINGLETON(ServiceEIDSPreConfig)->getRsdbType();
		stServerInfo.strIp = SINGLETON(ServiceEIDSPreConfig)->getRsdbIp();
		stServerInfo.iPort = CharPointerConvert2Number<int>(SINGLETON(ServiceEIDSPreConfig)->getRsdbPort().c_str());
		//strConn=stServerInfo.strUserName+"/"+stServerInfo.strPasswd+"@"+stServerInfo.strSessionName;
		//while(!pQtOpt->QtConnect(stServerInfo))
		if(!pQtOpt->QtConnect(stServerInfo))
		{
			strError = PubOpt::StringOpt::StringFormat(
				"Connect Oracle ERROR: %s", 
				pQtOpt->GetErrorMessage().c_str());
			Aos_Assert_S(strError.c_str());
			return false;
		}
		else
		{
			strError = PubOpt::StringOpt::StringFormat("Rsdb (QT) Connect Success factory:%s",strFactoryCode.c_str());
			Aos_WriteLog(strError.c_str());
		}
		
		return true;
	}

	bool RsdbIsConnect()
	{
		/*if (SINGLETON(RsdbAdapter)->QtIsConnect()) 
		{
			return true;
		}
		if (!RsdbConnect()) return false;*/
		return true;
	}


	bool RsdbConnect()
	{
		//std::string strConn,strSessionName,strUserName,strPasswd;
		//std::string strError;
		//DBServerInfo stServerInfo;
		//stServerInfo.strSessionName = SINGLETON(ServiceEIDSPreConfig)->getOciSessionName();
		//stServerInfo.strUserName = SINGLETON(ServiceEIDSPreConfig)->getOciUserName();
		//stServerInfo.strPasswd = SINGLETON(ServiceEIDSPreConfig)->getOciPassWD();
		//stServerInfo.strRsdbType = SINGLETON(ServiceEIDSPreConfig)->getRsdbType();
		//stServerInfo.strIp = SINGLETON(ServiceEIDSPreConfig)->getRsdbIp();
		//stServerInfo.iPort = CharPointerConvert2Number<int>(SINGLETON(ServiceEIDSPreConfig)->getRsdbPort().c_str());
		////strConn=stServerInfo.strUserName+"/"+stServerInfo.strPasswd+"@"+stServerInfo.strSessionName;
		//while(!SINGLETON(RsdbAdapter)->QtConnect(stServerInfo))
		//{
		//	strError = PubOpt::StringOpt::StringFormat("Connect RSDB ERROR: %s", 
		//		SINGLETON(RsdbAdapter)->GetErrorMessage().c_str());
		//	Aos_Assert_S(strError.c_str());
		//	//rdbConnectFaildAlarm(strError);
		//	PubOpt::SystemOpt::SleepWait(2000);
		//}

		////rdbConnectSuccessAlarm();
		//Aos_WriteLog("连接数据库成功！");
		return true;
	}

	bool connectRtdbDB()
	{
//		if (!SINGLETON(RtdbAdapter)->RtdbIsConnect())
//		{
//			/*if (!SINGLETON(RtdbAdapter)->RtdbConnect())
//			{
//				return false;
//			}*/
			
//			SINGLETON(RtdbAdapter)->RtdbDisConnect();//add by wk 2018-1-4
//			//std::string strFname = PubOpt::SystemOpt::GetCurExePath() + RTDB_CONFIG_FILE;
//			SINGLETON(RtdbAdapter)->RtdbInitial();
//			while(!SINGLETON(RtdbAdapter)->RtdbConnect())
//			{
//				PubOpt::SystemOpt::SleepWait(2000);
//			}
//		}
		return true;
	}
	
	bool StringSplit(const std::string &strSrc, 
		std::vector<std::string> &lstRet, 
		const std::string &strSplit,bool isCheckReap)
	{
		std::vector<std::string>::iterator iter;
		if (strSplit.empty())
		{
			return false;
		}
		std::string strSrcBak = strSrc;
		std::string strIn;
		size_t siFind = 0;
		while(!strSrcBak.empty())
		{
			siFind = strSrcBak.find(strSplit);
			if (std::string::npos == siFind)
			{   
			    //add by wk
			    if(strSrcBak.empty()) 
                {
                    lstRet.clear();
                    return false;
                }
			    //add by wk 
				if (isCheckReap)
				{
					iter = std::find(lstRet.begin(), lstRet.end(), strSrcBak);
					if(iter == lstRet.end())
						lstRet.push_back(strSrcBak);
				}
				else
					lstRet.push_back(strSrcBak);

				strSrcBak.clear();
				continue;
			}
			//add by wk
			strIn.clear();
			strIn=strSrcBak.substr(0, siFind);
			if(strIn.empty()) 
			{
			    lstRet.clear();
			    return false;
			}
			//end add
			if (isCheckReap)
			{
				iter = std::find(lstRet.begin(), lstRet.end(), strSrcBak.substr(0, siFind));
				if(iter == lstRet.end())
					lstRet.push_back(strSrcBak.substr(0, siFind));
			}
			else
				lstRet.push_back(strSrcBak.substr(0, siFind));
			strSrcBak = strSrcBak.substr(siFind + strSplit.size());
		}
		return true;
	}
	
	
	unsigned long getNowTime()
	{
		time_t nowtime = time(NULL);
		return nowtime;
	}

	bool getRtdbCurTimeToString(std::string &current_time)
	{
//		bool rslt = connectRtdbDB();
//		if (!rslt) return false;

//		long ltime;
//		if (!SINGLETON(RtdbAdapter)->RtdbGetCurrentTime(&ltime))
//		{
//			Aos_Assert_S("获取实时数据库当前时间失败");
//		}
//		current_time = PubOpt::SystemOpt::DateTmToStr(ltime,0);
		return true;
	}

	long getRtdbCurTimeToLong()
	{
		long ltime;
//		Aos_Assert_R(connectRtdbDB(), 0);
//		if (!SINGLETON(RtdbAdapter)->RtdbGetCurrentTime(&ltime))
//		{
//			Aos_Assert_S("获取实时数据库当前时间失败");
//			ltime = 0;
//		}
		return ltime;
	}


	/*std::string	 getSystemDirectory()
	{
		char strTemp[MAX_PATH];
		memset(strTemp, 0, MAX_PATH);
		GetSystemDirectory(strTemp, MAX_PATH); 
		std::string strPath = strTemp;
		if(strPath.substr(strPath.length()-1, 1) != "\\")   strPath = strPath + "\\";
		return strPath;
	}*/

	long convertIntMinute(const long &ltime)
	{
		long oneMin = 60;
		return ltime - (ltime % oneMin);
	}

	int getMinute(const time_t & c_time)
	{
		int tm_min;
		struct tm *timeinfo; 
		timeinfo = localtime(&c_time);
		tm_min= timeinfo->tm_min;
		return tm_min;
	}

	void UtilsanityCheck(const int flag, const std::string &strmsg)
	{	
		static long s_time = 0;
		if (flag == 1) s_time = Util::getNowTime();
		if (flag == 2)
			Aos_WriteLog(PubOpt::StringOpt::StringFormat(strmsg.c_str(), Util::getNowTime() - s_time).c_str());

	}
	bool JudgeIsExcept(double fExceptVal)
	{
		bool bExcept = true;
		std::string strTemp;
		strTemp= PubOpt::StringOpt::StringFormat("%f",fExceptVal);
		if (strcmp(strTemp.c_str(),"1.#QNAN0")==0||strcmp(strTemp.c_str(),"-1.#INF00")==0||
			strcmp(strTemp.c_str(),"1.#INF00")==0||strcmp(strTemp.c_str(),"1.#SNAN0")==0||
			strcmp(strTemp.c_str(),"-1.#IND00")==0||strcmp(strTemp.c_str(),"-nan")==0)
		{
			bExcept = false;
		}
        return bExcept;
    }

    std::string GetGUID()
    {
        return QUuid::createUuid().toString().toStdString();
    }

}
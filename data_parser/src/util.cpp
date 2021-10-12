/*******************************************************************************
* Copyright��C��,2010-2015,DTXY Tech .Co.Ltd;
* �� �� ��: util.h
* �ļ�����: ��������
*  ��  �� : %������%��18942552977
* ��������: 2014-9-29 10:42:00
*******************************************************************************/

#include "util.h"

#ifdef _WIN32
#include <windows.h>
#include <time.h>
#else
#include <sys/time.h>
#include <sys/stat.h> 
#endif

#include <boost/filesystem.hpp>

#ifdef WIN32
#pragma comment(lib, "ws2_32.lib")
#endif

namespace Util
{
		
		unsigned long  GetLastWriteTime(const std::string &filename)
		{

			time_t m_time =  boost::filesystem::last_write_time(filename);
			return m_time;
//#ifdef WIN32
//			WIN32_FIND_DATA p;
//			SYSTEMTIME  wtm;
//			HANDLE h = ftLastWriteTime(filename.c_str(),&p);
//			FileTimeToSystemTime(&(p.ftCreationTime), &wtm);
//			struct tm tm;
//			tm.tm_year     = wtm.wYear - 1900;
//			tm.tm_mon     = wtm.wMonth - 1;   
//			tm.tm_mday     = wtm.wDay;        
//			tm.tm_hour     = wtm.wHour;       
//			tm.tm_min     = wtm.wMinute;      
//			tm.tm_sec     = wtm.wSecond;      
//			tm. tm_isdst    = -1;             
//			m_time = mktime(&tm);     
//#else
//			struct stat msg;
//			stat(filename.c_str(), &msg);
//			m_time =  msg.st_ctime;
//#endif
//			return m_time;
		}

		unsigned long GetNowTime()
		{
			time_t nowtime = time(NULL);
			return nowtime;
		}

		unsigned long long  GetTimestamp()
		{
			timeval t;
#ifdef _WIN32
			struct tm tm;
			SYSTEMTIME wtm;
			GetLocalTime(&wtm);
			tm.tm_year     = wtm.wYear - 1900;
			tm.tm_mon     = wtm.wMonth - 1;
			tm.tm_mday     = wtm.wDay;
			tm.tm_hour     = wtm.wHour;
			tm.tm_min     = wtm.wMinute;
			tm.tm_sec     = wtm.wSecond;
			tm. tm_isdst    = -1;
			time_t clock = mktime(&tm);

			t.tv_sec = clock;
			t.tv_usec = wtm.wMilliseconds * 1000;
#else

			gettimeofday(&t, 0);
#endif
			return ((((unsigned long long)t.tv_sec) * 1000000) + (unsigned int)t.tv_usec);
		}

		std::vector<std::string> 
		SplitString(const std::string& sSplit,const char* szSplits,bool IgnoreEmpty)
		{
			//���Ͷ���
			typedef std::string				string_type;
			typedef string_type::size_type	size_type;

			//assert(szSplits);
			std::vector<string_type> vecStr;
			if (szSplits == NULL)
			{
				return vecStr;
			}

			if(sSplit.empty())//�����������ַ�Ϊ�գ�ֱ�ӷ���
				return vecStr;
			size_type begIndex,endIndex;//��ѯ�еĿ�ʼ����ʼλ��
			begIndex=0;

			while(string_type::npos !=begIndex)
			{	
				endIndex=sSplit.find_first_of (szSplits,begIndex);//��ѯ�ַ��ε�ĩβ
				if(string_type::npos ==endIndex)//��ѯ������λ��
					endIndex=sSplit.length ();
				string_type subStr=sSplit.substr (begIndex,endIndex-begIndex);//�ӿ�ʼ�ͽ���λ�ý�ȡ�ַ���
				if(!IgnoreEmpty || (IgnoreEmpty && (! subStr.empty () && subStr!="") ))
					vecStr.push_back (sSplit.substr (begIndex,endIndex-begIndex));
				begIndex=endIndex+1;//��һ����ʼλ��Ϊ��һλ�ú�
				if(endIndex==sSplit.length ())//��ѯ����
					break;
			}
			return vecStr; 
		}
}


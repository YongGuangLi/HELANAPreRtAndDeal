/*******************************************************************************
* Copyright（C）,2016-2020,DTXY Tech .Co.Ltd;
* 文 件 名: Util.cpp
* 文件描述: 基础函数类
*  作  者 : %王凯%，
* 创建日期: 2016-10-10 16:33:09
*******************************************************************************/

#ifndef __UTIL_H__
#define __UTIL_H__

#include <vector>
#include <sstream>
#include "RsdbAdapter.h"
#include <QUuid>

namespace Util
{
	////功能描述: 类型转换 
	template<class in_type,class out_type>
	out_type Convert(const in_type & t)
	{
		out_type result;
		std::stringstream stream;
		stream << t;
		stream >> result;
		return result;
	}

	////功能描述: 类型转换 
	template<class out_type>
	out_type CharPointerConvert2Number(const char * t)
	{
		if (strlen(t) == 0)
		{
			return 0;
		}
		out_type result;
		std::stringstream stream;
		stream << t;
		stream >> result;
		return result;
	}

	//Util::Convert<char, string>(a)


    unsigned char crcTail(unsigned char *data, int length );


	// 功能描述: 将数字类型转换为字符串 
	template<class NumberType>
	std::string Number2String(NumberType vv)
	{
		std::string result = Convert<NumberType, std::string>(vv);
		result.erase(std::remove(result.begin(), result.end(),','), result.end());
		return result;
	}
	// 功能描述: 字符串切割处理函数
	bool StringSplit(const std::string &strSrc, 
		std::vector<std::string> &lstRet, 
        const std::string &strSplit,bool isCheckReap=true);

	// 功能描述: 获取本机系统时间
    unsigned long getNowTime();
    bool RsdbConnect();

	// 功能描述: 连接关系数据库
    bool QtConnect(RsdbAdapter* pQtOpt,std::string strFactoryCode="");
	// 功能描述: 连接关系数据库
    bool QtConnectOnce(RsdbAdapter* pQtOp,std::string strFactoryCode);
    // 功能描述: 获取实时数据库的当前时间
    long getRtdbCurTimeToLong();
    // 功能描述: 获取实时数据库的当前时间
    bool getRtdbCurTimeToString(std::string &current_time);

	// 功能描述: 获取win系统目录
	//std::string getSystemDirectory();

	// 功能描述: 将long将为整分钟
	long convertIntMinute(const long &ltime);

	int getMinute(const time_t & c_time);
	void UtilsanityCheck(const int flag, const std::string &strmsg="");

	//add by wk 2017-12-21
	bool JudgeIsExcept(double fExceptVal);
	//end add

    std::string GetGUID();
}

#endif

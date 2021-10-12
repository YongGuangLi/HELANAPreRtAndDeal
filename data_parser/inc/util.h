/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: util.h
* 文件描述: 公共方法
*  作  者 : %林晓雨%，18942552977
* 创建日期: 2014-9-29 10:42:00
*******************************************************************************/
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <vector>

namespace Util
{

		//功能描述:文件内容最后被修改的时间
		unsigned long  GetLastWriteTime(const std::string &filename);

		//功能描述:获取当前系统second
		unsigned long GetNowTime();

		//功能描述: 类型转换 
		template<class in_type,class out_type>
		out_type Convert(const in_type & t)
		{
			out_type result;
			std::stringstream stream;
			stream << t;
			stream >> result;
			return result;
		}

		// 功能描述: 将数字类型转换为字符串 
		template<class NumberType>
		std::string Number2String(NumberType vv)
		{
			std::string result = Convert<NumberType, std::string>(vv);
			result.erase(std::remove(result.begin(), result.end(),','), result.end());
			return result;
		}

		unsigned long long  GetTimestamp();

		//功能描述:	分离字符串
		std::vector<std::string> SplitString(const std::string& sSplit,const char* szSplits,bool IgnoreEmpty=false);
}


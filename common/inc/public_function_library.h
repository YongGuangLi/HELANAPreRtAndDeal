/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: public_function_library.h
* 文件描述: 公共函数定义头文件
* 创建日期: 2014-9-9 15:26:28
*******************************************************************************/
#include <vector>
#include <list>
#include <string>
#include <sstream>

namespace PubOpt
{
    namespace TypeOpt
    {
        /* 
        * 功能描述: 长整型数据字符化
        * 输入参数: 长整型数值
        * 输出参数: 无
        * 返 回 值: 字符化后的长整型，长度为4
        *  作  者 : 汤卫波，13739072308
        */
        std::string UInt32ToChar4(const unsigned int &ulInt32);
        /* 
        * 功能描述: 字符化长整型转换
        * 输入参数: 长整型字符化串
        * 输出参数: 无
        * 返 回 值: 长整型数值
        *  作  者 : 汤卫波，13739072308
        */
        unsigned int Char4ToUInt32(const std::string &strUInt32);

		double CharPointerConvert2Number(const char * t);

    }

    namespace StringOpt
    {
        /* 
        * 功能描述: 截取字符串前空格
        * 输入参数: 带左空格字符串
        * 输出参数: 无
        * 返 回 值: 截取左空格后字符串
        *  作  者 : 汤卫波，13739072308
        */
        std::string LeftTrim(const std::string &strMsg);

        /* 
        * 功能描述: 截取字符串后空格
        * 输入参数: 带右空格字符串
        * 输出参数: 无
        * 返 回 值: 截取右空格后字符串
        *  作  者 : 汤卫波，13739072308
        */
        std::string RightTrim(const std::string &strMsg);

        /* 
        * 功能描述: 截取字符串前后空格
        * 输入参数: 带前后空格字符串
        * 输出参数: 无
        * 返 回 值: 截取前后空格后字符串
        *  作  者 : 汤卫波，13739072308
        */
        std::string TrimString(const std::string &strMsg);

        /* 
        * 功能描述: 字符串全大写格式化
        * 输入参数: 指定格式化字符串
        * 输出参数: 无
        * 返 回 值: 格式化后全大写字符串
        *  作  者 : 汤卫波，13739072308
        */
        std::string StringUpper(const std::string &strMsg);

        /* 
        * 功能描述: 字符串全小写格式化
        * 输入参数: 指定格式化字符串
        * 输出参数: 无
        * 返 回 值: 格式化后全小写字符串
        *  作  者 : 汤卫波，13739072308
        */
        std::string StringLower(const std::string &strMsg);

        /* 
        * 功能描述: 字符串格式化函数
        * 输入参数: 格式化格式
        * 输入参数: 拼接集合
        * 输出参数: 无
        * 返 回 值: 格式化字符串信息
        *  作  者 : 汤卫波，13739072308
        */
        std::string StringFormat(const char* pszFormat, ...);

        /* 
        * 功能描述: 字符串切割处理函数
        * 输入参数: 需要切割的原字符串
        * 输入参数: 切割字符
        * 输出参数: 无
        * 返 回 值: 切割后的字符段列表
        *  作  者 : 汤卫波，13739072308
        */
        bool StringSplit(const std::string &strSrc, 
            std::list<std::string> &lstRet, 
            const std::string &strSplit);
            
           
                /* 
        * 功能描述: 字符串切割处理函数
        * 输入参数: 需要切割的原字符串
        * 输入参数: 切割字符
        * 输出参数: 无
        * 返 回 值: 切割后的第nBit个字符串
        *  作  者 : 王凯，13739072308
        */
        std::string StringSplit(const std::string &strSrc, 
            const int &nBit, 
            const std::string &strSplit);

		bool StringSplit(const std::string &strSrc, std::vector<std::string> &lstRet, const std::string &strSplit);
        /* 
        * 功能描述: 字符批量替换处理
        * 输入参数: 原字符串
        * 输入参数: 被替换字符串
        * 输入参数: 替换字符串
        * 输出参数: 无
        * 返 回 值: 替换后的字符串
        *  作  者 : 汤卫波，13739072308
        *  注  意 : 替换会进行字符串递归替换
        */
        std::string StringReplace(const std::string &strSrc, 
            const std::string &strRepSrc, 
            const std::string &strRepSnk);
    }

    namespace FileOpt
    {
        /* 
        * 功能描述: 判断文件是否存在    注：支持目录判断
        * 输入参数: 文件名称
        * 输出参数: 无
        * 返 回 值: 成功返回true，失败返回false
        *  作  者 : 林晓雨, 1894255297 
        */
        bool IsFindFile(const std::string &strFileAll);

        /* 
        * 功能描述: 删除指定的文件
        * 输入参数: 文件名称
        * 输出参数: 无
        * 返 回 值: 成功返回true，失败返回false
        *  作  者 : 林晓雨, 1894255297 
        */
        bool RemoveFile(const std::string &strFname);

        /* 
        * 功能描述: 创建目录
        * 输入参数: 目录名称
        * 输出参数: 无
        * 返 回 值: 成功返回true，失败返回false
        *  作  者 : 林晓雨, 1894255297 
        */
        bool NewDirect(const std::string &strPath);

        /* 
        * 功能描述: 获取指定文件（路径+文件名+扩展名），文件名信息（文件名+扩展名）
        * 输入参数: 文件全名(带路径)
        * 输出参数: 文件名信息（文件名+扩展名）
        * 返 回 值: 文件名称
        *  作  者 : 林晓雨, 1894255297 
        */
        std::string GetFileName(const std::string &strFileAll);

		/* 
        * 功能描述: 获取当前执行文件名（文件名+扩展名）
        * 输出参数: 执行文件名（文件名+扩展名）
        * 返 回 值: 成功返回true，失败返回false
        */
		std::string GetExeFileName(void);

        /* 
        * 功能描述: 获取指定文件（路径+文件名+扩展名），文件名称（文件名）
        * 输入参数: 文件名称
        * 输出参数: 无
        * 返 回 值: 文件名
        *  作  者 : 汤卫波，13739072308
        */
        std::string GetNameByFile(const std::string &strFname);

        /* 
        * 功能描述: 获取文件大小
        * 输入参数: 文件名称
        * 输出参数: 文件大小
        * 返 回 值: 成功返回true，失败返回false
        *  作  者 : 汤卫波，13739072308
        */
        bool GetFileSize(const std::string &strFileName, int &nFileSize);
    }

    namespace SystemOpt
    {
        /* 
        * 功能描述: 系统休眠
        * 输入参数: 等待时间，单位(毫秒)
        * 输出参数: 无
        * 返 回 值: 无
        *  作  者 : 林晓雨, 1894255297 
        */
        void SleepWait(const int &nMilliTime);

        /* 
        * 功能描述: 获取当前系统时间
        * 输入参数: 无
        * 输出参数: 无
        * 返 回 值: 当前系统时间
        *  作  者 : 汤卫波，13739072308
        *  注  意 : 时间格式   [YYYY-MM-DD HH:mm:SS.sss]
        */
        std::string GetSystemDateTime(void);

        /* 
        * 功能描述: 获取当前系统主机名称
        * 输入参数: 无
        * 输出参数: 无
        * 返 回 值: 返回当前系统主机名称
        *  作  者 : 汤卫波，13739072308
        */
        std::string GetSystemHostName(void);

        /* 
        * 功能描述: 获取年月日时分
        * 输入参数: const time_t &
        * 输出参数: 无
        * 返 回 值: double
        *  作  者 : 王凯
        *  注  意 : 
        *           
        */
        int GetYear(const time_t & c_time);
        int GetMonth(const time_t & c_time);
        int GetDay(const time_t & c_time);
        int GetHour(const time_t & c_time);
        int GetMinute(const time_t & c_time);
		int GetSecond(const time_t & c_time);
        int GetDayOfWeek(const time_t & c_time);
        
        /* 
        * 功能描述: 获取std:string转化为time_t
        * 输入参数: std:string
        * 输出参数: 无
        * 返 回 值: time_t
        *  作  者 : 王凯
        *  注  意 : Windows时间格式 [YYYY-MM-DD HH:mm:SS]
        *           
        */
        time_t StrToDateTm(const std::string & time_string);

        /* 
        * 功能描述: time_t获取转化为std:string
        * 输入参数: time_t
        * 输出参数: 无
        * 返 回 值: std:string
        *  作  者 : 王凯
        *  注  意 : Windows时间格式 [YYYY-MM-DD HH:mm:SS]
        *           
        */
        std::string DateTmToStr(const time_t & c_time);

		/* 
        * 功能描述: time_t获取转化为std:string
        * 输入参数: time_t
        * 输出参数: 无
        * 返 回 值: std:string
        *  作  者 : 王凯
        *  注  意 : Windows时间格式 [YYYY-MM-DD HH:mm:SS]
        *           
        */
        std::string DateTmToStr(const time_t & c_time, int itype);
 
        /* 
        * 功能描述: 两个时间字符串间隔小时 如2014-9-16 12：00：00 与2014-9-16 13：00：00间隔一个小时
        * 输入参数: std:string
        * 输出参数: 无
        * 返 回 值: double
        *  作  者 : 王凯
        *  注  意 : 
        *           
        */
        double GetDevHour(std::string szCurrDate,std::string szFrontDate);

        /* 
        * 功能描述: 获取当前执行文件路径
        * 输入参数: 文件名称
        * 输出参数: 文件大小
        * 返 回 值: 成功返回true，失败返回false
        *  作  者 : 汤卫波，13739072308
        */
        std::string GetCurExePath(void);
    }
}


/*******************************************************************************
* Copyright��C��,2010-2015,DTXY Tech .Co.Ltd;
* �� �� ��: util.h
* �ļ�����: ��������
*  ��  �� : %������%��18942552977
* ��������: 2014-9-29 10:42:00
*******************************************************************************/
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <vector>

namespace Util
{

		//��������:�ļ���������޸ĵ�ʱ��
		unsigned long  GetLastWriteTime(const std::string &filename);

		//��������:��ȡ��ǰϵͳsecond
		unsigned long GetNowTime();

		//��������: ����ת�� 
		template<class in_type,class out_type>
		out_type Convert(const in_type & t)
		{
			out_type result;
			std::stringstream stream;
			stream << t;
			stream >> result;
			return result;
		}

		// ��������: ����������ת��Ϊ�ַ��� 
		template<class NumberType>
		std::string Number2String(NumberType vv)
		{
			std::string result = Convert<NumberType, std::string>(vv);
			result.erase(std::remove(result.begin(), result.end(),','), result.end());
			return result;
		}

		unsigned long long  GetTimestamp();

		//��������:	�����ַ���
		std::vector<std::string> SplitString(const std::string& sSplit,const char* szSplits,bool IgnoreEmpty=false);
}


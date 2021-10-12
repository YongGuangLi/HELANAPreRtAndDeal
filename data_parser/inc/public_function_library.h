/*******************************************************************************
* Copyright��C��,2010-2015,DTXY Tech .Co.Ltd;
* �� �� ��: public_function_library.h
* �ļ�����: ������������ͷ�ļ�
* ��������: 2014-9-9 15:26:28
*******************************************************************************/

#include <list>
#include <string>
#include <sstream>

namespace PubOpt
{
    namespace TypeOpt
    {
        /* 
        * ��������: �����������ַ���
        * �������: ��������ֵ
        * �������: ��
        * �� �� ֵ: �ַ�����ĳ����ͣ�����Ϊ4
        *  ��  �� : ��������13739072308
        */
        std::string UInt32ToChar4(const unsigned int &ulInt32);
        /* 
        * ��������: �ַ���������ת��
        * �������: �������ַ�����
        * �������: ��
        * �� �� ֵ: ��������ֵ
        *  ��  �� : ��������13739072308
        */
        unsigned int Char4ToUInt32(const std::string &strUInt32);

		double CharPointerConvert2Number(const char * t);

    }

    namespace StringOpt
    {
        /* 
        * ��������: ��ȡ�ַ���ǰ�ո�
        * �������: ����ո��ַ���
        * �������: ��
        * �� �� ֵ: ��ȡ��ո���ַ���
        *  ��  �� : ��������13739072308
        */
        std::string LeftTrim(const std::string &strMsg);

        /* 
        * ��������: ��ȡ�ַ�����ո�
        * �������: ���ҿո��ַ���
        * �������: ��
        * �� �� ֵ: ��ȡ�ҿո���ַ���
        *  ��  �� : ��������13739072308
        */
        std::string RightTrim(const std::string &strMsg);

        /* 
        * ��������: ��ȡ�ַ���ǰ��ո�
        * �������: ��ǰ��ո��ַ���
        * �������: ��
        * �� �� ֵ: ��ȡǰ��ո���ַ���
        *  ��  �� : ��������13739072308
        */
        std::string TrimString(const std::string &strMsg);

        /* 
        * ��������: �ַ���ȫ��д��ʽ��
        * �������: ָ����ʽ���ַ���
        * �������: ��
        * �� �� ֵ: ��ʽ����ȫ��д�ַ���
        *  ��  �� : ��������13739072308
        */
        std::string StringUpper(const std::string &strMsg);

        /* 
        * ��������: �ַ���ȫСд��ʽ��
        * �������: ָ����ʽ���ַ���
        * �������: ��
        * �� �� ֵ: ��ʽ����ȫСд�ַ���
        *  ��  �� : ��������13739072308
        */
        std::string StringLower(const std::string &strMsg);

        /* 
        * ��������: �ַ�����ʽ������
        * �������: ��ʽ����ʽ
        * �������: ƴ�Ӽ���
        * �������: ��
        * �� �� ֵ: ��ʽ���ַ�����Ϣ
        *  ��  �� : ��������13739072308
        */
        std::string StringFormat(const char* pszFormat, ...);

        /* 
        * ��������: �ַ����и����
        * �������: ��Ҫ�и��ԭ�ַ���
        * �������: �и��ַ�
        * �������: ��
        * �� �� ֵ: �и����ַ����б�
        *  ��  �� : ��������13739072308
        */
        bool StringSplit(const std::string &strSrc, 
            std::list<std::string> &lstRet, 
            const std::string &strSplit);
            
           
                /* 
        * ��������: �ַ����и����
        * �������: ��Ҫ�и��ԭ�ַ���
        * �������: �и��ַ�
        * �������: ��
        * �� �� ֵ: �и��ĵ�nBit���ַ���
        *  ��  �� : ������13739072308
        */
        std::string StringSplit(const std::string &strSrc, 
            const int &nBit, 
            const std::string &strSplit);
        /* 
        * ��������: �ַ������滻����
        * �������: ԭ�ַ���
        * �������: ���滻�ַ���
        * �������: �滻�ַ���
        * �������: ��
        * �� �� ֵ: �滻����ַ���
        *  ��  �� : ��������13739072308
        *  ע  �� : �滻������ַ����ݹ��滻
        */
        std::string StringReplace(const std::string &strSrc, 
            const std::string &strRepSrc, 
            const std::string &strRepSnk);
    }

    namespace FileOpt
    {
        /* 
        * ��������: �ж��ļ��Ƿ����    ע��֧��Ŀ¼�ж�
        * �������: �ļ�����
        * �������: ��
        * �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
        *  ��  �� : ������, 1894255297 
        */
        bool IsFindFile(const std::string &strFileAll);

        /* 
        * ��������: ɾ��ָ�����ļ�
        * �������: �ļ�����
        * �������: ��
        * �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
        *  ��  �� : ������, 1894255297 
        */
        bool RemoveFile(const std::string &strFname);

        /* 
        * ��������: ����Ŀ¼
        * �������: Ŀ¼����
        * �������: ��
        * �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
        *  ��  �� : ������, 1894255297 
        */
        bool NewDirect(const std::string &strPath);

        /* 
        * ��������: ��ȡָ���ļ���·��+�ļ���+��չ�������ļ�����Ϣ���ļ���+��չ����
        * �������: �ļ�ȫ��(��·��)
        * �������: �ļ�����Ϣ���ļ���+��չ����
        * �� �� ֵ: �ļ�����
        *  ��  �� : ������, 1894255297 
        */
        std::string GetFileName(const std::string &strFileAll);

		/* 
        * ��������: ��ȡ��ǰִ���ļ������ļ���+��չ����
        * �������: ִ���ļ������ļ���+��չ����
        * �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
        */
		std::string GetExeFileName(void);

        /* 
        * ��������: ��ȡָ���ļ���·��+�ļ���+��չ�������ļ����ƣ��ļ�����
        * �������: �ļ�����
        * �������: ��
        * �� �� ֵ: �ļ���
        *  ��  �� : ��������13739072308
        */
        std::string GetNameByFile(const std::string &strFname);

        /* 
        * ��������: ��ȡ�ļ���С
        * �������: �ļ�����
        * �������: �ļ���С
        * �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
        *  ��  �� : ��������13739072308
        */
        bool GetFileSize(const std::string &strFileName, int &nFileSize);
    }

    namespace SystemOpt
    {
        /* 
        * ��������: ϵͳ����
        * �������: �ȴ�ʱ�䣬��λ(����)
        * �������: ��
        * �� �� ֵ: ��
        *  ��  �� : ������, 1894255297 
        */
        void SleepWait(const int &nMilliTime);

        /* 
        * ��������: ��ȡ��ǰϵͳʱ��
        * �������: ��
        * �������: ��
        * �� �� ֵ: ��ǰϵͳʱ��
        *  ��  �� : ��������13739072308
        *  ע  �� : ʱ���ʽ   [YYYY-MM-DD HH:mm:SS.sss]
        */
        std::string GetSystemDateTime(void);

        /* 
        * ��������: ��ȡ��ǰϵͳ��������
        * �������: ��
        * �������: ��
        * �� �� ֵ: ���ص�ǰϵͳ��������
        *  ��  �� : ��������13739072308
        */
        std::string GetSystemHostName(void);

        /* 
        * ��������: ��ȡ������ʱ��
        * �������: const time_t &
        * �������: ��
        * �� �� ֵ: double
        *  ��  �� : ����
        *  ע  �� : 
        *           
        */
        int GetYear(const time_t & c_time);
        int GetMonth(const time_t & c_time);
        int GetDay(const time_t & c_time);
        int GetHour(const time_t & c_time);
        int GetMinute(const time_t & c_time);
        int GetDayOfWeek(const time_t & c_time);
        
        /* 
        * ��������: ��ȡstd:stringת��Ϊtime_t
        * �������: std:string
        * �������: ��
        * �� �� ֵ: time_t
        *  ��  �� : ����
        *  ע  �� : Windowsʱ���ʽ [YYYY-MM-DD HH:mm:SS]
        *           
        */
        time_t StrToDateTm(const std::string & time_string);

        /* 
        * ��������: time_t��ȡת��Ϊstd:string
        * �������: time_t
        * �������: ��
        * �� �� ֵ: std:string
        *  ��  �� : ����
        *  ע  �� : Windowsʱ���ʽ [YYYY-MM-DD HH:mm:SS]
        *           
        */
        std::string DateTmToStr(const time_t & c_time);

        /* 
        * ��������: ����ʱ���ַ������Сʱ ��2014-9-16 12��00��00 ��2014-9-16 13��00��00���һ��Сʱ
        * �������: std:string
        * �������: ��
        * �� �� ֵ: double
        *  ��  �� : ����
        *  ע  �� : 
        *           
        */
        double GetDevHour(std::string szCurrDate,std::string szFrontDate);

        /* 
        * ��������: ��ȡ��ǰִ���ļ�·��
        * �������: �ļ�����
        * �������: �ļ���С
        * �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
        *  ��  �� : ��������13739072308
        */
        std::string GetCurExePath(void);
    }
}


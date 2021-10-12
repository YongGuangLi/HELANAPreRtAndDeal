/*******************************************************************************
* Copyright��C��,2014-2020,DTXY Tech .Co.Ltd;
* �� �� ��: scan_path_file.h
* �ļ�����: ɨ��Ŀ¼�ļ�������ʵ����
*  ��  �� : ��������13739072308
* ��������: 2014-8-16 14:57:38
*******************************************************************************/

#ifndef __SCAN_PATH_FILE_H__
#define __SCAN_PATH_FILE_H__

#include <list>
#include <string>

#define MAX_SCAN_DEPTH        10      // ���ɨ�����

typedef enum ScanType                 // ɨ�����Ͷ���
{
    FILE_TYPE = 0,    // �ļ�
    DIRECTORY_TYPE,   // Ŀ¼
    UnKnown_Error     // δ֪����
}*P_SCAN_TYPE;

class ScanPathFile
{
public:
    /*
    * ����������Ŀ¼ɨ���������캯��
    * ���������ɨ�����ͣ�FILE_TYPE(�ļ�����)��DIRECTORY_TYPE(Ŀ¼����)
    * ����������༶Ŀ¼ɨ���Σ�ע�����֧��10��Ŀ¼ɨ��
    */
    ScanPathFile(const ScanType nType = FILE_TYPE, const int &nDepth = MAX_SCAN_DEPTH);
    virtual ~ScanPathFile(void);
public:
    /*
    * ����������Ŀ¼ɨ��ִ�к���
    * ���������ɨ����ļ��б�
    * ����ֵ��true(�ɹ�)��false(ʧ��)
    */
    bool ScanFile(const std::string &strScanPath, std::list<std::string> &lstFile);
private:
    // �����������ж��Ƿ�ΪĿ¼
    bool IsDirectory(const std::string &strDirectory);
    // ����������ִ���ļ�ɨ��
    bool DoRunScanFile(std::list<std::string> &lstFile);
private:
    int m_nDepth;                     // ɨ�����
    ScanType m_enType;                // ɨ������
    std::string m_strScanPath;        // ɨ���ļ�Ŀ¼
};

#endif//__SCAN_PATH_FILE_H__

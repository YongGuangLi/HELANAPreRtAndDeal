/*******************************************************************************
* Copyright��C��,2010-2015,DTXY Tech .Co.Ltd;
* �� �� ��: buff_points.h
* �ļ�����: Buff�ļ��������ݹ�����
*  ��  �� : ��������13730895608
* ��������: 2014-10-23 8:57:25
*******************************************************************************/

#ifndef __BUFF_POINTS_H__
#define __BUFF_POINTS_H__

#include "data_def.h"
#include <string>

class DataMgr;

class BuffPoints
{
public:
    BuffPoints(void);
    virtual ~BuffPoints(void);
public:

	int GetBuffFileCount(void);
    /* 
    * ��������: ��ʼ��Buff�ļ��������
    * �������: Buff�ļ�����Ŀ¼
    * �������: �ļ�ǰ׺��
    * �������: ��
    * �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
    */
    bool InitPoints(const std::string &strPath, const std::string &strHname);

	 /* 
    * ��������: ��ʼ��Buff�ļ��������
    * �������: Buff�ļ�����Ŀ¼
    * �������: �ļ�ǰ׺��
    * �������: ��
    * �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
    */
    bool InitBuff(const std::string &strPath, const std::string &strHname,const int &itype);
    /* 
    * ��������: ��ȡ���Buff�ļ���Ϣ
    * �������: ��
    * �������: ��
    * �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
    */
    bool ReadBuffFile(void);
    /* 
    * ��������: �ͷż��صĵ�������Ϣ
    * �������: ��
    * �������: ��
    * �� �� ֵ: ��
    */
    void DestoryPoints(void);

	/* 
    * ��������: ���صĵ�ռ�����
    * �������: ��
    * �������: ��
    * �� �� ֵ: ��
    */
	void CreatePointData(const int iCount);

	bool SentPointData(); 
public:
    // ��������: ��ȡ�糧���
    long GetFactoryTag(void);
    // ��������: ��ȡ��ĸ���
    long GetPointCount(void);
    // ��������: ��ȡ��������ʱ��
    std::string GetPacketDTime(void);
    // ��������: ��ȡָ����������Ϣ
    PointValue* GetPointsValue(const std::string &strPointName);
    // ��������: ��ȡָ����λ�õ���Ϣ
    PointValue* GetPointsValue(const long &lPointBit);

	// ��������: ��ȡָ����������Ϣ
	ModelPackageValue* GetPointsValueEx(const std::string &strPointName);
	// ��������: ��ȡָ����λ�õ���Ϣ
	ModelPackageValue* GetPointsValueEx(const long &lPointBit,const long imax);
public:
    DataMgr* m_pBuffOpt;            // Buff�ļ����������
    PointDatas m_stPoints;          // �������Ϣ����

private:
	int m_FileType;
	int m_DataType;
};

#endif//__BUFF_POINTS_H__

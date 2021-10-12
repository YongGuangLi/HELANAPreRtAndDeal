/*******************************************************************************
* Copyright��C��,2010-2015,DTXY Tech .Co.Ltd;
* �� �� ��: data_format.h
* �ļ�����: ���ݽ����ӿ���
*  ��  �� : %������%��18942552977
* ��������: 2014-9-10 14:23:03
*******************************************************************************/

#ifndef __DATA_PARSER_H__
#define __DATA_PARSER_H__

#include "data_def.h"
#include <iostream>
#include <vector>

#include "file_buff.h"

class DataParser
{
private:
	ParserType		mType;
	FileBuff *		mFileBuff;
	RemoteDataType	mDataType;

protected:
	std::string		mStrError;
public:
	DataParser(const ParserType type);

	virtual ~DataParser(void);

	void config(
		const RemoteDataType &data_type,
		const std::string &path,
		const std::string &point_fname_prefix);

	//��������: ��ͨѶ
	bool rt_Open();

	//��������: �ر�ͨѶ
	void rt_Close();

	//��������: �ͷ�һ�����ݰ�
	virtual void  DeletePointData(PointDatas* aPoints) = 0;

	//��������: ����һ�����ݰ�
	void CreatePointData(PointDatas* aPoints, unsigned long lPointCount);

	//��������: ��������
	bool  rt_Receive(PointDatas* pPoints);

	//��������:��������
	bool  rt_Send(const PointDatas& aPoints);

	//��������: ��ȡ������Ϣ
	std::string  getError();
//��������:��ȡĿ¼�ļ��ܸ���  add by wk 2018-7-10
	int getDirFileNum();
private:
	//��������: ����һ�����ݰ�
	virtual void  CreatePrivatePointValue(PointDatas* aPoints,unsigned long lPointCount) = 0;

	//��������:	���ݴ�����ַ�������
	virtual bool  PackPrivatePointDataToStr(PointDatas aPoints, std::string& strData) = 0;

	//��������:	���ַ����н��
	virtual bool  UnpackPrivatePointDataFromStr(PointDatas* pPoints, std::vector<std::string> &strSplits,std::vector<std::string>::iterator &i) = 0;

	//��������:	���ݴ��
	virtual void  PackPrivatePointData(PointDatas aPoints, char* &pTem) = 0;

	//��������: ���ݽ��
	virtual bool  UnpackPrivatePointData(const char* pTem, PointDatas* pPoints, long nPointCount) = 0;

	//��������:	��ȡ����Ҫ����İ����ݳ���
	virtual bool  GetPointPackLen(PointDatas aPoints,long* pLen) = 0; 

	//��������:	 ��ȡ�����ݴ�����ı�����
	virtual bool  GetPointPackTxtLen(PointDatas aPoints,long* pLen) = 0;

	//��������:	��ȡ�����ݵ�����
 	virtual bool  GetPackDataType(const void* pData, PackDataType* peDataType) = 0;

	//��������:	 ��ȡ����Ҫ����ĵ����ݳ���
	virtual bool  GetPointDataLen(PointDatas aPoints,long* pLen) = 0;
private:
	//��������:	 ���ݴ�����ַ�������
	bool  PackPointDataToStr(PointDatas aPoints, std::string& strData);
	//��������:	 ���ַ����н��
	bool  UnpackPointDataFromStr(const std::string& strData,PointDatas* pPoints);
	//��������:	 ���ݴ��
	bool  PackPointData(PointDatas aPoints,void* pData,long* pDataLen);
	//��������:	 ���ݽ��
	bool  UnpackPointData(const void* pData,long pDataLen, PointDatas* pPoints);
	//��������: 16λУ���
	unsigned short int  CheckSum16(unsigned char* pData,long pLen);

};
#endif

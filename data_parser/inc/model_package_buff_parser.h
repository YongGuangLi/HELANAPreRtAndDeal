/*******************************************************************************
* Copyright��C��,2010-2015,DTXY Tech .Co.Ltd;
* �� �� ��: model_package_buff_parser.h
* �ļ�����: ģ�����ݰ�ͨѶ����Э�����ʵ����
*  ��  �� : %����%��
* ��������: 2018-5-15 14:58:24
*******************************************************************************/
#ifndef __MODEL_PACKAGE_BUFF_PARSER_H__
#define __MODEL_PACKAGE_BUFF_PARSER_H__

#include "data_parser.h"
#include <iostream>
#include <vector>

class ModelPackageBuffParser :public DataParser
{
private:
	unsigned long 	mLPointCount;
public:
	ModelPackageBuffParser(void);
	~ModelPackageBuffParser(void);

	//��������: ����һ�����ݰ�
	virtual void  CreatePrivatePointValue(PointDatas* aPoints,unsigned long lPointCount);

	//��������:	���ݴ�����ַ�������
	virtual bool  PackPrivatePointDataToStr(PointDatas aPoints, std::string& strData);

	//��������:	���ַ����н��
	virtual bool  UnpackPrivatePointDataFromStr(PointDatas* pPoints, std::vector<std::string> &strSplits, std::vector<std::string>::iterator &i);

	//��������:	���ݴ��
	virtual void  PackPrivatePointData(PointDatas aPoints, char* &pTem);

	//��������: ���ݽ��
	virtual bool  UnpackPrivatePointData(const char* pTem, PointDatas* pPoints, long nPointCount);

	//��������:	��ȡ����Ҫ����İ����ݳ���
	virtual bool  GetPointPackLen(PointDatas aPoints,long* pLen); 

	//��������:	 ��ȡ�����ݴ�����ı�����
	virtual bool  GetPointPackTxtLen(PointDatas aPoints,long* pLen);

	//��������:	��ȡ�����ݵ�����
	virtual bool  GetPackDataType(const void* pData, PackDataType* peDataType);

	//��������:	 ��ȡ����Ҫ����ĵ����ݳ���
	virtual bool  GetPointDataLen(PointDatas aPoints,long* pLen);

	//��������: �ͷ�һ�����ݰ�
	virtual void  DeletePointData(PointDatas* aPoints);
};
#endif

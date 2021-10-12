/*******************************************************************************
* Copyright��C��,2010-2015,DTXY Tech .Co.Ltd;
* �� �� ��: dc_buff_parser.h
* �ļ�����: ý�ġ��������������ļ�����
*  ��  �� : %������%��18942552977
* ��������: 2014-9-10 16:03:40
*******************************************************************************/
#ifndef __DC_BUFF_PARSER_H__
#define __DC_BUFF_PARSER_H__

#include "data_parser.h"
#include <iostream>
#include <vector>

class DCBuffParser :public DataParser
{
public:
	DCBuffParser();
	~DCBuffParser(void);

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

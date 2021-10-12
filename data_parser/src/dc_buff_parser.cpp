/*******************************************************************************
* Copyright��C��,2010-2015,DTXY Tech .Co.Ltd;
* �� �� ��: dc_buff_parser.cpp
* �ļ�����: ý�ġ��������������ļ�����
*  ��  �� : %������%��18942552977
* ��������: 2014-9-10 16:05:34
*******************************************************************************/
#include "dc_buff_parser.h"

#include "error_def.h"
#include "util.h"
#include "public_function_library.h"
#include <iostream>
#include <string.h>
using namespace std;

DCBuffParser::DCBuffParser()
:
DataParser(DCPoint)
{
}

DCBuffParser::~DCBuffParser(void)
{
}


bool 
DCBuffParser::PackPrivatePointDataToStr(PointDatas aPoints, string& strData)
{
	for(unsigned long i=0;i<aPoints.Count;++i)
	{
		if(aPoints.ID)
			strData+=Util::Number2String<long>(aPoints.Points[i].ID)+SPLIT_CHAR;//��ID
		if(aPoints.Name)
			strData+=string(aPoints.Points[i].Name)+SPLIT_CHAR;//����
		if(aPoints.SetCode)
			strData+=Util::Convert<char,string>(aPoints.Points[i].SetCode)+SPLIT_CHAR;//�����
			//strData+=Util::Convert<short,string>((short)aPoints.Points[i].SetCode)+SPLIT_CHAR;//�����
		strData+=Util::Number2String(aPoints.Points[i].Value)+SPLIT_CHAR;//��ֵ
		if(aPoints.State)
			strData+=Util::Convert<char,string>(aPoints.Points[i].State)+SPLIT_CHAR;//���״̬
			//strData+=Util::Convert<short,string>((short)aPoints.Points[i].State)+SPLIT_CHAR;//���״̬
		if(aPoints.Time)
			strData+=PubOpt::SystemOpt::DateTmToStr(aPoints.Points[i].Time)+SPLIT_LINE;//ʱ���
	}
	return true;
}


bool 
DCBuffParser::UnpackPrivatePointDataFromStr(
	PointDatas* pPoints,
	vector<std::string> &strSplits,
	vector<std::string>::iterator &i)
{
	unsigned long nCount=0;
	while(true)
	{
		if(pPoints->ID )//���ID
		{
			if(i==strSplits.end())
				break;
			else
			{
				pPoints->Points[nCount].ID=Util::Convert<string,long>(*i);
				++i;
			}
		}
		if(pPoints->Name)//����
		{
			if(i==strSplits.end())
				break;
			else
			{
				strcpy(pPoints->Points[nCount].Name,i->c_str());
				++i;
			}
		}
		if(pPoints->SetCode)//��Ļ����
		{
			if(i==strSplits.end())
				break;
			else
			{
				//pPoints->Points[nCount].SetCode=(char)Util::Convert<string,short>(*i);
				pPoints->Points[nCount].SetCode=Util::Convert<string,char>(*i);
				++i;
			}
		}
		
		if(i==strSplits.end())//��ֵ
			break;
		else
		{
			pPoints->Points[nCount].Value=Util::Convert<string,float>(*i);
			++i;
		}
		
		if(pPoints->State)//��״̬
		{
			if(i==strSplits.end())
				break;
			else
			{
				//pPoints->Points[nCount].State=(char)Util::Convert<string,short>(*i);
				pPoints->Points[nCount].State=Util::Convert<string,char>(*i);
				++i;
			}
		}
		if(pPoints->Time)//��ʱ���
		{
			if(i==strSplits.end())
				break;
			else
			{
				pPoints->Points[nCount].Time=PubOpt::SystemOpt::StrToDateTm(*i);
				++i;
			}
		}
		++nCount;
		if(nCount >= pPoints->Count)
		{
			mStrError = IDS_ERROR_DATA;
			return false;
		}
	}
	pPoints->Count=nCount;
	return true;
}


void 
DCBuffParser::PackPrivatePointData(PointDatas aPoints, char* &pTem)
{
	for(unsigned long i=0;i<aPoints.Count;++i)
	{
		//��ı��
		if(aPoints.ID)
		{
			memcpy(pTem,&aPoints.Points[i].ID,sizeof(aPoints.Points[i].ID));
			pTem+=PACK_POINT_NO_LEN;
		}
		//�������
		if(aPoints.Name)
		{
			memcpy(pTem,aPoints.Points[i].Name,PACK_POINT_NAME_LEN);
			pTem+=PACK_POINT_NAME_LEN;
		}
		//��Ļ����
		if(aPoints.SetCode)
		{
			*pTem=aPoints.Points[i].SetCode;
			pTem+=PACK_SET_CODE_LEN;
		}
		//��ֵ
		memcpy(pTem,&aPoints.Points[i].Value,sizeof(aPoints.Points[i].Value));
		pTem+=PACK_VALUE_LEN;

		if(aPoints.Time)
		{
			memcpy(pTem,&aPoints.Points[i].Time,sizeof(aPoints.Points[i].Time));
			pTem+=PACK_TIME_LEN;
		}
		if(aPoints.State)
		{
			*pTem=aPoints.Points[i].State;
			pTem+=PACK_STATE_LEN;
		}
	}
}


bool 
DCBuffParser::UnpackPrivatePointData(const char* pTem, PointDatas* pPoints, long nPointCount)
{
	//��ȡ�������
	long i=0;
	for(i=0;i<nPointCount;++i)
	{
		if((unsigned long)i>=pPoints->Count)
			break;
		//���ID
		if(pPoints->ID)
		{
			pPoints->Points[i].ID=*(long*)pTem;
			pTem+=PACK_POINT_NO_LEN;
		}

		//�������
		if(pPoints->Name)
		{
			memcpy(pPoints->Points[i].Name,pTem,PACK_POINT_NAME_LEN);
			pTem+=PACK_POINT_NAME_LEN;
		}

		//��Ļ����
		if(pPoints->SetCode)
		{
			pPoints->Points[i].SetCode=(char)(*pTem);
			pTem+=PACK_SET_CODE_LEN;
		}
		//float* f=(float*)pTem;
		//��ֵ
		pPoints->Points[i].Value=*(float*)pTem;
		pTem+=PACK_VALUE_LEN;

		//���ʱ���
		if(pPoints->Time)
		{
			pPoints->Points[i].Time=*(long*)pTem;
			pTem+=PACK_TIME_LEN;
		}

		//���״̬
		if(pPoints->State)
		{
			pPoints->Points[i].State=(char)(*pTem);
			pTem+=PACK_STATE_LEN;
		}
	}

	pPoints->Count=i;
	return true;
}


void 
DCBuffParser::CreatePrivatePointValue(PointDatas* aPoints,unsigned long lPointCount)
{
	aPoints->Points=new PointValue[lPointCount];
	memset(aPoints->Points,0,sizeof(PointValue)*lPointCount);
}


void 
DCBuffParser::DeletePointData(PointDatas* aPoints)
{
	aPoints->Count=0;
	if(aPoints->Points!=NULL)
	{
		delete[] aPoints->Points;
		aPoints->Points=NULL;
	}
}


 bool 
 DCBuffParser::GetPackDataType(const void* pData,PackDataType* peDataType)
 {
	if(pData==NULL)
	{
		mStrError=IDS_NULL_POINT;
		return false;
	}
	char* pTem=(char*)const_cast<void*>(pData);
	//�����ֽ���ȡ��������
	pTem+=(PACK_NODE_NO_LEN+PACK_NO_LEN+PACK_TIME_LEN);	
	*peDataType=(PackDataType)(char)(*pTem);
	return true;
 }


bool 
DCBuffParser::GetPointPackTxtLen(PointDatas aPoints,long* pLen)
{
	if(pLen==NULL)
	{
		mStrError=IDS_NULL_POINT;
		return false;
	}
	int nHeardLen=PACK_NODE_NO_TXT_LEN;
	nHeardLen+=PACK_NO_TXT_LEN;
	nHeardLen+=PACK_DATA_COUNT_TXT_LEN;
	nHeardLen+=PACK_TIME_TXT_LEN;
	nHeardLen+=PACK_DC_NO_TXT_LEN;
	nHeardLen+=PACK_BOOL_TXT_LEN*5;

	int nPointLen=0;
	if(aPoints.ID)
		nPointLen+=PACK_POINT_NO_TXT_LEN;
	if(aPoints.Name)
		nPointLen+=PACK_POINT_NAME_TXT_LEN;
	if(aPoints.SetCode)
		nPointLen+=PACK_SET_CODE_TXT_LEN;
	nPointLen+=PACK_VALUE_TXT_LEN;
	if(aPoints.State)
		nPointLen+=PACK_STATE_TXT_LEN;
	if(aPoints.Time)
		nPointLen+=PACK_TIME_TXT_LEN;
	*pLen=nHeardLen + nPointLen*aPoints.Count;
	return true;
}


bool 
DCBuffParser::GetPointDataLen(PointDatas aPoints,long* pLen)
{
	if(pLen==NULL)
	{
		mStrError=IDS_NULL_POINT;
		return false;
	}
	int nLen=PACK_CONTROL_LEN+PACK_DATA_COUNT_LEN;
	int nPointLen=0;
	if(aPoints.ID)
		nPointLen+=PACK_POINT_NO_LEN;
	if(aPoints.Name)
		nPointLen+=PACK_POINT_NAME_LEN;
	if(aPoints.Time)
		nPointLen+=PACK_TIME_LEN;
	nPointLen+=PACK_VALUE_LEN;
	if(aPoints.State)
		nPointLen+=PACK_STATE_LEN;
	if(aPoints.SetCode)
		nPointLen+=PACK_SET_CODE_LEN;
	*pLen=nLen+nPointLen*aPoints.Count;
	return true;
}


bool 
DCBuffParser::GetPointPackLen(PointDatas aPoints,long* pLen)
{
	if(pLen==NULL)
	{
		mStrError=IDS_NULL_POINT;
		return false;
	}
	int nLen= PACK_NODE_NO_LEN+PACK_NO_LEN+PACK_TIME_LEN+PACK_DATA_TYPE_LEN+PACK_DC_NO_LEN+PACK_DATA_LEN_LEN+
		PACK_CONTROL_LEN+PACK_DATA_COUNT_LEN+PACK_CHECK_SUM_LEN ;
	int nPointLen=0;
	if(aPoints.ID)
		nPointLen+=PACK_POINT_NO_LEN;
	if(aPoints.Name)
		nPointLen+=PACK_POINT_NAME_LEN;
	if(aPoints.Time)
		nPointLen+=PACK_TIME_LEN;
	nPointLen+=PACK_VALUE_LEN;
	if(aPoints.State)
		nPointLen+=PACK_STATE_LEN;
	if(aPoints.SetCode)
		nPointLen+=PACK_SET_CODE_LEN;
	*pLen=nLen+nPointLen*aPoints.Count;
	return true;
}

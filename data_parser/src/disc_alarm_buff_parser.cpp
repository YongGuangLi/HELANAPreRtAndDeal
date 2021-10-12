/*******************************************************************************
* Copyright��C��,2010-2015,DTXY Tech .Co.Ltd;
* �� �� ��: disc_alarm_buff_parser.cpp
* �ļ�����: �������澯ͨѶ����Э�����ʵ����
*  ��  �� : %������%��18942552977
* ��������: 2014-9-18 14:59:04
*******************************************************************************/

#include "disc_alarm_buff_parser.h"

#include "error_def.h"
#include "util.h"
#include "public_function_library.h"
#include <iostream>
#include <string.h>
using namespace std;

DiscAlarmBuffParser::DiscAlarmBuffParser(void)
:
DataParser(DiscAlarm),
mLPointCount(0)
{
}

DiscAlarmBuffParser::~DiscAlarmBuffParser(void)
{
}


bool 
DiscAlarmBuffParser::PackPrivatePointDataToStr(PointDatas aPoints, string& strData)
{
	for(unsigned long i=0;i<aPoints.Count;++i)
	{
		if(aPoints.ID)
			strData+=Util::Number2String<long>(aPoints.Points[i].ID)+SPLIT_CHAR;//��ID
		if(aPoints.Name)
			strData+=string(aPoints.Points[i].Name)+SPLIT_CHAR;//����
		if(aPoints.SetCode)
			strData+=Util::Convert<char,string>(aPoints.Points[i].SetCode)+SPLIT_CHAR;//�����
		strData+=Util::Number2String(aPoints.Points[i].Value)+SPLIT_CHAR;//��ֵ

		strData+=Util::Convert<unsigned short,string>(aPoints.Points[i].Disc->AlarmInfoCount)+SPLIT_LINE;  //�澯����
		for (unsigned short j = 0; j < aPoints.Points[i].Disc->AlarmInfoCount; j++)
		{
			strData+=string(aPoints.Points[i].Disc->AlarmInfo[j].AlarmMsg)+SPLIT_CHAR;//�澯��Ϣ
			strData+=Util::Convert<char, string>(aPoints.Points[i].Disc->AlarmInfo[j].AlarmState)+SPLIT_CHAR; //�澯״̬
			strData+=Util::Convert<char, string>(aPoints.Points[i].Disc->AlarmInfo[j].AlarmLevel)+SPLIT_CHAR; //�澯����
		}
		//strData+=string(aPoints.Points[i].Disc->AlarmMsg)+SPLIT_CHAR;//�澯��Ϣ
		//strData+=Util::Convert<char, string>(aPoints.Points[i].Disc->AlarmState)+SPLIT_CHAR; //�澯״̬
		//strData+=Util::Convert<char, string>(aPoints.Points[i].Disc->AlarmLevel)+SPLIT_CHAR; //�澯����

		strData+=Util::Number2String(aPoints.Points[i].Disc->PretMeanFront)+SPLIT_CHAR;// Ԥ����ǰ��ֵ
		strData+=Util::Number2String(aPoints.Points[i].Disc->PretMeanBack)+SPLIT_CHAR;//Ԥ������ֵ
		strData+=Util::Number2String(aPoints.Points[i].Disc->StanDevi)+SPLIT_CHAR;//��׼��ֵ
		strData+=Util::Number2String(aPoints.Points[i].Disc->DetectType)+SPLIT_CHAR;//��ⷽ��

		if(aPoints.State)
			strData+=Util::Convert<char,string>(aPoints.Points[i].State)+SPLIT_CHAR;//���״̬
		if(aPoints.Time)
			strData+=PubOpt::SystemOpt::DateTmToStr(aPoints.Points[i].Time) + SPLIT_CHAR;//ʱ���
	}
	return true;
}


bool 
DiscAlarmBuffParser::UnpackPrivatePointDataFromStr(
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


		if(i==strSplits.end())//�澯����
			break;
		else
		{
			pPoints->Points[nCount].Disc->AlarmInfoCount = Util::Convert<string,unsigned short>(*i);
			++i;
		}

		for (unsigned short j = 0; j < pPoints->Points[nCount].Disc->AlarmInfoCount; j++)
		{
			if(i==strSplits.end())//�澯��Ϣ
				break;
			else
			{
				strcpy(pPoints->Points[nCount].Disc->AlarmInfo[j].AlarmMsg,i->c_str());
				++i;
			}

			if(i==strSplits.end())//�澯״̬
				break;
			else
			{
				//pPoints->Points[nCount].Disc->AlarmState=(char)Util::Convert<string,short>(*i);
				pPoints->Points[nCount].Disc->AlarmInfo[j].AlarmState=Util::Convert<string,char>(*i);
				++i;
			}

			if(i==strSplits.end())//�澯����
				break;
			else
			{
				//pPoints->Points[nCount].Disc->AlarmLevel=(char)Util::Convert<string,short>(*i);
				pPoints->Points[nCount].Disc->AlarmInfo[j].AlarmLevel=Util::Convert<string,char>(*i);
				++i;
			}
		}
		if(i==strSplits.end())//Ԥ����ǰ��ֵ
			break;
		else
		{
			pPoints->Points[nCount].Disc->PretMeanFront=Util::Convert<string,float>(*i);
			++i;
		}

		if(i==strSplits.end())//Ԥ������ֵ
			break;
		else
		{
			pPoints->Points[nCount].Disc->PretMeanBack=Util::Convert<string,float>(*i);
			++i;
		}

		if(i==strSplits.end())//��׼��ֵ
			break;
		else
		{
			pPoints->Points[nCount].Disc->StanDevi=Util::Convert<string,float>(*i);
			++i;
		}

		if(i==strSplits.end())//��ⷽ��
			break;
		else
		{
			pPoints->Points[nCount].Disc->DetectType=Util::Convert<string,int>(*i);
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
DiscAlarmBuffParser::PackPrivatePointData(PointDatas aPoints, char* &pTem)
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

		//�澯����
		memcpy(pTem,&aPoints.Points[i].Disc->AlarmInfoCount,sizeof(aPoints.Points[i].Disc->AlarmInfoCount));
		pTem+=PACK_ALARM_INFO_LEN;

		for (unsigned short j = 0; j < aPoints.Points[i].Disc->AlarmInfoCount; j++)
		{
			//�澯��Ϣ
			memcpy(pTem,aPoints.Points[i].Disc->AlarmInfo[j].AlarmMsg,PACK_ALARM_MSG_LEN);
			pTem+=PACK_ALARM_MSG_LEN;

			//�澯״̬
			*pTem = aPoints.Points[i].Disc->AlarmInfo[j].AlarmState;	
			pTem+=PACK_ALARM_STATE_LEN;

			//�澯����
			*pTem = aPoints.Points[i].Disc->AlarmInfo[j].AlarmLevel;	
			pTem+=PACK_ALARM_LEVEL_LEN;
		}

		for (unsigned short j = aPoints.Points[i].Disc->AlarmInfoCount; j < ALARM_MSG_MAX_COUNT; j++)
		{
			//�澯��Ϣ
			memset(pTem, 0,PACK_ALARM_MSG_LEN);
			pTem+=PACK_ALARM_MSG_LEN;

			//�澯״̬
			memset(pTem, 0,PACK_ALARM_STATE_LEN);
			pTem+=PACK_ALARM_STATE_LEN;

			//�澯����
			memset(pTem, 0,PACK_ALARM_LEVEL_LEN);
			pTem+=PACK_ALARM_LEVEL_LEN;
		}

		//Ԥ����ǰ��ֵ
		memcpy(pTem,&aPoints.Points[i].Disc->PretMeanFront,sizeof(aPoints.Points[i].Disc->PretMeanFront));
		pTem+=PACK_PRET_MEAN_FRONT_LEN;

		//Ԥ������ֵ
		memcpy(pTem,&aPoints.Points[i].Disc->PretMeanBack,sizeof(aPoints.Points[i].Disc->PretMeanBack));
		pTem+=PACK_PRET_MEAN_BACK_LEN;

		//��׼��ֵ
		memcpy(pTem,&aPoints.Points[i].Disc->StanDevi,sizeof(aPoints.Points[i].Disc->StanDevi));
		pTem+=PACK_STAN_DEVI_LEN;

		//��ⷽ��
		memcpy(pTem,&aPoints.Points[i].Disc->DetectType,sizeof(aPoints.Points[i].Disc->DetectType));
		pTem+=PACK_PRET_DETECT_TYPE;

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
DiscAlarmBuffParser::UnpackPrivatePointData(const char* pTem, PointDatas* pPoints, long nPointCount)
{
	//��ȡ�������
	long i=0;
	for(i=0;i<nPointCount;++i)
	{
		if((unsigned long) i>=pPoints->Count)
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
		//��ֵ
		pPoints->Points[i].Value=*(float*)pTem;
		pTem+=PACK_VALUE_LEN;

		//�澯����
		pPoints->Points[i].Disc->AlarmInfoCount = *(unsigned short*)pTem;
		pTem+=PACK_ALARM_INFO_LEN;

		for (unsigned short j = 0; j < pPoints->Points[i].Disc->AlarmInfoCount; j++)
		{
			//�澯��Ϣ
			memcpy(pPoints->Points[i].Disc->AlarmInfo[j].AlarmMsg,pTem,PACK_ALARM_MSG_LEN);
			pTem+=PACK_ALARM_MSG_LEN;

			//�澯״̬
			pPoints->Points[i].Disc->AlarmInfo[j].AlarmState = (char)(*pTem);
			pTem+=PACK_ALARM_STATE_LEN;

			//�澯����
			pPoints->Points[i].Disc->AlarmInfo[j].AlarmLevel = (char)(*pTem);
			pTem+=PACK_ALARM_LEVEL_LEN;		
		}

		for (unsigned short j = pPoints->Points[i].Disc->AlarmInfoCount; j < ALARM_MSG_MAX_COUNT; j++)
		{
			pTem+=PACK_ALARM_MSG_LEN;
			pTem+=PACK_ALARM_STATE_LEN;
			pTem+=PACK_ALARM_LEVEL_LEN;
		}

		//Ԥ����ǰ��ֵ
		pPoints->Points[i].Disc->PretMeanFront = *(float*)pTem;
		pTem+=PACK_PRET_MEAN_FRONT_LEN;

		//Ԥ������ֵ
		pPoints->Points[i].Disc->PretMeanBack = *(float*)pTem;
		pTem+=PACK_PRET_MEAN_BACK_LEN;

		//��׼��ֵ
		pPoints->Points[i].Disc->StanDevi = *(float*)pTem;
		pTem+=PACK_STAN_DEVI_LEN;

		//��ⷽ��
		pPoints->Points[i].Disc->DetectType = *(int*)pTem;
		pTem+=PACK_PRET_DETECT_TYPE;

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
DiscAlarmBuffParser::CreatePrivatePointValue(PointDatas* aPoints,unsigned long lPointCount)
{
	aPoints->Points = new PointValue[lPointCount];
	memset(aPoints->Points,0,sizeof(PointValue)*lPointCount);

	for (unsigned long i = 0; i < lPointCount; i++)
	{
		aPoints->Points[i].Disc = new DiscAlarmValue;
		memset(aPoints->Points[i].Disc,0,sizeof(DiscAlarmValue));
	}
	mLPointCount = lPointCount;
}


void 
DiscAlarmBuffParser::DeletePointData(PointDatas* aPoints)
{
	if(aPoints->Points != NULL)
	{
		for (unsigned long i = 0; i < mLPointCount; i++)
		{
			if (aPoints->Points[i].Disc != NULL)
			{
				delete aPoints->Points[i].Disc;
				aPoints->Points[i].Disc = NULL;
			}
		}
		delete[] aPoints->Points;
		aPoints->Points = NULL;
	}
}


bool 
DiscAlarmBuffParser::GetPackDataType(const void* pData,PackDataType* peDataType)
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
DiscAlarmBuffParser::GetPointPackTxtLen(PointDatas aPoints,long* pLen)
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

	nPointLen += PACK_ALARM_INFO_TXT_LEN;
	int alarm_group_len = PACK_ALARM_MSG_TXT_LEN;
	alarm_group_len += PACK_ALARM_STATE_TXT_LEN;
	alarm_group_len += PACK_ALARM_LEVEL_TXT_LEN;
	nPointLen += (alarm_group_len * ALARM_MSG_MAX_COUNT);
	//nPointLen+=PACK_ALARM_MSG_TXT_LEN;
	//nPointLen+=PACK_ALARM_STATE_TXT_LEN;
	//nPointLen+=PACK_ALARM_LEVEL_TXT_LEN;
	nPointLen+=PACK_PRET_MEAN_FRONT_TXT_LEN;
	nPointLen+=PACK_PRET_MEAN_BACK_TXT_LEN;
	nPointLen+=PACK_STAN_DEVI_TXT_LEN;
	nPointLen+=PACK_PRET_DETECT_TXT_TYPE;
	*pLen=nHeardLen+nPointLen*aPoints.Count;
	return true;
}


bool 
DiscAlarmBuffParser::GetPointDataLen(PointDatas aPoints,long* pLen)
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

	nPointLen+=PACK_ALARM_INFO_LEN;
	int alarm_group_len = PACK_ALARM_MSG_LEN;
	alarm_group_len += PACK_ALARM_STATE_LEN;
	alarm_group_len += PACK_ALARM_LEVEL_LEN;
	nPointLen += (alarm_group_len * ALARM_MSG_MAX_COUNT);
	//nPointLen+=PACK_ALARM_MSG_LEN;
	//nPointLen+=PACK_ALARM_STATE_LEN;
	//nPointLen+=PACK_ALARM_LEVEL_LEN;

	nPointLen+=PACK_PRET_MEAN_FRONT_LEN;
	nPointLen+=PACK_PRET_MEAN_BACK_LEN;
	nPointLen+=PACK_STAN_DEVI_LEN;
	nPointLen+=PACK_PRET_DETECT_TYPE;
	if(aPoints.State)
		nPointLen+=PACK_STATE_LEN;
	if(aPoints.SetCode)
		nPointLen+=PACK_SET_CODE_LEN;
	*pLen=nLen+nPointLen*aPoints.Count;
	return true;
}


bool 
DiscAlarmBuffParser::GetPointPackLen(PointDatas aPoints,long* pLen)
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

	nPointLen+=PACK_ALARM_INFO_LEN;
	int alarm_group_len = PACK_ALARM_MSG_LEN;
	alarm_group_len += PACK_ALARM_STATE_LEN;
	alarm_group_len += PACK_ALARM_LEVEL_LEN;
	nPointLen += (alarm_group_len * ALARM_MSG_MAX_COUNT);
	//nPointLen+=PACK_ALARM_MSG_LEN;
	//nPointLen+=PACK_ALARM_STATE_LEN;
	//nPointLen+=PACK_ALARM_LEVEL_LEN;

	nPointLen+=PACK_PRET_MEAN_FRONT_LEN;
	nPointLen+=PACK_PRET_MEAN_BACK_LEN;
	nPointLen+=PACK_STAN_DEVI_LEN;
	nPointLen+=PACK_PRET_DETECT_TYPE;
	if(aPoints.State)
		nPointLen+=PACK_STATE_LEN;
	if(aPoints.SetCode)
		nPointLen+=PACK_SET_CODE_LEN;
	*pLen=nLen+nPointLen*aPoints.Count;
	return true;
}

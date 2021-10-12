/*******************************************************************************
* Copyright��C��,2010-2015,DTXY Tech .Co.Ltd;
* �� �� ��: test_data_parser.cpp
* �ļ�����: ���ݽ������Գ���
*  ��  �� : %������%��18942552977
* ��������: 2014-9-22 10:18:35
*******************************************************************************/

#include "test_data_parser.h"
#include "data_def.h"
#include "error_def.h"
#include "data_mgr.h"
#include "util.h"
#include "public_function_library.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

TestDataParser::TestDataParser(void)
:
mNum(0)
{
}

TestDataParser::~TestDataParser(void)
{
	mSendData->rt_Close();
	mReData->rt_Close();
}

bool
TestDataParser::alarm()
{
	cout << "Alarm" << endl;	
	return false;
}

bool
TestDataParser::config()
{
	mSendData = new DataMgr();
	string path = "/home/linda/DTXY/data_parser/data/";
	//mSendData->rt_Initial(DCPoint, Text, path, "dc");
	//mSendData->rt_Initial(DCPoint, Binary, path, "dc");
	mSendData->rt_Initial(DiscAlarm, Text, path, "disc");
	bool rslt = mSendData->rt_Open();
	if (!rslt)
	{
		return alarm();
	}
	mReData = new DataMgr();
	//mReData->rt_Initial(DCPoint, Text, path, "dc");
	//mReData->rt_Initial(DCPoint, Binary, path);
	mReData->rt_Initial(DiscAlarm, Text, path, "disc");
	rslt = mReData->rt_Open();
	if (!rslt)
	{
		return  alarm();
	}
	return true;
}


bool
TestDataParser::run()
{
	cout << "tries:" << mNum++ << ";"<< endl;
	PointDatas pPointData;
	mSendData->CreatePointData(&pPointData, 5001);
	createPublicPointData(&pPointData);
	//createDCPointData(&pPointData);
	createDiscPointData(&pPointData);
	bool rslt = mSendData->rt_Send(pPointData);
	if (!rslt) 
	{
		return alarm();
	}

	PointDatas pReData;
	mReData->CreatePointData(&pReData, 5001);

PubOpt::SystemOpt::SleepWait(2000);
	rslt = mReData->rt_Receive(&pReData);
	if (!rslt) 
	{
		if (mReData->GetError() == ID_DIR_NULL) return true;
		return alarm();
	}
	rslt = checkPublicPointData(pPointData, pReData);
	if (!rslt) 
	{
		return alarm();
	}

	//rslt = checkDCPointData(pPointData, pReData);
	rslt = checkDiscPointData(pPointData, pReData);
	if (!rslt) 
	{
		return alarm();
	}

	mSendData->DeletePointData(&pPointData);
	mReData->DeletePointData(&pReData);
	return true;
}

bool
TestDataParser::createPublicPointData(PointDatas* pPoints)
{
	pPoints->No=rand()%100;//�����
	
	string time = randTimeStr();
	pPoints->PackTime=PubOpt::SystemOpt::StrToDateTm(time);//����ʱ��

	pPoints->DCNo=rand() %10;//�糧���

	pPoints->ID= rand() % 2 ;//�Ƿ���ID
pPoints->ID= 1;//�Ƿ���ID

	pPoints->Name= rand() % 2;//�Ƿ��е���
pPoints->Name= 1;//�Ƿ��е���

	pPoints->SetCode= rand() % 2;//�Ƿ��л����
pPoints->SetCode= 1;//�Ƿ��л����

	pPoints->State= rand() % 2;//�Ƿ���״̬
pPoints->State= 1;//�Ƿ���״̬

	pPoints->Time= rand() % 2;//�Ƿ��е��ʱ���
pPoints->Time= 1;//�Ƿ��е��ʱ���
	//pPoints->Count=rand() %9999 + 1;
	pPoints->Count=rand() %5000 + 1;
	//pPoints->Count= 10001;
	pPoints->CheckSum = rand() %99 + 1;
	return true;
}
											   

bool
TestDataParser::createDCPointData(PointDatas* pPoints)
{
	long nCount= 0;
	while((unsigned long) nCount < pPoints->Count)
	{
		if(pPoints->ID )//���ID
		{
			long id = rand()%30;
			pPoints->Points[nCount].ID =id;
		}
		if(pPoints->Name)//����
		{
			string name = randNameStr();
			strcpy(pPoints->Points[nCount].Name,name.c_str());
		}
		if(pPoints->SetCode)//��Ļ����								
		{
			pPoints->Points[nCount].SetCode = rand() % 10 + 48;
		}

		float f = rand()% 8989;
		pPoints->Points[nCount].Value=f;

		if(pPoints->State)//��״̬
		{
			pPoints->Points[nCount].State= rand() % 10 + 48;
		}
		if(pPoints->Time)//��ʱ���
		{
			string time = randTimeStr();
			pPoints->Points[nCount].Time=PubOpt::SystemOpt::StrToDateTm(time);
		}
		++nCount;
	}
	return true;
}


bool
TestDataParser::createDiscPointData(PointDatas* pPoints)
{
	long nCount= 0;
	while((unsigned long) nCount < pPoints->Count)
	{
		if(pPoints->ID )//���ID
		{
			long id = rand()%30;
			pPoints->Points[nCount].ID =id;
		}
		if(pPoints->Name)//����
		{
			string name = randNameStr();
			strcpy(pPoints->Points[nCount].Name,name.c_str());
		}
		if(pPoints->SetCode)//��Ļ����								
		{
			pPoints->Points[nCount].SetCode = rand() % 10 + 48;
		}

		float f = rand()% 8989;
		pPoints->Points[nCount].Value=f;

		unsigned short r = rand () % 5;
		pPoints->Points[nCount].Disc->AlarmInfoCount = r;
		for (unsigned short j = 0; j < r; j++)
		{
			//�澯��Ϣ
			string msg = randMsgStr();
			strcpy(pPoints->Points[nCount].Disc->AlarmInfo[j].AlarmMsg, msg.c_str());

			//�澯״̬
			pPoints->Points[nCount].Disc->AlarmInfo[j].AlarmState = (char)(rand() % 10 + 48);

			//�澯����
			pPoints->Points[nCount].Disc->AlarmInfo[j].AlarmLevel = (char)(rand()%10 + 48);
		}

		//Ԥ����ǰ��ֵ
		pPoints->Points[nCount].Disc->PretMeanFront=rand()%200;

		//Ԥ������ֵ
		pPoints->Points[nCount].Disc->PretMeanBack=rand()%200;

		//��׼��ֵ
		pPoints->Points[nCount].Disc->StanDevi=rand()%200;

		if(pPoints->State)//��״̬
		{
			pPoints->Points[nCount].State= rand() % 10 + 48;
		}
		if(pPoints->Time)//��ʱ���
		{
			string time = randTimeStr();
			pPoints->Points[nCount].Time=PubOpt::SystemOpt::StrToDateTm(time);
		}
		++nCount;
	}
	return true;
}


bool
TestDataParser::checkPublicPointData(const PointDatas &pLhs, const PointDatas &pRhs)
{
	if (pLhs.No != pRhs.No)
	{
		return alarm();
	}

	if (pLhs.PackTime != pRhs.PackTime)
	{
		return alarm();
	}
		
	if (pLhs.DCNo != pRhs.DCNo)
	{
		return alarm();
	}

	if (pLhs.ID != pRhs.ID)
	{
		return alarm();
	}

	if (pLhs.Name != pRhs.Name)
	{
		return alarm();
	}

	if (pLhs.Time != pRhs.Time)
	{
		return alarm();
	}

	if (pLhs.State != pRhs.State)
	{
		return alarm();
	}

	if (pLhs.SetCode != pRhs.SetCode)
	{
		return alarm();
	}
	if (pLhs.Count != pRhs.Count)
	{
		return alarm();
	}
	return true;
}


bool
TestDataParser::checkDCPointData(const PointDatas &pLhs, const PointDatas &pRhs)
{
	long nCount= 0;
	while((unsigned long) nCount < pLhs.Count)
	{
		if(pLhs.ID )//���ID
		{
			if(pLhs.Points[nCount].ID != pRhs.Points[nCount].ID)
			{
				return alarm();
			}
		}
		if(pLhs.Name)//����
		{
			if (strcmp(pLhs.Points[nCount].Name, pRhs.Points[nCount].Name) != 0)
			{
				return alarm();
			}
		}
		if(pLhs.SetCode)//��Ļ����								
		{
			if (pLhs.Points[nCount].SetCode != pRhs.Points[nCount].SetCode)
			{
				return alarm();
			}
		}

		if (pLhs.Points[nCount].Value != pRhs.Points[nCount].Value)
		{
			return alarm();
		}


		if(pLhs.State)//��״̬
		{
			if (pLhs.Points[nCount].State != pRhs.Points[nCount].State)
			{
				return alarm();
			}
		}

		if(pLhs.Time)//��ʱ���
		{
			if (pLhs.Points[nCount].Time != pRhs.Points[nCount].Time)
			{
				return alarm();
			}
		}
		++nCount;
	}

	return true;
}


bool
TestDataParser::checkDiscPointData(const PointDatas &pLhs, const PointDatas &pRhs)
{
	long nCount= 0;
	while((unsigned long) nCount < pLhs.Count)
	{
		if(pLhs.ID )//���ID
		{
			if(pLhs.Points[nCount].ID != pRhs.Points[nCount].ID)
			{
				return alarm();
			}
		}
		if(pLhs.Name)//����
		{
			if (strcmp(pLhs.Points[nCount].Name, pRhs.Points[nCount].Name) != 0)
			{
				return alarm();
			}
		}
		if(pLhs.SetCode)//��Ļ����								
		{
			if (pLhs.Points[nCount].SetCode != pRhs.Points[nCount].SetCode)
			{
				return alarm();
			}
		}

		if (pLhs.Points[nCount].Value != pRhs.Points[nCount].Value)
		{
			return alarm();
		}

		if (pLhs.Points[nCount].Disc->AlarmInfoCount != pRhs.Points[nCount].Disc->AlarmInfoCount)
		{
			return alarm();
		}

		for (unsigned short j = 0; j < pLhs.Points[nCount].Disc->AlarmInfoCount; j++)
		{
			if(strcmp(pLhs.Points[nCount].Disc->AlarmInfo[j].AlarmMsg, pRhs.Points[nCount].Disc->AlarmInfo[j].AlarmMsg) != 0)
			{
				return alarm();
			}

			if (pLhs.Points[nCount].Disc->AlarmInfo[j].AlarmState != pRhs.Points[nCount].Disc->AlarmInfo[j].AlarmState)
			{
				return alarm();
			}

			if (pLhs.Points[nCount].Disc->AlarmInfo[j].AlarmLevel != pRhs.Points[nCount].Disc->AlarmInfo[j].AlarmLevel)
			{
				return alarm();
			}
		}

		if (pLhs.Points[nCount].Disc->PretMeanFront != pRhs.Points[nCount].Disc->PretMeanFront)
		{
			return alarm();
		}

		if (pLhs.Points[nCount].Disc->PretMeanBack != pRhs.Points[nCount].Disc->PretMeanBack)
		{
			return alarm();
		}

		if (pLhs.Points[nCount].Disc->StanDevi != pRhs.Points[nCount].Disc->StanDevi)
		{
			return alarm();
		}

		if(pLhs.State)//��״̬
		{
			if (pLhs.Points[nCount].State != pRhs.Points[nCount].State)
			{
				return alarm();
			}
		}

		if(pLhs.Time)//��ʱ���
		{
			if (pLhs.Points[nCount].Time != pRhs.Points[nCount].Time)
			{
				return alarm();
			}
		}
		++nCount;
	}
	return true;
}


string
TestDataParser::randTimeStr()
{
	string time = "2014-";
	int i = rand() % 12;
	time +=Util::Convert<int,string>(i);
	time += "-";
	i = rand() % 29;
	time +=Util::Convert<int,string>(i);
	time += " ";
	i = rand() % 24;							  
	time +=Util::Convert<int,string>(i);
	time += ":";
	i = rand() % 60;
	time +=Util::Convert<int,string>(i);
	time += ":";
	i = rand() % 60;
	time +=Util::Convert<int, string>(i);
	return time;
}

string
TestDataParser::randNameStr()
{
	string name;
	int r = rand()%10 + 5;
	for (int t = 0; t < r ; t++)
	{
		name += (rand()%26 + 'A');
	}
	return name;
}

string
TestDataParser::randMsgStr()
{
	string name;
	//int r = rand()%123 + 5;
	int r = 128;
	for (int t = 0; t < r ; t++)
	{
		name += (rand()%26 + 'a');
	}
	return name;
}

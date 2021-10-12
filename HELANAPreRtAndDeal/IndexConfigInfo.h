/*******************************************************************************
* Copyright��C��,2010-2016,DTXY Tech .Co.Ltd;
* �� �� ��: IndexConfigInfo.h
* �ļ�����: ָ���������
*  ��  �� : %������%��
* ��������: 2015-5-27 10:21:06
*******************************************************************************/

#ifndef __INDEXCONFIGINFO_H__
#define __INDEXCONFIGINFO_H__

#include <map>
#include <string>
#include <vector>
#include "public_function_library.h"

struct IndexConfigInfo
{
	std::string				mFullIndexCode; 		//���糧ǰ׺��ָ����
	std::string				mIndexCode; 		//ָ����
	std::string				mIndexName;			//ָ����������
	std::string				mSetCode;			//������
	std::string				mWriteBackCode;		//��д���ʶ
	std::string				mLocalVar;			//�ڲ�����
	std::string				mOutVarAndFunc;		//�ⲿ�����뺯������
	std::string				mExpression;		//���㹫ʽ
	int						mPeriodTime;		//��������(����Ϊ��λ)  ->tb_pub_period
	int						mIsCal;				//�Ƿ����ü�������<�͸����Ƿ����>(0:�� ����  1������)
	int						mIsClearZero;		//�Ƿ�����(0:������ 1:����)
	int						mIsWriteRdtb;		//�Ƿ��дʵʱ���ݿ�(0:�� ��д  1����д)
	int						mType;				//ָ������(0��һ��ָ�� 1������ָ�� 2����������������ָ�� 3����ָͣ��)

	bool					mNew;				//ָ���Ƿ��Ѿ�����ĸ��±�־ true--�Ѿ����� false--û�м���
	int						mIsCalState;        //ָ������״̬(0:��ǰû�м��� 1����ǰ���ڼ���)
	double					mFDefaultVal;       //Ĭ��ֵ
	double					mUpLimit;			//����
	double					mLowLimit;			//����
	

	std::string				mTranOutVarAndFun;   //���������д�ŵ� "@"��ʽת���� "_"��ʽ,�γ��µ��ⲿ�����뺯������
	std::vector<std::string>mOutFuncVarArray;     //�ⲿ��������+�ⲿ����

	IndexConfigInfo(void)
	{
		mIndexCode = "";
		mIndexName = "";
		mWriteBackCode = "";
		mLocalVar = "";
		mOutVarAndFunc = "";
		mExpression = "";
		mPeriodTime = 0;
		mIsCal = 0;
		mIsClearZero = 0;

		mSetCode = "";
		mNew = false;
		mIsCalState = 0;
		mFDefaultVal = 0;
		mIsWriteRdtb = 1;
		mUpLimit	=	9999999;
		mLowLimit	=	-9999999;
		mTranOutVarAndFun = "";
		mOutFuncVarArray.clear();
	}

	~IndexConfigInfo()
	{
		mOutFuncVarArray.clear();
	}
	
	std::string toString()
	{
		std::string varArray;
		for (unsigned int i = 0; i < mOutFuncVarArray.size(); i++)
		{
			varArray += mOutFuncVarArray[i];
			varArray += "&";
		}
		std::string strMsg = PubOpt::StringOpt::StringFormat(
			"mIndexCode:%s, mIndexName:%s, mSetCode:%s, mWriteBackCode:%s, mLocalVar:%s, mOutVarAndFunc:%s, mExpression:%s, mPeriodTime:%d, mTranOutVarAndFun:%s, mOutFuncVarArray:(%s);",
			mIndexCode.c_str(), mIndexName.c_str(), mSetCode.c_str(), 
			mWriteBackCode.c_str(), mLocalVar.c_str(), mOutVarAndFunc.c_str(),
			mExpression.c_str(), mPeriodTime, 
			mTranOutVarAndFun.c_str(),
			varArray.c_str());
		return strMsg;
	}

	void clearMiddleRslt()
	{
		mNew = false;
		mIsCalState = 0;
	}
	//������ָ����ⲿ����
	void setOutVarAndFunc(const std::string pOutVar)
	{
		if (pOutVar.empty()) return;

		std::string strOutVar = pOutVar;											//�������
		if (!strOutVar.empty())
		{
			if(strOutVar.substr(strOutVar.size()-1,1) == ",")
			{
				strOutVar = strOutVar + mIndexCode;
			}
			else
			{
				strOutVar = strOutVar + "," + mIndexCode;
			}
		}
		else
		{
			strOutVar = "," + mIndexCode;
		}

		mOutVarAndFunc = strOutVar;

		//���ݿ��д�ŵ��� "@"��ʽ�� Ҫת���� "_"��ʽ
		//��ָ�걾��Ҳ��Ϊ�ⲿ�������뵽�ⲿ�������У���ֹ��ʽ���������Լ���ָ��
		//����������£���ָ֤��ļ���˳�򣬽���dll��ָ�걾���ڱ�������ȥ���ˣ��ڼ���ʱ����
		strOutVar = PubOpt::StringOpt::StringReplace(strOutVar,"@","_");

		mTranOutVarAndFun = strOutVar;
		ParseOutVarFunc();
	}

	///*----------------------------------------------------------------------------*/
	////	��������:	������ָ����ⲿ�����뺯�����Ե�����ʽ�������ڴ���
	///*----------------------------------------------------------------------------*/
	void ParseOutVarFunc()
	{
		int iOfLen = 0;
		std::string strICode;
		//ȡ�ⲿ������Ա����
		std::string strOutVarFunc = mOutVarAndFunc;
		strOutVarFunc = PubOpt::StringOpt::TrimString(strOutVarFunc);
		if (!strOutVarFunc.empty())
		{
			if (strOutVarFunc.substr(strOutVarFunc.size()-1,1) != ",")     //�ұ�û��",",��","
			{
				strOutVarFunc += ",";
			}
			if (strOutVarFunc.substr(0,1) == ",")      //�����",",��ȥ��","
			{
				strOutVarFunc = strOutVarFunc.substr(1,strOutVarFunc.size()-1);
			}
			while (strOutVarFunc.find(",") != std::string::npos&&strOutVarFunc.find(",")!=strOutVarFunc.size())
			{
				iOfLen = strOutVarFunc.find(",");
				strICode = strOutVarFunc.substr(0,iOfLen);
				strOutVarFunc = strOutVarFunc.substr(iOfLen+1,strOutVarFunc.size()-iOfLen-1);
				strICode = PubOpt::StringOpt::TrimString(strICode);
				if(!strICode.empty()) mOutFuncVarArray.push_back(strICode);
			}
		}

		std::string strTemp = mTranOutVarAndFun;
		//ȥ���ⲿ�����뺯����϶���ǰ��������","(����)
		if (!strTemp.empty())
		{
			if (strTemp.substr(strTemp.size()-1,1) == ",")     //�ұ���",",��ȥ��","
			{
				strTemp = strTemp.substr(1,strTemp.size()-1);   //�ⲿ�����뺯��
			}
			if (strTemp.substr(0,1) == ",")      //�����",",��ȥ��","
			{
				strTemp = strTemp.substr(1,strTemp.size()-1);
			}

			mTranOutVarAndFun = strTemp; //�ⲿ��������+�ⲿ����
			strTemp.clear();
		}
	}
};

#endif

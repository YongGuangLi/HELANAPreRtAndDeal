/**************************************************************************
* Copyright��C��,2014-2090,dtxy Tech .Co.Ltd;
* �� �� ��: ModeMethodAvgConfig.h
* �ļ�����: ģ������ֵ����
*  ��  �� : ������15802613961
* ��������: 2016-1-16 16:44:33
**************************************************************************/
#ifndef __MODEMETHODAVGCONFIG_H__
#define __MODEMETHODAVGCONFIG_H__

#include <vector>
#include "Util.h"
struct MethodAvg
{
    std::string mCondId;     //ģ��ģʽID
	bool        mIsOk;       //ģʽѵ�������Ƿ���Ч  true����Ч  false�� ��Ч
	double      mDSimLimit;	//ģʽ��ֵ
    std::vector<std::string> mVectorModePoint;
    std::vector<std::string> mVectorTempValue;
    std::vector<std::vector<double>> mVectorFunValue;
	std::vector<std::vector<double>> mVectorRelationValue;
    std::vector<double> mVectorMaValue;
    MethodAvg()
    {
        cleanVar();
		mIsOk=true;
    }
    ~MethodAvg()
    {
        cleanVar();
    }
bool CheckIntoFunValue(const int typeVec)
    {
        double dValue;
        std::vector<double> vecRow;
        std::string strTemp;
        for (std::vector<std::string>::iterator it=mVectorTempValue.begin();it!=mVectorTempValue.end();++it)
        {
            if((*it).empty()) 
            {
              cleanVar();
              return false;  
            }
            strTemp=*it;
           dValue=Util::CharPointerConvert2Number<double>((*it).c_str()); 
           vecRow.push_back(dValue);
        }
		if(1==typeVec)
          mVectorFunValue.push_back(vecRow);
		else if(2==typeVec)
		  mVectorRelationValue.push_back(vecRow);
        return true;
    }
void cleanVar()
    {
        mVectorTempValue.clear();
        mVectorModePoint.clear();
        for(std::vector<std::vector<double>>::iterator it=mVectorFunValue.begin();it!=mVectorFunValue.end();++it)
            it->clear();
        mVectorFunValue.clear();
        mVectorMaValue.clear();
		for(std::vector<std::vector<double>>::iterator it=mVectorRelationValue.begin();it!=mVectorRelationValue.end();++it)
			it->clear();
		mVectorRelationValue.clear();
    }
};

struct ModeMethodAvg
{
	std::string mModeId;	//ģ��ID
	std::map<std::string, MethodAvg *>		mMapmethodavg;
	ModeMethodAvg()
	{
		cleanVar();
	}
	~ModeMethodAvg()
	{
		cleanVar();
	}
	void cleanVar()
	{
		std::map<std::string, MethodAvg *>::iterator it;
		for (it=mMapmethodavg.begin();it!=mMapmethodavg.end();++it)
		{
			delete it->second;
		}
		mMapmethodavg.clear();
	}
};
#endif//__MODEMETHODAVGCONFIG_H__

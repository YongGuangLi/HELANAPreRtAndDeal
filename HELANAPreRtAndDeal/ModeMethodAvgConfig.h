/**************************************************************************
* Copyright（C）,2014-2090,dtxy Tech .Co.Ltd;
* 文 件 名: ModeMethodAvgConfig.h
* 文件描述: 模型期望值配置
*  作  者 : 王凯，15802613961
* 创建日期: 2016-1-16 16:44:33
**************************************************************************/
#ifndef __MODEMETHODAVGCONFIG_H__
#define __MODEMETHODAVGCONFIG_H__

#include <vector>
#include "Util.h"
struct MethodAvg
{
    std::string mCondId;     //模型模式ID
	bool        mIsOk;       //模式训练样本是否有效  true：有效  false： 无效
	double      mDSimLimit;	//模式限值
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
	std::string mModeId;	//模型ID
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

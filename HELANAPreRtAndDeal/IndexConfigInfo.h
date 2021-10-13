/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: IndexConfigInfo.h
* 文件描述: 指标基础配置
*  作  者 : %林晓雨%，
* 创建日期: 2015-5-27 10:21:06
*******************************************************************************/

#ifndef __INDEXCONFIGINFO_H__
#define __INDEXCONFIGINFO_H__

#include <map>
#include <string>
#include <vector>
#include "public_function_library.h"

struct IndexConfigInfo
{
    std::string				mFullIndexCode; 		//带电厂前缀的指标编号
    std::string				mIndexCode; 		//指标编号
    std::string				mIndexName;			//指标中文描述
    std::string				mSetCode;			//机组编号
    std::string				mWriteBackCode;		//回写点标识
    std::string				mLocalVar;			//内部变量
    std::string				mOutVarAndFunc;		//外部变量与函数名称
    std::string				mExpression;		//计算公式
    int						mPeriodTime;		//计算周期(以秒为单位)  ->tb_pub_period
    int						mIsCal;				//是否启用计算条件<低负荷是否计算>(0:不 计算  1：计算)
    int						mIsClearZero;		//是否清零(0:不清零 1:清零)
    int						mIsWriteRdtb;		//是否回写实时数据库(0:不 回写  1：回写)
    int						mType;				//指标类型(0：一般指标 1：超限指标 2：带负荷能力关联指标 3：启停指标)

    bool					mNew;				//指标是否已经计算的更新标志 true--已经计算 false--没有计算
    int						mIsCalState;        //指标计算的状态(0:当前没有计算 1：当前正在计算)
    double					mFDefaultVal;       //默认值
    double					mUpLimit;			//上限
    double					mLowLimit;			//下限


    std::string				mTranOutVarAndFun;   //函数名称中存放的 "@"格式转换成 "_"格式,形成新的外部变量与函数名称
    std::vector<std::string>mOutFuncVarArray;     //外部函数变量+外部变量

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
    //解析出指标的外部变量
    void setOutVarAndFunc(const std::string pOutVar)
    {
        if (pOutVar.empty()) return;

        std::string strOutVar = pOutVar;											//输出变量
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

        //数据库中存放的是 "@"格式的 要转换成 "_"格式
        //将指标本身也作为外部变量加入到外部变量串中，防止公式中引用了自己的指标
        //（这种情况下，保证指标的计算顺序，解析dll将指标本身在变量串中去掉了）在计算时出错
        strOutVar = PubOpt::StringOpt::StringReplace(strOutVar,"@","_");

        mTranOutVarAndFun = strOutVar;
        ParseOutVarFunc();
    }

    ///*----------------------------------------------------------------------------*/
    ////	功能描述:	解析出指标的外部变量与函数，以单个形式保存在内存中
    ///*----------------------------------------------------------------------------*/
    void ParseOutVarFunc()
    {
        int iOfLen = 0;
        std::string strICode;
        //取外部函数成员名称
        std::string strOutVarFunc = mOutVarAndFunc;
        strOutVarFunc = PubOpt::StringOpt::TrimString(strOutVarFunc);
        if (!strOutVarFunc.empty())
        {
            if (strOutVarFunc.substr(strOutVarFunc.size()-1,1) != ",")     //右边没有",",加","
            {
                strOutVarFunc += ",";
            }
            if (strOutVarFunc.substr(0,1) == ",")      //左边有",",就去掉","
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
        //去掉外部变量与函数组合对象前面与最后的","(逗号)
        if (!strTemp.empty())
        {
            if (strTemp.substr(strTemp.size()-1,1) == ",")     //右边有",",就去掉","
            {
                strTemp = strTemp.substr(1,strTemp.size()-1);   //外部变量与函数
            }
            if (strTemp.substr(0,1) == ",")      //左边有",",就去掉","
            {
                strTemp = strTemp.substr(1,strTemp.size()-1);
            }

            mTranOutVarAndFun = strTemp; //外部函数变量+外部变量
            strTemp.clear();
        }
    }
};

#endif

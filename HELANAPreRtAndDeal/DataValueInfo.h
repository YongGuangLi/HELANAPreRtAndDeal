/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: DataValueInfo.h
* 文件描述: 数据类
*  作  者 : %WK%，
* 创建日期: 2016-1-13 9:08:41
*******************************************************************************/

#ifndef __DATAVALUEINFO_H__
#define __DATAVALUEINFO_H__

#include "public_function_library.h"
#include "Util.h"
#include <list>
#include <map>
#include <vector>
#include <iostream>
#include "../funlib/FunPublic.h"
#include <QString>

#define  NO_ALARM "no_alarm"
#define PRE_CAL_DELAY_NUMBER  4								//延时计算
//struct Interval
//{
//	double	 m_UpLimit;              //上限值
//	bool     m_IsUpLimit;			//上限值是否存在
//	double   m_LowLimit;			//下限值
//	bool     m_IsLowLimit;			//下限值是否存在
//};
struct IntervalEX
{

	Interval m_interval;
	int		 m_DataType;         //数据来源 ，带负荷能力数据来源(0:实时出力 1:定值 -1: 为空，额定负荷)
	double   m_value;			//数据值
};
struct AParam         //计算健康度依赖的可变参数a配置结构
{
	std::string     mPoint;			//参数名
	double			mSimValue;		//健康度值
};
//struct VarParam         //计算健康度依赖的可变参数a配置结构
//{
//	std::string     mPoint;			//模型参数名
//	double			mCurValue;		//实时值
//	Interval		m_Interval;     //区间
//	int				m_iType;		//类型(1:正向 2:反向 3:双向)
//	int				m_iParamSource; //可调参数a数据来源(0:公式计算 1:手工设定)
//	double			m_ParamValue;	//可调参数a值
//};
struct Dfhnl
{
public:
	Dfhnl()
	{
		m_dfhValue = 0;
		m_icategory = 0;
		m_Fullcode = "";
	}
	virtual ~Dfhnl()
	{
		m_VectorDfhInterval.clear();
		m_VectorDfhValue.clear();
	}
	std::string   m_Fullcode;	//带负荷计算带电厂编号前缀的测点名，包括测点和指标 比如ZZ_D2_A,ZZ_M1_X
	std::string   m_code;		//带负荷计算测点名，包括测点和指标
	std::string   m_SourceCode;	//带负荷计算测点回写点名，包括测点和指标
	int           m_icategory;	//带负荷引用点属性，对象类别(2:模型 3:参数类 4: 模型参数 5:测点和指标)
	double		  m_dfhValue;	//带负荷值
	std::map<std::string , IntervalEX>	m_VectorDfhInterval;
	std::vector<double>		m_VectorDfhValue;
};
typedef std::map<std::string , IntervalEX> MapStringToIntervalEX;
typedef MapStringToIntervalEX::iterator    MapStringToIntervalEX_It;
enum GetDateWay
{
	eFromRtdb = 1,			//从实时数据库获取数据或者表示是子站系统
    eFromDir = 2,		    //从目录获取数据或者表示是主站系统
};
enum PointType
{
	eInvalid = 0,
	eRealTimeOrgDPoint = 1,		//实时点
	eRealTimeDPoint = 2,		//回写实时点
	eExpMaunalPoint = 3,		//计算公式解析的手工点
	ePreDPoint=4,				//实时点期望值
	eSimDPoint=5,				//测点相似度
	eSim = 6,					//非测点相似度
	eIndex = 7,					//指标
	eDfh  = 8,					//带负荷能力
	eDfhCome  = 9,				//带负荷能力计算引用的模型、参数类、模型参数
	eMcond  =10	,				//模型的模式回写点
    eMstatus  =11			    //模型的启停回写点
};
struct mModelAllPointSource
{
	std::string mModelId;
	std::map<std::string, std::string>	mapPoint;
};
struct DataInfo  
{
public:
	
	DataInfo(void)
	{
		mDValue = 0;
		mPointType = eInvalid;
		mRsdbPointIdIsExist = false;
		mError = 0;
		mForeVal = 0;
		m_IsGetValue = false;
		mIsWriteRtdb = false;
		mRtdbPSourceIsExist = false;
		mSet = "0";
		mNotInMedlePoints = false;
		mFullPointId = "";
	}
public:
    double						mDValue;			    //实时数据库获取的测点原始值
    bool						m_IsGetValue;           //是否获取到原始值
    long                        mlTime;                 //测点时间
public:
	std::string                 mSet;
	std::string 				mFullPointId;			//关系数据库测点加电厂编号原始全点名
    std::string 				mPointId;			    //关系数据库测点原始全点名
    std::string					mPSource;	            //实时数据库测点原始全点名
	PointType					mPointType;				//点类型
    bool                        mNotInMedlePoints;      //是否不存在在模型测点中 true：不存在 false：存在
	bool						mRsdbPointIdIsExist;	//关系数据库中此点是否存在
    bool						mRtdbPSourceIsExist;    //实时数据库中此点是否存在
    bool						mIsWriteRtdb;		    //是否回写实时数据库
	int		  					mError;			   		//主站指标值的有效性   0--有误 1--正常    数据库中STATUS字段 1表示正常 0表示错误
	double    					mForeVal;          		//公式计算上一个周期的值

	void resetValue()
	{
		mError = 0;
		mDValue = 0;
	}


	std::string toString()
	{
        //std::string strMsg = PubOpt::StringOpt::StringFormat( "mStrCode:%s, mOrigValue:%f,  mForeVal:%f, mError:%d;",  mPointId, mDValue, mForeVal, mError);
        std::string strMsg = QString( "mStrCode:%1, mOrigValue:%2,  mForeVal:%3, mError:%4;").arg(mPointId.c_str()).arg(mDValue).arg(mForeVal).arg(mError).toStdString();
		return strMsg;
	}

	double getOrigValue()
	{
		return mDValue;
	}
	void setCurrVar(const double vv)
	{
		if (Util::JudgeIsExcept(vv))
		{
			mDValue = vv;
		}
		else
		{
			mDValue = 0;
		}
		m_IsGetValue = true;
	}

	double getCurrVar(int dtype)
	{
		return mDValue;
	}
};
struct DataValueInfo  
{
public:

	DataValueInfo(void)
	{
		mDOrigValue = 0;
		//mDWriteOrigValue=0;
		mDPreValue = 0;
		mDSimValue=0;
		mMonitPointId = "";
		mPointSource = "";
		mPreSource = "";
		mPOrigSource = "";
		mSimSource = "";
		mPointType = eInvalid;
		mRsdbPointIdIsExist = false;
		mRtdbPOrigSourceIsExist=false;
		mRtdbPointSourceIsExist=false;
		mRtdbPreSourceIsExist=false;
		mRtdbSimSourceIsExist=false;
		
		mIsPreAlarm = 1;
		mError = 0;
		mForeVal = 0;

		m_IsGetOrigValue = false;
		m_IsGetPreValue = false;
		m_IsGetSimValue = false;
	}


public:
	double						mDOrigValue;				//实时数据库获取的测点原始值
    bool						m_IsGetOrigValue;           //是否获取到原始值
    //double						mDWriteOrigValue;       //回写测点原始值
    double						mDPreValue;          	    //期望值
    bool						m_IsGetPreValue;            //是否获取到期望值
    double						mDSimValue;          	    //测点健康度
    bool						m_IsGetSimValue;            //是否获取到健康度值
    long                        mlTime;                     //测点时间
public:	
    std::string 				mMonitPointId;		        //关系数据库测点原始全点名
    std::string 				mPointId;			        //关系数据库测点原始全点名
    std::string					mPOrigSource;	            //实时数据库测点原始全点名
    std::string 				mPointSource;			    //测点回写原始值点名
    std::string					mPreSource;			        //测点回写期望值点名
    std::string					mSimSource;			        //测点回写健康度点名
		
    PointType					mPointType;				    //点类型
    
    bool						mRsdbPointIdIsExist;	    //关系数据库中此点是否存在
	bool						mRtdbPOrigSourceIsExist;	//实时数据库中此点是否存在
	bool						mRtdbPointSourceIsExist;	//实时数据库中此点是否存在
    bool						mRtdbPreSourceIsExist;	    //实时数据库中此点是否存在
    bool						mRtdbSimSourceIsExist;	    //实时数据库中此点是否存在

    int		  					mError;			   		    //主站指标值的有效性   0--有误 1--正常    数据库中STATUS字段 1表示正常 0表示错误
    double    					mForeVal;          		    //公式计算上一个周期的值
	 	 
    int							mIsPreAlarm;			    //此点是否告警(点的状态(0:异常 1:正常))

	void resetValue()
	{
		mError = 0;
		mDOrigValue = 0;
		mDPreValue = 0;
		mDSimValue=0;
	}


	std::string toString()
	{
		std::string strMsg = PubOpt::StringOpt::StringFormat(
				"mStrCode:%s, mOrigValue:%f, mCurrVal:%f, mPointSource:%s, mForeVal:%f, mError:%d;", 
				 mDOrigValue, mDPreValue, mPointSource.c_str(), mForeVal, mError); 
		return strMsg;
	}

	double getOrigValue()
	{
		return mDOrigValue;
	}
	void setCurrVar(const double vv,int dtype)
	{
	    if(1==dtype)
		{
			if (Util::JudgeIsExcept(vv))
			{
				mDOrigValue = vv;
			}
			else
			{
				mDOrigValue = 0;
			}
			m_IsGetOrigValue = true;
		}
        if(2==dtype)
		{
			if (Util::JudgeIsExcept(vv))
			{
				mDPreValue = vv;
			}
			else
				mDPreValue = 0;
		}
        if(3==dtype)
		{
			if (Util::JudgeIsExcept(vv))
			{
				mDSimValue = vv;
			}
			else
				mDSimValue = 0;
		}
	}

	double getCurrVar(int dtype)
	{
	    if(1==dtype)
		    return mDOrigValue;
        if(2==dtype)
            return mDPreValue;
        if(3==dtype)
            return mDSimValue;
		else
			return mDOrigValue;
	}
};


struct ModelCondition
{
	ModelCondition(void)
	{
		m_ModelConditionId="";
		m_strLocalVar="";
		m_strOutVar="";
		m_strOutVarFun="";
		m_strTranOutVarFun="";
		m_Exp="";
		m_ModelConditionValue = -1;
		m_OutFuncVarArray.clear();
	}
	ModelCondition(std::string	modelId);
	~ModelCondition(void)
	{
		m_OutFuncVarArray.clear();
	}

	std::string				m_ModelConditionId;//莫式ID
	//std::string				m_ModelConditionName;
	double					m_ModelConditionValue;//模式配置值
	std::string				m_strLocalVar;			//本地变量
	std::string				m_strOutVar;         //输出外部变量名称
	std::string				m_strOutVarFun;         //输出外部函数名称
	std::string				m_strOutVarAndFun;         //输出外部函数名称
	std::string				m_strTranOutVarFun;     //函数名称中存放的 "@"格式转换成 "_"格式,形成新的外部变量与函数名称
	std::vector<std::string>			m_OutFuncVarArray;      //外部函数变量+外部变量
	std::string				m_Exp;					//条件 

	std::string				m_modelId;		//莫型ID

	//解析出指标的外部变量
	void setOutVarAndFunc()
	{
		if (m_strOutVar.empty()) return;

		std::string strOutVar = m_strOutVar;											//输出变量
		if (!strOutVar.empty())
		{
			if(strOutVar.substr(strOutVar.size()-1,1) == ",")
			{
				strOutVar = strOutVar + m_ModelConditionId;
			}
			else
			{
				strOutVar = strOutVar + "," + m_ModelConditionId;
			}
		}
		else
		{
			strOutVar = "," + m_ModelConditionId;
		}

		m_strOutVar = strOutVar;

		strOutVar=m_strOutVarFun;
		if (!strOutVar.empty()&&strOutVar.substr(0,1) != ",")
		{
			strOutVar = "," + strOutVar;
			m_strOutVarFun=strOutVar;
		}
		m_strOutVarAndFun=m_strOutVar+m_strOutVarFun;
		strOutVar=m_strOutVarAndFun;
		//数据库中存放的是 "@"格式的 要转换成 "_"格式
		//将指标本身也作为外部变量加入到外部变量串中，防止公式中引用了自己的指标
		//（这种情况下，保证指标的计算顺序，解析dll将指标本身在变量串中去掉了）在计算时出错
		strOutVar = PubOpt::StringOpt::StringReplace(strOutVar,"@","_");

		m_strTranOutVarFun = strOutVar;
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
		std::string strOutVarFunc = m_strOutVarAndFun;
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
				if(!strICode.empty()) m_OutFuncVarArray.push_back(strICode);
			}
		}

		std::string strTemp = m_strTranOutVarFun;
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

			m_strTranOutVarFun = strTemp; //外部函数变量+外部变量
			strTemp.clear();
		}
	}
};

typedef std::map<std::string, DataValueInfo *>		MapStringToMDataValueInfo;
typedef MapStringToMDataValueInfo::iterator			MapStringToMDataValueInfo_It;

typedef std::map<std::string, ModelCondition *>		MapStringToModeCond;
typedef MapStringToModeCond::iterator			MapStringToModeCond_It;


struct PointGroup
{
	PointGroup()
	{
		m_ValueType = 0;
		m_ValueNum = 0;
		m_JkdValue = 0;
	}
	~PointGroup()
	{
		std::map<std::string, DataValueInfo *>::iterator it = mMapGroupPoint.begin();
		for (;it!=mMapGroupPoint.end();++it)
		{
			delete it->second;
		}
		mMapGroupPoint.clear();
	}
	std::string m_Group;        //参数类Id
	std::string m_GroupJkd;    //参数类健康度Id
	int         m_ValueType;   //取值方式类别(0: 中值 1:最小值(去尾))
	int         m_ValueNum;	   //去尾个数
	double      m_JkdValue;     //参数类健康度值
	bool		mRtdbGroupJkdIsExist;  //参数类健康度是否存在
	double		m_GroupWeight;  //参数类权重
	std::map<std::string, DataValueInfo *>  mMapGroupPoint;   //参数类测点集合
	//std::vector<std::string>				mVectorPoint;	  //参数分类下所有参数名集合
	std::vector<double>		mVectorAValues;  //模型参数类测点健康度集合
};
typedef std::map<std::string , PointGroup*>		MapStringToPointGroup;
typedef MapStringToPointGroup::iterator			MapStringToPointGroup_It;

typedef std::map<std::string,DataInfo*>			MapStringToPointData;
typedef MapStringToPointData::iterator			MapStringToPointData_It;
struct DataMode
{
public:
	
        DataMode(void)
        {
            mModeId="";
            mSimPoint="";
            mSimSource="";
			mCondId = "";
			mCondIdSource = "";
            mDModeSim=0;
			mCondValue = -1;
            mRtdbModleConIsWrite = true;
			mRtdbSimModleIsWrite = true;
            m_IsDeal = false;
			m_IsCalOk = false;
        }
        virtual ~DataMode()
        {
            /*for (MapStringToMDataValueInfo::iterator it=mMapModePoint.begin();it!=mMapModePoint.end();++it)
            {
               delete it->second;
            }
            mMapModePoint.clear();*/
            mVectorPValues.clear();
			for (MapStringToModeCond::iterator it=mMapModeCond.begin();it!=mMapModeCond.end();++it)
			{
				delete it->second;
			}
			mMapModeCond.clear();
			for (MapStringToPointGroup_It it = mMapGroup.begin();it!=mMapGroup.end();++it)
			{
				delete it->second;
			}
			for (MapStringToPointData_It it = mMapModePoint.begin();it != mMapModePoint.end();++it)
			{
				delete it->second;
			}
			mMapModePoint.clear();
			mMapGroup.clear();
        }
public:
    std::string                 mModeId;    
	std::string                 mCondId;			//当前满足模式ID
	std::string                 mCondIdSource;			//模式回写ID
	double						mCondValue;			//模式值
	std::string                 mStatus;		   //模型启停ID
	std::string                 mStatusSource;	  //模型启停回写实时数据库ID
    std::string                 mSimPoint;         //模型健康度点名
    std::string                 mSimSource;			 //模型健康度回写实时数据库点名
	double						mSimLimit;           //模型当前满足的健康度限值
    double                      mDModeSim;           //模型健康度值
	double                      mDModeWeight;       //模型权重值
	bool						mIsSimAlarm;		//模型健康度告警

	bool						mRtdbModleConIsWrite;//模型模式值是否回写实时数据库
    bool						mRtdbSimModleIsWrite;	//健康度是否回写实时数据库
    bool                        m_IsDeal;               //是否满足计算条件
	bool						m_IsCalOk;				//是否计算成功
    //MapStringToMDataValueInfo   mMapModePoint;        //模型测点集合
    //std::map<std::string, DataValueInfo *>  mMapModePoint;   //模型测点集合
	std::map<std::string,DataInfo*> mMapModePoint;   //模型测点集合
    std::vector<double>			mVectorPValues;  //模型测点值集合
	std::vector<VarParam>		mVectorParamCfgs;  //模型测点计算健康度依赖的可变参数a配置集合
	std::map<std::string,std::vector<VarParam>> mMapCondParamCfgs;
	std::map<std::string, ModelCondition *>  mMapModeCond;  //模型模式条件

	std::vector<std::string>    mCondPointVector;			//模型模式条件引用的测点集合
	std::map<std::string , PointGroup*>  mMapGroup;

	

};
typedef std::map<std::string,std::vector<VarParam>>          MapStringToCondParamCfgs;
typedef MapStringToCondParamCfgs::iterator		        MapStringToCondParamCfgs_It;
struct SysCfg
{
	SysCfg()
	{
		mSysWeight = 0 ;
		mSysJkdValue = 0;
		mSysDfhValue = 0;
	};
	virtual ~SysCfg()
	{
		for (std::map<std::string,DataMode*>::iterator it= mMapModles.begin();it!=mMapModles.end();++it)
		{
			delete it->second;
		}
		mMapModles.clear();
		for (std::map<std::string,Dfhnl*>::iterator it = mMapSysDfhnl.begin();it!=mMapSysDfhnl.end();++it)
		{
			delete it->second;
		}
		mMapSysDfhnl.clear();
	}
    std::string							mSys;			     //系统ID
    std::string							mSysJkd;		     //系统健康度id
	bool								mRtdbSysJkdIsExist;  //系统健康度是否存在
	double								mSysJkdValue;
    double								mSysWeight;		     //系统权重
    std::string							mSysDfh;		     //系统带负荷id
	bool								mRtdbSysDfhIsExist;  //系统带负荷能力是否存在
	double								mSysDfhValue;
    std::map<std::string,DataMode*>		mMapModles;          //系统下所有模型配置集合
    std::map<std::string,Dfhnl*>        mMapSysDfhnl;	     //系统带负荷能力配置集合

};
typedef std::map<std::string,Dfhnl*>	MapStringToDfhnl;
typedef MapStringToDfhnl::iterator      MapStringToDfhnl_It;
struct  SetCfg
{
	SetCfg()
	{
		mSetDefFh  = 0;
		mSetJkdValue = 0;
	}
	virtual ~SetCfg()
	{
		for (std::map<std::string,SysCfg*>::iterator it = mMapSys.begin();it!=mMapSys.end();++it)
		{
			delete it->second;
		}
		mMapSys.clear();
	}
    std::string							mSet;			     //机组ID
    std::string							mSetCode;			 //机组号
    std::string							mSetJkd;		     //机组健康度id
	bool								mRtdbSetJkdIsExist;  //机组健康度是否存在
	double								mSetJkdValue;
    std::string							mSetDfh;		     //机组带负荷id
	bool								mRtdbSetDfhIsExist;  //机组带负荷能力是否存在
    double								mSetDfhValue;        //机组带负荷能力值
    double								mSetDefFh;		     //机组额定功率
    double								mSetRfFh;		     //机组实时负荷
    std::string							mSetFh;		         //机组实时负荷id
    std::string							mSetTJ;		         //机组开停机指标id
    std::map<std::string,SysCfg*>		mMapSys;             //机组下所有系统配置集合
};

struct PublicDate
{
	std::string						m_perId;//上次的前一次ID
	std::string						m_perIdBack;//上次的前一次ID的备份，便于记录提交失败后回滚
	std::string						m_lastId;//上次记录ID
	std::string						m_id;	//本次记录ID
	int								m_perValue;//上次的前一次值
	int								m_perValueBack;//上次的前一次值的备份，便于记录提交失败后回滚
	int								m_lastValue;//上一次的值
	int								m_curValue;//当前值
    double                          m_alarmScore;   //本条记录得分 （分类、模型、系统、机组特有）
	double                          m_alarmLastScore;//上条记录得分
	int								m_alarmType;    //报警类型 0：正常 1：原始值报警 2偏差值报警 3健康度报警 4混合报警
	int								m_lastAlarmType;    //上次报警类型 0：正常 1：原始值报警 2偏差值报警 3健康度报警 4混合报警

	int								m_LastPcValue;//上次偏差值
	int								m_PcValue;//偏差值
	long							m_Time;//计算时间
	long							m_StartTime;//开始时间
	long							m_EndTime;//结束时间
	long							m_TimeLong;//持续时间

	long							m_LastStartTime;//上次开始时间
	long							m_LastEndTime;//上次结束时间
	double							m_LastTimeLong;//上次持续时间
	long							m_perStartTime;//上次的前一次开始时间
	long							m_perEndTime;//上次的前一次结束时间
	long							m_perStartTimeBack;//上次的前一次开始时间的备份，便于记录提交失败后回滚
	long							m_perEndTimeBack;//上次的前一次结束时间的备份，便于记录提交失败后回滚
	long							m_perTimeLong;//上次的前一次
	int								m_deaBand;		//死区记录时间
	int								m_count;		//记录计数
	bool							m_lastisInto;		//上条记录是否插入新记录
	bool							m_isInto;		//本条记录是否插入新记录
	bool							m_lastisIntoBack;		//上条记录是否插入新记录的备份，便于记录提交失败后回滚
	bool							m_isIntoBack;		//本条记录是否插入新记录的备份，便于记录提交失败后回滚
	bool							m_init;        //新告警
	bool							m_initBack;        //新告警的备份，便于记录提交失败后回滚
public:
	PublicDate()
	{
		m_LastTimeLong = 0;
		m_TimeLong = 0;
		m_alarmLastScore = 0;
		m_alarmScore = 0;
		m_curValue = 0;
		m_lastValue = 0;
		m_LastPcValue = 0;
		m_PcValue = 0;
		m_deaBand = 120;
		m_count = 0;
		m_alarmType = 0;
		m_lastAlarmType = 0;
		m_lastisInto = true;
		m_isInto = true;
		m_init   = true;
	}
	void DataDeal(bool first,bool isChangeContion,int bandTime,const long calTime)
	{
		long tlong = 0;
		m_Time = calTime;
		m_deaBand = bandTime;
		if(first)
		{
            m_id = Util::GetGUID();
            m_lastId = Util::GetGUID();
			m_StartTime = m_Time;
			m_EndTime = m_Time;
			m_TimeLong = m_EndTime-m_StartTime;
			m_LastStartTime = m_StartTime;
			m_LastEndTime = m_Time;
			m_LastTimeLong = m_LastEndTime-m_LastStartTime;
			//m_deaBand = bandTime;
		}
		else
		{
			if (m_lastValue==m_curValue)//本次和上一次状态相同
			{
				m_EndTime = m_Time;
				m_TimeLong = m_EndTime-m_StartTime;
				if (isChangeContion)
				{
					m_lastId = m_id;
                    m_id = Util::GetGUID();

					m_LastStartTime = m_StartTime;
					m_LastEndTime = m_Time;
					m_LastTimeLong = m_LastEndTime-m_LastStartTime;
					m_StartTime = m_Time;
					m_EndTime = m_Time;
					m_TimeLong = 0;

					m_lastisInto = m_isInto;
					m_isInto = true;
				}

			}
			else//本次和上一次状态不相同
			{
				if(m_lastValue*m_curValue > 0)
				{
					m_EndTime = m_Time;
					m_TimeLong = m_EndTime-m_LastStartTime;
					m_LastStartTime = m_StartTime;
					m_LastEndTime = m_Time;
					m_LastTimeLong = m_LastEndTime-m_LastStartTime;
					if (isChangeContion)
					{
						m_lastId = m_id;
                        m_id = Util::GetGUID();

						m_LastStartTime = m_StartTime;
						m_LastEndTime = m_Time;
						m_LastTimeLong = m_LastEndTime-m_LastStartTime;
						m_StartTime = m_Time;
						m_EndTime = m_Time;
						m_TimeLong = 0;

						m_lastisInto = m_isInto;
						m_isInto = true;
						m_init = true;
					}
					else
					{
						if (m_LastTimeLong<m_deaBand)
						{
							m_lastValue = m_curValue = m_lastValue>m_curValue?m_lastValue:m_curValue;
						}
						else
						{
							m_lastId = m_id;
                            m_id = Util::GetGUID();

							m_LastStartTime = m_StartTime;
							m_LastEndTime = m_Time;
							m_LastTimeLong = m_LastEndTime-m_LastStartTime;
							m_StartTime = m_Time;
							m_EndTime = m_Time;
							m_TimeLong = 0;

							m_lastisInto = m_isInto;
							m_isInto = true;
							m_init = true;
						}
					}
				}
				else
				{
					tlong = m_LastEndTime-m_LastStartTime;

					m_lastId = m_id;
                    m_id = Util::GetGUID();

					m_LastStartTime = m_StartTime;
					m_LastEndTime = m_Time;
					m_LastTimeLong = m_LastEndTime-m_LastStartTime;
					m_StartTime = m_Time;
					m_EndTime = m_Time;

					m_TimeLong = 0;

					m_lastisInto = m_isInto;
					m_isInto = true;
					m_init = true;
				}
			}
		}

		m_isIntoBack = m_isInto;
		m_lastisIntoBack = m_lastisInto;
		m_perIdBack = m_perId;
		m_perValueBack = m_perValue;
		m_perStartTimeBack = m_perStartTime;
		m_perEndTimeBack = m_perEndTime;
		m_initBack = m_init;
	}
};


struct PublicConditionDate
{
	std::string						m_perId;//上次的前一次ID存入数据的最后一条记录的ID
	std::string						m_perIdBack;//上次的前一次ID的备份，便于记录提交失败后回滚
	std::string						m_lastId;//上次记录ID
	std::string						m_id;	//本次记录ID
	std::string						m_perValue;//上次的前一次值
	std::string						m_perValueBack;//上次的前一次值的备份，便于记录提交失败后回滚
	std::string						m_lastValue;//上一次的值
	std::string						m_curValue;//当前值

	long							m_Time;//计算时间
	long							m_StartTime;//开始时间
	long							m_EndTime;//结束时间
	long							m_TimeLong;//持续时间

	long							m_LastStartTime;//上次开始时间
	long							m_LastEndTime;//上次结束时间
	double							m_LastTimeLong;//上次持续时间
	double							m_xsd;//存入数据的最后一条记录的健康度
	double							m_lastxsd;//上个计算周期的健康度
	double							m_curxsd;//本计算周期的健康度
	long							m_perStartTime;//上次的前一次开始时间
	long							m_perEndTime;//上次的前一次结束时间
	long							m_perStartTimeBack;//上次的前一次开始时间的备份，便于记录提交失败后回滚
	long							m_perEndTimeBack;//上次的前一次结束时间的备份，便于记录提交失败后回滚
	long							m_perTimeLong;//上次的前一次
	int								m_deaBand;		//死区记录时间
	int								m_count;		//记录计数
	bool							m_lastisInto;	//上条记录是否插入新记录
	bool							m_isInto;		//本条记录是否插入新记录
	bool							m_lastisIntoBack;		//上条记录是否插入新记录的备份，便于记录提交失败后回滚
	bool							m_isIntoBack;		//本条记录是否插入新记录的备份，便于记录提交失败后回滚
	bool							m_isChange;         //匹配度是否一样 true：一样 false： 不一样 
	bool							m_isPPDChange;      //上周期和本周期状态相同的特殊情况下本周期认为是新纪录标识符
	bool							m_isCalCycOk;       //本计算周期是否没有匹配到可插入记录 true：没有匹配 false：匹配到
public:
	PublicConditionDate()
	{
		m_curValue = "";
		m_lastValue = "";
		m_perValue = "";
		m_deaBand = 120;
		m_count = 0;
		m_LastTimeLong = 0;
		m_TimeLong = 0;
		m_lastisInto = true;
		m_isInto = true;
		m_isChange = false;
		m_isPPDChange = false;
		m_isCalCycOk = false;
		m_lastxsd = 0;
		m_curxsd = 0;
		m_xsd  = 0;
	}
	void DataDeal(bool first,int bandTime,const long calTime)
	{
		long tlong = 0;
		m_Time = calTime;
		m_deaBand = bandTime;
		if(first)
		{
			m_lastisInto = false;
			m_isInto = false;
            m_id = Util::GetGUID();
            m_lastId = Util::GetGUID();
			m_StartTime = m_Time;
			m_EndTime = m_Time;
			m_TimeLong = m_EndTime-m_StartTime;

			m_LastStartTime = m_StartTime;
			m_LastEndTime = m_Time;
			m_LastTimeLong = m_LastEndTime-m_LastStartTime;
			if (m_isChange)
			{
				m_lastisInto = m_isInto;
				m_isInto=true;
				m_isChange = false;
			}
			//m_deaBand = bandTime;
		}
		else
		{
			if (m_lastValue==m_curValue)//本次和上一次状态相同
			{
				if (m_isChange)     //&&(!m_isInto)
				{
					m_lastId = m_id;
                    m_id = Util::GetGUID();

					m_LastStartTime = m_StartTime;
					m_LastEndTime = m_Time;
					m_LastTimeLong = m_LastEndTime-m_LastStartTime;
					m_StartTime = m_Time;
					//m_StartTime = m_EndTime;
					m_EndTime = m_Time;
					m_TimeLong = 0;

					m_lastisInto = m_isInto;
					m_isInto = true;
					m_isPPDChange = true;
					m_isChange = false;
				}
				m_EndTime = m_Time;
				m_TimeLong = m_EndTime-m_StartTime;

			}
			else//本次和上一次状态不相同
			{
				m_LastStartTime = m_StartTime;
				m_LastEndTime = m_Time;
				m_LastTimeLong = m_LastEndTime-m_LastStartTime;
				m_StartTime = m_Time;
				//m_StartTime = m_EndTime;
				m_EndTime = m_Time;
				m_TimeLong = 0;
				m_lastisInto = m_isInto;
				tlong = m_LastEndTime-m_LastStartTime;
				if (m_isChange)
				{
					m_lastId = m_id;
                    m_id = Util::GetGUID();

					//m_LastStartTime = m_StartTime;
					//m_LastEndTime = m_Time;
					//m_LastTimeLong = m_LastEndTime-m_LastStartTime;
					//m_StartTime = m_Time;
					////m_StartTime = m_EndTime;
					//m_EndTime = m_Time;
					//m_TimeLong = 0;
					m_lastisInto = m_isInto;
					m_isInto = true;
					m_isChange = false;
				}
				/*else
					m_TimeLong = m_EndTime-m_StartTime;*/
			}
		}

		m_isIntoBack = m_isInto;
		m_lastisIntoBack = m_lastisInto;
		m_perIdBack = m_perId;
		m_perValueBack = m_perValue;
		m_perStartTimeBack = m_perStartTime;
		m_perEndTimeBack = m_perEndTime;
	}
	void DataDealConsine(bool first,int bandTime,const long calTime,const double xsd)
	{
		m_Time = calTime;
		if(first)
		{
            m_id = Util::GetGUID();
            m_lastId = Util::GetGUID();
			m_StartTime = m_Time;
			m_EndTime = m_Time;
			m_TimeLong = m_EndTime-m_StartTime;

			m_LastStartTime = m_StartTime;
			m_LastEndTime = m_Time;
			m_LastTimeLong = m_LastEndTime-m_LastStartTime;
			m_lastxsd = m_curxsd;

			if (m_isChange)
			{
				/*m_lastxsd = m_curxsd;*/
				m_curxsd = xsd;

				m_lastisInto = m_isInto;
				m_isInto=true;
				m_isChange = false;
			}
			m_deaBand = bandTime;
		}
		else
		{
			m_lastxsd = m_curxsd;

			if (m_lastValue==m_curValue)//本次和上一次状态相同
			{
				if (m_isChange)     //&&(!m_isInto)
				{
					m_lastId = m_id;
                    m_id = Util::GetGUID();

					m_LastStartTime = m_StartTime;
					m_LastEndTime = m_Time;
					m_LastTimeLong = m_LastEndTime-m_LastStartTime;
					m_StartTime = m_Time;
					m_EndTime = m_Time;
					m_TimeLong = 0;
					m_isPPDChange = true;
					m_isChange = false;
					m_lastisInto = m_isInto;
					m_isInto = true;
					/*m_lastxsd = m_curxsd;*/
					m_curxsd = xsd;
				}
				m_EndTime = m_Time;
				m_TimeLong = m_EndTime-m_StartTime;

			}
			else//本次和上一次状态不相同
			{
				m_LastStartTime = m_StartTime;
				m_LastEndTime = m_Time;
				m_LastTimeLong = m_LastEndTime-m_LastStartTime;
				m_StartTime = m_Time;
				m_EndTime = m_Time;
				m_TimeLong = 0;
				m_lastisInto = m_isInto;
				m_isInto = true;
				//if (m_isChange)
				//{
					m_lastId = m_id;
                    m_id = Util::GetGUID();
					//m_isChange = false;
				//}
				/*m_lastxsd = m_curxsd;*/
				m_curxsd = xsd;
			}
		}
		m_isIntoBack = m_isInto;
		m_lastisIntoBack = m_lastisInto;
		m_perIdBack = m_perId;
		m_perValueBack = m_perValue;
		m_perStartTimeBack = m_perStartTime;
		m_perEndTimeBack = m_perEndTime;
	}
};


//typedef std::map<std::string, DataMode *>		MapStringToDataMode;
//typedef MapStringToDataMode::iterator			MapStringToDataMode_It;

struct PointInfo
{
	std::string strCode;    //点名
	double      dValue;     //点值
};

struct CMonmentDatas 
{
public:
	~CMonmentDatas()
	{
		clean();
	}
	void clean()
	{
		std::map<std::string,PointInfo*>::iterator it;
		it = m_mapPointInfo.begin();
		for (;it!=m_mapPointInfo.end();++it)
		{
			delete it->second;
		}
		m_mapPointInfo.clear();
	}
	bool                m_isOk;                      //是否取到数据
	std::string			m_strTimeStamp;				//时间片标记
	long                lTimeStamp;	
	int                 m_iNum;						//时间顺序编号
	std::map<std::string,PointInfo*>			m_mapPointInfo;				//该时间片所有点值
};
typedef  std::map<std::string,PointInfo*>		MapMonmentPoint;
typedef  MapMonmentPoint::iterator				MapMonmentPoint_It;
typedef  MapMonmentPoint::const_iterator		MapMonmentPoint_const_It;
typedef  std::map<long,CMonmentDatas*>			MapMonmentDatas;
typedef MapMonmentDatas::iterator				MapMonmentDatas_It;
typedef MapMonmentDatas::const_iterator			MapMonmentDatas_const_It;





#endif 
 

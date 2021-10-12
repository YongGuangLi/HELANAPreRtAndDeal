/*******************************************************************************
* Copyright��C��,2016-2020,DTXY Tech .Co.Ltd;
* �� �� ��: PubSetInfo.h
* �ļ�����: ���鵽���澯�ṹ�������ü�������
*  ��  �� : %����%��
* ��������: 2016-10-25 10:08:08
*******************************************************************************/

#ifndef __PUBSETINFO_H__
#define __PUBSETINFO_H__
#include "Util.h"
#include "DataValueInfo.h"
#include <math.h>

//�澯�÷���������
struct AlarmScore
{
	std::string     mStrKey;
	int				mAlarmLevel;
	double			mAlarmScore;
	double			mUpper;
	double			mLower;
};
//���澯����
struct AlarmPointZone  
{
	std::string			mStrZoneID;			//���������
	int					mIAlarmType;			//�澯����(0:ƫ��ֵ�澯 1:ʵ��ֵ�澯)
	int					mIAlarmLevel;			//�澯����
	double				mDAlarmLower;			//�澯����
	double				mDAlarmUpper;			//�澯����
	bool                mLowExist;              //�澯�����Ƿ���� true������ false��������
	bool                mUperExist;				//�澯�����Ƿ���� true������ false��������

};
// ���
struct AlarmPointInfo
{
	std::string   mStrPointId;
	double        mDcurValue;     //ԭʼֵ
	double        mDpreValue;	  //����ֵ
	double        mDsim;          //��㽡����ֵ
	bool		  mIsGetPreVale;//����ֵ�Ƿ�ȡ��
	bool          mIsGetCurVale;//ԭʼֵ�Ƿ�ȡ��
	bool		  mIsGetSimVale;//�������Ƿ�ȡ��
	bool		  mIsInitPreVale;//����ֵ�Ƿ�ȡ��
	bool          mIsInitCurVale;//ԭʼֵ�Ƿ�ȡ��
	bool		  mIsInitSimVale;//�������Ƿ�ȡ��
	PublicDate	  mDate;
	int           miBand;   //����ʱ��
	double		  m_minValue;    //�澯ʱ�����Сֵ
	double		  m_maxValue;    //�澯ʱ������ֵ
	double		  m_avgValue;    //�澯ʱ���ƽ��ֵ
	double		  m_pminValue;    //�澯ʱ�������ֵ��Сֵ
	double		  m_pmaxValue;    //�澯ʱ�������ֵ���ֵ
	double		  m_pavgValue;    //�澯ʱ�������ֵƽ��ֵ
	double		  m_savgValue;    //�澯ʱ��ν�����ƽ��ֵ
	int			  m_iCount;	   //�澯������ȡ������ͳ�ƴ���

	std::vector<AlarmPointZone>   mVectZone;	//���澯���伯��

	AlarmPointInfo()
	{
		mIsInitPreVale = false;
		mIsInitCurVale = false;
		mIsInitSimVale = false;
		m_minValue = 0;    
		m_maxValue = 0;
		m_avgValue = 0;
		m_pminValue = 0;
		m_pmaxValue = 0;
		m_pavgValue = 0;
		m_savgValue = 0;
		mDcurValue = 0;
		mDpreValue = 0;
		mDsim = 0;
		if(0!=mVectZone.size())
			clear();
	}
	~AlarmPointInfo()
	{
		clear();
	}
private:
	void clear()
	{
		mVectZone.clear();
	}
};
typedef std::map<std::string,AlarmPointInfo *> MapStringToAlarmPointInfo;
typedef	MapStringToAlarmPointInfo::iterator    MapStringToAlarmPointInfo_It;
struct AlaramModelGroup
{
	std::string							mStrGroupId;
	PublicDate							mDate;
	int									miBand;   //����ʱ��
	double								mWeight;  //Ȩ��
	std::map<std::string,AlarmPointInfo *>   mapPointInfo;

	AlaramModelGroup()
	{

	}
	~AlaramModelGroup()
	{
		clear();
	}
	void clear()
	{
		MapStringToAlarmPointInfo_It it=mapPointInfo.begin();
		for (;it!=mapPointInfo.end();++it)
		{
			if (NULL!=it->second)
			{
				delete it->second;
				it->second=NULL;
			}
		}
		mapPointInfo.clear();
	}
};
typedef std::map<std::string,AlaramModelGroup *> MapStringToAlaramModelGroup;
typedef	MapStringToAlaramModelGroup::iterator    MapStringToAlaramModelGroup_It;
typedef	MapStringToAlaramModelGroup::const_iterator   MapStringToAlaramModelGroupConst_It;

struct CDCosine
{
public:
	std::string			mId;
	std::string			mName;
	std::string			mCauses;
	std::string			mAnalye;
	std::string			mGuid;
	bool				isMok;
	double				mPValue;
	double				mMoValue;
	std::map<std::string , int>	mMapCosine;
	//PublicDate		mDate;
public:
	CDCosine()
	{
		isMok=true;
		mMoValue = 0;
		mPValue = 0;
	}
	~CDCosine()
	{
		mMapCosine.clear();
	}
	bool StringSplit(const std::string &strSrc,const std::string &strSplit)
	{
		if (strSplit.empty()||strSrc.empty())
		{
			return false;
		}
		double dValue;
		std::string strSrcBak = strSrc;
		std::string strPoints,strValues,strp,strv;
		size_t siFind = 0;
		siFind = strSrcBak.find(strSplit);
		if (std::string::npos == siFind)
			return false;
		strPoints.clear();
		strValues.clear();
		strPoints= strSrcBak.substr(0, siFind);
		strValues= strSrcBak.substr(siFind+1,strSrcBak.length()-siFind-1);
		if(','!= strPoints.at(strPoints.length()-1)) strPoints +=",";
		if(','!= strValues.at(strValues.length()-1)) strValues +=",";
		if(strPoints.empty()||strValues.empty()) 
		{
			return false;
		}
		while(!strPoints.empty())
		{
			siFind = strPoints.find(",");
			strp= strPoints.substr(0, siFind);
			strPoints = strPoints.substr(siFind+1);
			siFind = strValues.find(",");
			strv= strValues.substr(0,siFind);
			strValues = strValues.substr(siFind+1);

			dValue = Util::CharPointerConvert2Number<double>(strv.c_str());
			mMapCosine.insert(make_pair(strp,dValue));
			mMoValue+= pow(dValue,2);
		}
		mMoValue= sqrt(mMoValue);
		return true;
	}
};
typedef std::map<std::string ,CDCosine *>    MapStringToAlaramCosine;
typedef MapStringToAlaramCosine::iterator    MapStringToAlaramCosine_It;
struct CDCosineCfg
{
public:
	std::string			mId;
	std::string			mName;
	std::string			mCauses;
	std::string			mAnalye;
	std::string			mGuid;
};
typedef std::map<std::string ,CDCosineCfg *>    MapStringToAlaramCosineCfg;
typedef MapStringToAlaramCosineCfg::iterator    MapStringToAlaramCosineCfg_It;
struct AlarmModel
{

public:
	std::string					mstrModelId;
	std::string					mstrSn;
	std::string					mCondId;			//��ǰ�����ģʽID
	PublicDate					mDate;
	PublicConditionDate			mCondtionDate;		//ģʽ��¼����

	std::string					mLastCosineId;  //��������cosineId
	std::string					mCosineId;  //����cosineId
	PublicConditionDate			mCosineDate;	//���϶�λ��¼����
	CDCosine*					mConsine;       //��ǰ����Ĺ��ϵ���������
	double						mXsd;
	double						mSumAlram;  //�������������в���cosine����ֵƽ�����ٿ�ƽ��
	double						mLastSumAlram;  //�������������в���cosine����ֵƽ�����ٿ�ƽ��
	double						mDevPPD;    //�ϸ��������ںͱ����ڲ��澯���е�ƥ���
	double						mDevFabsSum; //�ϸ��������ڲ��ƫ��ֵ�ľ���ֵ�ͱ��������ڶ�Ӧ���ƫ��ֵ�ľ���ֵ��˺����ܺ�

	bool						m_IsChangeCondition;
	int							miBand;   //����ʱ��
	double						mWeight;  //Ȩ��
	//DataMode	mode_info;
	//MethodAvg	mode_fun;
	bool						mIsDeal;	//ģ���Ƿ��� true ������ false ��������  
	double						mdSimLimit;
	bool						mIsSimAlarm;
	MapStringToAlaramModelGroup mapAlarmGroup;
	MapStringToAlaramCosine		mapAlarmCosine;
public:
	AlarmModel()
	{
		mLastCosineId = NO_ALARM;
		mCosineId = NO_ALARM;
		mSumAlram= 0;
		mLastSumAlram = 0;
		mDevPPD = 0;
		mDevFabsSum = 0;
		mWeight= 0;
		miBand= 1;
		mIsDeal= false;
	}
	~AlarmModel()
	{
		clear();
	}
	void clear()
	{
		MapStringToAlaramModelGroup_It it=mapAlarmGroup.begin();
		for (;it!= mapAlarmGroup.end();++it)
		{
			if (NULL!= it->second)
			{
				delete it->second;
				it->second= NULL;
			}
		}
		mapAlarmGroup.clear();
		MapStringToAlaramCosine_It it_consine= mapAlarmCosine.begin();
		for (;it_consine!= mapAlarmCosine.end();++it_consine)
		{
			if (NULL!= it_consine->second)
			{
				delete it_consine->second;
				it_consine->second = NULL;
			}
		}
		mapAlarmCosine.clear();
	}
};
typedef std::map<std::string, AlarmModel *>		    MapStringToAlarmModel;
typedef MapStringToAlarmModel::iterator			    MapStringToAlarmModel_It;


struct AlarmSetSys
{
public:
	AlarmSetSys()
	{
		mSys="";
		miBand=0;
	}
	virtual ~AlarmSetSys()
	{
		clear();
	}
public:
	std::string mSys;
	PublicDate  mDate;
	int         miBand;   //����ʱ��
	double      mWeight;  //Ȩ��
	std::map<std::string, AlarmModel *>	 mapAlarmMode;      //ϵͳ�µ�ģ�ͼ���
	std::map<std::string,Dfhnl*>          mapDfhnl;			//�������������ü���
private:
	void clear()
	{
		std::map<std::string, AlarmModel *>::iterator	 it=mapAlarmMode.begin();
		for (;it!= mapAlarmMode.end();++it)
		{
			if (NULL!= it->second)
			{
				delete it->second;
				it->second=NULL;
			}
		}
		mapAlarmMode.clear();

		std::map<std::string,Dfhnl*> ::iterator it_dfh = mapDfhnl.begin();
		for (;it_dfh!=mapDfhnl.end();++it_dfh)
		{

			if (NULL!= it_dfh->second)
			{
				delete it_dfh->second;
				it_dfh->second=NULL;
			}
		}
		mapDfhnl.clear();
	}

};
typedef std::map<std::string, AlarmSetSys *>		        MapStringToAlarmSetSys;
typedef MapStringToAlarmSetSys::iterator			        MapStringToAlarmSetSys_It;
struct AlarmSetInfo
{
public:
	AlarmSetInfo(void)
	{
		mSet="";
		miBand=0;
	}
	~AlarmSetInfo(void)
	{
		clear();
	}

public:
	std::string mSet;
	PublicDate  mDate;
	int         miBand;   //����ʱ��
	MapStringToAlarmSetSys mapSys;    //����ϵͳ����
	void clear()
	{
		MapStringToAlarmSetSys_It it= mapSys.begin();
		for (;it!= mapSys.end();++it)
		{
			if (NULL!= it->second)
			{
				delete it->second;
				it->second=NULL;
			}
		}
		mapSys.clear();
	}
};
typedef std::map<std::string, AlarmSetInfo *>		    MapStringToAlarmSetInfo;
typedef MapStringToAlarmSetInfo::iterator			    MapStringToAlarmSetInfo_It;

typedef std::vector<AlarmScore >                       VectorAlarmScore;
typedef VectorAlarmScore::iterator					   VecetorAlarmScore_It;

struct AlarmPointRst
{
	std::string   mStrModelId;		
	std::string   mStrGroupId;
	std::string   mStrCondId;
	std::string   mStrPointId;
	double        mDcurValue;     //ԭʼֵ
	double        mDpreValue;	  //����ֵ
	double        mDsim;          //��㽡����ֵ
	bool		  mIsGetPreVale;//����ֵ�Ƿ�ȡ��
	bool          mIsGetCurVale;//ԭʼֵ�Ƿ�ȡ��
	bool		  mIsGetSimVale;//�������Ƿ�ȡ��
	bool		  mIsInitPreVale;//����ֵ�Ƿ�ȡ��
	bool          mIsInitCurVale;//ԭʼֵ�Ƿ�ȡ��
	bool		  mIsInitSimVale;//�������Ƿ�ȡ��
	PublicDate*	  mDate;
	//int           miBand;   //����ʱ��
	double		  m_minValue;    //�澯ʱ�����Сֵ
	double		  m_maxValue;    //�澯ʱ������ֵ
	double		  m_avgValue;    //�澯ʱ���ƽ��ֵ
	double		  m_pminValue;    //�澯ʱ�������ֵ��Сֵ
	double		  m_pmaxValue;    //�澯ʱ�������ֵ���ֵ
	double		  m_pavgValue;    //�澯ʱ�������ֵƽ��ֵ
	double		  m_savgValue;    //�澯ʱ��ν�����ƽ��ֵ

	AlarmPointRst()
	{
		mIsGetPreVale = false;
		mIsGetCurVale = false;
		mIsGetSimVale = false;
		mIsInitPreVale = false;
		mIsInitCurVale = false;
		mIsInitSimVale = false;
		mStrCondId = "";
		m_minValue = 0;    
		m_maxValue = 0;   
		m_avgValue = 0;    
		m_pminValue = 0;    
		m_pmaxValue = 0;    
		m_pavgValue = 0;   
		m_savgValue = 0;
		mDcurValue = 0;
		mDpreValue = 0;
		mDsim = 0;
	}
};

struct  AlarmGrouRst
{
	std::string					mStrGroupId;
	PublicDate*					mDate;
	//int							miBand;   //����ʱ��
};
struct  AlarmModeltoSetRst
{
	std::string					mStrId;             //ģ��id��ϵͳid�����id
	PublicDate*					mDate;
	//int							miBand;   //����ʱ��
};
struct  AlarmModelConditionRst
{
	std::string					mModelIdTest;//������ʱ	
	std::string					mCondId;			//��ǰ�����ģʽID
	PublicConditionDate*		mCondtionDate;
	//int							miBand;   //����ʱ��
};
struct  AlarmModelCosineRst
{
	std::string					mStrModelId;
	std::string					mstrSn;
	std::string					mLastCosineId;  //��������cosineId
	std::string					mCosineId;  //����cosineId
	PublicConditionDate*		mCosineDate;	//���϶�λ��¼����
	CDCosine*					mConsine;
	//CDCosine*					mlastConsine;
	MapStringToAlaramCosineCfg	mapRlstAlarmCosineCfg;
	//int							miBand;   //����ʱ��
	double						mXsd;
	AlarmModelCosineRst()
	{
		mXsd = 0;
	}
	~AlarmModelCosineRst()
	{
		for (MapStringToAlaramCosineCfg_It it = mapRlstAlarmCosineCfg.begin();it != mapRlstAlarmCosineCfg.end();++it)
		{
			delete it->second;
		}
		mapRlstAlarmCosineCfg.clear();
	}
};
typedef std::map<std::string,AlarmPointRst *>			MapStringToAlarmPointRst;
typedef MapStringToAlarmPointRst::iterator				MapStringToAlarmPointRst_It;
typedef std::map<std::string,AlarmGrouRst *>			MapStringToAlarmGrouRst;
typedef MapStringToAlarmGrouRst::iterator				MapStringToAlarmGrouRst_It;
typedef std::map<std::string,AlarmModeltoSetRst *>		MapStringToAlarmModeltoSetRst;
typedef MapStringToAlarmModeltoSetRst::iterator			MapStringToAlarmModeltoSetRst_It;
typedef std::map<std::string,AlarmModelConditionRst *>	MapStringToAlarmModelConditionRst;
typedef MapStringToAlarmModelConditionRst::iterator		MapStringToAlarmModelConditionRst_It;
typedef std::map<std::string,AlarmModelCosineRst *>		MapStringToAlarmModelCosineRst;
typedef MapStringToAlarmModelCosineRst::iterator		MapStringToAlarmModelCosineRst_It;
#endif 
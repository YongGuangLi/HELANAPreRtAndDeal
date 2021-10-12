#ifndef __ALGOVARDEF_H__
#define __ALGOVARDEF_H__

#include <vector>
#define DTRow std::vector<double> 
#define DTRows std::vector<DTRow>

#include <iostream>
#include "FunPublic.h"


struct TrainSampleResult
{
	DTRow			mAlphaData;	 //权值集合Alpha[M]
	DTRows			mMuData;	 //均值(期望值)集合Mu[M][D]	 行:噪音类别;列:测点个数
	//add by wk 2016-6-8
	DTRows			mGData;	 //相关性矩阵集合G[M][M] 行:噪音类别;列:噪音类别
	//end add 
	DTRow			mSigmaData;	 //方差sigma[D0][D1][M]
	unsigned int    mSiLine;	 //D0值	  测点个数
	unsigned int    mSiDim;		 //D1值	  测点个数
	unsigned int	mSiLineLine; //M值	  噪音类别

	double			mMinSim;	 //相似度限值
	double			mMaxSim;	 //样本数据相似度最大值
	double			mAvSim;		 //样本数据相似度平均值

	DTRow			mVSim;		//样本相似度集合
	DTRows			mVpm;		//样本测点相似度集合
	DTRows			mVmt;		//样本期望值集合

	bool			mErr;		 //是否有异常
	std::string		mErrmsg;	 //异常信息

	DTRows			mTestPostNM;

	TrainSampleResult(const unsigned int rM)
	:
	mSiLine(0),
	mSiDim(0),
	mSiLineLine(0),
	mMinSim(0),
	mMaxSim(0),
	mAvSim(0),
	mErr(true),
	mErrmsg("")
	{
		for (unsigned int i = 0; i < rM; i++)
		{
			DTRow muRow;
			mMuData.push_back(muRow);
		}
	}

	~TrainSampleResult()
	{
		mAlphaData.clear();
		for (unsigned int i = 0; i < mMuData.size(); i++)
		{
			mMuData[i].clear();
		}
		mMuData.clear();
		mSigmaData.clear();

		mVSim.clear();
		for (unsigned int i = 0; i < mVpm.size(); i++)
		{
			mVpm[i].clear();
		}
		mVpm.clear();

		for (unsigned int i = 0; i < mVmt.size(); i++)
		{
			mVmt[i].clear();
		}
		mVmt.clear();

		for (unsigned int i = 0; i < mTestPostNM.size(); i++)
		{
			mTestPostNM[i].clear();
		}  
		mTestPostNM.clear();
		//add by wk 2016-6-8
		for (unsigned int i = 0; i < mGData.size(); i++)
		{
			mGData[i].clear();
		}
		mGData.clear();
		//end add
	}
};

#endif

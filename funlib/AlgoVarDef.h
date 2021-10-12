#ifndef __ALGOVARDEF_H__
#define __ALGOVARDEF_H__

#include <vector>
#define DTRow std::vector<double> 
#define DTRows std::vector<DTRow>

#include <iostream>
#include "FunPublic.h"


struct TrainSampleResult
{
	DTRow			mAlphaData;	 //Ȩֵ����Alpha[M]
	DTRows			mMuData;	 //��ֵ(����ֵ)����Mu[M][D]	 ��:�������;��:������
	//add by wk 2016-6-8
	DTRows			mGData;	 //����Ծ��󼯺�G[M][M] ��:�������;��:�������
	//end add 
	DTRow			mSigmaData;	 //����sigma[D0][D1][M]
	unsigned int    mSiLine;	 //D0ֵ	  ������
	unsigned int    mSiDim;		 //D1ֵ	  ������
	unsigned int	mSiLineLine; //Mֵ	  �������

	double			mMinSim;	 //���ƶ���ֵ
	double			mMaxSim;	 //�����������ƶ����ֵ
	double			mAvSim;		 //�����������ƶ�ƽ��ֵ

	DTRow			mVSim;		//�������ƶȼ���
	DTRows			mVpm;		//����������ƶȼ���
	DTRows			mVmt;		//��������ֵ����

	bool			mErr;		 //�Ƿ����쳣
	std::string		mErrmsg;	 //�쳣��Ϣ

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

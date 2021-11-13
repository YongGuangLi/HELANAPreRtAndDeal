/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: AlgoFunc.cpp
* 文件描述: 诊断算法
*  作  者 : %林晓雨%
* 创建日期: 2016-1-18 16:21:37
*******************************************************************************/
#include "AlgoFunc.h"

#include "Kmeanfun.h"
#include "SimFunc.h"
#include "GmmEmFunc.h"

#include <iostream>
#include <time.h>

bool TRAINSAMPLEDeal(unsigned short rM, 
								 DTRows &rData, 
								 const DTRow &rMa, 
								 TrainSampleResult &lTrainSampleRslt)
{
	//Kmean算法
	if (rM > rData.size()) return false;
	DTRow alphaKmeanRet, muKmeanRet, sigmaKmeanRet;
	unsigned int rSiLine, rSiDim, rSiLineLine;
	unsigned short rAlLine, rAlDim, rMu0Line, rMu0Dim;
	Kmeanfun::KmeanFun(rM, rData, alphaKmeanRet, rAlLine, rAlDim, muKmeanRet, rMu0Line, 
						rMu0Dim, sigmaKmeanRet, rSiLine, rSiDim, rSiLineLine);

	//GMM-EM算法
	unsigned int lNSampleNum = rData.size();
	if (lNSampleNum == 0) return false;

	GmmEmFunc* gmm = new GmmEmFunc(lNSampleNum, rData[0].size(),rM);
	bool rslt = gmm->calculate(rData, alphaKmeanRet, rAlLine, rAlDim, muKmeanRet, 
		rMu0Line, rMu0Dim, sigmaKmeanRet, rSiLine, rSiDim, rSiLineLine);
	if (!rslt)
	{	  
		lTrainSampleRslt.mErrmsg = gmm->getStrErrorMessage();
		return false;
	}
	gmm->getData(lTrainSampleRslt.mMuData, lTrainSampleRslt.mAlphaData, 
		lTrainSampleRslt.mSigmaData,lTrainSampleRslt.mSiLineLine, 
		lTrainSampleRslt.mSiLine, lTrainSampleRslt.mSiDim);
//gmm->getDataTest(lTrainSampleRslt.mTestPostNM);
	delete gmm;

	lNSampleNum = lTrainSampleRslt.mMuData.size();
	if (lNSampleNum == 0) return false;
	BaseSim* gmm2 = new BaseSim(lNSampleNum, lTrainSampleRslt.mMuData[0].size());
	gmm2->calculate(lTrainSampleRslt.mMuData,lTrainSampleRslt.mGData);
	delete gmm2;

	SimFunc * simfunc=new SimFunc();

	rslt=simfunc->SIMDeal(rData,lTrainSampleRslt.mGData, rMa, lTrainSampleRslt.mMuData, lTrainSampleRslt.mMinSim, 
		lTrainSampleRslt.mMaxSim, lTrainSampleRslt.mAvSim, lTrainSampleRslt.mVSim, 
		lTrainSampleRslt.mVpm, lTrainSampleRslt.mVmt, lTrainSampleRslt.mErrmsg);
	/*rslt = SimFunc::SIMDeal(rData, rMa, lTrainSampleRslt.mMuData, lTrainSampleRslt.mMinSim, 
							 lTrainSampleRslt.mMaxSim, lTrainSampleRslt.mAvSim, lTrainSampleRslt.mVSim, 
							 lTrainSampleRslt.mVpm, lTrainSampleRslt.mVmt, lTrainSampleRslt.mErrmsg);*/
	if (!rslt) 
	{
		delete simfunc;
		return false;
	}
	delete simfunc;
	//百分比显示
	lTrainSampleRslt.mAvSim	*= 100;
	lTrainSampleRslt.mMinSim *= 100;
	lTrainSampleRslt.mMaxSim *= 100;
	for (unsigned int i = 0; i < lTrainSampleRslt.mVSim.size(); i++)
	{
		lTrainSampleRslt.mVSim[i] *= 100;
	}

	for (unsigned int i = 0; i < lTrainSampleRslt.mVpm.size(); i++)
	{
		for (unsigned int j = 0; j < lTrainSampleRslt.mVpm[i].size(); j++)
		{
			 lTrainSampleRslt.mVpm[i][j] *= 100;
		}
	}
	lTrainSampleRslt.mErr = false;
	return true;
}


bool SIMROWDeal(const DTRow &rData,
							const DTRows &GData,
							const DTRow &maData, 
							const DTRows &muData,
							double & msim,DTRow &pm,
							DTRow &mt,std::string &err)
{
	bool rslt;
	SimFunc * simfunc=new SimFunc();
	rslt = simfunc->SIMROWDeal(rData,GData, maData, muData, msim, pm, mt, err);
   //rslt = SimFunc::SIMROWDeal(rData, maData, muData, msim, pm, mt, err);
	if (!rslt) 
	{
		delete simfunc;
		return false;
	}
	delete simfunc;
   //百分比显示
   msim *= 100;
   for (unsigned int i = 0; i < pm.size(); i++)
   {
	   pm[i]*=100;
   }
   return rslt;
}


bool SIMROWDealEx(DTRowParam rData,
							const DTRows &GData,
							const DTRow &maData, 
							const DTRows &muData,
							double & msim,DTRow &pm,
							DTRow &mt,std::string &err)
{
	bool rslt;
	SimFunc * simfunc=new SimFunc();
	rslt = simfunc->SIMROWDealEx(rData,GData, maData, muData, msim, pm, mt, err);
	//rslt = SimFunc::SIMROWDeal(rData, maData, muData, msim, pm, mt, err);
	if (!rslt) 
	{
		delete simfunc;
		return false;
	}
	delete simfunc;
	//百分比显示
	/*msim *= 100;
	for (unsigned int i = 0; i < pm.size(); i++)
	{
		pm[i]*=100;
	}*/
	return rslt;
}

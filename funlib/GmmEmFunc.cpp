/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: GmmEmFunc.cpp
* 文件描述: 高斯混合模型算法实现
*  作  者 : %林晓雨%
* 创建日期: 2016-1-5 14:32:43
*******************************************************************************/
#include "GmmEmFunc.h"

#include <math.h>
#include <algorithm>
#include <iostream>
#include <time.h>

static bool		smSanityCheck = false;

GmmEmFunc::GmmEmFunc(void)
:
mNSampleNum(0),
mDPointNum(0),
mMLevel(0),
mData(NULL),
mVAlpha(NULL),
mCurrAlpha(NULL),
mMu(NULL),
mCurrMu(NULL),
mStrErrorMessage("")
{
}

GmmEmFunc::GmmEmFunc(const unsigned int n, const unsigned int d, const unsigned int m)
:
mNSampleNum(n),
mDPointNum(d),
mMLevel(m),
mData(NULL),
mVAlpha(NULL),
mCurrAlpha(NULL),
mMu(NULL),
mCurrMu(NULL),
mStrErrorMessage("")
{
	 //mTestPostNM = new Matrix(mNSampleNum, mMLevel);
}

GmmEmFunc::~GmmEmFunc(void)
{
	if (mMu != NULL) delete mMu;
	if (mData != NULL) delete mData;
	if (mCurrMu != NULL) delete mCurrMu;
	if (mVAlpha != NULL) delete mVAlpha;
	if (mCurrAlpha != NULL) delete mCurrAlpha;
	for (unsigned int i = 0; i < mMLevel; i++)
	{
		if (mSigma[i] != NULL) delete mSigma[i];
		if (mCurrSigma[i] != NULL) delete mCurrSigma[i];
	}
	mSigma.clear();
	mCurrSigma.clear();

	//if (mTestPostNM != NULL) delete mTestPostNM;
}


bool
GmmEmFunc::setData(DTRows &vectorData)
{
	if (vectorData.size() != mNSampleNum) 
	{
		mStrErrorMessage = "Data exception!";
		return false;
	}
	mData = new Matrix(mNSampleNum, mDPointNum);
	for (unsigned int i = 0; i < vectorData.size(); i++)
	{
		if (vectorData[i].size() != mDPointNum) return false;
		mData->setVar(i, vectorData[i]);
	}
	return true;
}

bool
GmmEmFunc::setAlpha(DTRow &vectorAlpha, const unsigned int alphaRow, const unsigned int alphaCol)
{
	if (alphaRow != 1 || alphaCol != mMLevel || mMLevel != vectorAlpha.size()) 
	{
		mStrErrorMessage = "Alpha0 exception!";
		return false;
	}

	mVAlpha = new Matrix(1, mMLevel);
	mVAlpha->setVar(vectorAlpha);

	mCurrAlpha = new Matrix(1, mMLevel);
	mCurrAlpha->copyMem(*mVAlpha);
	return true;
}

bool
GmmEmFunc::setMu(DTRow &vectorMu, const unsigned int muRow, const unsigned int muCol)
{
	if (muRow != mDPointNum || muCol != mMLevel || mDPointNum * mMLevel != vectorMu.size()) 
	{
		mStrErrorMessage = "Mu0 exception!";
		return false;
	}

	mMu = new Matrix(mDPointNum, mMLevel);
	mMu->setVar(vectorMu);

	mCurrMu = new Matrix(mDPointNum, mMLevel);
	mCurrMu->copyMem(*mMu);
	return true;
}


bool
GmmEmFunc::setSigma(
				DTRow &vectorSigma, 
				const unsigned int sigmaD1, 
				const unsigned int sigmaD2, 
				const unsigned int sigmaM3)
{
	if (sigmaM3 != mMLevel) 
	{
		mStrErrorMessage = "Sigma0 exception!";
		return false;   
	}

	if (sigmaD1 != mDPointNum || sigmaD2 != mDPointNum)
	{
		mStrErrorMessage = "Sigma0 exception!";
		return false;   
	}

	if (mDPointNum * mDPointNum * mMLevel != vectorSigma.size()) 
	{
		mStrErrorMessage = "Sigma0 exception!";
		return false;   
	}
	
	unsigned int idx = 0;
	for (unsigned int i = 0; i < mMLevel; i++)
	{
		Matrix *sigmaM = new Matrix(mDPointNum, mDPointNum);
		Matrix *sigmaMM = new Matrix(mDPointNum, mDPointNum);
		for (unsigned int j = 0; j < mDPointNum; j++)
		{
			for (unsigned int k = 0; k < mDPointNum; k++)
			{
				if (idx >= vectorSigma.size()) return false;
				sigmaM->setValue(j,k, vectorSigma[idx]);
				idx ++;
			}
		}
		sigmaMM->copyMem(*sigmaM);
		mSigma.push_back(sigmaM);
		mCurrSigma.push_back(sigmaMM);
	}
	return true;
}

bool
GmmEmFunc::calculate(DTRows &rData, 
					 DTRow &alphaKmeanRet,
					 unsigned int rAlLine, 
					 unsigned int rAlDim, 
					 DTRow muKmeanRet, 
					 unsigned int rMu0Line, 
					 unsigned int rMu0Dim, 
					 DTRow sigmaKmeanRet, 
					 unsigned int rSiLine, 
					 unsigned int rSiDim, 
					 unsigned int rSiLineLine)
{
	bool rslt = setData(rData);
	if (!rslt) return false;
	rslt = setMu(muKmeanRet, rMu0Line, rMu0Dim);
	if (!rslt) return false;
	muKmeanRet.clear();
	rslt = setAlpha(alphaKmeanRet, rAlLine, rAlDim);
	if (!rslt) return false;
	alphaKmeanRet.clear();
	rslt = setSigma(sigmaKmeanRet, rSiLine, rSiDim, rSiLineLine);
	if (!rslt) return false;
	sigmaKmeanRet.clear();

	MatrixPtr transDataDN = new Matrix(mDPointNum, mNSampleNum);
	if (mData->getRow() != mNSampleNum || mData->getCol() != mDPointNum)
	{
		 mStrErrorMessage = "Data transpose, Please check it.";
		 if (transDataDN != NULL) delete transDataDN;
		 return false;
	}
	transDataDN->transpose(*mData);

	MatrixPtr beta1M = new Matrix(1, mMLevel);
	MatrixPtr sumRetN1 = new Matrix(mNSampleNum, 1);
	MatrixPtr postNM = new Matrix(mNSampleNum, mMLevel);
	MatrixPtr muTmpDM = new Matrix(mDPointNum, mMLevel);

	MatrixPtr merge12M = new Matrix(1, 2*mMLevel);
	MatrixPtr sigmaDD = new Matrix(mDPointNum, mDPointNum);
	for (unsigned int nbStep = 0; nbStep < 200; nbStep ++)
	{
		//计算概率密度
//std::cout << "calculate nbStep = " << nbStep << std::endl;
		postNM->setZero();
//long t1 = time(NULL);
		rslt = gaussPDF(postNM);
		if (!rslt) break;

		//计算后验概率
		if(mCurrAlpha->getRow() != 1 || mCurrAlpha->getCol() != mMLevel)
		{
			mStrErrorMessage = "In Matrix::dotMulVectorRow(). Please check it.";
			rslt = false;
			break;
		}
		postNM->dotMulVectorRow(*mCurrAlpha);
		sumRetN1->sumRow(*postNM);
		sumRetN1->addAssi(REALMIN);
		postNM->dotDivVectorColAssi(*sumRetN1);

//postNM->sumPostNMTest();
//mTestPostNM->copyMem(*postNM);
		beta1M->sumCol(*postNM);

		//更新值 
		rslt = updateAlphaMuSigma(transDataDN, beta1M, postNM);
		if (!rslt)	break; 
		//条件判断
		muTmpDM->sub(*mCurrMu, *mMu);
		muTmpDM->absAssi();
		merge12M->setZero();
		merge12M->sumCol(*muTmpDM);

		beta1M->setZero();
		beta1M->sub(*mCurrAlpha, *mVAlpha);

		beta1M->absAssi();

		merge12M->mergeCol(mMLevel, *beta1M);
		beta1M->setZero();

		beta1M->sumRow(*merge12M);
		double sum = beta1M->getValue(0,0);

		double sum2 = 0;
		for (unsigned int i=0; i< mMLevel; i++)
		{
			sigmaDD->sub(*mCurrSigma[i], *mSigma[i]);
			sum2 += sigmaDD->determinent();
		}
		if (sum + sum2 < EPSILON) break;

		mMu->copyMem(*mCurrMu);
		mVAlpha->copyMem(*mCurrAlpha);

		for (unsigned int i=0; i< mCurrSigma.size(); i++)
		{
			mSigma[i]->copyMem(*mCurrSigma[i]);
		}
	}

	if (postNM != NULL) delete postNM;
	if (beta1M != NULL) delete beta1M;
	if (sigmaDD != NULL) delete sigmaDD;
	if (muTmpDM != NULL) delete muTmpDM;
	if (merge12M != NULL) delete merge12M;
	if (sumRetN1 != NULL) delete sumRetN1;
	if (transDataDN != NULL) delete transDataDN;
	return rslt;
}


//addition and assignment operator
//根据高斯分布函数计算每组数据的概率密度 
bool 
GmmEmFunc::gaussPDF(MatrixPtr &pixNM)
{	
	bool rslt = true; 
	double lValue = 0;
	MatrixPtr mu1D = new Matrix(1, mDPointNum);
	MatrixPtr probN1 = new Matrix(mNSampleNum,1);
	MatrixPtr retND = new Matrix(mNSampleNum, mDPointNum);
	MatrixPtr dataND = new Matrix(mNSampleNum, mDPointNum);
	MatrixPtr invSigmaDD = new Matrix(mDPointNum, mDPointNum);
	for (unsigned int i = 0; i < mMLevel; i++)
	{
		dataND->copyMem(*mData);

		if(mCurrMu->getRow() != mDPointNum || i >= mCurrMu->getCol())
		{
			mStrErrorMessage = "setVectorColAndTranspose. Please check it.";
			rslt = false;
			break;
		}
		mu1D->setVectorColAndTranspose(i, *mCurrMu);

		if (dataND->getCol() != mDPointNum)
		{
			mStrErrorMessage = "In subAndAssiVectorRow. Please check it.";
			rslt = false;
			break;
		}

		dataND->subVectorRowAssi(*mu1D);  // data -= mu		 
		if(mCurrSigma[i]->getCol() != mDPointNum || mCurrSigma[i]->getRow() != mDPointNum)    //非方阵
		{
			mStrErrorMessage ="In Matrix Matrix::Invert(). Please check it";
			rslt = false;
			break;
		}

		rslt = invSigmaDD->inverse(*mCurrSigma[i]);
		if (!rslt)
		{
			mStrErrorMessage ="In Matrix::inverse().Please check it.";
			rslt = false;
			break;
		}
	
		if(dataND->getRow() != mNSampleNum || invSigmaDD->getCol() != mDPointNum)
		{
			mStrErrorMessage ="In Matrix::mul().Please check it.";
			rslt = false;
			break;
		}
		retND->mul(*dataND, *invSigmaDD);

		if(dataND->getCol() != mDPointNum)
		{
			mStrErrorMessage = "In Matrix::dotMulAssi(). Please check it.";
			rslt = false;
			break;
		}
		retND->dotMulAssi(*dataND);

		probN1->sumRow(*retND);

		probN1->mulAssi(-0.5);

		probN1->expAssi();

		lValue = mCurrSigma[i]->determinent();

		lValue = pow(2*PI, (int)mDPointNum) * (fabs(lValue) + REALMIN);
		lValue = sqrt(lValue);
		if (lValue == 0)
		{
			mStrErrorMessage = "In lValue = 0. Please check it.";
			rslt = false;
			break;
		}

		probN1->divAssi(lValue);
		pixNM->insertCol(i, *probN1);
	}

	if (mu1D != NULL)  delete mu1D;
	if (retND != NULL)  delete retND;
	if (dataND != NULL) delete dataND;
	if (probN1 != NULL)  delete probN1;
	if (invSigmaDD != NULL)  delete invSigmaDD;
	return rslt;
}



bool
GmmEmFunc::updateAlphaMuSigma(MatrixPtr &pTransDataDN, MatrixPtr &pBeta1M, MatrixPtr &pPostNM)
{
	bool rslt = true;
	MatrixPtr mulRetD1 = new Matrix(mDPointNum, 1);
	MatrixPtr pixRowN1 = new Matrix(mNSampleNum, 1);
	MatrixPtr pixCol1N = new Matrix(1, mNSampleNum);
	MatrixPtr mulDD = new Matrix(mDPointNum, mDPointNum);
	MatrixPtr diagOnesDD = new Matrix(mDPointNum, mDPointNum);
	MatrixPtr dataTmpDN = new Matrix(mDPointNum, mNSampleNum);
	MatrixPtr dataTmpTransND = new Matrix(mNSampleNum, mDPointNum);
	diagOnesDD->setUnit();
	diagOnesDD->mulAssi(EPSILON);
	for (unsigned int i = 0; i < mMLevel; i++)
	{
		if (i >= pBeta1M->getCol())
		{
		   mStrErrorMessage ="In Matrix::geValue(). Please check it.";
		   rslt = false;
		   break;
		}
		double betalI = pBeta1M->getValue(0, i);

		//更新权值
		if(i >= mCurrAlpha->getCol())
		{
			mStrErrorMessage = "In double Matrix::setValue().Please check it";
			rslt = false;
			break;
		}

		mCurrAlpha->setValue(0, i, betalI/mNSampleNum);

		//更新均值
		if (i >= pPostNM->getCol())
		{
			mStrErrorMessage = "In double Matrix::setValue().Please check it";
			rslt = false;
			break;
		}
		pixRowN1->setVectorCol(i, *pPostNM);

		if (pTransDataDN->getRow() != mDPointNum)
		{
			mStrErrorMessage = "In double Matrix::mul().Please check it";
			rslt = false;
			break;
		}
		mulRetD1->mul(*pTransDataDN, *pixRowN1);

		if (betalI != 0)
		{
			mulRetD1->divAssi(betalI);
		}
		else
		{
			 mulRetD1->divAssi(REALMIN);
		}
		mCurrMu->insertCol(i, *mulRetD1);

		//更新方差 
		if (betalI == 0)
		{
			mCurrSigma[i]->copyMem(*diagOnesDD);
			continue;
		}
		dataTmpDN->subVectorCol(*pTransDataDN, *mulRetD1);
		dataTmpTransND->transpose(*dataTmpDN);
		pixCol1N->transpose(*pixRowN1);
	
		dataTmpDN->dotMulVectorRowAssi(*pixCol1N);

		mulDD->mul(*dataTmpDN, *dataTmpTransND);
		mulDD->divAssi(betalI);

		if (mSigma[i]->getRow() != mDPointNum || mSigma[i]->getCol() != mDPointNum)
		{
			mStrErrorMessage = "In add(). Please check it.";
			rslt = false;
			break;
		}
		mCurrSigma[i]->add(*mulDD, *diagOnesDD);
	}

	if (mulDD != NULL) delete mulDD;
	if (mulRetD1 != NULL) delete mulRetD1;
	if (pixRowN1 != NULL) delete pixRowN1;
	if (pixCol1N != NULL) delete pixCol1N;
	if (dataTmpDN != NULL) delete dataTmpDN;
	if (diagOnesDD != NULL) delete diagOnesDD;
	if (dataTmpTransND != NULL) delete dataTmpTransND;
	return rslt;
}


void
GmmEmFunc::display(MatrixPtr &m)
{
	if (!smSanityCheck)  return;
	m->display();
}


void 
GmmEmFunc::getData(
			DTRows &muData, 
			DTRow &alphaData,
			DTRow &sigmaData, 
			unsigned int &lSiLineLine, 
			unsigned int &lSiLine, 
			unsigned int &lSiDim)
{
	for(unsigned int col = 0; col < mMu->getCol(); col++)
	{
		mMu->getVarAndTranspose(col, muData[col]);
	}

	mVAlpha->getVar(0, alphaData);

	lSiLineLine = mSigma.size();
	lSiLine = mSigma[0]->getRow();
	lSiDim = mSigma[0]->getCol();
	for (unsigned int k = 0; k < mSigma.size(); k++)
	{
		for (unsigned int i = 0; i < mSigma[k]->getRow(); i++)
		{
			mSigma[k]->getVar(i, sigmaData);
		}
	}
}


//void 
//GmmEmFunc::getDataTest(DTRows &postNMD)
//{
//	for(unsigned int row = 0; row < mTestPostNM->getRow(); row++)
//	{
//		DTRow post;
//		mTestPostNM->getVar(row, post);
//		postNMD.push_back(post);
//	}
//}
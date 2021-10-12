/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: GmmEmFunc.h
* 文件描述: 高斯混合模型算法实现
*  作  者 : %林晓雨%
* 创建日期: 2016-1-5 14:32:06
*******************************************************************************/

#ifndef __GMMEMFUNC_H__
#define __GMMEMFUNC_H__

#define		PI			 3.1415926
#define		REALMIN		 2.2250738585072014e-308
#define	    EPSILON		 0.00000001

#include "Matrix.h"
#include "AlgoVarDef.h"

class GmmEmFunc
{
private:
	unsigned int			mNSampleNum;		// 样本数目
	unsigned int			mDPointNum;			// 测点个数
	unsigned int			mMLevel;			// 噪音级别 
	MatrixPtr				mData;				// 样本数据 行:样本数据组的个数,列:测点个数
	MatrixPtr				mVAlpha;			// 权重	  行: 1,列:噪音级别
	MatrixPtr				mMu;				// 均值	  行:测点个数,列噪音级别
	std::vector<MatrixPtr >	mSigma;				// 方差   vector是噪音级别  matrix 行列都是测点个数 

	MatrixPtr				mCurrAlpha;			// 权重	  行: 1,列:噪音级别
	MatrixPtr				mCurrMu;			// 均值	  行:测点个数,列噪音级别
	std::vector<MatrixPtr >	mCurrSigma;			// 方差   vector是噪音级别  matrix 行列都是测点个数 

	std::string				mStrErrorMessage;

	//MatrixPtr mTestPostNM;

public:
	GmmEmFunc(void);
	~GmmEmFunc(void);

	GmmEmFunc(const unsigned int n, const unsigned int d, const unsigned int m);

	bool setData(DTRows &vectorData);

	bool setAlpha(DTRow &vectorAlpha, const unsigned int alphaRow, const unsigned int alphaCol);

	bool setMu(DTRow &vectorMu, const unsigned int muRow, const unsigned int muCol);

	bool setSigma(DTRow &vectorSigma, const unsigned int sigmaD1, const unsigned int sigmaD2, const unsigned int sigmaM3);

	bool calculate(DTRows &rData, 
					DTRow &alphaKmeanRet,
					unsigned int rAlLine, 
					unsigned int rAlDim, 
					DTRow muKmeanRet, 
					unsigned int rMu0Line, 
					unsigned int rMu0Dim, 
					DTRow sigmaKmeanRet, 
					unsigned int rSiLine, 
					unsigned int rSiDim, 
					unsigned int rSiLineLine);

	std::string getStrErrorMessage() { return mStrErrorMessage;}

	void getData(DTRows &muData,
			 DTRow &alphaData,
			 DTRow &sigmaData, 
			 unsigned int &mSiLineLine, 
			 unsigned int &mSiLine, 
			 unsigned int &mSiDim);

	//void getDataTest(DTRows &postNMD);
private:
	bool gaussPDF(MatrixPtr &pixNM);

	bool updateAlphaMuSigma(MatrixPtr &pTransDataDN, MatrixPtr &pBeta1M, MatrixPtr &pPostNM);
	
	void display(MatrixPtr &m);
};
#endif

/*******************************************************************************
* Copyright��C��,2010-2015,DTXY Tech .Co.Ltd;
* �� �� ��: GmmEmFunc.h
* �ļ�����: ��˹���ģ���㷨ʵ��
*  ��  �� : %������%
* ��������: 2016-1-5 14:32:06
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
	unsigned int			mNSampleNum;		// ������Ŀ
	unsigned int			mDPointNum;			// ������
	unsigned int			mMLevel;			// �������� 
	MatrixPtr				mData;				// �������� ��:����������ĸ���,��:������
	MatrixPtr				mVAlpha;			// Ȩ��	  ��: 1,��:��������
	MatrixPtr				mMu;				// ��ֵ	  ��:������,����������
	std::vector<MatrixPtr >	mSigma;				// ����   vector����������  matrix ���ж��ǲ����� 

	MatrixPtr				mCurrAlpha;			// Ȩ��	  ��: 1,��:��������
	MatrixPtr				mCurrMu;			// ��ֵ	  ��:������,����������
	std::vector<MatrixPtr >	mCurrSigma;			// ����   vector����������  matrix ���ж��ǲ����� 

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

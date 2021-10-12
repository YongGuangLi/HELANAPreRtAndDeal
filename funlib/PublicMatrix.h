#pragma once
/*******************************************************************************
* Copyright（C）,2015-2020,DTXY Tech .Co.Ltd;
* 文 件 名: PublicMatrix.h
* 文件描述: 矩阵实现
*  作  者 : %王凯%，15802613961
* 创建日期: 2016-6-8 11:39:28
*******************************************************************************/
#ifndef __PublicMatrix_H__
#define __PublicMatrix_H__
#define		REALMIN		 2.2250738585072014e-308
#include <vector>
#include "FunPublic.h"
class PublicMatrix
{
private:
	double **mData;   
	unsigned int	mRow;
	unsigned int	mCol;	

public:
	PublicMatrix(void); //无参数的构造函数
	~PublicMatrix(void);//析构函数声明

	PublicMatrix(unsigned int row, unsigned int col);
	PublicMatrix(const PublicMatrix& m);

	unsigned int getCol() const;
	unsigned int getRow() const;

	void setMutoG(PublicMatrix tmp);
	void setGWVar(const std::vector<std::vector<double>> rMuData, std::vector<double> rData);
	void setGWVar(const std::vector<std::vector<double>> rMuData, DTRowParam rData);//发电能力功能扩展
	bool setGWoVar();

	void setUnit(); 

	void transpose(PublicMatrix &m);

	void setVectorColAndTranspose(const unsigned int col,  PublicMatrix &m);

	void subVectorRowAssi(const PublicMatrix& m);

	bool inverse(PublicMatrix &tmp);

	void mul(PublicMatrix& rhs, PublicMatrix &lhs);

	void dotMulAssi(const PublicMatrix& m);

	void sumRow(PublicMatrix &m);

	void mulAssi(double d);

	void expAssi();

	double determinent();

	void divAssi(double d);

	void insertCol(const unsigned int col, PublicMatrix &m);

	void dotMulVectorRowAssi(const PublicMatrix& m);

	void addAssi(const double d);

	void dotDivVectorColAssi(const PublicMatrix& m);

	void sumCol(PublicMatrix &m);

	double getValue(unsigned int i,unsigned int j);

	void setValue(unsigned int i,unsigned int j, double vv);

	void setVectorCol(const unsigned int col, PublicMatrix &m);

	void subVectorCol(PublicMatrix &rhs, const PublicMatrix& lhsVector);

	void add(const PublicMatrix& rhs, const PublicMatrix& lhs);

	void setZero();

	void dotMulVectorRow(const PublicMatrix& m);

	void sub(const PublicMatrix &rhs, const PublicMatrix& lhs);

	void absAssi();

	void mergeCol(const unsigned int col, PublicMatrix &m);

	void copyMem(PublicMatrix &m);

	void setVar(unsigned int i,const std::vector<double> &val);

	void display();

	void setVar(std::vector<double> &val);

	void setVar(unsigned int i,double *val);

	std::string toString(unsigned int i);

	void getVar(unsigned int i, std::vector<double> &val);
	bool getVar(unsigned int i, std::vector<double> &val,double & msim,std::vector<double> &pm,
		const std::vector<double> &rData,const std::vector<double> &ma);

	void CheckCap(const int itype,const double &simtemp,const double &RtValue,const double &PerValue,double &sim);
	bool getVar(unsigned int i, std::vector<double> &val,
				double & msim,std::vector<double> &pm,
				const DTRowParam &rData,const std::vector<double> &ma);//发电能力功能扩展

	void getVarAndTranspose(unsigned int col, std::vector<double> &val);

	void sumPostNMTest();
private:
	double determinent(double **data, int n);

	//double determinent(const unsigned int n);

	//int sgn(int order);

	//void swap(int *a, int *b);

	//int inver_order(int list[], int n);

	//double det(double **p, int n, int k, int list[], double sum);

	//unsigned int power(unsigned int m, unsigned int n);

	void sanityCheck(const PublicMatrix &m, unsigned int i, unsigned int j);
};

typedef  PublicMatrix*	PublicMatrixPtr;

#endif
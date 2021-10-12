/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: Matrix.h
* 文件描述: 矩阵实现
*  作  者 : %林晓雨%
* 创建日期: 2016-1-5 9:46:28
*******************************************************************************/
#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <vector>
#include <string>

class Matrix
{
private:
	double **mData;   
	unsigned int	mRow;
	unsigned int	mCol;	

public:
	Matrix(void); //无参数的构造函数
	~Matrix(void);//析构函数声明

	Matrix(unsigned int row, unsigned int col);
	Matrix(const Matrix& m);
	
	unsigned int getCol() const;
	unsigned int getRow() const;
	void setUnit(); 

	void transpose(Matrix &m);

	void setVectorColAndTranspose(const unsigned int col,  Matrix &m);

	void subVectorRowAssi(const Matrix& m);

	bool inverse(Matrix &tmp);

	void mul(Matrix& rhs, Matrix &lhs);

	void dotMulAssi(const Matrix& m);

	void sumRow(Matrix &m);

	void mulAssi(double d);

	void expAssi();

	double determinent();

	void divAssi(double d);

	void insertCol(const unsigned int col, Matrix &m);

	void dotMulVectorRowAssi(const Matrix& m);

	void addAssi(const double d);

	void dotDivVectorColAssi(const Matrix& m);

	void sumCol(Matrix &m);

	double getValue(unsigned int i,unsigned int j);

	void setValue(unsigned int i,unsigned int j, double vv);

	void setVectorCol(const unsigned int col, Matrix &m);

	void subVectorCol(Matrix &rhs, const Matrix& lhsVector);

	void add(const Matrix& rhs, const Matrix& lhs);

	void setZero();

	void dotMulVectorRow(const Matrix& m);

	void sub(const Matrix &rhs, const Matrix& lhs);

	void absAssi();

	void mergeCol(const unsigned int col, Matrix &m);

	void copyMem(Matrix &m);

	void setVar(unsigned int i, std::vector<double> &val);

	void display();

	void setVar(std::vector<double> &val);

	void setVar(unsigned int i,double *val);

	std::string toString(unsigned int i);

	void getVar(unsigned int i, std::vector<double> &val);

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

	void sanityCheck(const Matrix &m, unsigned int i, unsigned int j);
};

typedef  Matrix*	MatrixPtr;

#endif

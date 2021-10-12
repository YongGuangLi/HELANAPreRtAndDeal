/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: Matrix.cpp
* 文件描述: 矩阵实现
*  作  者 : %林晓雨%
* 创建日期: 2016-1-5 9:47:01
*******************************************************************************/
#pragma   warning(disable:4018   4244) 
#include "Matrix.h"

#include <math.h>
#include <numeric> 
#include <algorithm>
#include <functional>

#include <iostream>

using namespace std;

Matrix::Matrix(void)
:
mRow(0),
mCol(0),
mData(NULL)
{
}


Matrix::~Matrix(void)
{
	if(mData != NULL)
	{
		for(unsigned int i=0;i<mRow;i++)
		{
			delete[] mData[i];
		}
		delete[] mData;
	}
}



// constructor
Matrix::Matrix(unsigned int row, unsigned int col)
:
mRow(row),
mCol(col)
{
	mData=new double*[row];
	for(unsigned int i=0;i<row;i++)
	{
		mData[i]=new double[col];
	}
}


//copy  constructor
Matrix::Matrix(const Matrix& m)
:
mRow(m.mRow),
mCol(m.mCol)
{
	mData = new double*[mRow];
	for(unsigned int i=0;i<mRow;i++)
	{
		mData[i] = new double[mCol];
	}

	for(unsigned int i=0;i<mRow;i++)
	{
		copy(m.mData[i],m.mData[i]+mCol,mData[i]);
	}

}



unsigned int Matrix::getRow() const
{
	return mRow;
}


unsigned int Matrix::getCol() const
{
	return mCol;
}



void Matrix::setUnit()
{
	for(unsigned int i=0;i<mRow;i++)
		for(unsigned int j=0;j<mCol;j++)
			mData[i][j] = (i==j)?1:0;
}

//transpose 转置
void
Matrix::transpose(Matrix &m)
{
	for(unsigned int i=0;i<mRow;i++)
	{
		for(unsigned int j=0;j<mCol;j++)
		{
sanityCheck(m, j, i);
			mData[i][j] = m.mData[j][i];
		}
	}
}

 
void 
Matrix::setVectorColAndTranspose(const unsigned int col, Matrix &m) 
{
	//	       a b c
	// 设有X = d e f   
	//	       g h i
	//		   j k l
	//复制第col = 2列，生成新矩阵，新矩阵并且转置
	//  ret = b e h k 
	for(unsigned int i=0;i<m.mRow;i++)
	{
		mData[0][i] = m.mData[i][col];
sanityCheck(m, i, col);
sanityCheck(*this, 0, i);
	}
}


//addition and assignment operator
void
Matrix::subVectorRowAssi(const Matrix& m)
{
	//this矩阵-m向量矩阵
	for (unsigned int i=0; i<mRow; i++)
	{
		for (unsigned int j=0; j<mCol; j++)
		{
			mData[i][j]-= m.mData[0][j];
sanityCheck(m, 0, j);
		}
	}
}

bool
Matrix::inverse(Matrix &tmp) 
{
	unsigned int i, j, k;
	unsigned int n = mRow; 
	double max, temp;  
	double **t = new double*[mRow];
	for(unsigned int i=0;i<mRow;i++)
	{
		t[i]=new double[mRow];
	}                //临时矩阵  
	//将A矩阵存放在临时矩阵t[n][n]中  
	for (i = 0; i < n; i++)  
	{  
		for (j = 0; j < n; j++)  
		{  
			t[i][j] = tmp.mData[i][j];
sanityCheck(tmp, i, j);
		}  
	}  
	//初始化B矩阵为单位阵  
	for (i = 0; i < n; i++)  
	{  
		for (j = 0; j < n; j++)  
		{  
			mData[i][j] = (i == j) ? (float)1 : 0;  
		}  
	}  
	for (unsigned int i = 0; i < n; i++)  
	{  
		//寻找主元  
		max = t[i][i];  
		k = i;  
		for (j = i + 1; j < n; j++)  
		{  
			if (fabs(t[j][i]) > fabs(max))  
			{  
				max = t[j][i];  
				k = j;  
			}  
		}  
		//如果主元所在行不是第i行，进行行交换  
		if (k != i)  
		{  
			for (j = 0; j < n; j++)  
			{  
				temp = t[i][j];  
				t[i][j] = t[k][j];  
				t[k][j] = temp;  
				//B伴随交换  
				temp = mData[i][j];  
				mData[i][j] = mData[k][j];  
				mData[k][j] = temp;  
			}  
		}  
		//判断主元是否为0, 若是, 则矩阵A不是满秩矩阵,不存在逆矩阵  
		if (t[i][i] == 0)  
		{  
			cout << "There is no inverse matrix!"; 
			
			if(t != NULL)
			{
				for(unsigned int i=0;i<mRow;i++)
				{
					delete[] t[i];
				}
				delete[] t;
			}
			return false;  
		}  
		//消去A的第i列除去i行以外的各行元素  
		temp = t[i][i];  
		for (j = 0; j < n; j++)  
		{								 
			t[i][j] = t[i][j] / temp;        //主对角线上的元素变为1  
			mData[i][j] = mData[i][j] / temp;        //伴随计算  
		}  
		for (j = 0; j < n; j++)        //第0行->第n行  
		{  
			if (j != i)                //不是第i行  
			{  
				temp = t[j][i];  
				for (k = 0; k < n; k++)        //第j行元素 - i行元素*j列i行元素  
				{  
					t[j][k] = t[j][k] - t[i][k] * temp;  
					mData[j][k] = mData[j][k] - mData[i][k] * temp;  
				}  
			}  
		}  
	} 
	if(t != NULL)
	{
		for(unsigned int i=0;i<mRow;i++)
		{
			delete[] t[i];
		}
		delete[] t;
	}
	return true;
}

//乘法运算
void
Matrix::mul(Matrix& rhs, Matrix &lhs)//乘法运算
{
    double sum=0;
    for(unsigned int i=0;i<rhs.mRow;i++)
    {
        for(unsigned int j=0;j<lhs.mCol;j++)
        {
            for(unsigned int k=0;k<rhs.mCol;k++)
			{
                sum+=rhs.mData[i][k]*lhs.mData[k][j];
			}

            mData[i][j]=sum;
            sum = 0;
        }
    }
}


//两个矩阵相同位子元素相乘
void
Matrix::dotMulAssi(const Matrix& m)
{
	for(unsigned int i=0;i<mRow;i++)
	{
		for(unsigned int j=0;j<mCol;j++)
		{
			mData[i][j]=mData[i][j]*m.mData[i][j];
sanityCheck(m, i, j);
		}
	}
}



void 
Matrix::sumRow(Matrix &m) 
{			  
	double sum = 0;
	for(unsigned int i=0;i<m.mRow;i++)
	{
		sum =0;
		for(unsigned int j=0;j<m.mCol;j++)
		{
			sum+=m.mData[i][j];
		}
sanityCheck(*this, i, 0);
		mData[i][0] = sum;
	}
}

void
Matrix::mulAssi(double d)
{
	for(unsigned int i=0;i<mRow;i++)
	{
		for(unsigned int j=0;j<mCol;j++)
		{
			mData[i][j]=mData[i][j]*d;
		}
	}
}

void
Matrix::expAssi()
{
	for(unsigned int i=0;i<mRow;i++)
	{
		for(unsigned int j=0;j<mCol;j++)
		{
			mData[i][j]=exp(mData[i][j]);
		}
	}
}


void 
Matrix::divAssi(double d)
{
	for(unsigned int i=0;i<mRow;i++)
	{
		for(unsigned int j=0;j<mCol;j++)
		{
			mData[i][j]=mData[i][j]/d;
		}
	}
}


void Matrix::insertCol(const unsigned int col, Matrix &m)
{
	//从m向量矩阵的值复制到this矩阵col列中(一行或一列才能称为向量)
	for(unsigned int i=0;i<mRow;i++)
	{
		mData[i][col] = m.mData[i][0];
sanityCheck(m, i, 0);
sanityCheck(*this, i, col);
	}
}

//矩阵相乘wk？
void 
Matrix::dotMulVectorRowAssi(const Matrix& m) 
{
	for(unsigned int i=0;i<mRow;i++)
	{
		for(unsigned int j=0;j<mCol;j++)
		{
			mData[i][j]=mData[i][j]*m.mData[0][j];
sanityCheck(m, 0, j);
		}
	}
}

void Matrix::setZero()
{
    for(unsigned int i=0;i<mRow;i++)
        fill(mData[i],mData[i]+mCol,0);
}


void 
Matrix::addAssi(double d) 
{
	for(unsigned int i=0;i<mRow;i++)
	{
		for(unsigned int j=0;j<mCol;j++)
		{
			mData[i][j]=mData[i][j]+d;
		}
	}
}



void
Matrix::dotDivVectorColAssi(const Matrix& m)
{
	for(unsigned int i=0;i<mRow;i++)
	{
		for(unsigned int j=0;j<mCol;j++)
		{								 
sanityCheck(m, i, 0);
			
			mData[i][j]=mData[i][j]/m.mData[i][0];
		}
	}
}

void
Matrix::sumCol(Matrix &m)
{
	double sum = 0;
	for(unsigned int i=0;i<m.mCol;i++)
	{
		sum = 0;
		for(unsigned int j=0;j<m.mRow;j++)
		{
			sum+=m.mData[j][i];
		}
sanityCheck(*this, 0, i);
		mData[0][i] = sum;
	}
}


double Matrix::getValue(unsigned int i,unsigned int j)
{
sanityCheck(*this, i, j);
	return mData[i][j];
}

void 
Matrix::setValue(unsigned int i,unsigned int j, double vv)
{
sanityCheck(*this, i, j);
	mData[i][j] = vv;
}



void
Matrix::setVectorCol(const unsigned int col, Matrix &m)
{
	//从this矩阵复制row行所有元素到新矩阵中
	for (unsigned int i = 0; i < mRow; i++)
	{
sanityCheck(m, i, col);
		mData[i][0] = m.mData[i][col];
	}
}





void 
Matrix::subVectorCol(Matrix &rhs, const Matrix& lhsVector)
{
	//this矩阵-m向量矩阵
	for (unsigned int i=0; i<mRow; i++)
	{
		for (unsigned int j=0; j<mCol; j++)
		{
sanityCheck(rhs, i, j);
sanityCheck(lhsVector, i, 0);
			mData[i][j] = rhs.mData[i][j]- lhsVector.mData[i][0];
		}
	}
}

//两个矩阵相加
void
Matrix::add(const Matrix& rhs, const Matrix& lhs) 
{
	for(unsigned int i=0;i<mRow;i++)
	{
		for (unsigned int j=0; j<mCol;j++)
		{
			mData[i][j] = rhs.mData[i][j] + lhs.mData[i][j];
sanityCheck(rhs, i, j);
sanityCheck(lhs, i, j);
		}	
	}
}


void 
Matrix::dotMulVectorRow(const Matrix& m) 
{
	for(unsigned int i=0;i<mRow;i++)
	{
		for(unsigned int j=0;j<mCol;j++)
		{
sanityCheck(m, 0, j);
			mData[i][j]=mData[i][j]*m.mData[0][j];
		}
	}
}

//两个矩阵相减
void
Matrix::sub(const Matrix &rhs, const Matrix& lhs) 
{
	for(unsigned int i=0;i<mRow;i++)
	{
		for (unsigned int j=0; j<mCol;j++)
		{
sanityCheck(rhs, i, j);
sanityCheck(lhs, i, j);
			mData[i][j] = rhs.mData[i][j] - lhs.mData[i][j];
		}	
	}
}


void
Matrix::absAssi()
{
	for(unsigned int i=0;i<mRow;i++)
	{
		for(unsigned int j=0;j<mCol;j++)
		{
			mData[i][j]=fabs(mData[i][j]);
		}
	}
}



void
Matrix::mergeCol(const unsigned int col, Matrix &m)
{
	for(unsigned int i=0;i<mRow;i++)
	{
		for (unsigned int k=0; k<m.mCol;k++)
		{
sanityCheck(*this, i, col+k);
sanityCheck(m, i, k);
			mData[i][col + k] = m.mData[i][k];
		}
	}
}


void
Matrix::copyMem(Matrix &m)
{
	for(unsigned int i=0;i<mRow;i++)
	{
		copy(m.mData[i],m.mData[i]+mCol,mData[i]);
	}
}

void 
Matrix::setVar(unsigned int i, std::vector<double> &val)		
{ 
	for(unsigned int j=0;j<mCol;j++) 
	{
sanityCheck(*this, i, j);
		mData[i][j]=val[j];
	}
}


void 
Matrix::display()
{
    unsigned int i,j;
    for(i=0;i<mRow;i++)
    {
        for(j=0;j<mCol;j++)
            printf("%f  ",mData[i][j]);
       cout << endl;
    }
	cout << "--------------------------- " << endl;
}


void 
Matrix::setVar(vector<double> &val)		
{ 
	unsigned int k = 0;
	for (unsigned int i=0; i<mRow; i++)
	{
		for(unsigned int j=0;j<mCol;j++) 
		{
			mData[i][j]=val[k++];
		}
	}
}

void 
Matrix::setVar(unsigned int i,double *val)		
{ 
	for(unsigned int j=0;j<mCol;j++) 
	{
		mData[i][j]=val[j];
	}
}

void
Matrix::getVar(unsigned int i, std::vector<double> &val)
{
	for(unsigned int j=0;j<mCol;j++) 
	{
		val.push_back(mData[i][j]);
	}
}


void
Matrix::getVarAndTranspose(unsigned int col, std::vector<double> &val)
{
	for(unsigned int i=0;i<mRow;i++) 
	{
		val.push_back(mData[i][col]);
	}
}

void
Matrix::sanityCheck(const Matrix &m, unsigned int i, unsigned int j)
{
	if (i < 0 || i >= m.mRow ||  j < 0 || j >= m.mCol)
	{
		std::cout << "Array overflow" << std::endl;
	}
}


//#define zero(x) (fabs(x) < 1e-10)
#define zero(x) (fabs(x) < 1e-308)
 
//化为三角形行列式
double 
Matrix::determinent()
{
	return determinent(mData, mRow);
}

double 
Matrix::determinent(double **data, int n)
{
	unsigned int j, sign = 0;
	double ret = 1, t; 

	double **b = new double*[n];
	for (unsigned int i = 0; i < n; i++)
	{
		b[i] = new double[n];
		for (unsigned int j= 0; j < n; j++)
		{
			b[i][j] = data[i][j];
		}
	}

	for (unsigned int i = 0; i < n; i++)
	{
		if (zero(b[i][i]))
		{
			for (j = i+1; j < n; j++)
			{
				if (!zero(b[j][i]))
				{
					break;
				}
			}
			if (j == n) 
			{
				if(b != NULL)
				{
					for(i=0;i<n;i++)
					{
						delete[] b[i];
					}
					delete[] b;
				}
				return 0;
			}
			
			for (unsigned int k = i; k < n; k++)
			{
				t = b[i][k], b[i][k] = b[j][k], b[j][k] = t;
			}
			sign++;	
		}
		ret *= b[i][i];
		for (unsigned int k = i+1; k < n; k++)
		{
			b[i][k]/=b[i][i];
		}
		for (j = i+1; j < n; j++)
		{
			for (unsigned int k = i +1; k < n; k++)
			{
				b[j][k]-=b[j][i]*b[i][k];
			}
		}
	}

	if (sign & 1) ret =-ret;

	if(b != NULL)
	{
		for(unsigned int i=0;i<n;i++)
		{
			delete[] b[i];
		}
		delete[] b;
	}
	return ret;
}



void 
Matrix::sumPostNMTest()
{
	double sum = 0;
	int aa = 0;
	for (unsigned int i = 0; i < mRow; i++)
	{
		sum = 0;
		for (unsigned int j = 0; j < mCol; j++)
		{
			sum += mData[i][j];
		}
		if (sum < 0.999 || sum > 1.001)
		{
			cout << "i = " << i << "(" << sum << ")" << ",";
			aa = 1;
		}
	}
	if (aa == 1) cout << endl;
}





//void 
//Matrix::swap(int *a, int *b)
//{
//	int m;
//	m = *a;
//	*a = *b;
//	*b = m;
//}
//
////求逆序对的个数
//int 
//Matrix::inver_order(int list[], int n)
//{
//	int ret = 0;
//	for (int i = 1; i < n; i++)
//	{
//		for (int j = 0; j < i; j++)
//		{
//			if (list[j] > list[i])
//			{
//				ret ++;
//			}
//		}
//
//	}
//	return ret;
//}
//
//int 
//Matrix::sgn(int order)
//{
//	return order % 2? -1:1;
//}
//
//
//double 
//Matrix::det(double **p, int n, int k, int list[], double sum)
//{
//	if (k >= n)
//	{
//		int order = inver_order(list, n);
//		double item = (double)sgn(order);
//		for (int i = 0; i < n ; i++)
//		{
//			//item *=*(p+i*n+list[i]);
//			item *= p[i][list[i]];
//		}
//		return sum + item;
//	}
//	else
//	{
//		for(int i = k; i < n; i++)
//		{
//			swap(&list[k], &list[i]);
////cout << "n=" << n << ";k:" << k+1 << ";i=" << i << endl;
//			sum = det(p, n, k+1, list, sum)	;
//			swap(&list[k], &list[i]);
//		}
//	}
//	return sum;
//}
//
//
//double 
//Matrix::determinent()
//{
//	int n = mRow;
//	int *list = new int[n];
//	for (int i = 0; i < n; i++)
//	{
//		list[i] = i;
//	}  
//	double ret = det(mData, n ,0, list, 0.0);
//	delete [] list;
//	return ret;
//}


/*
///计算n阶行列式
double 
Matrix::determinent()
{
	return determinent(mRow);
}

double 
Matrix::determinent(const unsigned int n)
{
	double temp = 0;
	if (n == 1)
	{
		temp = mData[0][0];
	}
	else if (n == 2)
	{
		temp = mData[0][0]*mData[1][1]-mData[0][1]*mData[1][0];
	}
	else if (n == 3)
	{
		temp = mData[0][0]*mData[1][1]*mData[2][2]
		+mData[0][1]*mData[1][2]*mData[2][0]
		+mData[0][2]*mData[1][0]*mData[2][1]
		-mData[0][2]*mData[1][1]*mData[2][0]
		-mData[0][1]*mData[1][0]*mData[2][2]
		-mData[0][0]*mData[1][2]*mData[2][1];
	}
	else
	{
		temp = 0;
		//double b[mRow];
		double *b = new double[n];
		//double c[mRow][mCol];
		double **c = new double*[n];
		for(unsigned int i=0;i<n;i++)
		{
			c[i]=new double[n];
		}

		for (unsigned int i = 0; i < n; i++)
			b[i] = mData[i][0] * power(-1,i+1+1);
		for (unsigned int i = 0; i < n; i++)
			for (unsigned int j= 0; j < n-1; j++)
				mData[i][j] = mData[i][j+1];
		for (unsigned int i =0; i < n; i++)
			for (unsigned int j = 0; j < n-1; j++)
				c[i][j] = mData[i][j];
		for (unsigned int i = 0; i < n; i++)
		{
			//for (unsigned int j = i; j < n; j++)
			for (unsigned int j = i; j < n-1; j++)
			{
				for (unsigned int k = 0; k < n-1; k++)
				{
					mData[j][k] = mData[j+1][k];
				}
			}
			temp += b[i]*determinent(n-1);
			for (unsigned int i = 0;i < n; i++)
				for (unsigned int j = 0; j < n-1; j++)
					mData[i][j]= c[i][j];
		}

		if (b != NULL) delete [] b;
		if(c != NULL)
		{
			for(unsigned int i=0;i<n;i++)
			{
				delete[] c[i];
			}
			delete[] c;
		}
	}
	return temp;
}

unsigned int 
Matrix::power(unsigned int m, unsigned int n)
{
	unsigned int sum = 1;
	if (n == 0 && m != 0)
	{
		return 1;
	}
	else
	{
		for (unsigned int i = 0; i < n; i++)
			sum*=m;
		return sum;
	}
}
*/





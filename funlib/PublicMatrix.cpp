/*******************************************************************************
* Copyright（C）,2015-2020,DTXY Tech .Co.Ltd;
* 文 件 名: PublicMatrix.cpp
* 文件描述: 矩阵实现
*  作  者 : %王凯%，15802613961
* 创建日期: 2016-6-8 11:39:28
*******************************************************************************/

#pragma   warning(disable:4018   4244) 
#include "PublicMatrix.h"

#include <math.h>
#include <numeric> 
#include <algorithm>
#include <functional>

#include <iostream>

using namespace std;

PublicMatrix::PublicMatrix(void)
:
mRow(0),
mCol(0),
mData(NULL)
{
}


PublicMatrix::~PublicMatrix(void)
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
PublicMatrix::PublicMatrix(unsigned int row, unsigned int col)
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
PublicMatrix::PublicMatrix(const PublicMatrix& m)
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



unsigned int PublicMatrix::getRow() const
{
	return mRow;
}


unsigned int PublicMatrix::getCol() const
{
	return mCol;
}



void PublicMatrix::setUnit()
{
	for(unsigned int i=0;i<mRow;i++)
		for(unsigned int j=0;j<mCol;j++)
			mData[i][j] = (i==j)?1:0;
}

//transpose 转置
void
PublicMatrix::transpose(PublicMatrix &m)
{
	for(unsigned int i=0;i<mRow;i++)
	{
		for(unsigned int j=0;j<mCol;j++)
		{
sanityCheck(m, j, i);
			mData[i][j] = m.mData[j][i];
		}
	}
	//std::cout<<"--------转置---------"<<std::endl;
	//for (int i=0;  i<mRow;++i)
	//{
	//	for (int j=0;j<mCol;++j)
	//	{
	//		std::cout<<mData[i][j]<<" ";
	//	}
	//	std::cout<<std::endl;
	//}
}

 
void 
PublicMatrix::setVectorColAndTranspose(const unsigned int col, PublicMatrix &m) 
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
PublicMatrix::subVectorRowAssi(const PublicMatrix& m)
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
PublicMatrix::inverse(PublicMatrix &tmp) 
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
			cout << "There is no inverse PublicMatrix!"; 
			
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
	
//std::cout<<"-----------G~---------------"<<std::endl;
//	for (unsigned int i = 0; i < mRow; i++)
//	{
//		for (unsigned int j = 0; j < mCol; j++)
//		{
//			std::cout<<mData[i][j]<<" ";
//		}
//		std::cout<<std::endl;
//	}
	return true;
}


void
PublicMatrix::mul(PublicMatrix& rhs, PublicMatrix &lhs)//乘法运算
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
//std::cout<<"--------MU---------"<<std::endl;
	//for (int i=0; i<mRow;++i)
	//{
	//	for (int j=0;j<mCol;++j)
	//	{
	//		std::cout<<mData[i][j]<<" ";
	//	}
	//	std::cout<<std::endl;
	//}
}


//两个矩阵相同位子元素相乘？
void
PublicMatrix::dotMulAssi(const PublicMatrix& m)
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
PublicMatrix::sumRow(PublicMatrix &m) 
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
PublicMatrix::mulAssi(double d)
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
PublicMatrix::expAssi()
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
PublicMatrix::divAssi(double d)
{
	for(unsigned int i=0;i<mRow;i++)
	{
		for(unsigned int j=0;j<mCol;j++)
		{
			mData[i][j]=mData[i][j]/d;
		}
	}
}


void PublicMatrix::insertCol(const unsigned int col, PublicMatrix &m)
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
PublicMatrix::dotMulVectorRowAssi(const PublicMatrix& m) 
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

void PublicMatrix::setZero()
{
    for(unsigned int i=0;i<mRow;i++)
        fill(mData[i],mData[i]+mCol,0);
}


void 
PublicMatrix::addAssi(double d) 
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
PublicMatrix::dotDivVectorColAssi(const PublicMatrix& m)
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
PublicMatrix::sumCol(PublicMatrix &m)
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


double PublicMatrix::getValue(unsigned int i,unsigned int j)
{
sanityCheck(*this, i, j);
	return mData[i][j];
}

void 
PublicMatrix::setValue(unsigned int i,unsigned int j, double vv)
{
sanityCheck(*this, i, j);
	mData[i][j] = vv;
}



void
PublicMatrix::setVectorCol(const unsigned int col, PublicMatrix &m)
{
	//从this矩阵复制row行所有元素到新矩阵中
	for (unsigned int i = 0; i < mRow; i++)
	{
sanityCheck(m, i, col);
		mData[i][0] = m.mData[i][col];
	}
}





void 
PublicMatrix::subVectorCol(PublicMatrix &rhs, const PublicMatrix& lhsVector)
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
PublicMatrix::add(const PublicMatrix& rhs, const PublicMatrix& lhs) 
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
PublicMatrix::dotMulVectorRow(const PublicMatrix& m) 
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
PublicMatrix::sub(const PublicMatrix &rhs, const PublicMatrix& lhs) 
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
PublicMatrix::absAssi()
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
PublicMatrix::mergeCol(const unsigned int col, PublicMatrix &m)
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
PublicMatrix::copyMem(PublicMatrix &m)
{
	for(unsigned int i=0;i<mRow;i++)
	{
		copy(m.mData[i],m.mData[i]+mCol,mData[i]);
	}
}

void 
PublicMatrix::setVar(unsigned int i,const std::vector<double> &val)		
{ 
	for(unsigned int j=0;j<mCol;j++) 
	{
sanityCheck(*this, i, j);
		mData[i][j]=val[j];
	}
}


void 
PublicMatrix::display()
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
PublicMatrix::setVar(vector<double> &val)		
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
PublicMatrix::setVar(unsigned int i,double *val)		
{ 
	for(unsigned int j=0;j<mCol;j++) 
	{
		mData[i][j]=val[j];
	}
}

void
PublicMatrix::getVar(unsigned int i, std::vector<double> &val)
{
	for(unsigned int j=0;j<mCol;j++) 
	{
		val.push_back(mData[i][j]);
	}
}
bool
PublicMatrix::getVar(unsigned int i, std::vector<double> &val,
					 double & msim,std::vector<double> &pm,const std::vector<double> &rData,
					 const std::vector<double> &ma)
{
	if(rData.size()!=ma.size()||rData.size()!=mCol||0==mCol) 
		return false;
	double sim;
	msim = 0;
	for(unsigned int j=0;j<mCol;j++) 
	{
		val.push_back(mData[i][j]);

		sim=(ma[j]+0.0000000000001)/(ma[j]+abs(mData[i][j]-rData[j])+0.0000000000001);
		/*if(0==ma[j]+abs(mData[i][j]-rData[j]))
			sim=1;*/
		pm.push_back(sim);
		msim+=sim;
	}
	msim=msim/mCol;
	return true;
}
void PublicMatrix::CheckCap(const int itype,const double &simtemp,const double &RtValue,const double &PerValue,double &sim)
{
	switch (itype)
	{
	case 1:
		sim = RtValue<PerValue?simtemp*100:100;
		break;
	case 2:
		sim = RtValue>PerValue?simtemp*100:100;
		break;
	case 3:
		sim = simtemp*100 ;
		break;
	default:
		sim = simtemp*100 ;
	}
}
bool
PublicMatrix::getVar(unsigned int i, std::vector<double> &val,
					 double & msim,std::vector<double> &pm,const DTRowParam &rData,
					 const std::vector<double> &ma)
{
	if(rData.size()!=ma.size()||rData.size()!=mCol||0==mCol) 
		return false;
	double sim,simTemp,simup,simlow,amax,amin;
	msim = 0;
	for(unsigned int j=0;j<mCol;j++) 
	{
		if(23==j||24==j||25==j||29==j)
			int itemp = 100;
		val.push_back(mData[i][j]);

		if (0==rData[j].m_iParamSource)
		{
			if (rData[j].m_Interval.m_IsUpLimit&&rData[j].m_Interval.m_IsLowLimit)
			{
				//amax = (rData[j].m_Interval.m_UpLimit-mData[i][j])/9;
				amax = rData[j].m_Interval.m_UpLimit-rData[j].mCurValue;
				simup = (amax+0.0000000000001)/(amax+abs(mData[i][j]-rData[j].mCurValue)+0.0000000000001);
				//amin = (mData[i][j]-rData[j].m_Interval.m_LowLimit)/9;
				amin = rData[j].mCurValue-rData[j].m_Interval.m_LowLimit;
				simlow  = (amin+0.0000000000001)/(amin+abs(mData[i][j]-rData[j].mCurValue)+0.0000000000001);
				simTemp = amax>amin?amin:amax;
				simTemp = simup>simlow?simlow:simup;
				CheckCap(rData[j].m_iType,simTemp,rData[j].mCurValue,mData[i][j],sim);
			}
			else if (rData[j].m_Interval.m_IsUpLimit&&!rData[j].m_Interval.m_IsLowLimit)
			{
				//amax = (rData[j].m_Interval.m_UpLimit-mData[i][j])/9;
				amax = rData[j].m_Interval.m_UpLimit-rData[j].mCurValue;
				simup = (amax+0.0000000000001)/(amax+abs(mData[i][j]-rData[j].mCurValue)+0.0000000000001);
				CheckCap(rData[j].m_iType,simup,rData[j].mCurValue,mData[i][j],sim);
			}
			else if (!rData[j].m_Interval.m_IsUpLimit&&rData[j].m_Interval.m_IsLowLimit)
			{
				//amin = (mData[i][j]-rData[j].m_Interval.m_LowLimit)/9;
				amin = rData[j].mCurValue-rData[j].m_Interval.m_LowLimit;
				simlow  = (amin+0.0000000000001)/(amin+abs(mData[i][j]-rData[j].mCurValue)+0.0000000000001);
				CheckCap(rData[j].m_iType,simlow,rData[j].mCurValue,mData[i][j],sim);
			}
			else if (!rData[j].m_Interval.m_IsUpLimit&&!rData[j].m_Interval.m_IsLowLimit)
			{
				double d1 = ma[j];
				double d2 = mData[i][j];
				double d3 = rData[j].mCurValue;
				double d4 = abs(mData[i][j]-rData[j].mCurValue);
				//sim = 100*(ma[j]+0.0000000000001)/(ma[j]+abs(mData[i][j]-rData[j].mCurValue)+0.0000000000001);
				simTemp = (ma[j]+0.0000000000001)/(ma[j]+abs(mData[i][j]-rData[j].mCurValue)+0.0000000000001);
				CheckCap(rData[j].m_iType,simTemp,rData[j].mCurValue,mData[i][j],sim);
			}
		}
		else if (1==rData[j].m_iParamSource)
		{
			simTemp = (rData[j].m_ParamValue+0.0000000000001)/(rData[j].m_ParamValue+abs(mData[i][j]-rData[j].mCurValue)+0.0000000000001);
			CheckCap(rData[j].m_iType,simTemp,rData[j].mCurValue,mData[i][j],sim);
		}
		//sim=(ma[j]+0.0000000000001)/(ma[j]+abs(mData[i][j]-rData[j].pValue)+0.0000000000001);
		/*if(0==ma[j]+abs(mData[i][j]-rData[j]))
			sim=1;*/
		sim = sim>=0.001?sim:0;
		pm.push_back(sim);
		msim+=sim;
	}
	msim=msim/mCol;
	return true;
}
void
PublicMatrix::setGWVar(const std::vector<std::vector<double>> rMuData, DTRowParam rData)
{
	double rowSum,sum;
	sum=0;
	for (int i=0; i<rMuData.size();++i)
	{
		rowSum=0;
		for(int j=0;j<rData.size();++j)
		{
			rowSum+=pow((rData[j].mCurValue-rMuData[i][j]),2);
		}
		mData[i][0]=sqrt(rowSum);
	}
}
void
PublicMatrix::setGWVar(const std::vector<std::vector<double>> rMuData, std::vector<double> rData)
{
	double rowSum,sum;
	sum=0;
	for (int i=0; i<rMuData.size();++i)
	{
		rowSum=0;
		for(int j=0;j<rData.size();++j)
		{
			rowSum+=pow((rData[j]-rMuData[i][j]),2);
		}
		mData[i][0]=sqrt(rowSum);
		//sum+=mData[i][0];
	}
//std::cout<<"-------GW---------"<<std::endl;
//	for (int i=0; i<rMuData.size();++i)
//	{
//		std::cout<<mData[i][0]<<std::endl;
//	}
}
bool
PublicMatrix::setGWoVar()
{
	double sum=0;
	if(1!=mCol) return false;
	for (unsigned int i=0;i<mRow;++i)
	{
       sum+=mData[i][0];
	}
	for (unsigned int i=0;i<mRow;++i)
	{
		if(0==sum) sum=REALMIN;
		mData[i][0]=mData[i][0]/sum;
	}
	return true;
}
void
PublicMatrix::getVarAndTranspose(unsigned int col, std::vector<double> &val)
{
	for(unsigned int i=0;i<mRow;i++) 
	{
		val.push_back(mData[i][col]);
	}
}

void
PublicMatrix::sanityCheck(const PublicMatrix &m, unsigned int i, unsigned int j)
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
PublicMatrix::determinent()
{
	return determinent(mData, mRow);
}

double 
PublicMatrix::determinent(double **data, int n)
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

void PublicMatrix::setMutoG(PublicMatrix tmp)
{
	double sum = 0;
	for (unsigned int i = 0; i < tmp.mRow; i++)
	{
		for (unsigned int j = 0; j < tmp.mRow; j++)
		{
			if (i==j)
			{
				mData[i][j]=0;
			}
			else
			{
				sum = 0;
				for (unsigned int m = 0; m < tmp.mCol; m++)
					sum+=pow((tmp.mData[i][m]-tmp.mData[j][m]),2);
				mData[i][j]=sqrt(sum);
			}
		}
	}
	//std::cout<<"-----------G---------------"<<std::endl;
	//for (unsigned int i = 0; i < mRow; i++)
	//{
	//	for (unsigned int j = 0; j < mCol; j++)
	//	{
	//		std::cout<<mData[i][j]<<" ";
	//	}
	//	std::cout<<std::endl;
	//}
	
}

void 
PublicMatrix::sumPostNMTest()
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
//PublicMatrix::swap(int *a, int *b)
//{
//	int m;
//	m = *a;
//	*a = *b;
//	*b = m;
//}
//
////求逆序对的个数
//int 
//PublicMatrix::inver_order(int list[], int n)
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
//PublicMatrix::sgn(int order)
//{
//	return order % 2? -1:1;
//}
//
//
//double 
//PublicMatrix::det(double **p, int n, int k, int list[], double sum)
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
//PublicMatrix::determinent()
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
PublicMatrix::determinent()
{
	return determinent(mRow);
}

double 
PublicMatrix::determinent(const unsigned int n)
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
PublicMatrix::power(unsigned int m, unsigned int n)
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






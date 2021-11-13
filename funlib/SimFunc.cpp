#include "SimFunc.h"
#include <math.h>
#include <sstream> 
#include <string> 

SimFunc::SimFunc(void)
:
mNSampleNum(0),
mDPointNum(0),
mMu(NULL),
mStrErrorMessage("")
{
}
SimFunc::SimFunc(const unsigned int n, const unsigned int d)
:
mNSampleNum(n),
mDPointNum(d),
mMu(NULL),
mG(NULL),
mStrErrorMessage("")
{
	//mTestPostNM = new Matrix(mNSampleNum, mMLevel);
}
SimFunc::~SimFunc()
{
	if (mMu != NULL) delete mMu;
	if (mG != NULL) delete mG;
	if (GW != NULL) delete GW;
	if (GA != NULL) delete GA;
	if (transDataDN != NULL) delete transDataDN;
	if (EstData != NULL) delete EstData;
}
bool SimFunc::setMerry(const DTRows &vectorDataMu,const DTRows &vectorDataG)
{
	mDPointNum=vectorDataMu[0].size();
	if(vectorDataG.size()!= vectorDataG[0].size()||vectorDataG.size()!= vectorDataMu.size()) return false;
	mMu = new PublicMatrix(vectorDataMu.size(), vectorDataMu[0].size());
	for (unsigned int i = 0; i < vectorDataMu.size(); i++)
	{
		mMu->setVar(i, vectorDataMu[i]);
	}
	mG = new PublicMatrix(vectorDataG.size(), vectorDataG[0].size());

	for (unsigned int i = 0; i < vectorDataG.size(); i++)
	{
		mG->setVar(i, vectorDataG[i]);
	}
	if(mMu->getRow()!=mG->getRow()) return false;
	GW=new PublicMatrix(vectorDataMu.size(),1);
	GA=new PublicMatrix(vectorDataMu.size(),1);
	transDataDN=new PublicMatrix(1,vectorDataMu.size());
	EstData=new PublicMatrix(1,mDPointNum);
	return true;
}

bool SimFunc::setData(const DTRows &vectorDataMu,const DTRows &vectorDataG)
{
	if(mMu== NULL||mG== NULL) return false;
	for (unsigned int i = 0; i < vectorDataMu.size(); i++)
	{
		mMu->setVar(i, vectorDataMu[i]);
	}
	for (unsigned int i = 0; i < vectorDataG.size(); i++)
	{
		mG->setVar(i, vectorDataG[i]);
	}
	if(mMu->getRow()!=mG->getRow()) return false;
	return true;
}
/*******************************************************************************
* 函 数 名: .
* 函数描述: 一组测点期望值计算
* 参数说明: 
*    入 参: const vector<double> rData 一组测点数据,const vector<DTRow> muData 期望值集合 DTRows rGData G矩阵
*    出 参: std::vector<double> &mt 一组测点期望值 
* 返 回 值: bool
*    成 功:
*    失 败:	
*  作  者 : 王凯，15802613961
* 创建日期: 2016-6-14 01:02:32
*******************************************************************************/
bool SimFunc::calEstValue(const DTRow &rData,const DTRows &rMuData,const DTRows &rGData,DTRow &mt)
{
	//bool rslt=setMerry(rMuData,rGData);
	//if(!rslt) return false;
	//PublicMatrixPtr GW=new PublicMatrix(rMuData.size(),1);
	//PublicMatrixPtr GA=new PublicMatrix(rMuData.size(),1);
	//PublicMatrixPtr transDataDN=new PublicMatrix(1,rMuData.size());
	//PublicMatrixPtr EstData=new PublicMatrix(1,rData.size());
	GW->setGWVar(rMuData,rData);
	//std::cout<<"--------A---------"<<std::endl;
	GA->mul(*mG,*GW);
	GA->setGWoVar();
	//std::cout<<"--------A转置---------"<<std::endl;
	transDataDN->transpose(*GA);
	//std::cout<<"--------XEST---------"<<std::endl;
	EstData->mul(*transDataDN,*mMu);

	EstData->getVar(0,mt);

	/*if (GW!=NULL) delete GW;
	if (GA!=NULL) delete GA;
	if (transDataDN!=NULL) delete transDataDN;
	if (EstData!=NULL) delete EstData;*/
	return true;
}
bool SimFunc::calEstValue(const DTRowParam &rData,const DTRows &rMuData,
						  const DTRow &rMaData,const DTRows &rGData,DTRow &mt,
						  double & msim,std::vector<double> &pm)
{
	if(rData.size()!=rMaData.size()) return false;
	GW->setGWVar(rMuData,rData);
	//std::cout<<"--------A---------"<<std::endl;
	GA->mul(*mG,*GW);
	GA->setGWoVar();
	//std::cout<<"--------A转置---------"<<std::endl;
	transDataDN->transpose(*GA);
	//std::cout<<"--------XEST---------"<<std::endl;
	EstData->mul(*transDataDN,*mMu);

	EstData->getVar(0,mt,msim,pm,rData,rMaData);
	return true;
}
bool SimFunc::calEstValue(const DTRow &rData,const DTRows &rMuData,const DTRow &rMaData,const DTRows &rGData,DTRow &mt,
				 double & msim,std::vector<double> &pm)
{
	if(rData.size()!=rMaData.size()) return false;
	GW->setGWVar(rMuData,rData);
	//std::cout<<"--------A---------"<<std::endl;
	GA->mul(*mG,*GW);
	GA->setGWoVar();
	//std::cout<<"--------A转置---------"<<std::endl;
	transDataDN->transpose(*GA);
	//std::cout<<"--------XEST---------"<<std::endl;
	EstData->mul(*transDataDN,*mMu);

	EstData->getVar(0,mt,msim,pm,rData,rMaData);
	return true;
}
// 功能描述: 相似度算法
/*******************************************************************************
* 函 数 名: .
* 函数描述: 相似度算法
* 参数说明: 
*    入 参: const vector<double> rcData 一组测点数据,const vector<DTRow> muData 期望值集合
*    出 参: double & msim 样本相似度 std::vector<double> &pm 测点相似度集合 std::vector<double> &mt 一组测点期望值 int &num 噪声比
           std::string &err 异常信息
* 返 回 值:
*    成 功:
*    失 败:	
*  作  者 : 王凯，15802613961
* 创建日期: 2016-1-5 16:44:32
*******************************************************************************/

bool 
SimFunc::SIMROWDeal(const DTRow &rData,const DTRows &GData, const DTRow &maData, 
					const DTRows &muData,double & msim,std::vector<double> &pm,std::vector<double> &mt,std::string &err)
{
	bool rslt;
    int num=0;
    double sum;
    std::vector<double> temppm;
    std::vector<std::vector<double>> map_tempam;
    sum=0;
    msim=0;
    std::string strTemp;
    std::ostringstream oss;
    err.empty();
	if(0==rData.size()) return false;
	err=1;
    rslt = setMerry(muData,GData);
	err=2;
	if(!rslt) return false;
	err=3;
	//rslt=calEstValue(rData,muData,GData,mt);
	rslt=calEstValue(rData,muData,maData,GData,mt,msim,pm);
	err=4;
    if (0==muData.size())
    {
        err="期望值集合为空";
        return false;
    }
	if (maData.size()!=rData.size())
	{
		oss <<"\n数据集合rData与期望值集合maData行数据个数不匹配";
		err += oss.str();
		return false;
	}
	/*for (int i=0;i<rData.size();i++)
	{
		pim=maData[i]/(maData[i]+abs(rData[i]-mt[i]));
		pm.push_back(pim);
		msim+=pim;
	}
	msim=msim/rData.size();*/
    /*for (int i=0;i<muData.size();i++)
    {
        if (0==muData[i].size())
        {
            err=" 期望值矩阵有行数据为空";
            continue;
        }
        if (rData.size()!=muData[i].size()||maData.size()!=rData.size())
        {
            oss <<"\n数据集合与期望值集合第" << i<<"行数据个数不匹配";
            err += oss.str();
            continue;
        }
        temppm.clear();
        sum=0;
        for(int j=0;j<muData[i].size();j++)
        {
          //if(0==rData[j]&&0==muData[i][j])
          if(0==(maData[j]+abs(rData[j]-muData[i][j])))
            pim=1;
          else   
            pim=maData[j]/(maData[j]+abs(rData[j]-muData[i][j]));
            //pim=0.5*(abs(rData[j]+muData[i][j]))/(0.5*(abs(rData[j]+muData[i][j]))+abs(rData[j]-muData[i][j]));
          temppm.push_back(pim);
          sum+=pim;
        }
        sum=sum/muData[i].size();
        map_tempam.push_back(temppm);
        if (sum>msim)
        {
            msim=sum;
            num=i;
        }
    }
    for (int i=0;i<muData[num].size();i++)
    {
        //mt.push_back(muData[num][i]);  
        pm.push_back(map_tempam[num][i]);
    }
	*/
    return true;
}
bool 
SimFunc::SIMROWDealEx(DTRowParam rData,const DTRows &GData,const DTRow &maData,const DTRows &muData,
				double & msim,std::vector<double> &pm,std::vector<double> &mt,std::string &err)
{
	bool rslt;
	int num=0;
	double sum;
	std::vector<double> temppm;
	std::vector<std::vector<double>> map_tempam;
	sum=0;
	msim=0;
	std::string strTemp;
	std::ostringstream oss;
	err.empty();
	if(0==rData.size()) return false;
	err=1;
	rslt = setMerry(muData,GData);
	err=2;
	if(!rslt) return false;
	err=3;
	rslt = calEstValue(rData,muData,maData,GData,mt,msim,pm);
	err=4;
	if (0==muData.size())
	{
		err="期望值集合为空";
		return false;
	}
	if (maData.size()!=rData.size())
	{
		oss <<"\n数据集合rData与期望值集合maData行数据个数不匹配";
		err += oss.str();
		return false;
	}
	return true;
}
bool
SimFunc::SIMDeal(const DTRows &rcData,const DTRows &GData,const DTRow &maData,const DTRows &muData,double &minSim,double &maxSim,double &avSim,DTRow &vSim,DTRows &vpm,DTRows &vmt,std::string &err)
{
	bool rslt;
    int num=0;
    //double pim;
    double sim;
    minSim=1;
    maxSim=0;
    avSim=0;
    //std::string strTemp;
    std::ostringstream oss;
    //std::stringstream ss;
	DTRow mt;
    std::vector<double> temppm;
    std::vector<std::vector<double>> map_tempam;
    err.empty();
	rslt=setMerry(muData,GData);
    for (int i=0;i<rcData.size();i++)
    {
        if (0==muData.size())
        {
            err="期望值集合为空";
            minSim=1;
            maxSim=1;
            avSim=1;
            return false;
        }
		mt.clear();
		map_tempam.clear();
		temppm.clear();
		//rslt=calEstValue(rcData[i],muData,GData,mt);
		rslt=calEstValue(rcData[i],muData,maData,GData,mt,sim,temppm);
		vmt.push_back(mt);
		vpm.push_back(temppm);
		vSim.push_back(sim);
		if (sim<minSim)
		{
			minSim=sim;
		}
		if(sim>maxSim) 
		{
			maxSim=sim;
		}
		avSim+=sim;

        //sim=0;
        //num=0;
        //map_tempam.clear();
        //for (int m=0;m<muData.size();m++)
        //{
        //    if (0==muData[m].size())
        //    {
        //        err+=" 期望值矩阵有行数据为空";
        //        continue;
        //    }
        //    /*ss<<i;
        //    ss <<"数据集合第"<< i<<"行与期望值集合第" << m<<"行数据个数不匹配";
        //    oss <<"数据集合第"<< i<<"行与期望值集合第" << m<<"行数据个数不匹配";
        //        strTemp += oss.str();
        //    err+="数据集合第%d行与期望值集合第%d行数据个数不匹配";*/
        //    if (rcData[i].size()!=muData[m].size()||maData.size()!=rcData[i].size())
        //    {
        //        oss <<"\n数据集合第"<< i<<"行与期望值集合第" << m<<"行数据个数不匹配";
        //        /*strTemp += oss.str();
        //        err+="数据集合第%d行与期望值集合第%d行数据个数不匹配";*/
        //        err += oss.str();
        //        return false;
        //    }
        //    pim=0;
        //    temppm.clear();
        //    for(int j=0;j<muData[m].size();j++)
        //    {
        //        //if(0==rcData[i][j]&&0==muData[m][j])
        //        if(0==(maData[j]+abs(rcData[i][j]-muData[m][j])))
        //            pim+=1;
        //        else 
        //           pim+=maData[j]/(maData[j]+abs(rcData[i][j]-muData[m][j]));  
        //           /*pim+=0.5*(abs(rcData[i][j]+muData[m][j]))/(0.5*(abs(rcData[i][j]+muData[m][j]))+abs(rcData[i][j]-muData[m][j]));*/
        //        temppm.push_back(pim);
        //    }
        //    pim=pim/muData[m].size();
        //    map_tempam.push_back(temppm);
        //    if (pim>sim)
        //    {
        //        sim=pim;
        //        num=m;
        //    }
        //}
        //vSim.push_back(sim);
        ////vmt.push_back(muData[num]);
        //vpm.push_back(map_tempam[num]);
        //if (sim<minSim)
        //{
        //    minSim=sim;
        //}
        //if(sim>maxSim) 
        //{
        //   maxSim=sim;
        //}
        //avSim+=sim;
		
    }
    if (0==rcData.size())
    {
        err="样本数据为空";
        minSim=1;
        maxSim=1;
        avSim=1;
        return false;
    }
    avSim=avSim/rcData.size();
    
    return true;
}
BaseSim::BaseSim(void)
:
mNSampleNum(0),
mDPointNum(0),
mData(NULL),
mGMu(NULL),
mStrErrorMessage("")
{
}
BaseSim::BaseSim(const unsigned int n, const unsigned int d)
:
mNSampleNum(n),
mDPointNum(d),
mData(NULL),
mGMu(NULL),
mGnMu(NULL),
mStrErrorMessage("")
{
	//mTestPostNM = new Matrix(mNSampleNum, mMLevel);
}
BaseSim::~BaseSim(void)
{
	if (mGMu != NULL) delete mGMu;
	if (mGnMu != NULL) delete mGnMu;
	if (mData != NULL) delete mData;
}
bool
BaseSim::setData(const DTRows &vectorData)
{
	if (vectorData.size() != mNSampleNum) 
	{
		mStrErrorMessage = "Data exception!";
		return false;
	}
	mData = new PublicMatrix(mNSampleNum, mDPointNum);
	mGMu  = new PublicMatrix(mNSampleNum, mNSampleNum);
	mGnMu = new PublicMatrix(mNSampleNum, mNSampleNum);
	for (unsigned int i = 0; i < vectorData.size(); i++)
	{
		if (vectorData[i].size() != mDPointNum) return false;
		mData->setVar(i, vectorData[i]);
	}
	return true;
}

bool BaseSim::calculate(const DTRows &rMuData, 
			   DTRows &rGData)
{
	bool rslt = setData(rMuData);
	if (!rslt) return false;
	mGMu->setMutoG(*mData);
	mGnMu->inverse(*mGMu);
	getData(rGData);
	return true;
}

void BaseSim::getData(DTRows &rGData)
{
	for (unsigned int i = 0; i < mGnMu->getCol(); i++)
	{
		DTRow muRow;
		rGData.push_back(muRow);
	}
	for(unsigned int col = 0; col < mGnMu->getCol(); col++)
	{
		mGnMu->getVarAndTranspose(col, rGData[col]);
	}
	
}
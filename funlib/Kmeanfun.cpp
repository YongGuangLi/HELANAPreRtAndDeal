#include "Kmeanfun.h"

#include <time.h>
#include <math.h>
#include <algorithm>

void Kmeanfun::KmeanFun(unsigned short iM,DTRows YbData,DTRow &Alpha0,unsigned short &iAlLine,unsigned short &iAlDim,DTRow &Mu0,unsigned short &iMu0Line,unsigned short &iMu0Dim,DTRow &Sigma0,unsigned int &iSiLine,unsigned int &iSiDim,unsigned int &iSiLineLine)
{
	DTRow YbDataEx;
	srand(time(NULL));//
	std::string strRandLine = "";
	DTRow Mu;
	unsigned short iN = 0,iDim = 0,iRandLine = 0,iTotalLine = 0,iMuLine = 0,iMuDim = 0;
	iN = (unsigned short)YbData.size();
	iDim = (unsigned short)YbData.begin()->size();

	//
	for(DTRows::iterator it = YbData.begin(); it != YbData.end();++it)
		for(DTRow::iterator inner_it = it->begin();inner_it != it->end();++inner_it)
			YbDataEx.push_back(*inner_it);
	//
	
	std::vector<short> myRandLine;
	for(;;)
	{
		iRandLine = rand()%iN+1;
		strRandLine = IntToString(iRandLine);
		
		if(find(myRandLine.begin(),myRandLine.end(),iRandLine) == myRandLine.end())
		{
			myRandLine.push_back(iRandLine);
			iTotalLine++;
			for(unsigned int ix=(iRandLine-1)*iDim;ix<=iRandLine*iDim-1;ix++)
		    	Mu0.push_back(YbDataEx[ix]);
		}
		if(iTotalLine>=iM)
			break;
	}
	
	iMu0Line = iDim;
	iMu0Dim = iM;
	Mu = Mu0;
	
    DTRow DataId;
	unsigned short iDataIdLine = iN, iDataIdDim = 1,iTmp = 0;
	for(unsigned short iter = 0;iter<100;iter++)
	{
		
		iMuLine = iMu0Line;
		iMuDim = iMu0Dim;

		DataId.clear();
		for(unsigned short i=1;i<=iN;i++)
		{
			unsigned short iMinLine = 0;
			double fMinValue = 0,fSumLine = 0;
			
            for(unsigned short iy=1;iy<=iM;iy++)
			{
				iTmp=0;
				fSumLine = 0;
				for(unsigned int ix=(i-1)*iDim;ix<=i*iDim-1;ix++)
				{
					iTmp++;
					fSumLine = fSumLine+pow(YbDataEx[ix]-Mu[(iy-1)*iDim+iTmp-1],2);
				}
				if(iy == 1)
				{
					fMinValue = fSumLine;
					iMinLine = 1;
				}
				else if(fSumLine<fMinValue)
				{
					fMinValue = fSumLine;
					iMinLine = iy;
				}
			}
			
			DataId.push_back(iMinLine);
		}

		DTRow IdTmp;
		unsigned short iIdTmpLine = 0,iIdTmpDim = 1;
		for(unsigned short i=1;i<=iM;i++)
		{
			IdTmp.clear();
			iIdTmpLine = 0;
			for(unsigned short ix=1;ix<=iN;ix++)
			{
				if(i == (unsigned short)DataId[ix-1])
				{
					iIdTmpLine++;
					IdTmp.push_back(ix);
				}
			}
			
			if(iIdTmpLine>1)
			{
				double fSumDim = 0;
				for(unsigned short iy=1;iy<=iDim;iy++)
				{
					fSumDim = 0;
					for(unsigned short ix=1;ix<=iIdTmpLine;ix++)
						fSumDim = fSumDim+YbDataEx[((unsigned short)IdTmp[ix-1]-1)*iDim+iy-1];
				    fSumDim = fSumDim/iIdTmpLine;
										
					Mu[(i-1)*iDim+iy-1]=fSumDim;
				}
			}
		}
		
		double fSumDim = 0;
		for(unsigned int i=0;i<iM*iDim;i++)
			fSumDim = fSumDim+abs(Mu[i]-Mu0[i]);
		
		if(fSumDim<0.00001)
			break;

		//
		Mu0 = Mu;
	}
	DTRow IdTmp;
	unsigned short iIdTmpLine = 0,iIdTmpDim = 1;
	iAlLine = 1;
	iAlDim = iM;

	iSiLine = iDim;
	iSiDim = iDim;
	iSiLineLine = iM;

	for(unsigned short i=1;i<=iM;i++)
	{
		IdTmp.clear();
	    iIdTmpLine = 0,iIdTmpDim = 1;
		for(unsigned short ix=1;ix<=iN;ix++)
		{
			if(i == (unsigned short)DataId[ix-1])
			{
				iIdTmpLine++;
				IdTmp.push_back(ix);
			}
		}
		Alpha0.push_back(iIdTmpLine+0.0000000001);
		if(iIdTmpLine<1)
		{
			for(unsigned short ix=1;ix<=iDim;ix++)
			{
				for(unsigned short iy=1;iy<=iDim;iy++)
				{
					if(ix == iy)
			    		Sigma0.push_back(0.0000000001);
					else
						Sigma0.push_back(0);
				}
			}
		}
		else
		{
			DTRow TmpData;
        	unsigned short iTmpDataLine = 0,iTmpDataDim = iDim;
			DTRow TmpDataEx;
        	unsigned short iTmpDataExLine = 0,iTmpDataExDim = iDim;
			for(unsigned short iI=1;iI<=iIdTmpLine;iI++)
			{
				iTmpDataLine++;
				iTmpDataExLine++;
				for(unsigned short iy=1;iy<=iDim;iy++)
				{
					TmpData.push_back(YbDataEx[((unsigned short)IdTmp[iI-1]-1)*iDim+iy-1]);
					TmpDataEx.push_back(YbDataEx[((unsigned short)IdTmp[iI-1]-1)*iDim+iy-1]);
				}
			}
			
			for(unsigned short ix=1;ix<=iTmpDataLine;ix++)
			{
				iTmpDataExLine++;
				for(unsigned short iy=1;iy<=iDim;iy++)
					TmpDataEx.push_back(TmpData[(ix-1)*iDim+iy-1]);
			}
			
			DTRow TmpSig;
        	unsigned short iTmpSigLine = iDim,iTmpSigDim = iDim;
			double fSumFC = 0;
			for(unsigned short ix=1;ix<=iDim;ix++)
			{
				for(unsigned short iy=1;iy<=iDim;iy++)
				{
					fSumFC = 0;
					
					double xP=0,yP=0,xSum=0,ySum=0;
					for(unsigned short iL=1;iL<=iTmpDataExLine;iL++)
					{
						xSum = xSum+TmpDataEx[(iL-1)*iDim+ix-1];
						ySum = ySum+TmpDataEx[(iL-1)*iDim+iy-1];
					}
					xP = xSum/iTmpDataExLine;
					yP = ySum/iTmpDataExLine;
					
					for(unsigned short iL=1;iL<=iTmpDataExLine;iL++)
						fSumFC = fSumFC+(TmpDataEx[(iL-1)*iDim+ix-1]-xP)*(TmpDataEx[(iL-1)*iDim+iy-1]-yP);
					
					TmpSig.push_back(fSumFC/(iTmpDataExLine-1));
				}
			}
			
			for(unsigned short ix=1;ix<=iDim;ix++)
			{
				for(unsigned short iy=1;iy<=iDim;iy++)
				{
					if(ix == iy)
				    	Sigma0.push_back(TmpSig[(ix-1)*iDim+iy-1]+0.0000000001);
					else
						Sigma0.push_back(TmpSig[(ix-1)*iDim+iy-1]);
				}
			}
		}
	}
	DTRow ZZMu0;
	for(unsigned short iy=1; iy<=iDim; iy++)
		for(unsigned short ix=1; ix<=iM; ix++)
			ZZMu0.push_back(Mu0[(ix-1)*iDim+iy-1]);
	Mu0 = ZZMu0;
	
	double fSumAl = 0;
	for(unsigned short i=1;i<=iM;i++)
		fSumAl = fSumAl+Alpha0[i-1];
	if(!(fabs(fSumAl)<0.000001))
	{
		for(unsigned short i=1;i<=iM;i++)
			Alpha0[i-1] = Alpha0[i-1]/fSumAl;
	}
}

std::string 
Kmeanfun::IntToString(int num) 
{   
	char pp[64] = { 0 };    
	sprintf( pp, "%d", num ); // 将num以%f的形式存储到p中     
	return std::string(pp); // 用p初始化string对象str
}

#ifndef __KMEANFUN_H__
#define __KMEANFUN_H__

#include "AlgoVarDef.h"

class Kmeanfun
{
public:
	Kmeanfun(){};
	~Kmeanfun(){};

	static void KmeanFun(unsigned short iM, DTRows YbData,
		DTRow &Alpha0,unsigned short &iAlLine, unsigned short &iAlDim,
		DTRow &Mu0, unsigned short &iMu0Line,	unsigned short &iMu0Dim,
		DTRow &Sigma0, unsigned int &iSiLine,unsigned int &iSiDim,unsigned int &iSiLineLine);

private:
		static std::string IntToString(int num) ;
};
#endif
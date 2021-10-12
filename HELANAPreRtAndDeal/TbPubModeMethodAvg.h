/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: TbPubModeMethodAvg.h
* 文件描述: 查询模型期望值方法配置
*  作  者 : %王凯%，
* 创建日期: 2016-1-16 16:50:33
*******************************************************************************/
#ifndef __TBPUBMODEMETHODAVG_H__
#define __TBPUBMODEMETHODAVG_H__

#include "TypeDef.h"
#include "RDbOperationComplex.h"

#define MODEFUN_CONFIG						"TbPubModeMethodAvg"

class TbPubModeMethodAvg:public RDbOperationComplex
{
private:

public:
	TbPubModeMethodAvg();
	TbPubModeMethodAvg(RsdbAdapter * QtOpt);
	~TbPubModeMethodAvg(void);

	bool loadDB(MapStringToBool &mMapModleNameStatus,
				MapStringToModeMethodAvg &pModeFunInfo,
				MapStringToString &pPointSourceName,
				std::string strCon);
	//bool bindVar();
	bool loadValue(MapStringToBool &mMapModleNameStatus,MapStringToModeMethodAvg &pModeFunInfo,MapStringToString &pPointSourceName);
	void SetOciMemory();
	void FreeOciMemory();
	
private:
    bool GetMuValue(std::vector<std::string>& tempVec,MethodAvg* condtion_fun,const int num,const int typeVec);	
};   
#endif//__TBPUBMODEMETHODAVG_H__

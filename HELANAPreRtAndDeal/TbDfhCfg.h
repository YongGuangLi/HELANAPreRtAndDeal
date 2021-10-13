#ifndef __TBDFHCFG_H__
#define __TBDFHCFG_H__

#include "TypeDef.h"
#include "RDbOperationComplex.h"
#define CFG_DFH						"TbDfhCfg"
class TbDfhCfg:public RDbOperationComplex
{
private: 

	bool loadValue(MapStringToSetCfg &mapSetInfo);

public:
	TbDfhCfg(void);
	TbDfhCfg(RsdbAdapter * QtOpt);
	~TbDfhCfg(void);
	bool loadDB(MapStringToSetCfg &SetInfo,std::string strCon);
};


#endif//__TBDFHCFG_H__
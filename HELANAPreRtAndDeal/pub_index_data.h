#ifndef __PUB_INDEX_DATA_H__
#define __PUB_INDEX_DATA_H__

#include "TypeDef.h"
#include "RDbOperationComplex.h"
#define   INDEX_CFG     "pub_index_data"

class pub_index_data:public RDbOperationComplex
{
private: 

	bool loadValue(MapStringToIndexConfInfo& m_mapIndexConfInfo,MapStringToPointData& mMapPointData);

public:
	pub_index_data(void);
	pub_index_data(RsdbAdapter * QtOpt);
	~pub_index_data(void);

	bool loadDB(MapStringToIndexConfInfo& m_mapIndexConfInfo,MapStringToPointData& mMapPointData,std::string strCon);
};


#endif//__PUB_INDEX_DATA_H__

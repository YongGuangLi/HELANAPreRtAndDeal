#ifndef PUBPOINTVALUE_H
#define PUBPOINTVALUE_H
#include <QCoreApplication>
#include <string>
#include "RDbOperationComplex.h"
#include "RsdbAdapter.h"
#include "RDbHead.h"
#include "TypeDef.h"


#define PUBPOINTVALUE "PubPointValue"
#define RETCODE_RESTART 773


class PubPointValue : public RDbOperationComplex
{
public:
    PubPointValue(RsdbAdapter * QtOpt,std::string strCon);

    bool checkModelModifyStatus();

    bool loadDB(long &lTimeStamp, const long nowTime, MapStringToSetCfg &mMapSetInfo, MapStringToString &pPointSourceName,  MapStringToPointData &mPointData, std::string strCon = "TS");

    void SetModelPointValues(MapStringToSetCfg	&mMapSetInfo, MapStringToPointData &mMapPointData);

};

#endif // PUBPOINTVALUE_H

#ifndef PUBPOINTVALUE_H
#define PUBPOINTVALUE_H
#include <QCoreApplication>
#include <string>
#include <unistd.h>
#include "RDbOperationComplex.h"
#include "RsdbAdapter.h"
#include "RDbHead.h"
#include "TypeDef.h"


#define PUBPOINTVALUE "PubPointValue"
#define RETCODE_RESTART 773

typedef struct
{
    std::string full_point_code;
    double point_value;
    QDateTime timestamp;
}stCurPointValue;

class PubPointValue : public RDbOperationComplex
{
public:
    PubPointValue(RsdbAdapter * QtOpt,std::string strCon);

    bool checkModelModifyStatus();

    bool loadDB(long &lTimeStamp, MapStringToString &pPointSourceName,  MapStringToPointData &mPointData, std::string strCon = "TS");

    void SetModelPointValues(MapStringToSetCfg	&mMapSetInfo, MapStringToPointData &mMapPointData);

    QList<stCurPointValue> listCurPointValue;
};

#endif // PUBPOINTVALUE_H

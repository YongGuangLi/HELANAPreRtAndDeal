#include <iostream>
#include <string.h>
#include "data_def.h"
#include "data_mgr.h"

using namespace std;
 
int main(int argc, char *argv[])
{
	//申请多个包的资源
	PointDatas pPointData;
	DataMgr dm;
	string path = "/home/linda/DTXY/data_parser/test/";
	dm.rt_Initial(DCPoint, Text, path);
	dm.rt_Open();
	dm.CreatePointData(&pPointData, 10001);
	dm.rt_Receive(&pPointData);
	dm.rt_Close();

	dm.DeletePointData(&pPointData);
	return 0;
}


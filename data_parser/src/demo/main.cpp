#include <iostream>
#include <string.h>
#include "data_def.h"
#include "data_mgr.h"
#include "error_def.h"

using namespace std;
 
int main(int argc, char *argv[])
{
	string path = "/home/linda/DTXY/data_parser/test2/";
	DataMgr *send_data = new DataMgr();
	send_data->rt_Initial(DiscAlarm, Text, path);
	send_data->rt_Open();

	PointDatas pPointData;
	send_data->CreatePointData(&pPointData, 10001);
	send_data->rt_Send(pPointData);

	DataMgr *re_data = new DataMgr();
	re_data->rt_Initial(DiscAlarm, Text, path);
	re_data->rt_Open();

	PointDatas pReData;
	re_data->CreatePointData(&pReData, 10001);

	bool rslt = re_data->rt_Receive(&pReData);
	if (!rslt) 
	{
		if (re_data->GetError() == ID_DIR_NULL) return 1;
		return -1;
	}

	send_data->DeletePointData(&pPointData);
	re_data->DeletePointData(&pReData);
	return 0;
}


#include <iostream>
#include <string.h>
#include "data_def.h"
#include "data_mgr.h"
#include "test_data_parser.h"
#include "public_function_library.h"

using namespace std;
 
int main(int argc, char *argv[])
{
	/*
	//申请多个包的资源
	PointDatas pPointData;
	DataMgr dm;
	string path = "/home/linda/DTXY/data_parser/test/";
	dm.rt_Initial(DCPoint, Text, path);
	dm.rt_Open();
	dm.CreatePointData(&pPointData, 10001);
	dm.rt_Receive(&pPointData);
	dm.rt_Close();

std::cout << "DDDDDDDDDDD" << std::endl;

	DataMgr dm1;
	path = "/home/linda/DTXY/data_parser/test2/";
	dm1.rt_Initial(DCPoint, Text, path);
	dm1.rt_Open();
	dm1.rt_Send(pPointData);
	dm1.rt_Close();

	dm.DeletePointData(&pPointData);
	dm1.DeletePointData(&pPointData);
	*/

	TestDataParser test;
	test.config();
	while(1)
	{
		test.run();
		PubOpt::SystemOpt::SleepWait(1000);
	}
	return 0;
}


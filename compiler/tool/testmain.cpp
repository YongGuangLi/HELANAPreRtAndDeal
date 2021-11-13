#include "compiler.h"

#include <time.h>
#include <string>
#include <stdio.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    Init();
    SetStdWasp(97);
    char* tag = NULL;
    char* err = NULL;
    //string exvar(",M12_lcgrqyl,M12_lcgrqwd");  
    //string invar(",a");  
    //string incode("{{a=FDAHPT(M12_lcgrqyl*10,M12_lcgrqwd);return a;}}");  
    //string sa1("M12_lcgrqyl=15.538,M12_lcgrqwd=542.037"); 
    
	string exvar(",D1_Gdwatt");  
    string invar(",a");  
    string incode("{a=0;if(D1_Gdwatt > 10.0) a=1;return a;}");  
    string sa1("D1_Gdwatt=15.538"); 
	
    if (!PROGRAM(const_cast<char*>(exvar.c_str()), const_cast<char*>(invar.c_str()), 
        const_cast<char*>(incode.c_str()), &tag, &err))
    {
        std::cout <<"PROGRAM:"<<err<<std::endl;
        return -1;
    }
    std::cout <<"申请计算成功"<<std::endl;
	 
    double bret;
    time_t t1 = clock();
    if (!CALCULATE(tag, const_cast<char*>(sa1.c_str()), &bret, &err))
    {
        std::cout <<err<<std::endl;
        Destory();
        return -1;
    }
    time_t t2 = clock();
    std::cout <<"计算成功"<<std::endl;
    printf("计算结果: %.8f, 耗时: %lu毫秒\n", bret, t2-t1);
    RealseRec(tag, err);
    Destory();
    return 0;
}

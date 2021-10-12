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
    string exvar("a,b");
    std::cout <<"�ⲿ����������:"<<std::flush;
    getline(cin, exvar);
    string sa1("a=100,b=200");
    std::cout <<"�ⲿ����������:"<<std::flush;
    getline(cin, sa1); 
    string invar;
    std::cout <<"���ر���������:"<<std::flush;
    getline(cin ,invar);
    string incode(" return FDWHPT(1,2);");
    std::cout <<"������:"<<std::flush;
    getline(cin, incode);

    incode = "{"+incode;
    incode += "}";
    
    if (!PROGRAM(const_cast<char*>(exvar.c_str()), const_cast<char*>(invar.c_str()), 
        const_cast<char*>(incode.c_str()), &tag, &err))
    {
        std::cout <<err<<std::endl;
        return -1;
    }
    std::cout <<"�������ɹ�"<<std::endl;
    double bret;
    time_t t1 = clock();
    if (!CALCULATE(tag, const_cast<char*>(sa1.c_str()), &bret, &err))
    {
        std::cout <<err<<std::endl;
        Destory();
        return -1;
    }
    time_t t2 = clock();
    std::cout <<"����ɹ�"<<std::endl;
    printf("������: %.8f, ��ʱ: %lu����\n", bret, t2-t1);
    RealseRec(tag, err);
    Destory();
    return 0;
}

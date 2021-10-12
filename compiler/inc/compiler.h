#ifndef __COMPILER_H__
#define __COMPILER_H__

#ifdef WIN32
#ifndef IMPORT_TYPE
#define IMPORT_TYPE extern "C" __declspec(dllexport)
#endif//IMPORT_TYPE
#else
#ifndef IMPORT_TYPE
#define IMPORT_TYPE extern "C"
#endif//IMPORT_TYPE
#endif

IMPORT_TYPE void SetStdWasp(int StdID);
IMPORT_TYPE int GetStdWasp();

IMPORT_TYPE bool Init(void);
IMPORT_TYPE bool Destory(void);
IMPORT_TYPE bool PROGRAM(char* ex, char* in, char* code, char** tag , char** err);
IMPORT_TYPE bool CALCULATE(char* tag, char* ex, double* ret,char** err);
IMPORT_TYPE bool RealseRec(char* &tag, char* &err);

#endif//__COMPILER_H__

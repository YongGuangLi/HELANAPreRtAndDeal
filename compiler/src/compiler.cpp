#include "symbol.h"
#include "record.h"
#include "except.h"
#include "waspcn.h"
#include "compiler.h"

#include <stdio.h>
#include <string.h>

typedef map<string,PRecord>     MPRecord;
typedef MPRecord::iterator      MPRecordInt;

MPRecord  m_data;

IMPORT_TYPE void SetStdWasp(int StdID)
{
    waspcn::SETSTD_WASP(StdID);
}
IMPORT_TYPE int GetStdWasp()
{
    int nID=0;
    waspcn::GETSTD_WASP(nID);
    return nID;
}
IMPORT_TYPE bool PROGRAM(char* ex, char* in, char* code, char** tag , char** err)
{
    if (*tag != NULL)
    {
        delete[] *tag;
        *tag=NULL;
    }
    if (*err != NULL)
    {
        delete[] *err;
        *err=NULL;
    }

    PRecord  record=new CRecord();
    static unsigned long ulBit = 0;
    char szTmp[1024];
    sprintf(szTmp, "%lu", ulBit++);
    std::string strKey = static_cast<std::string>("Program") + szTmp;
    while (m_data.find(strKey) != m_data.end())
    {
        sprintf(szTmp, "%lu", ulBit++);
        strKey = static_cast<std::string>("Program") + szTmp;
    }
    m_data.insert(MPRecord::value_type(strKey, record));
    try
    {
        record->DeclareVariant(ex,false);
        record->DeclareVariant(in);
        record->DeclareCode(code);
    }
    catch(CExcept& e)
    {
        *err = new char[1024];
        strcpy(*err, e.get_err().c_str());
        delete record;
        m_data.erase(strKey);
        return false;
    }
    *tag = new char[strKey.size()+1];
    memset(*tag, 0, strKey.size()+1);
    strcpy(*tag, strKey.c_str());
    return true;
}


IMPORT_TYPE bool CALCULATE(char* tag, char* ex, double* ret,char** err)
{
    *ret = 0;
    if (*err != NULL)
    {   
        delete[] *err;
        *err=NULL;
    }

    MPRecordInt	Int=m_data.find(tag);
    if(Int==m_data.end())
    {
        strcpy(*err, "invalid tag ");
        return false;
    }

    PRecord  record=(*Int).second;
    try
    {
        record->DefineVariant(ex);
        record->Calculate(*ret);
    }
    catch(CExcept& e)
    {
        strcpy(*err, e.get_err().c_str());
        delete record;
        m_data.erase(tag);
        return false;
    }
    catch(...)
    {
        strcpy(*err, "非法异常！");
        delete record;
        m_data.erase(tag);
        return false;
    }
    return true;
}
//查找tag是否存在m_data中，如果存在，就删除。
IMPORT_TYPE bool RealseRec(char* &tag, char* &err)
{
    MPRecordInt Int=m_data.find(tag);
    if(Int!=m_data.end())
    {
        delete (*Int).second;
        m_data.erase(tag);
    }
    if (NULL != tag)
    {
        delete []tag;
        tag = NULL;
    }
    if (NULL != err)
    {
        delete []err;
        err = NULL;
    }
    return true;
}

IMPORT_TYPE bool Init(void)
{
    CType::InitEnv();//初始化类型表
    CSymbol::InitEnv();//初始化符号表
    return true;
}

IMPORT_TYPE bool Destory(void)
{
    CType::FreeEnv();
    CSymbol::FreeEnv();

    MPRecordInt bInt=m_data.begin();
    MPRecordInt eInt=m_data.end();

    while(bInt!=eInt)
    {
        delete (*bInt).second;
        bInt++;
    }

    m_data.clear();
    return true;
}

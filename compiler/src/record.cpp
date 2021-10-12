#include "record.h"
#include "except.h"

#include <stdlib.h>

CRecord::CRecord(void)
{
    InitEnv();
}

CRecord::~CRecord(void)
{
}

//��������
void CRecord::DeclareVariant(string var,bool in)
{
    char  split=',';
    basic_string <char>::size_type first, last;
    static const basic_string <char>::size_type npos = -1;
    string  substr;
    first=last=0;
    while((last=var.find_first_of(split,first))!=npos)
    {
        substr=var.substr(first,last-first);
        m_symbol.AddSymbolByEx(substr,in);
        first=++last;
    }

    if(first!=var.length())
    {
        substr=var.substr(first,var.length()-first);
        m_symbol.AddSymbolByEx(substr,in);
    }
}

//��������
void CRecord::DeclareCode(string code)
{
    m_lex.InitEnv(code);
    m_lex.GetTok();
    m_stmt.Statement();

}

//��������
void CRecord::DefineVariant(string var)
{
    char  split0='=',split1=',';

    basic_string <char>::size_type first, last;
    static const basic_string <char>::size_type npos = -1;

    PSymbolMeta psymbol=NULL;

    string  subvar,subval;

    first=last=0;

    while((last=var.find_first_of(split0,first))!=npos)
    {
        subvar=var.substr(first,last-first);
        first=++last;
        psymbol=m_symbol.LookupByEx(subvar);//�ҳ�m_symbol�ж�Ӧsubvar��ָ��

        if(psymbol==NULL)
        {
            throw CExcept(" undeclare variant");
        }

        while((last=var.find_first_of(split1,first))!=npos)
        {
            subval=var.substr(first,last-first);
            psymbol->m_value =atof(subval.c_str());//����ֵ
            first=++last;
            break;
        }

        if(first!=last)
        {
            subval=var.substr(first,var.length()-first);
            psymbol->m_value =atof(subval.c_str());
            break;
        }
    }
}

//����
void CRecord::Calculate(double& result)
{
    //COleDateTime d0=COleDateTime::GetCurrentTime();

    //for(int i=0;i<10000;i++)
    m_code.Calculate(result);

    //COleDateTime d1=COleDateTime::GetCurrentTime();

    //double len=(d1.m_dt -d0.m_dt)*24*60*60;
}

#ifndef __RECORD_H__
#define __RECORD_H__

#include "lex.h"
#include "exp.h"
#include "tree.h"
#include "code.h"
#include "symbol.h"
#include "state_ment.h"

typedef class CRecord* PRecord;

class CRecord
{
public:
    CRecord(void);
    virtual ~CRecord(void);
private:
    CType       m_type;
    CSymbol     m_symbol;
    CLex        m_lex;
    CTree       m_tree;
    CNode       m_node;
    CExp        m_exp;
    CStatement  m_stmt;
    CCode       m_code;
private:
    void InitEnv(void)
    {
        m_lex.m_syms=&m_symbol;
        m_tree.IniEnv(&m_symbol,&m_type);
        m_exp.InitEnv(&m_symbol,&m_type,&m_lex,&m_tree);
        m_code.InitEnv(&m_symbol,&m_node);
        m_stmt.InitEnv(&m_symbol,&m_lex,&m_exp,&m_tree,&m_code);
    }
public:
    //声明变量
    void DeclareVariant(string var,bool in=true);
    //声明代码
    void DeclareCode(string code);
    //变量定义
    void DefineVariant(string var);
    //计算
    void Calculate(double& result);
};

#endif//__RECORD_H__

#ifndef __STATE_MENT_H__
#define __STATE_MENT_H__

#include "lex.h"
#include "exp.h"
#include "tree.h"
#include "code.h"
#include "symbol.h"

class CStatement
{
public:
    CStatement(void);
    virtual ~CStatement(void);
private:
    PSymbol  m_syms;
    PLex	 m_lex;
    PExp     m_exp;
    PTree    m_tree;
    PCode    m_code;
public:
    void  InitEnv(PSymbol sym, PLex lex, PExp exp, PTree tree ,PCode code)
    {
        m_syms=sym;
        m_lex=lex;
        m_exp=exp;
        m_tree=tree;
        m_code=code;
    }
public:
    //语句描述分析
    void Statement(int loop=0);
private:
    //条件语句分析
    void IfStmt(int lab, int loop=0);
    //组合语句分析
    void Compound(int loop=0);
};
#endif//__STATE_MENT_H__

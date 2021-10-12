#ifndef __EXP_H__
#define __EXP_H__

#include "tree.h"
#include "lex.h"

typedef class CExp* PExp;

class CExp
{
public:
    CExp(void);
    ~CExp(void);
private:
    PSymbol m_sym;
    PType   m_type;
    PLex    m_lex;
    PTree   m_tree;
public:
    void  InitEnv(PSymbol sym, PType type, PLex lex, PTree tree)
    {
        m_sym=sym;
        m_type=type;
        m_lex=lex;
        m_tree=tree;
    }
public:
    PTreeMeta  Expression(int tok);
    //条件表达式分析
    PTreeMeta CondExpr(void);
    //二元表达式分析
    PTreeMeta BinaryExpr(int k);
    //一元表达式分析
    PTreeMeta UnaryExpr(void);
    //后缀表达式分析
    PTreeMeta PostfixExpr(PTreeMeta  p);
    //基元表达式
    PTreeMeta PrimaryExpr(void);
    //条件表达式分析
    PTreeMeta Conditional(int tok);
    //函数参数分析
    PTreeMeta CallExp(PTreeMeta f, PTypeMeta fty);
};

#endif//__EXP_H__

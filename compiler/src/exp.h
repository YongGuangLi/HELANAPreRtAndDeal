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
    //�������ʽ����
    PTreeMeta CondExpr(void);
    //��Ԫ���ʽ����
    PTreeMeta BinaryExpr(int k);
    //һԪ���ʽ����
    PTreeMeta UnaryExpr(void);
    //��׺���ʽ����
    PTreeMeta PostfixExpr(PTreeMeta  p);
    //��Ԫ���ʽ
    PTreeMeta PrimaryExpr(void);
    //�������ʽ����
    PTreeMeta Conditional(int tok);
    //������������
    PTreeMeta CallExp(PTreeMeta f, PTypeMeta fty);
};

#endif//__EXP_H__

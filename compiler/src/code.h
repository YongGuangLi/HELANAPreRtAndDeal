#ifndef __CODE_H__
#define __CODE_H__

#include "tree.h"
#include "symbol.h"
#include "code_meta.h"

#include <functional>

#define Label  0
#define Start  1
#define Gen    2
#define CJump  3

typedef class CCode*  PCode;

class CCode
{

public:
    CCode(void);
    virtual ~CCode(void);
private:
    LPCodeMeta  m_code;
    LPNodeMeta  m_forest;
private:
    PSymbol    m_syms;
    PNode      m_node;
public:
    void InitEnv(PSymbol sym, PNode node)
    {
        m_syms=sym;
        m_node=node;
    }
public:
    //创建新的代码
    void NewCode(int kind);
    //将标号定义添加到代码表中
    void DefineLab(int lab);
    //分支函数
    void Branch(int lab);
    //产生跳转功能
    PNodeMeta Jump(int lab);
    //转换tree为dag,并产生代码
    void Walk(PTreeMeta tp, int tlab=0, int flab=0);
    //tree转为dag
    PNodeMeta ListNodes(PTreeMeta tp, int tlab=0, int flab=0);
    //计算
    void  Calculate(double& result);
};

class IsSameLabel
{
public:
    IsSameLabel( double value)
        : m_value(value)
    {
    }
    bool operator() (PCodeMeta x)
    {
        if(x->m_kind==Label&&x->m_forest .front()->m_sym->m_value==m_value)
            return true;
        else
            return false;
    }
private:
    double  m_value;
};

#endif//__CODE_H__

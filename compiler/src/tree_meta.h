#ifndef __TREE_META_H__
#define __TREE_META_H__

#include "symbol_meta.h"

typedef class CTreeMeta* PTreeMeta;
typedef class CNodeMeta* PNodeMeta;
typedef PNodeMeta*       PPNodeMeta;

typedef list<PTreeMeta>         LPTreeMeta;
typedef LPTreeMeta::iterator    LPTreeMetaInt;
typedef list<PNodeMeta>         LPNodeMeta;
typedef LPNodeMeta::iterator    LPNodeMetaInt;

class CTreeMeta
{
public:
    CTreeMeta(void);
    CTreeMeta(int  op, 
        PTypeMeta type, PTreeMeta left=NULL, PTreeMeta right=NULL,
        PSymbolMeta  sym=NULL, PNodeMeta node=NULL, double value=0);
    virtual ~CTreeMeta(void);
public:
    //操作符号代码
    int		m_op;
    //类型
    PTypeMeta  m_type;
    //子树
    PTreeMeta  m_kids[2];
    //值
    double  m_value;
    //符号
    PSymbolMeta  m_sym;
    //代码
    PNodeMeta  m_node;
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class CNodeMeta
{
public:
    CNodeMeta(void);
    CNodeMeta(int op,
        PNodeMeta l=NULL,PNodeMeta r=NULL,PSymbolMeta sym=NULL,double value=0);
    virtual ~CNodeMeta(void);
public:
    //操作符号
    int		m_op;
    //子节点
    PNodeMeta  m_kids[2];
    //值
    double	m_value;
    //符号表
    PSymbolMeta  m_sym;
};

#endif//__TREE_META_H__

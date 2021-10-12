#include "tree_meta.h"

CTreeMeta::CTreeMeta(void)
{
    m_op=0;
    m_type=NULL;
    m_kids[0]=NULL;
    m_kids[1]=NULL;
    m_sym=NULL;
    m_node=NULL;
    m_value=0;
}

CTreeMeta::CTreeMeta(int  op, PTypeMeta  type, PTreeMeta left, PTreeMeta right,PSymbolMeta  sym ,PNodeMeta node ,double value)
{
    m_op=op;
    m_type=type;
    m_kids[0]=left;
    m_kids[1]=right;
    m_sym=sym;
    m_node=node;
    m_value=value;
}

CTreeMeta::~CTreeMeta(void)
{
}


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


CNodeMeta::CNodeMeta(void)
{
    m_op=0;
    m_kids[0]=NULL;
    m_kids[1]=NULL;
    m_sym=NULL;
    m_value=0;
}

CNodeMeta::CNodeMeta(int op,PNodeMeta l,PNodeMeta r,PSymbolMeta sym, double value)
{
    m_op=op;
    m_kids[0]=l;
    m_kids[1]=r;
    m_sym=sym;
    m_value=value;
}

CNodeMeta::~CNodeMeta(void)
{
}


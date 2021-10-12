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
    //�������Ŵ���
    int		m_op;
    //����
    PTypeMeta  m_type;
    //����
    PTreeMeta  m_kids[2];
    //ֵ
    double  m_value;
    //����
    PSymbolMeta  m_sym;
    //����
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
    //��������
    int		m_op;
    //�ӽڵ�
    PNodeMeta  m_kids[2];
    //ֵ
    double	m_value;
    //���ű�
    PSymbolMeta  m_sym;
};

#endif//__TREE_META_H__

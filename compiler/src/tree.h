#ifndef __TREE_H__
#define __TREE_H__

#include "symbol.h"
#include "tree_meta.h"

typedef class CTree*  PTree;
typedef class CNode*  PNode;

class CTree
{
public:
    CTree(void);
    virtual ~CTree(void);
private:
    //����
    LPTreeMeta m_tree;
    //������
    PSymbol  m_syms;
    PType    m_types;
public:
    //������
    PTreeMeta NewTree(int op, PTypeMeta type, PTreeMeta left, PTreeMeta right);
    //������
    PTreeMeta IDTree(PSymbolMeta p);
    //���ɳ�����
    PTreeMeta ConstTree(unsigned n, PTypeMeta ty);
    //����������
    PTreeMeta CondTree(PTreeMeta e, PTreeMeta l, PTreeMeta r);
    //��ֵ��
    PTreeMeta AsgnTree(int op, PTreeMeta l, PTreeMeta r);
    //����call����t3Ϊ��������ֵ����
    PTreeMeta CallTree(PTreeMeta f, PTypeMeta ty, PTreeMeta args, PSymbolMeta t3);
    //��e����ֵ������p
    PTreeMeta Asgn(PSymbolMeta p, PTreeMeta e) ;
    //����һ�����Ա�ʾĳ��ֵ��������0���Ƚϣ�תΪһ��������
    PTreeMeta Cond(PTreeMeta p);
    //������һ��Ƕ�׵�right�������ұߵķ�right������
    PTreeMeta RightKid(PTreeMeta p);
    //������ͺ������ڱ��ʽʱ��ҪתΪָ��
    PTreeMeta Pointer(PTreeMeta p);
    //����p�����򷵻�ty���͵�p�ĸ���
    PTreeMeta ReType(PTreeMeta p, PTypeMeta ty);
    //����ϵ���ʽתΪһ��ֵ
    PTreeMeta ValueTree(PTreeMeta p);
    //��ȡ��������p->op����Ϊindir,type����Ϊvoid 
    PTreeMeta lValue(PTreeMeta p);
    //����indir������ȡp��ַ������
    PTreeMeta rValue(PTreeMeta p);
    //�������������Ϊcall��mul�任������1
    bool HasCall(PTreeMeta p);
public:
    void  IniEnv(PSymbol syms,PType  types)
    {
        m_syms=syms;
        m_types=types;
    }
};


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

class CNode
{
private:
    LPNodeMeta   m_node;
public:
    CNode(void)
    {
    }
    virtual ~CNode(void)
    {
        LPNodeMetaInt bInt=m_node.begin();
        LPNodeMetaInt eInt=m_node.end();
        while(bInt!=eInt)
        {
            delete *bInt;
            bInt++;
        }
        m_node.clear();
    }
public:
    //����dag�Ľڵ�
    PNodeMeta  NewNode(int op, PNodeMeta l, PNodeMeta r, PSymbolMeta sym)
    {
        PNodeMeta node=new CNodeMeta(op,l,r,sym);
        m_node.push_back(node);
        return node;
    }
};

#endif//__TREE_H__


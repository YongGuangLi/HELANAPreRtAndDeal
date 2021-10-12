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
    //向量
    LPTreeMeta m_tree;
    //符号类
    PSymbol  m_syms;
    PType    m_types;
public:
    //创建树
    PTreeMeta NewTree(int op, PTypeMeta type, PTreeMeta left, PTreeMeta right);
    //符号树
    PTreeMeta IDTree(PSymbolMeta p);
    //生成常量树
    PTreeMeta ConstTree(unsigned n, PTypeMeta ty);
    //生成条件树
    PTreeMeta CondTree(PTreeMeta e, PTreeMeta l, PTreeMeta r);
    //赋值树
    PTreeMeta AsgnTree(int op, PTreeMeta l, PTreeMeta r);
    //建立call树，t3为函数返回值变量
    PTreeMeta CallTree(PTreeMeta f, PTypeMeta ty, PTreeMeta args, PSymbolMeta t3);
    //将e树赋值给变量p
    PTreeMeta Asgn(PSymbolMeta p, PTreeMeta e) ;
    //返回一个可以表示某个值的树，和0作比较，转为一个条件树
    PTreeMeta Cond(PTreeMeta p);
    //返回在一组嵌套的right树中最右边的非right操作树
    PTreeMeta RightKid(PTreeMeta p);
    //当数组和函数用于表达式时需要转为指针
    PTreeMeta Pointer(PTreeMeta p);
    //返回p，否则返回ty类型的p的副本
    PTreeMeta ReType(PTreeMeta p, PTypeMeta ty);
    //将关系表达式转为一个值
    PTreeMeta ValueTree(PTreeMeta p);
    //获取左子树，p->op必须为indir,type不能为void 
    PTreeMeta lValue(PTreeMeta p);
    //构建indir树，获取p地址的内容
    PTreeMeta rValue(PTreeMeta p);
    //如果树操作符号为call或mul变换，返回1
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
    //生成dag的节点
    PNodeMeta  NewNode(int op, PNodeMeta l, PNodeMeta r, PSymbolMeta sym)
    {
        PNodeMeta node=new CNodeMeta(op,l,r,sym);
        m_node.push_back(node);
        return node;
    }
};

#endif//__TREE_H__


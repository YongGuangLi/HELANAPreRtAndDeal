#include "tree.h"
#include "define.h"
#include "except.h"

CTree::CTree(void)
: m_syms(NULL)
, m_types(NULL)
{
}

CTree::~CTree(void)
{
    LPTreeMetaInt bInt=m_tree.begin();
    LPTreeMetaInt eInt=m_tree.end();

    while(bInt!=eInt)
    {
        delete *bInt;
        bInt++;
    }

    m_tree.clear();
}

//������
PTreeMeta CTree::NewTree(int op, PTypeMeta type, PTreeMeta left, PTreeMeta right) 
{
    PTreeMeta  tree=new CTreeMeta(op,type,left,right,NULL);
    m_tree.push_back(tree);
    return tree;
}

//���ɳ�����
PTreeMeta CTree::ConstTree(unsigned n, PTypeMeta ty) 
{
    PTreeMeta p=NewTree(CNST,ty,NULL,NULL);
    p->m_value=n;
    return p;
}

//����������
PTreeMeta CTree::CondTree(PTreeMeta e, PTreeMeta l, PTreeMeta r) 
{
    PSymbolMeta  t1;
    PTypeMeta    ty=e->m_type, xty = l->m_type;//, yty = r->m_type;
    PTreeMeta    p;

    if (e->m_op==CNST)
        return ReType(e->m_value!=0.0 ? l : r,xty);

    if (e->m_type != CType::_voidtype ) 
    {
        t1 = m_syms->Genident(ty);
        l = Asgn(t1, l);
        r = Asgn(t1, r);
    } 
    else
        t1 = NULL;

    p = NewTree(COND, ty, Cond(e),NewTree(RIGHT, ty, l, r));
    p->m_sym=t1;

    return p;
}

//��ֵ��
PTreeMeta CTree:: AsgnTree(int op, PTreeMeta l, PTreeMeta r) 
{
    l = lValue(l);
    r = Pointer(r);
    return NewTree(op, l->m_type, l, r);
}

//������
PTreeMeta CTree::IDTree(PSymbolMeta p) 
{
    PTreeMeta e;
    PTypeMeta ty = p->m_type;


    if (ty->m_op==FUNCTION_SYM)
        e = NewTree(ADDRG, p->m_type, NULL, NULL);
    else
        e = NewTree(ADDRG, m_types->Ptr(p->m_type), NULL, NULL);

    e->m_sym=p;

    if (e->m_type->m_op==POINTER_SYM)
        e = rValue(e);

    return e;
}

//����call����t3Ϊ��������ֵ����
PTreeMeta CTree:: CallTree(PTreeMeta f, PTypeMeta ty, PTreeMeta args, PSymbolMeta t3) 
{
    //������Ϊ�գ�����right������������Ϊ��������ֵ����
    if (args)
        f = NewTree(RIGHT, f->m_type, args, f);

    return NewTree(CALL, ty, f, NULL);
}

//��e����ֵ������p
PTreeMeta CTree::Asgn(PSymbolMeta p, PTreeMeta e) 
{
    return AsgnTree(ASGN, IDTree(p), e);
}


//����һ�����Ա�ʾĳ��ֵ��������0���Ƚϣ�תΪһ��������
PTreeMeta CTree::Cond(PTreeMeta p) 
{
    //��ȡ�������ղ�������
    int op = RightKid(p)->m_op;

    if (op == AND || op == OR || op == NOT ||  op == EQ  || op == NE 
        ||  op == LE  || op == LT || op == GE || op == GT)
        return p;

    p = Pointer(p);

    return NewTree(NE, CType::_doubletype, p, ConstTree(0, CType::_doubletype));
}


//������һ��Ƕ�׵�right�������ұߵķ�right������
PTreeMeta CTree::RightKid(PTreeMeta p) 
{
    while (p && p->m_op == RIGHT)
    {
        if (p->m_kids[1])
            p = p->m_kids[1];
        else if (p->m_kids[0])
            p = p->m_kids[0];
        else
            throw CExcept(" right tree is invalid");
    }

    if(p==NULL)
        throw CExcept(" right tree is invalid");

    return p;

}

//����ϵ���ʽתΪһ��ֵ
PTreeMeta CTree::ValueTree(PTreeMeta p)
{
    //��ȡ�������ղ�������
    int op = RightKid(p)->m_op;

    if (p->m_type != CType::_voidtype && (op==AND || op==OR || op==NOT || op==EQ || op==NE
        ||  op== LE || op==LT || op== GE || op==GT))
        p = CondTree(p, ConstTree(1, CType::_doubletype),ConstTree(0, CType::_doubletype));

    return p;
}

//������ͺ������ڱ��ʽʱ��ҪתΪָ��
PTreeMeta CTree::Pointer(PTreeMeta p)
{
    if (p->m_type->m_op==FUNCTION_SYM)
        p = ReType(p, m_types->Ptr(p->m_type));

    return p;
}

//��ȡ��������p->op����Ϊindir,type����Ϊvoid 
PTreeMeta CTree::lValue(PTreeMeta p) 
{
    if(p->m_op!= INDIR)
        throw CExcept(" invalid lvalue");

    return p->m_kids[0];
}

//����indir������ȡp��ַ������
PTreeMeta CTree::rValue(PTreeMeta p) 
{
    return NewTree(INDIR, m_types->Deref(p->m_type), p, NULL);
}


//����p�����򷵻�ty���͵�p�ĸ���
PTreeMeta CTree::ReType(PTreeMeta p, PTypeMeta ty)
{
    if (p->m_type == ty)
        return p;

    PTreeMeta q = NewTree(p->m_op, ty, p->m_kids[0], p->m_kids[1]);
    q->m_sym=p->m_sym;
    q->m_value=p->m_value;

    return q;
}

//�������������Ϊcall��mul�任������1
bool CTree::HasCall(PTreeMeta p)
{
    if (p == 0)
        return false;
    if (p->m_op == CALL)
        return true;

    return HasCall(p->m_kids[0]) || HasCall(p->m_kids[1]);
}


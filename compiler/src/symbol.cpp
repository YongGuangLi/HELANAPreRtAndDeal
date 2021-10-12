#include "symbol.h"
#include "define.h"

#include <sstream>
#include <algorithm>


string funcname[]=
{
#define ff(a,b,c,d) d,
#define df(a,b,c,d) d,
#define sf(a,b,c,d) d,
#define vf(a,b,c,d) d,
#include "func.h"
};


////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////


//ȫ�־�̬���ͱ�
LPTypeMeta CType::_vstype;
//int����
PTypeMeta CType::_inttype=NULL;
//double����
PTypeMeta CType::_doubletype=NULL;
//void����
PTypeMeta CType::_voidtype=NULL;
//_voidptype����
PTypeMeta CType::_voidptype=NULL;


CType::CType(void)
{
}

CType::~CType(void)
{
    LPTypeMetaInt bInt=m_vtype.begin();
    LPTypeMetaInt eInt=m_vtype.end();

    while(bInt!=eInt)
    {
        delete *bInt;
        bInt++;
    }

    m_vtype.clear();
}

//��������
PTypeMeta CType::NewType(LPTypeMeta& vt, int op, PTypeMeta ty, PSymbolMeta sym) 
{
    PTypeMeta  meta=new CTypeMeta(op,ty,sym);
    LPTypeMetaInt Int=find_if(vt.begin(),vt.end(),IsSameTypeMeta(meta));

    if(Int==vt.end())
    {
        vt.push_back(meta);
        return meta;
    }
    else
    {
        delete meta;

        return *Int;
    }
}

//����ָ�뻯
PTypeMeta CType::Ptr(PTypeMeta ty)
{
    return CType::NewType( m_vtype, POINTER_SYM, ty, CSymbol::_pointersym );
}

//����ȥָ�뻯
PTypeMeta CType::Deref(PTypeMeta ty) 
{
    if (ty && ty->m_op==POINTER_SYM)
        return ty->m_type;
    else
        return NULL;
}

//�������Ͷ���
PTypeMeta CType::FuncType(PTypeMeta ty, VPTypeMeta& proto) 
{
    if (ty && ty->m_op!=FUNCTION_SYM)
    {
        ty = NewType(m_vtype ,FUNCTION_SYM, ty, NULL);
        ty->m_proto=proto;
        return ty;
    }

    return NULL;
}

//���غ�����ֵ����
PTypeMeta CType::FuncValueType(PTypeMeta ty) 
{
    if (ty && ty->m_op==FUNCTION_SYM)
        return ty->m_type;
    else
        return NULL;
}


//��ʼ������
void CType::InitEnv() 
{
    PSymbolMeta p;

    //int
    p  = CSymbol::NewSymbol("int", CSymbol::_types);
    _inttype = NewType(_vstype ,INT_SYM, 0, p);
    p->m_type=_inttype;

    //double
    p = CSymbol::NewSymbol("double", CSymbol::_types);
    _doubletype = NewType(_vstype ,DOUBLE_SYM, 0, p);
    p->m_type=_doubletype;

    //void
    p  = CSymbol::NewSymbol("void", CSymbol::_types);
    _voidtype = NewType(_vstype ,VOID_SYM, 0, p);
    p->m_type=_voidtype;

    //_voidptype
    _voidptype = NewType(_vstype,POINTER_SYM, _voidtype, CSymbol::_pointersym);
}


void CType::FreeEnv()
{
    LPTypeMetaInt bInt=_vstype.begin();
    LPTypeMetaInt eInt=_vstype.end();

    while(bInt!=eInt)
    {
        delete *bInt;
        bInt++;
    }

    _vstype.clear();
}


////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

//ȫ�ֺ������ű�
MPSymbolMeta   CSymbol::_functions;
//ȫ�����ͷ��ű�
MPSymbolMeta   CSymbol::_types;
//ָ�����
PSymbolMeta    CSymbol::_pointersym=NewSymbol("T*", CSymbol::_types);

CSymbol::CSymbol(void)
: m_inclab(1)
{
    m_retsym=Genident(CType::_doubletype);
}

CSymbol::~CSymbol(void)
{
    MPSymbolMetaInt bInt=m_Globals.begin();
    MPSymbolMetaInt eInt=m_Globals.end();
    PSymbolMeta  p;

    while(bInt!=eInt)
    {
        p=(*bInt).second;
        delete p;
        bInt++;
    }

    m_Globals.clear();

    bInt=m_Locals.begin();
    eInt=m_Locals.end();

    while(bInt!=eInt)
    {
        p=(*bInt).second;
        delete p;
        bInt++;
    }

    m_Locals.clear();

    bInt=m_Labels.begin();
    eInt=m_Labels.end();

    while(bInt!=eInt)
    {
        p=(*bInt).second;
        delete p;
        bInt++;
    }

    m_Labels.clear();

    bInt=m_Constants.begin();
    eInt=m_Constants.end();

    while(bInt!=eInt)
    {
        p=(*bInt).second;
        delete p;
        bInt++;
    }

    m_Constants.clear();
}


// ������̬��ʶ����
PSymbolMeta CSymbol::NewSymbol(const string& name, MPSymbolMeta& ms)
{
    MPSymbolMetaInt  Int=ms.find(name);

    if(Int==ms.end())
    {
        PSymbolMeta p=new CSymbolMeta(name);
        ms.insert(MPSymbolMeta::value_type(name,p));
        Int=ms.find(name);
    }

    return (*Int).second;
}

//���ұ��
PSymbolMeta CSymbol::LabelSym(long lab)
{
    ostringstream buff;
    buff<<lab;

    PSymbolMeta p=NewSymbol(buff.str(),m_Constants);
    p->m_value=lab;

    return p;
}

//���ɳ�������
PSymbolMeta CSymbol::ConstantSym(PTypeMeta ty, double v) 
{
    ostringstream buff;
    buff<<v;

    PSymbolMeta p=NewSymbol(buff.str(),m_Constants);
    p->m_type=ty;
    p->m_value=v;

    return p;
}

//������ʱ����
PSymbolMeta CSymbol::Genident(PTypeMeta type) 
{
    ostringstream buff;
    buff<<GenLabel(1);

    PSymbolMeta p=NewSymbol(buff.str(),m_Locals);
    p->m_type=type;

    return p;
}


// ���ұ�ʶ����
PSymbolMeta CSymbol::Lookup( string& name)
{
    PSymbolMeta  sym;

    sym=LookupByScale(name,m_Locals);
    if(sym!=NULL) return sym;

    sym=LookupByScale(name,m_Globals);
    if(sym!=NULL) return sym;

    sym=LookupByScale(name,_functions);
    if(sym!=NULL) return sym;

    return NULL;
}

// ���ݷ�Χ���ҷ���
PSymbolMeta CSymbol::LookupByScale(const string& name, MPSymbolMeta& ms)
{
    MPSymbolMetaInt Int=ms.find(name);

    if(Int!=ms.end())
        return (*Int).second;
    else
        return NULL;
}


//���ɱ������
long CSymbol::GenLabel(long n) 
{
    m_inclab += n;
    return m_inclab - n;
}

//�ⲿ���ӱ���
void CSymbol::AddSymbolByEx(const string& name,bool in)
{
    PSymbolMeta p;

    if(in)
        p=NewSymbol(name,m_Locals);
    else
        p=NewSymbol(name,m_Globals);

    p->m_type=CType::_doubletype;
    p->m_value=0;
}

//�ⲿ���ұ���
PSymbolMeta CSymbol::LookupByEx(const string& name)
{
    return LookupByScale(name,m_Globals);
}


//��ʼ������
void CSymbol::InitEnv() 
{
    string		name;
    PSymbolMeta	sym=NULL;
    PTypeMeta   ty=NULL;
    VPTypeMeta  proto;
    int			i=0;

    while((name=funcname[i])!="EOI")
    {
        if(name=="")
        {
            i++;
            continue;
        }

        sym=NewSymbol(name,_functions);
        ty=CType::NewType(CType::_vstype , FUNCTION_SYM, CType::_doubletype, sym);
        sym->m_type=ty;
        sym->m_index=i;

        proto.clear();

        if(i >=DFUNC && i< SFUNC)
        {//˫����
            proto.push_back(CType::_doubletype);
            proto.push_back(CType::_doubletype);
        }
        else if(i>=SFUNC && i<VFUNC)
        {//������
            proto.push_back(CType::_doubletype);
        }
        else
        {//�ɱ����
            proto.push_back(CType::_doubletype);
            proto.push_back(CType::_voidtype);
        }

        ty->m_proto=proto;
        i++;
    }
}

//�ͷŻ���
void   CSymbol::FreeEnv()
{
    MPSymbolMetaInt bInt=_functions.begin();
    MPSymbolMetaInt eInt=_functions.end();

    while(bInt!=eInt)
    {
        delete (*bInt).second;
        bInt++;
    }

    _functions.clear();

    bInt=_types.begin();
    eInt=_types.end();

    while(bInt!=eInt)
    {
        delete (*bInt).second;
        bInt++;
    }

    _types.clear();
}


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


//全局静态类型表
LPTypeMeta CType::_vstype;
//int类型
PTypeMeta CType::_inttype=NULL;
//double类型
PTypeMeta CType::_doubletype=NULL;
//void类型
PTypeMeta CType::_voidtype=NULL;
//_voidptype类型
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

//创建类型
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

//类型指针化
PTypeMeta CType::Ptr(PTypeMeta ty)
{
    return CType::NewType( m_vtype, POINTER_SYM, ty, CSymbol::_pointersym );
}

//类型去指针化
PTypeMeta CType::Deref(PTypeMeta ty) 
{
    if (ty && ty->m_op==POINTER_SYM)
        return ty->m_type;
    else
        return NULL;
}

//函数类型定义
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

//返回函数的值类型
PTypeMeta CType::FuncValueType(PTypeMeta ty) 
{
    if (ty && ty->m_op==FUNCTION_SYM)
        return ty->m_type;
    else
        return NULL;
}


//初始化环境
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

//全局函数符号表
MPSymbolMeta   CSymbol::_functions;
//全局类型符号表
MPSymbolMeta   CSymbol::_types;
//指针符号
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


// 创建静态标识符号
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

//查找标号
PSymbolMeta CSymbol::LabelSym(long lab)
{
    ostringstream buff;
    buff<<lab;

    PSymbolMeta p=NewSymbol(buff.str(),m_Constants);
    p->m_value=lab;

    return p;
}

//生成常量符号
PSymbolMeta CSymbol::ConstantSym(PTypeMeta ty, double v) 
{
    ostringstream buff;
    buff<<v;

    PSymbolMeta p=NewSymbol(buff.str(),m_Constants);
    p->m_type=ty;
    p->m_value=v;

    return p;
}

//产生临时变量
PSymbolMeta CSymbol::Genident(PTypeMeta type) 
{
    ostringstream buff;
    buff<<GenLabel(1);

    PSymbolMeta p=NewSymbol(buff.str(),m_Locals);
    p->m_type=type;

    return p;
}


// 查找标识符号
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

// 根据范围查找符号
PSymbolMeta CSymbol::LookupByScale(const string& name, MPSymbolMeta& ms)
{
    MPSymbolMetaInt Int=ms.find(name);

    if(Int!=ms.end())
        return (*Int).second;
    else
        return NULL;
}


//生成标号数字
long CSymbol::GenLabel(long n) 
{
    m_inclab += n;
    return m_inclab - n;
}

//外部增加变量
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

//外部查找变量
PSymbolMeta CSymbol::LookupByEx(const string& name)
{
    return LookupByScale(name,m_Globals);
}


//初始化环境
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
        {//双参数
            proto.push_back(CType::_doubletype);
            proto.push_back(CType::_doubletype);
        }
        else if(i>=SFUNC && i<VFUNC)
        {//单参数
            proto.push_back(CType::_doubletype);
        }
        else
        {//可变参数
            proto.push_back(CType::_doubletype);
            proto.push_back(CType::_voidtype);
        }

        ty->m_proto=proto;
        i++;
    }
}

//释放环境
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


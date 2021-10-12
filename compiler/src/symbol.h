#ifndef __SYMBOL_H__
#define __SYMBOL_H__

#include "symbol_meta.h"

#include <string>
using namespace std;

typedef class CType*        PType;
typedef class CSymbol*      PSymbol;

class CType
{
public:
    CType(void);
    virtual ~CType(void);
private:
    //动态类型表
    LPTypeMeta  m_vtype;
public:
    //类型指针化
    PTypeMeta Ptr(PTypeMeta ty);
    //类型去指针化
    PTypeMeta  Deref(PTypeMeta ty);
    //函数类型定义
    PTypeMeta FuncType(PTypeMeta ty, VPTypeMeta& proto);
    //返回函数的值类型
    PTypeMeta FuncValueType(PTypeMeta ty) ;
public:
    //全局静态类型表
    static LPTypeMeta _vstype;
    //int类型
    static PTypeMeta _inttype;
    //double类型
    static PTypeMeta _doubletype;
    //void类型
    static PTypeMeta _voidtype;
    //void*类型
    static PTypeMeta _voidptype;
public:
    //初始化环境
    static void	  InitEnv();
    //释放环境
    static void   FreeEnv();
    //创建类型
    static PTypeMeta NewType(LPTypeMeta& vt, int op, PTypeMeta ty=NULL, PSymbolMeta sym=NULL);
};


////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

class CSymbol
{
public:
    CSymbol(void);
    virtual ~CSymbol(void);
private:
    MPSymbolMeta  m_Globals;
    MPSymbolMeta  m_Locals;
    MPSymbolMeta  m_Labels;
    MPSymbolMeta  m_Constants;
    long  m_inclab;
public:
    //全局函数符号表
    static MPSymbolMeta   _functions;
    //全局类型符号表
    static MPSymbolMeta   _types;
    //指针符号
    static PSymbolMeta   _pointersym;
    //返回指针
    PSymbolMeta  m_retsym;
public:
    // 查找符号
    PSymbolMeta Lookup( string& name);
    // 生成标号
    PSymbolMeta LabelSym(long lab);
    // 生成常量符号
    PSymbolMeta ConstantSym(PTypeMeta ty, double v);
    // 产生临时变量
    PSymbolMeta Genident(PTypeMeta type);
    // 生成标号数字
    long GenLabel(long n);
    //外部增加变量
    void AddSymbolByEx(const string& name,bool in=true);
    //外部查找变量
    PSymbolMeta LookupByEx(const string& name);
public:
    // 在指定表中,创建一个新的符号
    static PSymbolMeta NewSymbol(const string& name, MPSymbolMeta& ms);
    // 根据范围查找符号
    static PSymbolMeta LookupByScale(const string& name, MPSymbolMeta& ms);
    //初始化环境
    static void  InitEnv();
    //释放环境
    static void   FreeEnv();
};

#endif//__SYMBOL_H__

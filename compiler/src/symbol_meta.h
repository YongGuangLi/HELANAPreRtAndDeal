#ifndef __SYMBOL_META_H__
#define __SYMBOL_META_H__

#include <map>
#include <list>
#include <string>
#include <vector>
using namespace std;

typedef class CTypeMeta*            PTypeMeta;
typedef list<PTypeMeta>             LPTypeMeta;
typedef LPTypeMeta::iterator        LPTypeMetaInt;
typedef vector<PTypeMeta>           VPTypeMeta;
typedef VPTypeMeta::iterator        VPTypeMetaInt;
typedef class CSymbolMeta*          PSymbolMeta;
typedef map<string,PSymbolMeta>     MPSymbolMeta;
typedef MPSymbolMeta::iterator      MPSymbolMetaInt;
typedef vector<PSymbolMeta>         VPSymbolMeta;
typedef VPSymbolMeta::iterator      VPSymbolMetaInt;

class CTypeMeta
{
public:
    CTypeMeta(void);
    CTypeMeta( int &op,PTypeMeta type,PSymbolMeta sym);
    virtual ~CTypeMeta(void);
public:
    // 操作代码
    int m_op;
    // 操作类型
    PTypeMeta m_type;
    //符号类型
    PSymbolMeta m_symbol;
    // 函数原型类型链表
    VPTypeMeta m_proto;
};

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

class IsSameTypeMeta
{
public:
    IsSameTypeMeta(PTypeMeta value)
        :m_value(value)
    {
    }
    bool operator() (PTypeMeta x)  
    {
        if(x->m_op==m_value->m_op&&x->m_type==m_value->m_type
            &&x->m_symbol== m_value->m_symbol)
            return true;
        else
            return false;
    }
private:
    PTypeMeta  m_value;
};


////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////


class CSymbolMeta
{
public:
    //缺省构造函数
    CSymbolMeta(void);
    //参数构造函数
    CSymbolMeta( const string &name);
    virtual ~CSymbolMeta(void);
public:
    // 名称
    string m_name;
    // 类型
    PTypeMeta  m_type;
    // 函数参数符号链表
    VPSymbolMeta m_callee;
    // 值
    double m_value;
    //函数索引
    int m_index;
};

#endif//__SYMBOL_META_H__

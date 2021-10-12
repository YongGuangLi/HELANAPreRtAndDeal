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
    // ��������
    int m_op;
    // ��������
    PTypeMeta m_type;
    //��������
    PSymbolMeta m_symbol;
    // ����ԭ����������
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
    //ȱʡ���캯��
    CSymbolMeta(void);
    //�������캯��
    CSymbolMeta( const string &name);
    virtual ~CSymbolMeta(void);
public:
    // ����
    string m_name;
    // ����
    PTypeMeta  m_type;
    // ����������������
    VPSymbolMeta m_callee;
    // ֵ
    double m_value;
    //��������
    int m_index;
};

#endif//__SYMBOL_META_H__

#include "symbol_meta.h"

//ȱʡ���캯��
CTypeMeta::CTypeMeta(void)
: m_op(0)
, m_type(NULL)
, m_symbol(NULL)
{
}

//�������캯��
CTypeMeta::CTypeMeta( int &op,PTypeMeta type,PSymbolMeta sym)
: m_op(op)
, m_type(type)
, m_symbol(sym)
{
}

CTypeMeta::~CTypeMeta(void)
{
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

//ȱʡ���캯��
CSymbolMeta::CSymbolMeta(void)
: m_name("")
, m_type(NULL)
, m_value(0)
, m_index(0)
{
}

//�������캯��
CSymbolMeta::CSymbolMeta(const string &name)
: m_name(name)
, m_type(NULL)
, m_value(0)
{
}


CSymbolMeta::~CSymbolMeta(void)
{
}

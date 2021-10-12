#include "code_meta.h"

CCodeMeta::CCodeMeta(void)
: m_kind(0)
{

}

CCodeMeta::CCodeMeta(int kind , LPNodeMeta forest)
: m_kind(kind)
, m_forest(forest)
{

}

CCodeMeta::~CCodeMeta(void)
{

}

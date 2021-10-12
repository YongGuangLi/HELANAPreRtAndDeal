#ifndef __CODE_META_H__
#define __CODE_META_H__

#include "tree_meta.h"

typedef class CCodeMeta*        PCodeMeta;
typedef list<PCodeMeta>         LPCodeMeta;
typedef LPCodeMeta::iterator    LPCodeMetaInt;
typedef LPCodeMetaInt*          PLPCodeMetaInt;

class CCodeMeta
{
public:
    CCodeMeta(void);
    CCodeMeta(int kind, LPNodeMeta forest);
    virtual ~CCodeMeta(void);
public:
    int m_kind;
    LPNodeMeta  m_forest;
};

#endif//__CODE_META_H__

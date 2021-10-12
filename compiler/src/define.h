#ifndef __DEFINE_H__
#define __DEFINE_H__

#define CHAR_MAXLEN  256

enum
{
    CONSTANTS=0,
    LABELS,
    FUNC,
    GLOBAL, 
    LOCAL
};

enum
{
#define xx(a,b,c,d,e,f,g) a=b,
#define yy(a,b,c,d,e,f,g)
#include "token.h"
};

enum
{
#define xx(a,b,c) a=b,
#define yy(a,b,c) a=b,
#include "opfunc.h"
};

enum
{
    DFUNC=0,
    SFUNC=19,
    VFUNC=36
};

#endif//__DEFINE_H__

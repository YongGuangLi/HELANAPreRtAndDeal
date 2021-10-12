#ifndef __EXCEPT_H__
#define __EXCEPT_H__

#include <string>
using namespace std;

class CExcept
{
public:
    CExcept(void)
    {
    }
    CExcept(string err)
    {
        m_err=err;
    }
    virtual ~CExcept(void)
    {
    }
private:
    string  m_err;
public:
    string get_err(void) 
    {
        return m_err;
    }
};

#endif//__EXCEPT_H__

#ifndef __LEX_H__
#define __LEX_H__

#include "symbol.h"

typedef class CLex* PLex;

class CLex
{
public:
    CLex(void);
    virtual ~CLex(void);
public:
    string  m_text;
    //当前符号指针
    unsigned char* m_cp;
    //符号类
    PSymbol   m_syms;
    //符号代码
    int		m_code;
    //符号名称
    string	m_token;
    //当前符号
    PSymbolMeta m_tsym;
    //常量符号
    CSymbolMeta  m_tval;
    //前项指针
    unsigned char *m_precp;
public:
    void InitEnv(string text)
    {
        m_text=text;
        m_cp=(unsigned char*)m_text.c_str();
    }
    //获取下一个单词
    void GetTok(void);
    //获取下一个字符
    void GetChar(void);
    //期望函数
    void ExpectChar(int tok);
};

#endif//__LEX_H__

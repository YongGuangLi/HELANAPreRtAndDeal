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
    //��ǰ����ָ��
    unsigned char* m_cp;
    //������
    PSymbol   m_syms;
    //���Ŵ���
    int		m_code;
    //��������
    string	m_token;
    //��ǰ����
    PSymbolMeta m_tsym;
    //��������
    CSymbolMeta  m_tval;
    //ǰ��ָ��
    unsigned char *m_precp;
public:
    void InitEnv(string text)
    {
        m_text=text;
        m_cp=(unsigned char*)m_text.c_str();
    }
    //��ȡ��һ������
    void GetTok(void);
    //��ȡ��һ���ַ�
    void GetChar(void);
    //��������
    void ExpectChar(int tok);
};

#endif//__LEX_H__

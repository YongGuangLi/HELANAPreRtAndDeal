#include "except.h"
#include "define.h"
#include "state_ment.h"

static char kind[]=
{
#define xx(a,b,c,d,e,f,g) f,
#define yy(a,b,c,d,e,f,g) f,
#include "token.h"
};


CStatement::CStatement(void)
{
}

CStatement::~CStatement(void)
{
}

//语句描述分析
void CStatement::Statement(int loop) 
{
    int t=m_lex->m_code;
    switch (t) 
    {
    case IF_SYM:       
        IfStmt(m_syms->GenLabel(2));
        break;
    case RETURN_SYM:
        m_lex->GetTok();
        if (m_lex->m_code != ';')
            m_code->Walk(m_tree->Asgn(m_syms->m_retsym, m_exp->Expression(0)));
        m_lex->ExpectChar(';' );
        break;
    case '{':      
        Compound(loop); 
        break;
    case ';':
        m_lex->GetTok();
        break;
    default: 
        t=m_lex->m_code;
        if (kind[t] != ID_SYM) 
            throw CExcept(" except id ");
        else
            m_code->ListNodes(m_exp->Expression(0));

        m_lex->ExpectChar(';' );

        break;

    }

    t=m_lex->m_code;
    if (kind[t] != IF_SYM && kind[t] != ID_SYM && t != '}' && t != EOI_SYM) 
        throw CExcept(" invalid expression ");
}

//if '(' expression ')' statement
//if '(' expression ')' statement else statement
void CStatement::IfStmt(int lab, int loop)
{
    m_lex->GetTok();
    m_lex->ExpectChar('(');

    m_code->Walk(m_exp->Conditional(')'), 0, lab);
    Statement(loop);

    if (m_lex->m_code == ELSE_SYM) 
    {
        m_code->Branch(lab + 1);
        m_lex->GetTok();
        m_code->DefineLab(lab);
        Statement(loop);
        m_code->DefineLab(lab + 1);
    } 
    else
        m_code->DefineLab(lab);
}

//statement:
//if '(' expression ')' statement
//if '(' expression ')' statement else statement
//return [expression];
//compond-statement
//compond-statement: '{' {declaration} {statement} '}'

void CStatement::Compound(int loop) 
{
    m_code->Walk(NULL);
    m_lex->ExpectChar('{');
    int t=m_lex->m_code;
    while (kind[t] == IF_SYM || kind[t] == ID_SYM)
    {
        Statement(loop);
        t=m_lex->m_code;
    }
    m_code->Walk(NULL);
    m_lex->ExpectChar('}');
}

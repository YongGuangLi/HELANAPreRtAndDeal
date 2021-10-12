#include "exp.h"
#include "define.h"
#include "except.h"

static char prec[] = 
{
#define xx(a,b,c,d,e,f,g) c,
#define yy(a,b,c,d,e,f,g) c,
#include "token.h"
};

static int oper[] = 
{
#define xx(a,b,c,d,e,f,g) d,
#define yy(a,b,c,d,e,f,g) d,
#include "token.h"
};

CExp::CExp(void)
{
}

CExp::~CExp(void)
{
}

//expression-expression:
//conditional-expression
//unary-expression { assing-operator conditional-expression }
PTreeMeta CExp::Expression(int tok)
{
    PTreeMeta p = CondExpr();

    if (m_lex->m_code == '=')
    {
        m_lex->GetTok();
        p = m_tree->AsgnTree(ASGN, p, m_tree->ValueTree(Expression(0)));
    }

    if (tok)
    {
        m_lex->ExpectChar(tok);
    }

    return p;
}

//conditional-expression: binary-expression [? expression: conditional-expression]
PTreeMeta CExp::CondExpr(void) 
{
    PTreeMeta p = BinaryExpr(4);

    if (m_lex->m_code == '?')
    {
        PTreeMeta l, r;

        p = m_tree->Pointer(p);
        m_lex->GetTok();
        l = m_tree->Pointer(Expression(':'));
        r = m_tree->Pointer(CondExpr());
        p = m_tree->CondTree(p, l, r);
    }

    return p;
}

//binary-expression:unary-expression { binary-operator unary-expression }
//binary-operator: || && == != <= >= < > + - * /
PTreeMeta CExp::BinaryExpr(int k) 
{
    PTreeMeta p = UnaryExpr();
    PTreeMeta r;
    int  op;

    for (int k1 = prec[m_lex->m_code]; k1 >= k; k1--)
    {
        while (prec[m_lex->m_code] == k1) 
        {
            op = m_lex->m_code;
            m_lex->GetTok();
            p = m_tree->Pointer(p);
            if (op == ANDAND_SYM || op == OROR_SYM)
                r = m_tree->Pointer(BinaryExpr(k1));
            else
                r = m_tree->Pointer(BinaryExpr(k1 + 1));

            if (op == ANDAND_SYM || op == OROR_SYM)
                p = m_tree->NewTree(oper[op], CType::_doubletype, m_tree->Cond(p), m_tree->Cond(r));
            else
                p = m_tree->NewTree(oper[op], CType::_doubletype, p, r);
        }
    }
    return p;
}

//unary-expression:
//postfix-expression
//unary-operator unaray-expression
//'(' typename ')' unaray-expression
//unary-operator:- !
PTreeMeta CExp::UnaryExpr(void) 
{
    PTreeMeta p;

    switch (m_lex->m_code) 
    {
    case '-':
        m_lex->GetTok();
        p = UnaryExpr();
        p = m_tree->Pointer(p);
        p = m_tree->NewTree(SUB, p->m_type, m_tree->ConstTree(0,CType::_doubletype), p);
        break;
    case '!':    
        m_lex->GetTok();
        p = UnaryExpr();
        p = m_tree->Pointer(p);
        p = m_tree->NewTree(NOT, CType::_doubletype, m_tree->Cond(p), NULL);
        break;
    case '(':
        m_lex->GetTok();
        p = PostfixExpr(Expression(')'));
        break;
    default:
        p = PostfixExpr(PrimaryExpr());
    }

    return p;
}

//postfix-expression:primary-expression {postfix-operator}
//postfix-operator:'(' [assignment-expression {, assignment-expression} ] ')'
PTreeMeta CExp::PostfixExpr(PTreeMeta p) 
{
    for (;;)
    {
        switch (m_lex->m_code) 
        {
        case '(':

            PTypeMeta  ty;
            p = m_tree->Pointer(p);

            if(p->m_type->m_op== POINTER_SYM && p->m_type->m_type->m_op==FUNCTION_SYM)
                ty=p->m_type->m_type;
            else
                throw CExcept(" expect '(' ");

            m_lex->GetTok();
            p = CallExp(p, ty);
            break;
        default:
            return p;
        }
    }
}

//primary-expression:identifier|constant|'(' expression ')'
PTreeMeta CExp::PrimaryExpr(void) 
{
    PTreeMeta	p;
    PSymbolMeta sym=m_lex->m_tsym;

    switch (m_lex->m_code) 
    {
    case FCON_SYM: 
        p = m_tree->NewTree(CNST, sym->m_type, NULL, NULL);
        p->m_value=sym->m_value;
        break;
    case ID_SYM:
        if (sym == NULL)
            throw CExcept(" invalid variant");

        if(sym->m_type->m_op==FUNCTION_SYM)
        {
            sym=m_sym->Genident(sym->m_type);
            sym->m_index=m_lex->m_tsym->m_index;
        }

        p=m_tree->IDTree(sym);
        break;
    default:
        throw CExcept(" undeclare variant ");
        break;
    }

    m_lex->GetTok();

    return p;
}

//条件表达式分析
PTreeMeta CExp:: Conditional(int tok) 
{
    return m_tree->Cond(Expression(tok));
}


//函数参数分析
PTreeMeta CExp::CallExp(PTreeMeta f, PTypeMeta fty) 
{
    VPSymbolMeta callee;
    PSymbolMeta	 temp=NULL;

    PTreeMeta	args = NULL,r = NULL,e = NULL;
    PTypeMeta	rty = m_type->FuncValueType(fty);

    VPTypeMeta		proto = fty->m_proto;
    VPTypeMetaInt	Int = proto.begin();

    //判断树中是否含有call操作符号或mul符号，决定是否使用right树
    if (m_tree->HasCall(f))
        r = f;

    //分析函数
    if (m_lex->m_code != ')')
    {
        for (;;) 
        {
            PTreeMeta q = m_tree->Pointer(Expression(0));

            if(Int!=proto.end() && (*Int)!=CType::_voidtype )
            {
                q=m_tree->ValueTree(q);
                Int++;
            }
            else
            {
                if(Int==proto.end())
                    throw CExcept(" too param ");

                q=m_tree->ValueTree(q);
            }

            //产生临时变量
            temp=m_sym->Genident(CType::_doubletype);
            callee.push_back(temp);

            //如果是call树则建立right树
            if (m_tree->HasCall(q))
                r = r ? m_tree->NewTree(RIGHT, CType::_voidtype, r, q) : q;
            //建立arg树
            args = m_tree->NewTree(ARG, CType::_doubletype, q, args);
            args->m_sym=temp;

            //参数声明结束
            if (m_lex->m_code != ',')
                break;

            m_lex->GetTok();
        }
    }

    //获取期望的')'
    m_lex->ExpectChar(')');

    if(Int!=proto.end() && (*Int)!=CType::_voidtype)
        throw CExcept(" less param ");

    //将临时变量加入函数符号的CALLEE中
    f->m_sym->m_callee=callee;

    if (r)
        args = m_tree->NewTree(RIGHT, CType::_voidtype, r, args);
    //建立call树
    e = m_tree->CallTree(f, rty, args, NULL);
    return e;
}

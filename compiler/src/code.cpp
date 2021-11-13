#include "code.h"
#include "define.h"
#include "except.h"

#include <algorithm>

typedef vector<double>  VDOUBLE;
typedef double (*EXTFUNCTION)(VDOUBLE& t);
extern  EXTFUNCTION extfun[];

static plus<double> _plus;
static minus<double> _minus;
static multiplies<double> _multiplies;
static divides<double> _divides;
static equal_to<double> _equal_to;
static greater_equal<double> _greater_equal;
static greater<double>  _greater;
static less<double>  _less;
static less_equal<double>  _less_equal;
static not_equal_to<double> _not_equal_to;

static void ASGNCal(PPNodeMeta  p);
static void ARGCal (PPNodeMeta  p);
static void CALLCal(PPNodeMeta  p);
static void EQCal  (PPNodeMeta  p);
static void GECal  (PPNodeMeta  p);
static void GTCal  (PPNodeMeta  p);
static void LECal  (PPNodeMeta  p);
static void LTCal  (PPNodeMeta  p);
static void NECal  (PPNodeMeta  p);

static void ADDCal  (PPNodeMeta  p);
static void SUBCal  (PPNodeMeta  p);
static void MULCal  (PPNodeMeta  p);
static void DIVCal  (PPNodeMeta  p);
static void CNSTCal (PPNodeMeta  p);
static void INDIRCal(PPNodeMeta  p);
static void ADDRGCal(PPNodeMeta  p);

typedef void (*OPFUNCTION)(PPNodeMeta  p);

static OPFUNCTION opfunc[]=
{
#define xx(a,b,c) c,
#define yy(a,b,c) 
#include "opfunc.h"
};


CCode::CCode(void)
{
}

CCode::~CCode(void)
{
    LPCodeMetaInt bInt=m_code.begin();
    LPCodeMetaInt eInt=m_code.end();
    while(bInt!=eInt)
    {
        delete *bInt;
        bInt++;
    }
}

//创建新的代码
void CCode::NewCode(int kind) 
{
    PCodeMeta code=new CCodeMeta(kind,m_forest);
    m_code.push_back(code);
    m_forest.clear();
}

//转换tree为dag
void CCode::Walk(PTreeMeta tp, int tlab, int flab) 
{
    ListNodes(tp, tlab, flab);
    NewCode(Gen);
}

//tree转为dag
PNodeMeta CCode::ListNodes(PTreeMeta tp, int tlab, int flab)
{
    PNodeMeta  p=NULL, l=NULL, r=NULL;

    if (tp == NULL)
        return NULL;
    if (tp->m_node)
        return tp->m_node;
    int op=tp->m_op;
    switch (op) 
    {
    case AND:
        if (flab) 
        {// tlab=0 flab=L--> if e1==0 goto L;if e2==0 goto L
            ListNodes(tp->m_kids[0], 0, flab);
            ListNodes(tp->m_kids[1], 0, flab);
        } 
        else 
        {//tlab=L flab=0--> if e1==0 goto L';if e2!=0 goto L
            ListNodes(tp->m_kids[0], 0, flab = m_syms->GenLabel(1));
            ListNodes(tp->m_kids[1], tlab, 0);
            DefineLab(flab);
        }
        break;
    case OR:
        if (tlab) 
        {
            ListNodes(tp->m_kids[0], tlab, 0);
            ListNodes(tp->m_kids[1], tlab, 0);
        } 
        else 
        {
            tlab = m_syms->GenLabel(1);
            ListNodes(tp->m_kids[0], tlab, 0);
            ListNodes(tp->m_kids[1], 0, flab);
            DefineLab(tlab);
        }
        break;
    case NOT:
        return ListNodes(tp->m_kids[0], flab, tlab);
    case CNST:
        if (tlab || flab) 
        {
            if (tlab && tp->m_value != 0)
                m_forest.push_back(Jump(tlab));
            else if (flab && tp->m_value== 0)
                m_forest.push_back(Jump(flab));
        }
        else
        {
            p = m_node->NewNode(op, NULL, NULL, m_syms->ConstantSym(tp->m_type, tp->m_value));
        }
        break;
    case RIGHT:
        if (tp->m_kids[1]) 
        {
            ListNodes(tp->m_kids[0], 0, 0);
            p = ListNodes(tp->m_kids[1], tlab, flab);
        } 
        else
        {
            p = ListNodes(tp->m_kids[0], tlab, flab); 
        }
        break;
    case JUMP:
        l = ListNodes(tp->m_kids[0], 0, 0);
        m_forest.push_back(m_node->NewNode(JUMP, l, NULL, NULL));
        break;
    case CALL:
        l = ListNodes(tp->m_kids[0], 0, 0);
        r = ListNodes(tp->m_kids[1], 0, 0);
        p = m_node->NewNode(op, l, r, NULL);
        m_forest.push_back(p);
        break;
    case ARG:
        ListNodes(tp->m_kids[1], 0, 0);
        l = ListNodes(tp->m_kids[0], 0, 0);
        l = m_node->NewNode(op, l, NULL,tp->m_sym);
        m_forest.push_back(l);
        break;
    case EQ:  case NE: case GT: 
    case GE:  case LE: case LT:
        l = ListNodes(tp->m_kids[0], 0, 0);
        r = ListNodes(tp->m_kids[1], 0, 0);
        if (tlab)
        {
            m_forest.push_back(m_node->NewNode(op, l, r, m_syms->LabelSym(tlab)));
        }
        else if (flab) 
        {
            switch (op) 
            {
            case EQ: op = NE; break;
            case NE: op = EQ; break;
            case GT: op = LE; break;
            case LT: op = GE; break;
            case GE: op = LT; break;
            case LE: op = GT; break;
            }
            m_forest.push_back(m_node->NewNode(op, l, r, m_syms->LabelSym(flab)));
        }
        break;
    case ASGN:
        l = ListNodes(tp->m_kids[0], 0, 0);
        r = ListNodes(tp->m_kids[1], 0, 0);
        m_forest.push_back(m_node->NewNode(ASGN, l, r, NULL));
        //p = ListNodes(tp->m_kids[1], 0, 0);
        break;
    case ADD: case SUB: 
    case MUL: case DIV:
        l = ListNodes(tp->m_kids[0], 0, 0);
        r = ListNodes(tp->m_kids[1], 0, 0);
        p = m_node->NewNode(op, l, r, NULL);
        break;
    case INDIR:
        l = ListNodes(tp->m_kids[0], 0, 0);
        p = m_node->NewNode(op, l, NULL, NULL);
        break;
    case ADDRG:
        p = m_node->NewNode(op, NULL, NULL, tp->m_sym);
        break;
    }
    tp->m_node=p;
    return p;
}


//将标号定义添加到代码表中
void CCode::DefineLab(int lab) 
{
    PSymbolMeta p = m_syms->LabelSym(lab);
    Walk(NULL, 0, 0);
    m_forest.push_back(m_node->NewNode(LABEL, NULL, NULL, p));
    NewCode(Label);
}

//分支函数
void CCode::Branch(int lab) 
{
    //PSymbolMeta p = m_syms->LabelSym(lab);
    Walk(NULL, 0, 0);
    m_forest.push_back(Jump(lab));
    NewCode(CJump);
}


//产生跳转功能
PNodeMeta CCode::Jump(int lab) 
{
    PSymbolMeta sym = m_syms->LabelSym(lab);
    PNodeMeta   node = m_node->NewNode(ADDRG, NULL, NULL, sym);
    return m_node->NewNode(JUMP, node , NULL, NULL);
}

//计算
void  CCode::Calculate(double& result)
{
    result=0;
    int op;
    LPCodeMetaInt	bInt=m_code.begin();
    LPCodeMetaInt	eInt=m_code.end();
    LPCodeMetaInt	q;              // LPCodeMetaInt q=NULL;        Old Code
    LPNodeMeta		forest;
    LPNodeMetaInt	bfInt;
    LPNodeMetaInt	efInt;

    while(bInt!=eInt)
    {
        forest=(*bInt)->m_forest;
        switch((*bInt)->m_kind)
        {
        case Start:
        case Label:
            bInt++;
            break;
        case CJump:
            {
                double temp=forest.front()->m_kids[0]->m_sym->m_value;
                bInt=find_if(m_code.begin(),m_code.end(),IsSameLabel(temp));
                break;
            }
        case Gen:
            q=m_code.end();     // q=NULL;      Old Code
            bfInt=forest.begin();
            efInt=forest.end();
            while(bfInt!=efInt)
            {
                op=(*bfInt)->m_op;
                (*opfunc[op])(&(*bfInt));

                if(op>=EQ&&op<=NE&&(*bfInt)->m_value)
                {
                    q=find_if(m_code.begin(),m_code.end(),IsSameLabel((*bfInt)->m_sym->m_value));
                    break;
                }
                bfInt++;
            }
            if(q!=m_code.end())     // if(q!=NULL)      Old Code
                bInt=q;
            else
                bInt++;
            break;
        }
    }
    if(m_syms->m_retsym!=NULL)
        result=m_syms->m_retsym->m_value;
}

void ADDCal(PPNodeMeta  p)
{
    (*opfunc[(*p)->m_kids[0]->m_op])(&((*p)->m_kids[0]));
    (*opfunc[(*p)->m_kids[1]->m_op])(&((*p)->m_kids[1]));
    (*p)->m_value=_plus((*p)->m_kids[0]->m_value,(*p)->m_kids[1]->m_value);
}

void SUBCal(PPNodeMeta  p)
{
    (*opfunc[(*p)->m_kids[0]->m_op])(&((*p)->m_kids[0]));
    (*opfunc[(*p)->m_kids[1]->m_op])(&((*p)->m_kids[1]));

    (*p)->m_value=_minus((*p)->m_kids[0]->m_value,(*p)->m_kids[1]->m_value);
}

void MULCal(PPNodeMeta  p)
{
    (*opfunc[(*p)->m_kids[0]->m_op])(&((*p)->m_kids[0]));
    (*opfunc[(*p)->m_kids[1]->m_op])(&((*p)->m_kids[1]));
    (*p)->m_value=_multiplies((*p)->m_kids[0]->m_value,(*p)->m_kids[1]->m_value);
}

void DIVCal(PPNodeMeta  p)
{
    (*opfunc[(*p)->m_kids[0]->m_op])(&((*p)->m_kids[0]));
    (*opfunc[(*p)->m_kids[1]->m_op])(&((*p)->m_kids[1]));
    (*p)->m_value=_divides((*p)->m_kids[0]->m_value,(*p)->m_kids[1]->m_value);
}


void CNSTCal(PPNodeMeta  p)
{
    (*p)->m_value=(*p)->m_sym->m_value;
}

void INDIRCal(PPNodeMeta  p)
{
    (*opfunc[(*p)->m_kids[0]->m_op])(&((*p)->m_kids[0]));
    (*p)->m_value=(*p)->m_kids[0]->m_value;
}

void  ADDRGCal(PPNodeMeta  p)
{
    (*p)->m_value=(*p)->m_sym->m_value;
}

void  ARGCal(PPNodeMeta  p)
{
    (*opfunc[(*p)->m_kids[0]->m_op])(&((*p)->m_kids[0]));
    (*p)->m_sym->m_value=(*p)->m_kids[0]->m_value;
}

void CALLCal(PPNodeMeta  p)
{
    PSymbolMeta     s=(*p)->m_kids[0]->m_sym;
    VPSymbolMeta    t=s->m_callee;
    VPSymbolMetaInt bInt = t.begin();
    VPSymbolMetaInt eInt = t.end();
    int				index=s->m_index;
    VDOUBLE			values;
    double errorvalue =-99999.99;

    if(index>=DFUNC && index<SFUNC)
    {
        if(index==4)  //double FDAHPS(double pa,double sa); 通过压力和熵求气体的焓 
        {
            double tmpvalue = (*bInt)->m_value ;
            if(tmpvalue==0)
            {
                (*p)->m_value = errorvalue;
                return ;
            }
        }
        values.push_back((*bInt)->m_value);
        bInt++;
        values.push_back((*bInt)->m_value);
    }
    else if(index<VFUNC)
    {
        if(index==20) //double FSTSP(double t); 通过压力求温度 ,参数＝0或>1290会导致程序占用CPU 100%资源
        {
            double tmpvalue = (*bInt)->m_value ;
            if(tmpvalue==0||tmpvalue>1290)
            {
                (*p)->m_value = errorvalue;
                return ;
            }
        }
        values.push_back((*bInt)->m_value);
    }
    else
    {
        while(bInt!=eInt)
        {
            values.push_back((*bInt)->m_value);
            bInt++;
        }
    }

    (*p)->m_value=(*extfun[index])(values);
}

void ASGNCal(PPNodeMeta  p)
{
    (*opfunc[(*p)->m_kids[0]->m_op])(&((*p)->m_kids[0]));
    (*opfunc[(*p)->m_kids[1]->m_op])(&((*p)->m_kids[1]));
    double value=(*p)->m_kids[1]->m_value;
    (*p)->m_kids[0]->m_value=value;
    (*p)->m_kids[0]->m_sym->m_value=value;
}

void EQCal(PPNodeMeta  p)
{
    (*opfunc[(*p)->m_kids[0]->m_op])(&((*p)->m_kids[0]));
    (*opfunc[(*p)->m_kids[1]->m_op])(&((*p)->m_kids[1]));
    if(_equal_to((*p)->m_kids[0]->m_value,(*p)->m_kids[1]->m_value))
        (*p)->m_value=1;
    else
        (*p)->m_value=0;
}

void GECal(PPNodeMeta  p)
{
    (*opfunc[(*p)->m_kids[0]->m_op])(&((*p)->m_kids[0]));
    (*opfunc[(*p)->m_kids[1]->m_op])(&((*p)->m_kids[1]));
    if(_greater_equal((*p)->m_kids[0]->m_value,(*p)->m_kids[1]->m_value))
        (*p)->m_value=1;
    else
        (*p)->m_value=0;
}

void GTCal(PPNodeMeta  p)
{
    (*opfunc[(*p)->m_kids[0]->m_op])(&((*p)->m_kids[0]));
    (*opfunc[(*p)->m_kids[1]->m_op])(&((*p)->m_kids[1]));
    if(_greater((*p)->m_kids[0]->m_value,(*p)->m_kids[1]->m_value))
        (*p)->m_value=1;
    else
        (*p)->m_value=0;
}

void LECal(PPNodeMeta  p)
{
    (*opfunc[(*p)->m_kids[0]->m_op])(&((*p)->m_kids[0]));
    (*opfunc[(*p)->m_kids[1]->m_op])(&((*p)->m_kids[1]));
    if(_less_equal((*p)->m_kids[0]->m_value,(*p)->m_kids[1]->m_value))
        (*p)->m_value=1;
    else
        (*p)->m_value=0;
}

void LTCal(PPNodeMeta  p)
{
    (*opfunc[(*p)->m_kids[0]->m_op])(&((*p)->m_kids[0]));
    (*opfunc[(*p)->m_kids[1]->m_op])(&((*p)->m_kids[1]));
    if(_less((*p)->m_kids[0]->m_value,(*p)->m_kids[1]->m_value))
        (*p)->m_value=1;
    else
        (*p)->m_value=0;
}

void NECal(PPNodeMeta  p)
{
    (*opfunc[(*p)->m_kids[0]->m_op])(&((*p)->m_kids[0]));
    (*opfunc[(*p)->m_kids[1]->m_op])(&((*p)->m_kids[1]));
    if(_not_equal_to((*p)->m_kids[0]->m_value,(*p)->m_kids[1]->m_value))
        (*p)->m_value=1;
    else
        (*p)->m_value=0;
}

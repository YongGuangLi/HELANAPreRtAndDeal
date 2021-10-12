#ifndef __SYMBOL_H__
#define __SYMBOL_H__

#include "symbol_meta.h"

#include <string>
using namespace std;

typedef class CType*        PType;
typedef class CSymbol*      PSymbol;

class CType
{
public:
    CType(void);
    virtual ~CType(void);
private:
    //��̬���ͱ�
    LPTypeMeta  m_vtype;
public:
    //����ָ�뻯
    PTypeMeta Ptr(PTypeMeta ty);
    //����ȥָ�뻯
    PTypeMeta  Deref(PTypeMeta ty);
    //�������Ͷ���
    PTypeMeta FuncType(PTypeMeta ty, VPTypeMeta& proto);
    //���غ�����ֵ����
    PTypeMeta FuncValueType(PTypeMeta ty) ;
public:
    //ȫ�־�̬���ͱ�
    static LPTypeMeta _vstype;
    //int����
    static PTypeMeta _inttype;
    //double����
    static PTypeMeta _doubletype;
    //void����
    static PTypeMeta _voidtype;
    //void*����
    static PTypeMeta _voidptype;
public:
    //��ʼ������
    static void	  InitEnv();
    //�ͷŻ���
    static void   FreeEnv();
    //��������
    static PTypeMeta NewType(LPTypeMeta& vt, int op, PTypeMeta ty=NULL, PSymbolMeta sym=NULL);
};


////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

class CSymbol
{
public:
    CSymbol(void);
    virtual ~CSymbol(void);
private:
    MPSymbolMeta  m_Globals;
    MPSymbolMeta  m_Locals;
    MPSymbolMeta  m_Labels;
    MPSymbolMeta  m_Constants;
    long  m_inclab;
public:
    //ȫ�ֺ������ű�
    static MPSymbolMeta   _functions;
    //ȫ�����ͷ��ű�
    static MPSymbolMeta   _types;
    //ָ�����
    static PSymbolMeta   _pointersym;
    //����ָ��
    PSymbolMeta  m_retsym;
public:
    // ���ҷ���
    PSymbolMeta Lookup( string& name);
    // ���ɱ��
    PSymbolMeta LabelSym(long lab);
    // ���ɳ�������
    PSymbolMeta ConstantSym(PTypeMeta ty, double v);
    // ������ʱ����
    PSymbolMeta Genident(PTypeMeta type);
    // ���ɱ������
    long GenLabel(long n);
    //�ⲿ���ӱ���
    void AddSymbolByEx(const string& name,bool in=true);
    //�ⲿ���ұ���
    PSymbolMeta LookupByEx(const string& name);
public:
    // ��ָ������,����һ���µķ���
    static PSymbolMeta NewSymbol(const string& name, MPSymbolMeta& ms);
    // ���ݷ�Χ���ҷ���
    static PSymbolMeta LookupByScale(const string& name, MPSymbolMeta& ms);
    //��ʼ������
    static void  InitEnv();
    //�ͷŻ���
    static void   FreeEnv();
};

#endif//__SYMBOL_H__

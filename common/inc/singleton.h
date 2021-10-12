/*******************************************************************************
* Copyright（C）,2014-2020,Tacker Tech .Co.Ltd;
* 文 件 名: singleton.h
* 文件描述: 单例模板定义类头文件
*  作  者 : 汤卫波，13739072308
* 创建日期: 2013-8-21 9:45:27
*******************************************************************************/

#ifndef __SINGlETON_H__
#define __SINGlETON_H__

#include <stdlib.h>

// 单例调用模板定义
#define SINGLETON(CBaseClass) CBaseClass::Instance()

// 单例声明实现模板（自动构造及析构）
#define DECLARE_SINGLETON(CBaseClass) \
private:\
    CBaseClass(){} \
    virtual ~CBaseClass(){} \
public:\
    static CBaseClass* Instance(void); \
    static void Destory(void); \
private:\
    volatile static CBaseClass* m_pInstance;

// 单例声明实现模板（提供用户手动实现构造及析构）
#define DECLARE_SINGLETON_INIT(CBaseClass) \
private:\
    CBaseClass();\
    virtual ~CBaseClass(); \
public:\
    static CBaseClass* Instance(void); \
    static void Destory(void); \
private:\
    volatile static CBaseClass* m_pInstance;

// 单例模板定义实现模板
#define IMPLEMENT_SINGLETON(CBaseClass) \
volatile CBaseClass *CBaseClass::m_pInstance = NULL;\
CBaseClass *CBaseClass::Instance()\
{\
    if(NULL == m_pInstance)\
    {\
        if (NULL == m_pInstance)\
        {\
            m_pInstance = new CBaseClass;\
            atexit(CBaseClass::Destory);\
        }\
    }\
    return (CBaseClass *)m_pInstance;\
}\
\
void CBaseClass::Destory()\
{\
    if(NULL != m_pInstance)\
    {\
        delete m_pInstance;\
        m_pInstance = NULL;\
    }\
}\

#endif//__SINGlETON_H__

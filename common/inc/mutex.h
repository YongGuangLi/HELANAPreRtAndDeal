/*******************************************************************************
* Copyright（C）,2014-2020,Tacker Tech .Co.Ltd;
* 文 件 名: mutex.h
* 文件描述: 系统内核互斥锁，封装类
*  作  者 : 汤卫波，13739072308
* 创建日期: 2014-8-25 9:12:50
*******************************************************************************/

#ifndef __MUTEX_H__
#define __MUTEX_H__

namespace boost
{
    class mutex;
}

class MutexLock
{
public:
    MutexLock(void);
    virtual ~MutexLock(void);
public:
    void Lock(void);            // 加锁
    void UnLock(void);          // 解锁
private:
    boost::mutex* m_pMutex;
};

class AutoLock                          // 自动加锁类
{
public:
    // 功能描述：加锁，构造函数
    AutoLock(MutexLock& oMutexLock);
    // 功能描述：解锁，析构函数
    virtual ~AutoLock(void);
private:
    MutexLock &m_oAutoLock;     // 内部锁成员
};

#endif//__MUTEX_H__

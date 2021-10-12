/*******************************************************************************
* Copyright��C��,2014-2020,Tacker Tech .Co.Ltd;
* �� �� ��: mutex.h
* �ļ�����: ϵͳ�ں˻���������װ��
*  ��  �� : ��������13739072308
* ��������: 2014-8-25 9:12:50
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
    void Lock(void);            // ����
    void UnLock(void);          // ����
private:
    boost::mutex* m_pMutex;
};

class AutoLock                          // �Զ�������
{
public:
    // �������������������캯��
    AutoLock(MutexLock& oMutexLock);
    // ������������������������
    virtual ~AutoLock(void);
private:
    MutexLock &m_oAutoLock;     // �ڲ�����Ա
};

#endif//__MUTEX_H__

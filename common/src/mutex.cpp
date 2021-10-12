#include "mutex.h"

#include <boost/thread.hpp>

MutexLock::MutexLock(void)
: m_pMutex(NULL)
{
    m_pMutex = new boost::mutex();
}

MutexLock::~MutexLock(void)
{
    if (NULL != m_pMutex)
    {
        delete m_pMutex;
        m_pMutex = NULL;
    }
}

void MutexLock::Lock(void)
{
    m_pMutex->lock();
}

void MutexLock::UnLock(void)
{
    m_pMutex->unlock();
}

AutoLock::AutoLock(MutexLock& oMutexLock)
: m_oAutoLock(oMutexLock)
{
    m_oAutoLock.Lock();
}

AutoLock::~AutoLock(void)
{
    m_oAutoLock.UnLock();
}

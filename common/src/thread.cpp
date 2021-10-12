#include "thread.h"
#include "public_function_library.h"
#include <iostream>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

Thread::Thread(void)
: m_pThread(NULL)
{
    m_bRunning = true;
    m_nTimeOut = 100;
}

Thread::~Thread(void)
{
    if (NULL != m_pThread)
    {
        delete m_pThread;
        m_pThread = NULL;
    }
}

void Thread::Start(void)
{
    if (NULL == m_pThread)
    {
        m_pThread = new boost::thread(
            boost::bind(&Thread::ThreadCallBack, 
            this)
            );
    }
}

void Thread::ThreadCallBack(void)
{

    while (m_bRunning)
    {
        this->Run();
		std::cout<<"sasasas"<<std::endl;
		//boost::this_thread::sleep(boost::posix_time::seconds(1));
        PubOpt::SystemOpt::SleepWait(m_nTimeOut);
    }
}

void Thread::Stop(void)
{
    m_bRunning = false;
    m_pThread->join();
}

void Thread::SetTimeOut(const int &nTimeOut /* = 100 */)
{
    m_nTimeOut = nTimeOut;
}

int Thread::GetTimeOut(void)
{
    return m_nTimeOut;
}

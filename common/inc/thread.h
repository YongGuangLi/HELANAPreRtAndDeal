/*******************************************************************************
* Copyright��C��,2010-2015,DTXY Tech .Co.Ltd;
* �� �� ��: thread.h
* �ļ�����: ��ƽ̨�ں˶��߳�ģ�ͣ���װ��
*  ��  �� : ��������13730895608
* ��������: 2014-9-30 9:01:27
*******************************************************************************/

#ifndef __THREAD_H__
#define __THREAD_H__

namespace boost
{
    class thread;
}

class Thread
{
public:
    Thread(void);
    virtual ~Thread(void);
public:
    /* 
    * ��������: �����߳�ģ������ʱ�䣨��λ���룩
    * �������: ϵͳ����ʱ�䣬����
    * �������: ��
    * �� �� ֵ: ��
    */
    virtual void SetTimeOut(const int &nTimeOut = 100);

    /* 
    * ��������: ��ȡ�߳�ģ������ʱ��
    * �������: ��
    * �������: ��
    * �� �� ֵ: ϵͳ����ʱ�䣬����
    */
    virtual int GetTimeOut(void);

    /* 
    * ��������: �߳�������ģ�͵��ú���
    * �������: ��
    * �������: ��
    * �� �� ֵ: ��
    */
    virtual void Start(void);

    /* 
    * ��������: �߳�ֹͣ��ģ�͵��ú���
    * �������: ��
    * �������: ��
    * �� �� ֵ: ��
    */
    virtual void Stop(void);
protected:
    // �����������߳�ģ��ִ�У��ص�����
    void ThreadCallBack(void);
    // �����������߳�����ִ�й��ܺ�������Ҫ�����Լ�ʵ��
    virtual void Run(void) = 0;
private:
    boost::thread* m_pThread;   // ���߳̾��
    int m_nTimeOut;             // ѭ������
    bool m_bRunning;            // �߳�ִ�п���
};

#endif//__THREAD_H__

/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: thread.h
* 文件描述: 跨平台内核多线程模型，封装类
*  作  者 : 汤卫波，13730895608
* 创建日期: 2014-9-30 9:01:27
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
    * 功能描述: 设置线程模型周期时间（单位毫秒）
    * 输入参数: 系统休眠时间，毫秒
    * 输出参数: 无
    * 返 回 值: 无
    */
    virtual void SetTimeOut(const int &nTimeOut = 100);

    /* 
    * 功能描述: 获取线程模型周期时间
    * 输入参数: 无
    * 输出参数: 无
    * 返 回 值: 系统休眠时间，毫秒
    */
    virtual int GetTimeOut(void);

    /* 
    * 功能描述: 线程启动，模型调用函数
    * 输入参数: 无
    * 输出参数: 无
    * 返 回 值: 无
    */
    virtual void Start(void);

    /* 
    * 功能描述: 线程停止，模型调用函数
    * 输入参数: 无
    * 输出参数: 无
    * 返 回 值: 无
    */
    virtual void Stop(void);
protected:
    // 功能描述：线程模型执行，回调函数
    void ThreadCallBack(void);
    // 功能描述：线程能力执行功能函数，需要子类自己实现
    virtual void Run(void) = 0;
private:
    boost::thread* m_pThread;   // 多线程句柄
    int m_nTimeOut;             // 循环周期
    bool m_bRunning;            // 线程执行开关
};

#endif//__THREAD_H__

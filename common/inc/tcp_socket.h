/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: tcp_socket.h
* 文件描述: Tcp网络套接字封装接口类
*  作  者 : 汤卫波，13739072308
* 创建日期: 2013-3-12 14:49:53
*******************************************************************************/

#ifndef __TCP_SOCKET_H__
#define __TCP_SOCKET_H__

#include <string>

#define MAX_TCP_RECV_SIZE        (4 * 1024)

typedef struct TcpHostInfo
{
    std::string strHostIP;      // 主机IP信息
    unsigned short usHostPort;          // 主机端口信息
    unsigned int ulMaxConnect;        // 服务器允许的最大连接数
    TcpHostInfo()
    {
        strHostIP = "127.0.0.1";
        usHostPort = 9000;
        ulMaxConnect = 1000;
    }
}*TCP_HOST_INFO;

class TcpSocket
{
public:
    TcpSocket(void);
    virtual ~TcpSocket(void);
public:
    // 功能描述: 初始化Socket环境
    unsigned long TcpInit(int &nSockfd);
    // 功能描述: 绑定本地IP及端口
    unsigned long TcpBind(const int &nSockfd, const TcpHostInfo &stHostInfo);
    // 功能描述: 服务端进行Socket连接监听
    unsigned long TcpListen(const int &nSockfd, const unsigned int &ulMaxConnect);
    // 功能描述: 服务端接收Socket连接请求
    unsigned long TcpAccept(const int &nSockfd, int &nCliSockfd, TcpHostInfo &stHostInfo);
    // 功能描述: 客户端进行连接请求
    unsigned long TcpConnect(const int &nSockfd, const TcpHostInfo &stHostInfo);
    // 功能描述: 发送消息至指定的Sockfd连接通道
    unsigned long TcpSend(const int &nSockfd, const std::string &strSend);
    // 功能描述: 接收指定Sockfd连接通道的消息
    unsigned long TcpRecv(const int &nSockfd, const int &nRecvLen, std::string &strRecv);
    // 功能描述: 关闭指定的Sockfd连接通道
    void TcpClose(const int &nSockfd);
public:
    // 功能描述: Short主机字节序转网络字节序
    unsigned short HostToNetShort(const unsigned short &usInfo);
    // 功能描述: Short网络字节序转主机字节序
    unsigned short NetToHostShort(const unsigned short &usInfo);
    // 功能描述: 将字符串类型IP转换为Uint32类型
    unsigned int StrHostIPtoUint32(const std::string &strHostIP);
    // 功能描述: 将Uint32类型IP转换为字符串类型
    std::string Uint32HostIPtoStr(const unsigned int &ulHostIP);
private:
    char* m_pszRecvBuff;           // 接收信息缓存区
};

#endif//__TCP_SOCKET_H__

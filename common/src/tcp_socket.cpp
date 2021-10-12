#include "tcp_socket.h"

#include <string.h>

#ifdef WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#else
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#endif

#ifdef WIN32
#pragma comment(lib, "ws2_32")
#endif

TcpSocket::TcpSocket(void)
: m_pszRecvBuff(NULL)
{
    m_pszRecvBuff = new char[MAX_TCP_RECV_SIZE];
}

TcpSocket::~TcpSocket(void)
{
    if (NULL != m_pszRecvBuff)
    {
        delete []m_pszRecvBuff;
        m_pszRecvBuff = NULL;
    }
}

unsigned long TcpSocket::TcpInit(int &nSockfd)
{
#ifdef WIN32
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2, 2), &wsadata);
#endif
    nSockfd = static_cast<int>(socket(AF_INET, SOCK_STREAM, 0));
    if (-1 == nSockfd)
    {
        return -1;
    }
    return 0;
}

unsigned long TcpSocket::TcpBind(const int &nSockfd, const TcpHostInfo &stHostInfo)
{
    struct sockaddr_in stAddr;
    stAddr.sin_family = AF_INET;
    stAddr.sin_port = this->HostToNetShort(stHostInfo.usHostPort);
    stAddr.sin_addr.s_addr = this->StrHostIPtoUint32(stHostInfo.strHostIP);
    int iRet = bind(nSockfd, (struct sockaddr*)&stAddr, sizeof(struct sockaddr));
    if (0 != iRet)
    {
        return -1;
    }
    return 0;
}

unsigned long TcpSocket::TcpListen(const int &nSockfd, const unsigned int &ulMaxConnect)
{
    int iRet = listen(nSockfd, ulMaxConnect);
    if (0 != iRet)
    {
        return -1;
    }
    return 0;
}

unsigned long TcpSocket::TcpAccept(const int &nSockfd, int &nCliSockfd, TcpHostInfo &stHostInfo)
{
    struct sockaddr_in stCliAddr;
    socklen_t sin_size = sizeof(struct sockaddr);
    nCliSockfd = static_cast<int>(accept(nSockfd, (struct sockaddr*)&stCliAddr, &sin_size));
    if (-1 == nCliSockfd)
    {
#ifdef WIN32
#else
        if (EAGAIN == errno)
        {
            return 0;
        }
#endif
        return -1;
    }

    stHostInfo.usHostPort = this->NetToHostShort(stCliAddr.sin_port);
    stHostInfo.strHostIP = this->Uint32HostIPtoStr(stCliAddr.sin_addr.s_addr);
    return 0;
}

unsigned long TcpSocket::TcpConnect(const int &nSockfd, const TcpHostInfo &stHostInfo)
{
    struct sockaddr_in stAddr;
    stAddr.sin_family = AF_INET;
    stAddr.sin_port = this->HostToNetShort(stHostInfo.usHostPort);
    stAddr.sin_addr.s_addr = this->StrHostIPtoUint32(stHostInfo.strHostIP);
    int iRet = connect(nSockfd, (struct sockaddr*)&stAddr, sizeof(struct sockaddr));
    if (0 != iRet)
    {
        return -1;
    }
    return 0;
}

unsigned long TcpSocket::TcpSend(const int &nSockfd, const std::string &strSend)
{
    if (strSend.empty())
    {
        return 0;
    }
    int iRet = send(nSockfd, strSend.c_str(), static_cast<int>(strSend.size()), 0);
    if (-1 == iRet)
    {
        return -1;
    }
    return 0;
}

unsigned long TcpSocket::TcpRecv(const int &nSockfd, const int &nRecvLen, std::string &strRecv)
{
    strRecv.clear();
    int nRecvDBLen = 0;
    for(int i=1; i<=nRecvLen; ++i)
    {
        int iRet = recv(nSockfd, m_pszRecvBuff + nRecvDBLen++, 1, 0);
        if (-1 == iRet)
        {
            return -1;
        }
        if (0 == iRet)
        {
            strRecv.clear();
            return 0;
        }
        if (i%MAX_TCP_RECV_SIZE == 0)
        {
            std::string strRecvDB(m_pszRecvBuff, MAX_TCP_RECV_SIZE);
            strRecv += strRecvDB;
            memset(m_pszRecvBuff, 0, MAX_TCP_RECV_SIZE);
            nRecvDBLen = 0;
        }
#ifndef WIN32
        if (errno == EAGAIN)
        {
            break;
        }
#endif
    }
    std::string strRecvDB(m_pszRecvBuff, nRecvDBLen);
    strRecv += strRecvDB;
    memset(m_pszRecvBuff, 0, MAX_TCP_RECV_SIZE);
    return 0;
}

void TcpSocket::TcpClose(const int &nSockfd)
{
#ifdef WIN32
    closesocket(nSockfd);
#else
    close(nSockfd);
#endif
}

unsigned short TcpSocket::HostToNetShort(const unsigned short &usInfo)
{
    return htons(usInfo);
}

unsigned short TcpSocket::NetToHostShort(const unsigned short &usInfo)
{
    return ntohs(usInfo);
}

unsigned int TcpSocket::StrHostIPtoUint32(const std::string &strHostIP)
{
    return inet_addr(strHostIP.c_str());
}

std::string TcpSocket::Uint32HostIPtoStr(const unsigned int &ulHostIP)
{
    struct in_addr stAddr;
    stAddr.s_addr = ulHostIP;
    std::string strHostIP = inet_ntoa(stAddr);
    return strHostIP;
}

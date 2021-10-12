/*******************************************************************************
* Copyright��C��,2010-2015,DTXY Tech .Co.Ltd;
* �� �� ��: tcp_socket.h
* �ļ�����: Tcp�����׽��ַ�װ�ӿ���
*  ��  �� : ��������13739072308
* ��������: 2013-3-12 14:49:53
*******************************************************************************/

#ifndef __TCP_SOCKET_H__
#define __TCP_SOCKET_H__

#include <string>

#define MAX_TCP_RECV_SIZE        (4 * 1024)

typedef struct TcpHostInfo
{
    std::string strHostIP;      // ����IP��Ϣ
    unsigned short usHostPort;          // �����˿���Ϣ
    unsigned int ulMaxConnect;        // ��������������������
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
    // ��������: ��ʼ��Socket����
    unsigned long TcpInit(int &nSockfd);
    // ��������: �󶨱���IP���˿�
    unsigned long TcpBind(const int &nSockfd, const TcpHostInfo &stHostInfo);
    // ��������: ����˽���Socket���Ӽ���
    unsigned long TcpListen(const int &nSockfd, const unsigned int &ulMaxConnect);
    // ��������: ����˽���Socket��������
    unsigned long TcpAccept(const int &nSockfd, int &nCliSockfd, TcpHostInfo &stHostInfo);
    // ��������: �ͻ��˽�����������
    unsigned long TcpConnect(const int &nSockfd, const TcpHostInfo &stHostInfo);
    // ��������: ������Ϣ��ָ����Sockfd����ͨ��
    unsigned long TcpSend(const int &nSockfd, const std::string &strSend);
    // ��������: ����ָ��Sockfd����ͨ������Ϣ
    unsigned long TcpRecv(const int &nSockfd, const int &nRecvLen, std::string &strRecv);
    // ��������: �ر�ָ����Sockfd����ͨ��
    void TcpClose(const int &nSockfd);
public:
    // ��������: Short�����ֽ���ת�����ֽ���
    unsigned short HostToNetShort(const unsigned short &usInfo);
    // ��������: Short�����ֽ���ת�����ֽ���
    unsigned short NetToHostShort(const unsigned short &usInfo);
    // ��������: ���ַ�������IPת��ΪUint32����
    unsigned int StrHostIPtoUint32(const std::string &strHostIP);
    // ��������: ��Uint32����IPת��Ϊ�ַ�������
    std::string Uint32HostIPtoStr(const unsigned int &ulHostIP);
private:
    char* m_pszRecvBuff;           // ������Ϣ������
};

#endif//__TCP_SOCKET_H__

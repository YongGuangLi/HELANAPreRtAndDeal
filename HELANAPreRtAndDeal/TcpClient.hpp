//  (C) Copyright  2010.
//  windows socket tcp client class
//  Software License, Version 1.0.1

#ifndef WIN_SOCKET_TCP_CLIENT_HPP
#define WIN_SOCKET_TCP_CLIENT_HPP

#ifdef WIN32
#include<winsock2.h>
#pragma comment(lib, "ws2_32.lib")
typedef int		SOCKET_LEN;
#define MSG_NOSIGNAL 0
#else
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<sys/ioctl.h>
#include <netinet/tcp.h>
typedef int 				SOCKET;
typedef struct sockaddr_in 	SOCKADDR_IN;
typedef struct sockaddr 	SOCKADDR;
typedef SOCKADDR*			LPSOCKADDR;
typedef socklen_t			SOCKET_LEN;
#define SOCKET_ERROR		(-1)
#define INVALID_SOCKET		(-1)
#endif

#include "IncludeHead.h"

#define INVALID_CONNECT -1

class TcpClient
{
public:
    TcpClient()
    {
        IsConnected_ = NO;
    }

    virtual ~TcpClient(){
        ClearResource();
    }

public: 
    virtual bool Connect()
    {
        if( IsConnected_ )
            return true;

        if( Successful_Socket_ )
            CloseSocket( Socket_ );

        Successful_Socket_ = ( Socket_ = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP) ) != INVALID_SOCKET;
        if( !Successful_Socket_ )
        {
            return Successful_Socket_;
        }

        SetSocketCacheLength(Socket_);

        AddrServ_.sin_family			= AF_INET;
        AddrServ_.sin_port				= htons(12312);
        AddrServ_.sin_addr.s_addr  = inet_addr( "192.168.19.94");

        int rv = connect( Socket_, (LPSOCKADDR)(&AddrServ_), sizeof(AddrServ_) );
        IsConnected_ = ( rv != SOCKET_ERROR );

        return IsConnected_;
    }

    virtual void Broken(){
        if( Successful_Socket_ )
        {
            CloseSocket( Socket_ );
            IsConnected_ = false;
            Successful_Socket_ = false;
        }
    }



    virtual bool Send( EPPackage* value ){
        if (!IsConnected_)
        {
            Connect();
            return false;
        }

        if( value->BytePack.Length == -1 )
            return true;

        int rv = send( Socket_, (char*)value->BytePack.Data, value->GetBytePackActualLength(), MSG_NOSIGNAL );
        if( rv == SOCKET_ERROR )
        {
            IsConnected_ = false;
            return false;
        }
        else
            IsConnected_ = true;


        return true;
    }

    virtual const STRING& Id(){
        static const STRING id( Name() );
        return id;
    }

    virtual bool IsAsync(){
        return false;
    }

    virtual int BufferLength(){
        return buffer_len_;
    }


    virtual int GetLastError(){
        if (!IsConnected_)
        {
            return INVALID_CONNECT;
        }

#ifdef WIN32
        err_code_ = WSAGetLastError();
#else
        ////linux copyright
#endif
        return err_code_;
    }

    ///
    ///
    ///
    virtual STRING ErrorMessage( int err_code ){
#ifdef WIN32
        return WindowsErrorMessage( err_code );
#else
        return LinuxErrorMessage( err_code );
#endif
    }

protected:
#ifdef WIN32
    STRING WindowsErrorMessage( int err_code ){
        switch( err_code )
        {
        case WSAEINVAL:
            return "WSAEINVAL";
        case WSAENETDOWN:
            return "WSAENETDOWN";
        case WSAENETUNREACH:
            return "WSAENETUNREACH";
        case WSAECONNABORTED:
            return "WSAECONNABORTED";
        case WSAENOTCONN:
            return "WSAENOTCONN";
        }
        return "CUSTON ERROR";
    }
#else
    STRING LinuxErrorMessage( int err_code ){
    }
#endif

protected:
    IS_SUCCESS IsInitSuccess() const { return Successful_Startup_ && Successful_Socket_; }

    void ClearResource(){
        if( Successful_Startup_ )
        {
            if( Successful_Socket_ )
            {
                if( Socket_ > 0)
                {
                    CloseSocket( Socket_ );
                }
            }
#ifdef WIN32
            WSACleanup();
#endif
        }
    }

    void SetSocketCacheLength( SOCKET sockets ){
        if( is_need_setcache_ )
            SetSocketCacheLength(  sockets, cache_len_ );
    }


protected:
    void CloseSocket( SOCKET socket ){
#ifdef WIN32
        closesocket( socket );
#else
        close( socket );
#endif
    }


private:
    void SetSocketCacheLength( SOCKET sockets, int length ){
        ERROR_CODE error_code;
        int    		buf_length;
        SOCKET_LEN 	opt_length = sizeof( int );

        if( SOCKET_ERROR == ( error_code = getsockopt( sockets, SOL_SOCKET, SO_RCVBUF, (PCHAR)(&buf_length), (&opt_length) ) ) )
        {
            return;
        }

        if( SOCKET_ERROR == ( error_code = setsockopt( sockets, SOL_SOCKET, SO_RCVBUF, (PCHAR)(&length), opt_length ) ) )
        {
            return;
        }

        error_code = getsockopt( sockets, SOL_SOCKET, SO_RCVBUF, (PCHAR)(&buf_length), &opt_length );
        if( SOCKET_ERROR == error_code )
        {
            return;//
        }

        ///buffer_len_ = buf_length;
    }



protected:
    IS_SUCCESS 		Successful_Startup_;
    IS_SUCCESS		IsConnected_;
    IS_SUCCESS		NewConnected_;
    IS_SUCCESS		Successful_Socket_;

    SOCKET			Socket_;
    SOCKADDR_IN		AddrServ_;
    LPSOCKADDR		pAddrServ_;
    timeval			TimeVal_;
    int			Af_;
    int			Sock_;
    int			IpProtocol_;
    int         sleep_;
    int			buffer_len_;
    bool        is_need_ack_;
    //int			select_time_;

    bool		is_need_setcache_;
    int			cache_len_;


protected:
    int		err_code_;

public:
    static const char* Name(){
        static const char name[] = "tcp_client";
        return name;
    }
};

#endif

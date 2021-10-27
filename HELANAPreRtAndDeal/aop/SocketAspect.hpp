//  (C) Copyright ï¿½ï¿½ï¿½ï¿½ 2009.
//  custom windows sockets ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
//  ï¿½Ã»ï¿½ï¿½ï¿½ï¿½Ô¸ï¿½ï¿½ï¿½Ô¼ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ô¼ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿?
//  Software License, Version 1.0.

#ifndef DTXYNET_INTERFACE_SOCKET_AOP_HPP
#define DTXYNET_INTERFACE_SOCKET_AOP_HPP

#include "framework/TypeDefine.h"
#include "implement/IncludeHead.h"
#include "utility/parse/regex.hpp"
#include <iostream>

//xxx_Aspect class		--------ï¿½ï¿½ï¿½ï¿½:ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½æ£¨ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ö¾ï¿½ï¿½ï¿½ï¿½ï¿½
class WinSocketAspect
{
public:
	WinSocketAspect() : who_( "Winsocket" ) , log_( NULL ){};

public:
	void AttachLogger( LogPtrT log ){	
		log_ = log;
	}

	void ShowMessage(string strmsg)
	{
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, TRACK, "Winsocket", strmsg, TimeInt32() );
	}

	void ShowErrorMessage(string strmsg)
	{
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, ERR, "Winsocket", strmsg, TimeInt32() );
	}

protected:
	LogPtrT log_;
	STRING who_;
};

class WinSocketConnectAspect : public WinSocketAspect
{
public:
	WinSocketConnectAspect(){
	}
	
	void Failure( INTEGER error_code ){	
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, ERR, "Winsocket Connect", "Tcp connect failure.", TimeInt32() );
	}

	void Failure(){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, ERR, "Winsocket Connect", "Tcp connect failure.", TimeInt32() );
	}

	void SelectFailure(){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, ERR, "Winsocket Connect", "Select is failure, we need bind again.", TimeInt32() );
	}

	void Success(){				
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, WORN, "Winsocket Connect", "Tcp connect success.", TimeInt32() );
	}

	~WinSocketConnectAspect(){
	}
};

class WinSocketInitianizeAspect : public WinSocketAspect
{
public:
	WinSocketInitianizeAspect(){
	}

	void StartupFailure( INTEGER error_code ){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, ERR, "Winsocket Initianize", "Initianize failure.", TimeInt32() );
	}

	void StartupFailure(){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, ERR, "Winsocket Initianize", "Initianize failure.", TimeInt32() );
	}

	void StartupSuccess(){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, WORN, "Winsocket Initianize", "Initianize success.", TimeInt32() );
	}

	void SocketFailure( INTEGER error_code ){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, ERR, "Winsocket Initianize", "Socket create failure.", TimeInt32() );
	}

	void SocketFailure(){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, ERR, "Winsocket Initianize", "Socket create failure.", TimeInt32() );
	}

	void SocketSuccess(){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, WORN, "Winsocket Initianize", "Socket create success.", TimeInt32() );
	}

	~WinSocketInitianizeAspect(){
	}
};

class WinSocketSendAspect : public WinSocketAspect
{
public:
	WinSocketSendAspect(){
	}

	void Failure( INTEGER error_code ){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, ERR, "Socket Send", "Socket send failure.", TimeInt32() );
	}

	void Failure(){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, ERR, "Socket Send", "Socket send failure.", TimeInt32() );
	}

	void Success(){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, WORN, "Socket Send", "Socket send success.", TimeInt32() );
	}

	void AckSuccess(){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, WORN, "AckSuccess", "Get ack success.", TimeInt32() );
	}

	void AckFailure(){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, WORN, "AckFailure", "Get ack failure.", TimeInt32() );
	}

	~WinSocketSendAspect(){
	}
};

class WinSocketUdpSendAspect : public WinSocketAspect
{
public:
	WinSocketUdpSendAspect(){
	}

	void Failure( INTEGER error_code ){	
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, ERR, "Udp", "Udp package send failure.", TimeInt32() );
	}

	void Failure(){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, ERR, "Udp", "Udp package send failure.", TimeInt32() );
	}

	void Success(){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, WORN, "Udp", "Udp package send success.", TimeInt32() );
	}

	void AckSuccess(){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, WORN, "AckSuccess", "Get ack success.", TimeInt32() );
	}

	void AckFailure(){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, WORN, "AckFailure", "Get ack failure.", TimeInt32() );
	}

	~WinSocketUdpSendAspect(){
	}
};

class WinSocketReceiveAspect : public WinSocketAspect
{
public:
	WinSocketReceiveAspect(){
	}

	void Failure( INTEGER error_code ){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, ERR, "Socket Receive", "Socket receive failure.", TimeInt32() );
	}

	void Failure(){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, ERR, "Socket Receive", "Socket receive failure.", TimeInt32() );
	}

	void Success(){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, WORN, "Socket Receive", "Socket receive success.", TimeInt32() );
	}

	void Success( char* data, int length ){
		if( IsNull( log_ ) )
			return ;
		STRING str;
 		DtxyNet::Utility::HexStr<char>( data, length, str );
 		log_->Record( who_, TRACK, "Data Package", str, TimeInt32() );
	}

	~WinSocketReceiveAspect(){
	}
};

class WinSocketUdpRecvAspect : public WinSocketAspect
{
public:		
	WinSocketUdpRecvAspect(){				
	}

	void Failure( INTEGER error_code ){		
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, ERR, "Udp", "Udp package receive failure.", TimeInt32() );
	}

	void Failure(){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, ERR, "Udp", "Udp package receive failure.", TimeInt32() );
	}

	void Success(){				
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, WORN, "Udp", "Udp package receive success.", TimeInt32() );
	}

	void Success( char* data, int length ){
		if( IsNull( log_ ) )
			return ;
		STRING str;
 		DtxyNet::Utility::HexStr<char>( data, length, str );
 		log_->Record( who_, TRACK, "Data Package", str, TimeInt32() );
	}

	~WinSocketUdpRecvAspect(){
	}
};

class WinSocketListenAspect : public WinSocketAspect
{
public:
	WinSocketListenAspect(){
	}

	void AddClient( std::string address, INTEGER port ){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, WORN, "AddClient", "Add  a new client socket : address[ " + address + "] | port[ " + IToA( port ) + " ]", TimeInt32() );
	}

	void AddClient( std::string address ){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, WORN, "AddClient", "Add a new client socket : address[ " + address + " ]", TimeInt32() );
	}

	void BeginCreateClientThread(){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, WORN, "BeginCreateClientThread", "Begin create a client thread", TimeInt32() );
	}

	void CreateClientThreadFailure(){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, ERR, "CreateClientThreadFailure", "Create a client thread failure", TimeInt32() );
	}

	void CreateClientThreadSuccess(){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, WORN, "CreateClientThreadFailure", "Create a client thread success", TimeInt32() );
	}

	void ClientThreadLevelUp(){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, WORN, "ClientThreadLevelUp", "Client thread begin to level up" , TimeInt32() );
	}

	void ClientThreadLevelUpSuccess(){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, WORN, "MainThreadLevelDownFailure", "Local system don't support FIFO thread shedule" , TimeInt32() );
	}

	void NextNotRead(){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, WORN, "TcpServer NextNotRead", "Port is not readable" , TimeInt32() );
	}

	void ServerAddrFailure(){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, ERR, "ServerAddrFailure", "Server addr failure" , TimeInt32() );
	}

	void BeginListen(){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, WORN, "TcpServer BeginListen", "Server begin listen" , TimeInt32() );
	}

	void ListenFailure(){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, ERR, "TcpServer Listen", "Server listen failure" , TimeInt32() );
	}

	void MainThreadLevelDown(){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, WORN, "MainThreadLevelDown", "Main thread begin to level down" , TimeInt32() );
	}

	void MainThreadLevelDownFailure(){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, ERR, "MainThreadLevelDownFailure", "Client system don't support FIFO thread shedule" , TimeInt32() );
	}

	void ConnectSuccess(){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, ERR, "ConnectSuccess", "Server connect success" , TimeInt32() );
	}

	void WaitClient(){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, WORN, "TcpServer WaitClient", "Server is waiting client connection" , TimeInt32() );
	}

	void BeginReadData(){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, WORN, "TcpServer WaitClient", "Server is reading data" , TimeInt32() );
	}

	void ReadDataError(){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, WORN, "TcpServer ReadDataError", "Server can not read anything from client socket" , TimeInt32() );
	}

	void HasMaxClientConnect( INTEGER max_client_num ){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, WORN, "TcpServer HasMaxClientConnect", "Warnning! Max client socket connection ! [ " + IToA( max_client_num ) + " ]" , TimeInt32() );
	}

	void HasClientConnect( INTEGER  client_num ){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, WORN, "TcpServer HasClientConnect", "Server current client socket connection number is [ " + IToA( client_num ) + " ]" , TimeInt32() );
	}

	void ClientExit( std::string address ){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, WORN, "ClientExit", "Client socket : address[ " + address + " ] had exited", TimeInt32() );
	}

	//ÎªTcpServerMultÌí¼ÓµÄÈÕÖ¾
	void BindFailure(){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, ERR, "TcpServer Bind", "Server bind failure" , TimeInt32() );
	}
	
	void SelectFailure(){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, ERR, "TcpServer listen", "Select is failure, we need bind again.", TimeInt32() );
	}

	void AcceptFailure(){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, ERR, "TcpServer Accept", "Server accept failure" , TimeInt32() );
	}

	void AddClient(  ){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, WORN, "AddClient", "Add a new client socket ", TimeInt32() );
	}

	void DeleteClientForRecv(  ){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, ERR, "DeleteClient", "Delete a client socket for recv err ", TimeInt32() );
	}

	void DeleteClientForTimeout(  ){
		if( IsNull( log_ ) )
			return ;
		log_->Record( who_, ERR, "DeleteClient", "Delete a client socket for timeout ", TimeInt32() );
	}

	~WinSocketListenAspect(){
	}
};

#endif

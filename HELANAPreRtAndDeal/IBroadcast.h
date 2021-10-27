//  (C) Copyright 李理 2010.
//  data broadcast base class .
//  Software License, Version 1.0.0

#ifndef INTERDTXY_INCLUDE_FRAMEWORK_IBROADCAST_H
#define INTERDTXY_INCLUDE_FRAMEWORK_IBROADCAST_H

template<	typename T,
			typename LogT,
			typename TransferT,
			typename SignalT>
class IBroadcast
{
public:
	typedef T value_type;

public:
	IBroadcast(){}

	virtual ~IBroadcast(){
		sig_ = Null<SignalT>();
		comm_= Null<TransferT>();
		log_=  Null<LogT>();
	}

public:
	///
	///广播
	///
	virtual void Send( T data ) = 0;	
	
	///
	/// 动态注入数据终端对象
	///
	virtual void AttachSignal( SignalT sig  ){		
		sig_ = sig;
	}

	///
	/// 是否需要数据通讯对象
	///
	virtual bool NeedTransfer() = 0;

	///
	/// 动态注入数据通讯对象
	/// 要求异步通讯.
	///
	virtual void AttachTransfer( TransferT comm  ){				
		comm_ = comm;
	}

	///
	/// 是否支持该通讯传输对象
	///
	bool IsSupport( TransferT comm  ){	
		return comm->IsAsync();
	}

	///
	/// 是否支持该通讯传输对象
	///
	virtual bool IsSupport( const STRING& name ) = 0;

	///
	///获取标志名称
	///
	virtual const STRING& Id() = 0;	

	///
	/// 动态注入日志处理对象
	///
	virtual void AttachLogger( LogT log ){		
		log_ = log;
	}

	//SignalT GetSignal(){ return sig_; }

protected:
	SignalT		sig_;
	TransferT	comm_;
	LogT		log_;
};

#endif
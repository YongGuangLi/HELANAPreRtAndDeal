//  (C) Copyright ���� 2010.
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
	///�㲥
	///
	virtual void Send( T data ) = 0;	
	
	///
	/// ��̬ע�������ն˶���
	///
	virtual void AttachSignal( SignalT sig  ){		
		sig_ = sig;
	}

	///
	/// �Ƿ���Ҫ����ͨѶ����
	///
	virtual bool NeedTransfer() = 0;

	///
	/// ��̬ע������ͨѶ����
	/// Ҫ���첽ͨѶ.
	///
	virtual void AttachTransfer( TransferT comm  ){				
		comm_ = comm;
	}

	///
	/// �Ƿ�֧�ָ�ͨѶ�������
	///
	bool IsSupport( TransferT comm  ){	
		return comm->IsAsync();
	}

	///
	/// �Ƿ�֧�ָ�ͨѶ�������
	///
	virtual bool IsSupport( const STRING& name ) = 0;

	///
	///��ȡ��־����
	///
	virtual const STRING& Id() = 0;	

	///
	/// ��̬ע����־�������
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
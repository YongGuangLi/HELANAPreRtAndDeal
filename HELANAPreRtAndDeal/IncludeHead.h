//  (C) Copyright Lili 2010.
//  total include header files
//  Software License, Version 1.0.0

#ifndef INTERDTXY_INCLUDE_FRAMEWORK_INCLUDE_HEAD_H
#define INTERDTXY_INCLUDE_FRAMEWORK_INCLUDE_HEAD_H

///
///standard c++ library
///
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/vector.hpp> 
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
//#include <boost/noncopyable.hpp>
#ifdef WIN32
	#include <string>
#else
	#include <string.h>
#endif
#include <vector>
#include <map>
using namespace std;

///essential data type
enum BINARY{ ZERO = 0, ONE };

////
////锟斤拷志锟斤拷锟斤拷枚锟斤拷
////
enum LOG_LEVEL{ TRACK, WORN, HIGH_WORN, ERR, DEAD };


////
////锟斤拷锟斤拷锟斤拷锟斤拷刹锟斤拷值锟矫讹拷锟斤拷锟斤拷投锟斤拷锟?
////
enum FRAMWORK_PART{ PROTOCOL = 0,
                    TRANSFER,
                    BROADCAST,
                    SIGNAL1,
                    LOGGER,
                    PT_TABLE,
                    PTO_TRANSFER,
                    BRD_TRANSFER,
                    SIG_TRANSFER ,
                    DEFAULT};

///
///
///
enum SERVICE_EVENT{ CLIENT_IS_ACTIVED = 0,
					INVALID_CLIENT,
					SERVICE_IS_END,
					NEW_CLIENT,
					CLIENT_JOIN_SERVICE,
					CLIENT_EXIT_SERVICE,
					CLIENT_RECV_ACK
};

////
////Service run type 
////
enum SERVICE_RUNTYPE{ ALLWAYS = 0, ONCE };

////
////Service run state
////
enum SERVICE_STATE{ BEGIN_RUN = 0, RUNNING, STOPPING, STOP, PAUSE };

typedef char					CHAR;
typedef char*					PCHAR;
typedef unsigned char			UCHAR;		
typedef unsigned char*			PUCHAR;
typedef boost::shared_array<UCHAR>	PucSPT;

typedef int			INTEGER;
typedef short		SHORT;
typedef long		LONG;
typedef unsigned short USHORT;
typedef float		FLOAT;
typedef std::string STRING;
typedef int			ERROR_CODE;
typedef bool		IS_SUCCESS;

#define SUCCESS ZERO;
#define FAILURE ONE;
#define NO		ZERO;
#define OK		ONE;

struct SingleThreadTraits{};
struct MultiThreadTraits{};


typedef 
struct ElecPoint
{
	ElecPoint() : Name( "NoName" ), Id( -9999 ), IsFloat( false ), FValue( -9999 ), NValue( -9999 ), Time( -9999 ), Status( 1 ), GroupSn( '0' ){}
	ElecPoint( const STRING& name, int id, float f_value, int time, int status ) : Name( name ), Id( id ), IsFloat( true ) , FValue( f_value ), NValue( 0 )      , Time( time ), Status( status ), GroupSn( '0' ), PackageId( 0 ){}
	ElecPoint( const STRING& name, int id, long  n_value, int time, int status ) : Name( name ), Id( id ), IsFloat( false ), FValue( 0.0     ), NValue( n_value ), Time( time ), Status( status ), GroupSn( '0' ), PackageId( 0 ){}
	ElecPoint( const STRING& name, int id, float f_value, int time, int status, int group_sn) : Name( name ), Id( id ), IsFloat( true ) , FValue( f_value ), NValue( 0 )      , Time( time ), Status( status ), GroupSn( group_sn ), PackageId( 0 ){}
	ElecPoint( const STRING& name, int id, long  n_value, int time, int status, int group_sn) : Name( name ), Id( id ), IsFloat( false ), FValue( 0.0     ), NValue( n_value ), Time( time ), Status( status ), GroupSn( group_sn ), PackageId( 0 ){} 
	ElecPoint( const STRING& name, int id, float f_value, int time, int status, int group_sn, int package_id ) : Name( name ), Id( id ), IsFloat( true ) , FValue( f_value ), NValue( 0 )      , Time( time ), Status( status ), GroupSn( group_sn ), PackageId( package_id ){}
	ElecPoint( const STRING& name, int id, long  n_value, int time, int status, int group_sn, int package_id ) : Name( name ), Id( id ), IsFloat( false ), FValue( 0.0     ), NValue( n_value ), Time( time ), Status( status ), GroupSn( group_sn ), PackageId( package_id ){} 

public:
	STRING	Name;
	int		Id;
	bool	IsFloat;
	float	FValue;
	long	NValue;
	long	Time;
	int		Status;
	int		GroupSn;
	int     PackageId;
	//CHAR	CopyName[32];

private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & Name;
		ar & Id;
		ar & IsFloat;
		ar & FValue;
		ar & NValue;
		ar & Time;
		ar & Status;	
		ar & GroupSn;	
		ar & PackageId;
	}
} EP;

BOOST_SERIALIZATION_SHARED_PTR(EP)

struct BytePackage
{
	typedef unsigned char CharT;

	BytePackage(){
		Data   = new CharT[ 0 ];
		Length = 0;
	}

	BytePackage( int length ){
		Data = new CharT[ length ];
		memset( Data, 0, length );
		Length = length;
	}

	~BytePackage(){
		delete[] Data;
	}

	void SetZero(){
		if( Data == NULL || Length < 0 )
			return;
		memset( Data, 0, Length );
	}

	void Reset(int length)
	{
		delete[] Data;
		Data = NULL;
		Length = length;
		if( length == 0 )
			return;
		Data = new CharT[ length ];
		memset( Data, 0, length );
	}

public:
	void Swap( BytePackage& other ){		
		CharT*	tmp_data = Data;
		int		tmp_length = Length;

		Data = other.Data;
		Length = other.Length;

		other.Data = tmp_data;
		other.Length = tmp_length;
	}

	CharT* Data;
	int Length;

private:
	friend class boost::serialization::access;
	template<class Archive>
    void save(Archive & ar, const unsigned int version) const
    {
        ar & Length;		
		for( int i = 0; i < Length; ++i ){
			ar & Data[i];  
		}
    }
    template<class Archive>
    void load(Archive & ar, const unsigned int version)
    {
		ar & Length;
		Data = new CharT[ Length ];
		memset( Data, 0, Length );
		for( int i = 0; i < Length; ++i ){
			ar & Data[i];
		}        
    }
    BOOST_SERIALIZATION_SPLIT_MEMBER()

public:	
	static BytePackage* Instance(){
		return new BytePackage();
	}

	static BytePackage* Instance( int length ){
		return new BytePackage( length );
	}

	bool Equals( const BytePackage& other ){
		if( Length != other.Length )
			return false;

		///
		///在此并未使用字符串的比较函数,因为
		///很可能在报文中间有'\0'字符,出现
		///中间截断.
		///故采用最基本的逐个比较
		///
		for( int i = 0; i < Length; ++i ){
			if( Data[i] != other.Data[i] )
				return false;
		}

		return true;
	}
};

template<typename T>
struct DefaultPtrType
{
	typedef T* PtrT;
};

template<>
struct DefaultPtrType<EP>
{	
	typedef boost::shared_ptr<EP> PtrT;
};

struct EPPackage
{
public:
	typedef vector< DefaultPtrType<EP>::PtrT > EPListT;

	EPPackage() : BytePackActualLength( 0 ), PackageId( 0 ){}
	EPPackage( int length ) : BytePack( length ), BytePackActualLength( length ), PackageId( 0 ){}

	BytePackage BytePack;	
	EPListT		EPList;
	int			PackageId;

private:
	///
	///该变量并未与BytePack中的length进行同步,
	///只是简单地进行报文实际长度的中间保存.
	///
	int			BytePackActualLength;

public:
	void SetBytePackActualLength( int length ){
		if( length > BytePack.Length )
			return;
		BytePackActualLength = length;
	}

	int GetBytePackActualLength(){
		return BytePackActualLength;
	}

private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		//ar & BytePack;
		ar & EPList;
		ar & PackageId;
	}

public:	
	void AddEP(){
		AddEP( "", -1, (long)-1, -1, -1 );	
	}

	void AddEP( const STRING& name, int id, float f_value, int time, int status ) {
		EPList.push_back( DefaultPtrType<EP>::PtrT( new EP( name, id, f_value, time, status, 0, PackageId ) ) );
	}
	
	void AddEP( const STRING& name, int id, long  n_value, int time, int status ) {
		EPList.push_back( DefaultPtrType<EP>::PtrT( new EP( name, id, n_value, time, status, 0, PackageId ) ) );
	}

	void AddEP( const STRING& name, int id, float f_value, int time, int status, int group_sn ) {
		EPList.push_back( DefaultPtrType<EP>::PtrT( new EP( name, id, f_value, time, status, group_sn, PackageId ) ) );
	}

	void AddEP( const STRING& name, int id, long  n_value, int time, int status, int group_sn ) {
		EPList.push_back( DefaultPtrType<EP>::PtrT( new EP( name, id, n_value, time, status, group_sn, PackageId ) ) );
	}

	void AddEP( const STRING& name, int id, long  n_value, int time, int status, int group_sn, int package_id ) {
		EPList.push_back( DefaultPtrType<EP>::PtrT( new EP( name, id, n_value, time, status, group_sn, package_id ) ) );
	}

	void AddEP( const STRING& name, int id, float  n_value, int time, int status, int group_sn, int package_id ) {
		EPList.push_back( DefaultPtrType<EP>::PtrT( new EP( name, id, n_value, time, status, group_sn, package_id ) ) );
	}

public:
	static EPPackage* Instance(){
		return new EPPackage();
	}

	static EPPackage* Instance( int length ){
		return new EPPackage( length );
	}
};

BOOST_SERIALIZATION_SHARED_PTR(EPPackage)

template<>
struct DefaultPtrType<EPPackage>
{
	typedef boost::shared_ptr<EPPackage> PtrT;
};

/////////////
///////////// extend EPPackage struct define
/////////////
struct EPPackageEx : public EPPackage
{
public:
	EPPackageEx(){}

	EPPackageEx( int length ) : EPPackage( length ){}

public:
	enum PointState{ POINT_HAS_ID = 1, POINT_HAS_NAME = 2, POINT_HAS_TIME = 4, POINT_HAS_STATUS = 8, POINT_HAS_GROUP = 16 };
	int		Node;				//包节点编号
	long	Sn;					//包序号
	long	Time;				//包发送的时间
	unsigned short FactorySN;	//电厂编号
	unsigned int   PtState;     //For example : PtState = POINT_HAS_ID | POINT_HAS_STATUS;
	unsigned short CheckSum;	//校验和,算法待定！		

public:
	bool HasId()	{ return ( PtState & POINT_HAS_ID )		== POINT_HAS_ID;	}
	bool HasName()	{ return ( PtState & POINT_HAS_NAME )	== POINT_HAS_NAME;	}
	bool HasTime()	{ return ( PtState & POINT_HAS_TIME )	== POINT_HAS_TIME;	}
	bool HasStatus(){ return ( PtState & POINT_HAS_STATUS )	== POINT_HAS_STATUS;}
	bool HasGroup()	{ return ( PtState & POINT_HAS_GROUP )	== POINT_HAS_GROUP;	}

private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & Node;
		ar & Sn;
		ar & Time;
		ar & FactorySN;		
		ar & PtState;
		ar & CheckSum;
		ar & BytePack;
		ar & EPList;
	}

public:
	static EPPackageEx* Instance(){
		return new EPPackageEx();
	}

	static EPPackageEx* Instance( int length ){
		return new EPPackageEx( length );
	}
};

struct InterfaceParam
{
public:
	InterfaceParam(){}
	InterfaceParam( boost::posix_time::ptime begin_day_time, boost::posix_time::ptime end_day_time ):BeginDayTime( begin_day_time ), EndDayTime( end_day_time ){}
public:
	boost::posix_time::ptime BeginDayTime;
	boost::posix_time::ptime EndDayTime;
	long   PackageSn;
	short  ACKType;
	STRING CfgName;
};

template<>
struct DefaultPtrType<EPPackageEx>
{
	typedef boost::shared_ptr<EPPackageEx> PtrT;
};

typedef std::vector< std::vector< STRING > > PointTableT;

template<>
struct DefaultPtrType<PointTableT>
{
	typedef boost::shared_ptr<PointTableT> PtrT;
};

typedef DefaultPtrType<PointTableT>::PtrT PointTablePtrT;

template<typename PtrT>
bool IsNull( PtrT ptr ){
	return ptr == NULL;	
}

template<typename PtrT>
PtrT Null(){
	return NULL;
}

template<>
inline bool IsNull<PointTablePtrT>( PointTablePtrT ptr ){
	return ptr.get() == NULL;
}

#endif

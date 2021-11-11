//  (C) Copyright ���� 2009.
//  common bit opertators
//  Software License, Version 1.0.

#ifndef DTXYNET_INTERFACE_UTILITY_CONVERTOR_HPP
#define DTXYNET_INTERFACE_UTILITY_CONVERTOR_HPP

#include <bitset>
#include <stdlib.h>
#include <boost/lexical_cast.hpp>

using namespace std;

#define INNER_ERROR_NUMBER -99999
namespace DtxyNet
{
	namespace Utility
	{ 
		template<typename T, typename CharT>
		T AToAny( const CharT* data)
		{
			T result = 0;
			if( data == NULL )
				return result;
			
			CharT* ptr = (CharT*)(&result);
			for( int i = 0; i < sizeof(T) ; ++i)
				ptr[i] = data[i];
			return result;
		}

		template<typename T, typename CharT>
		T AToAny( const CharT* data, int length )
		{
			T result = 0;
			if( data == NULL )
				return result;
			
			CharT* ptr = (CharT*)(&result);
			for( int i = 0; i < length ; ++i)
				ptr[i] = data[i];
			return result;
		}

		///be care for
		template<typename T, typename CharT>
		T AToAnyReverse( const CharT* data, int length )
		{
			T result = 0;
			if( data == NULL )
				return result;

			CharT* ptr = (CharT*)(&result);
			for( int i = length - 1; i >= 0 ; i--)
				ptr[i] = data[length - i - 1];
			return result;
		}

		template<typename T, typename CharT>
		void FToA( T f , CharT *data )
		{
			unsigned char *p =(unsigned char *)&f;
			for( int i = 0; i < sizeof(T); i++ )
			{
				data[i] = p[i];
			}
		}

		template<typename CharT >
		float IEEEAtoF( CharT pByte[4] )
		{
			if( pByte[0] == 0 && pByte[1] == 0 && pByte[2] == 0 && pByte[3] == 0 )
				return 0;
			 bitset<32> bitAll( *(unsigned long*)pByte );
			 bitset<32> bitTemp;
			 bitTemp = bitAll;
			 bitTemp <<= 1;
			 long ulExponent = 0;
			 for ( int i = 0; i < 8; i++ )
			 {
				ulExponent |= ( bitTemp[ 31 - i ] << ( 7 - i ) );
			 }
			 ulExponent -= 127;
			 bitTemp = bitAll;
			 bitTemp <<= 9;
			 float fMantissa = 1.0f;
			 for ( int i = 0; i < 23; i++ )
			 {
				  bool b = bitTemp[ 31 - i ];
				  fMantissa += ( (float)bitTemp[ 31 - i ] / (float)( 2 << i ) );
			 }
			 float fPow;
			 if ( ulExponent >= 0 )
			 {
				fPow = (float)( 2 << ( ulExponent - 1 ) );
			 }
			 else
			 {
				fPow = 1.0f / (float)( 2 << ( -1 - ulExponent ) );
			 }
			 return fMantissa * fPow;
		}

		template<typename T, typename CharT>
		void IToA( T n , CharT *data, int length, bool reverse = true )
		{
			T tmp = n;
			if( reverse )
			{
				for( int i = length - 1, j = 0 ; i >= 0 ; --i , ++j )
				{
					tmp >>= ( i * 8 );
					data[j] = (CharT)tmp;
					tmp <<= ( i * 8 );
					n -= tmp;
					tmp = n; 
				}
			}
			else
			{
				for( int i = length - 1 ; i >= 0 ; --i )
				{
					tmp >>= ( i * 8 );
					data[i] = (CharT)tmp;
					tmp <<= ( i * 8 );
					n -= tmp;
					tmp = n; 
				}
			}
		}

		template<typename T, typename StrT>
		T str_to_number( StrT value )
		{
			T d;
			try
			{
				d = boost::lexical_cast<T>(value);
				return d;
			}
			catch( boost::bad_lexical_cast ex )
			{
				return (T)INNER_ERROR_NUMBER;
			}
		}

		template<typename T>
		bool StrToAny( const std::string& str_value, T* rhs ){		
			if( rhs == NULL || str_value.size() == 0 )
				return false;
			T value = str_to_number<T,std::string>( str_value );
			*rhs = value;
			return true;
		}


		template<typename T, typename CharT>
		void FToA( T f , CharT *data, int length ){
			unsigned char *p =(unsigned char *)&f;
			for( int i = 0; i < length; i++ )
			{
				data[i] = p[i];
			}
		}
	};
};

#endif

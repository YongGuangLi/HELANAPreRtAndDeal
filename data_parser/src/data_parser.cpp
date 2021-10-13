/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: data_format.cpp
* 文件描述: 数据解析接口类
*  作  者 : %林晓雨%，18942552977
* 创建日期: 2014-9-10 14:25:01
*******************************************************************************/

#include "data_parser.h"
#include "file_buff.h"
#include "error_def.h"
#include "pub_def.h"
#include "public_function_library.h"
#include "util.h"

#include <memory.h>
#include <iostream>
#include <string.h>
using namespace std;

DataParser::DataParser(const ParserType tt)
:
mType(tt),
mFileBuff(NULL),
mStrError(static_cast<std::string>(STRING_EMPTY))
{

}


DataParser::~DataParser(void)
{
	if (mFileBuff != NULL) delete mFileBuff;
}


void
DataParser::config(
		const RemoteDataType &data_type,
		const string &path,
		const string &point_fname_prefix)
{
	mDataType = data_type;
	mFileBuff = new FileBuff(path, point_fname_prefix);
}


bool
DataParser::rt_Open()
{
	if (mFileBuff == NULL) return false;
	return mFileBuff->open();
}


void
DataParser::rt_Close()
{
	if (mFileBuff != NULL)  mFileBuff->close();
}


void
DataParser::CreatePointData(PointDatas* aPoints, unsigned long lPointCount)
{				  
	aPoints->NodeNo = 0;
	aPoints->ID=true;
	aPoints->PackTime = 0;
	aPoints->DCNo = 0;
	aPoints->Name=true;
	aPoints->No=true;
	aPoints->State=true;
	aPoints->Time=true;
	aPoints->SetCode=true;
	aPoints->Count=lPointCount;
	aPoints->CheckSum = 0;

	CreatePrivatePointValue(aPoints, lPointCount);
}


bool 
DataParser::rt_Receive(PointDatas* pPoints)
{
	//获取缓冲区大小
	long nLen=0;
	if(mDataType == Binary)
	{
		if(!GetPointPackLen(*pPoints,&nLen))
			return false;
	}
	else
	{
		if(!GetPointPackTxtLen(*pPoints,&nLen))
			return false;
	}
	
	if (mFileBuff == NULL) return false;
	//缓冲区数据
	//void* pData=new char[nLen];
	//Linda
	char * pData=new char[nLen];
	memset(pData,0,sizeof(char)*nLen);
	//接收数据
	if(!mFileBuff->retrieveData(pData, nLen))
	{
		mStrError = mFileBuff->getError();
		delete[] pData;
		return false;
	}

	if(nLen <= 0)
	{
		pPoints->Count=0;
		delete[] pData;
		return true;
	}

	if(mDataType == Binary)//按照二进制解包
	{
		bool bRet= UnpackPointData(pData, nLen, pPoints);
		if(!bRet)
			pPoints->Count=0;
		delete[] pData;
		return true;
	}

	//按文本方式解包
	//string strData=string(nLen+1,0);
	//strData=(char*)pData;
	string strData(pData, nLen);
	UnpackPointDataFromStr(strData,pPoints);	
	delete[] pData;
	return true;
}
int DataParser::getDirFileNum()
{
	return mFileBuff->getDirFileNum();
}

bool 
DataParser::rt_Send(const PointDatas& aPoints)
{
	if (mFileBuff == NULL) return false;
	if(mDataType == Binary)
	{
		//获取缓冲区大小
		long nLen=0;
		if(!GetPointPackLen(aPoints,&nLen))
			return false;
		//打包数据
		//void* pData=new char[nLen];
		//Linda
		char* pData=new char[nLen];
		if(!PackPointData(aPoints,pData,&nLen))
		{
			delete[] pData;
			return false;
		}
		//发送数据
		if(!mFileBuff->saveData(pData,nLen))
		{
			mStrError=mFileBuff->getError();
			delete[] pData;
			return false;
		}
		delete[] pData;
		return true;
	}
	else
	{
		//按文本方式发送
		string strData="";
		if(!PackPointDataToStr(aPoints,strData))
			return false;
		if(!mFileBuff->saveData(strData.c_str(),strData.length()))
		{
			mStrError=mFileBuff->getError();
			return false;
		}
		return true;
	}
}


string 
DataParser::getError()
{
	string str_errmsg = mStrError;
	mStrError = static_cast<std::string>(STRING_EMPTY);
	return str_errmsg;
}


bool 
DataParser::UnpackPointData(const void* pData,long pDataLen, PointDatas* pPoints)
{
	if(pData==NULL || pPoints->Count==0)
	{
		mStrError=IDS_NULL_POINT;
		return false;
	}
	if (ModelPackage != mType)
	{
		if (NULL == pPoints->Points)
		{
			mStrError=IDS_NULL_POINT;
			return false;
		}
	}
	else
	{
		if (NULL == pPoints->MPValues)
		{
			mStrError=IDS_NULL_POINT;
			return false;
		}
	}
	char* pTem=(char*)const_cast<void*>(pData);
	//获取数包节点
	int cNodeCode=*(int*)pTem;
	if(cNodeCode!=PACK_NODE_NO)
	{
		mStrError=IDS_ERROR_PACK;																						  
		return false;
	}
	pPoints->NodeNo=cNodeCode;//节点号
	//获取包数据类型
	PackDataType eDataType;
	GetPackDataType(pData,&eDataType);
	if(eDataType!=Point)
	{
		mStrError=IDS_ERROR_POINT_PACK;
		return false;
	}
	//校验和
	pTem+=(pDataLen-PACK_CHECK_SUM_LEN);
	unsigned short nCheckSum=*(unsigned short*)pTem;
	//计算校验和
	unsigned short sCheckSum=CheckSum16((unsigned char*)pData,pDataLen-PACK_CHECK_SUM_LEN);
	//包的编号
	pTem=(char*)const_cast<void*>(pData);
	pTem+=PACK_NODE_NO_LEN;
	pPoints->No=*(long*)pTem;//(long)(*pTem);
	if(sCheckSum!=nCheckSum)
	{
		mStrError=Util::Convert<long,std::string>(pPoints->No)+ IDS_ERROR_CHECK_SUM;
		return false;
	}
	//电厂编号
	pTem+=PACK_NO_LEN;
	pPoints->PackTime=*(long*)pTem;//包发送时间
	pTem+=PACK_TIME_LEN;
	pTem+=PACK_DATA_TYPE_LEN;
	pPoints->DCNo=*(unsigned short*)pTem;

	pTem+=PACK_DC_NO_LEN;	
	pTem+=PACK_DATA_LEN_LEN;
	//控制位
	unsigned short nControl=*(unsigned short*)pTem;
	pPoints->ID=((nControl&0X1)==1);//是否编号
	pPoints->Name=((nControl&0X2)>>1==1);//是否点名
	pPoints->Time=((nControl&0X4)>>2==1);//是否时间戳
	pPoints->State=((nControl&0X8)>>3==1);//是否状态
	pPoints->SetCode=((nControl&0X10)>>4==1);//是否机组号

	//点数
	pTem+=PACK_CONTROL_LEN;
	long nPointCount=*(long*)pTem;

	pTem+=PACK_DATA_COUNT_LEN;

	return UnpackPrivatePointData(pTem, pPoints, nPointCount);
}


bool 
DataParser::UnpackPointDataFromStr(const string& strData,PointDatas* pPoints)
{
	//检查数据
	if(strData == "")
	{
		mStrError=IDS_DATA_NULL;
		return false;
	}
	//包头数据数大于
	//LYZ_LIB::strings strSplits=LYZ_LIB::SplitString(strData, SPLIT, true);
	vector<std::string> strSplits = Util::SplitString(strData, SPLIT, true);
	if(strSplits.size()<PACK_HEAD_COUNT)
	{
		mStrError=IDS_PACK_HEAD_ERROR;
		return false;
	}
	//LYZ_LIB::strings::iterator i=strSplits.begin();
	vector<std::string>::iterator i=strSplits.begin();
	//std::list<std::string>::iterator i=strSplits.begin();
	if(*i!=TXT_HEADER)
	{
		mStrError=IDS_ERROR_BUFFER_FILE;
		return false;
	}
	pPoints->NodeNo = PACK_NODE_NO;
	++i;
	pPoints->No=Util::Convert<string,long>(*i);//包序号
	++i;
	pPoints->Count=Util::Convert<string,unsigned long>(*i);//点的个数
	++i;
	pPoints->PackTime=PubOpt::SystemOpt::StrToDateTm(*i);//包的时间
	++i;
	pPoints->DCNo=Util::Convert<string,unsigned short>(*i);//电厂编号
	++i;
	pPoints->ID=Util::Convert<string,bool>(*i);//是否有ID
	++i;
	pPoints->Name=Util::Convert<string,bool>(*i);//是否有点名
	++i;
	pPoints->SetCode=Util::Convert<string,bool>(*i);//是否有机组号
	++i;
	pPoints->State=Util::Convert<string,bool>(*i);//是否有状态
	++i;
	pPoints->Time=Util::Convert<string,bool>(*i);//是否有点的时间戳
	++i;
	int nLeftPointData=strSplits.size()-PACK_HEAD_COUNT;//剩下数据的个数
	if(nLeftPointData==0)
	{
		pPoints->Count=0;
		return true;
	}

	return UnpackPrivatePointDataFromStr(pPoints, strSplits, i);
}


bool 
DataParser::PackPointDataToStr(PointDatas aPoints, string& strData)
{
	strData=TXT_HEADER;//文本文件头
	strData+=SPLIT_LINE;
	strData+=Util::Number2String<long>(aPoints.No)+SPLIT_CHAR;//包序号
	strData+=Util::Number2String<unsigned long>(aPoints.Count)+SPLIT_CHAR;//点的数目
	strData+=PubOpt::SystemOpt::DateTmToStr(aPoints.PackTime)+SPLIT_CHAR;//包时间
	strData+=Util::Convert<unsigned short,string>(aPoints.DCNo)+SPLIT_LINE;//电厂编号
	strData+=Util::Convert<bool,string>(aPoints.ID)+SPLIT_CHAR;//是否有ID
	strData+=Util::Convert<bool,string>(aPoints.Name)+SPLIT_CHAR;//是否有点名
	strData+=Util::Convert<bool,string>(aPoints.SetCode)+SPLIT_CHAR;//是否有机组号
	strData+=Util::Convert<bool,string>(aPoints.State)+SPLIT_CHAR;//是否有状态
	strData+=Util::Convert<bool,string>(aPoints.Time)+SPLIT_LINE;//是否有点时间戳

	return PackPrivatePointDataToStr(aPoints, strData);
}


bool 
DataParser::PackPointData(PointDatas aPoints,void* pData,long* pDataLen)
{
	if(pData==NULL || pDataLen==NULL)
	{
		mStrError=IDS_NULL_POINT;
		return false;
	}
	long nPackLen=0;
	//获取打包需要的字节数
	GetPointPackLen(aPoints,&nPackLen);
	if(*pDataLen<nPackLen)
	{
		mStrError=IDS_BUFFER_SMALL;
		return false;
	}
	char* pTem=(char*)pData;
	int nNode=PACK_NODE_NO;
	memcpy(pTem,&nNode,sizeof(nNode));//包节点号

	pTem+=PACK_NODE_NO_LEN;
	memcpy(pTem,&aPoints.No,sizeof(aPoints.No));//包序号

	pTem+=PACK_NO_LEN;
	memcpy(pTem,&aPoints.PackTime,sizeof(aPoints.PackTime));//包发送的时间

	pTem+=PACK_TIME_LEN;
	*pTem=Point;//包的数据类型

	pTem+=PACK_DATA_TYPE_LEN;
	memcpy(pTem,&aPoints.DCNo,sizeof(aPoints.DCNo));//电厂编号

	pTem+=PACK_DC_NO_LEN;	
	long nDataLen=0;//数据长度
	GetPointDataLen(aPoints,&nDataLen);
	memcpy(pTem,&nDataLen,sizeof(long));//数据区的长度

	pTem+=PACK_DATA_LEN_LEN;
	short int nControl=0;
	if(aPoints.ID)
		nControl=nControl|0X1;//编号控制位
	if(aPoints.Name)
		nControl=nControl|0X2;//点名控制位
	if(aPoints.Time)
		nControl=nControl|0X4;//时间戳控制位
	if(aPoints.State)
		nControl=nControl|0X8;//状态控制位
	if(aPoints.SetCode)
		nControl=nControl|0X10;//机组号控制位
	memcpy(pTem,&nControl,sizeof(nControl));//数据控制区

	pTem+=PACK_CONTROL_LEN;
	memcpy(pTem,&aPoints.Count,sizeof(aPoints.Count));//点数

	pTem+=PACK_DATA_COUNT_LEN;

	PackPrivatePointData(aPoints, pTem);

	//校验和
	//unsigned short nCheckSum=CheckSum16((unsigned char*)pData,nPackLen-2);
	unsigned short nCheckSum=CheckSum16((unsigned char*)pData,nPackLen-PACK_CHECK_SUM_LEN);								   
	memcpy(pTem,&nCheckSum,sizeof(nCheckSum));//CheckSum16((unsigned char*)pTem,nPackLen-2);
	*pDataLen=nPackLen;
	return true;
}

const unsigned char szCRCHi[]=   
{   
	0x00,0xC1,0x81,0x40,0x01,0xC0,0x80,0x41,0x01,0xC0,   
	0x80,0x41,0x00,0xC1,0x81,0x40,0x01,0xC0,0x80,0x41,   
	0x00,0xC1,0x81,0x40,0x00,0xC1,0x81,0x40,0x01,0xC0,   
	0x80,0x41,0x01,0xC0,0x80,0x41,0x00,0xC1,0x81,0x40,   
	0x00,0xC1,0x81,0x40,0x01,0xC0,0x80,0x41,0x00,0xC1,   
	0x81,0x40,0x01,0xC0,0x80,0x41,0x01,0xC0,0x80,0x41,   
	0x00,0xC1,0x81,0x40,0x01,0xC0,0x80,0x41,0x00,0xC1,   
	0x81,0x40,0x00,0xC1,0x81,0x40,0x01,0xC0,0x80,0x41,   
	0x00,0xC1,0x81,0x40,0x01,0xC0,0x80,0x41,0x01,0xC0,   
	0x80,0x41,0x00,0xC1,0x81,0x40,0x00,0xC1,0x81,0x40,   
	0x01,0xC0,0x80,0x41,0x01,0xC0,0x80,0x41,0x00,0xC1,   
	0x81,0x40,0x01,0xC0,0x80,0x41,0x00,0xC1,0x81,0x40,   
	0x00,0xC1,0x81,0x40,0x01,0xC0,0x80,0x41,0x01,0xC0,   
	0x80,0x41,0x00,0xC1,0x81,0x40,0x00,0xC1,0x81,0x40,   
	0x01,0xC0,0x80,0x41,0x00,0xC1,0x81,0x40,0x01,0xC0,   
	0x80,0x41,0x01,0xC0,0x80,0x41,0x00,0xC1,0x81,0x40,   
	0x00,0xC1,0x81,0x40,0x01,0xC0,0x80,0x41,0x01,0xC0,   
	0x80,0x41,0x00,0xC1,0x81,0x40,0x01,0xC0,0x80,0x41,   
	0x00,0xC1,0x81,0x40,0x00,0xC1,0x81,0x40,0x01,0xC0,   
	0x80,0x41,0x00,0xC1,0x81,0x40,0x01,0xC0,0x80,0x41,   
	0x01,0xC0,0x80,0x41,0x00,0xC1,0x81,0x40,0x01,0xC0,   
	0x80,0x41,0x00,0xC1,0x81,0x40,0x00,0xC1,0x81,0x40,   
	0x01,0xC0,0x80,0x41,0x01,0xC0,0x80,0x41,0x00,0xC1,   
	0x81,0x40,0x00,0xC1,0x81,0x40,0x01,0xC0,0x80,0x41,   
	0x00,0xC1,0x81,0x40,0x01,0xC0,0x80,0x41,0x01,0xC0,   
	0x80,0x41,0x00,0xC1,0x81,0x40    
};   

const unsigned char szCRCLo[]=   
{   
	0x00,0xC0,0xC1,0x01,0xC3,0x03,0x02,0xC2,0xC6,0x06,   
	0x07,0xC7,0x05,0xC5,0xC4,0x04,0xCC,0x0C,0x0D,0xCD,   
	0x0F,0xCF,0xCE,0x0E,0x0A,0xCA,0xCB,0x0B,0xC9,0x09,   
	0x08,0xC8,0xD8,0x18,0x19,0xD9,0x1B,0xDB,0xDA,0x1A,   
	0x1E,0xDE,0xDF,0x1F,0xDD,0x1D,0x1C,0xDC,0x14,0xD4,   
	0xD5,0x15,0xD7,0x17,0x16,0xD6,0xD2,0x12,0x13,0xD3,   
	0x11,0xD1,0xD0,0x10,0xF0,0x30,0x31,0xF1,0x33,0xF3,   
	0xF2,0x32,0x36,0xF6,0xF7,0x37,0xF5,0x35,0x34,0xF4,   
	0x3C,0xFC,0xFD,0x3D,0xFF,0x3F,0x3E,0xFE,0xFA,0x3A,   
	0x3B,0xFB,0x39,0xF9,0xF8,0x38,0x28,0xE8,0xE9,0x29,   
	0xEB,0x2B,0x2A,0xEA,0xEE,0x2E,0x2F,0xEF,0x2D,0xED,   
	0xEC,0x2C,0xE4,0x24,0x25,0xE5,0x27,0xE7,0xE6,0x26,   
	0x22,0xE2,0xE3,0x23,0xE1,0x21,0x20,0xE0,0xA0,0x60,   
	0x61,0xA1,0x63,0xA3,0xA2,0x62,0x66,0xA6,0xA7,0x67,   
	0xA5,0x65,0x64,0xA4,0x6C,0xAC,0xAD,0x6D,0xAF,0x6F,   
	0x6E,0xAE,0xAA,0x6A,0x6B,0xAB,0x69,0xA9,0xA8,0x68,   
	0x78,0xB8,0xB9,0x79,0xBB,0x7B,0x7A,0xBA,0xBE,0x7E,   
	0x7F,0xBF,0x7D,0xBD,0xBC,0x7C,0xB4,0x74,0x75,0xB5,   
	0x77,0xB7,0xB6,0x76,0x72,0xB2,0xB3,0x73,0xB1,0x71,   
	0x70,0xB0,0x50,0x90,0x91,0x51,0x93,0x53,0x52,0x92,   
	0x96,0x56,0x57,0x97,0x55,0x95,0x94,0x54,0x9C,0x5C,   
	0x5D,0x9D,0x5F,0x9F,0x9E,0x5E,0x5A,0x9A,0x9B,0x5B,   
	0x99,0x59,0x58,0x98,0x88,0x48,0x49,0x89,0x4B,0x8B,   
	0x8A,0x4A,0x4E,0x8E,0x8F,0x4F,0x8D,0x4D,0x4C,0x8C,   
	0x44,0x84,0x85,0x45,0x87,0x47,0x46,0x86,0x82,0x42,   
	0x43,0x83,0x41,0x81,0x80,0x40    
};


unsigned short int  
DataParser::CheckSum16(unsigned char* pData,long pLen)
{
	unsigned char uchCRCHi=0xFF ;   
	unsigned char uchCRCLo=0xFF ;   
	unsigned short uIndex ;   

	while( pLen-- )   
	{   
		uIndex   = uchCRCHi^*pData++;   
		uchCRCHi = uchCRCLo^szCRCHi[uIndex];   
		uchCRCLo = szCRCLo[uIndex];   
	}   
	return( uchCRCHi << 8 | uchCRCLo ); 
}


/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: model_package_buff_parser.h
* 文件描述: 模型数据包通讯传输协议解析实现类
*  作  者 : %刘毅%，
* 创建日期: 2018-5-15 14:58:24
*******************************************************************************/

#include "model_package_buff_parser.h"

#include "error_def.h"
#include "util.h"
#include "public_function_library.h"
#include <iostream>
#include <string.h>
using namespace std;

ModelPackageBuffParser::ModelPackageBuffParser(void)
:
DataParser(ModelPackage),
mLPointCount(0)
{
}

ModelPackageBuffParser::~ModelPackageBuffParser(void)
{
}

/*!
 * \function 私有点信息按文本方式打包
 * \param aPoints 点信息， strData 传出文本字符串
 * \return 打包结果
 * \brief 
 * \author liuyi
 * \date 2018/05/21
 */
bool ModelPackageBuffParser::PackPrivatePointDataToStr(PointDatas aPoints, string& strData)
{	
	for(unsigned long i = 0; i < aPoints.Count; ++i)
	{		
		if( aPoints.ID )
			strData += Util::Number2String<long>(aPoints.MPValues[i].ID) + SPLIT_CHAR;	//点ID

		if(aPoints.Name)
		{			
			strData += string(aPoints.MPValues[i].Name) + SPLIT_CHAR;	//点名			
		}

		if(aPoints.SetCode)
		{			
			strData += string(aPoints.MPValues[i].SetCode) + SPLIT_CHAR;	//机组号
		}
		
		strData += Util::Convert<char, string>(aPoints.MPValues[i].PointType) + SPLIT_CHAR;	//测点类型		
		strData += Util::Number2String(aPoints.MPValues[i].Value) + SPLIT_CHAR;	//点值		

		if(aPoints.State)
			strData += Util::Convert<char, string>(aPoints.MPValues[i].State) + SPLIT_CHAR;	//点的状态

		if(aPoints.Time)
			strData += PubOpt::SystemOpt::DateTmToStr(aPoints.MPValues[i].Time) + SPLIT_CHAR;	//时间戳

		if(ModelMeasurePoint == aPoints.MPValues[i].PointType)
		{
			strData += Util::Number2String(aPoints.MPValues[i].ExpectVal) + SPLIT_CHAR;	//模型期望值
			strData += Util::Number2String(aPoints.MPValues[i].HealthVal) + SPLIT_CHAR;	//模型健康度值
		}
	}
	return true;
}

/*!
 * \function 私有点信息按文本方式解包
 * \param aPoints 点信息， strSplits 文本字符串列表， i 列表迭代器
 * \return 解包结果
 * \brief 
 * \author liuyi
 * \date 2018/05/21
 */
bool ModelPackageBuffParser::UnpackPrivatePointDataFromStr(
	PointDatas* pPoints,
	vector<std::string> &strSplits,
	vector<std::string>::iterator &i)
{
	unsigned long nCount = 0;
	//while(i != strSplits.end() && nCount < pPoints->Count)
	while(true)
	{
		if( pPoints->ID )//点的ID
		{
			if(i == strSplits.end())
				break;
			else
			{
				pPoints->MPValues[nCount].ID = Util::Convert<string, long>(*i);
				++i;
			}
		}
		if(pPoints->Name)//点名
		{
			if(i == strSplits.end())
				break;
			else
			{
				strcpy(pPoints->MPValues[nCount].Name, i->c_str());
				++i;
			}
		}
		if(pPoints->SetCode)//点的机组号
		{
			if(i == strSplits.end())
				break;
			else
			{				
				strcpy(pPoints->MPValues[nCount].SetCode, i->c_str());				
				++i;
			}
		}

		if(i==strSplits.end())//测点类型
			break;
		else
		{
			pPoints->MPValues[nCount].PointType = Util::Convert<string,char>(*i);
			++i;
		}

		
		if(i==strSplits.end())//点值
			break;
		else
		{
			pPoints->MPValues[nCount].Value = Util::Convert<string,float>(*i);
			++i;
		}		
		
		if(pPoints->State)//点状态
		{
			if(i == strSplits.end())
				break;
			else
			{
				//pPoints->Points[nCount].State=(char)Util::Convert<string,short>(*i);
				pPoints->MPValues[nCount].State = Util::Convert<string,char>(*i);
				++i;
			}
		}
		if(pPoints->Time)//点时间戳
		{
			if(i == strSplits.end())
				break;
			else
			{
				pPoints->MPValues[nCount].Time = (long)PubOpt::SystemOpt::StrToDateTm(*i);
				++i;
			}
		}

		if (ModelMeasurePoint == pPoints->MPValues[nCount].PointType)
		{
			if(i == strSplits.end())	//期望值
				break;
			else
			{
				pPoints->MPValues[nCount].ExpectVal=Util::Convert<string,float>(*i);
				++i;
			}

			if(i == strSplits.end())	//健康度值
				break;
			else
			{
				pPoints->MPValues[nCount].HealthVal = Util::Convert<string,float>(*i);
				++i;
			}
		}
		
		++nCount;
		if (nCount >= pPoints->Count)
		{
			mStrError = IDS_ERROR_DATA;
			return false;
		}
		/*if(nCount == pPoints->Count)
		{
			if (i != strSplits.end())
			{
				mStrError = IDS_ERROR_DATA;
				return false;
			}
			else
			{
				break;
			}			
		}*/
	}
	pPoints->Count=nCount;
	return true;
}

/*!
 * \function 私有点信息按二进制方式打包
 * \param aPoints 点信息， pTem 传出字符串指针
 * \return 
 * \brief 
 * \author liuyi
 * \date 2018/05/21
 */
void ModelPackageBuffParser::PackPrivatePointData(PointDatas aPoints, char* &pTem)
{
	for(unsigned long i=0;i<aPoints.Count;++i)
	{
		//点的编号
		if(aPoints.ID)
		{
			memcpy(pTem,&aPoints.MPValues[i].ID,sizeof(aPoints.MPValues[i].ID));
			pTem+=PACK_POINT_NO_LEN;
		}
		//点的名称
		if(aPoints.Name)
		{
			memcpy(pTem,aPoints.MPValues[i].Name,PACK_MODEL_POINT_NAME_LEN);
			pTem+=PACK_MODEL_POINT_NAME_LEN;
		}
		//点的机组号
		if(aPoints.SetCode)
		{
			memcpy(pTem,aPoints.MPValues[i].SetCode,PACK_MODEL_SET_CODE_LEN);
			pTem+=PACK_MODEL_SET_CODE_LEN;
		}

		//测点类型
		*pTem=aPoints.MPValues[i].PointType;
		pTem+=PACK_MODEL_MEASURE_POINT_TYPE_LEN;

		//点值
		memcpy(pTem,&aPoints.MPValues[i].Value,sizeof(aPoints.MPValues[i].Value));
		pTem+=PACK_VALUE_LEN;

		//点状态
		if(aPoints.State)
		{
			*pTem=aPoints.MPValues[i].State;
			pTem+=PACK_STATE_LEN;
		}

		//时间戳
		if(aPoints.Time)
		{
			memcpy(pTem,&aPoints.MPValues[i].Time,sizeof(aPoints.MPValues[i].Time));
			pTem+=PACK_TIME_LEN;
		}

		if (ModelMeasurePoint == aPoints.MPValues[i].PointType)
		{
			memcpy(pTem,&aPoints.MPValues[i].ExpectVal,sizeof(aPoints.MPValues[i].ExpectVal));
			pTem+=PACK_MODEL_EXPECT_VALUE_LEN;

			memcpy(pTem,&aPoints.MPValues[i].HealthVal,sizeof(aPoints.MPValues[i].HealthVal));
			pTem+=PACK_MODEL_HEALTH_VALUE_LEN;
		}		
	}
}

/*!
 * \function 私有点信息按二进制方式解包
 * \param pPoints 点信息， pTem 二进制字符串， nPointCount 点数量
 * \return 解包结果
 * \brief 
 * \author liuyi
 * \date 2018/05/21
 */
bool ModelPackageBuffParser::UnpackPrivatePointData(const char* pTem, PointDatas* pPoints, long nPointCount)
{
	//获取点的数据
	long i=0;
	for(i=0;i<nPointCount;++i)
	{
		if((unsigned long) i>=pPoints->Count)
			break;
		//点的ID
		if(pPoints->ID)
		{
			pPoints->MPValues[i].ID=*(long*)pTem;
			pTem+=PACK_POINT_NO_LEN;
		}

		//点的名称
		if(pPoints->Name)
		{
			memcpy(pPoints->MPValues[i].Name,pTem,PACK_MODEL_POINT_NAME_LEN);
			pTem+=PACK_MODEL_POINT_NAME_LEN;
		}

		//点的机组号
		if(pPoints->SetCode)
		{
			memcpy(pPoints->MPValues[i].SetCode,pTem,PACK_MODEL_SET_CODE_LEN);
			pTem+=PACK_MODEL_SET_CODE_LEN;
		}

		//测点类型
		pPoints->MPValues[i].PointType=(char)(*pTem);
		pTem+=PACK_MODEL_MEASURE_POINT_TYPE_LEN;

		//点值
		pPoints->MPValues[i].Value=*(float*)pTem;
		pTem+=PACK_VALUE_LEN;

		//点的状态
		if(pPoints->State)
		{
			pPoints->MPValues[i].State=(char)(*pTem);
			pTem+=PACK_STATE_LEN;
		}
		
		//点的时间戳
		if(pPoints->Time)
		{
			pPoints->MPValues[i].Time=*(long*)pTem;
			pTem+=PACK_TIME_LEN;
		}

		if (ModelMeasurePoint == pPoints->MPValues[i].PointType)
		{
			pPoints->MPValues[i].ExpectVal=*(float*)pTem;		//期望值
			pTem+=PACK_MODEL_EXPECT_VALUE_LEN;

			pPoints->MPValues[i].HealthVal=*(float*)pTem;		//健康度值
			pTem+=PACK_MODEL_HEALTH_VALUE_LEN;
		}		
	}

	pPoints->Count=i;
	return true;
}

/*!
 * \function 创建私有点信息内存并初始化
 * \param pPoints 点信息， nPointCount 点数量
 * \return 
 * \brief 
 * \author liuyi
 * \date 2018/05/21
 */
void ModelPackageBuffParser::CreatePrivatePointValue(PointDatas* aPoints,unsigned long lPointCount)
{
	aPoints->Points = NULL;

	aPoints->MPValues = new ModelPackageValue[lPointCount];
	memset(aPoints->MPValues, 0, sizeof(ModelPackageValue) * lPointCount);

	mLPointCount = lPointCount;
}

/*!
 * \function 释放私有点信息内存
 * \param pPoints 点信息
 * \return 
 * \brief 
 * \author liuyi
 * \date 2018/05/21
 */
void ModelPackageBuffParser::DeletePointData(PointDatas* aPoints)
{
	if(aPoints->Points != NULL)
	{		
		delete[] aPoints->Points;
		aPoints->Points = NULL;
	}

	if (NULL != aPoints->MPValues)
	{
		delete []aPoints->MPValues;
		aPoints->MPValues = NULL;
	}
}

/*!
 * \function 获取数据类型
 * \param pData数据字符串， peDataType 传出数据类型指针
 * \return 获取结果
 * \brief 
 * \author liuyi
 * \date 2018/05/21
 */
bool ModelPackageBuffParser::GetPackDataType(const void* pData,PackDataType* peDataType)
{
	if(pData==NULL)
	{
		mStrError=IDS_NULL_POINT;
		return false;
	}
	char* pTem=(char*)const_cast<void*>(pData);

	//下移字节提取数据类型	
	pTem+=(PACK_NODE_NO_LEN+PACK_NO_LEN+PACK_TIME_LEN);	
	*peDataType=(PackDataType)(char)(*pTem);
	return true;
}

/*!
 * \function 获取文本类型数据长度
 * \param aPoints 点数据信息， pLen 传出长度指针
 * \return 获取结果
 * \brief 
 * \author liuyi
 * \date 2018/05/21
 */
bool ModelPackageBuffParser::GetPointPackTxtLen(PointDatas aPoints,long* pLen)
{
	if(pLen==NULL)
	{
		mStrError=IDS_NULL_POINT;
		return false;
	}
	int nHeardLen=PACK_NODE_NO_TXT_LEN;
	nHeardLen+=PACK_NO_TXT_LEN;
	nHeardLen+=PACK_DATA_COUNT_TXT_LEN;
	nHeardLen+=PACK_TIME_TXT_LEN;
	nHeardLen+=PACK_DC_NO_TXT_LEN;
	nHeardLen+=PACK_BOOL_TXT_LEN*5;

	int nPointLen=0;

	for (unsigned long i = 0 ; i < aPoints.Count; i++)
	{
		if(aPoints.ID)
			nPointLen+=PACK_POINT_NO_TXT_LEN;
		if(aPoints.Name)
			nPointLen+=PACK_MODEL_POINT_NAME_TXT_LEN;
		if(aPoints.SetCode)
			nPointLen+=PACK_MODEL_SET_CODE_TXT_LEN;
		nPointLen+=PACK_MODEL_MEASURE_POINT_TYPE_TXT_LEN;
		nPointLen+=PACK_VALUE_TXT_LEN;
		if(aPoints.State)
			nPointLen+=PACK_STATE_TXT_LEN;
		if(aPoints.Time)
			nPointLen+=PACK_TIME_TXT_LEN;

		if (ModelMeasurePoint == aPoints.MPValues[i].PointType)
		{
			nPointLen+=PACK_MODEL_EXPECT_VALUE_TXT_LEN;
			nPointLen+=PACK_MODEL_HEALTH_VALUE_TXT_LEN;
		}
	}	

	*pLen=nHeardLen+nPointLen;
	return true;
}

/*!
 * \function 获取二进制类型数据长度
 * \param aPoints 点数据信息， pLen 传出长度指针
 * \return 获取结果
 * \brief 
 * \author liuyi
 * \date 2018/05/21
 */
bool ModelPackageBuffParser::GetPointDataLen(PointDatas aPoints,long* pLen)
{
	if(pLen==NULL)
	{
		mStrError=IDS_NULL_POINT;
		return false;
	}
	int nLen=PACK_CONTROL_LEN+PACK_DATA_COUNT_LEN;

	int nPointLen=0;
	for (unsigned long i = 0 ; i < aPoints.Count; i++)
	{
		if(aPoints.ID)
			nPointLen+=PACK_POINT_NO_LEN;
		if(aPoints.Name)
			nPointLen+=PACK_MODEL_POINT_NAME_LEN;
		if(aPoints.SetCode)
			nPointLen+=PACK_MODEL_SET_CODE_LEN;
		nPointLen+=PACK_MODEL_MEASURE_POINT_TYPE_LEN;
		nPointLen+=PACK_VALUE_LEN;
		if(aPoints.State)
			nPointLen+=PACK_STATE_LEN;
		if(aPoints.Time)
			nPointLen+=PACK_TIME_LEN;

		if (ModelMeasurePoint == aPoints.MPValues[i].PointType)
		{
			nPointLen+=PACK_MODEL_EXPECT_VALUE_LEN;
			nPointLen+=PACK_MODEL_HEALTH_VALUE_LEN;
		}
	}
	*pLen=nLen+nPointLen;
	return true;
}

/*!
 * \function 获取文本类型数据包总长度
 * \param aPoints 点数据信息， pLen 传出长度指针
 * \return 获取结果
 * \brief 
 * \author liuyi
 * \date 2018/05/21
 */
bool ModelPackageBuffParser::GetPointPackLen(PointDatas aPoints,long* pLen)
{
	if(pLen==NULL)
	{
		mStrError=IDS_NULL_POINT;
		return false;
	}
	int nLen= PACK_NODE_NO_LEN+PACK_NO_LEN+PACK_TIME_LEN+PACK_DATA_TYPE_LEN+PACK_DC_NO_LEN+PACK_DATA_LEN_LEN+
		PACK_CONTROL_LEN+PACK_DATA_COUNT_LEN+PACK_CHECK_SUM_LEN ;
	int nPointLen=0;
	for (unsigned long i = 0 ; i < aPoints.Count; i++)
	{
		if(aPoints.ID)
			nPointLen+=PACK_POINT_NO_LEN;
		if(aPoints.Name)
			nPointLen+=PACK_MODEL_POINT_NAME_LEN;
		if(aPoints.SetCode)
			nPointLen+=PACK_MODEL_SET_CODE_LEN;
		nPointLen+=PACK_MODEL_MEASURE_POINT_TYPE_LEN;
		nPointLen+=PACK_VALUE_LEN;
		if(aPoints.State)
			nPointLen+=PACK_STATE_LEN;
		if(aPoints.Time)
			nPointLen+=PACK_TIME_LEN;

		if (ModelMeasurePoint == aPoints.MPValues[i].PointType)
		{
			nPointLen+=PACK_MODEL_EXPECT_VALUE_LEN;
			nPointLen+=PACK_MODEL_HEALTH_VALUE_LEN;
		}
	}
	*pLen=nLen+nPointLen;
	return true;
}

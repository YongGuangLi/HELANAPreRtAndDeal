/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: PPubPointValue.cpp
* 文件描述: 存储耗差实时点实时值
*  作  者 : %林晓雨%，
* 创建日期: 2015-7-27 11:54:21
*******************************************************************************/

#include "PPubPointValue.h"
#include "RsdbAdapter.h"
#include "public_function_library.h"
#include "Util.h"
#include "StartupServer.h"
#include <iostream>

PPubPointValue::PPubPointValue()
: 
RDbOperationComplex()
{
 	/*mPointIdPtr = (char **) mPointId;
	mUpdateDatePtr = (char **) mUpdateDate;

	mSimValue = new double[ROW_COUNT];*/
}

PPubPointValue::~PPubPointValue(void)
{
   /* if (NULL != mPointIdPtr) mPointIdPtr = NULL;
    if (NULL != mUpdateDatePtr) mUpdateDatePtr = NULL;

    if (NULL != mSimValue)
    {
        delete[] mSimValue;
        mSimValue = NULL;
    }*/

}

bool PPubPointValue::ExecPPubPointValue(const long &lCalTimeStamp, MapStringToDataMode &mMapModeInfo)
{
	Aos_Assert_R(Util::QtConnect(mQtOpt), false);
   
	// 绑定执行存储过程
	Aos_Assert_R(stmtPrepare(PPOINT_VALUE, g_strSavePointValueSQL), false);

	 // 绑定存储过程输入/输出变量
	//Aos_Assert_R(BindPPubPointValue(), false);

	int iNumOci = 0;				 
	std::string pointId, strTime;
	DataMode *  data_value_info;
	MapStringToDataMode_It itr = mMapModeInfo.begin();
	for(;itr != mMapModeInfo.end(); ++itr)
	{
		data_value_info = itr->second;
		if (!data_value_info->m_IsDeal &&!data_value_info->mRtdbSimModleIsWrite) continue;
		
		pointId  = data_value_info->mSimSource;
		if (pointId.empty())
		{
			Aos_Assert_S("模型健康度回写编号有误!");
			continue;
		}

		strTime = PubOpt::SystemOpt::DateTmToStr(lCalTimeStamp,0);
		//strcpy(mPointId[iNumOci], pointId.c_str());
		//strcpy(mUpdateDate[iNumOci], strTime.c_str());
		
		double vv = data_value_info->mDModeSim;
		//memcpy(&mSimValue[iNumOci], &vv,sizeof(double));

		iNumOci ++;
//		if (!mQtOpt->BindOutputByName(strTime))
//		{
//			mStrErrorMessage = PubOpt::StringOpt::StringFormat("Bind PPubPointValue 1 \
//															   UpdateTimeC SQL ERROR: %s",
//															   mQtOpt->GetErrorMessage().c_str());
//			Aos_Assert_S(mStrErrorMessage.c_str());
//			return false;
//		}

//		if (!mQtOpt->BindOutputByName(vv))
//		{
//			mStrErrorMessage = PubOpt::StringOpt::StringFormat("Bind PPubPointValue 2 \
//															   CurrentValue SQL ERROR: %s",
//															   mQtOpt->GetErrorMessage().c_str());
//			Aos_Assert_S(mStrErrorMessage.c_str());
//			return false;
//		}

//		if (!mQtOpt->BindOutputByName(pointId))
//		{
//			mStrErrorMessage = PubOpt::StringOpt::StringFormat("Bind PPubPointValue 3 \
//															   AlarmInfo SQL ERROR: %s",
//															   mQtOpt->GetErrorMessage().c_str());
//			Aos_Assert_S(mStrErrorMessage.c_str());
//			return false;
//		}

	    if (iNumOci == ROW_COUNT)
		{
			Aos_Assert_R(stmtTransCommit(PPOINT_VALUE), false);
			iNumOci = 0;
		}
	}

	if (iNumOci != 0)
	{
		Aos_Assert_R(stmtTransCommit(PPOINT_VALUE), false);
	}
	stmtCloseStream(); 
    return true;
}

//bool PPubPointValue::BindPPubPointValue()
//{
//	if (!mQtOpt->BindOutputByName(mUpdateDatePtr))
//	{
//		mStrErrorMessage = PubOpt::StringOpt::StringFormat("Bind PPubPointValue 1 \
//															UpdateTimeC SQL ERROR: %s",
//															mQtOpt->GetErrorMessage().c_str());
//		Aos_Assert_S(mStrErrorMessage.c_str());
//		return false;
//	}
//
//	if (!mQtOpt->BindOutputByName(mSimValue))
//	{
//		mStrErrorMessage = PubOpt::StringOpt::StringFormat("Bind PPubPointValue 2 \
//														   CurrentValue SQL ERROR: %s",
//														   mQtOpt->GetErrorMessage().c_str());
//		Aos_Assert_S(mStrErrorMessage.c_str());
//		return false;
//	}
//
//	if (!mQtOpt->BindOutputByName(mPointIdPtr))
//	{
//		mStrErrorMessage = PubOpt::StringOpt::StringFormat("Bind PPubPointValue 3 \
//														   AlarmInfo SQL ERROR: %s",
//														   mQtOpt->GetErrorMessage().c_str());
//		Aos_Assert_S(mStrErrorMessage.c_str());
//		return false;
//	}
//
//    return true;
//}
//
//

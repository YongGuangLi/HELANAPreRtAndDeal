/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: RDbOperationSimple.cpp
* 文件描述: 关系数据库简单操作实现类
*  作  者 : %WK%，
* 创建日期: 2015-5-28 9:41:18
*******************************************************************************/

#include "RDbOperationSimple.h"
#include "Util.h"
#include "public_function_library.h"
#include "ErrorDef.h"
#include "RDbOperationComplex.h"
#include "StartupServer.h"
#include "TypeDef.h"

RDbOperationSimple::RDbOperationSimple(void)
{
	mQtOpt = NULL;
}
RDbOperationSimple::RDbOperationSimple(RsdbAdapter * QtOpt)
:mQtOpt(QtOpt)
{

}
RDbOperationSimple::~RDbOperationSimple(void)
{
}


//bool 
//RDbOperationSimple::getDbmsCurrentTime(std::string &current_time)
//{
//	if (!mQtOpt->QtIsConnect()) return false;
//	
//	int nErr = SINGLETON(OciAdapter)->SQLStmtPrepare(g_strGetDBDateTimeSQL);// 绑定查询SQL语句
//	if (0 != nErr)
//	{
//		mStrErrorMessage = PubOpt::StringOpt::StringFormat("Prepare CurrentTime SQL ERROR: %s", 
//				SINGLETON(OciAdapter)->GetErrorMessage().c_str());
//		Aos_WriteLog(mStrErrorMessage.c_str());
//		return false;
//	}
//
//	char * pszOutputBuff = new char[ALL_VALUE_SIZE];
//	if (!SINGLETON(OciAdapter)->BindOutputStrByPos(0, pszOutputBuff, ALL_VALUE_SIZE))
//	{
//		mStrErrorMessage = PubOpt::StringOpt::StringFormat(
//				"Bind PubSet Variables %d ERROR: ",
//				1, SINGLETON(OciAdapter)->GetErrorMessage().c_str());
//		Aos_WriteLog(mStrErrorMessage.c_str());
//		return false;
//	}
//
//	nErr = SINGLETON(OciAdapter)->SQLStmtExecute();
//	if (0 != nErr)                                                  // 执行查询SQL语句
//	{
//		mStrErrorMessage = PubOpt::StringOpt::StringFormat("Execute CurrentTime SQL ERROR: %s", 
//				SINGLETON(OciAdapter)->GetErrorMessage().c_str());
//		Aos_WriteLog(mStrErrorMessage.c_str());
//		delete[] pszOutputBuff;
//		return false;
//	}
//
//	if (FETCH_NO_DATA == SINGLETON(OciAdapter)->SQLStmtFetch())
//	{
//		delete[] pszOutputBuff;
//		return false;
//	}
//	current_time = pszOutputBuff;
//	delete[] pszOutputBuff;
//	return true;
//}
//
//

bool 
RDbOperationSimple::stmtPrepare(const std::string &classname, const std::string &str_sql)
{
	bool nErr = mQtOpt->QtQuerySelect(str_sql);// 绑定查询SQL语句
	if (!nErr)
	{
		Aos_Assert_S(PubOpt::StringOpt::StringFormat("Prepare %s SQL ERROR: %s", 
			classname.c_str(), mQtOpt->GetErrorMessage().c_str()).c_str());
		return false;
	}	
	return true;
}

void
RDbOperationSimple::stmtCloseStream()
{
	mQtOpt->SQLStmtCloseStream();
}

bool 
RDbOperationSimple::getFactoryNo(std::string strFactoryCode,unsigned short &DcNum)
{	
	std::string strCode;
	//int DNumber = 0;
	//bool nErr;
	//if (!mQtOpt->QtIsConnect()) return false;
	Aos_Assert_R(Util::QtConnect(mQtOpt), false);
	std::string strSQL =  PubOpt::StringOpt::StringFormat(g_strFactoryNoSQL.c_str(),strFactoryCode.c_str());
	Aos_Assert_R(stmtPrepare("getIndexConfigStatus",strSQL), false);
	int nNumber = 0;
	while (mQtOpt->SQLStmtFetch())
	{
		nNumber++;
		strCode = std::string(mQtOpt->m_query->value(0).toString().toLocal8Bit());

	}
	stmtCloseStream();  
	
	DcNum = (strCode.empty())?0:Util::CharPointerConvert2Number<int>(strCode.c_str());

	return true;
}
bool 
RDbOperationSimple::getIndexConfigStatus(std::string strFactoryCode)
{	
	std::string strCode;
	//bool nErr;
	//if (!mQtOpt->QtIsConnect()) return false;
	Aos_Assert_R(Util::QtConnect(mQtOpt,strFactoryCode), false);
	std::string strSQL =  PubOpt::StringOpt::StringFormat(g_strSysStatusSQL.c_str(),strFactoryCode.c_str());
	Aos_Assert_R(stmtPrepare("getIndexConfigStatus",strSQL), false);
	//Aos_Assert_R(stmtPrepare("getIndexConfigStatus", g_strSysStatusSQL), false);
	int nNumber = 0;
	while (mQtOpt->SQLStmtFetch())
	{
		nNumber++;
		strCode = std::string(mQtOpt->m_query->value(0).toString().toLocal8Bit());

	}
	stmtCloseStream();  
	bool is_update = Util::CharPointerConvert2Number<int>(strCode.c_str()) != 0?true:false;
	
	return is_update;
}

bool 
RDbOperationSimple::getIndexUpdataTime(std::string strFactoryCode,long &calTime)
{	
	std::string strTime;
	//bool nErr;
	//if (!mQtOpt->QtIsConnect()) return false;
	Aos_Assert_R(Util::QtConnect(mQtOpt), false);
	std::string strSQL =  PubOpt::StringOpt::StringFormat(g_strSysCalTimeSQL.c_str(),strFactoryCode.c_str());
	Aos_Assert_R(stmtPrepare("getIndexConfigStatus",strSQL), false);
	//Aos_Assert_R(stmtPrepare("getIndexConfigStatus", g_strSysStatusSQL), false);
	int nNumber = 0;
	while (mQtOpt->SQLStmtFetch())
	{
		nNumber++;
		strTime = std::string(mQtOpt->m_query->value(0).toString().toLocal8Bit());

	}
	stmtCloseStream();  
	calTime = PubOpt::SystemOpt::StrToDateTm(strTime);

	return true;
}
bool 
RDbOperationSimple::UpdataCalTime(std::string strFactoryCode,std::string strcalTime,const int itype)
{	
	//std::string strTime ="2018-5-29 12:12:28";
	//strcalTime = strTime;
	//bool nErr;
	if(strcalTime.empty()) return true;
	if (!mQtOpt->QtIsConnect()) return false;
	//calTime = PubOpt::SystemOpt::StrToDateTm(strTime);
	std::string strSQL =  PubOpt::StringOpt::StringFormat(g_strUpdateSysCalTimeSQL.c_str(),strcalTime.c_str(),itype,strFactoryCode.c_str());
	Aos_Assert_R(stmtPrepare("getIndexConfigStatus",strSQL), false);
	//Aos_Assert_R(stmtPrepare("getIndexConfigStatus", g_strSysStatusSQL), false);
	bool rslt = mQtOpt->QtExec();
	rslt = mQtOpt->QtCommit();
	stmtCloseStream();  
	
	return rslt;
}





bool 
RDbOperationSimple::updateIndexConfigStatus(const int &status,std::string strFactory)
{
	bool err;
	if (!mQtOpt->QtIsConnect()) return false;
	
	std::string strSql = PubOpt::StringOpt::StringFormat(g_strUpdateStatusSQL.c_str(), status,strFactory.c_str());
	Aos_WriteLog(strSql.c_str());
	err = mQtOpt->SQLDirectExecute(strSql);
	return err;
}



//bool 
//RDbOperationSimple::updatePointValueByStable(const long &lCalTimeStamp, MapStringToPubSetInfo &pMapPubSetInfo)
//{
//	if (!mQtOpt->QtIsConnect()) return false;
//
//	int nErr = 0;
//	int status = 1;
//	std::string strTime = PubOpt::SystemOpt::DateTmToStr(lCalTimeStamp);
//	MapStringToPubSetInfo_It p_itr = pMapPubSetInfo.begin();
//	for(; p_itr != pMapPubSetInfo.end(); ++p_itr)
//	{
//		if (p_itr->second->mPointId.empty()) 
//		{
//			Aos_WriteLog_D(PubOpt::StringOpt::StringFormat(HCXNJS_ERROR_STEADY, 
//				p_itr->second->mSetCode.c_str()).c_str());
//			//Aos_Assert_S(PubOpt::StringOpt::StringFormat(HCXNJS_ERROR_STEADY, 
//			//	p_itr->second->mSetCode.c_str()).c_str());
//			continue;
//		}
//
//		nErr = SINGLETON(OciAdapter)->SQLStmtPrepare(g_strSavePointValueSQL);// 绑定查询SQL语句
//		if (0 != nErr)
//		{
//			Aos_Assert_S(PubOpt::StringOpt::StringFormat("updatePointValueByStable SQL ERROR: %s", 
//				SINGLETON(OciAdapter)->GetErrorMessage().c_str()).c_str());
//			return false;
//		}
//
//		if (!SINGLETON(OciAdapter)->BindInputStrByPos(0, strTime))
//		{
//			mStrErrorMessage = PubOpt::StringOpt::StringFormat("Bind updatePointValueByStable 1 \
//															FullIndexCode SQL ERROR: %s",
//															SINGLETON(OciAdapter)->GetErrorMessage().c_str());
//			SINGLETON(Log)->WriteLog(mStrErrorMessage.c_str());
//			return false;
//		}
//
//		 double vv = p_itr->second->mIsStable;
//		if (!SINGLETON(OciAdapter)->BindInputDoubleByPos(1, vv))
//		{
//			mStrErrorMessage = PubOpt::StringOpt::StringFormat("Bind updatePointValueByStable 2 \
//																FStandValue SQL ERROR: %s",
//																SINGLETON(OciAdapter)->GetErrorMessage().c_str());
//			SINGLETON(Log)->WriteLog(mStrErrorMessage.c_str());
//			return false;
//		}
//
//		if (!SINGLETON(OciAdapter)->BindInputDoubleByPos(2, vv))
//		{
//			mStrErrorMessage = PubOpt::StringOpt::StringFormat("Bind updatePointValueByStable 3 \
//															FStandValue SQL ERROR: %s",
//															SINGLETON(OciAdapter)->GetErrorMessage().c_str());
//			SINGLETON(Log)->WriteLog(mStrErrorMessage.c_str());
//			return false;
//		}
//
//		if (!SINGLETON(OciAdapter)->BindInputIntByPos(3, status))
//		{
//			mStrErrorMessage = PubOpt::StringOpt::StringFormat("Bind updatePointValueByStable 4 \
//																AlarmLevel SQL ERROR: %s",
//																SINGLETON(OciAdapter)->GetErrorMessage().c_str());
//			SINGLETON(Log)->WriteLog(mStrErrorMessage.c_str());
//			return false;
//		}
//
//		if (!SINGLETON(OciAdapter)->BindInputStrByPos(4, p_itr->second->mPointId))
//		{
//			mStrErrorMessage = PubOpt::StringOpt::StringFormat("Bind updatePointValueByStable 5 \
//															FullIndexCode SQL ERROR: %s",
//															SINGLETON(OciAdapter)->GetErrorMessage().c_str());
//			SINGLETON(Log)->WriteLog(mStrErrorMessage.c_str());
//			return false;
//		}
//
//		nErr = SINGLETON(OciAdapter)->SQLStmtExecute();
//		if (0 != nErr)                                                  // 执行查询SQL语句
//		{
//			Aos_Assert_S(PubOpt::StringOpt::StringFormat("Execute updatePointValueByStable SQL ERROR: %s", 
//				SINGLETON(OciAdapter)->GetErrorMessage().c_str()).c_str());
//			return false;
//		}
//	}
//
//	nErr = SINGLETON(OciAdapter)->SQLTransCommit();
//	if (0 != nErr) 
//	{
//		Aos_Assert_S(PubOpt::StringOpt::StringFormat("Commit updatePointValueByStable SQL ERROR: %s", 
//			SINGLETON(OciAdapter)->GetErrorMessage().c_str()).c_str());
//		return false;
//	}
//	return true;
//}
//
//

//测试组临时表									
//bool 
//RDbOperationSimple::insertAnalyseDataTemp(const long &lCalTimeStamp, MapStringToDataValueInfo &pMapDataValueInfo)
//{
//	if (!mQtOpt->QtIsConnect()) return false;
//	
//	int nErr = 0;
//	int status = 1;
//	bool isFound = false;
//	DataValueInfo * data_value_info = NULL;
//	std::string strTime = PubOpt::SystemOpt::DateTmToStr(lCalTimeStamp);
//	MapStringToDataValueInfo_It itr = pMapDataValueInfo.begin();
//	for(; itr != pMapDataValueInfo.end(); ++itr)
//	{
//		data_value_info = itr->second;
//		
//		if (!isSaveTemp(data_value_info->mStrCode, data_value_info->mSetCode)) continue;
//
//		isFound = true;
//		nErr = SINGLETON(OciAdapter)->SQLStmtPrepare(g_strAnalyseDataTempSQL);// 绑定查询SQL语句
//		if (0 != nErr)
//		{
//			Aos_Assert_S(PubOpt::StringOpt::StringFormat("insertAnalyseDataTemp SQL ERROR: %s", 
//				SINGLETON(OciAdapter)->GetErrorMessage().c_str()).c_str());
//			return false;
//		}
//
//		if (!SINGLETON(OciAdapter)->BindInputStrByPos(0, strTime))
//		{
//			mStrErrorMessage = PubOpt::StringOpt::StringFormat("Bind insertAnalyseDataTemp 1 \
//															   FullIndexCode SQL ERROR: %s",
//															   SINGLETON(OciAdapter)->GetErrorMessage().c_str());
//			SINGLETON(Log)->WriteLog(mStrErrorMessage.c_str());
//			return false;
//		}
//
//		std::string strSetCode = data_value_info->mSetCode;
//		if (strSetCode.empty())
//		{
//			strSetCode = data_value_info->mStrCode.substr(1,1);
//		}
//
//		if (!SINGLETON(OciAdapter)->BindInputStrByPos(1, strSetCode))
//		{
//			mStrErrorMessage = PubOpt::StringOpt::StringFormat("Bind insertAnalyseDataTemp 2 \
//															   FullIndexCode SQL ERROR: %s",
//															   SINGLETON(OciAdapter)->GetErrorMessage().c_str());
//			SINGLETON(Log)->WriteLog(mStrErrorMessage.c_str());
//			return false;
//		}
//
//		if (!SINGLETON(OciAdapter)->BindInputStrByPos(2, data_value_info->mStrCode))
//		{
//			mStrErrorMessage = PubOpt::StringOpt::StringFormat("Bind insertAnalyseDataTemp 3 \
//															   FullIndexCode SQL ERROR: %s",
//															   SINGLETON(OciAdapter)->GetErrorMessage().c_str());
//			SINGLETON(Log)->WriteLog(mStrErrorMessage.c_str());
//			return false;
//		}
//
//		double vv = data_value_info->getCurrVar(StartupServer::smIsStartDelay);
//		if (!SINGLETON(OciAdapter)->BindInputDoubleByPos(3, vv))
//		{
//			mStrErrorMessage = PubOpt::StringOpt::StringFormat("Bind insertAnalyseDataTemp 4 \
//															   FullIndexCode SQL ERROR: %s",
//															   SINGLETON(OciAdapter)->GetErrorMessage().c_str());
//			SINGLETON(Log)->WriteLog(mStrErrorMessage.c_str());
//			return false;
//		}
//
//		nErr = SINGLETON(OciAdapter)->SQLStmtExecute();
//		if (0 != nErr)                                                  // 执行查询SQL语句
//		{
//			Aos_Assert_S(PubOpt::StringOpt::StringFormat("Execute insertAnalyseDataTemp SQL ERROR: %s", 
//				SINGLETON(OciAdapter)->GetErrorMessage().c_str()).c_str());
//			return false;
//		}
//	}
//	if (!isFound) return true;
//	nErr = SINGLETON(OciAdapter)->SQLTransCommit();
//	if (0 != nErr) 
//	{
//		Aos_Assert_S(PubOpt::StringOpt::StringFormat("Commit insertAnalyseDataTemp SQL ERROR: %s", 
//			SINGLETON(OciAdapter)->GetErrorMessage().c_str()).c_str());
//		return false;
//	}
//	return true;
//}
//

bool
RDbOperationSimple::isSaveTemp(const std::string pointId, const std::string setCode)
{
	if (pointId.substr(0,1) == "M")
	{
		std::string strSetCode = setCode;
		if (strSetCode.empty())
		{
			strSetCode = pointId.substr(1,1);
		}

		if (strSetCode == "0")
		{
			if (pointId == "M0_zzqyl")    return true;
			if (pointId == "M0_dqyl")    return true;
			if (pointId == "M0_zfl")    return true;
			if (pointId == "M0_fdl")    return true;
			if (pointId == "M0_fhl")    return true;
			if (pointId == "M0_FH")    return true;
		}

		if (strSetCode == "1")
		{
			if (pointId == "M1_zzqyl")    return true;
			if (pointId == "M1_dqyl")    return true;
			if (pointId == "M1_zfl")    return true;
			if (pointId == "M1_fdl")    return true;
			if (pointId == "M1_fhl")    return true;
			if (pointId == "M1_FH")    return true;
		}
		if (strSetCode == "2")
		{
			if (pointId == "M2_zzqyl")    return true;
			if (pointId == "M2_dqyl")    return true;
			if (pointId == "M2_zfl")    return true;
			if (pointId == "M2_fdl")    return true;
			if (pointId == "M2_fhl")    return true;
			if (pointId == "M2_FH")    return true;
		}

		if (strSetCode == "3")
		{
			if (pointId == "M3_zzqyl")    return true;
			if (pointId == "M3_dqyl")    return true;
			if (pointId == "M3_zfl")    return true;
			if (pointId == "M3_fdl")    return true;
			if (pointId == "M3_fhl")    return true;
			if (pointId == "M3_FH")    return true;
		}

		if (strSetCode == "4")
		{
			if (pointId == "M4_zzqyl")    return true;
			if (pointId == "M4_dqyl")    return true;
			if (pointId == "M4_zfl")    return true;
			if (pointId == "M4_fdl")    return true;
			if (pointId == "M4_fhl")    return true;
			if (pointId == "M4_FH")    return true;
		}
	}
	if (pointId.substr(0,1) == "D")
	{
		if (setCode == "0")
		{
			if (pointId == "D0_dqyl")		return true;
			if (pointId == "D0_gsll")		return true;
			if (pointId == "D0_fdjyggl")    return true;
			if (pointId == "D0_zzqll")		return true;
			if (pointId == "D0_zzqyl")		return true;
			if (pointId == "D0_glzgswd")	return true;
			if (pointId == "D0_zrzqrkwd")   return true;
			if (pointId == "D0_zzqwdL")		return true;
		}

		if (setCode == "1")
		{
			if (pointId == "D1_dqyl")		return true;
			if (pointId == "D1_gsll")		return true;
			if (pointId == "D1_fdjyggl")    return true;
			if (pointId == "D1_zzqll")		return true;
			if (pointId == "D1_zzqyl")		return true;
			if (pointId == "D1_glzgswd")	return true;
			if (pointId == "D1_zrzqrkwd")   return true;
			if (pointId == "D1_zzqwdL")		return true;
		}
		if (setCode == "2")
		{
			if (pointId == "D2_dqyl")		return true;
			if (pointId == "D2_gsll")		return true;
			if (pointId == "D2_fdjyggl")    return true;
			if (pointId == "D2_zzqll")		return true;
			if (pointId == "D2_zzqyl")		return true;
			if (pointId == "D2_glzgswd")	return true;
			if (pointId == "D2_zrzqrkwd")   return true;
			if (pointId == "D2_zzqwdL")		return true;
		}

		if (setCode == "3")
		{
			if (pointId == "D3_dqyl")		return true;
			if (pointId == "D3_gsll")		return true;
			if (pointId == "D3_fdjyggl")    return true;
			if (pointId == "D3_zzqll")		return true;
			if (pointId == "D3_zzqyl")		return true;
			if (pointId == "D3_glzgswd")	return true;
			if (pointId == "D3_zrzqrkwd")   return true;
			if (pointId == "D3_zzqwdL")		return true;
		}

		if (setCode == "4")
		{
			if (pointId == "D4_dqyl")		return true;
			if (pointId == "D4_gsll")		return true;
			if (pointId == "D4_fdjyggl")    return true;
			if (pointId == "D4_zzqll")		return true;
			if (pointId == "D4_zzqyl")		return true;
			if (pointId == "D4_glzgswd")	return true;
			if (pointId == "D4_zrzqrkwd")   return true;
			if (pointId == "D4_zzqwdL")		return true;
		}
	}
	return false;
}

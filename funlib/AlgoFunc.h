#ifndef __ALGOFUNC_H__
#define __ALGOFUNC_H__

#include "AlgoVarDef.h"
//#define IMPORT_TYPE
//#ifdef WIN32
//#ifndef IMPORT_TYPE
//#define IMPORT_TYPE extern "C" __declspec(dllexport)
//#endif
//#else
//#ifndef IMPORT_TYPE
//#define IMPORT_TYPE extern "C"
//#endif
//#endif


// 功能描述: 训练样本调用训练样本(Kmean算法、GMM-EM算法、相似度算法)
/*******************************************************************************
* 函 数 名: TRAINSAMPLEDeal
* 函数描述: 训练样本
* 参数说明: 
*    入 参: const vector<DTRow> rcData 历史样本集合	 DTRow rMa 最大值绝对值+最小绝对值的乘以0.5
*    出 参: TrainSampleResult &result 集合
* 返 回 值:
*    成 功:
*    失 败:	
*  作  者 : 
* 创建日期: 2016-1-5 16:44:32
*******************************************************************************/

 bool TRAINSAMPLEDeal(unsigned short rM,
								 DTRows &rData, 
								 const DTRow &rMa, 
								 TrainSampleResult &lTrainSampleRslt);

// 功能描述: 实时调用相似度算法
/*******************************************************************************
* 函 数 名: SIMROWDeal
* 函数描述: 相似度算法
* 参数说明: 
*    入 参: const vector<double> rcData 一组测点数据,const vector<DTRow> muData 期望值集合
*    出 参: double & msim 样本相似度 std::vector<double> &pm 测点相似度集合 std::vector<double> &mt 一组测点期望值 int &num 噪声比
           std::string &err 异常信息
* 返 回 值:
*    成 功:
*    失 败:	
*  作  者 : 王凯，15802613961
* 创建日期: 2016-1-5 16:44:32
*******************************************************************************/
bool SIMROWDeal(const DTRow &rData,
							const DTRows &GData,
							const DTRow &maData,
							const DTRows &muData,
                            double & msim,DTRow &pm,
							DTRow &mt,std::string &err);


bool SIMROWDealEx(DTRowParam rData,
							const DTRows &GData,
							const DTRow &maData,
							const DTRows &muData,
							double & msim,DTRow &pm,
							DTRow &mt,std::string &err);
                           
#endif
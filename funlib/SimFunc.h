#ifndef __SIMFUNC_H__
#define __SIMFUNC_H__

#include "AlgoVarDef.h"
#include "PublicMatrix.h"

class SimFunc
{
public:
	unsigned int			mNSampleNum;		// 样本数目
	unsigned int			mDPointNum;			// 测点个数
	PublicMatrixPtr			mMu;				// 均值	  行:测点个数,列噪音级别
	//PublicMatrixPtr			mData;				// 样本数据 行:样本数据组的个数,列:测点个数
	PublicMatrixPtr			mG;
	PublicMatrixPtr			GW;
	PublicMatrixPtr			GA;
	PublicMatrixPtr			transDataDN;
	PublicMatrixPtr			EstData;
	std::string				mStrErrorMessage;
	SimFunc();
	~SimFunc();
	SimFunc(const unsigned int n, const unsigned int d);

	bool calEstValue(const DTRow &rData,const DTRows &rMuData,const DTRows &rGData,DTRow &mt);
	bool calEstValue(const DTRow &rData,const DTRows &rMuData,const DTRow &rMaData,const DTRows &rGData,
		DTRow &mt,double & msim,std::vector<double> &pm);

	bool calEstValue(const DTRowParam &rData,const DTRows &rMuData,
					const DTRow &rMaData,const DTRows &rGData,DTRow &mt,
					double & msim,std::vector<double> &pm);//add 发电能力功能扩展
//private:
	bool setMerry(const DTRows &vectorDataMu,const DTRows &vectorDataG);
	bool setData(const DTRows &vectorDataMu,const DTRows &vectorDataG);
	//void getData(DTRows &rGData);

	// 功能描述: 历史调用相似度算法
	/*******************************************************************************
	* 函 数 名: SIMDeal
	* 函数描述: 历史调用相似度算法
	* 参数说明: 
	*    入 参: const vector<DTRow> rcData 历史样本集合 const vector<DTRow> muData 期望值集合
	*    出 参: double &minSim 相似度限值 double &maxSim样本数据相似度最大值 double &avSim样本数据相似度平均值
 				DTRow &vSim样本相似度集合 DTRows &vpm样本测点相似度集合 DTRows &vmt样本期望值集合
	* 返 回 值:
	*    成 功:
	*    失 败:	
	*  作  者 : 王凯，15802613961
	* 创建日期: 2016-1-6 15:03:34
	*******************************************************************************/

	 bool SIMDeal(const DTRows &rcData,const DTRows &GData,const DTRow &maData,const DTRows &muData,double &minSim,double &maxSim,double &avSim,DTRow &vSim,DTRows &vpm,DTRows &vmt,std::string &err);
		//
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
	 bool SIMROWDeal(const DTRow &rData,const DTRows &GData,const DTRow &maData,const DTRows &muData,
                            double & msim,std::vector<double> &pm,std::vector<double> &mt,std::string &err);

	 bool SIMROWDealEx(DTRowParam rData,const DTRows &GData,const DTRow &maData,const DTRows &muData,
		 double & msim,std::vector<double> &pm,std::vector<double> &mt,std::string &err);
};

class BaseSim  
{
	public:
		unsigned int			mNSampleNum;		// 样本数目
		unsigned int			mDPointNum;			// 测点个数
		PublicMatrixPtr			mData;				// 样本数据 行:样本数据组的个数,列:测点个数
		PublicMatrixPtr			mGMu;				// 均值	  行:测点个数,列噪音级别
		PublicMatrixPtr			mGnMu;				// 均值	  行:测点个数,列噪音级别
		std::string				mStrErrorMessage;
		BaseSim(void);
		~BaseSim(void);

		BaseSim(const unsigned int n, const unsigned int d);

		bool setData(const DTRows &vectorData);

		bool calculate(const DTRows &rMuData, 
			DTRows &rGData);

		void getData(DTRows &rGData);

};

#endif//__SIMFUNC_H__
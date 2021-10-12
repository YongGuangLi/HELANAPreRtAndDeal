#ifndef __SIMFUNC_H__
#define __SIMFUNC_H__

#include "AlgoVarDef.h"
#include "PublicMatrix.h"

class SimFunc
{
public:
	unsigned int			mNSampleNum;		// ������Ŀ
	unsigned int			mDPointNum;			// ������
	PublicMatrixPtr			mMu;				// ��ֵ	  ��:������,����������
	//PublicMatrixPtr			mData;				// �������� ��:����������ĸ���,��:������
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
					double & msim,std::vector<double> &pm);//add ��������������չ
//private:
	bool setMerry(const DTRows &vectorDataMu,const DTRows &vectorDataG);
	bool setData(const DTRows &vectorDataMu,const DTRows &vectorDataG);
	//void getData(DTRows &rGData);

	// ��������: ��ʷ�������ƶ��㷨
	/*******************************************************************************
	* �� �� ��: SIMDeal
	* ��������: ��ʷ�������ƶ��㷨
	* ����˵��: 
	*    �� ��: const vector<DTRow> rcData ��ʷ�������� const vector<DTRow> muData ����ֵ����
	*    �� ��: double &minSim ���ƶ���ֵ double &maxSim�����������ƶ����ֵ double &avSim�����������ƶ�ƽ��ֵ
 				DTRow &vSim�������ƶȼ��� DTRows &vpm����������ƶȼ��� DTRows &vmt��������ֵ����
	* �� �� ֵ:
	*    �� ��:
	*    ʧ ��:	
	*  ��  �� : ������15802613961
	* ��������: 2016-1-6 15:03:34
	*******************************************************************************/

	 bool SIMDeal(const DTRows &rcData,const DTRows &GData,const DTRow &maData,const DTRows &muData,double &minSim,double &maxSim,double &avSim,DTRow &vSim,DTRows &vpm,DTRows &vmt,std::string &err);
		//
	// ��������: ʵʱ�������ƶ��㷨
	/*******************************************************************************
	* �� �� ��: SIMROWDeal
	* ��������: ���ƶ��㷨
	* ����˵��: 
	*    �� ��: const vector<double> rcData һ��������,const vector<DTRow> muData ����ֵ����
	*    �� ��: double & msim �������ƶ� std::vector<double> &pm ������ƶȼ��� std::vector<double> &mt һ��������ֵ int &num ������
			   std::string &err �쳣��Ϣ
	* �� �� ֵ:
	*    �� ��:
	*    ʧ ��:	
	*  ��  �� : ������15802613961
	* ��������: 2016-1-5 16:44:32
	*******************************************************************************/
	 bool SIMROWDeal(const DTRow &rData,const DTRows &GData,const DTRow &maData,const DTRows &muData,
                            double & msim,std::vector<double> &pm,std::vector<double> &mt,std::string &err);

	 bool SIMROWDealEx(DTRowParam rData,const DTRows &GData,const DTRow &maData,const DTRows &muData,
		 double & msim,std::vector<double> &pm,std::vector<double> &mt,std::string &err);
};

class BaseSim  
{
	public:
		unsigned int			mNSampleNum;		// ������Ŀ
		unsigned int			mDPointNum;			// ������
		PublicMatrixPtr			mData;				// �������� ��:����������ĸ���,��:������
		PublicMatrixPtr			mGMu;				// ��ֵ	  ��:������,����������
		PublicMatrixPtr			mGnMu;				// ��ֵ	  ��:������,����������
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
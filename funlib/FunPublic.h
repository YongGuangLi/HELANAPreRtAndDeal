#ifndef __FUNPUBLIC_H__
#define __FUNPUBLIC_H__

#include <string>

struct Interval
{
	double	 m_UpLimit;              //上限值
	bool     m_IsUpLimit;			//上限值是否存在
	double   m_LowLimit;			//下限值
	bool     m_IsLowLimit;			//下限值是否存在
};
struct VarParam         //计算健康度依赖的可变参数a配置结构
{
	std::string     mPoint;			//模型参数名
	double			mCurValue;		//实时值
	Interval		m_Interval;     //区间
	int				m_iType;		//类型(1:正向 2:反向 3:双向)
	int				m_iParamSource; //可调参数a数据来源(0:公式计算 1:手工设定)
	double			m_ParamValue;	//可调参数a值
};
struct Rtpoint
{
	VarParam  aparam;
	double    pValue;
};
#define DTRowParam std::vector<VarParam>	
#define DTRowPoint std::vector<Rtpoint>

#endif//__FUNPUBLIC_H__

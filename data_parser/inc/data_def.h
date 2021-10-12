/*******************************************************************************
* Copyright（C）,2010-2015, DTXT. Tech .Co.Ltd;
* 文 件 名: data_def.h
* 文件描述: 数据描述类  
*  作  者 : %林晓雨%，18942552977
* 创建日期: 2014-9-12 9:21:53
*******************************************************************************/

#ifndef __DATA_DEF_H__
#define __DATA_DEF_H__


//包定义字节数
#define PACK_NODE_NO_LEN	 sizeof(int)			//包节点号字节数
#define PACK_NO_LEN			 sizeof(long)			//包序号字节数
#define PACK_DATA_TYPE_LEN	 1						//包数据类型字节数
#define PACK_DC_NO_LEN		 sizeof(unsigned short)	//电厂编号字节数
#define PACK_DATA_LEN_LEN	 sizeof(long)			//数据区长度字节数
#define PACK_CONTROL_LEN	 sizeof(short int)		//控制区字节数
#define PACK_DATA_COUNT_LEN	 sizeof(unsigned long)	//数据个数字节数
#define PACK_POINT_NO_LEN	 sizeof(long)			//点的编号字节数
#define PACK_POINT_NAME_LEN	 32 					//点名字节数
#define	PACK_SET_CODE_LEN	 sizeof(char)			//机组编号字节数
#define PACK_VALUE_LEN		 sizeof(float)			//点值字节数
#define PACK_TIME_LEN		 sizeof(long)			//点时间戳字节数
#define PACK_STATE_LEN		 sizeof(char)  			//点的状态字节数
#define PACK_CHECK_SUM_LEN	 sizeof(unsigned short)	//校验位字节数

//数据甄别告警包定义字节数
#define PACK_ALARM_INFO_LEN 		sizeof(unsigned short) //告警个数字节数
#define PACK_ALARM_MSG_LEN			128		//告警信息字节数
#define PACK_ALARM_STATE_LEN		sizeof(char)  //告警状态字节数
#define PACK_ALARM_LEVEL_LEN		sizeof(char)  //告警级别字节数
#define PACK_PRET_MEAN_FRONT_LEN	sizeof(float) //预处理前均值字节数
#define PACK_PRET_MEAN_BACK_LEN		sizeof(float) //预处理后均值字节数 
#define PACK_STAN_DEVI_LEN			sizeof(float) //标准差值
#define PACK_PRET_DETECT_TYPE		sizeof(int)  //检验方法

//文本数据字节定义
#define PACK_NODE_NO_TXT_LEN	 5	//包节点号字节数
#define PACK_NO_TXT_LEN			 11	//包序号字节数
#define PACK_DC_NO_TXT_LEN		 4	//电厂编号字节数
#define PACK_DATA_COUNT_TXT_LEN	 11	//数据个数字节数
#define PACK_POINT_NO_TXT_LEN	 11	//点的编号字节数
#define PACK_POINT_NAME_TXT_LEN	 32 //点名字节数
#define	PACK_SET_CODE_TXT_LEN	 3	//机组编号字节数
#define PACK_VALUE_TXT_LEN		 10	//点值字节数
#define PACK_TIME_TXT_LEN		 11	//点时间戳字节数
#define PACK_STATE_TXT_LEN		 4  //点的状态字节数
#define PACK_BOOL_TXT_LEN		2  //bool字节数

#define PACK_ALARM_INFO_TXT_LEN 	4	 //告警个数字节数
#define PACK_ALARM_MSG_TXT_LEN		128	//告警信息字节数
#define PACK_ALARM_STATE_TXT_LEN	4 	//告警状态字节数
#define PACK_ALARM_LEVEL_TXT_LEN	4 	//告警级别字节数
#define PACK_PRET_MEAN_FRONT_TXT_LEN	10 //预处理前均值字节数
#define PACK_PRET_MEAN_BACK_TXT_LEN		10 //预处理后均值字节数 
#define PACK_STAN_DEVI_TXT_LEN			10  //标准差值
#define PACK_PRET_DETECT_TXT_TYPE		4  //检验方法

//模型数据包扩展定义字节数
#define PACK_MODEL_POINT_NAME_LEN	 64 			//模型数据包点名字节数
#define	PACK_MODEL_SET_CODE_LEN	 3					//模型机组编号字节数

#define PACK_MODEL_MEASURE_POINT_TYPE_LEN	sizeof(char) //测点类型
#define PACK_MODEL_EXPECT_VALUE_LEN	sizeof(float) //模型预测值
#define PACK_MODEL_HEALTH_VALUE_LEN	sizeof(float) //模型健康值

//模型数据包扩展定义文本字节数
#define PACK_MODEL_POINT_NAME_TXT_LEN	 64 //模型数据包点名字节数
#define	PACK_MODEL_SET_CODE_TXT_LEN	 3	//模型数据包机组编号字节数

#define PACK_MODEL_MEASURE_POINT_TYPE_TXT_LEN	4 //测点类型
#define PACK_MODEL_EXPECT_VALUE_TXT_LEN	10 //模型预测值
#define PACK_MODEL_HEALTH_VALUE_TXT_LEN	10 //模型健康值


//包头长度
#define PACK_HEAD_LEN		PACK_NODE_NO_LEN+PACK_NO_LEN+PACK_TIME_LEN+PACK_DATA_TYPE_LEN+PACK_DC_NO_LEN+PACK_DATA_LEN_LEN

#define TXT_HEADER		"dtxy"

#define PACK_NODE_NO	  2037937252  //数据包的节点号 也就是占用4个字节，转换为字符就是"dtxy"

#define PONIT_NAME_LEN	32
#define ALARM_MSG_LEN 	128	
#define ALARM_MSG_MAX_COUNT	5	

#define MODEL_POINT_NAME_LEN 64

enum ParserType
{
	DCPoint = 1, //煤耗、脱硫、脱硝数据
	DiscAlarm = 2, //数据甄别告警数据
	ModelPackage = 3, //模型数据包数据
};

//<class>**********************************************************************
// 类名:  PackDataType
// 目的:  数据类型
//*********************************************************************</class>
enum PackDataType
{
	Point=1,//点数据
	Cfg=2,//配置数据
	Data=3,//普通数据
};

//<class>**********************************************************************
// 类名:  MeasurePointType
// 目的:  测点类型   ly 20180517
//*********************************************************************</class>
enum MeasurePointType
{
	CommonMeasurePoint = '0',//常规测点
	ModelMeasurePoint = '1',//模型测点	
};

//<class>**********************************************************************
// 类名:  DiscAlarmMsg
// 目的:  数据甄别增加的点数据
//*********************************************************************</class>
struct DiscAlarmInfo
{
	char  AlarmMsg[ALARM_MSG_LEN]; //告警信息
	char  AlarmState;	//告警状态
	char  AlarmLevel;//告警级别
};

//<class>**********************************************************************
// 类名:  DiscData
// 目的:  数据甄别增加的点数据
//*********************************************************************</class>
struct DiscAlarmValue
{
	unsigned short 		AlarmInfoCount; //告警个数
	DiscAlarmInfo		AlarmInfo[ALARM_MSG_MAX_COUNT]; //告警组
	float PretMeanFront; //预处理前均值
	float PretMeanBack;  //预处理后值
	float StanDevi;// 标准差值
	int   DetectType; //检测方法 
};

//<class>**********************************************************************
// 类名:  ModelPackageValue
// 目的:  模型数据包增加的点数据  ly  20180517
//*********************************************************************</class>
struct ModelPackageValue
{
	long ID;//点ID
	char Name[MODEL_POINT_NAME_LEN];//点名	
	float Value;//点值
	long  Time;//点的时间戳
	char  State;//点的状态
	char  SetCode[3];//机组编号		
	char  PointType;		//测点类型  0:常规测点，1：模型测点	
	float ExpectVal;	//模型期望值
	float HealthVal;	//模型健康度值
};


//<class>**********************************************************************
// 类名:  PointData
// 目的:  点数据
//*********************************************************************</class>
struct PointValue
{
	long ID;//点ID
	char Name[PONIT_NAME_LEN];//点名	
	float Value;//点值
	long  Time;//点的时间戳
	char  State;//点的状态
	char  SetCode;//机组编号	
	DiscAlarmValue *Disc;//数据甄别点增加数据	
};

//<class>**********************************************************************
// 类名:  PointDatas
// 目的:  多点数据
//*********************************************************************</class>
struct PointDatas
{
	int NodeNo;//包节点编号（"dtxy"）
	long  No;//包序号
	long  PackTime;//包发送的时间
	unsigned short DCNo;//电厂编号
	bool ID;//是否有ID
	bool Name;//是否有点名
	bool Time;//是否有时间戳
	bool State;//是否有点状态
	bool SetCode;//是否有机组号
	unsigned long  Count;//点的个数
	unsigned short  CheckSum;//校验和
	PointValue* Points;//点
	ModelPackageValue *MPValues; //模型数据包增加的点数据
};

//数据传输方式
enum RemoteDataType
{
	Binary=0,//二进制
	Text=1,//文本
};

#define SPLIT_CHAR	";"
#define SPLIT_LINE ";"
#define SPLIT ";"
#define PACK_HEAD_COUNT	10


#endif

/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: buff_points.h
* 文件描述: Buff文件解析数据管理类
*  作  者 : 汤卫波，13730895608
* 创建日期: 2014-10-23 8:57:25
*******************************************************************************/

#ifndef __BUFF_POINTS_H__
#define __BUFF_POINTS_H__

#include "data_def.h"
#include <string>

class DataMgr;

class BuffPoints
{
public:
    BuffPoints(void);
    virtual ~BuffPoints(void);
public:

    int GetBuffFileCount(void);
    /*
    * 功能描述: 初始化Buff文件点的数据
    * 输入参数: Buff文件所在目录
    * 输入参数: 文件前缀名
    * 输出参数: 无
    * 返 回 值: 成功返回true，失败返回false
    */
    bool InitPoints(const std::string &strPath, const std::string &strHname);

    /*
    * 功能描述: 初始化Buff文件点的数据
    * 输入参数: Buff文件所在目录
    * 输入参数: 文件前缀名
    * 输出参数: 无
    * 返 回 值: 成功返回true，失败返回false
    */
    bool InitBuff(const std::string &strPath, const std::string &strHname,const int &itype);
    /*
    * 功能描述: 读取最近Buff文件信息
    * 输入参数: 无
    * 输出参数: 无
    * 返 回 值: 成功返回true，失败返回false
    */
    bool ReadBuffFile(void);
    /*
    * 功能描述: 释放加载的点数据信息
    * 输入参数: 无
    * 输出参数: 无
    * 返 回 值: 无
    */
    void DestoryPoints(void);

    /*
    * 功能描述: 加载的点空间申请
    * 输入参数: 无
    * 输出参数: 无
    * 返 回 值: 无
    */
    void CreatePointData(const int iCount);

    bool SentPointData();
public:
    // 功能描述: 获取电厂编号
    long GetFactoryTag(void);
    // 功能描述: 获取点的个数
    long GetPointCount(void);
    // 功能描述: 获取包的生成时间
    std::string GetPacketDTime(void);
    // 功能描述: 获取指定点名的信息
    PointValue* GetPointsValue(const std::string &strPointName);
    // 功能描述: 获取指定点位置的信息
    PointValue* GetPointsValue(const long &lPointBit);

    // 功能描述: 获取指定点名的信息
    ModelPackageValue* GetPointsValueEx(const std::string &strPointName);
    // 功能描述: 获取指定点位置的信息
    ModelPackageValue* GetPointsValueEx(const long &lPointBit,const long imax);
public:
    DataMgr* m_pBuffOpt;            // Buff文件点操作对象
    PointDatas m_stPoints;          // 保存点信息数据

private:
    int m_FileType;
    int m_DataType;
};

#endif//__BUFF_POINTS_H__

/*******************************************************************************
* Copyright（C）,2010-2015,DTXY.Tech .Co.Ltd;
* 文 件 名: file_buff.h
* 文件描述: buff 文件解析 数据输入输出功能实现类 
*  作  者 : %林晓雨%，18942552977
* 创建日期: 2014-9-15 11:57:09
*******************************************************************************/

#ifndef __FILE_BUFF_H__
#define __FILE_BUFF_H__

#include <iostream> 
#include <list>

class ScanPathFile;

class FileBuff
{
    std::string					mDataFullPath;//目录全路径 
	std::string					mFnamePrefix;
    ScanPathFile *				mScanPathFile; //扫描目录对象
	std::string					mStrError;
	std::list<std::string> 		mListFile;
public:
    FileBuff(
		const std::string &data_path,
		const std::string &point_fname_prefix);

    ~FileBuff(void);

	//功能描述:检测目录是否存在
	bool open();

	//功能描述:释放
	void close();

	//功能描述:读取数据包
	bool retrieveData(void* pack_data, long &read_data_len);

	//功能描述:保存数据包
	bool saveData(
			const void* pack_data, 
			const long &data_len);

	//功能描述:获取错误信息
	std::string getError();
	//功能描述:获取目录文件总个数  add by wk 2018-7-10
	int getDirFileNum();
private:
	//功能描述:扫描文件目录
	bool scanFileName(std::string &file_name);
	//功能描述:从文件中读取数据包
	bool readFile(const std::string &filename, void* pack_data, long &read_data_len);
	//功能描述:将数据包写入文件
	bool writeFile(
			const void* pack_data, 
			const long &data_len,
			const std::string &filename);
	//功能描述:拼接文件名
	std::string composeFullFileName();
	//功能描述:检查数据包是否完整
	bool  checkData(const void* data, long len);
	static bool my_cmp(const std::string &v1, const std::string &v2);
};
#endif

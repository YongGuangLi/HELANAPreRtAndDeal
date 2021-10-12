/*******************************************************************************
* Copyright（C）,2010-2015,DTXY.Tech .Co.Ltd;
* 文 件 名: file.h
* 文件描述: 文件功能实现类 
*  作  者 : %林晓雨%，18942552977
* 创建日期: 2014-9-15 11:57:09
*******************************************************************************/

#ifndef __FILE_H__
#define __FILE_H__

#include <iostream> 
#include <stdio.h> 

class File
{
	FILE *          		mFile;
	std::string 		    mName;
	std::string            	mMode;

public:
    File(const std::string &name, const std::string &mode);
    ~File(void);

	//功能描述:关闭文件 
	void closeFile();

	//功能描述:判断文件否打开 
	bool isGood() const {return mFile != NULL;}

	//功能描述:写文件 
	bool append(const void* data, const unsigned int &data_len);

	//功能描述:读文件 
	unsigned int  read(void* data, const unsigned int &data_len);
};
#endif

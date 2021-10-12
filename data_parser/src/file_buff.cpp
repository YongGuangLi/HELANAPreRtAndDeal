/******************************************************************************
* Copyright（C）,2010-2015,DTXY.Tech .Co.Ltd;
* 文 件 名: file_buff.cpp
* 文件描述: buff 文件解析 数据输入输出功能实现类 
*  作  者 : %林晓雨%，18942552977
* 创建日期: 2014-9-15 11:57:28
*******************************************************************************/

#include "file_buff.h"

#include "pub_def.h"
#include "error_def.h"
#include "util.h"
#include "public_function_library.h"
#include "scan_path_file.h"
#include "file.h"

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <list> 

using namespace std;			 

#define END			"end"
#define END_LEN		 3

FileBuff::FileBuff(const string &path, const string &point_fname_prefix)
:
mDataFullPath(path),
mFnamePrefix(point_fname_prefix),
mScanPathFile(NULL),
mStrError(static_cast<std::string>(STRING_EMPTY))
{
	mScanPathFile = new ScanPathFile(FILE_TYPE, 1);
}


FileBuff::~FileBuff(void)
{
	if (mScanPathFile != NULL) delete mScanPathFile;
}


bool
FileBuff::open()
{
	if (!PubOpt::FileOpt::IsFindFile(mDataFullPath))
	{
		mStrError = IDS_DIR_ISEXIST;
		return false;
	}
	return true;
}


void
FileBuff::close()
{
	mListFile.clear();
}


bool
FileBuff::my_cmp(const string &v1, const string &v2)
{
	time_t t1 =  Util::GetLastWriteTime(v1);
	time_t t2 =  Util::GetLastWriteTime(v2);
	return t1 < t2;
}

bool
FileBuff::scanFileName(string &file_name)
{
    //扫描目录
	file_name = static_cast<std::string>(STRING_EMPTY);
	//如果内存的文件数小于2个则重新加载文件
	if (mListFile.size() < 2)
	{
		mListFile.clear();
		if (!mScanPathFile->ScanFile(mDataFullPath, mListFile))
		{
			mStrError = IDS_SCANFILE_ERROR;
			return false;
		}
	}

	// 如果目录下文件等于1，有可能其它进程正在操作些文件，忽略;
	if (mListFile.empty())
	{
		return true;
	}

	mListFile.sort();
	//mListFile.sort(FileBuff::my_cmp);
    list<string>::iterator itr = mListFile.begin();
	if (itr == mListFile.end()) return true;

	if (mListFile.size() == 1) 
	{
		string fname = *itr;
		unsigned long  m_time = Util::GetLastWriteTime(fname);
		unsigned long c_time = Util::GetNowTime();
		//if (c_time < m_time || c_time - m_time <= 1)

#if 0
		if (c_time < m_time || c_time - m_time <= 60)
		{
			return true;
		}
#endif
	}

    file_name = *itr;
	mListFile.erase(itr);
	return true;
}


bool
FileBuff::retrieveData(void* pack_data, long &read_data_len)
{
	string filename;
	if (!scanFileName(filename)) return false;

	if (filename.empty()) 
	{
		mStrError = ID_DIR_NULL;
		return false;
	}

	cout << "read file; filename:" << filename << ";"<< endl;
	bool rslt = readFile(filename, pack_data, read_data_len);
	PubOpt::FileOpt::RemoveFile(filename);
	return rslt;
}

int FileBuff::getDirFileNum()
{
	if (!mScanPathFile->ScanFile(mDataFullPath, mListFile))
		return 0;
	return mListFile.size();
}

bool
FileBuff::readFile(
		const string &filename,
		void* pack_data,
		long &read_data_len)
{
	if (!PubOpt::FileOpt::IsFindFile(filename))
	{
		mStrError = IDS_DATA_NULL;
		read_data_len = 0;
		return false;
	}
	
	int file_len = 0;
	if (!PubOpt::FileOpt::GetFileSize(filename, file_len))
	{
		mStrError = IDS_DATA_NULL;
		read_data_len = 0;
		return false;
	}

	if (file_len - END_LEN <= 0)
	{	
		mStrError = IDS_DATA_NULL;
		read_data_len = 0;
		return false;
	}

	if (file_len >= MAX_FILE_SIZE)
	{
		mStrError = IDS_BIG_DATA_ERROR;
		read_data_len = 0;
		return false;
	}

	if (file_len - END_LEN > read_data_len)
	{
		mStrError = IDS_ERROR_BUFFER_FILE;
		read_data_len = 0;
		return false;
	}

	// 加载文件信息
	//
    File *file = new File(filename, "rb");
    if(!file->isGood())
	{
		mStrError = IDS_READ_FILE_ERROR;
		read_data_len = 0;
		delete file;
		return false;
	}

	unsigned int data_len = file_len - END_LEN;
	unsigned int rr = file->read(pack_data, data_len);
	if (rr != data_len)   // 加载文件
	{
		mStrError = IDS_READ_FILE_ERROR;
		read_data_len = 0;
		delete file;
		return false;
	}
//cout << "cal_len:" << read_data_len << ";len:" << file_len -END_LEN << endl;

	read_data_len = file_len - END_LEN;

	char end_str[END_LEN +1] = {0};
	rr = file->read(end_str, END_LEN);
	if (rr != END_LEN)
	{
		mStrError = IDS_ERROR_DATA;
		read_data_len = 0;
		delete file;
		return false;
	}
	delete file;

	if (!checkData(end_str, END_LEN))
	{
		mStrError = IDS_ERROR_DATA;
		read_data_len = 0;
		return false;
	}
	return true;
}


bool
FileBuff::saveData(
		const void* pack_data,
	  	const long &data_len)
{
	string filename = composeFullFileName();
	while(PubOpt::FileOpt::IsFindFile(filename))
	{
		PubOpt::SystemOpt::SleepWait(1000);
		filename = composeFullFileName();
	}
	//cout << "saveData" << filename << ";" << data_len << ";"<< endl;
	return writeFile(pack_data, data_len, filename);
}


bool
FileBuff::writeFile(
		const void* pack_data,
		const long &data_len,
		const string &filename)
{
    File * file = new File(filename.c_str(), "wb");
    if(!file->isGood())
	{
		mStrError = filename +":" + IDS_WRITE_FILE_ERROR;
		delete file;
		return false;
	}

	bool rslt = file->append(pack_data, data_len);
	if (!rslt)
	{
		mStrError = IDS_WRITE_FILE_ERROR;
		delete file;
		return false;
	}

	file->append(END, END_LEN);
	delete file;
    return true;
}


string
FileBuff::composeFullFileName()
{
    string full_path = mDataFullPath;
    int strlen = full_path.length();
    if(full_path.c_str()[strlen-1] != '/')   full_path = full_path + "/";

	full_path += mFnamePrefix;

    // modify begin: tangweibo  修改BUff文件生成文件名称
	//unsigned long long timestamp = Util::GetTimestamp();
    //   full_path += Util::Number2String<unsigned long long>(timestamp);
    std::string strTime = PubOpt::SystemOpt::GetSystemDateTime();
    if (strTime.size() <= 19)
    {
        strTime += ".000";
    }
    strTime = PubOpt::StringOpt::StringReplace(strTime, ":", ".");
    full_path += strTime + ".txt";
    // modify end: tangweibo  修改BUff文件生成文件名称
	return full_path;
}

string 
FileBuff::getError()
{
	string str_errmsg =  mStrError;
	mStrError = static_cast<std::string>(STRING_EMPTY);
	return str_errmsg;
}


bool 
FileBuff::checkData(const void* data, long len)
{
	char* szEnd=(char*)data;
	if((size_t)len<strlen(END))
		return false;
	//以end为结尾
	if(strcmp(szEnd,END)==0)
		return true;
	else
		return false;
}


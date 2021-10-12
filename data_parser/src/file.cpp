/******************************************************************************
* Copyright��C��,2010-2015,DTXY.Tech .Co.Ltd;
* �� �� ��: file.cpp
* �ļ�����: �ļ�����ʵ���� 
*  ��  �� : %������%��18942552977
* ��������: 2014-9-15 11:57:28
*******************************************************************************/

#include "file.h"

using namespace std;

File::File(const string &name, const string &mode)
:
mFile(NULL),
mName(name),
mMode(mode)
{
    mFile = ::fopen(mName.c_str(), mMode.c_str());
}


File::~File(void)
{
	closeFile();
}


void
File::closeFile()
{
	if (!mFile)  return;
	::fclose(mFile);
	mFile = NULL;
}


bool
File::append(const void* data, const unsigned int &data_len)
{
	if (mFile == NULL) return false;
	::fseek(mFile, 0, SEEK_END);
	size_t asize = ::fwrite(data, 1, data_len, mFile);
	if (asize < 0 || (long) asize != data_len)
	{
		return false;
	}
	return true;
}


unsigned int
File::read(void* data, const unsigned int &data_len)
{
	if (mFile == NULL) return 0;
	unsigned int rr =::fread(data, 1, data_len, mFile);
	return rr;
}


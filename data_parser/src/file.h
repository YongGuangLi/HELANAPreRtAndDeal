/*******************************************************************************
* Copyright��C��,2010-2015,DTXY.Tech .Co.Ltd;
* �� �� ��: file.h
* �ļ�����: �ļ�����ʵ���� 
*  ��  �� : %������%��18942552977
* ��������: 2014-9-15 11:57:09
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

	//��������:�ر��ļ� 
	void closeFile();

	//��������:�ж��ļ���� 
	bool isGood() const {return mFile != NULL;}

	//��������:д�ļ� 
	bool append(const void* data, const unsigned int &data_len);

	//��������:���ļ� 
	unsigned int  read(void* data, const unsigned int &data_len);
};
#endif

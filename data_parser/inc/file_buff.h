/*******************************************************************************
* Copyright��C��,2010-2015,DTXY.Tech .Co.Ltd;
* �� �� ��: file_buff.h
* �ļ�����: buff �ļ����� ���������������ʵ���� 
*  ��  �� : %������%��18942552977
* ��������: 2014-9-15 11:57:09
*******************************************************************************/

#ifndef __FILE_BUFF_H__
#define __FILE_BUFF_H__

#include <iostream> 
#include <list>

class ScanPathFile;

class FileBuff
{
    std::string					mDataFullPath;//Ŀ¼ȫ·�� 
	std::string					mFnamePrefix;
    ScanPathFile *				mScanPathFile; //ɨ��Ŀ¼����
	std::string					mStrError;
	std::list<std::string> 		mListFile;
public:
    FileBuff(
		const std::string &data_path,
		const std::string &point_fname_prefix);

    ~FileBuff(void);

	//��������:���Ŀ¼�Ƿ����
	bool open();

	//��������:�ͷ�
	void close();

	//��������:��ȡ���ݰ�
	bool retrieveData(void* pack_data, long &read_data_len);

	//��������:�������ݰ�
	bool saveData(
			const void* pack_data, 
			const long &data_len);

	//��������:��ȡ������Ϣ
	std::string getError();
	//��������:��ȡĿ¼�ļ��ܸ���  add by wk 2018-7-10
	int getDirFileNum();
private:
	//��������:ɨ���ļ�Ŀ¼
	bool scanFileName(std::string &file_name);
	//��������:���ļ��ж�ȡ���ݰ�
	bool readFile(const std::string &filename, void* pack_data, long &read_data_len);
	//��������:�����ݰ�д���ļ�
	bool writeFile(
			const void* pack_data, 
			const long &data_len,
			const std::string &filename);
	//��������:ƴ���ļ���
	std::string composeFullFileName();
	//��������:������ݰ��Ƿ�����
	bool  checkData(const void* data, long len);
	static bool my_cmp(const std::string &v1, const std::string &v2);
};
#endif

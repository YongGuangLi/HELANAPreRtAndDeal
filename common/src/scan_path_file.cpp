#include "scan_path_file.h"

#include <boost/filesystem.hpp>

ScanPathFile::ScanPathFile(const ScanType nType /*= FILE_TYPE*/, 
                           const int &nDepth /*= MAX_SCAN_DEPTH*/)
{
    m_enType = nType;
    m_nDepth = nDepth;
}

ScanPathFile::~ScanPathFile(void)
{
    // �������
}

bool ScanPathFile::ScanFile(const std::string &strPath, std::list<std::string> &lstFile)
{
    if (!IsDirectory(strPath))
    {
        return false;
    }
    m_strScanPath = strPath;
    if (!DoRunScanFile(lstFile))
    {
        return false;
    }
    return true;
}

bool ScanPathFile::IsDirectory(const std::string &strDirectory)
{
    // �жϵ�ǰ�ļ��Ƿ�ΪĿ¼
    if (!boost::filesystem::is_directory(strDirectory.c_str()))
    {
        return false;
    }
    return true;
}

bool ScanPathFile::DoRunScanFile(std::list<std::string> &lstFile)
{
    lstFile.clear();
    boost::filesystem::recursive_directory_iterator end_itr;
    boost::filesystem::recursive_directory_iterator iter(m_strScanPath.c_str());
    for (; iter != end_itr; ++iter)
    {
        if (iter.level() >= m_nDepth)         // ɨ������жϣ�ע����ȴ�0��ʼ
        {
            continue;
        }
        std::string strFile = iter->path().string();
        if ((DIRECTORY_TYPE == m_enType)&&IsDirectory(strFile))       // ΪĿ¼ʱ
        {
            lstFile.push_back(strFile);
        } else if ((FILE_TYPE == m_enType)&&!IsDirectory(strFile))    // Ϊ�ļ�ʱ
        {
            lstFile.push_back(strFile);
        }
    }
    return true;
}

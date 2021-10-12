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
    // 空语句体
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
    // 判断当前文件是否为目录
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
        if (iter.level() >= m_nDepth)         // 扫描深度判断，注：深度从0开始
        {
            continue;
        }
        std::string strFile = iter->path().string();
        if ((DIRECTORY_TYPE == m_enType)&&IsDirectory(strFile))       // 为目录时
        {
            lstFile.push_back(strFile);
        } else if ((FILE_TYPE == m_enType)&&!IsDirectory(strFile))    // 为文件时
        {
            lstFile.push_back(strFile);
        }
    }
    return true;
}

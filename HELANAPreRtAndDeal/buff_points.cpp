#include "log.h"
#include "mutex.h"
#include "data_mgr.h"
#include "error_def.h"
#include "buff_points.h"
#include "ServiceEIDSPreConfig.h"
#include "public_function_library.h"

BuffPoints::BuffPoints(void)
    : m_pBuffOpt(NULL)
{
    m_pBuffOpt = new DataMgr();
}

BuffPoints::~BuffPoints(void)
{
    if (NULL != m_pBuffOpt)
    {
        delete m_pBuffOpt;
        m_pBuffOpt = NULL;
    }
}
bool BuffPoints::InitBuff(const std::string &strPath, const std::string &strHname,const int &itype)
{
    if(!PubOpt::FileOpt::IsFindFile(strPath))
    {
        bool is_ok = PubOpt::FileOpt::NewDirect(strPath);
        if(!is_ok)
            return false;
    }

    if(1 == itype)
    {
        m_FileType = SINGLETON(ServiceEIDSPreConfig)->GetBuffFileType();
        m_DataType = SINGLETON(ServiceEIDSPreConfig)->GetBuffDataType();
    }
    else
    {
        m_FileType = SINGLETON(ServiceEIDSPreConfig)->GetSentBuffFileType();
        m_DataType = SINGLETON(ServiceEIDSPreConfig)->GetSentBuffDataType();
    }

    m_pBuffOpt->rt_Initial(
                static_cast<ParserType>(m_FileType),
                static_cast<RemoteDataType>(m_DataType),
                strPath, strHname);
    if (!m_pBuffOpt->rt_Open())
    {
        return false;
    }

    return true;
}

bool BuffPoints::InitPoints(const std::string &strPath, const std::string &strHname)
{
    if(!PubOpt::FileOpt::IsFindFile(strPath))
    {
        bool is_ok = PubOpt::FileOpt::NewDirect(strPath);
        if(!is_ok) return false;
    }
    int nFileType = SINGLETON(ServiceEIDSPreConfig)->GetBuffFileType();
    int nDataType = SINGLETON(ServiceEIDSPreConfig)->GetBuffDataType();
    m_pBuffOpt->rt_Initial(
                static_cast<ParserType>(nFileType),
                static_cast<RemoteDataType>(nDataType),
                strPath, strHname);
    if (!m_pBuffOpt->rt_Open())
    {
        return false;
    }
    m_pBuffOpt->CreatePointData(&m_stPoints, 10001);
    return true;
}
int BuffPoints::GetBuffFileCount(void)
{
    return m_pBuffOpt->getDirFileNum();
}
bool BuffPoints::ReadBuffFile(void)
{
    extern MutexLock g_oScanFile;
    AutoLock oAutoLock(g_oScanFile);
    if (!m_pBuffOpt->rt_Receive(&m_stPoints))
    {
        if (m_pBuffOpt->GetError() == ID_DIR_NULL)
        {
            SINGLETON(Log)->WriteLog("No Data In The Directory.", true);
        }
        else
        {
            SINGLETON(Log)->WriteLog("Read Buff File Failed.", true);
        }
        return false;
    }
    SINGLETON(Log)->WriteLog(
                PubOpt::StringOpt::StringFormat("Read Buff File Point %u Success.", m_stPoints.Count));
    return true;
}

long BuffPoints::GetFactoryTag(void)
{
    return m_stPoints.DCNo;
}

long BuffPoints::GetPointCount(void)
{
    extern MutexLock g_oScanFile;
    AutoLock oAutoLock(g_oScanFile);
    return m_stPoints.Count;
}

std::string BuffPoints::GetPacketDTime(void)
{
    extern MutexLock g_oScanFile;
    AutoLock oAutoLock(g_oScanFile);
    return PubOpt::SystemOpt::DateTmToStr(m_stPoints.PackTime,1);
}

void BuffPoints::DestoryPoints(void)
{
    m_pBuffOpt->DeletePointData(&m_stPoints);
}
void BuffPoints::CreatePointData(const int iCount)
{
    m_pBuffOpt->CreatePointData(&m_stPoints, iCount);
}
bool BuffPoints::SentPointData()
{
    return m_pBuffOpt->rt_Send(m_stPoints);
}
PointValue* BuffPoints::GetPointsValue(const std::string &strPointName)
{
    PointValue* pPointValue = NULL;
    for (long i=0; i<GetPointCount(); ++i)
    {
        pPointValue = GetPointsValue(i);
        if ((NULL != pPointValue) && (strPointName == pPointValue->Name))
        {
            return pPointValue;
        }
    }
    return NULL;
}

PointValue* BuffPoints::GetPointsValue(const long &lPointBit)
{
    if (lPointBit >= GetPointCount())
    {
        return NULL;
    }
    return &m_stPoints.Points[lPointBit];
}
ModelPackageValue* BuffPoints::GetPointsValueEx(const std::string &strPointName)
{
    ModelPackageValue* pPointValue = NULL;
    long imax = GetPointCount();
    for (long i=0; i<imax; ++i)
    {
        pPointValue = GetPointsValueEx(i,imax);
        if ((NULL != pPointValue) && (strPointName == pPointValue->Name))
        {
            return pPointValue;
        }
    }
    return NULL;
}
ModelPackageValue* BuffPoints::GetPointsValueEx(const long &lPointBit,const long imax)
{
    extern MutexLock g_oScanFile;
    AutoLock oAutoLock(g_oScanFile);

    /*if (lPointBit >= GetPointCount())
    {
        return NULL;
    }*/
    if (lPointBit >= imax)
    {
        return NULL;
    }
    return &m_stPoints.MPValues[lPointBit];
}

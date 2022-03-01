#include "dtwaincore.h"
DTwainCore::DTwainCore()
{

}

DTwainCore::~DTwainCore()
{
    if (lib.isLoaded())
    {
        lib.unload();
    }
}

bool DTwainCore::Loadlib()
{
    if (lib.isLoaded())
    {
        return true;
    }
    QString libfile = "";
    libfile = "libs/windows/dtwain.dll";
    QString libAllFilePath = qApp->applicationDirPath() + "/" + libfile;
    lib.setFileName(libAllFilePath);
    lib.load();
    if (!lib.isLoaded())
    {
        return false;
    }
    m_DTWAIN_ENTRYPOINT.DTWain_Init = reinterpret_cast<LP_DTWain_Init>(lib.resolve("DTWain_Init"));
    m_DTWAIN_ENTRYPOINT.DTWain_UnInit = reinterpret_cast<LP_DTWain_UnInit>(lib.resolve("DTWain_UnInit"));
    m_DTWAIN_ENTRYPOINT.DTWain_GetScanerList = reinterpret_cast<LP_DTWain_GetScanerList>(lib.resolve("DTWain_GetScanerList"));
    m_DTWAIN_ENTRYPOINT.DTWain_SetSelectedSource = reinterpret_cast<LP_DTWain_SetSelectedSource>(lib.resolve("DTWain_SetSelectedSource"));
    m_DTWAIN_ENTRYPOINT.DTWain_SetShowUI = reinterpret_cast<LP_DTWain_SetShowUI>(lib.resolve("DTWain_SetShowUI"));
    m_DTWAIN_ENTRYPOINT.DTWain_SetDuplexEnabled = reinterpret_cast<LP_DTWain_SetDuplexEnabled>(lib.resolve("DTWain_SetDuplexEnabled"));
    m_DTWAIN_ENTRYPOINT.DTWain_SetJPGQuality = reinterpret_cast<LP_DTWain_SetJPGQuality>(lib.resolve("DTWain_SetJPGQuality"));
    m_DTWAIN_ENTRYPOINT.DTWain_SetBeforeSCanWaitingTime = reinterpret_cast<LP_DTWain_SetBeforeSCanWaitingTime>(lib.resolve("DTWain_SetBeforeSCanWaitingTime"));
    m_DTWAIN_ENTRYPOINT.DTWain_SetPixelType = reinterpret_cast<LP_DTWain_SetPixelType>(lib.resolve("DTWain_SetPixelType"));
    m_DTWAIN_ENTRYPOINT.DTWain_SetDPI = reinterpret_cast<LP_DTWain_SetDPI>(lib.resolve("DTWain_SetDPI"));
    m_DTWAIN_ENTRYPOINT.DTWain_SetProgress = reinterpret_cast<LP_DTWain_SetProgress>(lib.resolve("DTWain_SetProgress"));
    m_DTWAIN_ENTRYPOINT.DTWain_SetStandardSize = reinterpret_cast<LP_DTWain_SetStandardSize>(lib.resolve("DTWain_SetStandardSize"));
    m_DTWAIN_ENTRYPOINT.DTWain_SetFrame = reinterpret_cast<LP_DTWain_SetFrame>(lib.resolve("DTWain_SetFrame"));
    m_DTWAIN_ENTRYPOINT.DTWain_SetRotation = reinterpret_cast<LP_DTWain_SetRotation>(lib.resolve("DTWain_SetRotation"));
    m_DTWAIN_ENTRYPOINT.DTWain_SetFeederEnabled = reinterpret_cast<LP_DTWain_SetFeederEnabled>(lib.resolve("DTWain_SetFeederEnabled"));
    m_DTWAIN_ENTRYPOINT.DTWain_DoScanToFile = reinterpret_cast<LP_DTWain_DoScanToFile>(lib.resolve("DTWain_DoScanToFile"));
    m_DTWAIN_ENTRYPOINT.DTWain_DoScanToDir = reinterpret_cast<LP_DTWain_DoScanToDir>(lib.resolve("DTWain_DoScanToDir"));
    m_DTWAIN_ENTRYPOINT.DTWain_SetCallBackForScanToDir = reinterpret_cast<LP_DTWain_SetCallBackForScanToDir>(lib.resolve("DTWain_SetCallBackForScanToDir"));
    return true;
}

bool DTwainCore::Freelib()
{
    if (lib.isLoaded())
    {
        lib.unload();
    }
    m_DTWAIN_ENTRYPOINT.DTWain_Init = nullptr;
    m_DTWAIN_ENTRYPOINT.DTWain_UnInit = nullptr;
    m_DTWAIN_ENTRYPOINT.DTWain_GetScanerList = nullptr;
    m_DTWAIN_ENTRYPOINT.DTWain_SetSelectedSource = nullptr;
    m_DTWAIN_ENTRYPOINT.DTWain_SetDuplexEnabled = nullptr;
    m_DTWAIN_ENTRYPOINT.DTWain_SetJPGQuality = nullptr;
    m_DTWAIN_ENTRYPOINT.DTWain_SetBeforeSCanWaitingTime = nullptr;
    m_DTWAIN_ENTRYPOINT.DTWain_SetShowUI = nullptr;
    m_DTWAIN_ENTRYPOINT.DTWain_SetPixelType = nullptr;
    m_DTWAIN_ENTRYPOINT.DTWain_SetDPI = nullptr;
    m_DTWAIN_ENTRYPOINT.DTWain_SetProgress = nullptr;
    m_DTWAIN_ENTRYPOINT.DTWain_SetStandardSize = nullptr;
    m_DTWAIN_ENTRYPOINT.DTWain_SetFrame = nullptr;
    m_DTWAIN_ENTRYPOINT.DTWain_SetRotation = nullptr;
    m_DTWAIN_ENTRYPOINT.DTWain_SetFeederEnabled = nullptr;
    m_DTWAIN_ENTRYPOINT.DTWain_DoScanToFile = nullptr;
    m_DTWAIN_ENTRYPOINT.DTWain_DoScanToDir = nullptr;
    m_DTWAIN_ENTRYPOINT.DTWain_SetCallBackForScanToDir = nullptr;
    return true;
}


DTwainAPP* DTwainAPP::m_DToperation = nullptr;
DTwainAPP::~DTwainAPP()
{
    m_DTwainCore->~DTwainCore();
}

DTwainAPP* DTwainAPP::getDTInstance()
{
    if (m_DToperation == nullptr)
    {
        m_DToperation = new DTwainAPP();
    }
    return m_DToperation;
}
void DTwainAPP::initAPP()
{
    m_DTwainCore = new DTwainCore();
    m_State = 0;
    if (!m_DTwainCore->Loadlib())
    {
        QMessageBox::information(nullptr, "提示", "未找到dtwain.dll");
        return;
    }
    m_State = 1;
    if (m_DTwainCore->m_DTWAIN_ENTRYPOINT.DTWain_Init())
    {
        m_State = 2;
    }

}

void DTwainAPP::exitAPP()
{
    m_DTwainCore->m_DTWAIN_ENTRYPOINT.DTWain_UnInit();
}

void DTwainAPP::reInitAPP()
{
    if (m_State > 0)
    {
        m_DTwainCore->Freelib();
        m_State = 0;
    }

    if (!m_DTwainCore->Loadlib())
    {
        QMessageBox::information(nullptr, "提示", "未找到dtwain.dll");
        return;
    }
    m_State = 1;
    if (m_DTwainCore->m_DTWAIN_ENTRYPOINT.DTWain_Init())
    {
        m_State = 2;
    }
}

bool DTwainAPP::get_device_list()
{
    wchar_t llist[256] = {0};
    if (m_DTwainCore->m_DTWAIN_ENTRYPOINT.DTWain_GetScanerList(llist))
    {
        m_State = 3;
        if (QString::fromWCharArray(llist).isNull() || QString::fromWCharArray(llist).isEmpty())
        {
            m_device_list.clear();
        }
        else
        {
            m_device_list = QString::fromWCharArray(llist).split("\r\n", QString::SkipEmptyParts);
        }
        return true;
    }
    return false;
}

int DTwainAPP::get_device_list_count()
{
    m_device_list_count = m_device_list.count();
    return m_device_list_count;
}

bool DTwainAPP::setSelectedSource(uint Sourceindex)
{
    qDebug() << "";
    return m_DTwainCore->m_DTWAIN_ENTRYPOINT.DTWain_SetSelectedSource(Sourceindex);
}
bool DTwainAPP::setShowUI(bool showUI)
{
    qDebug() << "";
    return m_DTwainCore->m_DTWAIN_ENTRYPOINT.DTWain_SetShowUI(showUI);
}
bool DTwainAPP::setDuplexEnabled(bool duplexEnabled)
{
    if (m_DTwainCore->m_DTWAIN_ENTRYPOINT.DTWain_SetDuplexEnabled == nullptr)
    {
        return false;
    }
    qDebug() << "";
    return m_DTwainCore->m_DTWAIN_ENTRYPOINT.DTWain_SetDuplexEnabled(duplexEnabled);
}
bool DTwainAPP::setJPGQuality(int aiJPGQuality)
{
    if (m_DTwainCore->m_DTWAIN_ENTRYPOINT.DTWain_SetJPGQuality == nullptr)
    {
        return true;
    }
    qDebug() << "";
    return m_DTwainCore->m_DTWAIN_ENTRYPOINT.DTWain_SetJPGQuality(aiJPGQuality);
}
bool DTwainAPP::setBeforeSCanWaitingTime(int aiBeforeSCanWaitingTime)
{
    qDebug() << "";
    return m_DTwainCore->m_DTWAIN_ENTRYPOINT.DTWain_SetBeforeSCanWaitingTime(aiBeforeSCanWaitingTime);
}

bool DTwainAPP::setPixelType(uint PixelType)
{
    qDebug() << "";
    return m_DTwainCore->m_DTWAIN_ENTRYPOINT.DTWain_SetPixelType(PixelType);
}
bool DTwainAPP::setDPI(uint DPI)
{
    qDebug() << "";
    return m_DTwainCore->m_DTWAIN_ENTRYPOINT.DTWain_SetDPI(DPI);
}
bool DTwainAPP::setProgress(bool showProgress)
{
    qDebug() << "";
    return m_DTwainCore->m_DTWAIN_ENTRYPOINT.DTWain_SetProgress(showProgress);
}
bool DTwainAPP::setStandardSize(uint StandardSize)
{
    qDebug() << "";
    return m_DTwainCore->m_DTWAIN_ENTRYPOINT.DTWain_SetStandardSize(StandardSize);
}
bool DTwainAPP::setFrame(bool FrameEnabled, double Left, double Top, double Right, double Bottom)
{
    qDebug() << "";
    return m_DTwainCore->m_DTWAIN_ENTRYPOINT.DTWain_SetFrame(FrameEnabled, Left,  Top,  Right,  Bottom);
}

bool DTwainAPP::setRotation(uint rota)
{
    qDebug() << "";
    return m_DTwainCore->m_DTWAIN_ENTRYPOINT.DTWain_SetRotation(rota);
}

bool DTwainAPP::setFeederEnabled(bool FeederEnabled)
{
    qDebug() << "";
    return m_DTwainCore->m_DTWAIN_ENTRYPOINT.DTWain_SetFeederEnabled(FeederEnabled);
}

bool DTwainAPP::doScanToFile(QString ALLFilePath)
{
    QFileInfo fileInfo(ALLFilePath);
    QDir dir;
    if (!dir.exists(fileInfo.absolutePath()))
    {
        if (!dir.mkpath(fileInfo.absolutePath()))
        {
            return false;
        }
    }
    wchar_t llist[512] = {0};
    ALLFilePath.toWCharArray(llist);
    bool ret = m_DTwainCore->m_DTWAIN_ENTRYPOINT.DTWain_DoScanToFile(llist);
    return ret;
}

bool DTwainAPP::doScanToDir(QString ALLFilePath, QString& aFileNameList, QString& aFilesCount)
{
    QFileInfo fileInfo(ALLFilePath);
    QDir dir;
    bool Rec;
    if (!dir.exists(fileInfo.absolutePath()))
    {
        if (!dir.mkpath(fileInfo.absolutePath()))
        {
            return false;
        }
    }
    wchar_t llist[512] = {0};
    wchar_t llistFileName[512] = {0};
    wchar_t FilesCount[512] = {0};
    ALLFilePath.toWCharArray(llist);
    aFileNameList.toWCharArray(llistFileName);
    aFilesCount.toWCharArray(FilesCount);
    Rec = m_DTwainCore->m_DTWAIN_ENTRYPOINT.DTWain_DoScanToDir(llist, llistFileName, FilesCount);
    aFileNameList = QString::fromWCharArray(llistFileName);
    aFilesCount = QString::fromWCharArray(FilesCount);
    return Rec;
}

void DTwainAPP::setCallBackFunShowOnePic(LP_Hx_ShowOnePicCallBackFun aShowOnePicCallBackFun)
{
    m_ShowOnePicCallBackFun = aShowOnePicCallBackFun;
}

bool DTwainAPP::setCallBackForScanToDir()
{
    qDebug() << "";
    if (m_ShowOnePicCallBackFun != nullptr)
    {
        qDebug() << "---setCallBackForScanToDir--1----";
        bool rec = m_DTwainCore->m_DTWAIN_ENTRYPOINT.DTWain_SetCallBackForScanToDir(m_ShowOnePicCallBackFun);
        if (!rec)
            QString msg =  "--setCallBackForScanToDir--2---status=" + rec ? "success" : "error";
        return rec;
    }
}

#ifndef DTWAINCORE_H
#define DTWAINCORE_H


#include <QObject>
#include <QGuiApplication>
#include <QMessageBox>
#include <QtDebug>
#include <QLibrary>
#include <QFileInfo>
#include <QDir>
#include "twain/twain.h"


typedef void (*LP_Hx_ShowOnePicCallBackFun)(int FileIndex);
typedef bool (*LP_DTWain_Init)();
typedef bool (*LP_DTWain_UnInit)(void);
typedef bool (*LP_DTWain_GetScanerList)(wchar_t* device_list);
typedef bool (*LP_DTWain_SetSelectedSource)(uint ASelectedSourceIndex);
typedef bool (*LP_DTWain_SetShowUI)(bool SetShowUI);
typedef bool (*LP_DTWain_SetDuplexEnabled)(bool SetDuplexEnabled);
typedef bool (*LP_DTWain_SetJPGQuality)(uint aiJPGQuality);
typedef bool (*LP_DTWain_SetBeforeSCanWaitingTime)(uint aiBeforeSCanWaitingTime);
typedef bool (*LP_DTWain_SetPixelType)(uint PixelType);
typedef bool (*LP_DTWain_SetDPI)(uint ADPI);
typedef bool (*LP_DTWain_SetProgress)(bool ShowProgress);
typedef bool (*LP_DTWain_SetStandardSize)(uint AStandardSizeType);
typedef bool (*LP_DTWain_SetFrame)(bool AFrameEnabled, double ALeft, double ATop, double ARight, double ABottom);
typedef bool (*LP_DTWain_SetRotation)(uint rota);
typedef bool (*LP_DTWain_SetFeederEnabled)(bool AFeederEnabled);
typedef bool (*LP_DTWain_DoScanToFile)(wchar_t* ALLFilePath); //平板扫
typedef bool (*LP_DTWain_DoScanToDir)(wchar_t* ALLFilePath, wchar_t* FileNameList, wchar_t* FilesCount); //高扫
typedef bool (*LP_DTWain_SetCallBackForScanToDir)(LP_Hx_ShowOnePicCallBackFun ShowOnePicCallBackFun);//高扫的回调函数



typedef struct
{
    LP_DTWain_Init      DTWain_Init = nullptr;
    LP_DTWain_UnInit      DTWain_UnInit = nullptr;
    LP_DTWain_GetScanerList   DTWain_GetScanerList = nullptr;
    LP_DTWain_SetSelectedSource       DTWain_SetSelectedSource = nullptr;
    LP_DTWain_SetShowUI       DTWain_SetShowUI = nullptr;
    LP_DTWain_SetDuplexEnabled       DTWain_SetDuplexEnabled = nullptr;
    LP_DTWain_SetJPGQuality       DTWain_SetJPGQuality = nullptr;
    LP_DTWain_SetBeforeSCanWaitingTime       DTWain_SetBeforeSCanWaitingTime = nullptr;
    LP_DTWain_SetPixelType     DTWain_SetPixelType = nullptr;
    LP_DTWain_SetDPI DTWain_SetDPI = nullptr;
    LP_DTWain_SetProgress DTWain_SetProgress = nullptr;
    LP_DTWain_SetStandardSize DTWain_SetStandardSize = nullptr;
    LP_DTWain_SetFrame DTWain_SetFrame = nullptr;
    LP_DTWain_SetRotation DTWain_SetRotation = nullptr;
    LP_DTWain_SetFeederEnabled DTWain_SetFeederEnabled = nullptr;
    LP_DTWain_DoScanToFile DTWain_DoScanToFile = nullptr; //平板扫
    LP_DTWain_DoScanToDir DTWain_DoScanToDir = nullptr; //高扫
    LP_DTWain_SetCallBackForScanToDir DTWain_SetCallBackForScanToDir = nullptr; //高扫的回调函数
} DTWAIN_ENTRYPOINT, *pDTWAIN_ENTRYPOINT;

class DTwainCore : public QObject
{
    Q_OBJECT
private:
    QLibrary lib;
public:
    DTwainCore();
    ~DTwainCore();
    bool Loadlib();
    bool Freelib();
    DTWAIN_ENTRYPOINT m_DTWAIN_ENTRYPOINT;
};


class DTwainAPP : public QObject
{
    Q_OBJECT
private:
    DTwainCore* m_DTwainCore;
private:
    DTwainAPP() {}
    DTwainAPP(const DTwainAPP& obj) = delete;
    DTwainAPP& operator=(const DTwainAPP* obj) = delete;
    static DTwainAPP* m_DToperation;
public:
    static DTwainAPP* getDTInstance();
    ~DTwainAPP();
    int m_device_list_count = 0;
    int m_State = 0;
    QStringList m_device_list;
    LP_Hx_ShowOnePicCallBackFun m_ShowOnePicCallBackFun;
    void initAPP();
    void exitAPP();
    void reInitAPP();
    bool get_device_list();
    int  get_device_list_count();
    bool setSelectedSource(uint Sourceindex);
    bool setShowUI(bool showUI = false);
    bool setDuplexEnabled(bool duplexEnabled);
    bool setJPGQuality(int aiJPGQuality);//图片损耗率 1到100
    bool setBeforeSCanWaitingTime(int aiBeforeSCanWaitingTime);//单位为毫秒，扫描之前的等待时间
    bool setPixelType(uint PixelType = TWPT_RGB);
    bool setDPI(uint DPI = 300);
    bool setProgress(bool showProgress = true);
    bool setStandardSize(uint StandardSize = TWSS_A4);
    bool setFrame(bool FrameEnabled, double Left, double Top, double Right, double Bottom);
    bool setRotation(uint rota = 0);
    bool setFeederEnabled(bool FeederEnabled = false);
    bool doScanToFile(QString ALLFilePath);//平板扫
    bool doScanToDir(QString ALLFilePath, QString& aFileNameList, QString& aFilesCount); //高扫
    void setCallBackFunShowOnePic(LP_Hx_ShowOnePicCallBackFun aShowOnePicCallBackFun);
    bool setCallBackForScanToDir();//高扫的回调函数
};

#endif // DTWAINCORE_H

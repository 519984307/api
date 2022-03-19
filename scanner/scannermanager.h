#ifndef SCANNERMANAGER_H
#define SCANNERMANAGER_H

#include <QObject>
#ifdef APP_WINDOWS_X64
#include "dtwaincore.h"
#include "scannerapp.h"
#else

#include "scannerapp.h"
#endif
#include <QWidget>
#include <QDateTime>
#include <QFileInfo>
#include <QUrl>
#include <QDesktopServices>
#include <QSettings>
#include <QDir>
#include <QtDebug>
#include <QUuid>
#include "sanecore.h"
#include <memory>
#include <QMessageBox>

using namespace std;
struct ScanInfo
{
    QString pathName;
    QString folder;
    int index;
   #ifndef APP_WINDOWS_X64
    SANE_Handle handle;
   #endif
};

class ScannerManager : public QObject
{
    Q_OBJECT
public:
    explicit ScannerManager(QObject* parent = nullptr);
    bool savConfig();
    void updateUI();
#ifdef APP_WINDOWS_X64
    DTwainAPP* operation = DTwainAPP::getDTInstance();
#else
    QList<SANE_Handle> scannerListHandle;
#endif
    int sc_DefaultScan_Index;//扫描仪列表 默认扫描仪序号
    bool sc_ShowUI;  //windows  是否显示自带扫描仪驱动界面
    bool sc_DuplexEnabled;//window false: 单面扫描  true: 双面扫描
    int sc_BeforeSCanWaitingTime = 0;//扫描图片之前等待时间
    bool sc_ScanType;//windows  扫描类型 false: 平板扫描 true: 高扫
    int sc_ColorSetting; //颜色设置
    int sc_DPI; //DPI
    int sc_JPGQuality; //JPG质量
    int sc_Orientation; //放纸方式
    int sc_Rotation; //旋转角度
    int sc_StandardSize; //页面尺寸
    int sc_StandardSizeW; //页面宽
    int sc_StandardSizeH; //页面高
    int sc_FrameSizeW; //框架宽
    int sc_FrameSizeH; //框架高
    int sr_BeforeSCanWaitingTime;
    QStringList m_listScannerNameFilters;//扫描仪白名单,对中晶、富士通扫描仪放行。
    bool m_boolEnabledScannerNameFilters; //扫描仪白名单: true: 启用限制。false: 不启用限制
    int getRand(int iValue);
    int getRandTimeForScannerWaiteDefault();
    void initScannerList();
    QStringList scannerList;
    static shared_ptr<ScannerManager> m_instance;
    void init();
    void startScan(ScanInfo& info);
    const QString& scanType() const;
    void setScanType(const QString& newScanType);

    int scannerIndex() const;
    void setScannerIndex(int newScannerIndex);

    bool showUI() const;
    void setShowUI(bool newShowUI);

    bool duplexEnabled() const;
    void setDuplexEnabled(bool newDuplexEnabled);
    void loadIniFile();
    void saveConfig(QString key, QVariant value);

    int rotation() const;
    void setRotation(int newRotation);

    int scanArea() const;
    void setScanArea(int newScanArea);

    int scanAreaWidth() const;
    void setScanAreaWidth(int newScanAreaWidth);

    int scanAreaHeight() const;
    void setScanAreaHeight(int newScanAreaHeight);

private slots:

#ifdef QT_SYSTEM_VERSION_ZAOZHUANG
    void on_u_comboBox_ScanArea_currentTextChanged(const QString& arg1);
#endif



private:

    QSettings*  m_ScannerIni = nullptr;
    QString m_scanType;
    int m_scannerIndex;
    bool m_showUI;
    bool m_duplexEnabled;
    int m_colorIndex;
    int m_orientation;
    QString m_orientationName;
    int m_rotation;
    int m_dpi;
    int m_jpgQuality;
    int m_scanArea;
    int m_scanAreaWidth;
    int m_scanAreaHeight;
    int m_waitTime;

};

ScannerManager* scannerManager();

#endif // SCANNERMANAGER_H

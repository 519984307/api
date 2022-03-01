#ifndef SCANNERCONFIG_H
#define SCANNERCONFIG_H
#ifdef QT_WIN
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
#include "dtwaincore.h"
namespace Ui
{
class ScannerConfig;
}

class ScannerConfig : public QWidget
{
    Q_OBJECT
public:
    explicit ScannerConfig(QWidget* parent = nullptr);
    ~ScannerConfig();
    bool savConfig();
    void updateUI();
#ifdef QT_WIN
    DTwainAPP* operation = DTwainAPP::getDTInstance();
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
private slots:
    void on_u_pushButton_ScanTest_clicked();
    void on_u_pushButton_SavConfig_clicked();
    void InitScannerList();
    void checkWriteIniFile();
    void loadIniFile();
    void on_u_comboBox_ScanArea_currentIndexChanged(const QString& arg1);
#ifdef QT_SYSTEM_VERSION_ZAOZHUANG
    void on_u_comboBox_ScanArea_currentTextChanged(const QString& arg1);
#endif
    void on_u_spinBox_DPI_valueChanged(int arg1);

private:
    Ui::ScannerConfig* ui;
    QSettings*  m_ScannerIni = nullptr;
};

//class ScannerAPP : public QObject
//{
//public:
//#ifdef WINNT
//    static DTwainAPP *m_ScannerCore;
//#else
//    static SaneAPP *m_ScannerCore;
//#endif
//    static void InitAPP();
////
//    static int sc_DefaultScan_Index;//扫描仪列表 默认扫描仪序号
//    static bool sc_ShowUI;  //windows  是否显示自带扫描仪驱动界面
//    static bool sc_ScanType;//windows  扫描类型 false: 平板扫描 true: 高扫
//    static int sc_ColorSetting; //颜色设置
//    static int sc_DPI; //DPI
//    static int sc_JPGQuality; //JPG质量
//    static int sc_Orientation; //放纸方式
//    static int sc_Rotation; //旋转角度
//    static int sc_StandardSize; //页面尺寸
//    static int sc_StandardSizeW; //页面宽
//    static int sc_StandardSizeH; //页面高
//    static int sc_FrameSizeW; //框架宽
//    static int sc_FrameSizeH; //框架高
//};
#endif
#endif // SCANNERCONFIG_H

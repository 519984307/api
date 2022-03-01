#ifndef SCANNERCONFIG_SANE_H
#define SCANNERCONFIG_SANE_H
#ifdef APP_WINDOWS_X64
#else
#include <QWidget>
#include <QDateTime>
#include <QFileInfo>
#include <QUrl>
#include <QDesktopServices>
#include <QSettings>
#include <QDir>
#include <QUuid>

#include "scanner.h"
#include "scanner_operation.h"

namespace Ui
{
class ScannerConfig_Sane;
}

class ScannerConfig_Sane : public QWidget
{
    Q_OBJECT
public:
    explicit ScannerConfig_Sane(QWidget* parent = nullptr);
    ~ScannerConfig_Sane();
    bool savConfig();
    void updateUI();
    void InitScannerList();
    void checkWriteIniFile();
    void loadIniFile();
    bool set_Color();
    bool set_DPI();
    bool set_ScanSource();
    bool set_PaperSize();
    bool setautoGemory();
    bool saveIniConfig();
    void setWidth_Height();
    bool set_bg_color_270EX();
    bool set_rotate();
    Scanner_Operation* operation = Scanner_Operation::getInstance();

    int sc_DefaultScan_Index;
    bool sc_ShowUI;
    bool sc_ScanType;
    bool sc_ScanSDType;
    int sc_ColorSetting;
    int sc_DPI;
    int sc_JPGQuality;
    int sc_Rotation;
    int sc_StandardSize;
    int sc_StandardSizeW;
    int sc_StandardSizeH;
    int sc_Orientation;
private slots:
    void on_u_pushButton_ScanTest_clicked();
    void on_u_pushButton_SavConfig_clicked();
    void on_u_comboBox_ScanArea_currentIndexChanged(const QString& arg1);
    void on_u_spinBox_DPI_valueChanged(int arg1);
    void on_u_comboBox_ScanArea_currentTextChanged(const QString& arg1);
    void on_u_comboBox_ScannerList_currentIndexChanged(const QString& arg1);
    void on_u_comboBox_Orientation_currentIndexChanged(const QString& arg1);

private:
    Ui::ScannerConfig_Sane* ui;
    QSettings*  m_ScannerIni = nullptr;

};

#endif // SCANNERCONFIG_H
#endif

#include "scannerconfig_sane.h"
#include "ui_scannerconfig_sane.h"
#ifdef APP_WINDOWS_X64
#else
#include <QMessageBox>
#include <QDebug>
#include <stdio.h>
#include <unistd.h>
#include "scanner_operation.h"
ScannerConfig_Sane::ScannerConfig_Sane(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::ScannerConfig_Sane)
{
    ui->setupUi(this);
    //加载扫描仪列表
//    QString jsonfile(QApplication::applicationDirPath() +"/configs/scanconfig.json");
//    operation->InitScanner(jsonfile);
    while (1)
    {
        if (!operation->init_status)
        {
            usleep(10);
        }
        else
        {
            break;
        }
    }
    InitScannerList();
    checkWriteIniFile();
    loadIniFile();
}

ScannerConfig_Sane::~ScannerConfig_Sane()
{
    delete ui;
}

void ScannerConfig_Sane::on_u_pushButton_ScanTest_clicked()
{
    QString lAllFileDir =  qApp->applicationDirPath() + "/scantmp/";
    QString lAllFilePath =  lAllFileDir + QUuid::createUuid().toString(QUuid::WithoutBraces) + ".jpg";
    qDebug() << "lAllFilePath :" << lAllFilePath << "lAllFileDir:" << lAllFileDir << endl;
    if (!sc_ScanType)
    {
        if (operation->doScanToFile(operation->scannerlist[sc_DefaultScan_Index]->get_saneHandle(), lAllFilePath))
        {
            if (QFileInfo::exists(lAllFilePath))
            {
                QDesktopServices::openUrl(QUrl("file:///" + lAllFileDir));
                QDesktopServices::openUrl(QUrl("file:///" + lAllFilePath));
            }
            else
            {
                QMessageBox::information(this, "提示", "图片不存在");
            }
        }
        else
        {
            QMessageBox::information(this, "提示", "扫描失败，请重试");
        }
    }
    else
    {
        //测试高扫
        QStringList lListFileName;
        QString FilesCount;
        int index, iPicCount;
        if (operation->doScanToDir_Test(operation->scannerlist[sc_DefaultScan_Index]->get_saneHandle(), lAllFileDir, lListFileName, FilesCount))
        {
            iPicCount = FilesCount.toInt();
            qDebug() << "iPicCount :" << iPicCount << endl;
            for (index = 0; index < iPicCount; index ++)
            {
                lAllFilePath = lListFileName.at(index);
                if (QFileInfo::exists(lAllFilePath))
                {
                    QDesktopServices::openUrl(QUrl("file:///" + lAllFileDir));
                    QDesktopServices::openUrl(QUrl("file:///" + lAllFilePath));
                }
                else
                {
                    QMessageBox::information(this, "提示", "高扫 图片不存在" + lAllFilePath);
                }
            }
        }
        else
        {
            QMessageBox::information(this, "提示", "高扫 扫描失败，请重试");
        }
    }
}

void ScannerConfig_Sane::on_u_pushButton_SavConfig_clicked()
{
    if (this->savConfig())
    {
        QMessageBox::information(this, "提示", "扫描仪参数设置成功!");
    }
    else
    {
        QMessageBox::information(this, "提示", "扫描仪参数设置失败,请重新尝试设置直到成功过，否则无效!");
    }
}


void ScannerConfig_Sane::InitScannerList()
{
    for (int i = 0; i < operation->scanner_count; i++)
    {
        ui->u_comboBox_ScannerList->addItem(operation->scannerlist[i]->get_scanner_name());
    }
}

void ScannerConfig_Sane::checkWriteIniFile()
{
    qDebug() << "checkWriteIniFile" << endl;
    QString configAllFilePath = QGuiApplication::applicationDirPath() + "/configs/canner.ini";
    //没有检测到先写一遍默认值
    if (!QFile::exists(configAllFilePath))
    {
        qDebug() << "don't have canner.ini" << endl;
        QSettings*  lini = new QSettings(configAllFilePath, QSettings::IniFormat);
        lini->setIniCodec("UTF8");
        lini ->beginGroup("canner");//功能
        lini->setValue("DefaultScan_Index",  sc_DefaultScan_Index);//扫描仪列表 默认扫描仪序号
        lini->setValue("ShowUI",  sc_ShowUI);  //扫描仪自带界面
        lini->setValue("ScanType", sc_ScanType); //扫描来源 1=高扫 0=平板
        lini->setValue("ScanSDType", sc_ScanSDType); //单双面选择  0-单面 1-双面
        lini->setValue("ColorSetting",  sc_ColorSetting);  //颜色设置
        lini->setValue("DPI",  sc_DPI);  //页面尺寸
        lini->setValue("JPGQuality", sc_JPGQuality);
        lini->setValue("Orientation", sc_Orientation); //放纸方式
        lini->setValue("Rotation", sc_Rotation); //旋转角度
        lini->setValue("StandardSize",  sc_StandardSize);  //页面尺寸
        lini->setValue("StandardSizeW",  sc_StandardSizeW);  //自定义时的宽
        lini->setValue("StandardSizeH",  sc_StandardSizeH);  //自定义时的高
        lini->endGroup();
    };
}

void ScannerConfig_Sane::loadIniFile()
{
    QString configAllFilePath = QGuiApplication::applicationDirPath() + "/configs/canner.ini";
    if (QFile::exists(configAllFilePath))
    {
        qDebug() << "loadIniFile canner.ini exists" << endl;
        QSettings*  lini = new QSettings(configAllFilePath, QSettings::IniFormat);
        lini->setIniCodec("UTF8");
        lini ->beginGroup("canner");//功能
        sc_DefaultScan_Index = lini->value("DefaultScan_Index",  -1).toInt();//扫描仪列表 默认扫描仪序号
        sc_ShowUI = lini->value("ShowUI",  false).toBool();  //扫描仪自带界面
        sc_ScanType = lini->value("ScanType",  false).toBool();  //扫描类型
        sc_ScanSDType = lini->value("ScanSDType", false).toBool(); //单双面扫描
        sc_ColorSetting = lini->value("ColorSetting",  2).toInt();  //颜色设置
        sc_DPI = lini->value("DPI",  300).toInt(); //页面尺寸
        sc_JPGQuality = lini->value("JPGQuality", 100).toInt();
        sc_Orientation = lini->value("Orientation", 0).toInt(); //放纸方式
        sc_Rotation = lini->value("Rotation", 0).toInt(); //旋转角度
        sc_StandardSize = lini->value("StandardSize",  1).toInt();  //页面尺寸
        sc_StandardSizeW = lini->value("StandardSizeW",  2478).toInt();  //自定义时的宽
        sc_StandardSizeH = lini->value("StandardSizeH",  3510).toInt();  //自定义时的高
        lini->endGroup();
        updateUI();
    };
}

void ScannerConfig_Sane::updateUI()
{
    if (ui->u_comboBox_ScannerList->count() > 0)
    {
        ui->u_comboBox_ScannerList->setCurrentIndex(sc_DefaultScan_Index);
    }
    if (sc_ShowUI)
    {
        ui->u_comboBox_ShowUI->setCurrentIndex(1);
    }
    else
    {
        ui->u_comboBox_ShowUI->setCurrentIndex(0);
    }
    if (sc_ScanType)
    {
        ui->cbbScanType->setCurrentIndex(1);
    }
    else
    {
        ui->cbbScanType->setCurrentIndex(0);
    }
    if (sc_ScanSDType)
    {
        ui->cbbScanSD->setCurrentIndex(1);
    }
    else
    {
        ui->cbbScanSD->setCurrentIndex(0);
    }
    ui->u_comboBox_ColorSetting->setCurrentIndex(sc_ColorSetting);
    ui->u_spinBox_DPI->setValue(sc_DPI);
    ui->u_spinBox_JPGQuality->setValue(sc_JPGQuality);
    ui->u_comboBox_Orientation->setCurrentIndex(sc_Orientation);
    ui->u_comboBox_Rotation->setCurrentIndex(sc_Rotation);
    ui->u_comboBox_ScanArea->setCurrentIndex(sc_StandardSize);
    if (ui->u_comboBox_ScanArea->currentIndex() == (ui->u_comboBox_ScanArea->count() - 1))
    {
        ui->u_doubleSpinBox_ScanArea_Width->setValue(sc_StandardSizeW);
        ui->u_doubleSpinBox_ScanArea_Height->setValue(sc_StandardSizeH);
    }
    else
    {
        on_u_comboBox_ScanArea_currentIndexChanged(ui->u_comboBox_ScanArea->currentText());
    }
}
void get_ZC8860_Gamma(SANE_String lSANE_String, SANE_Fixed& lFramel_fixed, SANE_Fixed& lFramet_fixed, SANE_Fixed& lFrameW_fixed, SANE_Fixed& lFrameH_fixed, int type)
{
    if (strcmp(lSANE_String, "A4") == 0)
    {
        lFramel_fixed = 65536 * (216 - 210) / 2;
        lFramet_fixed = 65536 * 0;
        if (type == 0)
        {
            lFrameW_fixed = 65536 * 210;
            lFrameH_fixed = 65536 * 297;
        }
        else if (type == 1)
        {
            lFrameW_fixed = 65536 * 297;
            lFrameH_fixed = 65536 * 210;
        }
    }
    else if (strcmp(lSANE_String, "A5") == 0)
    {
        lFramel_fixed = 65536 * (216 - 210) / 2;
        lFramet_fixed = 65536 * 0;
        if (type == 0)
        {
            lFrameW_fixed = 65536 * 148;
            lFrameH_fixed = 65536 * 210;
        }
        else if (type == 1)
        {
            lFrameW_fixed = 65536 * 210;
            lFrameH_fixed = 65536 * 148;
        }
    }
    else if (strcmp(lSANE_String, "A6") == 0)
    {
        lFramel_fixed = 65536 * (216 - 210) / 2;
        lFramet_fixed = 65536 * 0;
        if (type == 0)
        {
            lFrameW_fixed = 65536 * 105;
            lFrameH_fixed = 65536 * 148;
        }
        else if (type == 1)
        {
            lFrameW_fixed = 65536 * 148;
            lFrameH_fixed = 65536 * 105;
        }
    }
    else if (strcmp(lSANE_String, "B5") == 0)
    {
        lFramel_fixed = 65536 * (216 - 176) / 2;
        lFramet_fixed = 65536 * 0;
        if (type == 0)
        {
            lFrameW_fixed = 65536 * 17.6;
            lFrameH_fixed = 65536 * 25.0;
        }
        else if (type == 1)
        {
            lFrameW_fixed = 65536 * 25.0;
            lFrameH_fixed = 65536 * 17.6;
        }
    }
    else if (strcmp(lSANE_String, "Letter") == 0)
    {
        lFramel_fixed = 65536 * 0;
        lFramet_fixed = 65536 * 0;
        if (type == 0)
        {
            lFrameW_fixed = 65536 * 21.6;
            lFrameH_fixed = 65536 * 27.9;
        }
        else if (type == 1)
        {
            lFrameW_fixed = 65536 * 27.9;
            lFrameH_fixed = 65536 * 21.6;
        }
    }
    else if (strcmp(lSANE_String, "Legal") == 0)
    {
        lFramel_fixed = 65536 * 0;
        lFramet_fixed = 65536 * 0;
        if (type == 0)
        {
            lFrameW_fixed = 65536 * 21.6;
            lFrameH_fixed = 65536 * 35.6;
        }
        else if (type == 1)
        {
            lFrameW_fixed = 65536 * 35.6;
            lFrameH_fixed = 65536 * 21.6;
        }
    }
}

void get_XT7000_Gamma(SANE_String lSANE_String, SANE_Fixed& lFramel_fixed, SANE_Fixed& lFramet_fixed, SANE_Fixed& lFrameW_fixed, SANE_Fixed& lFrameH_fixed, int type)
{
    if (strcmp(lSANE_String, "A3") == 0)
    {
        lFramel_fixed = 65536 * (305 - 297) / 2;
        lFramet_fixed = 65536 * 0;
        lFrameW_fixed = 65536 * 297;
        lFrameH_fixed = 65536 * 420;

    }
    else if (strcmp(lSANE_String, "A4") == 0)
    {
        lFramel_fixed = 65536 * (305 - 210) / 2;
        lFramet_fixed = 65536 * 0;
        if (type == 0)
        {
            lFrameW_fixed = 65536 * 210;
            lFrameH_fixed = 65536 * 297;
        }
        else if (type == 1)
        {
            lFrameW_fixed = 65536 * 297;
            lFrameH_fixed = 65536 * 210;
        }
    }
    else if (strcmp(lSANE_String, "A5") == 0)
    {
        lFramel_fixed = 65536 * (305 - 210) / 2;
        lFramet_fixed = 65536 * 0;
        if (type == 0)
        {
            lFrameW_fixed = 65536 * 148;
            lFrameH_fixed = 65536 * 210;
        }
        else if (type == 1)
        {
            lFrameW_fixed = 65536 * 210;
            lFrameH_fixed = 65536 * 148;
        }

    }
    else if (strcmp(lSANE_String, "A6") == 0)
    {
        lFramel_fixed = 65536 * (305 - 210) / 2;
        lFramet_fixed = 65536 * 0;
        if (type == 0)
        {
            lFrameW_fixed = 65536 * 105;
            lFrameH_fixed = 65536 * 148;
        }
        else if (type == 1)
        {
            lFrameW_fixed = 65536 * 148;
            lFrameH_fixed = 65536 * 105;
        }
    }
    else if (strcmp(lSANE_String, "B5") == 0)
    {
        lFramel_fixed = 65536 * (305 - 176) / 2;
        lFramet_fixed = 65536 * 0;
        if (type == 0)
        {
            lFrameW_fixed = 65536 * 17.6;
            lFrameH_fixed = 65536 * 25.0;
        }
        else if (type == 1)
        {
            lFrameW_fixed = 65536 * 25.0;
            lFrameH_fixed = 65536 * 17.6;
        }
    }
    else if (strcmp(lSANE_String, "Letter") == 0)
    {
        lFramel_fixed = 65536 * 0;
        lFramet_fixed = 65536 * 0;
        if (type == 0)
        {
            lFrameW_fixed = 65536 * 21.6;
            lFrameH_fixed = 65536 * 27.9;
        }
        else if (type == 1)
        {
            lFrameW_fixed = 65536 * 27.9;
            lFrameH_fixed = 65536 * 21.6;
        }
    }
    else if (strcmp(lSANE_String, "Legal") == 0)
    {
        lFramel_fixed = 65536 * 0;
        lFramet_fixed = 65536 * 0;
        if (type == 0)
        {
            lFrameW_fixed = 65536 * 21.6;
            lFrameH_fixed = 65536 * 35.6;
        }
        else if (type == 1)
        {
            lFrameW_fixed = 65536 * 35.6;
            lFrameH_fixed = 65536 * 21.6;
        }
    }
}
void get_YINGYUAN_Gamma(SANE_String lSANE_String, SANE_Fixed& lFramel_fixed, SANE_Fixed& lFramet_fixed, SANE_Fixed& lFrameW_fixed, SANE_Fixed& lFrameH_fixed, int type)
{
    if (strcmp(lSANE_String, "A3") == 0)
    {
        lFramel_fixed = 65536 * 0.1;
        lFramet_fixed = 65536 * 0;
        lFrameW_fixed = 65536 * 297;
        lFrameH_fixed = 65536 * 420;
    }
    else if (strcmp(lSANE_String, "A4") == 0)
    {
        lFramel_fixed = 65536 * 0.1;
        lFramet_fixed = 65536 * 0;
        if (type == 0)
        {
            lFrameW_fixed = 65536 * 210;
            lFrameH_fixed = 65536 * 297;
        }
        else if (type == 1)
        {
            lFrameW_fixed = 65536 * 297;
            lFrameH_fixed = 65536 * 210;
        }
    }
    else if (strcmp(lSANE_String, "A5") == 0)
    {
        lFramel_fixed = 65536 * 0.1;
        lFramet_fixed = 65536 * 0;
        if (type == 0)
        {
            lFrameW_fixed = 65536 * 148;
            lFrameH_fixed = 65536 * 210;
        }
        else if (type == 1)
        {
            lFrameW_fixed = 65536 * 210;
            lFrameH_fixed = 65536 * 148;
        }
    }
    else if (strcmp(lSANE_String, "A6") == 0)
    {
        lFramel_fixed = 65536 * 0.1;
        lFramet_fixed = 65536 * 0;
        if (type == 0)
        {
            lFrameW_fixed = 65536 * 105;
            lFrameH_fixed = 65536 * 148;
        }
        else if (type == 1)
        {
            lFrameW_fixed = 65536 * 148;
            lFrameH_fixed = 65536 * 105;
        }
    }
    else if (strcmp(lSANE_String, "B5") == 0)
    {
        lFramel_fixed = 65536 * 0.1;
        lFramet_fixed = 65536 * 0;
        if (type == 0)
        {
            lFrameW_fixed = 65536 * 17.6;
            lFrameH_fixed = 65536 * 25.0;
        }
        else if (type == 1)
        {
            lFrameW_fixed = 65536 * 25.0;
            lFrameH_fixed = 65536 * 17.6;
        }
    }
    else if (strcmp(lSANE_String, "Letter") == 0)
    {
        lFramel_fixed = 65536 * 0;
        lFramet_fixed = 65536 * 0;
        if (type == 0)
        {
            lFrameW_fixed = 65536 * 21.6;
            lFrameH_fixed = 65536 * 27.9;
        }
        else if (type == 1)
        {
            lFrameW_fixed = 65536 * 27.9;
            lFrameH_fixed = 65536 * 21.6;
        }
    }
    else if (strcmp(lSANE_String, "Legal") == 0)
    {
        lFramel_fixed = 65536 * 0;
        lFramet_fixed = 65536 * 0;
        if (type == 0)
        {
            lFrameW_fixed = 65536 * 21.6;
            lFrameH_fixed = 65536 * 35.6;
        }
        else if (type == 1)
        {
            lFrameW_fixed = 65536 * 35.6;
            lFrameH_fixed = 65536 * 21.6;
        }
    }
}

bool ScannerConfig_Sane::set_Color()
{
    //颜色设置
    SANE_String lSANE_String = new char[32];

    switch (ui->u_comboBox_ColorSetting->currentIndex())
    {
    case 0:
    {
        strcpy(lSANE_String, "Lineart");
        break;
    }
    case 1:
    {
        strcpy(lSANE_String, "Gray");
        break;
    }
    case 2:
    {
        strcpy(lSANE_String, "Color");
        break;
    }
    }

    if (!operation->set_color_option(operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_saneHandle(), \
                                     operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_color_optionID(), lSANE_String))
    {
        return false;
    }
    return true;
    qDebug() << "save color sucess" << endl;
}

bool ScannerConfig_Sane::set_DPI()
{
    if (operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_scanner_name() == "ZC8860" ||
        operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_scanner_name() == "Microtek XT-7000 highspeed")
    {
        SANE_Fixed dpivalue = 65536 * (static_cast<SANE_Int>(ui->u_spinBox_DPI->value()));
        qDebug() << "dpivalue :" << dpivalue << endl;
        if (!operation->set_DPI_option_byte(operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_saneHandle(), \
                                            operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_dpi_optionID(), dpivalue))
        {
            return false;
        }
    }
    else
    {
        //WinMage GL3000
        SANE_Int dpivalue = static_cast<SANE_Int>(ui->u_spinBox_DPI->value());
        if (!operation->set_DPI_option(operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_saneHandle(), \
                                       operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_dpi_optionID(), dpivalue))
        {
            return false;
        }
    }
    return true;
}

bool ScannerConfig_Sane::set_ScanSource()
{
    SANE_String lSANE_String = new char[32];

    if (operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_scanner_name() == "Microtek XT-7000 highspeed" ||
        operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_scanner_name() == "WinMage GL3000")
    {
        ui->cbbScanSD->setCurrentIndex(0);
        ui->cbbScanType->setCurrentIndex(0);
    }
    else
    {
        //扫描来源 平板  高扫
        switch (ui->cbbScanType->currentIndex())
        {
        case 0:
            qDebug() << "设置为平板扫描" << endl;
            strcpy(lSANE_String, operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_flatedName());
            break;
        case 1:
            qDebug() << "设置为高速扫描" << endl;
            if (ui->cbbScanSD->currentIndex() == 0)
            {
                strcpy(lSANE_String, operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_adfName()); //ADFAutomatic Document Feeder
            }
            else if (ui->cbbScanSD->currentIndex() == 1)
            {
                qDebug() << "get_adfDuplexName is" << operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_adfDuplexName() << endl;
                strcpy(lSANE_String, operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_adfDuplexName());
            }
            break;
        }

        if (!operation->set_source(operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_saneHandle(), \
                                   operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_selectFAID(), lSANE_String))
        {
            return false;
        }

        switch (ui->cbbScanSD->currentIndex())
        {
        case 0:
            qDebug() << "设置为单面扫描" << endl;
            break;
        case 1:
            if (ui->cbbScanType->currentIndex() == 1)
            {
                qDebug() << "设置为双面扫描" << endl;
            }
            else
            {
                ui->cbbScanSD->setCurrentIndex(0);
            }
            break;
        }

        if (ui->cbbScanType->currentIndex() == 1 && operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_batchscanID() != SANE_Int(-1))
        {
            SANE_Int batch_scan = SANE_Int(1);
            if (!operation->set_batchscan(operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_saneHandle(), \
                                          operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_batchscanID(), batch_scan))
            {
                qDebug() << "set_batchscan() failed" << endl;
            }
            else
            {
                qDebug() << "set_batchscan() sucess" << endl;
            }
        }
    }
    return true;
}

bool ScannerConfig_Sane::set_PaperSize()
{
    SANE_String lSANE_String = new char[32];
    switch (ui->u_comboBox_ScanArea->currentIndex())
    {
    //A3
    case 0:
    {
        strcpy(lSANE_String, "A3");
        break;
    }
    //A4
    case 1:
    {
        strcpy(lSANE_String, "A4");
        break;
    }
    //A5
    case 2:
    {
        strcpy(lSANE_String, "A5");
        break;
    }
    //A6
    case 3:
    {
        strcpy(lSANE_String, "A6");
        break;
    }
    //B5
    case 4:
    {
        strcpy(lSANE_String, "B5");
        break;
    }
    //Letter
    case 5:
    {
        strcpy(lSANE_String, "Letter");
        break;
    }
    //Legal
    case 6:
    {
        strcpy(lSANE_String, "Legal");
        break;
    }
    default:
    {
        break;
    }
    }
    if (operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_scanner_name() == "ZC8860" ||
        operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_scanner_name() == "Microtek XT-7000 highspeed" ||
        operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_scanner_name() == "WinMage GL3000" ||
        operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_scanner_name() == "WinMage X270E+")
    {
        SANE_Fixed lFramel_fixed;
        SANE_Fixed lFramet_fixed;
        SANE_Fixed lFrameW_fixed;
        SANE_Fixed lFrameH_fixed;
        int type = ui->u_comboBox_Orientation->currentIndex();
        if (operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_scanner_name() == "ZC8860")
            get_ZC8860_Gamma(lSANE_String, lFramel_fixed, lFramet_fixed, lFrameW_fixed, lFrameH_fixed, type);
        else if (operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_scanner_name() == "Microtek XT-7000 highspeed")
            get_XT7000_Gamma(lSANE_String, lFramel_fixed, lFramet_fixed, lFrameW_fixed, lFrameH_fixed, type);
        else if (operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_scanner_name() == "WinMage GL3000" ||
                 operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_scanner_name() == "WinMage X270E+") //影源扫描仪
            get_YINGYUAN_Gamma(lSANE_String, lFramel_fixed, lFramet_fixed, lFrameW_fixed, lFrameH_fixed, type);

        if (operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_scanner_name() == "WinMage GL3000" ||
            operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_scanner_name() == "WinMage X270E+")
        {
            // 41
            SANE_Int autocrop;
            if (operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_scanner_name() == "WinMage GL3000")
                autocrop = 41;
            else
                autocrop = 42;
            SANE_Bool croptyep = false;
            if (!operation->set_autocropdeskew_enable(operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_saneHandle(), \
                                                      autocrop, croptyep))
            {
                return false;
            }
        }

        if (!operation->set_geometry_Fixed(operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_saneHandle(), \
                                           operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_tlxID(), lFramel_fixed))
        {
            return false;
        }
        if (!operation->set_geometry_Fixed(operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_saneHandle(), \
                                           operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_tlyID(), lFramet_fixed))
        {
            return false;
        }
        if (!operation->set_geometry_Fixed(operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_saneHandle(), \
                                           operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_brxID(), lFrameW_fixed))
        {
            return false;
        }

        if (!operation->set_geometry_Fixed(operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_saneHandle(), \
                                           operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_bryID(), lFrameH_fixed))
        {
            return false;
        }
    }
    else
    {
        if (!operation->set_papersize_option(operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_saneHandle(), \
                                             operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_papersize_optionID(), lSANE_String))
        {
            return false;
        }
    }
    return true;
}

bool ScannerConfig_Sane::set_rotate()
{
    SANE_String lSANE_String = new char[32];
    switch (ui->u_comboBox_Rotation->currentIndex())
    {
    case 0:
        strcpy(lSANE_String, "None");
        break;
    case 1:
        strcpy(lSANE_String, "90");
        break;
    case 2:
        strcpy(lSANE_String, "180");
        break;
    case 3:
        strcpy(lSANE_String, "270");
        break;
    }
    if (operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_scanner_name() == "WinMage X270E+")
    {
        if (!operation->set_rotate_option(operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_saneHandle(), SANE_Int(48), lSANE_String))
            return false;
    }else if (operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_scanner_name() == "WinMage GL3000")
    {
        if (!operation->set_rotate_option(operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_saneHandle(), SANE_Int(46), lSANE_String))
            return false;
    }else{
        return true;
    }
    return true;
}

bool ScannerConfig_Sane::setautoGemory()
{
    if (ui->u_comboBox_ScanArea->currentIndex() == ui->u_comboBox_ScanArea->count() - 1)
    {
        SANE_Int lFrame0 = 0;
        SANE_Int lFrameW = ui->u_doubleSpinBox_ScanArea_Width->text().toInt();
        SANE_Int lFrameH = ui->u_doubleSpinBox_ScanArea_Width->text().toInt();

        if (!operation->set_geometry(operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_saneHandle(), \
                                     operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_tlxID(), lFrame0))
        {
            return false;
        }
        if (!operation->set_geometry(operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_saneHandle(), \
                                     operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_tlyID(), lFrame0))
        {
            return false;
        }
        if (!operation->set_geometry(operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_saneHandle(), \
                                     operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_brxID(), lFrameW))
        {
            return false;
        }

        if (!operation->set_geometry(operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_saneHandle(), \
                                     operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_bryID(), lFrameH))
        {
            return false;
        }
    }
    return true;
}

bool ScannerConfig_Sane::saveIniConfig()
{
    QString configAllFilePath = QGuiApplication::applicationDirPath() +  "/configs/canner.ini";
    //没有检测到先写一遍默认值
    QSettings*  lini = new QSettings(configAllFilePath, QSettings::IniFormat);
    lini->setIniCodec("UTF8");
    lini ->beginGroup("canner");//功能
    lini->setValue("DefaultScan_Index", ui->u_comboBox_ScannerList->currentIndex());//扫描仪列表 默认扫描仪序号
    lini->setValue("ShowUI",  bool(ui->u_comboBox_ShowUI->currentText() == "启用")); //扫描仪自带界面
    lini->setValue("ScanType",  bool(ui->cbbScanType->currentText() == "高速扫描")); //扫描仪来源
    lini->setValue("ScanSDType", bool(ui->cbbScanSD->currentText() == "双面扫描")); //单双面扫描设置
    lini->setValue("ColorSetting",  ui->u_comboBox_ColorSetting->currentIndex());  //颜色设置
    lini->setValue("Orientation",  ui->u_comboBox_Orientation->currentIndex());  //放纸方式
    lini->setValue("Rotation",  ui->u_comboBox_Rotation->currentIndex());  //旋转角度
    lini->setValue("DPI",  ui->u_spinBox_DPI->value());  //页面尺寸
    lini->setValue("JPGQuality", ui->u_spinBox_JPGQuality->value());
    lini->setValue("StandardSize",  ui->u_comboBox_ScanArea->currentIndex());  //页面尺寸
    if (ui->u_comboBox_ScanArea->currentIndex() == (ui->u_comboBox_ScanArea->count() - 1))
    {
        lini->setValue("StandardSizeW",  ui->u_doubleSpinBox_ScanArea_Width->value());  //页面宽
        lini->setValue("StandardSizeH",  ui->u_doubleSpinBox_ScanArea_Height->value());  //页面高
    }
    lini->endGroup();
    loadIniFile();
    return true;
}

bool ScannerConfig_Sane::set_bg_color_270EX()
{
    //option 64
    SANE_String lSANE_String = new char[32];
    SANE_Int bg_color_option = 64;
    strcpy(lSANE_String, "White");

    if (!operation->set_bg_color_option(operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_saneHandle(), \
                                        bg_color_option, lSANE_String))
    {
        return false;
    }
    return true;
}

bool ScannerConfig_Sane::savConfig()
{
    if (ui->u_comboBox_ScannerList->currentIndex() < 0)
    {
        return false;
    }
    //颜色设置
    if (!set_Color())
        return false;
    //DPI分辨率
    if (!set_DPI())
        return false;
    //设置单双面和平板，高扫
    if (!set_ScanSource())
        return false;
    //页面尺寸
    if (!set_PaperSize())
        return false;
    // 框架尺寸
    if (ui->u_comboBox_ScanArea->currentIndex() == 7)
    {
        if (!setautoGemory())
            return false;
    }
    //设置旋转角度270E+ option:48  GL3000:46
    if (!set_rotate())
    {
        return false;
    }
    if (operation->scannerlist[ui->u_comboBox_ScannerList->currentIndex()]->get_scanner_name() == "WinMage X270E+")
    {
        set_bg_color_270EX();
    }
    saveIniConfig();
    return true;
}

void ScannerConfig_Sane::setWidth_Height()
{
    ui->u_doubleSpinBox_ScanArea_Width->setEnabled(false);
    ui->u_doubleSpinBox_ScanArea_Height->setEnabled(false);
    QString size = ui->u_comboBox_ScanArea->currentText();
    double width, height;
    if (size == "A3")
    {
        ui->u_comboBox_Orientation->setCurrentIndex(0);
        //直式
        width = double(2970);
        height = double(4200);
    }
    else if (size == "A4")
    {
        if (ui->u_comboBox_Orientation->currentIndex() == 0)
        {
            width = double(2100);
            height = double(2970);
        }
        else if (ui->u_comboBox_Orientation->currentIndex() == 1)
        {
            width = double(2970);
            height = double(2100);
        }
    }
    else if (size == "A5")
    {
        if (ui->u_comboBox_Orientation->currentIndex() == 0)
        {
            width = double(1480);
            height = double(2100);
        }
        else if (ui->u_comboBox_Orientation->currentIndex() == 1)
        {
            width = double(2100);
            height = double(1480);
        }
    }
    else if (size == "A6")
    {
        if (ui->u_comboBox_Orientation->currentIndex() == 0)
        {
            width = double(1050);
            height = double(1480);
        }
        else if (ui->u_comboBox_Orientation->currentIndex() == 1)
        {
            width = double(1480);
            height = double(1050);
        }
    }
    else if (size == "B5")
    {
        if (ui->u_comboBox_Orientation->currentIndex() == 0)
        {
            width = double(176);
            height = double(250);
        }
        else if (ui->u_comboBox_Orientation->currentIndex() == 1)
        {
            width = double(250);
            height = double(176);
        }
    }
    else if (size == "Letter")
    {
        if (ui->u_comboBox_Orientation->currentIndex() == 0)
        {
            width = double(216);
            height = double(279);
        }
        else if (ui->u_comboBox_Orientation->currentIndex() == 1)
        {
            width = double(279);
            height = double(216);
        }
    }
    else if (size == "Legal")
    {
        if (ui->u_comboBox_Orientation->currentIndex() == 0)
        {
            width = double(215.9);
            height = double(355.6);
        }
        else if (ui->u_comboBox_Orientation->currentIndex() == 1)
        {
            width = double(355.6);
            height = double(215.9);
        }
    }
    else if (size == "自定义")
    {
        if (ui->u_comboBox_Orientation->currentIndex() == 0)
        {
            width = double(2100);
            height = double(2970);
        }
        else if (ui->u_comboBox_Orientation->currentIndex() == 1)
        {
            width = double(2970);
            height = double(2100);
        }
        ui->u_doubleSpinBox_ScanArea_Width->setEnabled(true);
        ui->u_doubleSpinBox_ScanArea_Height->setEnabled(true);
    }
    ui->u_doubleSpinBox_ScanArea_Width->setValue(width);
    ui->u_doubleSpinBox_ScanArea_Height->setValue(height);
}
void ScannerConfig_Sane::on_u_comboBox_ScanArea_currentIndexChanged(const QString& arg1)
{
    //  DPI 300
    //    "0-A3" 0,0,3508 4961   11.7 16.6
    //    "0-A4"   0,0,2480,3508  8.26 11.7
    //    "1-A5"   0,0,1748,2480  5.82 8.26
    //    "2-A6"  0,0,1240,1748   4.13 5.82
    //    "3-B5"  0,0,2079,2953   6.93 9.84
    //    "4-Letter"  0,0,2550,3300  8.5 11
    //    "5-Legal" 0,0,2550,4200    11 14
    Q_UNUSED(arg1)
    setWidth_Height();
}

void ScannerConfig_Sane::on_u_spinBox_DPI_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    on_u_comboBox_ScanArea_currentIndexChanged(ui->u_comboBox_ScanArea->currentText());
}

void ScannerConfig_Sane::on_u_comboBox_ScanArea_currentTextChanged(const QString& arg1)
{
    if (arg1.trimmed() == "A3")
    {
        ui->u_comboBox_Orientation->setCurrentIndex(1);
    }
    else
    {
        ui->u_comboBox_Orientation->setCurrentIndex(0);
    }
}
//扫描仪改变可设置选项enable修改
void ScannerConfig_Sane::on_u_comboBox_ScannerList_currentIndexChanged(const QString& arg1)
{
    ui->cbbScanType->setCurrentIndex(0);
    ui->cbbScanType->setEnabled(true);
    ui->cbbScanSD->setCurrentIndex(0);
    ui->cbbScanSD->setEnabled(true);
    if (arg1 == "WinMage X270E+")
    {
        ui->cbbScanType->setCurrentIndex(0);
        ui->cbbScanType->setEnabled(false);
        ui->cbbScanSD->setCurrentIndex(0);
        ui->cbbScanSD->setEnabled(false);
    }
}

void ScannerConfig_Sane::on_u_comboBox_Orientation_currentIndexChanged(const QString& arg1)
{
    Q_UNUSED(arg1)
    setWidth_Height();
}
#endif


#include "scannerconfig.h"
#include "ui_scannerconfig.h"
#ifdef  QT_WIN
ScannerConfig::ScannerConfig(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::ScannerConfig)
{
    ui->setupUi(this);
    operation->initAPP();
    //加载扫描仪列表
    sc_DefaultScan_Index = -1; //扫描仪列表 默认扫描仪序号
    sc_ShowUI = false; //windows  是否显示自带扫描仪驱动界面
    sc_DuplexEnabled = false; //windows  false:单面扫描 true:双面扫描
    sc_BeforeSCanWaitingTime = 0;//扫描图片之前等待时间
    sc_ScanType = false; //windows  扫描类型 false: 平板扫描
    sc_ColorSetting = 2; //颜色设置
    sc_DPI = 300; //DPI
    sc_JPGQuality = 100; //JPG质量 图片损耗率
    sc_Orientation = 0; //放纸方式
    sc_Rotation = 0; //旋转角度
    sc_StandardSize = 1; //页面尺寸
    sc_StandardSizeW = 2478; //自定义时保存的页面宽
    sc_StandardSizeH = 3510; //自定义时保存的页面高
    m_listScannerNameFilters << "Microtek" << "PaperStream";//中晶："Microtek"; PaperStream: 富士通
    m_boolEnabledScannerNameFilters = false;//false：正式版本不要启用这个限制;true: 农发行项目上才启用这个限制
    ui->lblWaitingTime->setVisible(false);
    ui->u_spinBox_WaitingTime->setVisible(false);
    InitScannerList();
    checkWriteIniFile();
    loadIniFile();
}

ScannerConfig::~ScannerConfig()
{
    delete ui;
}

void ScannerConfig::on_u_pushButton_ScanTest_clicked()
{
    qDebug() << "on_u_pushButton_ScanTest_clicked" << endl;
    if (!(this->savConfig()))
    {
        QMessageBox::information(this, "提示", "扫描仪参数设置失败,请重新尝试设置直到成功过，否则无效!");
        return;
    }
#ifdef  QT_WIN
    QString lAllFileDir =  qApp->applicationDirPath() + "/scantmp/";
    QString lAllFilePath =  lAllFileDir + QUuid::createUuid().toString(QUuid::WithoutBraces) + ".jpg";
    if (ui->cbbScanType->currentText() == "平板扫描")
    {
        if (operation->doScanToFile(lAllFilePath))
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
        QString lListFileName, FilesCount;
        int index, iPicCount;
        if (operation->doScanToDir(lAllFilePath, lListFileName, FilesCount))
        {
            iPicCount = FilesCount.toInt();
            for (index = 0; index < iPicCount; index ++)
            {
                lAllFilePath = lAllFileDir + "00" + QString::number(index + 1) + ".jpg";
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
#endif
}

void ScannerConfig::on_u_pushButton_SavConfig_clicked()
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


void ScannerConfig::InitScannerList()
{
    ui->u_comboBox_ScannerList->clear();
#ifdef QT_WIN
    if (operation->get_device_list())
    {
        for (int i = 0; i < operation->m_device_list.count(); i++)
        {
            ui->u_comboBox_ScannerList->addItem(operation->m_device_list.at(i));
        }
    }
#endif
}

void ScannerConfig::checkWriteIniFile()
{
#if QT_WIN
    QString configAllFilePath = QGuiApplication::applicationDirPath() +  "/configs/canner.ini";
    //没有检测到先写一遍默认值
    if (!QFile::exists(configAllFilePath))
    {
        QSettings*  lini = new QSettings(configAllFilePath, QSettings::IniFormat);
        lini->setIniCodec("UTF8");
        lini ->beginGroup("canner");//功能
        lini->setValue("DefaultScan_Index",  sc_DefaultScan_Index);//扫描仪列表 默认扫描仪序号
        lini->setValue("ShowUI",  sc_ShowUI);  //扫描仪自带界面
        lini->setValue("DuplexEnabled",  sc_DuplexEnabled);  //false 单面扫描 true 双面扫描
        lini->setValue("WaitingTime", sc_BeforeSCanWaitingTime); //扫描之前等待时间
        lini->setValue("ScanType", sc_ScanType); //扫描类型
        lini->setValue("ColorSetting", sc_ColorSetting);  //颜色设置
        lini->setValue("DPI",  sc_DPI);  //页面尺寸
        lini->setValue("JPGQuality", sc_JPGQuality);
        lini->setValue("Orientation", sc_Orientation); //放纸方式
        lini->setValue("Rotation", sc_Rotation); //旋转角度
        lini->setValue("StandardSize",  sc_StandardSize);  //页面尺寸
        lini->setValue("StandardSizeW", sc_StandardSizeW);  //自定义时的宽
        lini->setValue("StandardSizeH",  sc_StandardSizeH);  //自定义时的高
        lini->endGroup();
    }
#endif
}

int ScannerConfig::getRand(int iValue)
{
    if (iValue == 0)
    {
        return 0;
    }
    QTime time;
    time = QTime::currentTime();
    qsrand(time.msec() + time.second() * 1000);
    int num = qrand() % iValue;
    return num;
}
int ScannerConfig::getRandTimeForScannerWaiteDefault()
{
    return  1000 * (getRand(3)  + 1);
}

void ScannerConfig::loadIniFile()
{
#if QT_WIN
    QString configAllFilePath = QGuiApplication::applicationDirPath() +  "/configs/canner.ini";
    if (QFile::exists(configAllFilePath))
    {
        QSettings*  lini = new QSettings(configAllFilePath, QSettings::IniFormat);
        lini->setIniCodec("UTF8");
        lini ->beginGroup("canner");//功能
        int iScannerWaiteDefault = 0;
        if (m_boolEnabledScannerNameFilters)
        {
            iScannerWaiteDefault = 5000;    //getRandTimeForScannerWaiteDefault();
        }
        qDebug() << "--iScannerWaiteDefault=--" + QString::number(iScannerWaiteDefault);
        sc_DefaultScan_Index = lini->value("DefaultScan_Index",  -1).toInt();//扫描仪列表 默认扫描仪序号
        sc_ShowUI = lini->value("ShowUI",  false).toBool();  //扫描仪自带界面
        sc_DuplexEnabled = lini->value("DuplexEnabled",  false).toBool();  //false 单面扫描 true 双面扫描
        sr_BeforeSCanWaitingTime = iScannerWaiteDefault; //lini->value("WaitingTime", iScannerWaiteDefault).toInt();  //扫描之前等待时间
        sc_ScanType = lini->value("ScanType",  false).toBool();  //扫描类型
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
    }
#endif
}


void ScannerConfig::updateUI()
{
#if QT_WIN
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
    if (sc_DuplexEnabled)
    {
        ui->u_comboBox_DuplexEnabled->setCurrentIndex(1);
    }
    else
    {
        ui->u_comboBox_DuplexEnabled->setCurrentIndex(0);
    }
    ui->u_spinBox_WaitingTime->setValue(sr_BeforeSCanWaitingTime);
    if (sc_ScanType)
    {
        ui->cbbScanType->setCurrentIndex(1);
    }
    else
    {
        ui->cbbScanType->setCurrentIndex(0);
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
#endif
}

bool ScannerConfig::savConfig()
{
#ifdef WINNT
    if (!operation->setSelectedSource(static_cast<uint>(ui->u_comboBox_ScannerList->currentIndex())))
    {
        return false;
    }
    //启动扫描仪界面
    bool lSHowUI = true;
    if (ui->u_comboBox_ShowUI->currentIndex() == 0)
    {
        lSHowUI = false;
    }
    if (!operation->setShowUI(lSHowUI))
    {
        return false;
    }
    //启动单面扫描、双面扫描
    bool lDuplexEnabled = true;
    if (ui->u_comboBox_DuplexEnabled->currentIndex() == 0)
    {
        lDuplexEnabled = false;
    }
    if (!operation->setDuplexEnabled(lDuplexEnabled))
    {
        return false;
    }
    //图片损耗率
    if (!operation->setJPGQuality(static_cast<uint>(ui->u_spinBox_JPGQuality->value())))
    {
        //        return false;  这个参数设置不上也不要影响其它参数的设置，不进行return
    }
    int iBeforeSCanWaitingTime = 0;
    if (ui->u_spinBox_WaitingTime->isVisible())
    {
        iBeforeSCanWaitingTime = ui->u_spinBox_WaitingTime->value();
    }
    else
    {
        if (m_boolEnabledScannerNameFilters)
        {
            iBeforeSCanWaitingTime = 5000;    //这个是提前写死。
        }
        else
        {
            iBeforeSCanWaitingTime = 0;
        }
    }
    if (m_boolEnabledScannerNameFilters)
    {
        QString curScannerName = ui->u_comboBox_ScannerList->currentText();
        for (int iForfilters = 0 ; iForfilters < m_listScannerNameFilters.count() - 1; iForfilters++)
        {
            QString ScannerNameFlag = m_listScannerNameFilters.at(iForfilters).trimmed().toLower();
            if (curScannerName.toLower().contains(ScannerNameFlag.toLower()))
            {
                iBeforeSCanWaitingTime = 0;//扫描前等待时间:白名单中的扫描仪，扫描之前的等待时间设置为0，即放行
                break;
            }
        }
        qDebug() << "--filtertimes=" + QString::number(iBeforeSCanWaitingTime);
        if (!operation->setBeforeSCanWaitingTime(static_cast<uint>(iBeforeSCanWaitingTime)))
        {
            //        return false; 这个参数设置不上也不要影响其它参数的设置，不进行return
        }
    }
    //颜色设置
    //  TWPT_RGB=2
    if (!operation->setPixelType(static_cast<uint>(ui->u_comboBox_ColorSetting->currentIndex())))
    {
        return false;
    }
    //DPI分辨率
    if (!operation->setDPI(static_cast<uint>(ui->u_spinBox_DPI->value())))
    {
        return false;
    }
    //扫描仪进度条
    if (operation->setProgress(true))
    {
        //        return false;
    }
    //扫描类型
    bool boolScanType;
    if (ui->cbbScanType->currentText() == "高速扫描")
    {
        boolScanType = true;  // 默认平板扫描
    }
    else
    {
        boolScanType = false;// 高速扫描
    }
    if (!operation->setFeederEnabled(boolScanType))
    {
        return false;
    }
    if (!operation->setStandardSize(TWSS_NONE))
    {
        return false;
    }
    //旋转角度
    if (!operation->setRotation(ui->u_comboBox_Rotation->currentText().toUInt()))
    {
        return false;
    }
    double lHeight;
    double lWidth;
    if (ui->u_comboBox_Orientation->currentText() == "横式")
    {
        lWidth = ui->u_doubleSpinBox_ScanArea_Width->value() / ui->u_spinBox_DPI->value();
        lHeight = ui->u_doubleSpinBox_ScanArea_Height->value() / ui->u_spinBox_DPI->value();
    }
    else
    {
        lHeight = ui->u_doubleSpinBox_ScanArea_Width->value() / ui->u_spinBox_DPI->value();
        lWidth = ui->u_doubleSpinBox_ScanArea_Height->value() / ui->u_spinBox_DPI->value();
    }
    if (!operation->setFrame(true, 0, 0, lWidth, lHeight))
    {
        return false;
    }
#endif
    QString configAllFilePath = QGuiApplication::applicationDirPath() +  "/configs/canner.ini";
    //没有检测到先写一遍默认值
    QSettings*  lini = new QSettings(configAllFilePath, QSettings::IniFormat);
    lini->setIniCodec("UTF8");
    lini ->beginGroup("canner");//功能
    lini->setValue("DefaultScan_Index", ui->u_comboBox_ScannerList->currentIndex());//扫描仪列表 默认扫描仪序号
    lini->setValue("ShowUI",  bool(ui->u_comboBox_ShowUI->currentText() == "启用")); //扫描仪自带界面
    lini->setValue("DuplexEnabled",  bool(ui->u_comboBox_DuplexEnabled->currentText() == "双面扫描")); //扫描仪自带界面
    lini->setValue("ScanType",  bool(ui->cbbScanType->currentText() == "高速扫描")); //扫描仪自带界面
    lini->setValue("ColorSetting",  ui->u_comboBox_ColorSetting->currentIndex());  //颜色设置
    lini->setValue("Orientation",  ui->u_comboBox_Orientation->currentIndex());  //放纸方式
    lini->setValue("Rotation",  ui->u_comboBox_Rotation->currentIndex());  //旋转角度
    lini->setValue("DPI",  ui->u_spinBox_DPI->value());  //页面尺寸
    lini->setValue("JPGQuality", ui->u_spinBox_JPGQuality->value());
    lini->setValue("StandardSize",  ui->u_comboBox_ScanArea->currentIndex());  //页面尺寸
    lini->setValue("StandardSizeW",  ui->u_doubleSpinBox_ScanArea_Width->value());  //页面宽
    lini->setValue("StandardSizeH",  ui->u_doubleSpinBox_ScanArea_Height->value());  //页面高
    lini->setValue("WaitingTime", ui->u_spinBox_WaitingTime->value());
    lini->endGroup();
    loadIniFile();
    return true;
}

void ScannerConfig::on_u_comboBox_ScanArea_currentIndexChanged(const QString& arg1)
{
    //  DPI 300
    //    "0-A3" 0,0,3508 4961   11.7 16.6
    //    "0-A4"   0,0,2480,3508  8.26 11.7
    //    "1-A5"   0,0,1748,2480  5.82 8.26
    //    "2-A6"  0,0,1240,1748   4.13 5.82
    //    "3-B5"  0,0,2079,2953   6.93 9.84
    //    "4-Letter"  0,0,2550,3300  8.5 11
    //    "5-Legal" 0,0,2550,4200    11 14
    int lDPI = ui->u_spinBox_DPI->value();
#ifdef WINNT
    ui->u_doubleSpinBox_ScanArea_Width->setEnabled(false);
    ui->u_doubleSpinBox_ScanArea_Height->setEnabled(false);
    if (arg1 == "自定义")
    {
        ui->u_doubleSpinBox_ScanArea_Width->setEnabled(true);
        ui->u_doubleSpinBox_ScanArea_Height->setEnabled(true);
        ui->u_doubleSpinBox_ScanArea_Width->setValue(sc_StandardSizeW);
        ui->u_doubleSpinBox_ScanArea_Height->setValue(sc_StandardSizeH);
    }
    else if (arg1 == "A3")
    {
        ui->u_doubleSpinBox_ScanArea_Width->setValue(11.7 * lDPI);
        ui->u_doubleSpinBox_ScanArea_Height->setValue(16.6 * lDPI);
    }
    else if (arg1 == "A4")
    {
        ui->u_doubleSpinBox_ScanArea_Width->setValue(8.26 * lDPI);
        ui->u_doubleSpinBox_ScanArea_Height->setValue(11.7 * lDPI);
    }
    else if (arg1 == "A5")
    {
        ui->u_doubleSpinBox_ScanArea_Width->setValue(5.82 * lDPI);
        ui->u_doubleSpinBox_ScanArea_Height->setValue(8.26 * lDPI);
    }
    else if (arg1 == "A6")
    {
        ui->u_doubleSpinBox_ScanArea_Width->setValue(4.13 * lDPI);
        ui->u_doubleSpinBox_ScanArea_Height->setValue(5.82 * lDPI);
    }
    else if (arg1 == "B5")
    {
        ui->u_doubleSpinBox_ScanArea_Width->setValue(6.93 * lDPI);
        ui->u_doubleSpinBox_ScanArea_Height->setValue(9.84 * lDPI);
    }
    else if (arg1 == "Letter")
    {
        ui->u_doubleSpinBox_ScanArea_Width->setValue(8.5 * lDPI);
        ui->u_doubleSpinBox_ScanArea_Height->setValue(11 * lDPI);
    }
    else if (arg1 == "Legal")
    {
        ui->u_doubleSpinBox_ScanArea_Width->setValue(11 * lDPI);
        ui->u_doubleSpinBox_ScanArea_Height->setValue(14 * lDPI);
    }
#else
#endif
}

#ifdef QT_SYSTEM_VERSION_ZAOZHUANG
void ScannerConfig::on_u_comboBox_ScanArea_currentTextChanged(const QString& arg1)
{
    //在枣庄扫描仪项目上发现的问题，选择纸张类型的时候，其实应该保存这个类型对应的横竖信息的，暂时先这样
#ifdef WINNT
    if (arg1.trimmed() == "A3")
    {
        ui->u_comboBox_Orientation->setCurrentIndex(1); //横式
    }
    else
    {
        ui->u_comboBox_Orientation->setCurrentIndex(0); //竖式
    }
#else
#endif
}
#endif

void ScannerConfig::on_u_spinBox_DPI_valueChanged(int arg1)
{
    Q_UNUSED(arg1)
    on_u_comboBox_ScanArea_currentIndexChanged(ui->u_comboBox_ScanArea->currentText());
}

#endif


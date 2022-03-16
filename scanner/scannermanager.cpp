#include "scannermanager.h"

shared_ptr<ScannerManager> ScannerManager::m_instance = nullptr;
ScannerManager::ScannerManager(QObject* parent) : QObject(parent)
{

    ScannerApp::InitAPP();
    //加载扫描仪列表
    m_scannerIndex = 0; //扫描仪列表 默认扫描仪序号
    m_showUI = false; //windows  是否显示自带扫描仪驱动界面
    m_duplexEnabled = false; //windows  false:单面扫描 true:双面扫描
    m_waitTime = 0;//扫描图片之前等待时间
    m_scanType = "平板扫描"; //windows  扫描类型 false: 平板扫描
    m_colorIndex = 2; //颜色设置
    m_dpi = 300; //DPI
    m_jpgQuality = 100; //JPG质量 图片损耗率
    m_orientation = 0; //放纸方式
    m_rotation = 0; //旋转角度
    sc_StandardSize = 1; //页面尺寸
    m_scanAreaWidth = 2478; //自定义时保存的页面宽
    m_scanAreaHeight = 3510; //自定义时保存的页面高
    m_listScannerNameFilters << "Microtek" << "PaperStream";//中晶："Microtek"; PaperStream: 富士通
    m_boolEnabledScannerNameFilters = false;//false：正式版本不要启用这个限制;true: 农发行项目上才启用这个限制
//    ui->lblWaitingTime->setVisible(false);
//    ui->u_spinBox_WaitingTime->setVisible(false);
    initScannerList();
//    checkWriteIniFile();
    loadIniFile();


}

bool ScannerManager::savConfig()
{
#ifdef APP_WINDOWS_X64
    if (!operation->setSelectedSource(static_cast<uint>(m_scannerIndex)))
    {
        return false;
    }
    //启动扫描仪界面
    if (!operation->setShowUI(m_showUI))
    {
        return false;
    }
    //启动单面扫描、双面扫描
    if (!operation->setDuplexEnabled(m_duplexEnabled))
    {
        return false;
    }
    //图片损耗率
    if (!operation->setJPGQuality(m_jpgQuality))
    {
        //        return false;  这个参数设置不上也不要影响其它参数的设置，不进行return
    }
//    int iBeforeSCanWaitingTime = 0;
//    if (m_waitTime!=0)
//    {
//        iBeforeSCanWaitingTime = ui->u_spinBox_WaitingTime->value();
//    }
//    else
//    {
//        if (m_boolEnabledScannerNameFilters)
//        {
//            iBeforeSCanWaitingTime = 5000;    //这个是提前写死。
//        }
//        else
//        {
//            iBeforeSCanWaitingTime = 0;
//        }
//    }

//颜色设置
//  TWPT_RGB=2
    if (!operation->setPixelType(m_colorIndex))
    {
        return false;
    }
//DPI分辨率
    if (!operation->setDPI(m_dpi))
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
    if (m_scanType == "平板扫描")
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
    if (!operation->setStandardSize(m_scanArea))
    {
        return false;
    }
//旋转角度
    if (!operation->setRotation(m_rotation))
    {
        return false;
    }
    double lHeight;
    double lWidth;
    if (m_orientationName == "横式")
    {
        lWidth = m_scanAreaWidth / m_dpi;
        lHeight = m_scanAreaHeight / m_dpi;
    }
    else
    {
        lHeight = m_scanAreaWidth / m_dpi;
        lWidth = m_scanAreaHeight / m_dpi;
    }
    if (!operation->setFrame(m_scanArea == TWSS_NONE, 0, 0, lWidth, lHeight))
    {
        return false;
    }
#endif
    QString configAllFilePath = QGuiApplication::applicationDirPath() +  "/configs/scanner.ini";
    //没有检测到先写一遍默认值
    QSettings*  lini = new QSettings(configAllFilePath, QSettings::IniFormat);
    lini->setIniCodec("UTF8");
    lini ->beginGroup("canner");//功能
    lini->setValue("DefaultScan_Index", m_scannerIndex);//扫描仪列表 默认扫描仪序号
    lini->setValue("ShowUI",  m_showUI); //扫描仪自带界面
    lini->setValue("DuplexEnabled",  m_duplexEnabled); //扫描仪自带界面
    lini->setValue("ScanType",  m_scanType); //扫描仪自带界面
    lini->setValue("ColorSetting", m_colorIndex);  //颜色设置
    lini->setValue("Orientation",  m_orientation);  //放纸方式
    lini->setValue("Rotation",  m_rotation);  //旋转角度
    lini->setValue("DPI",  m_dpi);  //页面尺寸
    lini->setValue("JPGQuality", m_jpgQuality);
    lini->setValue("StandardSize",  m_scanArea);  //页面尺寸
    lini->setValue("StandardSizeW",  m_scanAreaWidth);  //页面宽
    lini->setValue("StandardSizeH",  m_scanAreaHeight);  //页面高
    lini->setValue("WaitingTime", m_waitTime);
    lini->endGroup();
    loadIniFile();
    return true;
}

void ScannerManager::initScannerList()
{
    scannerList.clear();
#ifdef APP_WINDOWS_X64
    if (operation->get_device_list())
    {
        for (int i = 0; i < operation->m_device_list.count(); i++)
        {
            scannerList << operation->m_device_list.at(i);
        }
    }


#else
    if (scannerList.count() > 0)
    {
        return;
    }
    SANE_Status lSANE_Status;
    const SANE_Device** devices = nullptr;
    lSANE_Status = sane_get_devices(&devices, SANE_TRUE);//返回本地直连设备
    if (SANE_STATUS_GOOD != lSANE_Status)
    {
        return;
    }
    int scanner_count = 0;
    for (int i = 0;; i++)
    {
        if (devices[i] == nullptr)
        {
            break;
        }
        else
        {
            scanner_count++;
        }
    }
    qDebug() << "scanner_count is " << scanner_count << endl;
    for(int i=0;i<scanner_count;i++)
    {
        QString scaner_name = devices[i]->vendor;
        QString model = devices[i]->model;

        QString name=devices[i]->name;
        scannerList<<name;

        SANE_Handle handle = nullptr;
        SANE_String_Const device_name = devices[i]->name;
        SANE_Status status = sane_open(device_name, &handle);
        if (status == SANE_STATUS_GOOD)
        {
            scannerListHandle<<handle;
        }
        else
        {
            scannerListHandle<<nullptr;
        }

    }

   delete devices;

#endif

}

void ScannerManager::init()
{

}

void ScannerManager::startScan(ScanInfo& info)
{
    qDebug() << "startScan" << endl;

    if (!(this->savConfig()))
    {
        QMessageBox::information(nullptr, "提示", "扫描仪参数设置失败,请重新尝试设置直到成功过，否则无效!");
        return;
    }
#ifdef  APP_WINDOWS_X64
    if (m_scanType == "平板扫描")
    {

        if (ScannerApp::m_ScannerCore->doScanToFile(info.pathName))
        {

        }
        else
        {
            QMessageBox::information(nullptr, "提示", "扫描失败，请重试");
        }

    }
    else
    {
        //测试高扫
        QString fileName, FilesCount;
        int index, iPicCount;
//        if (ScannerApp::m_ScannerCore->doScanToDir(info.folder, fileName, FilesCount))
//        {
//            iPicCount = FilesCount.toInt();
//            for (index = 0; index < iPicCount; index ++)
//            {
//                lAllFilePath = lAllFileDir + "00" + QString::number(index + 1) + ".jpg";

//            }
        //  }
        //  else
        //  {
        QMessageBox::information(nullptr, "提示", "高扫 扫描失败，请重试");
        // }
    }
#else
    if (m_scanType == "平板扫描")
    {



        if (ScannerApp::m_ScannerCore->doScanToFile(info.handle,info.pathName))
        {

        }
        else
        {
            QMessageBox::information(nullptr, "提示", "扫描失败，请重试");
        }

    }
    else
    {
        //测试高扫
        QString fileName, FilesCount;
        int index, iPicCount;
        QStringList fileNames;
        if (ScannerApp::m_ScannerCore->doScanToDir(0,info.handle,info.pathName, fileNames, FilesCount))
        {
            iPicCount = FilesCount.toInt();
            for (index = 0; index < iPicCount; index ++)
            {
                //lAllFilePath = lAllFileDir + "00" + QString::number(index + 1) + ".jpg";

            }
          }
          else
          {
        QMessageBox::information(nullptr, "提示", "高扫 扫描失败，请重试");
        }
    }
#endif

}

const QString& ScannerManager::scanType() const
{
    return m_scanType;
}

void ScannerManager::setScanType(const QString& newScanType)
{
    m_scanType = newScanType;
    saveConfig("ScanType", m_scanType);
}

int ScannerManager::scannerIndex() const
{
    return m_scannerIndex;
}

void ScannerManager::setScannerIndex(int newScannerIndex)
{
    m_scannerIndex = newScannerIndex;
}

bool ScannerManager::showUI() const
{
    return m_showUI;
}

void ScannerManager::setShowUI(bool newShowUI)
{
    m_showUI = newShowUI;
    saveConfig("ShowUI", m_showUI);
}

bool ScannerManager::duplexEnabled() const
{
    return m_duplexEnabled;
}

void ScannerManager::setDuplexEnabled(bool newDuplexEnabled)
{
    m_duplexEnabled = newDuplexEnabled;
}

void ScannerManager::loadIniFile()
{
    QString filePath = QGuiApplication::applicationDirPath() +  "/configs/scanner.ini";
    //没有检测到先写一遍默认值
    QSettings*  ini = new QSettings(filePath, QSettings::IniFormat);
    ini->setIniCodec("UTF8");
    ini ->beginGroup("canner");//功能
    m_showUI = ini->value("ShowUI", false).toBool();
    m_scanType = ini->value("ScanType", m_scanType).toString();
    m_rotation = ini->value("Rotation").toInt();
    m_scanArea = ini->value("StandardSize").toInt();
    m_scanAreaWidth = ini->value("StandardSizeW").toInt();
    m_scanAreaHeight = ini->value("StandardSizeH").toInt();
    ini->endGroup();
    delete ini;

}

void ScannerManager::saveConfig(QString key, QVariant value)
{
    QString filePath = QGuiApplication::applicationDirPath() +  "/configs/scanner.ini";
    //没有检测到先写一遍默认值
    QSettings*  ini = new QSettings(filePath, QSettings::IniFormat);
    ini->setIniCodec("UTF8");
    ini ->beginGroup("canner");//功能
    ini->setValue(key, value);//扫描仪列表 默认扫描仪序号
    ini->endGroup();
    delete ini;

}

int ScannerManager::rotation() const
{
    return m_rotation;
}

void ScannerManager::setRotation(int newRotation)
{
    m_rotation = newRotation;
}

int ScannerManager::scanArea() const
{
    return m_scanArea;
}

void ScannerManager::setScanArea(int newScanArea)
{
    m_scanArea = newScanArea;
    saveConfig("StandardSize", m_scanArea);
}

int ScannerManager::scanAreaWidth() const
{
    return m_scanAreaWidth;
}

void ScannerManager::setScanAreaWidth(int newScanAreaWidth)
{
    m_scanAreaWidth = newScanAreaWidth;
    saveConfig("StandardSizeW", m_scanAreaWidth);
}

int ScannerManager::scanAreaHeight() const
{
    return m_scanAreaHeight;
}

void ScannerManager::setScanAreaHeight(int newScanAreaHeight)
{
    m_scanAreaHeight = newScanAreaHeight;
    saveConfig("StandardSizeH", m_scanAreaHeight);
}

ScannerManager* scannerManager()
{
    if (ScannerManager::m_instance == nullptr)
    {
        ScannerManager::m_instance = shared_ptr<ScannerManager>(new ScannerManager());
    }
    return ScannerManager::m_instance.get();

}

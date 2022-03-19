#include "scanner_operation.h"
#ifdef APP_WINDOWS_X64
#else
#include "sane.h"
#include <QFile>
#include <QJsonParseError>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>
#include <QFileInfo>
#include <QImage>
#include <QDir>
#include <QDateTime>
Scanner_Operation* Scanner_Operation::m_scanner_operation = nullptr;

Scanner_Operation* Scanner_Operation::getInstance()
{
    if (m_scanner_operation == nullptr)
    {
        m_scanner_operation = new Scanner_Operation();
    }
    return m_scanner_operation;
}

bool Scanner_Operation::parsing_configfile(QString file, QJsonObject& jsonobject)
{
    QFile jsonfile(file);
    if (!jsonfile.open(QIODevice::ReadOnly))
    {
        qDebug() << "could not open json file" << endl;
        return false;
    }
    QByteArray allData = jsonfile.readAll();
    jsonfile.close();
    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &json_error));
    if (json_error.error != QJsonParseError::NoError)
    {
        qDebug() << "json error!" << json_error.errorString() << endl;
        return false;
    }
    jsonobject = jsonDoc.object();
    return true;
}

bool Scanner_Operation::Sane_init()
{
    SANE_Status lSANE_Status;
    SANE_Int version_code = 0;
    lSANE_Status = sane_init(&version_code, nullptr);
    if (SANE_STATUS_GOOD == lSANE_Status)
    {
        qDebug() << "init sucess!" << endl;
        return true;
    }
    else
    {
        return false;
    }
}
bool Scanner_Operation::InitScanner(QString jsonfile)
{
    if (scanner_count > 0)
    {
        return true;
    }
    SANE_Status lSANE_Status;
    const SANE_Device** devices = nullptr;
    lSANE_Status = sane_get_devices(&devices, SANE_FALSE);//返回本地直连设备
    if (SANE_STATUS_GOOD != lSANE_Status)
    {
        return false;
    }
    scanner_count = 0;
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
    scannerlist = (Scanner**)malloc(sizeof(Scanner*)*scanner_count);
    for (int i = 0; i < scanner_count; i++)
    {
        scannerlist[i] = new Scanner();
    }
    for (int i = 0; i < scanner_count; i++)
    {
        scannerlist[i]->set_sane_device(*devices[i]);
        QString scaner_name = devices[i]->vendor;
        if (scaner_name.isNull() || scaner_name.isEmpty())
        {
            scaner_name.clear();
        }
        else
        {
            scaner_name.append(" ");
        }
        QString model = devices[i]->model;
        if (model.contains("Pantum DS-230 Scanner"))
        {
            scaner_name.append(" ");
        }
        model = model.section("(libusb", 0, 0);
        scaner_name.append(model);
        scannerlist[i]->set_scanner_name(scaner_name);
        qDebug() << "" << scannerlist[i]->get_scanner_name() << endl;
    }
    QJsonObject jsonobject;
    if (!parsing_configfile(jsonfile, jsonobject))
    {
        return false;
    }
    for (int i = 0; i < scanner_count; i++)
    {
        QString scanname = scannerlist[i]->get_scanner_name();
        if (jsonobject.contains(scanname) && jsonobject[scanname].isObject())
        {
            QJsonObject subObj = jsonobject[scanname].toObject();
            scannerlist[i]->set_color_optionName(subObj["mode"].toString().toLatin1().data());
            scannerlist[i]->set_dpi_optionName(subObj["resolution"].toString().toLatin1().data());
            scannerlist[i]->set_papersize_optionName(subObj["paper-size"].toString().toLatin1().data());
            scannerlist[i]->set_tlxName(subObj["tl-x"].toString().toLatin1().data());
            scannerlist[i]->set_tlyName(subObj["tl-y"].toString().toLatin1().data());
            scannerlist[i]->set_brxName(subObj["br-x"].toString().toLatin1().data());
            scannerlist[i]->set_bryName(subObj["br-y"].toString().toLatin1().data());
            scannerlist[i]->set_selectFAName(subObj["selectFA"].toString().toLatin1().data());
            QJsonArray array = subObj["scanmode"].toArray();
            scannerlist[i]->set_flatedName(array[0].toString().toLatin1().data());
            scannerlist[i]->set_adfName(array[1].toString().toLatin1().data());
            scannerlist[i]->set_adfDuplexName(array[2].toString().toLatin1().data());
            if (subObj.contains("batch-scan"))
            {
                scannerlist[i]->set_batchscanName(subObj["batch-scan"].toString().toLatin1().data());
            }
            else
            {
                scannerlist[i]->set_batchscanID(SANE_Int(-1));
            }
        }
    }
    for (int i = 0; i < scanner_count; i++)
    {
        SANE_Handle handle = nullptr;
        SANE_String_Const device_name = scannerlist[i]->get_sane_device().name;
        SANE_Status status = sane_open(device_name, &handle);
        if (status == SANE_STATUS_GOOD)
        {
            scannerlist[i]->set_saneHandle(handle);
        }
        else
        {
            scannerlist[i]->set_saneHandle(nullptr);
        }
    }
    for (int index = 0; index < scanner_count; index++)
    {
        if (scannerlist[index]->get_saneHandle() == nullptr)
        {
            continue;
        }
        for (int i = 0;; i++)
        {
            SANE_Int option = SANE_Int(i);
            const SANE_Option_Descriptor* description = sane_get_option_descriptor(scannerlist[index]->get_saneHandle(), option);
//            qDebug()<<"option is :"<<option<<" description:"<<description->name<<" title:"<<description->title
//                   <<" desc:"<<description->desc<<" type:"<<description->type<<" unit"<<description->unit  \
//                  <<" size:"<<description->size <<" constraint_type:"<<description->constraint_type<<endl;
            if (description == nullptr)
            {
                break;
            }
            if (description->name == nullptr)
            {
                continue;
            }
            if (strcmp(description->name, scannerlist[index]->get_color_optionName()) == 0)
            {
                scannerlist[index]->set_color_optionID(option);
            }
            else if (strcmp(description->name, scannerlist[index]->get_dpi_optionName()) == 0)
            {
                scannerlist[index]->set_dpi_optionID(option);
            }
            else if (strcmp(description->name, scannerlist[index]->get_papersize_optionName()) == 0)
            {
                scannerlist[index]->set_papersize_optionID(option);
            }
            else if (strcmp(description->name, scannerlist[index]->get_tlxName()) == 0)
            {
                scannerlist[index]->set_tlxID(option);
            }
            else if (strcmp(description->name, scannerlist[index]->get_tlyName()) == 0)
            {
                scannerlist[index]->set_tlyID(option);
            }
            else if (strcmp(description->name, scannerlist[index]->get_brxName()) == 0)
            {
                scannerlist[index]->set_brxID(option);
            }
            else if (strcmp(description->name, scannerlist[index]->get_bryName()) == 0)
            {
                scannerlist[index]->set_bryID(option);
            }
            else if (strcmp(description->name, scannerlist[index]->get_selectFAName()) == 0)
            {
                scannerlist[index]->set_selectFAID(option);
            }
            else if (strcmp(description->name, scannerlist[index]->get_batchscanName()) == 0)
            {
                scannerlist[index]->set_batchscanID(option);
            }
        }
    }
    delete devices;
    init_status = true;
    return true;
}

void Scanner_Operation::UnitScanner(Scanner** scannerlist)
{
    for (int i = 0; i < scanner_count; i++)
    {

        if (scannerlist[i]->get_saneHandle() == nullptr)
        {
            break;
        }
        else
        {
            qDebug() << "UnitScanner scannerlist[i] is " << scannerlist[i]->get_saneHandle() << endl;
            sane_close(scannerlist[i]->get_saneHandle());
        }
    }
}

void Scanner_Operation::writeppm_header(SANE_Parameters& pars, QByteArray& qByteArray)
{
    char ppm_header[64] = "";
    int ppm_header_p = 6;
    if (pars.format == SANE_FRAME_GRAY)
    {
        ppm_header_p = 5;
    }
    if (pars.format == SANE_FRAME_RGB)
    {
        ppm_header_p = 6;
    }
    switch (pars.depth)
    {
    case 1:
        sprintf(ppm_header, "P4\n# SANE data follows\n%d %d\n%d\n", pars.pixels_per_line, pars.lines, 255);
        break;
    case 8:
        sprintf(ppm_header, "P%d\n# SANE data follows\n%d %d\n%d\n", ppm_header_p, pars.pixels_per_line, pars.lines, 255);
        break;
    case 16:
        sprintf(ppm_header, "P%d\n# SANE data follows\n%d %d\n%d\n", ppm_header_p, pars.pixels_per_line, pars.lines, 65535);
        break;
    case 24:
        sprintf(ppm_header, "P%d\n# SANE data follows\n%d %d\n%d\n", ppm_header_p, pars.pixels_per_line, pars.lines, 16777216);
        break;
    case 32:
        sprintf(ppm_header, "P%d\n# SANE data follows\n%d %d\n%d\n", ppm_header_p, pars.pixels_per_line, pars.lines, 16777216);
        break;
    default:
        sprintf(ppm_header, "P%d\n# SANE data follows\n%d %d\n%d\n", ppm_header_p, pars.pixels_per_line, pars.lines, 255);
        break;
    }
    int ppm_header_size = static_cast<int>(strlen(ppm_header));
    qByteArray.append(ppm_header, ppm_header_size);
    qByteArray.resize(ppm_header_size);
}

bool Scanner_Operation::read_bytes(SANE_Handle handle, QByteArray& qByteArray,SANE_Parameters &pars)
{
    SANE_Status lSANE_Status;
    SANE_Byte data[32 * 1024];
    SANE_Int max_length = sizeof(data);
    SANE_Int length;
    SANE_Int init_filesize = qByteArray.size();
    SANE_Int filesize = qByteArray.size();
    SANE_Status status = sane_get_parameters(handle, &pars);
    if (status != SANE_STATUS_GOOD)
    {
        return false;
    }

    while (1)
    {
        memset(data, 0x00, static_cast<size_t>(max_length));
        length = 0;
        lSANE_Status = sane_read(handle, data, max_length, &length);
        if (lSANE_Status != SANE_STATUS_GOOD)
        {
            if (lSANE_Status == SANE_STATUS_EOF)
                break;
            qDebug() << "sane_read lSANE_Status:" << lSANE_Status << endl;
            return false;
        }
        else
        {
            filesize = filesize + length;
            qByteArray.append(reinterpret_cast<char*>(data), length);
            qByteArray.resize(filesize);
        }
    }
    if (qByteArray.size() > init_filesize)
    {
        qDebug() << "init_filesize is " << init_filesize << " filesize:" << filesize << endl;
        return true;
    }
    return false;
}

bool Scanner_Operation::read_image(SANE_Handle handle, QList<QImage*>& qImagelist)
{

    SANE_Parameters pars;
    SANE_Status status = sane_get_parameters(handle, &pars);
    if (status != SANE_STATUS_GOOD)
    {
        return false;
    }
    QByteArray qByteArray;
    writeppm_header(pars, qByteArray);
    QStringList base64List;
    while (read_bytes(handle, qByteArray,pars))
    {
        QImage* qImage = new QImage;
        if (qImage->loadFromData(reinterpret_cast<uchar*>(qByteArray.data()), qByteArray.size()))
        {
            qImagelist<<qImage;
            return true;
        }
        else
        {
            sane_cancel(handle);
            return false;
        }
    }
    return true;
}

bool Scanner_Operation::doScanToFile(SANE_Handle handle, QString AllFilePath)
{
    SANE_Status status = sane_start(handle);
    if (status == SANE_STATUS_GOOD)
    {
        sane_set_io_mode(handle, false);
        QList<QImage*> qImage;
        if (read_image(handle, qImage))
        {
            QFileInfo fileInfo(AllFilePath);
            QDir dir;
            if (!dir.exists(fileInfo.absolutePath()))
            {
                if (!dir.mkpath(fileInfo.absolutePath()))
                {
                    sane_cancel(handle);
                    return false;
                }
            }
            if (qImage.count() > 0)
            {
                qImage.at(0)->save(AllFilePath, "JPG", 100);
                qDebug() << "AllFilePath:" << AllFilePath << endl;
                if (QFileInfo::exists(AllFilePath))
                {
                    sane_cancel(handle);
                    return true;
                }
            }
        }
    }
    sane_cancel(handle);
    return false;
}
/*
handle:扫描仪句柄
lAllFileDir:文件目录
aFileNameList:
aFilesCount:图片数量
*/
bool Scanner_Operation::doScanToDir_Test(SANE_Handle handle, QString lAllFileDir, QStringList& aFileNameList, QString& aFilesCount)
{
    SANE_Status status = sane_start(handle);
    qDebug() << "status:" << status << endl;
    qDebug() << "lAllFileDir is " << lAllFileDir << endl;
    int imagecount = 0;
    if (status == SANE_STATUS_GOOD)
    {
        sane_set_io_mode(handle, false);
        QList<QImage*> qImagelist;
        if (read_image(handle, qImagelist))
        {
            QFileInfo fileInfo(lAllFileDir);
            QDir dir;
            if (!dir.exists(fileInfo.absolutePath()))
            {
                if (!dir.mkpath(fileInfo.absolutePath()))
                {
                    sane_cancel(handle);
                    return false;
                }
            }
            for (int i = 0; i < qImagelist.count(); i++)
            {
                QString ALLFilePath;
                qDebug() << "i:" << i << " lAllFileDir:" << lAllFileDir << endl;
                ALLFilePath = lAllFileDir + QUuid::createUuid().toString(QUuid::WithoutBraces) + ".jpg";
                qImagelist.at(i)->save(ALLFilePath, "JPG", 100);
                aFileNameList.append(ALLFilePath);
                imagecount++;
            }
        }
        sane_cancel(handle);
        aFilesCount = QString::number(imagecount);
        return true;
    }
    sane_cancel(handle);
    return false;
}
bool Scanner_Operation::doScanToDir(int type, SANE_Handle handle, QString lAllFileDir, QStringList& aFileNameList, QString& aFilesCount)
{
    if (type == 0)
    {
        return doScanToDir_BT(handle, lAllFileDir, aFileNameList, aFilesCount);
    }
    else if (type == 1)
    {
        return doScanToDir_ZJ(handle, lAllFileDir, aFileNameList, aFilesCount);
    }
    return true;
}

bool Scanner_Operation::doScanToDir_BT(SANE_Handle handle, QString lAllFileDir, QStringList& aFileNameList, QString& aFilesCount)
{
    sane_cancel(handle);
    SANE_Status status = sane_start(handle);
    qDebug() << "doScanToDir_BT status:" << status << endl;
    qDebug() << "doScanToDir_BT lAllFileDir is " << lAllFileDir << endl;
    int imagecount = 0;
    if (status == SANE_STATUS_GOOD)
    {
        sane_set_io_mode(handle, false);
        QList<QImage*> qImagelist;
        if (read_image(handle, qImagelist))
        {
            QFileInfo info(lAllFileDir);

            QDir dir;
            dir.mkpath(info.absolutePath());



            if(qImagelist.count()>0)
            {

                qImagelist.at(0)->save(lAllFileDir);
                aFileNameList.append(lAllFileDir);
                qDebug()<<lAllFileDir;
                imagecount++;

            }
        }
        sane_cancel(handle);
        aFilesCount = QString::number(imagecount);
        return true;
    }
    sane_cancel(handle);
    return false;
}

bool Scanner_Operation::doScanToDir_ZJ(SANE_Handle handle, QString lAllFileDir, QStringList& aFileNameList, QString& aFilesCount)
{
    qDebug() << "doScanToDir_ZJ" << endl;
    int imagecount = 0;
    while (1)
    {
        SANE_Status status = sane_start(handle);
        if (status == SANE_STATUS_GOOD)
        {
            sane_set_io_mode(handle, false);
            QList<QImage*> qImagelist;
            if (read_image(handle, qImagelist))
            {
                QFileInfo fileInfo(lAllFileDir);
                QDir dir;
                if (!dir.exists(fileInfo.absolutePath()))
                {
                    if (!dir.mkpath(fileInfo.absolutePath()))
                    {
                        sane_cancel(handle);
                        return false;
                    }
                }
                if (qImagelist.count() < 0)
                {
                    sane_cancel(handle);
                    return true;
                }
                for (int i = 0; i < qImagelist.count(); i++)
                {
                    QString ALLFilePath;
                    qDebug() << "i:" << i << " lAllFileDir:" << lAllFileDir << endl;
                    ALLFilePath = lAllFileDir + "00" + QString::number(imagecount + 1) + ".jpg";
                    qImagelist.at(i)->save(ALLFilePath, "JPG", 100);
                    aFileNameList.append(ALLFilePath);
                    imagecount++;
                }
            }
        }
        else if (status == SANE_STATUS_NO_DOCS)
        {
            qDebug() << "SANE_STATUS_NO_DOCS" << endl;
            aFilesCount = QString::number(imagecount);
            sane_cancel(handle);
            return true;
        }
        else
        {
            aFilesCount = QString::number(imagecount);
            sane_cancel(handle);
            return true;
        }
    }
}

//bool Scanner_Operation::doScanToDir_ZJ(SANE_Handle handle,QString lAllFileDir,QStringList& aFileNameList,QString& aFilesCount)
//{
//    SANE_Status status=sane_start(handle);
//    qDebug()<<"doScanToDir_ZJ status:"<<status<<endl;
//    qDebug()<<"doScanToDir_ZJ lAllFileDir is "<<lAllFileDir<<endl;
//    int imagecount=0;
//    if (status == SANE_STATUS_GOOD ){
//        sane_set_io_mode(handle,false);
//        QList<QImage> qImagelist;
//        if(read_image(handle,qImagelist)){
//            QFileInfo fileInfo(lAllFileDir);
//            QDir dir;
//            if (!dir.exists(fileInfo.absolutePath())) {
//                if (!dir.mkpath(fileInfo.absolutePath())){
//                    sane_cancel(handle);
//                    return false;
//                }
//            }
//            for(int i=0;i<qImagelist.count();i++)
//            {
//                QString ALLFilePath;
//                qDebug()<<"i:"<<i<<" lAllFileDir:"<<lAllFileDir<<endl;
//                ALLFilePath = lAllFileDir+"00" + QString::number(i + 1) + ".jpg";
//                qImagelist.at(i).save(ALLFilePath,"JPG",100);
//                aFileNameList.append(ALLFilePath);
//                imagecount++;
//            }
//        }
//        sane_cancel(handle);
//        aFilesCount=QString::number(imagecount);
//        return true;
//    }
//    sane_cancel(handle);
//    return false;
//}


bool Scanner_Operation::set_color_option(SANE_Handle handle, SANE_Int option, SANE_String value)
{
    if (option < 0)
        return false;
    SANE_Status lSANE_Status;
    SANE_String color = value;
    lSANE_Status = sane_control_option(handle, option, SANE_ACTION_SET_VALUE, color, nullptr);
    return lSANE_Status == SANE_STATUS_GOOD;
}

bool Scanner_Operation::set_DPI_option(SANE_Handle handle, SANE_Int option, SANE_Int& value)
{
    if (option < 0)
        return false;
    SANE_Status lSANE_Status;
    lSANE_Status = sane_control_option(handle, option, SANE_ACTION_SET_VALUE, &value, nullptr);
    return lSANE_Status == SANE_STATUS_GOOD;
}
bool Scanner_Operation::set_DPI_option_byte(SANE_Handle handle, SANE_Int option, SANE_Fixed& value)
{
    if (option < 0)
        return false;
    SANE_Status lSANE_Status;
    lSANE_Status = sane_control_option(handle, option, SANE_ACTION_SET_VALUE, &value, nullptr);
    return lSANE_Status == SANE_STATUS_GOOD;
}


bool Scanner_Operation::set_papersize_option(SANE_Handle handle, SANE_Int option, SANE_String value)
{
    if (option < 0)
        return false;
    SANE_Status lSANE_Status;
    SANE_String papersize = value;
    lSANE_Status = sane_control_option(handle, option, SANE_ACTION_SET_VALUE, papersize, nullptr);
    return lSANE_Status == SANE_STATUS_GOOD;
}

bool Scanner_Operation::set_autocropdeskew_enable(SANE_Handle handle, SANE_Int option, SANE_Bool& value)
{
    if (option < 0)
        return false;
    SANE_Status lSANE_Status;
    lSANE_Status = sane_control_option(handle, option, SANE_ACTION_SET_VALUE, &value, nullptr);
    return lSANE_Status == SANE_STATUS_GOOD;
}


bool Scanner_Operation::set_geometry(SANE_Handle handle, SANE_Int option, SANE_Int& value)
{
    if (option < 0)
        return false;
    SANE_Status lSANE_Status;
    lSANE_Status = sane_control_option(handle, option, SANE_ACTION_SET_VALUE, &value, nullptr);
    return lSANE_Status == SANE_STATUS_GOOD;
}

bool Scanner_Operation::set_geometry_Fixed(SANE_Handle handle, SANE_Int option, SANE_Fixed& value)
{
    if (option < 0)
        return false;
    SANE_Status lSANE_Status;
    lSANE_Status = sane_control_option(handle, option, SANE_ACTION_SET_VALUE, &value, nullptr);
    return lSANE_Status == SANE_STATUS_GOOD;
}

bool Scanner_Operation::set_source(SANE_Handle handle, SANE_Int option, SANE_String value)
{
    if (option < 0)
        return false;
    SANE_Status lSANE_Status;
    SANE_String source = value;
    lSANE_Status = sane_control_option(handle, option, SANE_ACTION_SET_VALUE, source, nullptr);
    return lSANE_Status == SANE_STATUS_GOOD;
}

bool Scanner_Operation::set_batchscan(SANE_Handle handle, SANE_Int option, SANE_Int& value)
{
    if (option < 0)
        return false;
    SANE_Status lSANE_Status;
    lSANE_Status = sane_control_option(handle, option, SANE_ACTION_SET_VALUE, &value, nullptr);
    return lSANE_Status == SANE_STATUS_GOOD;
}

bool Scanner_Operation::set_bg_color_option(SANE_Handle handle, SANE_Int option, SANE_String value)
{
    if (option < 0)
        return false;
    SANE_Status lSANE_Status;
    SANE_String bg_color = value;
    lSANE_Status = sane_control_option(handle, option, SANE_ACTION_SET_VALUE, bg_color, nullptr);
    return lSANE_Status == SANE_STATUS_GOOD;
}

bool Scanner_Operation::set_rotate_option(SANE_Handle handle, SANE_Int option, SANE_String value)
{
    if (option < 0)
        return false;
    SANE_Status lSANE_Status;
    SANE_String rotate = value;
    lSANE_Status = sane_control_option(handle, option, SANE_ACTION_SET_VALUE, rotate, nullptr);
    return lSANE_Status == SANE_STATUS_GOOD;
}

#endif

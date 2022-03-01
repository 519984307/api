#include "sanecore.h"


SaneCore::SaneCore()
{

}
SaneCore::~SaneCore()
{
    if (lib.isLoaded())
    {
        lib.unload();
    }
}


bool SaneCore::Loadlib()
{
    if (lib.isLoaded())
    {
        return true;
    }
    QString libfile = "";
#if (APP_LINUX_X64)
    libfile = "libs/linux/libsane.so.1.0.25";
#endif
#if (QT_LINUX&&QT_ARCH_mips64)
    libfile = "libs/mips/libsane.so.1.0.25";
#endif
#if (QT_LINUX&&QT_ARCH_arm64)
    libfile = "libs/arm/libsane.so.1.0.25";
#endif
    QString libAllFilePath = qApp->applicationDirPath() + "/" + libfile;
    lib.setFileName(libAllFilePath);
    lib.load();
    if (!lib.isLoaded())
    {
        return false;
    }
    m_SANE_ENTRYPOINT.sane_init = reinterpret_cast<LP_sane_init>(lib.resolve("sane_init"));
    m_SANE_ENTRYPOINT.sane_exit = reinterpret_cast<LP_sane_exit>(lib.resolve("sane_exit"));
    m_SANE_ENTRYPOINT.sane_get_devices = reinterpret_cast<LP_sane_get_devices>(lib.resolve("sane_get_devices"));
    m_SANE_ENTRYPOINT.sane_open = reinterpret_cast<LP_sane_open>(lib.resolve("sane_open"));
    m_SANE_ENTRYPOINT.sane_close = reinterpret_cast<LP_sane_close>(lib.resolve("sane_close"));
    m_SANE_ENTRYPOINT.sane_get_option_descriptor = reinterpret_cast<LP_sane_get_option_descriptor>(lib.resolve("sane_get_option_descriptor"));
    m_SANE_ENTRYPOINT.sane_control_option = reinterpret_cast<LP_sane_control_option>(lib.resolve("sane_control_option"));
    m_SANE_ENTRYPOINT.sane_get_parameters = reinterpret_cast<LP_sane_get_parameters>(lib.resolve("sane_get_parameters"));
    m_SANE_ENTRYPOINT.sane_start = reinterpret_cast<LP_sane_start>(lib.resolve("sane_start"));
    m_SANE_ENTRYPOINT.sane_read = reinterpret_cast<LP_sane_read>(lib.resolve("sane_read"));
    m_SANE_ENTRYPOINT.sane_cancel = reinterpret_cast<LP_sane_cancel>(lib.resolve("sane_cancel"));
    m_SANE_ENTRYPOINT.sane_set_io_mode = reinterpret_cast<LP_sane_set_io_mode>(lib.resolve("sane_set_io_mode"));
    m_SANE_ENTRYPOINT.sane_get_select_fd = reinterpret_cast<LP_sane_get_select_fd>(lib.resolve("sane_get_select_fd"));
    m_SANE_ENTRYPOINT.sane_strstatus = reinterpret_cast<LP_sane_strstatus>(lib.resolve("sane_strstatus"));
    return true;
}

bool SaneCore::Freelib()
{
    if (lib.isLoaded())
    {
        lib.unload();
    }
    m_SANE_ENTRYPOINT.sane_init = nullptr;
    m_SANE_ENTRYPOINT.sane_exit = nullptr;
    m_SANE_ENTRYPOINT.sane_get_devices = nullptr;
    m_SANE_ENTRYPOINT.sane_open = nullptr;
    m_SANE_ENTRYPOINT.sane_close = nullptr;
    m_SANE_ENTRYPOINT.sane_get_option_descriptor = nullptr;
    m_SANE_ENTRYPOINT.sane_control_option = nullptr;
    m_SANE_ENTRYPOINT.sane_get_parameters = nullptr;
    m_SANE_ENTRYPOINT.sane_start = nullptr;
    m_SANE_ENTRYPOINT.sane_read = nullptr;
    m_SANE_ENTRYPOINT.sane_cancel = nullptr;
    m_SANE_ENTRYPOINT.sane_set_io_mode = nullptr;
    m_SANE_ENTRYPOINT.sane_get_select_fd = nullptr;
    m_SANE_ENTRYPOINT.sane_strstatus = nullptr;
    return true;
}



SaneAPP::SaneAPP()
{
    m_saneCore = new SaneCore();

}

SaneAPP::~SaneAPP()
{
    m_saneCore->~SaneCore();
}

void SaneAPP::SANE_Auth_Callback(SANE_String_Const resource,
                                 SANE_Char* username,
                                 SANE_Char* password)
{
    Q_UNUSED(resource);
    Q_UNUSED(username);
    Q_UNUSED(password);

}


void SaneAPP::initAPP()
{

    m_State = 0;
    if (!m_saneCore->Loadlib())
    {
        QMessageBox::information(nullptr, "提示", "未找到libsane.so");
        return;
    }
    m_State = 1;
    SANE_Status lSANE_Status;
    SANE_Int version_code = 0;
    lSANE_Status = m_saneCore->m_SANE_ENTRYPOINT.sane_init(&version_code, nullptr);
    if (SANE_STATUS_GOOD == lSANE_Status)
    {
        m_State = 2;
    }
    else
    {
        return;
    }
}

void SaneAPP::reInitAPP()
{
    if (m_State > 0)
    {
        m_saneCore->Freelib();
        m_State = 0;
    }

    if (!m_saneCore->Loadlib())
    {
        QMessageBox::information(nullptr, "提示", "未找到libsane.so");
        return;
    }
    m_State = 1;
    SANE_Status lSANE_Status;
    SANE_Int version_code = 0;
    lSANE_Status = m_saneCore->m_SANE_ENTRYPOINT.sane_init(&version_code, nullptr);
    if (SANE_STATUS_GOOD == lSANE_Status)
    {
        m_State = 2;
    }
    else
    {
        return;
    }
}

bool SaneAPP::get_device_list()
{
    m_dogetdevicelist_times++;
    SANE_Status lSANE_Status;
    lSANE_Status = m_saneCore->m_SANE_ENTRYPOINT.sane_get_devices(&m_device_list, SANE_TRUE);
    if (SANE_STATUS_GOOD != lSANE_Status)
    {
        return false;
    }
    m_State = 3;
    return true;

}

int SaneAPP::get_device_list_count()
{
    m_device_list_count = 0;
    if (m_device_list == nullptr)
    {
        return 0;
    }
    if (m_device_list[0] != nullptr)
    {
        m_device_list_count = sizeof(m_device_list) / sizeof(m_device_list[0]);
    }
    return m_device_list_count;
}


bool SaneAPP::sane_open(const SANE_Device* device)
{
    if (device != nullptr)
    {
        this->m_now_sane_handle = nullptr;
        SANE_Status lSANE_Status = m_saneCore->m_SANE_ENTRYPOINT.sane_open(device->name, &m_now_sane_handle);
        return SANE_STATUS_GOOD == lSANE_Status;
    }
    return  false;
}

bool SaneAPP::sane_open(int device_list_index)
{
    if ((m_device_list_count > 0) && (device_list_index < m_device_list_count))
    {
        const SANE_Device* device = m_device_list[device_list_index];
        if (device != nullptr)
        {
            m_now_sane_handle = nullptr;
            if (!sane_open(device))
            {
                return false;
            }
            m_now_device = m_device_list[device_list_index];
            return true;
        }
    }
    return  false;
}

bool SaneAPP::sane_close()
{
    if (m_now_sane_handle == nullptr)
    {
        return false;
    }
    if ((m_now_device != nullptr) && (m_now_sane_handle != nullptr))
    {
        m_saneCore->m_SANE_ENTRYPOINT.sane_close(m_now_sane_handle);
        return true;
    }
    return false;
}

bool SaneAPP::sane_start()
{
    if (m_now_sane_handle == nullptr)
    {
        return false;
    }
    SANE_Status lSANE_Status = m_saneCore->m_SANE_ENTRYPOINT.sane_start(m_now_sane_handle);
    if (SANE_STATUS_GOOD == lSANE_Status)
    {
        return true;
    }
    return  false;
}

bool SaneAPP::sane_set_io_mode(SANE_Bool non_blocking)
{
    if (m_now_sane_handle == nullptr)
    {
        return false;
    }
    SANE_Status lSANE_Status = m_saneCore->m_SANE_ENTRYPOINT.sane_set_io_mode(m_now_sane_handle, non_blocking);
    if (SANE_STATUS_GOOD == lSANE_Status)
    {
        return true;
    }
    else
    {
        return false;
    }
}

const SANE_Option_Descriptor* SaneAPP::sane_get_option_descriptor(SANE_Int option)
{
    if (m_now_sane_handle == nullptr)
    {
        return nullptr;
    }
    const SANE_Option_Descriptor* opt = nullptr;
    opt = m_saneCore->m_SANE_ENTRYPOINT.sane_get_option_descriptor(m_now_sane_handle, option);
    return opt;
}

const SANE_Option_Descriptor* SaneAPP::sane_get_option_descriptor(const char* name)
{
    if (m_now_device == nullptr)
    {
        return nullptr;
    }
    const SANE_Option_Descriptor* opt = nullptr;
    QVariant optionnum;
    if (sane_get_option(0, SANE_TYPE_INT, optionnum))
    {
        for (int option_num = 0; option_num < optionnum.toInt(); option_num++)
        {
            opt = sane_get_option_descriptor(option_num);
            if (opt != nullptr)
            {
                if (opt->name && strcmp(opt->name, name) == 0)
                {
                    return opt;
                }
            }
        }
    }
    return nullptr;
}

bool SaneAPP::sane_get_parameters(SANE_Parameters& pars)
{
    if (m_now_sane_handle == nullptr)
    {
        return false;
    }
    SANE_Status lSANE_Status = m_saneCore->m_SANE_ENTRYPOINT.sane_get_parameters(m_now_sane_handle, &pars);
    return (lSANE_Status == SANE_STATUS_GOOD);
}

bool SaneAPP::sane_control_option(SANE_Int option, SANE_Action action, void* value, SANE_Int* info)
{
    if (m_now_sane_handle == nullptr)
    {
        return false;
    }
    SANE_Status lSANE_Status = m_saneCore->m_SANE_ENTRYPOINT.sane_control_option(m_now_sane_handle, option, action, value, info);
    return (lSANE_Status == SANE_STATUS_GOOD);
}

bool SaneAPP::sane_get_option(SANE_Int option, SANE_Value_Type valueType, QVariant& qv_Value)
{
    if (m_now_sane_handle == nullptr)
    {
        return false;
    }
    SANE_Status lSANE_Status = SANE_STATUS_UNSUPPORTED;
    switch (valueType)
    {
    case SANE_TYPE_BOOL:
    {
        SANE_Bool value;
        lSANE_Status = m_saneCore->m_SANE_ENTRYPOINT.sane_control_option(m_now_sane_handle, option, SANE_ACTION_GET_VALUE, &value, nullptr);
        qv_Value = QVariant::fromValue(value);
        break;
    }

    case SANE_TYPE_INT:
    {
        SANE_Int value;
        lSANE_Status = m_saneCore->m_SANE_ENTRYPOINT.sane_control_option(m_now_sane_handle, option, SANE_ACTION_GET_VALUE, &value, nullptr);
        qv_Value = QVariant::fromValue(value);
        break;
    }
    case SANE_TYPE_FIXED:
    {
        SANE_Fixed value;
        lSANE_Status = m_saneCore->m_SANE_ENTRYPOINT.sane_control_option(m_now_sane_handle, option, SANE_ACTION_GET_VALUE, &value, nullptr);
        qv_Value = QVariant::fromValue(value);
        break;
    }
    case SANE_TYPE_STRING:
    {
        SANE_String value = nullptr;
        lSANE_Status = m_saneCore->m_SANE_ENTRYPOINT.sane_control_option(m_now_sane_handle, option, SANE_ACTION_GET_VALUE, value, nullptr);
        qv_Value = QVariant::fromValue(value);
        break;
    }
    case SANE_TYPE_BUTTON:
    {
        break;
    }
    case SANE_TYPE_GROUP:
    {
        break;
    }

    }
    if (lSANE_Status == SANE_STATUS_GOOD)
    {
        return true;
    }
    return false;
}

bool SaneAPP::sane_set_option(SANE_Int option, SANE_Value_Type valueType, QVariant& qv_Value)
{

    switch (valueType)
    {
    case SANE_TYPE_BOOL:
    {
        SANE_Bool value = qv_Value.value<SANE_Bool>();
        return m_saneCore->m_SANE_ENTRYPOINT.sane_control_option(m_now_sane_handle, option, SANE_ACTION_SET_VALUE, &value, nullptr) == SANE_STATUS_GOOD;
    }

    case SANE_TYPE_INT:
    {
        SANE_Int value = qv_Value.value<SANE_Int>();
        return m_saneCore->m_SANE_ENTRYPOINT.sane_control_option(m_now_sane_handle, option, SANE_ACTION_SET_VALUE, &value, nullptr) == SANE_STATUS_GOOD;
    }
    case SANE_TYPE_FIXED:
    {
        SANE_Fixed value = qv_Value.value<SANE_Fixed>();
        return m_saneCore->m_SANE_ENTRYPOINT.sane_control_option(m_now_sane_handle, option, SANE_ACTION_SET_VALUE, &value, nullptr) == SANE_STATUS_GOOD;
    }
    case SANE_TYPE_STRING:
    {
        SANE_String value = qv_Value.value<SANE_String>();
        return m_saneCore->m_SANE_ENTRYPOINT.sane_control_option(m_now_sane_handle, option, SANE_ACTION_SET_VALUE, value, nullptr) == SANE_STATUS_GOOD;
    }
    case SANE_TYPE_BUTTON:
    {
        return false;
    }
    case SANE_TYPE_GROUP:
    {
        return false;
    }
    }
    return false;
}

bool SaneAPP::sane_get_select_fd(SANE_Int* fd)
{
    if (m_now_sane_handle == nullptr)
    {
        return false;
    }
    SANE_Status lSANE_Status = m_saneCore->m_SANE_ENTRYPOINT.sane_get_select_fd(m_now_sane_handle, fd);
    return (lSANE_Status == SANE_STATUS_GOOD);

}

bool SaneAPP::sane_cancel()
{
    if (m_now_sane_handle == nullptr)
    {
        return false;
    }
    m_saneCore->m_SANE_ENTRYPOINT.sane_cancel(m_now_sane_handle);
    return true;
}
void SaneAPP::sane_exit()
{
    m_saneCore->m_SANE_ENTRYPOINT.sane_exit();
}

bool SaneAPP::sane_read(QByteArray& qByteArray)
{
    SANE_Status lSANE_Status;
    SANE_Byte data[32 * 1024];
    SANE_Int max_length = sizeof(data);
    SANE_Int length;
    SANE_Int init_filesize = qByteArray.size();
    SANE_Int filesize = qByteArray.size();
    while (1)
    {
        memset(data, 0x00, static_cast<size_t>(max_length));
        length = 0;
        lSANE_Status = m_saneCore->m_SANE_ENTRYPOINT.sane_read(m_now_sane_handle, data, max_length, &length);
        if (lSANE_Status != SANE_STATUS_GOOD)
        {
            if (lSANE_Status == SANE_STATUS_EOF)
                break;
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
        return true;
    }
    return false;
}


bool SaneAPP::sane_read(QImage& qImage)
{

    SANE_Parameters pars;
    if (!sane_get_parameters(pars))
    {
        return false;
    }
    QByteArray qByteArray;
    writeppm_header(pars, qByteArray);
    if (sane_read(qByteArray))
    {
        if (qImage.loadFromData(reinterpret_cast<uchar*>(qByteArray.data()), qByteArray.size()))
        {
            return true;
        }
    }
    return false;
}

void SaneAPP::writeppm_header(SANE_Parameters& pars, QByteArray& qByteArray)
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


bool SaneAPP::doScanToFile(QString ALLFilePath)
{
    if (sane_start())
    {
        QImage qImage;
        if (sane_read(qImage))
        {
            QFileInfo fileInfo(ALLFilePath);
            QDir dir;
            if (!dir.exists(fileInfo.absolutePath()))
            {
                if (!dir.mkpath(fileInfo.absolutePath()))
                {
                    sane_cancel();
                    return false;
                }
            }
            qImage.save(ALLFilePath, "JPG", 100);
            if (QFileInfo::exists(ALLFilePath))
            {
                sane_cancel();
                return true;
            }
        }
    }
    sane_cancel();
    return false;
}

bool SaneAPP::doScanToDir(QString ALLFilePath, QString& aFileNameList, QString& aFilesCount)
{
    Q_UNUSED(ALLFilePath);
    Q_UNUSED(aFileNameList);
    Q_UNUSED(aFilesCount);
    return false;
}

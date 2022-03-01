#include "scanner.h"
#ifdef APP_WINDOWS_X64
#else
Scanner::Scanner(QObject* parent) : QObject(parent)
{
//    m_sane_handle=new char[32];
    m_color_optionName = new char[32];
    m_dpi_optionName = new char[32];
    m_papersize_optionName = new char[32];
    m_tlxName = new char[32];
    m_tlyName = new char[32];
    m_brxName = new char[32];
    m_bryName = new char[32];
    m_selectFAName = new char[32];
    m_flatedName = new char[32];
    m_adfName = new char[32];
    m_adfDuplexName = new char[32];
    m_batchscanName = new char[32];
    m_sane_handle = new SANE_Handle();
}
Scanner::~Scanner()
{
    delete m_sane_handle, m_color_optionName, m_dpi_optionName, m_papersize_optionName, m_tlxName, m_tlyName, m_brxName, m_bryName, m_selectFAName, m_flatedName, m_adfName, m_sane_handle;
}
bool Scanner::set_color_optionName(SANE_String colorName)
{
    strcpy(m_color_optionName, colorName);
    return true;
}

bool Scanner::set_dpi_optionName(SANE_String dpi_Name)
{
    strcpy(m_dpi_optionName, dpi_Name);
    return true;
}

bool Scanner::set_papersize_optionName(SANE_String papersize_Name)
{
    strcpy(m_papersize_optionName, papersize_Name);
    return true;
}

bool Scanner::set_tlxName(SANE_String tlxName)
{
    strcpy(m_tlxName, tlxName);
    return true;
}

bool Scanner::set_tlyName(SANE_String tlyName)
{
    strcpy(m_tlyName, tlyName);
    return true;
}
bool Scanner::set_brxName(SANE_String brxName)
{
    strcpy(m_brxName, brxName);
    return true;
}

bool Scanner::set_bryName(SANE_String bryName)
{
    strcpy(m_bryName, bryName);
    return true;
}

bool Scanner::set_selectFAName(SANE_String selectFAName)
{
    strcpy(m_selectFAName, selectFAName);
    return true;
}
bool Scanner::set_flatedName(SANE_String flatedName)
{
    strcpy(m_flatedName, flatedName);
    return true;
}
bool Scanner::set_adfName(SANE_String adfName)
{
    strcpy(m_adfName, adfName);
    return true;
}
bool Scanner::set_adfDuplexName(SANE_String adfDuplexName)
{
    strcpy(m_adfDuplexName, adfDuplexName);
    return true;
}
bool Scanner::set_batchscanName(SANE_String batchscanName)
{
    strcpy(m_batchscanName, batchscanName);
    return true;

}
bool Scanner::set_color_optionID(SANE_Int color_ID)
{
    m_color_optionID = color_ID;
    return true;
}
bool Scanner::set_dpi_optionID(SANE_Int dpi_ID)
{
    m_dpi_optionID = dpi_ID;
    return true;
}
bool Scanner::set_papersize_optionID(SANE_Int papersize_ID)
{
    m_papersize_optionID = papersize_ID;
    return true;
}
bool Scanner::set_tlxID(SANE_Int tlxID)
{
    m_tlxID = tlxID;
    return true;
}
bool Scanner::set_tlyID(SANE_Int tlyID)
{
    m_tlyID = tlyID;
    return true;
}
bool Scanner::set_brxID(SANE_Int brxID)
{
    m_brxID = brxID;
    return true;
}
bool Scanner::set_bryID(SANE_Int bryID)
{
    m_bryID = bryID;
    return true;
}
bool Scanner::set_selectFAID(SANE_Int selectFAID)
{
    m_selectFAID = selectFAID;
    return true;
}
bool Scanner::set_batchscanID(SANE_Int batchscanID)
{
    m_batchscanID = batchscanID;
    return true;
}

SANE_String Scanner::get_color_optionName()
{
    return m_color_optionName;
}
SANE_String Scanner::get_dpi_optionName()
{
    return m_dpi_optionName;
}
SANE_String Scanner::get_papersize_optionName()
{
    return m_papersize_optionName;
}
SANE_String Scanner::get_tlxName()
{
    return m_tlxName;
}
SANE_String Scanner::get_tlyName()
{
    return m_tlyName;
}
SANE_String Scanner::get_brxName()
{
    return m_brxName;
}
SANE_String Scanner::get_bryName()
{
    return m_bryName;
}
SANE_String Scanner::get_selectFAName()
{
    return m_selectFAName;
}
SANE_String Scanner::get_flatedName()
{
    return m_flatedName;
}
SANE_String Scanner::get_adfName()
{
    return m_adfName;
}
SANE_String Scanner::get_adfDuplexName()
{
    return m_adfDuplexName;
}
SANE_String Scanner::get_batchscanName()
{
    return m_batchscanName;
}
SANE_Int Scanner::get_color_optionID()
{
    return m_color_optionID;
}
SANE_Int Scanner::get_dpi_optionID()
{
    return m_dpi_optionID;
}

SANE_Int Scanner::get_papersize_optionID()
{
    return m_papersize_optionID;
}
SANE_Int Scanner::get_tlxID()
{
    return m_tlxID;
}
SANE_Int Scanner::get_tlyID()
{
    return m_tlyID;
}
SANE_Int Scanner::get_brxID()
{
    return m_brxID;
}
SANE_Int Scanner::get_bryID()
{
    return m_bryID;
}
SANE_Int Scanner::get_selectFAID()
{
    return m_selectFAID;
}

SANE_Int Scanner::get_batchscanID()
{
    return m_batchscanID;
}
bool Scanner::set_saneHandle(SANE_Handle handle)
{
    m_sane_handle = handle;
    return true;
}

SANE_Handle Scanner::get_saneHandle()
{
    return m_sane_handle;
}

bool Scanner::set_sane_device(SANE_Device device)
{
    m_sane_device = device;
    return true;
}

SANE_Device Scanner::get_sane_device()
{
    return m_sane_device;
}

bool Scanner::set_scanner_name(QString scannername)
{
    m_scanner_name = scannername;

    return true;
}

QString Scanner::get_scanner_name()
{
    return m_scanner_name;
}
#endif


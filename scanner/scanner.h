#ifndef SCANNER_H
#define SCANNER_H
#ifdef APP_WINDOWS_X64
#else
#include "sane/include/sane.h"
#include <QObject>

class Scanner : public QObject
{
    Q_OBJECT
public:
    explicit Scanner(QObject* parent = nullptr);
    ~Scanner();
    bool set_color_optionName(SANE_String color_Name);
    bool set_dpi_optionName(SANE_String dpi_Name);
    bool set_papersize_optionName(SANE_String papersize_Name);
    bool set_tlxName(SANE_String tlxName);
    bool set_tlyName(SANE_String tlyName);
    bool set_brxName(SANE_String brxName);
    bool set_bryName(SANE_String bryName);
    bool set_selectFAName(SANE_String selectFAName);
    bool set_flatedName(SANE_String flatedName);
    bool set_adfName(SANE_String adfName);
    bool set_adfDuplexName(SANE_String adfDuplexName);
    bool set_batchscanName(SANE_String batchscanName);

    bool set_color_optionID(SANE_Int color_ID);
    bool set_dpi_optionID(SANE_Int dpi_ID);
    bool set_papersize_optionID(SANE_Int papersize_ID);
    bool set_tlxID(SANE_Int tlxID);
    bool set_tlyID(SANE_Int tlyID);
    bool set_brxID(SANE_Int brxID);
    bool set_bryID(SANE_Int bryID);
    bool set_selectFAID(SANE_Int selectFAID);
    bool set_batchscanID(SANE_Int batchscanID);

    SANE_String get_color_optionName();
    SANE_String get_dpi_optionName();
    SANE_String get_papersize_optionName();
    SANE_String get_tlxName();
    SANE_String get_tlyName();
    SANE_String get_brxName();
    SANE_String get_bryName();
    SANE_String get_selectFAName();
    SANE_String get_flatedName();
    SANE_String get_adfName();
    SANE_String get_adfDuplexName();
    SANE_String get_batchscanName();

    SANE_Int get_color_optionID();
    SANE_Int get_dpi_optionID();
    SANE_Int get_papersize_optionID();
    SANE_Int get_tlxID();
    SANE_Int get_tlyID();
    SANE_Int get_brxID();
    SANE_Int get_bryID();
    SANE_Int get_selectFAID();
    SANE_Int get_batchscanID();

    bool set_saneHandle(SANE_Handle handle);
    SANE_Handle get_saneHandle();

    bool set_sane_device(SANE_Device device);
    SANE_Device get_sane_device();

    bool set_scanner_name(QString scannername);
    QString get_scanner_name();
signals:

public slots:

private:
    QString m_scanner_name;
    SANE_Handle m_sane_handle = nullptr;
    SANE_String m_color_optionName = nullptr;
    SANE_String m_dpi_optionName = nullptr;
    SANE_String m_papersize_optionName = nullptr;
    SANE_String m_tlxName = nullptr;
    SANE_String m_tlyName = nullptr;
    SANE_String m_brxName = nullptr;
    SANE_String m_bryName = nullptr;
    SANE_String m_selectFAName = nullptr;
    SANE_String m_flatedName = nullptr;
    SANE_String m_adfName = nullptr;
    SANE_String m_adfDuplexName = nullptr;
    SANE_String m_batchscanName = nullptr;

    SANE_Int m_color_optionID;
    SANE_Int m_dpi_optionID;
    SANE_Int m_papersize_optionID;
    SANE_Int m_tlxID;
    SANE_Int m_tlyID;
    SANE_Int m_brxID;
    SANE_Int m_bryID;
    SANE_Int m_selectFAID;
    SANE_Int m_batchscanID;

    SANE_Device m_sane_device;
};
#endif
#endif // SCANNER_H


#ifndef SANECORE_H
#define SANECORE_H

#include <QObject>
#include <QLibrary>
#include <QGuiApplication>
#include <QMessageBox>
#include <QtDebug>
#include <QFile>
#include <QImage>
#include <QVariant>
#include <QFileInfo>
#include <QDir>
#include <stdlib.h>
#include "sane/include/sane.h"
#include "sane/include/saneopts.h"
#include <QDebug>
#include <QString>


Q_DECLARE_METATYPE(SANE_String);
Q_DECLARE_METATYPE(SANE_String_Const);


typedef SANE_Status(*LP_sane_init)(SANE_Int* version_code,
                                   SANE_Auth_Callback authorize);
typedef void (*LP_sane_exit)(void);
typedef SANE_Status(*LP_sane_get_devices)(const SANE_Device***  device_list,
                                          SANE_Bool local_only);
typedef SANE_Status(*LP_sane_open)(SANE_String_Const devicename,
                                   SANE_Handle* handle);
typedef void (*LP_sane_close)(SANE_Handle handle);
typedef const SANE_Option_Descriptor* (*LP_sane_get_option_descriptor)(SANE_Handle handle, SANE_Int option);
typedef SANE_Status(*LP_sane_control_option)(SANE_Handle handle, SANE_Int option,
                                             SANE_Action action, void* value,
                                             SANE_Int* info);
typedef SANE_Status(*LP_sane_get_parameters)(SANE_Handle handle,
                                             SANE_Parameters* params);
typedef SANE_Status(*LP_sane_start)(SANE_Handle handle);
typedef SANE_Status(*LP_sane_read)(SANE_Handle handle, SANE_Byte* data,
                                   SANE_Int max_length, SANE_Int* length);
typedef void (*LP_sane_cancel)(SANE_Handle handle);
typedef SANE_Status(*LP_sane_set_io_mode)(SANE_Handle handle,
                                          SANE_Bool non_blocking);
typedef SANE_Status(*LP_sane_get_select_fd)(SANE_Handle handle,
                                            SANE_Int* fd);
typedef SANE_String_Const(*LP_sane_strstatus)(SANE_Status status);


typedef struct
{
    LP_sane_init      sane_init = nullptr;
    LP_sane_exit      sane_exit = nullptr;
    LP_sane_get_devices   sane_get_devices = nullptr;
    LP_sane_open       sane_open = nullptr;
    LP_sane_close       sane_close = nullptr;
    LP_sane_get_option_descriptor     sane_get_option_descriptor = nullptr;
    LP_sane_control_option sane_control_option = nullptr;
    LP_sane_get_parameters sane_get_parameters = nullptr;
    LP_sane_start sane_start = nullptr;
    LP_sane_read sane_read = nullptr;
    LP_sane_cancel sane_cancel = nullptr;
    LP_sane_set_io_mode sane_set_io_mode = nullptr;
    LP_sane_get_select_fd sane_get_select_fd = nullptr;
    LP_sane_strstatus sane_strstatus = nullptr;
} SANE_ENTRYPOINT, *pSANE_ENTRYPOINT;


class SaneCore : public QObject
{
    Q_OBJECT
private:
    QLibrary lib;
public:
    SaneCore();
    ~SaneCore();
    bool Loadlib();
    bool Freelib();
    SANE_ENTRYPOINT m_SANE_ENTRYPOINT;
signals:

public slots:
};


class SaneAPP : public QObject
{
private:
    SaneCore* m_saneCore;
public:
    SaneAPP();
    ~SaneAPP();
    const  SANE_Device** m_device_list = nullptr;
    int m_device_list_count = 0; //设备个数
    int m_State = 0;
    int m_dogetdevicelist_times = 0; //获取设备列表函数执行的次数,外围控制是否还需要获取
    SANE_Handle m_now_sane_handle = nullptr;
    const SANE_Device* m_now_device = nullptr;
    static void SANE_Auth_Callback(SANE_String_Const resource,
                                   SANE_Char* username,
                                   SANE_Char* password);
    void initAPP();
    void reInitAPP();
    bool get_device_list();
    int get_device_list_count();

    bool sane_open(const SANE_Device* device);
    bool sane_open(int device_list_index = 0);

    bool sane_start();
    bool sane_set_io_mode(SANE_Bool non_blocking = SANE_FALSE);
    const SANE_Option_Descriptor* sane_get_option_descriptor(SANE_Int option);
    const SANE_Option_Descriptor* sane_get_option_descriptor(const char* name);
    bool sane_get_parameters(SANE_Parameters& pars);
    bool sane_control_option(SANE_Int option, SANE_Action action, void* value, SANE_Int* info);
    bool sane_get_option(SANE_Int option, SANE_Value_Type valueType, QVariant& qv_Value);
    bool sane_set_option(SANE_Int option, SANE_Value_Type valueType, QVariant& qv_Value);
    bool sane_get_select_fd(SANE_Int* fd);
    bool sane_read(QByteArray& qByteArray);
    bool sane_read(QImage& qImage);
    void writeppm_header(SANE_Parameters& pars, QByteArray& qByteArray);
    bool sane_close();
    bool sane_cancel();
    void sane_exit();
    bool doScanToFile(QString ALLFilePath);
    bool doScanToDir(QString ALLFilePath, QString& aFileNameList, QString& aFilesCount);
};

#endif // SANECORE_H

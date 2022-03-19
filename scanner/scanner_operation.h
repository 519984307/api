#ifndef SCANNER_OPERATION_H
#define SCANNER_OPERATION_H
#ifdef APP_WINDOWS_X64
#else
#include <QObject>
#include <QUuid>
#include "sane/include/sane.h"
#include "scanner.h"
#include <QJsonObject>
#include <QBuffer>
#include <QByteArray>
#include <QPointer>
#include <QList>
#include <QCryptographicHash>
class Scanner_Operation : public QObject
{
    Q_OBJECT
public:
    static Scanner_Operation* getInstance();
    ~Scanner_Operation() {};

    bool InitScanner(QString jsonfile);
    bool Sane_init();
    void UnitScanner(Scanner** scannerlist);
    bool doScanToFile(SANE_Handle handle, QString AllFilePath);
    bool doScanToDir_Test(SANE_Handle handle, QString lAllFileDir, QStringList& aFileNameList, QString& aFilesCount);
    bool doScanToDir(int type, SANE_Handle handle, QString lAllFileDir, QStringList& aFileNameList, QString& aFilesCount);
    bool doScanToDir_ZJ(SANE_Handle handle, QString lAllFileDir, QStringList& aFileNameList, QString& aFilesCount);
    bool doScanToDir_BT(SANE_Handle handle, QString lAllFileDir, QStringList& aFileNameList, QString& aFilesCount);

    bool read_image(SANE_Handle handle, QList<QImage*>& qImage);
    void writeppm_header(SANE_Parameters& pars, QByteArray& qByteArray);
    bool read_bytes(SANE_Handle handle, QByteArray& qByteArray,SANE_Parameters &pars);

    bool set_color_option(SANE_Handle handle, SANE_Int option, SANE_String value);
    bool set_DPI_option(SANE_Handle handle, SANE_Int option, SANE_Int& value);
    bool set_DPI_option_byte(SANE_Handle handle, SANE_Int option, SANE_Fixed& value);
    bool set_papersize_option(SANE_Handle handle, SANE_Int option, SANE_String value);

    bool set_autocropdeskew_enable(SANE_Handle handle, SANE_Int option, SANE_Bool& value);
    bool set_geometry(SANE_Handle handle, SANE_Int option, SANE_Int& value);
    bool set_geometry_Fixed(SANE_Handle handle, SANE_Int option, SANE_Fixed& value);
    bool set_source(SANE_Handle handle, SANE_Int option, SANE_String value);
    bool set_batchscan(SANE_Handle handle, SANE_Int option, SANE_Int& value);
    bool set_bg_color_option(SANE_Handle handle, SANE_Int option, SANE_String value);
    bool set_rotate_option(SANE_Handle handle, SANE_Int option, SANE_String value);
    int scanner_count = -1;
    bool init_status = false;
signals:

public slots:

private:
    Scanner_Operation() {};
    Scanner_Operation(const Scanner_Operation& obj) = delete;
    Scanner_Operation& operator=(const Scanner_Operation* obj) = delete;
    static Scanner_Operation* m_scanner_operation;

    bool parsing_configfile(QString file, QJsonObject& jsonobject);
public:
    Scanner** scannerlist;
};

#endif // SCANNER_OPERATION_H
#endif

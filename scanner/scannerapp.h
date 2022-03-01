#ifndef SCANNERAPP_H
#define SCANNERAPP_H

#include <QObject>
#ifdef APP_WINDOWS_X64
#include "scannerconfig.h"
#include "dtwaincore.h"
#else
#include "scanner_operation.h"
#include "scannerconfig_sane.h"
#endif

class ScannerApp : public QObject
{
    Q_OBJECT

public:
    static void InitAPP();

#ifdef APP_WINDOWS_X64
    static DTwainAPP* m_ScannerCore;
#else
    static Scanner_Operation* m_ScannerCore;
#endif

};

#endif // SCANNERAPP_H

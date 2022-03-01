#include "scannerapp.h"



#ifdef APP_WINDOWS_X64
DTwainAPP* ScannerApp::m_ScannerCore = nullptr;
#else
Scanner_Operation* ScannerApp::m_ScannerCore = nullptr;
#endif

void ScannerApp::InitAPP()
{
    if (m_ScannerCore != nullptr)
    {
        return;
    }
#ifdef APP_WINDOWS_X64
    ScannerApp::m_ScannerCore = DTwainAPP::getDTInstance();
    m_ScannerCore->initAPP();
#else
    ScannerApp::m_ScannerCore = Scanner_Operation::getInstance();
    m_ScannerCore->Sane_init();
#endif

}

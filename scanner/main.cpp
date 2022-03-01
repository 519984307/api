#include "scannerconfig.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ScannerAPP::InitAPP();
    ScannerConfig w;
    w.show();

    return a.exec();
}

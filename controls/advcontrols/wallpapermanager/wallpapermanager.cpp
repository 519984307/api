#include "wallpapermanager.h"

WallPaperManager::WallPaperManager(QObject* parent) : QObject(parent)
{

}

void WallPaperManager::changeWallPaper(QString path)
{
    if (path == "")
    {
        return;
    }
    TCHAR* ptch = (TCHAR*)(path.toStdWString().data()) ;   // 转换成宽字节，很重要，否则显示不了图片
    SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, ptch, SPIF_UPDATEINIFILE | SPIF_SENDWININICHANGE);

}

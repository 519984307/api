#include "imagebase.h"



bool isImageByFileExt(QString filePath)
{
    bool ret = false;
    QFileInfo info(filePath);
    if (info.exists())
    {
        QSet<QString> suffixes;
        suffixes << "jpg" << "jpeg" << "bmp" << "png";
        QString suffix = info.suffix().toLower();
        ret = suffixes.contains(suffix);
    }



    return ret;
}

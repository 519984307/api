#include "folderutils.h"



int getFileNumInFolder(QString path, QString suffix)
{
    int n = 0;
    QDir dir(path);

    QFileInfoList fileInfos = dir.entryInfoList();
    for (const QFileInfo& info : qAsConst(fileInfos))
    {
        if (info.suffix().toLower() == suffix.toLower())
        {
            n++;
        }
    }

    return n;
}

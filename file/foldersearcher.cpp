#include "foldersearcher.h"

FolderSearcher::FolderSearcher(QObject* parent) : QObject(parent)
{

}

void FolderSearcher::startSearch(QString path)
{
    QFileInfo info(path);
    folderlist << info;
    search(path);
}

void FolderSearcher::search(QString path)
{

    QDir dir(path);
    QFileInfoList infos = dir.entryInfoList();
    for (QFileInfo& info : infos)
    {

        if (info.isDir())
        {
            QString fileName = info.fileName();
            if ((fileName != ".") && (fileName != ".."))
            {
                folderlist << info;
                search(info.absoluteFilePath());
            }

        }
    }

}

int getImageFileNumInFolder(QString path)
{
    int i = 0;
    QDir dir(path);

    QFileInfoList infos = dir.entryInfoList();
    for (int i = 0; i < infos.count(); i++)
    {
        QFileInfo info = infos.at(i);
        if (info.isFile())
        {
            i++;
        }
    }

    return i;

}

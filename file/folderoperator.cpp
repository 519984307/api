#include "folderoperator.h"

FolderOperator::FolderOperator(QObject* parent) : QObject(parent)
{

}

void FolderOperator::copyFolder(QString srcFolder, QString destFolder)
{
    m_srcFolder = srcFolder;
    m_destFolder = destFolder;

    FileSeacher* searcher = new FileSeacher(this);
    connect(searcher, &FileSeacher::findFileInfo, this, [this](QString rootPath, QFileInfo & fileInfo)
    {

        QString srcfile = fileInfo.absoluteFilePath();
        QString destfile = srcfile;
        destfile = destfile.replace(m_srcFolder, m_destFolder);
        if (fileInfo.isDir())
        {
            QDir dir;
            dir.mkpath(destfile);

        }
        else
        {
            if (QFile::exists(destfile))
            {
                QFile::remove(destfile);
            }
            QFile::copy(srcfile, destfile);
        }
    });
    searcher->startSearch(srcFolder);
    delete searcher;


}

void FolderOperator::removeFilesInFolder(QString srcFolder)
{
    QStringList fileNames;
    QDir dir(srcFolder);
    QFileInfoList fileInfos = dir.entryInfoList();
    for (const QFileInfo& fileInfo : qAsConst(fileInfos))
    {
        fileNames << fileInfo.absoluteFilePath();

    }
    for (const QString& fileName : qAsConst(fileNames))
    {
        QFile::remove(fileName);
    }
}

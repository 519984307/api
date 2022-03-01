#ifndef FOLDERSEARCHER_H
#define FOLDERSEARCHER_H

#include <QObject>
#include <QDir>
#include <QDebug>


class FolderSearcher : public QObject
{
    Q_OBJECT
public:
    explicit FolderSearcher(QObject* parent = nullptr);
    void startSearch(QString path);
    QList<QFileInfo> folderlist;
private:
    void search(QString path);
signals:

};
int getImageFileNumInFolder(QString path);

#endif // FOLDERSEARCHER_H

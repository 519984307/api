#ifndef FOLDEROPERATOR_H
#define FOLDEROPERATOR_H

#include <QObject>
#include "fileseacher.h"

class FolderOperator : public QObject
{
    Q_OBJECT
public:
    explicit FolderOperator(QObject* parent = nullptr);
    void copyFolder(QString srcFolder, QString destFolder);
    void removeFilesInFolder(QString srcFolder);
private:
    QString m_srcFolder;
    QString m_destFolder;
signals:

};

#endif // FOLDEROPERATOR_H

#ifndef FNSHELLITEM_H
#define FNSHELLITEM_H

#include <QObject>
#include "../base/baseitem.h"
#include "fnshellfolderrect.h"

class FnShellFolderRect;
class FnShellItem : public BaseItem
{
    Q_OBJECT
public:
    explicit FnShellItem(QObject* parent = nullptr);

    bool isDir() const;
    void setIsDir(bool newIsDir);



    FnShellFolderRect* folderRect() const;
    void setFolderRect(FnShellFolderRect* newFolderRect);

signals:
private:
    bool m_isDir;
    FnShellFolderRect* m_folderRect;


};

#endif // FNSHELLITEM_H

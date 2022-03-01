#include "fnshellitem.h"

FnShellItem::FnShellItem(QObject* parent) : BaseItem(parent)
{

}

bool FnShellItem::isDir() const
{
    return m_isDir;
}

void FnShellItem::setIsDir(bool newIsDir)
{
    m_isDir = newIsDir;
}

FnShellFolderRect* FnShellItem::folderRect() const
{
    return m_folderRect;
}

void FnShellItem::setFolderRect(FnShellFolderRect* newFolderRect)
{
    m_folderRect = newFolderRect;
}



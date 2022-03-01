#include "fnshellfolderrect.h"

FnShellFolderRect::FnShellFolderRect(QObject* parent) : QObject(parent)
{
    m_width = 300;
    m_itemsTop = 16;
    m_selectedItem = nullptr;

}

FnShellFolderRect::~FnShellFolderRect()
{
    qDeleteAll(items);
    items.clear();

}

void FnShellFolderRect::append(QFileInfo& info)
{
    FnShellItem* item = new FnShellItem(this);
    item->setName(info.fileName());
    item->setPath(info.absoluteFilePath());
    QFileIconProvider provider;
    QIcon icon = provider.icon(info);
    item->setIcon(icon.pixmap(24, 24));
    item->setIsDir(info.isDir());
    item->setFolderRect(this);
    items << item;

}

int FnShellFolderRect::width() const
{
    return m_width;
}

void FnShellFolderRect::setWidth(int newWidth)
{
    m_width = newWidth;
}

int FnShellFolderRect::itemsTop() const
{
    return m_itemsTop;
}

void FnShellFolderRect::setItemsTop(int newItemsTop)
{
    m_itemsTop = newItemsTop;
}

int FnShellFolderRect::level() const
{
    return m_level;
}

void FnShellFolderRect::setLevel(int newLevel)
{
    m_level = newLevel;
}

const QRect& FnShellFolderRect::rect() const
{
    return m_rect;
}

void FnShellFolderRect::setRect(const QRect& newRect)
{
    m_rect = newRect;
}

FnShellItem* FnShellFolderRect::selectedItem() const
{
    return m_selectedItem;
}

void FnShellFolderRect::setSelectedItem(FnShellItem* newSelectedItem)
{
    m_selectedItem = newSelectedItem;
}

#ifndef FNSHELLFOLDERRECT_H
#define FNSHELLFOLDERRECT_H

#include <QObject>
#include "fnshellitem.h"
#include <QFileInfo>
#include <QFileIconProvider>

class FnShellItem;
class FnShellFolderRect : public QObject
{
    Q_OBJECT
public:
    explicit FnShellFolderRect(QObject* parent = nullptr);
    ~FnShellFolderRect();
    void append(QFileInfo& info);

    int width() const;
    void setWidth(int newWidth);
    QList<FnShellItem*> items;
    int itemsTop() const;
    void setItemsTop(int newItemsTop);

    int level() const;
    void setLevel(int newLevel);

    const QRect& rect() const;
    void setRect(const QRect& newRect);

    FnShellItem* selectedItem() const;
    void setSelectedItem(FnShellItem* newSelectedItem);

signals:
private:

    int m_width;
    int m_itemsTop;
    int m_level;
    QRect m_rect;
    FnShellItem* m_selectedItem;

};

#endif // FNSHELLFOLDERRECT_H

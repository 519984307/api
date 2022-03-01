#include "selectionitem.h"

SelectionItem::SelectionItem(QObject* parent)
    : QObject(parent)
{
    m_selected = false;
}

void SelectionItem::setItemRect(QRect& itemRect)
{
    m_itemRect = itemRect;
}

QRect& SelectionItem::itemRect()
{
    return m_itemRect;
}

QString SelectionItem::caption() const
{
    return m_caption;
}

void SelectionItem::setCaption(const QString& caption)
{
    m_caption = caption;
}

QPixmap SelectionItem::icon() const
{
    return m_icon;
}

void SelectionItem::setIcon(const QPixmap& icon)
{
    m_icon = icon.scaled(16, 16, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

bool SelectionItem::selected() const
{
    return m_selected;
}

void SelectionItem::setSelected(bool selected)
{
    m_selected = selected;
}

#include "tabitem.h"

TabItem::TabItem(QObject* parent) : QObject(parent)
{
    m_id = -1;

}

QString TabItem::caption() const
{
    return m_caption;
}

void TabItem::setCaption(const QString& caption)
{
    m_caption = caption;
}

int TabItem::width() const
{
    return m_width;
}

void TabItem::setWidth(int width)
{
    m_width = width;
}

int TabItem::height() const
{
    return m_height;
}

void TabItem::setHeight(int height)
{
    m_height = height;
}

int TabItem::index() const
{
    return m_index;
}

void TabItem::setIndex(int index)
{
    m_index = index;
}

bool TabItem::isActive() const
{
    return m_isActive;
}

void TabItem::setIsActive(bool isActive)
{
    m_isActive = isActive;
}

QRect TabItem::rect() const
{
    return m_rect;
}

void TabItem::setRect(const QRect& rect)
{
    m_rect = rect;
}

int TabItem::id() const
{
    return m_id;
}

void TabItem::setId(int newId)
{
    m_id = newId;
}

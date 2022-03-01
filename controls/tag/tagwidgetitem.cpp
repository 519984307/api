#include "tagwidgetitem.h"

TagWidgetItem::TagWidgetItem(QObject* parent) : QObject(parent)
{
    m_selected = false;

}

QString TagWidgetItem::caption() const
{
    return m_caption;
}

void TagWidgetItem::setCaption(const QString& caption)
{
    m_caption = caption;
}

QColor TagWidgetItem::color() const
{
    return m_color;
}

void TagWidgetItem::setColor(const QColor& color)
{
    m_color = color;
}

int TagWidgetItem::id() const
{
    return m_id;
}

void TagWidgetItem::setId(int id)
{
    m_id = id;
}

bool TagWidgetItem::selected() const
{
    return m_selected;
}

void TagWidgetItem::setSelected(bool selected)
{
    m_selected = selected;
}

int TagWidgetItem::index() const
{
    return m_index;
}

void TagWidgetItem::setIndex(int index)
{
    m_index = index;
}

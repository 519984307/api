#include "ganttcolumn.h"

GanttColumn::GanttColumn(QObject* parent) : QObject(parent)
{


}

const QString& GanttColumn::caption() const
{
    return m_caption;
}

int GanttColumn::width() const
{
    return m_width;
}

void GanttColumn::setCaption(const QString& newCaption)
{
    m_caption = newCaption;
}

void GanttColumn::setWidth(int newWidth)
{
    m_width = newWidth;
}

const QRect& GanttColumn::rect() const
{
    return m_rect;
}

void GanttColumn::setRect(const QRect& newRect)
{
    m_rect = newRect;
}

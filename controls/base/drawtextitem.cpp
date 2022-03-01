#include "drawtextitem.h"

DrawTextItem::DrawTextItem(QObject* parent) : QObject(parent)
{
    m_textColor = Qt::black;

}

const QString& DrawTextItem::text() const
{
    return m_text;
}

void DrawTextItem::setText(const QString& newText)
{
    m_text = newText;
}

const QRect& DrawTextItem::rect() const
{
    return m_rect;
}

void DrawTextItem::setRect(const QRect& newRect)
{
    m_rect = newRect;
}

const QColor& DrawTextItem::textColor() const
{
    return m_textColor;
}

void DrawTextItem::setTextColor(const QColor& newTextColor)
{
    m_textColor = newTextColor;
}

#include "imggoldrect.h"

ImgGoldRect::ImgGoldRect(QObject* parent) : QObject(parent)
{
    m_color = Qt::red;

}

ImgGoldRectType ImgGoldRect::rectType() const
{
    return m_rectType;
}

void ImgGoldRect::setRectType(const ImgGoldRectType& rectType)
{
    m_rectType = rectType;
}

QRect ImgGoldRect::rect() const
{
    return m_rect;
}

void ImgGoldRect::setRect(const QRect& rect)
{
    m_rect = rect;
}

QColor ImgGoldRect::color() const
{
    return m_color;
}

void ImgGoldRect::setColor(const QColor& color)
{
    m_color = color;
}

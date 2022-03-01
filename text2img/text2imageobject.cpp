#include "text2imageobject.h"

Text2ImageObject::Text2ImageObject(QObject* parent) : QObject(parent)
{

}

QString Text2ImageObject::text() const
{
    return m_text;
}

void Text2ImageObject::setText(const QString& text)
{
    m_text = text;
    m_length = m_text.toLocal8Bit().length();
}

QRect Text2ImageObject::textRect() const
{
    return m_textRect;
}

void Text2ImageObject::setTextRect(const QRect& textRect)
{
    m_textRect = textRect;
}

int Text2ImageObject::length() const
{
    return m_length;
}

void Text2ImageObject::setLength(int length)
{
    m_length = length;
}

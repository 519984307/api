#include "colorobject.h"

ColorObject::ColorObject(QObject* parent)
    : QObject(parent)
{
}

int ColorObject::id() const
{
    return m_id;
}

void ColorObject::setId(int id)
{
    m_id = id;
}

int ColorObject::r() const
{
    return m_r;
}

void ColorObject::setR(int r)
{
    m_r = r;
}

int ColorObject::g() const
{
    return m_g;
}

void ColorObject::setG(int g)
{
    m_g = g;
}

int ColorObject::b() const
{
    return m_b;
}

void ColorObject::setB(int b)
{
    m_b = b;
}

int ColorObject::a() const
{
    return m_a;
}

void ColorObject::setA(int a)
{
    m_a = a;
}

QRect ColorObject::rect() const
{
    return m_rect;
}

void ColorObject::setRect(const QRect& rect)
{
    m_rect = rect;
}

QString ColorObject::name() const
{
    return m_name;
}

void ColorObject::setName(const QString& name)
{
    m_name = name;
}

QColor ColorObject::color()
{
    return QColor(m_r, m_g, m_b);
}

QColor ColorObject::antiColor()
{
    return QColor(255 - m_r, 255 - m_g, 255 - m_b);
}

QString ColorObject::rgbColor()
{
    return QString("RGB:%1,%2,%3").arg(m_r).arg(m_g).arg(m_b);
}

QString ColorObject::htmlColor()
{
    return htmlColor(m_r, m_g, m_b);
}

QString ColorObject::htmlColor(int r, int g, int b)
{
    return QString("#%1%2%3").arg(intToHex(r)).arg(intToHex(g)).arg(intToHex(b));
}
QString ColorObject::intToHex(int i)
{
    QString ret = QString::number(i, 16);
    if (ret.length() == 1) {
        ret = "0" + ret;
    }
    return ret.toUpper();
}

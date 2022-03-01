#include "fngridline.h"

FnGridLine::FnGridLine(QObject* parent) : QObject(parent)
{
    m_isDraw = true;
    m_width = 1;
    m_color = Qt::black;

}

bool FnGridLine::isDraw() const
{
    return m_isDraw;
}

void FnGridLine::setIsDraw(bool isDraw)
{
    m_isDraw = isDraw;
}

int FnGridLine::width() const
{
    return m_width;
}

void FnGridLine::setWidth(int width)
{
    m_width = width;
}

QColor FnGridLine::color() const
{
    return m_color;
}

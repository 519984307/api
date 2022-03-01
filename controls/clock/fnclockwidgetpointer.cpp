#include "fnclockwidgetpointer.h"

FnClockWidgetPointer::FnClockWidgetPointer(QObject* parent) : QObject(parent)
{
    m_pointerType = tpHour;
    m_drawObj = new DrawObject(this);
    m_color = Qt::black;
    m_width = 3;

}

ClockPointerType FnClockWidgetPointer::pointerType() const
{
    return m_pointerType;
}

void FnClockWidgetPointer::setPointerType(const ClockPointerType& pointerType)
{
    m_pointerType = pointerType;
}

int FnClockWidgetPointer::value() const
{
    return m_value;
}

void FnClockWidgetPointer::setValue(int value)
{
    m_value = value;
}

double FnClockWidgetPointer::angle()
{

}

QPoint FnClockWidgetPointer::PointPos(QPoint centerPt, int r, QTime time)
{

    int h = time.hour();
    int m = time.minute();
    int s = time.second();
    int v = 0;
    if (m_pointerType == tpHour)
    {
        v = (h % 12) * 30 + m / 2;

    }
    else if (m_pointerType == tpMinute)
    {
        v = m * 6;

    }
    else
    {
        v = s * 6;
    }



    int x = centerPt.x() + r * cos(m_drawObj->angleToRadian(v - 90));
    int y = centerPt.y() + r * sin(m_drawObj->angleToRadian(v - 90));
    return QPoint(x, y);

}

void FnClockWidgetPointer::drawPointLine(QPainter& painter, QPoint centerPt, int r, QTime time)
{
    int h = time.hour();
    int m = time.minute();
    int s = time.second();
    int v = 0;
    if (m_pointerType == tpHour)
    {
        v = (h % 12) * 30 + m / 2;

    }
    else if (m_pointerType == tpMinute)
    {
        v = m * 6;

    }
    else
    {
        v = s * 6;
    }



    setStyle(painter);
    QMatrix matrix;
    matrix.translate(centerPt.x(), centerPt.y());
    matrix.rotate(v);
    painter.setMatrix(matrix);
    QPoint pt1 = QPoint(0, -r);
    QPoint pt2 = QPoint(0, 32);
    painter.drawLine(pt1, pt2);
    restore(painter);


}

QColor FnClockWidgetPointer::color() const
{
    return m_color;
}

void FnClockWidgetPointer::setColor(const QColor& color)
{
    m_color = color;
}

int FnClockWidgetPointer::width() const
{
    return m_width;
}

void FnClockWidgetPointer::setWidth(int width)
{
    m_width = width;
}

void FnClockWidgetPointer::setStyle(QPainter& painter)
{
    painter.save();
    QPen pen = painter.pen();
    pen.setColor(m_color);
    pen.setWidth(m_width);
    painter.setPen(pen);
}

void FnClockWidgetPointer::restore(QPainter& painter)
{
    painter.restore();
}

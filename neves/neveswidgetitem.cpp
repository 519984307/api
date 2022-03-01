#include "neveswidgetitem.h"

NevesWidgetItem::NevesWidgetItem(QObject* parent) : QObject(parent)
{

}

const QColor& NevesWidgetItem::color() const
{
    return m_color;
}

void NevesWidgetItem::setColor(const QColor& newColor)
{
    m_color = newColor;
}

NevesWidgetItemShape NevesWidgetItem::shape() const
{
    return m_shape;
}

void NevesWidgetItem::setShape(NevesWidgetItemShape newShape)
{
    m_shape = newShape;
}

QPoint NevesWidgetItem::center() const
{
    return m_center;
}

void NevesWidgetItem::setCenter(QPoint newCenter)
{
    m_center = newCenter;

}

int NevesWidgetItem::baseWidth() const
{
    return m_baseWidth;
}

void NevesWidgetItem::setBaseWidth(int newBaseWidth)
{
    m_baseWidth = newBaseWidth;
}

void NevesWidgetItem::drawShape(QPainter& painter)
{
    painter.save();
    painter.rotate(10);
    QPainterPath path;
    polygon.clear();
    QList<QPoint> pts;
    if (m_shape == 0)
    {

        pts << QPoint(m_center.x(), m_center.y() - m_baseWidth);
        pts << QPoint(m_center.x() - m_baseWidth * 2, m_center.y() + m_baseWidth);
        pts << QPoint(m_center.x() + m_baseWidth * 2, m_center.y() + m_baseWidth);

    }
    else if (m_shape == 1)
    {

        pts << QPoint(m_center.x() - m_baseWidth, m_center.y() - m_baseWidth * 2);
        pts << QPoint(m_center.x() - m_baseWidth, m_center.y() + m_baseWidth * 2);
        pts << QPoint(m_center.x() + m_baseWidth, m_center.y());

    }
    else if (m_shape == 2)
    {

        pts << QPoint(m_center.x() - m_baseWidth, m_center.y());
        pts << QPoint(m_center.x() + m_baseWidth, m_center.y() + m_baseWidth * 2);
        pts << QPoint(m_center.x() + m_baseWidth, m_center.y() - m_baseWidth * 2);

    }
    else if (m_shape == 3)
    {

        pts << QPoint(m_center.x() - m_baseWidth * 3, m_center.y() - m_baseWidth);
        pts << QPoint(m_center.x() + m_baseWidth, m_center.y() - m_baseWidth);
        pts << QPoint(m_center.x() + m_baseWidth, m_center.y() + m_baseWidth * 3);

    }
    else if (m_shape == 4)
    {

        pts << QPoint(m_center.x() - m_baseWidth * 2, m_center.y() - m_baseWidth);
        pts << QPoint(m_center.x() + m_baseWidth * 2, m_center.y() - m_baseWidth);
        pts << QPoint(m_center.x(), m_center.y() + m_baseWidth);

    }
    else if (m_shape == 5)
    {

        pts << QPoint(m_center.x() - m_baseWidth * 3, m_center.y() - m_baseWidth);
        pts << QPoint(m_center.x() + m_baseWidth, m_center.y() - m_baseWidth);
        pts << QPoint(m_center.x() + m_baseWidth * 3, m_center.y() + m_baseWidth);
        pts << QPoint(m_center.x() - m_baseWidth, m_center.y() + m_baseWidth);

    }
    else if (m_shape == 6)
    {

        pts << QPoint(m_center.x(), m_center.y() - m_baseWidth);
        pts << QPoint(m_center.x() - m_baseWidth, m_center.y());
        pts << QPoint(m_center.x(), m_center.y() + m_baseWidth);
        pts << QPoint(m_center.x() + m_baseWidth, m_center.y());

    }
    polygon.append(pts);
    path.addPolygon(polygon);
    painter.fillPath(path, m_color);
    painter.restore();

}

int NevesWidgetItem::index() const
{
    return m_index;
}

void NevesWidgetItem::setIndex(int newIndex)
{
    m_index = newIndex;
}

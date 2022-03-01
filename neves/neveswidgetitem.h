#ifndef NEVESWIDGETITEM_H
#define NEVESWIDGETITEM_H

#include <QObject>
#include <QColor>
#include <QPoint>
#include <QPainter>
#include <QPainterPath>
enum NevesWidgetItemShape
{
    NS_SHAPE_0 = 0,
    NS_SHAPE_1 = 1,
    NS_SHAPE_2 = 2,
    NS_SHAPE_3 = 3,
    NS_SHAPE_4 = 4,
    NS_SHAPE_5 = 5,
    NS_SHAPE_6 = 6,

};

class NevesWidgetItem : public QObject
{
    Q_OBJECT
public:
    explicit NevesWidgetItem(QObject* parent = nullptr);

    const QColor& color() const;
    void setColor(const QColor& newColor);

    NevesWidgetItemShape shape() const;
    void setShape(NevesWidgetItemShape newShape);

    QPoint center() const;
    void setCenter(QPoint newCenter);

    int baseWidth() const;
    void setBaseWidth(int newBaseWidth);
    void drawShape(QPainter& painter);
    QPolygon polygon;

    int index() const;
    void setIndex(int newIndex);

signals:
private:
    QColor m_color;
    NevesWidgetItemShape m_shape;
    QPoint m_center;
    int m_baseWidth;
    int m_index;

};

#endif // NEVESWIDGETITEM_H

#ifndef FNCLICKWIDGETPOINTER_H
#define FNCLICKWIDGETPOINTER_H

#include <QObject>
#include <QWidget>
#include "../../draw/drawobject.h"
#include <QTime>
enum ClockPointerType
{
    tpHour,
    tpMinute,
    tpSecond
};

class FnClockWidgetPointer : public QObject
{
    Q_OBJECT
public:
    explicit FnClockWidgetPointer(QObject* parent = nullptr);

    ClockPointerType pointerType() const;
    void setPointerType(const ClockPointerType& pointerType);

    int value() const;
    void setValue(int value);
    double angle();
    QPoint PointPos(QPoint centerPt, int r, QTime time);
    void drawPointLine(QPainter& painter, QPoint centerPt, int r, QTime time);
    QColor color() const;
    void setColor(const QColor& color);

    int width() const;
    void setWidth(int width);
    void setStyle(QPainter& painter);
    void restore(QPainter& painter);

signals:
private:
    ClockPointerType m_pointerType;
    int m_value;
    DrawObject* m_drawObj;
    QColor m_color;
    int m_width;

};

#endif // FNCLICKWIDGETPOINTER_H

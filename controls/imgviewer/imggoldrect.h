#ifndef IMGGOLDRECT_H
#define IMGGOLDRECT_H

#include <QObject>
#include <QWidget>

enum ImgGoldRectType
{
    tpHorRect,
    tpVerRect,
    tpLeftGoldSpiral,
    tpRightGoldSpiral,
    tpTopGoldSpiral,
    tpBottomGoldSpiral,
    tpNone

};
using ImgGoldRectCommand = ImgGoldRectType;
class ImgGoldRect : public QObject
{
    Q_OBJECT
public:
    explicit ImgGoldRect(QObject* parent = nullptr);

    ImgGoldRectType rectType() const;
    void setRectType(const ImgGoldRectType& rectType);

    QRect rect() const;
    void setRect(const QRect& rect);

    QColor color() const;
    void setColor(const QColor& color);

signals:
private:
    ImgGoldRectType m_rectType;
    QRect m_rect;
    QColor m_color;
};

#endif // IMGGOLDRECT_H

#ifndef IMAGESLIDER_H
#define IMAGESLIDER_H

#include <QWidget>
#include "imageobject.h"
#include "../base/widgethelper.h"
#include "parentimageviewer.h"
#include <QPainter>
namespace Ui
{
class ImageSlider;
}

class ImageSlider : public ParentImageViewer
{
    Q_OBJECT

public:
    explicit ImageSlider(QWidget* parent = nullptr);
    ~ImageSlider();
protected:
    void paintEvent(QPaintEvent* event);
    void wheelEvent(QWheelEvent* event);
    void mousePressEvent(QMouseEvent* event);
private:
    Ui::ImageSlider* ui;
    QColor m_bottomColor;
    QColor m_clientColor;
    QRect m_bottomRect;
    QRect m_clientRect;
    int m_snapLeft;
    QRect m_centerImgRect;
    QRect m_centerRect;
    QPixmap m_centerImg;
    double m_aspectRatio1;
    double m_aspectRatio2;

};

#endif // IMAGESLIDER_H

#ifndef HORPICTUREWATERFALL_H
#define HORPICTUREWATERFALL_H

#include <QWidget>
#include <QPainter>
#include <QDebug>
#include "imageobject.h"
#include "parentimageviewer.h"
#include <QException>

namespace Ui
{
class HorPictureWaterFall;
}

class HorPictureWaterFall : public ParentImageViewer
{
    Q_OBJECT

public:
    explicit HorPictureWaterFall(QWidget* parent = nullptr);
    ~HorPictureWaterFall();
    int getPictruesHeight(int k, int n);
protected:
    void paintEvent(QPaintEvent* event);
    void resizeEvent(QResizeEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
private:
    Ui::HorPictureWaterFall* ui;
    bool m_needCalImageHeight;
};

#endif // HORPICTUREWATERFALL_H

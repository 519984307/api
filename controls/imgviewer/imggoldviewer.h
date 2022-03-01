#ifndef IMGGOLDVIEWER_H
#define IMGGOLDVIEWER_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include "imggoldrect.h"
#include "../base/widgethelper.h"
#include "../../draw/drawobject.h"
#include <QWheelEvent>

namespace Ui
{
class ImgGoldViewer;
}

class ImgGoldViewer : public QWidget
{
    Q_OBJECT

public:
    explicit ImgGoldViewer(QWidget* parent = nullptr);
    ~ImgGoldViewer();
    QPixmap srcImg() const;
    void setSrcImg(const QPixmap& srcImg);


    QList<ImgGoldRect*> m_rects;


    ImgGoldRectCommand drawCommand() const;
    void setDrawCommand(const ImgGoldRectCommand& drawCommand);

protected:
    void paintEvent(QPaintEvent* event);

    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

private:
    Ui::ImgGoldViewer* ui;
    QPixmap m_srcImg;
    WidgetHelper* m_helper;
    ImgGoldRectCommand m_drawCommand;
    DrawObject* m_drawObj;
    QRect m_drawRect;
};

#endif // IMGGOLDVIEWER_H

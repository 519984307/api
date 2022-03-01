#ifndef BUTTONLIST_H
#define BUTTONLIST_H

#include <QWidget>
#include "buttonlistitem.h"
#include <QPainter>
#include <QPixmap>
#include <QStyle>
#include <QStyleOption>
#include <QStylePainter>
#include "../base/widgethelper.h"
#include <QWheelEvent>
#include "parentbuttonlist.h"

namespace Ui
{
class ButtonList;
}

class ButtonList : public ParentButtonList
{
    Q_OBJECT

public:
    explicit ButtonList(QWidget* parent = nullptr);
    ~ButtonList();





signals:

protected:
    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
private:
    Ui::ButtonList* ui;

};

#endif // BUTTONLIST_H

#ifndef ICONTOOLBAR_H
#define ICONTOOLBAR_H

#include <QWidget>
#include <QPixmap>

#include "../base/widgethelper.h"
#include "icontoolbaritem.h"
#include "../base/basewidget.h"

namespace Ui
{
class IconToolBar;
}

class IconToolBar : public BaseWidget
{
    Q_OBJECT

public:
    explicit IconToolBar(QWidget* parent = nullptr);
    ~IconToolBar();
    void addItem(IconToolbarItem* item);

    const QList<IconToolbarItem*>& items() const;
    void setItems(const QList<IconToolbarItem*>& newItems);
    const QColor& backgroundColor() const;
    void setBackgroundColor(const QColor& newBackgroundColor);



    const QPixmap& backgroundImage() const;
    void setBackgroundImage(const QPixmap& newBackgroundImage);
    void selectItem(IconToolbarItem* selItem);

signals:
    void clickItem(IconToolbarItem* item);
protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
private:
    Ui::IconToolBar* ui;
    QList<IconToolbarItem*> m_items;
    QColor m_backgroundColor;
    QPixmap m_backgroundImage;
};

#endif // ICONTOOLBAR_H

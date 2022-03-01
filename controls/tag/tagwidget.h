#ifndef TAGWIDGET_H
#define TAGWIDGET_H

#include <QWidget>
#include "tagwidgetitem.h"
#include <QPainter>
#include <QDebug>

namespace Ui
{
class TagWidget;
}
class TagWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TagWidget(QWidget* parent = nullptr);
    ~TagWidget();
    void addTag(int id, QString caption);
    QList<TagWidgetItem*> items;
    int itemsLeft() const;
    void setItemsLeft(int itemsLeft);
    void setSelectedByIndex(int index);
    void clearItems();


    int currentSelectedIndex() const;

signals:
    void onItemSelected(TagWidgetItem* item);
protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
private:
    Ui::TagWidget* ui;
    int m_itemsLeft;
    QPoint m_mousedownPoint;
    QPoint m_mouseclickPoint;
    bool m_mousedownFlag;
    int m_itemsWidth;
    int m_currentSelectedIndex;
};

#endif // TAGWIDGET_H

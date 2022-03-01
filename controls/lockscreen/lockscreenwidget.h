#ifndef LOCKSCREENWIDGET_H
#define LOCKSCREENWIDGET_H

#include <QWidget>
#include <QPainter>
#include "lockscreenitem.h"
#include "../base/widgethelper.h"

namespace Ui
{
class LockScreenWidget;
}

class LockScreenWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LockScreenWidget(QWidget* parent = nullptr);
    ~LockScreenWidget();
protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

private:
    Ui::LockScreenWidget* ui;
    QList<LockScreenItem*> m_items;
    QList<LockScreenItem*> m_paths;
    WidgetHelper* m_helper;
    LockScreenItem* getHoverItem();
    void initItems();
};

#endif // LOCKSCREENWIDGET_H

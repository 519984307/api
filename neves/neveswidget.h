#ifndef NEVESWIDGET_H
#define NEVESWIDGET_H

#include <QWidget>
#include <QPainter>
#include "neveswidgetitem.h"
#include "../controls/base/widgethelper.h"
using namespace std;

namespace Ui
{
class NevesWidget;
}

class NevesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NevesWidget(QWidget* parent = nullptr);
    ~NevesWidget();
    int baseWidth() const;
    void setBaseWidth(int newBaseWidth);
    QList<NevesWidgetItem*> items;
    QPoint center() const;
    void setCenter(QPoint newCenter);
    void reset();

    NevesWidgetItem* selectItem() const;
    void setSelectItem(NevesWidgetItem* newSelectItem);

protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
private:
    Ui::NevesWidget* ui;
    int m_baseWidth;
    QPoint m_center;
    NevesWidgetItem* m_selectItem;
    WidgetHelper* m_helper;

};

#endif // NEVESWIDGET_H

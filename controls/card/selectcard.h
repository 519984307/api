#ifndef SELECTCARD_H
#define SELECTCARD_H

#include <QWidget>
#include <QPainter>
#include <QDebug>
#include "selectcarditem.h"
#include "../base/widgethelper.h"
#include "../../draw/drawobject.h"
#include <QWheelEvent>
#include <QAction>
#include <QApplication>
#include <QClipboard>
#include <QStackedWidget>
#include "newselectcardwidgetwindow.h"

namespace Ui
{
class SelectCard;
}

class SelectCardItem;
class SelectCard : public QWidget
{
    Q_OBJECT

public:
    explicit SelectCard(QWidget* parent = nullptr);
    ~SelectCard();
    SelectCardItem* addItem(QString caption, int id);
    SelectCardItem* addItem(QString caption, QString uuid, QWidget* w);
    SelectCardItem* openOrAddItem(QString caption, QString uuid, QWidget* w);
    void setSelected(SelectCardItem* otherItem);
    bool hasItemId(int id);
    void mousePressEvent(QMouseEvent* event);
    void updateItemText(int id, QString& s);
    void deleteItemById(int id);
    void deletItemByUuid(QString uuid);
    void deleteItem(SelectCardItem* item);
    SelectCardItem* getPointInItem();
    QStackedWidget* getStackedWidget() const;
    void setStackedWidget(QStackedWidget* stackedWidget);
    void floatSelectWindow(SelectCardItem* item);

    SelectCardItem* itemByUuid(QString uuid);
    void makeItemShow(SelectCardItem* item);

signals:
    void itemSelect(SelectCardItem* item);
    void itemRemove(SelectCardItem* item);
public slots:
    void onMenuItemTriggerd();
protected:
    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);
private:
    Ui::SelectCard* ui;
    QList<SelectCardItem*> items;
    WidgetHelper* m_helper;
    DrawObject* m_drawObj;
    QPoint m_rightMousePt;
    QStackedWidget* m_stackedWidget;
    void addMenus();
};

#endif // SELECTCARD_H

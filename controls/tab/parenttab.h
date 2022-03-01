#ifndef PARENTTAB_H
#define PARENTTAB_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include "tabitem.h"
#include "../base/widgethelper.h"
class ParentTab : public QWidget
{
    Q_OBJECT
public:
    explicit ParentTab(QWidget* parent = nullptr);
    TabItem* addItem(QString caption);


    int index() const;
    void setIndex(int index);

    int activeIndex() const;
    void setActiveIndex(int activeIndex);

    int defaultButtonWidth() const;
    void setDefaultButtonWidth(int defaultButtonWidth);
    QList<QAction*>& tabItemActions(QString caption);
    void clearItems();

signals:
    void tabItemClick(TabItem* item);
protected:
    QList<TabItem*> m_items;
    WidgetHelper* m_helper;
    int m_activeIndex;
    int m_defaultButtonWidth;

};

#endif // PARENTTAB_H

#ifndef PARENTBUTTONLIST_H
#define PARENTBUTTONLIST_H

#include <QWidget>
#include "buttonlistitem.h"
#include <QPainter>
#include <QPixmap>
#include <QStyle>
#include <QStyleOption>
#include <QStylePainter>
#include "../base/widgethelper.h"
#include <QWheelEvent>

class ParentButtonList : public QWidget
{
    Q_OBJECT
public:
    explicit ParentButtonList(QWidget* parent = nullptr);

    const QList<ButtonListItem*>& items() const;
    void setItems(const QList<ButtonListItem*>& newItems);
    void addButtons(QStringList& buttonNames);
    int activeIndex() const;
    void setActiveIndex(int newActiveIndex);

    int maxCaptionLen() const;
    void setMaxCaptionLen(int newMaxCaptionLen);

signals:
    void clickButton(ButtonListItem* item);
protected:
    QList<ButtonListItem*> m_items;
    WidgetHelper* m_helper;
    int m_activeIndex;
    int m_maxCaptionLen;

};

#endif // PARENTBUTTONLIST_H

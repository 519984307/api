#ifndef ICONTOOLBARITEM_H
#define ICONTOOLBARITEM_H

#include <QObject>
#include <QWidget>
#include "../base/baseitem.h"

class IconToolbarItem : public BaseItem
{
    Q_OBJECT
public:
    explicit IconToolbarItem(QObject* parent = nullptr);

signals:


};

#endif // ICONTOOLBARITEM_H

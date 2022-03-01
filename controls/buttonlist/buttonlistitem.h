#ifndef BUTTONLISTITEM_H
#define BUTTONLISTITEM_H

#include <QObject>
#include "../base/baseitem.h"

class ButtonListItem : public BaseItem
{
    Q_OBJECT
public:
    explicit ButtonListItem(QObject *parent = nullptr);

signals:

};

#endif // BUTTONLISTITEM_H

#ifndef INFOLISTITEM_H
#define INFOLISTITEM_H

#include <QObject>
#include "../base/baseitem.h"
#include "../api/color/colortable.h"

class InfoListItem : public BaseItem
{
    Q_OBJECT
public:
    explicit InfoListItem(QObject* parent = nullptr);

signals:

};

#endif // INFOLISTITEM_H

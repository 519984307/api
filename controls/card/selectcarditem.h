#ifndef SELECTCARDITEM_H
#define SELECTCARDITEM_H

#include <QObject>
#include <QWidget>
#include "../base/baseitem.h"
#include "selectcard.h"

#include <QDebug>

class SelectCard;
class SelectCardItem : public BaseItem
{
    Q_OBJECT
public:
    explicit SelectCardItem(QObject* parent = nullptr);
    void setIcon(const QPixmap& icon);


signals:
private:

};

#endif // SELECTCARDITEM_H

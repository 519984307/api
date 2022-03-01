#ifndef QUICKSELECTORITEM_H
#define QUICKSELECTORITEM_H

#include <QObject>
#include <QWidget>
#include "abstractquicknode.h"

class QuickSelectorItem : public AbstractQuickNode
{
    Q_OBJECT
public:
    explicit QuickSelectorItem(QObject* parent = nullptr);

signals:

};

#endif // QUICKSELECTORITEM_H

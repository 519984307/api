#ifndef QUICKSELECTORBUTTON_H
#define QUICKSELECTORBUTTON_H

#include <QObject>
#include <QWidget>
#include "abstractquicknode.h"
#include "quickselectoritem.h"

class QuickSelectorButton : public AbstractQuickNode
{
    Q_OBJECT
public:
    explicit QuickSelectorButton(QObject* parent = nullptr);
    QList<QuickSelectorItem*> items;
    void addItem(QuickSelectorItem* item);


signals:
private:



};

#endif // QUICKSELECTORBUTTON_H

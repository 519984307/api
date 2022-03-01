#include "quickselectorbutton.h"

QuickSelectorButton::QuickSelectorButton(QObject* parent) : AbstractQuickNode(parent)
{

}

void QuickSelectorButton::addItem(QuickSelectorItem* item)
{
    items << item;

}




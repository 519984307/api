#include "selectcarditem.h"

SelectCardItem::SelectCardItem(QObject* parent) : BaseItem(parent)
{


}

void SelectCardItem::setIcon(const QPixmap& icon)
{
    BaseItem::setIcon(icon);
    SelectCard* card = static_cast<SelectCard*>(parent());
    // card->makeItemShow(this);

}



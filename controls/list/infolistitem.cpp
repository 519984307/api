#include "infolistitem.h"

InfoListItem::InfoListItem(QObject* parent) : BaseItem(parent)
{
    m_color = ColorTable::getRandomColor();

}

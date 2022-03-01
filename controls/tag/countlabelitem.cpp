#include "countlabelitem.h"

CountLabelItem::CountLabelItem(QObject* parent) : BaseItem(parent)
{
    m_backgroundColor = ColorTable::getRandomColor();

}

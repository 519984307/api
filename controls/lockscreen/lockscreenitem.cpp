#include "lockscreenitem.h"

LockScreenItem::LockScreenItem(QObject* parent) : BaseItem(parent)
{

}

QRect LockScreenItem::centerRect() const
{
    return m_centerRect;
}

void LockScreenItem::setCenterRect(const QRect& centerRect)
{
    m_centerRect = centerRect;
}

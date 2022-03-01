#ifndef LOCKSCREENITEM_H
#define LOCKSCREENITEM_H

#include <QObject>
#include "../base/baseitem.h"

class LockScreenItem : public BaseItem
{
    Q_OBJECT
public:
    explicit LockScreenItem(QObject* parent = nullptr);

    QRect centerRect() const;
    void setCenterRect(const QRect& centerRect);

signals:
private:
    QRect m_centerRect;

};

#endif // LOCKSCREENITEM_H

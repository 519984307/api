#ifndef RANDOMMACFUNCTIONITEM_H
#define RANDOMMACFUNCTIONITEM_H

#include <QObject>
#include "../abstractfunctionitem.h"
#include <QRandomGenerator>

class RandomMACFunctionItem : public AbstractFunctionItem
{
    Q_OBJECT
public:
    explicit RandomMACFunctionItem(QObject* parent = nullptr);
    QString run();
signals:

};

#endif // RANDOMMACFUNCTIONITEM_H

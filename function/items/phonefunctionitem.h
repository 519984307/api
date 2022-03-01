#ifndef PHONEFUNCTIONITEM_H
#define PHONEFUNCTIONITEM_H

#include <QObject>
#include "../abstractfunctionitem.h"
#include <QDateTime>
#include <QRandomGenerator>

class PhoneFunctionItem : public AbstractFunctionItem
{
    Q_OBJECT
public:
    explicit PhoneFunctionItem(QObject* parent = nullptr);

signals:
public:
    QString run();

};

#endif // PHONEFUNCTIONITEM_H

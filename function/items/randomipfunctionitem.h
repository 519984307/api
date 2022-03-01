#ifndef RANDOMIPFUNCTIONITEM_H
#define RANDOMIPFUNCTIONITEM_H

#include <QObject>
#include <QRandomGenerator>
#include "../abstractfunctionitem.h"

class RandomIPFunctionItem : public AbstractFunctionItem
{
    Q_OBJECT
public:
    explicit RandomIPFunctionItem(QObject* parent = nullptr);
    QString run();
signals:


};

#endif // RANDOMIPFUNCTIONITEM_H

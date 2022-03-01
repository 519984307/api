#ifndef IDCARDFUNCTIONITEM_H
#define IDCARDFUNCTIONITEM_H

#include <QObject>
#include "../abstractfunctionitem.h"
#include <QRandomGenerator>
#include <QDate>

class IDCardFunctionItem : public AbstractFunctionItem
{
    Q_OBJECT
public:
    explicit IDCardFunctionItem(QObject* parent = nullptr);

signals:
public:
    QString run();

};

#endif // IDCARDFUNCTIONITEM_H

#ifndef NOWDATEFUNCTIONITEM_H
#define NOWDATEFUNCTIONITEM_H

#include <QObject>
#include "../abstractfunctionitem.h"
#include <QDate>

class NowDateFunctionItem : public AbstractFunctionItem
{
    Q_OBJECT
public:
    explicit NowDateFunctionItem(QObject* parent = nullptr);

signals:
public:
    QString run();
};

#endif // NOWDATEFUNCTIONITEM_H

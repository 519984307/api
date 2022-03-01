#ifndef NOWDATETIMEFUNCTIONITEM_H
#define NOWDATETIMEFUNCTIONITEM_H

#include <QObject>
#include "../abstractfunctionitem.h"
#include <QDateTime>

class NowDateTimeFunctionItem : public AbstractFunctionItem
{
    Q_OBJECT
public:
    explicit NowDateTimeFunctionItem(QObject* parent = nullptr);


signals:
public:
    QString run();


};

#endif // NOWDATETIMEFUNCTIONITEM_H

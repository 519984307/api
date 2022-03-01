#ifndef NEWUUIDFUNTIONITEM_H
#define NEWUUIDFUNTIONITEM_H

#include <QObject>
#include <QUuid>
#include "../abstractfunctionitem.h"
class NewUUIDFuntionItem : public AbstractFunctionItem
{
    Q_OBJECT
public:
    explicit NewUUIDFuntionItem(QObject* parent = nullptr);

signals:
public:
    QString run();

};

#endif // NEWUUIDFUNTIONITEM_H

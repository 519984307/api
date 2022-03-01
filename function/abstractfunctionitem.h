#ifndef ABSTRACTFUNCTIONITEM_H
#define ABSTRACTFUNCTIONITEM_H

#include <QObject>
#include "../base/fnobject.h"
#include <QRandomGenerator>

enum FunctionParamType
{
    FUN_NOPARM,
    FUNC_INT,
    FUNC_UNKNOW
};

class AbstractFunctionItem : public FnObject
{
    Q_OBJECT
public:
    explicit AbstractFunctionItem(QObject* parent = nullptr);
public:
    virtual QString run();

signals:
protected:



};

#endif // ABSTRACTFUNCTIONITEM_H

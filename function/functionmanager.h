#ifndef FUNCTIONMANAGER_H
#define FUNCTIONMANAGER_H

#include <QObject>
#include <QDebug>
#include "abstractfunctionitem.h"

class FunctionManager : public QObject
{
    Q_OBJECT
public:
    explicit FunctionManager(QObject* parent = nullptr);
    QList<AbstractFunctionItem*> items;
    QString run(QString funcInfo);
    QString getFuncName(QString funcInfo);
    QString getFuncParams(QString funcInfo);
    FunctionParamType getFuncParamType(QString params);
    QStringList funcNames();
    QStringList functionNames();
    bool tryRun(QString funcInfo);
signals:

};

#endif // FUNCTIONMANAGER_H

#include "functionmanager.h"

FunctionManager::FunctionManager(QObject* parent) : QObject(parent)
{

}

QString FunctionManager::run(QString funcInfo)
{
    QString funcName = getFuncName(funcInfo);
    QString params = getFuncParams(funcInfo);
    qDebug() << params;
    AbstractFunctionItem* item = getObjectByName<AbstractFunctionItem*>(items, funcName);
    if (item == nullptr)
    {
        return "";
    }
    FunctionParamType paramType = getFuncParamType(params);
    if (paramType == FUN_NOPARM)
    {
        return item->run();
    }

    return "";

}

QString FunctionManager::getFuncName(QString funcInfo)
{
    int m = funcInfo.indexOf("(");
    if (m >= 0)
    {
        return funcInfo.left(m);
    }
    else
    {
        return funcInfo;
    }

}

QString FunctionManager::getFuncParams(QString funcInfo)
{
    int m = funcInfo.indexOf("(");
    if (m >= 0)
    {
        int n = funcInfo.indexOf(")");
        if (n >= 0)
        {
            QString params = funcInfo.mid(m + 1, n - m - 1);
            return params.trimmed();
        }
        else
        {
            return "";
        }
    }
    else
    {
        return "";
    }
}

FunctionParamType FunctionManager::getFuncParamType(QString params)
{

    if (params == "")
    {
        return FUN_NOPARM;
    }
    return FUNC_UNKNOW;

}

QStringList FunctionManager::funcNames()
{
    QStringList names;
    for (int i = 0; i < items.count(); i++)
    {
        names << items.at(i)->name();
    }
    return names;

}

QStringList FunctionManager::functionNames()
{
    QStringList names;
    for (int i = 0; i < items.count(); i++)
    {
        names << items.at(i)->name() + "()";
    }
    return names;
}

bool FunctionManager::tryRun(QString funcInfo)
{
    bool ret = false;
    for (int i = 0; i < items.count(); i++)
    {
        AbstractFunctionItem* item = items.at(i);
        if (funcInfo.startsWith(item->name() + "("))
        {
            ret = true;
            break;
        }
    }

    return ret;

}

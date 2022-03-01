#ifndef STRINGPARAMPROCESSER_H
#define STRINGPARAMPROCESSER_H

#include <QObject>
#include <QMap>
#include <QDebug>
#include <QTime>
#include <time.h>
#include <QThread>
#include <QApplication>
#include "../function/functionmanager.h"

class StringParamProcesser : public QObject
{
    Q_OBJECT
public:
    explicit StringParamProcesser(QObject* parent = nullptr);

    QString srcInfo() const;
    void setSrcInfo(const QString& srcInfo);
    QMap<QString, QStringList> paramValues;
    QSet<QString> params;
    void getParams();
    QString getRandomDestInfo();
    QString getRandomValue(QString name);

    FunctionManager* getFunctionManager() const;
    void setFunctionManager(FunctionManager* functionManager);

signals:
    QStringList getCustomValues(QString p);
private:
    QString m_srcInfo;
    FunctionManager* m_functionManager;

};

#endif // STRINGPARAMPROCESSER_H

#ifndef RANDOMNAMEFUNCTIONITEM_H
#define RANDOMNAMEFUNCTIONITEM_H

#include <QObject>
#include "../abstractfunctionitem.h"
#include <QThread>
#include <QApplication>

class RandomNameFunctionItem : public AbstractFunctionItem
{
    Q_OBJECT
public:
    explicit RandomNameFunctionItem(QObject* parent = nullptr);
    QString run();

signals:

};

#endif // RANDOMNAMEFUNCTIONITEM_H

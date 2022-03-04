#ifndef ABSTRACTPRINTER_H
#define ABSTRACTPRINTER_H

#include <QObject>
#include <QPrinter>
#include <QPainter>

class AbstractPrinter : public QObject
{
    Q_OBJECT
public:
    explicit AbstractPrinter(QObject* parent = nullptr);
public:
    virtual void print();
signals:

};

#endif // ABSTRACTPRINTER_H

#ifndef REPORTPRINTER_H
#define REPORTPRINTER_H

#include <QObject>
#include <QDebug>
#include "abstractprinter.h"
#include "reportpage.h"

class ReportPrinter : public AbstractPrinter
{
    Q_OBJECT
public:
    explicit ReportPrinter(QObject* parent = nullptr);
    virtual void print();
    QList<ReportPage*> pages;
signals:
private:
    QPrinter* m_printer;
    DrawObject* m_drawObj;

};

#endif // REPORTPRINTER_H

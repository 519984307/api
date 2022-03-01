#ifndef FNCALENDERBASE_H
#define FNCALENDERBASE_H

#include <QObject>
#include <QWidget>
#include <QDate>
#include "lunar.h"
struct FnCalenderData
{
    int line;
    int year;
    int month;
    int day;
    QRect rc;
    QDate date;
    QString lunarDate;
    QString lunarDay;
    bool isNull = false;
};

#endif // FNCALENDERBASE_H

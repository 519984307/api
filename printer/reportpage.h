#ifndef REPORTPAGE_H
#define REPORTPAGE_H

#include <QObject>
#include "reportcell.h"
#include <QPainter>

class ReportPage : public QObject
{
    Q_OBJECT
public:
    explicit ReportPage(QObject* parent = nullptr);
    QList<ReportCell*> cells;
    void addTitle(int top, int height, QString text);
    void draw(QPainter& painter);
signals:

};

#endif // REPORTPAGE_H

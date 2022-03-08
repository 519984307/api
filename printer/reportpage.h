#ifndef REPORTPAGE_H
#define REPORTPAGE_H

#include <QObject>
#include "reportcell.h"
#include <QPainter>
#include "../draw/drawobject.h"
class ReportPage : public QObject
{
    Q_OBJECT
public:
    explicit ReportPage(QObject* parent = nullptr);
    QList<ReportCell*> cells;
    void addTitle(int top, int height, QString text);
    void draw(QPainter& painter);
    double factor() const;
    void setFactor(double newFactor);
    void addCell(ReportCell* cell);
    ReportCell* addCellAtRight(ReportCell* leftCell, int width, QString text);

signals:
private:
    double m_factor;
    DrawObject* m_drawObj;

};

#endif // REPORTPAGE_H

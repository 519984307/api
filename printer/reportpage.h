#ifndef REPORTPAGE_H
#define REPORTPAGE_H

#include <QObject>
#include "reportcell.h"
#include <QPainter>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
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
    double addHorCells(double left, double top, double height, QStringList& values, QList<double>& widths);
    ReportCell* addCellAtRight(ReportCell* leftCell, int width, QString text);
    void addCellsFromJson(QString fileName);
    void addCellsFromJson(QString fileName, QStringList& values, double& cellsHeight);
    void appendCellsFromJson(QString fileName, QStringList& values, double& cellsHeight, double topMargin);
signals:
private:
    double m_factor;
    DrawObject* m_drawObj;

};

#endif // REPORTPAGE_H

#ifndef FNPOINTCHART_H
#define FNPOINTCHART_H

#include <QWidget>
#include "fnchartvalues.h"
#include <QPainter>
#include <QWheelEvent>
#include <QDebug>

namespace Ui
{
class FnPointChart;
}

class FnPointChart : public QWidget
{
    Q_OBJECT

public:
    explicit FnPointChart(QWidget* parent = nullptr);
    ~FnPointChart();
    void addChartValues(FnChartValues* values);
    int zoomValue() const;
    void setZoomValue(int zoomValue);
    void wheelEvent(QWheelEvent* event);
protected:
    void paintEvent(QPaintEvent* event);
private:
    Ui::FnPointChart* ui;
    QList<FnChartValues*> m_series;
    int m_zoomValue;
};

#endif // FNPOINTCHART_H

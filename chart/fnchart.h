#ifndef FNCHART_H
#define FNCHART_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include "fnchartxlabel.h"
#include "../controls/base/widgethelper.h"
#include "fnchartvalues.h"
#include <QKeyEvent>
namespace Ui
{
class FnChart;
}

class FnChart : public QWidget
{
    Q_OBJECT

public:
    explicit FnChart(QWidget* parent = nullptr);
    ~FnChart();

    int originX() const;
    void setOriginX(int originX);

    int originY() const;
    void setOriginY(int originY);

    int zoomX() const;
    void setZoomX(int zoomX);

    int zoomY() const;
    void resetOrigin();
    void addXLabel(QString caption);

    int xLabelWidth() const;
    void setXLabelWidth(int xLabelWidth);
    void addChartValues(FnChartValues* values);

protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void resizeEvent(QResizeEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
private:
    Ui::FnChart* ui;
    int m_originX;
    int m_originY;
    int m_zoomX;
    int m_zoomY;
    int m_xLabelWidth;
    int m_startX;
    int m_startY;
    QList<FnChartXLabel*> m_xlabels;
    QList<FnChartValues*> m_series;
    WidgetHelper* m_helper;
};

#endif // FNCHART_H

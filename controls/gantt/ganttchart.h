#ifndef GANTTCHART_H
#define GANTTCHART_H

#include <QWidget>
#include "../base/widgethelper.h"
#include <QDate>
#include <QDebug>
#include "ganttmonth.h"
#include "ganttday.h"
#include "ganttcolumn.h"
#include "gantttask.h"
#include "editganttdatespandialog.h"
#include <QMouseEvent>
#include <QMenu>
#include <QColorDialog>
namespace Ui
{
class GanttChart;
}

class GanttChart : public QWidget
{
    Q_OBJECT

public:
    explicit GanttChart(QWidget* parent = nullptr);
    ~GanttChart();

    int minYear() const;
    void setMinYear(int newMinYear);

    int maxYear() const;
    void setMaxYear(int newMaxYear);
    void applyRange();
    void paintEvent(QPaintEvent* event);
    QList<GanttMonth*> m_months;
    QList<GanttDay*> m_days;
    QMap<QString, GanttDay*> m_dayInfos;
    QList<GanttColumn*> m_columns;
    QList<GanttTask*> m_tasks;
    QList<GanttTask*> m_selectedTasks;
    void addColumn(QString caption, int columnWidth);
    void addTask(GanttTask* task);
public slots:
    void onMenuActionTriggered();
protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
private:
    Ui::GanttChart* ui;
    int m_minYear;
    int m_maxYear;
    int m_dayWidth;
    WidgetHelper* m_helper;
    int m_columnsWidth;

};

#endif // GANTTCHART_H

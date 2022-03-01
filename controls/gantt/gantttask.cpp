#include "gantttask.h"

GanttTask::GanttTask(QObject* parent) : QObject(parent)
{
    m_startDate = QDate::currentDate();
    m_endDate = QDate::currentDate();
    m_backgroundColor = QColor(84, 128, 177);

}

void GanttTask::setValue(QString key, QString value)
{
    m_taskValues[key] = value;

}

QString GanttTask::value(QString key)
{
    return  m_taskValues[key];

}

const QDate& GanttTask::startDate() const
{
    return m_startDate;
}

void GanttTask::setStartDate(const QDate& newStartDate)
{
    m_startDate = newStartDate;
}

const QDate& GanttTask::endDate() const
{
    return m_endDate;
}

void GanttTask::setEndDate(const QDate& newEndDate)
{
    m_endDate = newEndDate;
}

const QRect& GanttTask::rect() const
{
    return m_rect;
}

void GanttTask::setRect(const QRect& newRect)
{
    m_rect = newRect;
}

const QRect& GanttTask::spanRect() const
{
    return m_spanRect;
}

void GanttTask::setSpanRect(const QRect& newSpanRect)
{
    m_spanRect = newSpanRect;
}

const QColor& GanttTask::backgroundColor() const
{
    return m_backgroundColor;
}

void GanttTask::setBackgroundColor(const QColor& newBackgroundColor)
{
    m_backgroundColor = newBackgroundColor;
}

const QString& GanttTask::showInfo() const
{
    return m_showInfo;
}

void GanttTask::setShowInfo(const QString& newShowInfo)
{
    m_showInfo = newShowInfo;
}

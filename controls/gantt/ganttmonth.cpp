#include "ganttmonth.h"

GanttMonth::GanttMonth(QObject* parent) : QObject(parent)
{

}

void GanttMonth::setYear(int newYear)
{
    m_year = newYear;
}

void GanttMonth::setMonth(int newMonth)
{
    m_month = newMonth;
}

int GanttMonth::days() const
{
    return m_days;
}

void GanttMonth::setDays(int newDays)
{
    m_days = newDays;
}

const QRect& GanttMonth::rect() const
{
    return m_rect;
}

void GanttMonth::setRect(const QRect& newRect)
{
    m_rect = newRect;
}

int GanttMonth::year() const
{
    return m_year;
}

int GanttMonth::month() const
{
    return m_month;
}

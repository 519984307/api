#include "ganttday.h"

GanttDay::GanttDay(QObject* parent) : QObject(parent)
{

}

int GanttDay::year() const
{
    return m_year;
}

void GanttDay::setYear(int newYear)
{
    m_year = newYear;
}

int GanttDay::month() const
{
    return m_month;
}

void GanttDay::setMonth(int newMonth)
{
    m_month = newMonth;
}

int GanttDay::day() const
{
    return m_day;
}

void GanttDay::setDay(int newDay)
{
    m_day = newDay;
}

const QRect& GanttDay::rect() const
{
    return m_rect;
}

void GanttDay::setRect(const QRect& newRect)
{
    m_rect = newRect;
}

int GanttDay::weekDay() const
{
    return m_weekDay;
}

void GanttDay::setWeekDay(int newWeekDay)
{
    m_weekDay = newWeekDay;
}

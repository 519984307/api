#include "peroidinfo.h"

PeroidInfo::PeroidInfo(QObject* parent) : QObject(parent)
{

}

int PeroidInfo::startYear() const
{
    return m_startYear;
}

void PeroidInfo::setStartYear(int newStartYear)
{
    m_startYear = newStartYear;
}

int PeroidInfo::startMonth() const
{
    return m_startMonth;
}

void PeroidInfo::setStartMonth(int newStartMonth)
{
    m_startMonth = newStartMonth;
}

int PeroidInfo::startDay() const
{
    return m_startDay;
}

void PeroidInfo::setStartDay(int newStartDay)
{
    m_startDay = newStartDay;
}

int PeroidInfo::startHour() const
{
    return m_startHour;
}

void PeroidInfo::setStartHour(int newStartHour)
{
    m_startHour = newStartHour;
}

int PeroidInfo::startMinute() const
{
    return m_startMinute;
}

void PeroidInfo::setStartMinute(int newStartMinute)
{
    m_startMinute = newStartMinute;
}

int PeroidInfo::endYear() const
{
    return m_endYear;
}

void PeroidInfo::setEndYear(int newEndYear)
{
    m_endYear = newEndYear;
}

int PeroidInfo::endMonth() const
{
    return m_endMonth;
}

void PeroidInfo::setEndMonth(int newEndMonth)
{
    m_endMonth = newEndMonth;
}

int PeroidInfo::endDay() const
{
    return m_endDay;
}

void PeroidInfo::setEndDay(int newEndDay)
{
    m_endDay = newEndDay;
}

int PeroidInfo::endHour() const
{
    return m_endHour;
}

void PeroidInfo::setEndHour(int newEndHour)
{
    m_endHour = newEndHour;
}

int PeroidInfo::endMinute() const
{
    return m_endMinute;
}

void PeroidInfo::setEndMinute(int newEndMinute)
{
    m_endMinute = newEndMinute;
}

QString PeroidInfo::info() const
{
    return m_info;
}

void PeroidInfo::setInfo(QString newInfo)
{
    m_info = newInfo;
}

bool PeroidInfo::timeInRange(int hour, int minute)
{
    int t1 = m_startHour * 60 + m_startMinute;
    int t2 = m_endHour * 60 + m_endMinute;
    int t = hour * 60 + minute;
    if ((t >= t1) && (t <= t2))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool PeroidInfo::timeInRange(int hour, int minute, int hour1, int minute1, int hour2, int minute2)
{
    int t1 = hour1 * 60 + minute1;
    int t2 = hour2 * 60 + minute2;
    int t = hour * 60 + minute;
    if ((t >= t1) && (t <= t2))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool PeroidInfo::timeInRange()
{
    QTime tm = QTime::currentTime();
    return timeInRange(tm.hour(), tm.minute());
}

void PeroidInfo::setRangeInfo(QTime startTime, QTime endTime, QString info)
{
    m_startHour = startTime.hour();
    m_startMinute = startTime.minute();
    m_endHour = endTime.hour();
    m_endMinute = endTime.minute();
    m_info = info;
}

QTime PeroidInfo::startTime()
{
    QTime tm;
    tm.setHMS(m_startHour, m_startMinute, 0, 0);
    return tm;
}

QTime PeroidInfo::endTime()
{
    QTime tm;
    tm.setHMS(m_endHour, m_endMinute, 0, 0);
    return tm;
}
